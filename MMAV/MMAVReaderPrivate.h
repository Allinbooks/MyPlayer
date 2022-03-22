#pragma once
#include "MMAV.h"
extern "C"
{
	#include <libavformat/avformat.h>
}
class MMAVReaderPrivate
{
public:
	AVFormatContext* formatCtx = nullptr;
};