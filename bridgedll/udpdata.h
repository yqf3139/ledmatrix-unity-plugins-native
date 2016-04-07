/*************************************************
����:��γ
ʱ��:2016-01-10
����:�洢UDP���ݰ�����
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

	int getHeadLength();                    //��ȡhead�ĳ���
	int getBodyLength();                    //��ȡbody�ĳ���
	int getLength();                        //��ȡUDPData�ܳ���
	bool setHead(char *head = NULL, int len = 0);  //����head�е�����
	bool setiHead(int i, char data);        //����head�е�iλ����
	bool setBody(char *body = NULL, int len = 0);  //����body�е�����
	bool setiBody(int i, char data);        //����body�е�iλ����
	bool getData(char * data);			//��ȡUDPData�е�����
private:
	char *head;                     //UDP�����е�ͷ
	char *body;                     //UDP�����еĸ���
	int headLength;                 //head����
	int bodyLength;                 //body����
};

#endif // UDPDATA_H
