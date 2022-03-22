#pragma once
#include"MMAV.h"
extern "C"
{
	#include "libavformat\avformat.h"
}

class MMAVStreamPrivate
{
public:
	AVCodecParameters* codecpar = nullptr;
};