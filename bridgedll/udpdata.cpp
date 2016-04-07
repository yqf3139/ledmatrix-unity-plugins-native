#include "udpdata.h"

UDPData::UDPData(int headLen, int bodyLen)
{
	this->headLength = headLen;
	this->bodyLength = bodyLen;
	this->head = NULL;
	this->body = NULL;
}

UDPData::UDPData(const UDPData& other)
{
	headLength = other.headLength;
	bodyLength = other.bodyLength;
	head = new char[headLength];
	memcpy(head, other.head, headLength);
	body = new char[bodyLength];
	memcpy(body, other.body, bodyLength);
}

UDPData::~UDPData()
{
	if (NULL != this->head)
	{
		delete[] this->head;
		this->head = NULL;
	}
	if (NULL != this->body)
	{
		delete[] this->body;
		this->body = NULL;
	}
}

int UDPData::getHeadLength()
{
	return this->headLength;
}

int UDPData::getBodyLength()
{
	return this->bodyLength;
}

int UDPData::getLength()
{
	return this->headLength + this->bodyLength;
}

bool UDPData::setHead(char *head, int len)
{
	if (head == NULL)
	{
		printf("ERROR [UDPData:setHead] Parameter \"head\" is null.");
		return false;
	}
	if (0 != len)
		this->headLength = len;
	if (NULL == this->head)
		this->head = new char[this->headLength];
	memcpy(this->head, head, this->headLength);

	return true;
}

bool UDPData::setiHead(int i, char data)
{
	if (this->head == NULL)
	{
		printf("ERROR [UDPData:setiHead] \"head\" is null.");
		return false;
	}
	if (i >= getHeadLength())
	{
		printf("ERROR [UDPData:setiHead] Parameter \"i\" %d is bigger than head length.", i);
		return false;
	}
	head[i] = data;
	return true;
}

bool UDPData::setBody(char *body, int len)
{
	if (body == NULL)
	{
		printf("ERROR [UDPData:setBody] Parameter \"body\" is null.");
		return false;
	}
	if (0 != len)
		this->bodyLength = len;
	if(NULL == this->body)
		this->body = new char[this->bodyLength];
	memcpy(this->body, body, this->bodyLength);
	return true;
}

bool UDPData::setiBody(int i, char data)
{
	if (this->body == NULL)
	{
		printf("ERROR [UDPData:setiBody] \"body\" is null.");
		return false;
	}
	if (i >= getBodyLength())
	{
		printf("ERROR [UDPData:setiBody] Parameter \"i\" %d is bigger than body length.", i);
		return false;
	}
	body[i] = data;
	return true;
}

bool UDPData::getData(char *data)
{
	if (NULL == data || NULL == this->head || NULL == this->body)
		return false;
	char *src = data;
	memset(src, 0x00, getLength());
	memcpy(src, this->head, getHeadLength());
	memcpy(src + getHeadLength(), this->body, getBodyLength());
	return true;
}
