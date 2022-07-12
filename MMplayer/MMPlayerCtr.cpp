#include "MMplayer.h"

MMPlayerCtr::MMPlayerCtr(double _seekTime) {

	seekTime = _seekTime;
}

MMPlayerCtr::~MMPlayerCtr() {

}



void MMPlayerCtr::run() {
	MMPlayerReaderThread readerThread("A:/videoTemplate.mp4", seekTime, this);
	readerThread.Start();


	//��ȡ�߳�����ʱ�� startTime
	long long startTime = MMAVTime::GetTime();

	//��������ͣ��ʱ����������������
	long long sleepCountTime = 0;

	MMAVFrame* videoFrame = nullptr;
	MMAVFrame* audioFrame = nullptr;

	while (!stopFlag) {
		// ���̹߳���һ��ʱ�䣬��ֹ���ѭ������cpu����
		std::this_thread::sleep_for(std::chrono::microseconds(1));

		long long sleepTimeStart = MMAVTime::GetTime();
		while (status == MMPlayerCtrStatus::MMPLAY_CTR_STATUS_PAUSEING) {
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
		long long sleepTimeEnd = MMAVTime::GetTime();
		long long sleepDuring = sleepTimeEnd - sleepTimeStart;
		sleepCountTime += sleepDuring;

		//��ȡ��ǰʱ�� nowTime
		long long nowTime = MMAVTime::GetTime();

		//��ȡ��ǰʱ��Ϳ�ʼʱ��Ĳ�ֵ duringTime
		long long duringTime = nowTime - startTime - sleepCountTime;
		

		duringTime += (long long)seekTime * 1000;
		//printf("duringTime:%lld\n", duringTime);

		//����Ƶ��������л�ȡһ֡����Ƶ
		if (videoFrame == nullptr) {
			//����ȡһ֡��Ƶ
			videoQueue.Pop(&videoFrame);
		}
		
		//������֡��ʱ��С��seek��ʱ�䣬ֱ�ӷ������֡���ٴ���
		if (videoFrame != nullptr) {
			if (videoFrame->GetPts() <= (long long)(seekTime * 1000)) {
				delete videoFrame;
				videoFrame = nullptr;
			}
		}

		if (videoFrame != nullptr) {
			if (videoFrame->GetPts() < (long long)(seekTime * 1000)) {
				delete videoFrame;
				videoFrame = nullptr;
			}

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
			if (audioFrame->GetPts() <= (long long)(seekTime * 1000)) {
				delete audioFrame;
				audioFrame = nullptr;
			}
		}

		if (audioFrame != nullptr) {
			//�ж��Ƿ�Ҫ������֡audio
			// ���frame_time <= during_time
			if (audioFrame->GetPts() <= duringTime) {
				//��������
				//printf("Audio Frame: %lld\n", audioFrame->GetPts());
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

int MMPlayerCtr::Play() {
	status = MMPlayerCtrStatus::MMPLAY_CTR_STATUS_PLAYING;
	return 0;
}

int MMPlayerCtr::Pause() {
	status = MMPlayerCtrStatus::MMPLAY_CTR_STATUS_PAUSEING;
	return 0;
}