#include "MMAV.h"

MMAVReader::MMAVReader()
{
	formatCtx =  avformat_alloc_context();
}
MMAVReader::~MMAVReader()
{
	if (formatCtx != nullptr) {
		avformat_free_context(formatCtx);
		formatCtx = nullptr;
	}

}

int MMAVReader::Open(const char* path)
{
	if ((formatCtx == nullptr)||(path == nullptr)) {
		return -1;
	}
	// return 0 on success
	int res = avformat_open_input(&formatCtx, path, nullptr, nullptr);
	
	if (!res) {
		avformat_find_stream_info(formatCtx,nullptr);
	}

	return res;
}
int MMAVReader::Close()
{
	if (formatCtx == nullptr) {
		return -1;
	}
	avformat_close_input(&formatCtx);
	return 0;
}

int MMAVReader::Read(MMAVPacket* packet)
{
	if ((formatCtx == nullptr) || (packet == nullptr)) {
		return -1;
	}
	int res = av_read_frame(formatCtx, packet->pkt);
	return res;
}