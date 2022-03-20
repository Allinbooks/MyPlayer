#include "MMAV.h"
#include"MMAVPacketPrivate.h"

MMAVReader::MMAVReader()
{
	mmp = new MMAVPacketPrivate();
	mmp->formatCtx =  avformat_alloc_context();
}
MMAVReader::~MMAVReader()
{
	if (mmp->formatCtx != nullptr) {
		avformat_free_context(mmp->formatCtx);
		mmp->formatCtx = nullptr;
	}

}

int MMAVReader::Open(const char* path)
{
	if ((mmp->formatCtx == nullptr)||(path == nullptr)) {
		return -1;
	}
	// return 0 on success
	int res = avformat_open_input(&mmp->formatCtx, path, nullptr, nullptr);
	
	if (!res) {
		avformat_find_stream_info(mmp->formatCtx,nullptr);
	}

	return res;
}
int MMAVReader::Close()
{
	if (mmp->formatCtx == nullptr) {
		return -1;
	}
	avformat_close_input(&mmp->formatCtx);
	return 0;
}

int MMAVReader::Read(MMAVPacket* packet)
{
	if ((mmp->formatCtx == nullptr) || (packet == nullptr)) {
		return -1;
	}
	int res = av_read_frame(mmp->formatCtx, packet->imp->pkt);
	return res;
}