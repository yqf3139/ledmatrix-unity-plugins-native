/*************************************************
����:���M ��γ
ʱ��:2016-03-30
����:ʵ����LED�����ߴ�.xlsx�����ʵ�֡�
�õ�ÿһ��port����ʵ��ʹ�õĵ���
**************************************************/
#ifndef CYLINDERCONF_H
#define CYLINDERCONF_H


#include <cmath>
#include <map>
using std::map;
using std::pair;

const double PI = 3.14159;

class CylinderConf
{
public:
	CylinderConf();
	CylinderConf(int m_turnNum, int m_rStep, int m_bConsloeType,
		int m_verNum, int m_horDistance, int m_verDistance);
	~CylinderConf();
	void setTurnNum(int m_turnNum);
	void setRStep(int m_rStep);
	void setBConsloeType(int m_bConsloeType);
	void setVerNum(int m_verNum);
	void setHorDistance(int m_horDistance);
	void setVerDistance(int m_verDistance);

	map<int, int> getEachPortLEDNum();      //���ÿһ��port����ʵ��ʹ�õĵ���
private:
	int turnNum;        //��Ļ����Ȧ����
	int rStep;          //�뾶����
	int bConsloeType;   //�ֿ�����
	int verNum;         //��ֱ����
	int horDistance;    //ˮƽ���ص����ۼ��
	int verDistance;    //��ֱ���

	double getPerimeter(int circleNum);      //�ܳ�
	int getLightBarNum(int circleNum);       //ˮƽȡ����ʵ�ʵ�������Բ���۵���*2��
	int getTHorDistance();                   //ʵ��ˮƽ���(δʵ��)
	int getEachTurnLedNum(int circleNum);    //��Ļÿ�����
	int getEachPortLightBar();               //ÿ��port�ڿ��Ƶ�������
	int getEachTurnPortNum(int circleNum);   //�ֿ�port�ڸ���
};
#endif // CYLINDERCONF_H
