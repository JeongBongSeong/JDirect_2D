#pragma once
#include"JWorld.h"
#include "JPlayerObj2D.h"
#include "JObjectNpc2D.h"
#include "JSoundMgr.h"
#include "JInput.h"
#include "JEffectObj.h"
#include "JAttackObj2D.h"
class JZoneWorld : public JWorld
{
public:
	JSound* m_pBackGroundMusic;
public:
	JPlayerTank m_PlayerObj;
	JEffectObj m_AttackExplosionObj;
public:
	bool Load(std::wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

