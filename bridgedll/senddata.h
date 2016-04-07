/*************************************************
����:��γ
ʱ��:2016-01-10
����:ͨ��UdpЭ�鷢�����ݣ������з������
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
* Ĭ�����ɵ�UDPData��ͷ����Ϊ6�����ݳ���Ϊ768
******************************************************/
class SendData
{
public:
	SendData();
	SendData(string ip, int port);
	SendData(string ip, int port, int *data, int dataLength);
	~SendData();

	//ʵ����LED�����ߴ�.xlsx�����ʵ�֡��õ�ÿһ��port����ʵ��ʹ�õĵ���
	void setCylinderConf(int m_turnNum, int m_rStep, int m_bConsloeType, int m_verNum, int m_horDistance, int m_verDistance);
	void allocateResources();//������Դ

	bool setData(int *data, int len = 0);      //����Ҫ���͵�����
	void setData(FrameData* frame);
	bool setNetworkInfo(string ip, int port);
	
	void send37();								//����UDP����
	void send();								//����UDP����
protected:
	static unsigned long udpCount;                 //udp���ܸ���/2
private:
	SOCKET client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in sin;
	int len;

	int *data;                             //Ҫ���͵�����
	int dataLength;                        //Ҫ���͵����ݳ���
	FrameData* frame;                      //һ֡���ݣ�2D or 3D��
	map<int, int> result;                  //�洢ÿ��port led��ʵ��ʹ�ø���
	int eachFrameUdpNum;				   //һ֡ udp�ĸ���

	UDPData* udp;
	SaveData<char>* saveD;
    
	void branchPort();					   //��Port
	void ToUDPDatas();                     //װΪudp��׼���͸�ʽ
	void IntToChars(int* src, char* dst, int srcLen);//int ת char
	void init();
};

#endif // SENDDATA_H
