#include "framedata.h"
FrameData::FrameData(int x, int y)
{
	this->width = x;
	this->height = y;
	this->lenth = 0;
	this->frameID = 0;
	this->dataLen = x * y;
	this->data = NULL;
}

FrameData::FrameData(int x, int y, int z)
{
	this->width = x;
	this->height = y;
	this->lenth = z;
	this->frameID = 0;
	this->dataLen = x * y * z;
	this->data = NULL;
}

FrameData::FrameData(const FrameData& other)
{
	this->width = other.width;
	this->height = other.height;
	this->lenth = other.lenth;

	this->dataLen = other.dataLen;
	this->frameID = other.frameID;
	this->data = new int[width * height];
	memcpy(this->data, other.data, width * height * 4);
}

FrameData::~FrameData()
{
	this->width = 0;
	this->height = 0;
	this->frameID = 0;
	this->dataLen = 0;
	if (NULL != this->data)
	{
		delete[] this->data;
		this->data = NULL;
	}
}

int FrameData::getWidth()
{
	return this->width;
}

int FrameData::getHeight()
{
	return this->height;
}

int FrameData::getLen()
{
	return this->dataLen;
}

int *FrameData::getData()
{
	return this->data;
}

int FrameData::getFrameID()
{
	return this->frameID;
}

void FrameData::setWidth(int width)
{
	this->width = width;
}
void FrameData::setHeight(int height)
{
	this->height = height;
}
void FrameData::setFrameID(int frameID)
{
	this->frameID = frameID;
}

bool FrameData::setData(int *data, int len)
{
	if (data == NULL)
	{
		printf("ERROR [FrameData:setData] Parameter \"data\" is null.");
		return false;
	}
	if (0 == len) {
		this->data = new int[getLen()];
		memcpy(this->data, data, getLen() * 4);
	}
	else {
		this->dataLen = len;
		this->data = new int[len];
		memcpy(this->data, data, len * 4);
	}
	return true;
}

//ÕÛ·µ
void FrameData::changeType()
{
	int* srcIn = this->data;
	int* dstOut = new int[width * height];
	int count = 0;
	bool isOk = true;
	for (int i = 0; i < width; i++) {
		if (isOk) {
			for (int j = height - 1; j >= 0; j--) {
				dstOut[count] = srcIn[i*height + j];
				count++;
			}
		}
		else {
			for (int j = 0; j < height; j++) {
				dstOut[count] = srcIn[i*height + j];
				count++;
			}
		}
		isOk = !isOk;
	}
	memcpy(data, dstOut, width * height * sizeof(int));
	delete[] dstOut;
}

//ºáÏò±ä×ÝÏò
void FrameData::changeType2()
{
	int* dstOut = new int[width * height];
	int k = 0;
	for (int i = 0; i < width; i++) {
		for (int j = height - 1; j >= 0; j--) {
			dstOut[k] = data[i + j * width];
			k++;
		}
	}
	memcpy(data, dstOut, width * height * sizeof(int));
	delete[] dstOut;
}
