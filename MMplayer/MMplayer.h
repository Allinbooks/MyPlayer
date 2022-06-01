// MMplayer.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once
#include "MMThread/MMThread.h"
#include "MMAV/MMAV.h"
#include "MMQueue/MMQueue.h"
#include <string>

enum MMDecoderType {
	MMDECODER_TYPE_VIDEO = 0,
	MMDECODER_TYPE_AUDIO
};

//控制音频和视频解码速度，处理音画不同步
class MMPlayerCtr : public MMThread {
public:
	MMPlayerCtr();
	~MMPlayerCtr();

	virtual void run();

	int GetVideoQueueSize();
	int GetAudioQueueSize();

	int PushFrameToVideoQueue(MMAVFrame* frame);
	int PushFrameToAudioQueue(MMAVFrame* frame);
private:
	MMQueue<MMAVFrame> videoQueue;
	MMQueue<MMAVFrame> audioQueue;

	MMAVFrame* frame = nullptr;

};

class MMPlayerReaderThread : public MMThread
{
public:
	MMPlayerReaderThread(std::string path, MMPlayerCtr* playerCtr);
	~MMPlayerReaderThread();

	virtual void run();

private:
	std::string path;
	MMPlayerCtr* playerCtr = nullptr;
};

class MMPlayerDecoderThread : public MMThread
{
public:
	MMPlayerDecoderThread(MMPlayerCtr* playerCtr, MMDecoderType type);
	~MMPlayerDecoderThread();

	virtual void run();

	//int Init(MMAVStream* stream);
	int Init(MMAVStream* avstream);

	int PutPacket(MMAVPacket* pkt);
	int GetPacketQueueSize();

private:
	MMAVDecoder* decoder = nullptr;
	MMQueue<MMAVPacket> packetQueue;

	MMPlayerCtr* playerCtr = nullptr;

	MMDecoderType type;
};

class MMplayer {
public:
	MMplayer(std::string path);
	~MMplayer();

	// 在Open()时创建一个线程，等待Stop()函数调用时，结束这个线程
	int Open();
	int Stop();

	int Play();
	int Pause();

	int Seek(double time);

private:
	std::string path;
	MMPlayerReaderThread* readerThread = nullptr;
	MMPlayerCtr* playerCtr = nullptr;
};
