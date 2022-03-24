#pragma once
#include "MMAV.h"
extern "C"
{
#include <libavutil\frame.h>
}
class MMAVFramePrivate
{
public:
	AVFrame* frame = nullptr;
};
