#include "MMplayer.h"
#define MAX_FRAME 10

MMPlayerDecoderThread::MMPlayerDecoderThread(MMPlayerCtr* _playerCtr, MMDecoderType _type) {
	decoder = new MMAVDecoder();
	playerCtr = _playerCtr;
	type = _type;
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

int MMPlayerDecoderThread::GetPacketQueueSize() {
	return packetQueue.Size();
}

void MMPlayerDecoderThread::run() {
	int frameCount = 0;

	// 解码操作
	while (!stopFlag) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		//判断队列中如果已经有较多音视频帧存在，那么就自旋状态（防止大量解码占用内存）
		if (type == MMDecoderType::MMDECODER_TYPE_VIDEO) {
			if (playerCtr->GetVideoQueueSize() > MAX_FRAME) {
				continue;
			}
		}
		else if (type == MMDecoderType::MMDECODER_TYPE_AUDIO) {
			if (playerCtr->GetAudioQueueSize() > MAX_FRAME) {
				continue;
			}
		}

		MMAVPacket* pkt = nullptr;
		int ret = packetQueue.Pop(&pkt);
		if (ret) {
			//队列为空，无法取出packet
			continue;
		}

		decoder->SendPacket(pkt);
		while (true) {
			MMAVFrame* frame = new MMAVFrame();
			ret = decoder->RecvFrame(frame);
			if (ret) {
				break;
			}
			frameCount++;
			// printf("Decoder Success: %d\n", frameCount);
			// std::this_thread::sleep_for(std::chrono::seconds(1));

			// 通过 playerCtr 的句柄，想起塞入 Frame 数据
			if (type == MMDecoderType::MMDECODER_TYPE_VIDEO) {
				playerCtr->PushFrameToVideoQueue(frame);
			}
			else if (type == MMDecoderType::MMDECODER_TYPE_AUDIO) {
				playerCtr->PushFrameToAudioQueue(frame);
			}	
		}
	}
}
