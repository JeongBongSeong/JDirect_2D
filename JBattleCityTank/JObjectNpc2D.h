#pragma once
#include "JObject2D.h"
#include "JObjectMgr.h"
class JObjectNpc2D : public JObject2D
{
public:
	RECT m_rtIngame = {0,0,0,0};
public:
	bool Frame() override;
public:
	void HitOverlap(JBaseObject* pObj, DWORD dwState);
	void HitSelect(JBaseObject* pObj, DWORD dwState);
	void  UpdateData() override
	{
		m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);
		I_ObjectMgr.AddCollisionExecute(this,
			std::bind(&JBaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this,
			std::bind(&JBaseObject::HitSelect, this,
				std::placeholders::_1,
				std::placeholders::_2));
	}
public:
	JObjectNpc2D();
	virtual ~JObjectNpc2D();
};