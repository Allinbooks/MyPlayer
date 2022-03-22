#pragma once
#include <bits/stdc++.h>

class MMAVPacketPrivate;
class MMAVReaderPrivate;
class MMAVDecoderPrivate;
class MMAVStreamPrivate;


class MMAVPacket
{
public:
	MMAVPacket();
	~MMAVPacket();
	MMAVPacketPrivate* imp = nullptr;
};

class MMAVReader	
{
public:
	MMAVReader();
	~MMAVReader();

	int Open(const char* path);

	int GetStreamCount();
	int GetStream(MMAVStream* stream, int streamId);

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

	int RecvFrame();

private:
	MMAVDecoderPrivate* imp = nullptr;
};

class MMAVStream
{
public:
	MMAVStream();
	~MMAVStream();

	int streamIndex = -1;
	MMAVStreamPrivate* imp = nullptr;
private:
	
};