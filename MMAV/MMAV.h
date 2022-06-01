#pragma once
#include <bits/stdc++.h>

class MMAVPacketPrivate;
class MMAVReaderPrivate;
class MMAVDecoderPrivate;
class MMAVStreamPrivate;
class MMAVFramePrivate;

class MMAVStream;


class MMAVPacket
{
public:
	MMAVPacket();
	~MMAVPacket();
	int GetIndex();
	MMAVPacketPrivate* imp = nullptr;
};

class MMAVFrame
{
public:
	MMAVFrame();
	~MMAVFrame();

	int VideoPrint();
	int AudioPrint();

	int GetY(unsigned char* y);
	int GetU(unsigned char* u);
	int GetV(unsigned char* v);

	int GetW();
	int GetH();

	long long GetPts();
	MMAVFramePrivate* imp = nullptr;
};

class MMAVReader	
{
public:
	MMAVReader();
	~MMAVReader();

	int Open(const char* path);

	int GetStreamCount();
	int GetStream(MMAVStream* stream, int streamId);

	int GetVideoStreamIndex();
	int GetAudioStreamIndex();

	int Close();

	int Read(MMAVPacket* path);
	MMAVReaderPrivate* imp = nullptr;
};

class MMAVDecoder
{
public:
	MMAVDecoder();
	~MMAVDecoder();

	int Init(MMAVStream* stream);

	int SendPacket(MMAVPacket* pkt);

	int RecvFrame(MMAVFrame* frame);

	int Close();
private:
	MMAVDecoderPrivate* imp = nullptr;

	int timebaseNum = 0;
	int timebaseDen = 0;
};

class MMAVStream
{
public:
	MMAVStream();
	~MMAVStream();

	int timebaseNum = 0;
	int timebaseDen = 0;
	int streamIndex = -1;
	MMAVStreamPrivate* imp = nullptr;
private:
	
};

class MMAVTime
{
public:
	static long long GetTime();
};