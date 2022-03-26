#pragma once
#include "MMAV.h"
extern "C"
{
#include <libavutil\frame.h>
#include <libavutil\pixdesc.h>
}
class MMAVFramePrivate
{
public:
	AVFrame* frame = nullptr;
};
