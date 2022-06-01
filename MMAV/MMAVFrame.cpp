#pragma once
#include "MMAV.h"

#include "MMAVFramePrivate.h"

MMAVFrame::MMAVFrame()
{
	imp = new MMAVFramePrivate();
	imp->frame = av_frame_alloc();
}

MMAVFrame::~MMAVFrame()
{
	if (imp->frame != nullptr) {
		av_frame_free(&imp->frame);
		imp->frame = nullptr;
	}
	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}

int MMAVFrame::VideoPrint()
{
	std::cout << "Width: " << imp->frame->width << std::endl;
	std::cout << "Height: " << imp->frame->height << std::endl;

	AVPixelFormat format = (AVPixelFormat)imp->frame->format;

	char* str = (char*)malloc(128);
	str = av_get_pix_fmt_string(str, 128, format);

	std::cout << "Pixel Format: " << str << std::endl;
	free(str);

	for (int i = 0; i < AV_NUM_DATA_POINTERS; i++) {
		std::cout << "linesize[" << i << "]:" << imp->frame->linesize[i] << std::endl;
	}

	return 0;
}

int MMAVFrame::AudioPrint()
{
	int channel = imp->frame->channels;
	printf("Channel: %d\n", channel);
	printf("nb_samples: %d\n", imp->frame->nb_samples);
	printf("sample_rate: %d\n", imp->frame->sample_rate);
	

	AVSampleFormat format = (AVSampleFormat)(imp->frame->format);
	char* str = (char*)malloc(128);
	str = av_get_sample_fmt_string(str, 128, format);

	printf("Sample Format: %s\n", str);



	for (int i = 0; i < AV_NUM_DATA_POINTERS; i++) {
		std::cout << "linesize[" << i << "]:" << imp->frame->linesize[i] << std::endl;
	}
	return 0;
}

int MMAVFrame::GetW()
{
	return imp->frame->width;
}
int MMAVFrame::GetH()
{
	return imp->frame->height;
}

int MMAVFrame::GetY(unsigned char* y)
{
	int width = GetW();
	int height = GetH();
	/*memcpy(y, imp->frame->data[0], width * height);*/

	//循环拷贝可以去除每一帧的脏数据
	for (int i = 0; i < height; i++) {
		memcpy(y + i * width, imp->frame->data[0] + i * imp->frame->linesize[0], width);
	}
	return 0;
}
int MMAVFrame::GetU(unsigned char* u)
{
	int width = GetW() / 2;
	int height = GetH() / 2;
	for (int i = 0; i < height; i++) {
		memcpy(u + i * width, imp->frame->data[1] + i * imp->frame->linesize[1], width);
	}
	return 0;
}
int MMAVFrame::GetV(unsigned char* v)
{
	int width = GetW() / 2;
	int height = GetH() / 2;
	for (int i = 0; i < height; i++) {
		memcpy(v + i * width, imp->frame->data[2] + i * imp->frame->linesize[2], width);
	}
	return 0;
}

long long MMAVFrame::GetPts() {
	return (long long)(imp->ptsSec * 1000);
}