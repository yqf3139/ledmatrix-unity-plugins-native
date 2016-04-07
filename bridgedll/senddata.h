/*************************************************
作者:陈纬
时间:2016-01-10
内容:通过Udp协议发送数据，并进行封包操作
**************************************************/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#ifndef SENDDATA_H
#define SENDDATA_H
#include <WinSock2.h>
#include <string>
#include <vector>
#include <map>
#include "framedata.h"
#include "savedate.h"
#include "cylinderconf.h"
#include "udpdata.h"

#pragma comment(lib, "ws2_32.lib") 
using std::vector;
using std::map;
using std::string;
/*******************************************************
*
*
* 默认生成的UDPData的头长度为6，数据长度为768
******************************************************/
class SendData
{
public:
	SendData();
	SendData(string ip, int port);
	SendData(string ip, int port, int *data, int dataLength);
	~SendData();

	//实验室LED灯柱尺寸.xlsx报表的实现。得到每一个port口上实际使用的灯数
	void setCylinderConf(int m_turnNum, int m_rStep, int m_bConsloeType, int m_verNum, int m_horDistance, int m_verDistance);
	void allocateResources();//分配资源

	bool setData(int *data, int len = 0);      //设置要发送的数据
	void setData(FrameData* frame);
	bool setNetworkInfo(string ip, int port);
	
	void send37();								//发送UDP数据
	void send();								//发送UDP数据
protected:
	static unsigned long udpCount;                 //udp包总个数/2
private:
	SOCKET client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in sin;
	int len;

	int *data;                             //要发送的数据
	int dataLength;                        //要发送的数据长度
	FrameData* frame;                      //一帧数据（2D or 3D）
	map<int, int> result;                  //存储每个port led灯实际使用个数
	int eachFrameUdpNum;				   //一帧 udp的个数

	UDPData* udp;
	SaveData<char>* saveD;
    
	void branchPort();					   //分Port
	void ToUDPDatas();                     //装为udp标准发送格式
	void IntToChars(int* src, char* dst, int srcLen);//int 转 char
	void init();
};

#endif // SENDDATA_H
