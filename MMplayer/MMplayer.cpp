// MMplayer.cpp: 定义应用程序的入口点。
//

#include "MMplayer.h"
#include "MMThread/MMThread.h"
using namespace std;

static void threadfun(int m) {
	while (true)
	{
		cout << "hello world" << m << endl;
	}
	
}

void threadfunction(int i) {
	while (true) {
		cout << "xiaoming " << i << endl;
	}
}

class MyMMThread : public MMThread
{
public:
	virtual void run()
	{
		printf("MyMMThread\n");
	}
};

int main_tread()
{

	//thread t(threadfun, 1);
	//thread h(threadfunction, 2);
	//t.join();
	//h.join();
	////t.detach();
	////t.joinable();

	MyMMThread t;
	t.Start();
	this_thread::sleep_for(chrono::seconds(2));
	cout << "Hello MMplayer." << endl;
	return 0;
}
#include "MMAV/MMAV.h"
#include "MMQueue/MMQueue.h"

int main() {
	MMQueue<MMAVPacket> packetQueue;
	MMAVReader reader;

	int ret = reader.Open("A://44315a0bc6fb773fc280f0cb97bedde6.mp4");
	if (ret) {
		cout << "Open file fail!" << endl;
		return -1;
	}

	int videoStreamIndex = reader.GetVideoStreamIndex();
	int audioStreamIndex = reader.GetAudioStreamIndex();

	cout <<"videoStreamIndex: " << videoStreamIndex << endl;
	cout <<"audioStreamIndex: " << audioStreamIndex << endl;

	std::vector<MMAVDecoder*> decoderList;

	int streamCount = reader.GetStreamCount();
	for (int i = 0; i < streamCount; i++) {
		MMAVStream avStream;
		reader.GetStream(&avStream, i);

		cout << "StreamIndex: " << avStream.streamIndex << endl;

		MMAVDecoder* decoder = new MMAVDecoder();
		int ret = decoder->Init(&avStream);
		if (ret) {
			cout << "Init decoder fail" << endl;
		}

		decoderList.push_back(decoder);
	}

	FILE* f = fopen("A://44315a0bc6fb773fc280f0cb97bedde6.yuv", "wb");

	while (true)
	{
		MMAVPacket *pkt = new MMAVPacket();

		ret = reader.Read(pkt);

		if (ret) {
			break;
		}
		//cout << "Read Packet Success" << endl;


		packetQueue.Push(pkt);

		int streamIndex = pkt->GetIndex(); //寻找适用的解码器

		MMAVDecoder* decoder = decoderList[streamIndex];

		int ret = decoder->SendPacket(pkt);
		if (ret) {
			continue;
		}
		while (true) {
			MMAVFrame frame;
			int ret = decoder->RecvFrame(&frame);
			if (ret) {
				break; // 获取不到就跳出循环
			}
			
			//Recv success
			//判断当前帧是音频还是视频
			if (streamIndex == videoStreamIndex) {
				frame.VideoPrint();

				int width = frame.GetW();
				int height = frame.GetH();

				unsigned char* y = (unsigned char*)malloc(width * height);
				unsigned char* u = (unsigned char*)malloc(width * height / 4);
				unsigned char* v = (unsigned char*)malloc(width * height / 4);

				frame.GetY(y);
				frame.GetU(u);
				frame.GetV(v);

				fwrite(y, width * height, 1, f);
				fwrite(u, width * height/4, 1, f);
				fwrite(v, width * height/4, 1, f);


				free(y);
				free(u);
				free(v);
			}
			if (streamIndex == audioStreamIndex) {
				frame.AudioPrint();
			}
			
		}
		
	}

	for (int i = 0; i < decoderList.size(); i++) {
		MMAVDecoder* decoder = decoderList[i];
		// 清空解码器
		int ret = decoder->SendPacket(nullptr);
		while (true) {
			MMAVFrame frame;
			int ret = decoder->RecvFrame(&frame);
			if (ret) {
				break;
			}

			//Recv success

		}
	}

	while (packetQueue.Size() > 0) {
		MMAVPacket* pkt = nullptr;
		packetQueue.Pop(&pkt);

		printf("Packet Size(): %d\n", packetQueue.Size());

		if (pkt != nullptr) {
			delete pkt;
		}
	}

	reader.Close();

	for (int i = 0; i < decoderList.size(); i++) {
		decoderList[i]->Close();
		delete decoderList[i];
	}
	decoderList.clear();
	fclose(f);
	return 0;
}
