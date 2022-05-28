﻿// MMplayer.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once
#include "MMThread/MMThread.h"
#include "MMAV/MMAV.h"
#include "MMQueue/MMQueue.h"
#include <string>

class MMPlayerReaderThread : public MMThread
{
public:
	MMPlayerReaderThread(std::string path);
	~MMPlayerReaderThread();

	virtual void run();

private:
	std::string path;
};

class MMPlayerDecoderThread : public MMThread
{
public:
	MMPlayerDecoderThread();
	~MMPlayerDecoderThread();

	virtual void run();

	//int Init(MMAVStream* stream);
	int Init(MMAVStream* avstream);

	int PutPacket(MMAVPacket* pkt);
	int GetPacketQueueSize();

private:
	MMAVDecoder* decoder = nullptr;
	MMQueue<MMAVPacket> packetQueue;
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
};
