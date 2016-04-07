
/*
*   作者:陈纬
*   日期:2016-3-31
*   内容:存储数组（解决了浅拷贝问题）
*/

#ifndef SAVEDATE
#define SAVEDATE

#include <cstring>
#include <WS2tcpip.h>
template<class type> class SaveData
{
public:
	SaveData();
	SaveData(const SaveData& other);
	~SaveData();
	bool setData(type* data, int len);  //存储数据
	type* getData();                    //获得数据
	int getLen();                       //获得数据长度
private:
	type* m_data;   //数组
	int m_len;      //指针长度
};

template<class type> SaveData<type>::SaveData()
{
	m_data = NULL;
	m_len = 0;
}

template<class type> SaveData<type>::SaveData(const SaveData& other)
{
	m_len = other.m_len;
	m_data = new type[m_len];
	memcpy(m_data, other.m_data, m_len * sizeof(type));

}

template<class type> SaveData<type>::~SaveData()
{
	if (NULL != m_data)
	{
		delete[] m_data;
		this->m_data = NULL;
	}

}

//存储数据
template<class type> bool SaveData<type>::setData(type* data, int len)
{
	if (len > 0)
	{
		this->m_len = len;
		if (NULL == this->m_data)
			this->m_data = new type[len];
		memcpy(this->m_data, data, len * sizeof(type));
		return true;
	}
	return false;
}

//获得数据
template<class type> type* SaveData<type>::getData()
{
	return m_data;
}

//获得数据长度
template<class type> int SaveData<type>::getLen()
{
	return m_len;
}
#endif // SAVEDATE

