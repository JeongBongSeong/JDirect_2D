#include "JPacket.h"
void JPacket::PutData(const char* pData, int iSize)
{
	m_uPacket.ph.len += iSize;
	memcpy(m_pOffset, pData, iSize);
	m_pOffset += iSize;
};
void JPacket::GetData(const char* pData, int iSize)
{
	memcpy(const_cast<char*>(pData), m_pOffset, iSize);
	m_pOffset += iSize;
};
JPacket& JPacket::operator << (int data)
{
	PutData((char*)&data, sizeof(int));
	return *this;
}
JPacket& JPacket::operator << (long data)
{
	PutData((char*)&data, sizeof(long));
	return *this;
}
JPacket& JPacket::operator << (short data)
{
	PutData((char*)&data, sizeof(short));
	return *this;
}
JPacket& JPacket::operator << (float data)
{
	PutData((char*)&data, sizeof(float));
	return *this;
}
JPacket& JPacket::operator << (char* data)
{
	PutData(data, strlen(data) + 1);
	return *this;
}
JPacket& JPacket::operator << (std::string data)
{
	PutData(data.c_str(), data.size() + 1);
	return *this;
}



JPacket& JPacket::operator >> (int& data)
{
	GetData((char*)&data, sizeof(int));
	return *this;
}
JPacket& JPacket::operator >> (long& data)
{
	GetData((char*)&data, sizeof(long));
	return *this;
}
JPacket& JPacket::operator >> (short& data)
{
	GetData((char*)&data, sizeof(short));
	return *this;
}
JPacket& JPacket::operator >> (float& data)
{
	GetData((char*)&data, sizeof(float));
	return *this;
}
JPacket& JPacket::operator >> (char* data)
{
	int iSize = strlen(m_pOffset) + 1;
	GetData(data, iSize);
	return *this;
}
JPacket& JPacket::operator >> (std::string& data)
{
	int iSize = strlen(m_pOffset + 1);
	GetData(data.c_str(), iSize);
	return *this;
}
JPacket::JPacket()
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_uPacket.ph.len = PACKET_HEADER_SIZE;
	m_pOffset = m_uPacket.msg;
}
JPacket::JPacket(WORD iType)
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_uPacket.ph.len = PACKET_HEADER_SIZE;
	m_uPacket.ph.type = iType;
	m_pOffset = m_uPacket.msg;
}
JPacket::JPacket(const JPacket& packet)
{
	m_uPacket.ph = packet.m_uPacket.ph;
	memcpy(m_uPacket.msg, packet.m_uPacket.msg, sizeof(char) * 4096);
	m_pOffset = m_uPacket.msg;
}
JPacket::~JPacket()
{

}