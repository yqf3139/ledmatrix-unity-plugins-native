#include "senddata.h"
#include "config.h"
SendData::SendData()
{
	init();
}

SendData::SendData(string ip, int port)
{
	this->data = NULL;
	this->dataLength = 0;
	setNetworkInfo(ip, port);
	init();
}

SendData::SendData(string ip, int port, int * data, int dataLength)
{
	setNetworkInfo(ip, port);
	setData(data, dataLength);
	init();
}

void SendData::init()
{

}

SendData::~SendData()
{
	if (NULL != this->data)
	{
		delete this->data;
		this->data = NULL;
	}
	delete[] this->udp;
	delete[] this->saveD;
	udpCount = 0;
}

bool SendData::setNetworkInfo(string ip, int port)
{
	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(socketVersion, &wsaData) != 0)
	{
		return false;
	}
	this->client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	this->sin.sin_family = AF_INET;
	this->sin.sin_port = htons(port);
	//sin.sin_addr.s_addr = inet_pton(AF_INET,ip.c_str(),&sin.sin_addr);
	this->sin.sin_addr.s_addr = inet_addr(ip.c_str());
	this->len = sizeof(sin);
	return true;  
}

//实验室LED灯柱尺寸.xlsx报表的实现。得到每一个port口上实际使用的灯数
void SendData::setCylinderConf(int m_turnNum, int m_rStep, int m_bConsloeType, int m_verNum, int m_horDistance, int m_verDistance)
{
	CylinderConf* cyConf = new CylinderConf(m_turnNum, m_rStep, m_bConsloeType, m_verNum, m_horDistance, m_verDistance);
	result = cyConf->getEachPortLEDNum();
	allocateResources();
}

void SendData::allocateResources()
{
	this->eachFrameUdpNum = (result.size() + 2) * 2 * 2; //一帧 udp的个数
	this->udp = new UDPData[eachFrameUdpNum];
	this->saveD = new SaveData<char>[this->eachFrameUdpNum - 8];
}

bool SendData::setData(int *data, int len)
{
	//判断输入的数据是否超过标准
	if (0 > len)
	{
		printf("ERROR [SendData:setData] Data length %d is the wrong size.", len);
		return false;
	}
	this->dataLength = len;
	if (NULL == this->data)
		this->data = new int[len];
	memcpy(this->data, data, len * sizeof(int));
	return true;
}

void SendData::setData(FrameData* frame)
{
	this->frame = frame;
	setData(frame->getData(), frame->getLen());
}


void SendData::send37()
{
	//    char notice[37] = {
	//        0x02, 0x88, 0x02, 0x64, 0x05, 0x88, 0x00, 0x00,
	//        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	//        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	//        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	//        0x00, 0x00, 0x00, 0x00, 0x00 };

	char notice[37] = {
		0x02, 0x88, 0x02, 0x64, 0x08, 0x88, 0x88, 0x88,
		0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00 };
	//ws2811
	//    char notice[37] = {
	//        0x02, 0x19, 0x02, 0x64, 0x0c, 0x19, 0x19, 0x19,
	//        0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	//        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	//        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	//        0x00, 0x00, 0x00, 0x00, 0x00 };
	sendto(client, notice, 37, 0, (sockaddr *)&sin, len);
}

void SendData::send()
{
	branchPort();
	ToUDPDatas();
	char* src = new char[UDP_LEN];
	for (int i = 0; i < this->eachFrameUdpNum; i++)
	{
		this->udp[i].getData(src);
		sendto(client, src, UDP_LEN, 0, (sockaddr *)&sin, len);
	}
	delete[] src;
}

unsigned long SendData::udpCount = 0;
void SendData::ToUDPDatas()
{
	//vector<SaveData<char>* > dst = branchPort();//获得char 256*n 是否会自动释放
	int UDP_HEAD_LEN = 6;
	int UDP_BODY_LEN = 768;
	char *colorHead = new char[UDP_HEAD_LEN];
	char *colorBody = new char[UDP_BODY_LEN];
	memset(colorHead, 0x00, UDP_HEAD_LEN);
	memset(colorBody, 0x00, UDP_BODY_LEN);
	//head 1
	colorHead[0] = 0x03;
	//head 2~6
	unsigned long temp = udpCount++;
	for (int i = 2; i < UDP_HEAD_LEN; i++)
	{
		colorHead[i] = temp % 256;
		temp = temp / 256;
	}

	for (int udpPort = 0; udpPort < this->eachFrameUdpNum; udpPort++)
	{
		if (udpPort < 8)
		{
				//1,2-port1;3,4-port2  端口 0，1，2，3(主控的port)
			memset(colorBody, 0x00, UDP_BODY_LEN);
		}else
		{
			int dstLen = udpPort - 8;
			memcpy(colorBody, this->saveD[dstLen].getData(), UDP_BODY_LEN);
		}
		this->udp[udpPort].setHead(colorHead, UDP_HEAD_LEN);
		this->udp[udpPort].setBody(colorBody, UDP_BODY_LEN);
		if (udpPort%2)
			colorHead[1] += 0x01;
	}
	delete[] colorHead;
	delete[] colorBody;
}

/*************************
* 分Port
*    1.分解数组为int 1024*n(根据实际使用的情况，补0)
*    2.继续分解int 256*n
*    3.继续分解char 256*n
************************/
void SendData::branchPort()
{
	int type = BRANCH_CONSOLE_TYPE; //分控类型
	int udpInt = 256;               //一个udp包需要的int个数
	int len = type / udpInt;        //一个1024数组 = len * 256数组
	int ledNum = 0;                 //每一个port的LED实际使用个数
	int point = 0;                  //记录帧数据数组的指针
	int portNum = result.size();    //port口使用个数
	int* src = new int[type];       //int  1024
	int* src2 = new int[udpInt];    //int  256
	char* src3 = new char[udpInt * 3];//char 256
	int count = 0;
	for (int i = 1; i <= portNum; i++)
	{
		ledNum = result[i];
		memset(src, 0x00, type * sizeof(int));
		memcpy(src, data + point, ledNum * sizeof(int));
		for (int j = 0; j < len; j++)
		{
			memcpy(src2, src + (j * udpInt), udpInt * sizeof(int));
			IntToChars(src2, src3, udpInt);
			this->saveD[count++].setData(src3, udpInt * 3);
		}
		point += ledNum;
	}
	delete[] src;
	delete[] src2;
	delete[] src3;
}

//int 转 char
void SendData::IntToChars(int* src, char* dst, int srcLen)
{
	for (int i = 0; i < srcLen; i++)
	{
		int value = src[i];
		*(dst + 3 * i + 0) = (value >> 24) & 0x000000ff;//R
		*(dst + 3 * i + 1) = (value >> 16) & 0x000000ff;//G
		*(dst + 3 * i + 2) = (value >> 8) & 0x000000ff;//B
	}
}
