#include "cylinderconf.h"


CylinderConf::CylinderConf()
{
	turnNum = 0;
	rStep = 0;
	bConsloeType = 0;
	verNum = 0;
	horDistance = 0;
	verDistance = 0;
	/*现在使用的参数
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

//周长
double CylinderConf::getPerimeter(int circleNum)
{
	if (circleNum < turnNum + 1 && circleNum >= 0)
		return 2 * PI * (rStep * circleNum);//2*PI*R
	else
		return -1;
}

//水平取整后实际点数（半圆理论点数*2）
int CylinderConf::getLightBarNum(int circleNum)
{
	if (1 == circleNum)
		return (int)floor((getPerimeter(circleNum) / 2) / horDistance) * 2;//舍小数点
	else
		return (int)ceil((getPerimeter(circleNum) / 2) / horDistance) * 2;//进一位
}

//实际水平间距
int CylinderConf::getTHorDistance()
{
	return 0;
}

//环幕每层点数
int CylinderConf::getEachTurnLedNum(int circleNum)
{
	return verNum * getLightBarNum(circleNum);
}

//每个port口控制灯条个数
int CylinderConf::getEachPortLightBar()
{
	return (int)floor((double)bConsloeType / verNum);
}

//分控port口个数
int CylinderConf::getEachTurnPortNum(int circleNum)
{
	return (int)ceil((double)getLightBarNum(circleNum) / getEachPortLightBar());
}

//获得每一个port口上实际使用的灯数
map<int, int> CylinderConf::getEachPortLEDNum()
{
	int n = 1;
	map<int, int> result;
	int ledNumByPort = verNum * getEachPortLightBar();//每个port口上Led个数MAX
	for (int i = 1; i < turnNum + 1; i++)
	{
		int portNum = getEachTurnPortNum(i); //每一圈分控port口个数
		int ledNum = getEachTurnLedNum(i);   //每一圈的Led个数
		while (portNum > 0)
		{
			if (ledNum > ledNumByPort)       //判断每一圈的Led个数 是否大于 每个port口上Led个数MAX
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
