#include "cylinderconf.h"


CylinderConf::CylinderConf()
{
	turnNum = 0;
	rStep = 0;
	bConsloeType = 0;
	verNum = 0;
	horDistance = 0;
	verDistance = 0;
	/*����ʹ�õĲ���
	turnNum = 12;
	rStep = 200;
	bConsloeType = 1024;
	verNum = 133;
	horDistance = 200;
	verDistance = 60;
	*/
}

CylinderConf::CylinderConf(int m_turnNum, int m_rStep, int m_bConsloeType, int m_verNum, int m_horDistance, int m_verDistance)/* :
																															  turnNum(m_turnNum),
																															  rStep(m_rStep),
																															  bConsloeType(m_bConsloeType),
																															  verNum(m_verNum),
																															  horDistance(m_horDistance),
																															  verDistance(m_verDistance)*/
{
	turnNum = m_turnNum;
	rStep = m_rStep;
	bConsloeType = m_bConsloeType;
	verNum = m_verNum;
	horDistance = m_horDistance;
	verDistance = m_verDistance;
}

CylinderConf::~CylinderConf()
{

}

void CylinderConf::setTurnNum(int m_turnNum)
{
	turnNum = m_turnNum;
}

void CylinderConf::setRStep(int m_rStep)
{
	rStep = m_rStep;
}

void CylinderConf::setBConsloeType(int m_bConsloeType)
{
	bConsloeType = m_bConsloeType;
}

void CylinderConf::setVerNum(int m_verNum)
{
	verNum = m_verNum;
}

void CylinderConf::setHorDistance(int m_horDistance)
{
	horDistance = m_horDistance;
}

void CylinderConf::setVerDistance(int m_verDistance)
{
	verDistance = m_verDistance;
}

//�ܳ�
double CylinderConf::getPerimeter(int circleNum)
{
	if (circleNum < turnNum + 1 && circleNum >= 0)
		return 2 * PI * (rStep * circleNum);//2*PI*R
	else
		return -1;
}

//ˮƽȡ����ʵ�ʵ�������Բ���۵���*2��
int CylinderConf::getLightBarNum(int circleNum)
{
	if (1 == circleNum)
		return (int)floor((getPerimeter(circleNum) / 2) / horDistance) * 2;//��С����
	else
		return (int)ceil((getPerimeter(circleNum) / 2) / horDistance) * 2;//��һλ
}

//ʵ��ˮƽ���
int CylinderConf::getTHorDistance()
{
	return 0;
}

//��Ļÿ�����
int CylinderConf::getEachTurnLedNum(int circleNum)
{
	return verNum * getLightBarNum(circleNum);
}

//ÿ��port�ڿ��Ƶ�������
int CylinderConf::getEachPortLightBar()
{
	return (int)floor((double)bConsloeType / verNum);
}

//�ֿ�port�ڸ���
int CylinderConf::getEachTurnPortNum(int circleNum)
{
	return (int)ceil((double)getLightBarNum(circleNum) / getEachPortLightBar());
}

//���ÿһ��port����ʵ��ʹ�õĵ���
map<int, int> CylinderConf::getEachPortLEDNum()
{
	int n = 1;
	map<int, int> result;
	int ledNumByPort = verNum * getEachPortLightBar();//ÿ��port����Led����MAX
	for (int i = 1; i < turnNum + 1; i++)
	{
		int portNum = getEachTurnPortNum(i); //ÿһȦ�ֿ�port�ڸ���
		int ledNum = getEachTurnLedNum(i);   //ÿһȦ��Led����
		while (portNum > 0)
		{
			if (ledNum > ledNumByPort)       //�ж�ÿһȦ��Led���� �Ƿ���� ÿ��port����Led����MAX
			{
				result.insert(pair<int, int>(n++, ledNumByPort));
				ledNum -= ledNumByPort;
			}
			else
			{
				result.insert(pair<int, int>(n++, ledNum));
			}
			portNum--;
		}
	}
	return result;
}
