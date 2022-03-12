#pragma once
#include "JObject2D.h"
#include "JObjectMgr.h"
class JAttackObj2D : public JObject2D
{
public:
	JVector2 m_vStart;
	//방향받아올방법
public:
	bool Frame() override;
public:
	void SettingPosition(JVector2* pos, JVector2* dir);
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
	JAttackObj2D();
	virtual ~JAttackObj2D();
};