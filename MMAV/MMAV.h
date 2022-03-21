#pragma once


class MMAVPacketPrivate;
class MMAVReaderPrivate;
class MMAVDecoderPrivate;
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
	int Close();

	int Read(MMAVPacket* path);
	MMAVReaderPrivate* imp = nullptr;
};

class MMAVDecoder
{
public:
	MMAVDecoder();
	~MMAVDecoder();

	int Init();

private:
	MMAVDecoderPrivate* imp = nullptr;
};