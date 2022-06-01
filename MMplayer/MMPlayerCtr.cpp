#include "MMplayer.h"

MMPlayerCtr::MMPlayerCtr() {

}

MMPlayerCtr::~MMPlayerCtr() {

}



void MMPlayerCtr::run() {
	MMPlayerReaderThread readerThread("A:/videoTemplate.mp4", this);
	readerThread.Start();


	//��ȡ�߳�����ʱ�� startTime
	long long startTime = MMAVTime::GetTime();

	MMAVFrame* videoFrame = nullptr;
	MMAVFrame* audioFrame = nullptr;

	while (!stopFlag) {
		// ���̹߳���һ��ʱ�䣬��ֹ���ѭ������cpu����
		std::this_thread::sleep_for(std::chrono::microseconds(1));

		//��ȡ��ǰʱ�� nowTime
		long long nowTime = MMAVTime::GetTime();

		//��ȡ��ǰʱ��Ϳ�ʼʱ��Ĳ�ֵ duringTime
		long long duringTime = nowTime - startTime;
		
		//printf("duringTime:%lld\n", duringTime);

		//����Ƶ��������л�ȡһ֡����Ƶ
		if (videoFrame == nullptr) {
			//����ȡһ֡��Ƶ
			videoQueue.Pop(&videoFrame);
		}
		
		if (videoFrame != nullptr) {
			//�ж��Ƿ�Ҫ������֡��Ƶ
			// ���framePts <= duringTime
			if (videoFrame->GetPts() <= duringTime) {
				//��������
				printf("Video Frame: %lld\n", videoFrame->GetPts());
				delete videoFrame;
				videoFrame = nullptr;
			}
			else {
				//�ȴ�����ʱ�����ţ��ȴ�״̬��Э��������Ƶ��
			}
		}

		//��audio��������л�ȡһ֡��audio
		if (audioFrame == nullptr) {
			audioQueue.Pop(&audioFrame);
		}

		if (audioFrame != nullptr) {
			//�ж��Ƿ�Ҫ������֡audio
			// ���frame_time <= during_time
			if (audioFrame->GetPts() <= duringTime) {
				//��������
				printf("Audio Frame: %lld\n", audioFrame->GetPts());
				delete audioFrame;
				audioFrame = nullptr;
			}
			else {
				//�ȴ�����ʱ�����ţ��ȴ�״̬��
			}
		}
	}
	readerThread.Stop();
}

int MMPlayerCtr::GetVideoQueueSize() {
	return videoQueue.Size();
}

int MMPlayerCtr::GetAudioQueueSize() {
	return audioQueue.Size();
}

int MMPlayerCtr::PushFrameToVideoQueue(MMAVFrame* frame) {
	return videoQueue.Push(frame);
}

int MMPlayerCtr::PushFrameToAudioQueue(MMAVFrame* frame) {
	return audioQueue.Push(frame);
}