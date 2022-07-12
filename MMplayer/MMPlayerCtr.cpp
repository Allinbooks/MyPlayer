#include "MMplayer.h"

MMPlayerCtr::MMPlayerCtr(double _seekTime) {

	seekTime = _seekTime;
}

MMPlayerCtr::~MMPlayerCtr() {

}



void MMPlayerCtr::run() {
	MMPlayerReaderThread readerThread("A:/videoTemplate.mp4", seekTime, this);
	readerThread.Start();


	//获取线程启动时间 startTime
	long long startTime = MMAVTime::GetTime();

	//解决多次暂停的时间戳计算有误的问题
	long long sleepCountTime = 0;

	MMAVFrame* videoFrame = nullptr;
	MMAVFrame* audioFrame = nullptr;

	while (!stopFlag) {
		// 将线程挂起一段时间，防止多次循环导致cpu吃满
		std::this_thread::sleep_for(std::chrono::microseconds(1));

		long long sleepTimeStart = MMAVTime::GetTime();
		while (status == MMPlayerCtrStatus::MMPLAY_CTR_STATUS_PAUSEING) {
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
		long long sleepTimeEnd = MMAVTime::GetTime();
		long long sleepDuring = sleepTimeEnd - sleepTimeStart;
		sleepCountTime += sleepDuring;

		//获取当前时间 nowTime
		long long nowTime = MMAVTime::GetTime();

		//获取当前时间和开始时间的差值 duringTime
		long long duringTime = nowTime - startTime - sleepCountTime;
		

		duringTime += (long long)seekTime * 1000;
		//printf("duringTime:%lld\n", duringTime);

		//从视频缓冲队列中获取一帧是视频
		if (videoFrame == nullptr) {
			//尝试取一帧视频
			videoQueue.Pop(&videoFrame);
		}
		
		//如果这个帧的时间小于seek的时间，直接放弃这个帧不再处理
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

			//判断是否要播放这帧视频
			// 如果framePts <= duringTime
			if (videoFrame->GetPts() <= duringTime) {
				//立即播放
				printf("Video Frame: %lld\n", videoFrame->GetPts());
				delete videoFrame;
				videoFrame = nullptr;
			}
			else {
				//等待合适时机播放（等待状态或协助处理音频）
			}
		}

		//从audio缓冲队列中获取一帧是audio
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
			//判断是否要播放这帧audio
			// 如果frame_time <= during_time
			if (audioFrame->GetPts() <= duringTime) {
				//立即播放
				//printf("Audio Frame: %lld\n", audioFrame->GetPts());
				delete audioFrame;
				audioFrame = nullptr;
			}
			else {
				//等待合适时机播放（等待状态）
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