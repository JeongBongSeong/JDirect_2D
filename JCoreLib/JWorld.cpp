#include "JWorld.h"
JWorld* JWorld::m_pWorld = nullptr;

bool JWorld::Load(std::wstring saveFile)
{
	return true;
}
bool JWorld::Init()
{
	return true;
}
bool JWorld::Frame()
{
	for (auto obj : m_UIObj)
	{
		JObject2D* pObj = obj.second;
		if (pObj != nullptr)
		{
			pObj->Frame();
		}
	}
	return true;
}
bool JWorld::Render()
{
	for (auto obj : m_UIObj)
	{
		JObject2D* pObj = obj.second;
		if (pObj != nullptr)
		{
			pObj->Render();
		}
	}
	return true;
}
bool JWorld::Release()
{
	for (auto obj : m_UIObj)
	{
		obj.second->Release();
		delete obj.second;
	}
	for (auto obj : m_ItemObj)
	{
		obj.second->Release();
		delete obj.second;
	}
	for (auto obj : m_NpcObj)
	{
		obj.second->Release();
		delete obj.second;
	}
	for (auto obj : m_MapObj)
	{
		obj.second->Release();
		delete obj.second;
	}
	m_ItemObj.clear();
	m_UIObj.clear();
	m_NpcObj.clear();
	m_MapObj.clear();
	return true;
}

JWorld::JWorld()
{
}

JWorld::~JWorld()
{
}


