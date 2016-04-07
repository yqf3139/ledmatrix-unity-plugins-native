/*************************************************
作者:李芃 陈纬
时间:2016-03-30
内容:实验室LED灯柱尺寸.xlsx报表的实现。
得到每一个port口上实际使用的灯数
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

	map<int, int> getEachPortLEDNum();      //获得每一个port口上实际使用的灯数
private:
	int turnNum;        //环幕数（圈数）
	int rStep;          //半径步长
	int bConsloeType;   //分控类型
	int verNum;         //垂直点数
	int horDistance;    //水平像素点理论间距
	int verDistance;    //垂直间距

	double getPerimeter(int circleNum);      //周长
	int getLightBarNum(int circleNum);       //水平取整后实际点数（半圆理论点数*2）
	int getTHorDistance();                   //实际水平间距(未实现)
	int getEachTurnLedNum(int circleNum);    //环幕每层点数
	int getEachPortLightBar();               //每个port口控制灯条个数
	int getEachTurnPortNum(int circleNum);   //分控port口个数
};
#endif // CYLINDERCONF_H
