#include "MMplayer.h"

MMPlayerDecoderThread::MMPlayerDecoderThread() {
	decoder = new MMAVDecoder();
}


MMPlayerDecoderThread::~MMPlayerDecoderThread() {
	if (decoder != nullptr) {
		delete decoder;
		decoder = nullptr;
	}

}

int MMPlayerDecoderThread::Init(MMAVStream* avstream) {
	return decoder->Init(avstream);
}

int MMPlayerDecoderThread::PutPacket(MMAVPacket* pkt) {
	return packetQueue.Push(pkt);
}

void MMPlayerDecoderThread::run() {
	int frameCount = 0;

	// �������
	while (!stopFlag) {
		MMAVPacket* pkt = nullptr;
		int ret = packetQueue.Pop(&pkt);
		if (ret) {
			//����Ϊ�գ��޷�ȡ��packet
			continue;
		}

		decoder->SendPacket(pkt);
		while (true) {
			MMAVFrame frame;
			ret = decoder->RecvFrame(&frame);
			if (ret) {
				break;
			}
			frameCount++;
			printf("Decoder Success: %d\n", frameCount);
			std::this_thread::sleep_for(std::chrono::seconds(1));
			
		}

	}

}

int MMPlayerDecoderThread::GetPacketQueueSize() {
	return packetQueue.Size();
}
