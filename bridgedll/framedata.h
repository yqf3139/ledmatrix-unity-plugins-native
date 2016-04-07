/*************************************************
作者:陈纬
时间:2016-01-10
内容:存储帧数据
**************************************************/
#ifndef FRAMEDATA_H
#define FRAMEDATA_H
#include <string.h>
#include <stdio.h>
class FrameData
{
public:
	FrameData(int x = 0, int y = 0);
	FrameData(int x, int y, int z);
	FrameData(const FrameData &other);
	~FrameData();

	void setWidth(int width);                     //获取帧的宽度
	void setHeight(int height);                    //获取帧的高度
	void setFrameID(int frameID);
	bool setData(int *data, int len = 0);//设置帧中的数据

	int getWidth();                     //获取帧的宽度
	int getHeight();                    //获取帧的高度
	int getLen();
	int getFrameID();                   //获取帧号
	int *getData();                     //获取帧中的int数组数据

	void changeType();  //折返
	void changeType2(); //横向变纵向
private:
	int width;                 //帧的宽度，与LED灯阵的宽度对应
	int height;                //帧的高度，与LED灯阵的高度对应
	int lenth;                 //帧的长度，与LED灯阵的高度对应

	int dataLen;               //数据长度
	int frameID;               //帧号
	int *data;                 //帧中的数据
};

#endif // FRAMEDATA_H
