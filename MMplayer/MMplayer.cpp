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
int main() {
	MMAVReader reader;

	int ret = reader.Open("A://7.class template 7.mp4");
	if (ret) {
		cout << "Open file fail!" << endl;
		return -1;
	}

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

	while (true)
	{
		MMAVPacket pkt;
		ret = reader.Read(&pkt);
		if (ret) {
			break;
		}
		//cout << "Read Packet Success" << endl;

		int streamIndex = pkt.GetIndex(); //寻找适用的解码器

		MMAVDecoder* decoder = decoderList[streamIndex];

		int ret = decoder->SendPacket(&pkt);
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




	reader.Close();

	for (int i = 0; i < decoderList.size(); i++) {
		decoderList[i]->Close();
		delete decoderList[i];
	}
	decoderList.clear();
	return 0;
}
