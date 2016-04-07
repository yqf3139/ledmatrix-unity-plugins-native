/*************************************************
作者:陈纬
时间:2016-01-10
内容:存储UDP数据包数据
**************************************************/
#ifndef UDPDATA_H
#define UDPDATA_H

#include <string.h>
#include <stdio.h>
class UDPData
{
public:
	UDPData(int headLen = 0, int bodyLen = 0);
	UDPData(const UDPData& other);
	~UDPData();

	int getHeadLength();                    //获取head的长度
	int getBodyLength();                    //获取body的长度
	int getLength();                        //获取UDPData总长度
	bool setHead(char *head = NULL, int len = 0);  //设置head中的内容
	bool setiHead(int i, char data);        //设置head中第i位数据
	bool setBody(char *body = NULL, int len = 0);  //设置body中的内容
	bool setiBody(int i, char data);        //设置body中第i位数据
	bool getData(char * data);			//获取UDPData中的数据
private:
	char *head;                     //UDP数据中的头
	char *body;                     //UDP数据中的负载
	int headLength;                 //head长度
	int bodyLength;                 //body长度
};

#endif // UDPDATA_H
