#include "MMAV.h"
#include "MMAVDecoderPrivate.h"
#include "MMAVStreamPrivate.h"


MMAVDecoder::MMAVDecoder()
{
	imp = new MMAVDecoderPrivate();
	imp->codecContext = avcodec_alloc_context3(nullptr);
}

MMAVDecoder::~MMAVDecoder()
{
	if (imp->codecContext != nullptr) {
		avcodec_free_context(&imp->codecContext);
		imp->codecContext = nullptr;
	}
	if (imp != nullptr) {
		delete imp;
		imp->codecContext = nullptr;
	}
	
}

int MMAVDecoder::Init(MMAVStream* stream)
{
	avcodec_parameters_to_context(imp->codecContext, stream->imp->codecpar);

	const AVCodec* avCodec = avcodec_find_decoder(imp->codecContext->codec_id);
	//AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options
	int ret = avcodec_open2(imp->codecContext, avCodec, nullptr);
	if (ret) {
		std::cout << "avcodec_open2 fail ret:" << ret << std::endl;
		return -1;
	}

	return 0;
}
int MMAVDecoder::SendPacket(MMAVPacket* pkt)
{
	return 0;
}

int MMAVDecoder::RecvFrame()
{

	return 0;
}