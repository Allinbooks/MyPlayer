#pragma once
#include "MMAV.h"
extern "C"
{
#include <libavcodec/avcodec.h>
}
class MMAVDecoderPrivate
{
public:
	AVCodecContext* codecContext = nullptr;
};