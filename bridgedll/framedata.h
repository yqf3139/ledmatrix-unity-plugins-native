/*************************************************
����:��γ
ʱ��:2016-01-10
����:�洢֡����
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

	void setWidth(int width);                     //��ȡ֡�Ŀ��
	void setHeight(int height);                    //��ȡ֡�ĸ߶�
	void setFrameID(int frameID);
	bool setData(int *data, int len = 0);//����֡�е�����

	int getWidth();                     //��ȡ֡�Ŀ��
	int getHeight();                    //��ȡ֡�ĸ߶�
	int getLen();
	int getFrameID();                   //��ȡ֡��
	int *getData();                     //��ȡ֡�е�int��������

	void changeType();  //�۷�
	void changeType2(); //���������
private:
	int width;                 //֡�Ŀ�ȣ���LED����Ŀ�ȶ�Ӧ
	int height;                //֡�ĸ߶ȣ���LED����ĸ߶ȶ�Ӧ
	int lenth;                 //֡�ĳ��ȣ���LED����ĸ߶ȶ�Ӧ

	int dataLen;               //���ݳ���
	int frameID;               //֡��
	int *data;                 //֡�е�����
};

#endif // FRAMEDATA_H
