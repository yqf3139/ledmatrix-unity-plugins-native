
/*
*   ����:��γ
*   ����:2016-3-31
*   ����:�洢���飨�����ǳ�������⣩
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
	bool setData(type* data, int len);  //�洢����
	type* getData();                    //�������
	int getLen();                       //������ݳ���
private:
	type* m_data;   //����
	int m_len;      //ָ�볤��
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

//�洢����
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

//�������
template<class type> type* SaveData<type>::getData()
{
	return m_data;
}

//������ݳ���
template<class type> int SaveData<type>::getLen()
{
	return m_len;
}
#endif // SAVEDATE

