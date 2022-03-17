#pragma once
extern "C"
{
#include <libavformat/avformat.h>
}

class MMAVPacket
{
public:
	MMAVPacket();
	~MMAVPacket();
private:
	AVPacket* pkt = nullptr;
};


class MMAVReader	
{
public:
	MMAVReader();
	~MMAVReader();

	int Open(const char* path);
	int Close();

	int Read(MMAVPacket* path);
private:
	AVFormatContext* formatCtx = nullptr;
};