#include "JZoneWorld.h"

bool JZoneWorld::Init()
{
	return true;
}
bool JZoneWorld::Load(std::wstring filename)
{
	Sleep(1000);
	//사운드
	//m_testSound.Load("..\\..\\data\\Sound\\BattleCity\\BattleCityBGM.mp3");
	JSound* pSound = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\Attack.wav");
	m_pBackGroundMusic = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\StageGameBGM.wav");
	m_pBackGroundMusic = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\BattleCityBGM.mp3");
	//I_Sound.GetPtr(pSound->m_csName)->Play();
	m_pBackGroundMusic->Play(false);

	I_Sprite.Load(L"PlayerData.txt");
	m_PlayerObj.m_pSprite = I_Sprite.GetPtr(L"level1_top");

	m_PlayerObj.Init();
	m_PlayerObj.SetPosition(JVector2(m_PlayerObj.m_pSprite->m_vPos.x, m_PlayerObj.m_pSprite->m_vPos.y));

	m_PlayerObj.SetRectSource({ 1,33,15,14 });
	m_PlayerObj.SetRectDraw({ 0,g_rtClient.bottom-45, 45, 45 });
	m_PlayerObj.m_vMuzzlePosition = JVector2(22.5, g_rtClient.bottom - 45);
	m_PlayerObj.m_vDirection = JVector2(0, -1);
	m_PlayerObj.UpdateData();
	m_PlayerObj.m_csName = L"PlayerUser";
	if (!m_PlayerObj.Create(m_pd3dDevice, m_pContext,
		L"../../data/shader/DefaultUI.txt",//L"Shader.txt",
		//L"../../data/bitmap1.bmp"
		L"../../data/BattleCity/ObjectList_White.png"
		//	L"../../data/bitmap2.bmp"
	))
	{
		return false;
	}

	for (int iNpc = 0; iNpc < 10; iNpc++)
	{
		std::shared_ptr<JObjectNpc2D> npc = 
			std::make_shared<JObjectNpc2D>();
		npc->m_csName = L"NPC_";
		npc->m_csName += std::to_wstring(iNpc);
		npc->Init();
		npc->SetPosition(JVector2(50 + iNpc * 150, 50));
		if (iNpc % 2 == 0)
		{
			npc->SetRectSource({ 129,144,13,16 });
			npc->SetRectDraw({ 0,0, 45,45 });
		}
		else
		{
			npc->SetRectSource({ 129,130,13,13 });
			npc->SetRectDraw({ 0,0, 45,45 });
		}

		npc.get()->UpdateData();
		if (!npc->Create(m_pd3dDevice, m_pContext,
			L"../../data/shader/DefaultUI.txt",
			L"../../data/BattleCity/ObjectList_White.png"//,
			//L"../../data/bitmap2.bmp"
		))
		{
			return false;
		}
		m_NpcObj.push_back(npc);
	}
	// 포탄 이펙트
	I_Sprite.Load(L"AtackEffectData.txt");
	m_AttackExplosionObj.m_bDead = true;
	m_AttackExplosionObj.m_pSprite = I_Sprite.GetPtr(L"AttackEffect");

	m_AttackExplosionObj.Init();
	//m_AttackExplosionObj.SetPosition(JVector2(400, 500));
	//JSprite* pSprite = I_Sprite.GetPtr(L"rtExplosion");

	m_AttackExplosionObj.SetRectSource(m_AttackExplosionObj.m_pSprite->m_rtArray[0]);
	m_AttackExplosionObj.SetRectDraw({ 0,0, 34, 46 });

	if (!m_AttackExplosionObj.Create(m_pd3dDevice, m_pContext,
		L"../../data/shader/DefaultUI.txt",
		L"../../data/BattleCity/ObjectList_White.png"//,
		//L"../../data/bitmap2.bmp"
	))
	{
		return false;
	}
	for (int iCannonBall = 0; iCannonBall < 50; iCannonBall++)
	{
		std::shared_ptr<JAttackObj2D> CannonBall =
			std::make_shared<JAttackObj2D>();
		CannonBall->m_bDead = true;
		CannonBall->m_csName = L"CannonBall_";
		CannonBall->m_csName += std::to_wstring(iCannonBall);
		CannonBall->Init();
		CannonBall->SetPosition(m_PlayerObj.m_vMuzzlePosition);
		
		CannonBall->SetRectSource({ 323, 102, 3, 4 });
		CannonBall->SetRectDraw({ 0, 0, 3, 4 });
		
		CannonBall.get()->UpdateData();
		if (!CannonBall->Create(m_pd3dDevice, m_pContext,
			L"../../data/shader/DefaultUI.txt",
			L"../../data/BattleCity/ObjectList_White.png"//,
			//L"../../data/bitmap2.bmp"
		))
		{
			return false;
		}
		m_PlayerObj.m_CannonBallObj.push_back(CannonBall);
	}
	return true;
}


bool JZoneWorld::Frame()
{
	
	//m_SoundMgr.GetPtr(L"OnlyLove.MP3")->Play();
	//JSound* pSound = I_Sound.GetPtr(L"BattleCityBGM.mp3");
	//pSound->Frame();
	if (!m_pBackGroundMusic->isPlaying() && (m_pBackGroundMusic->m_csName != L"StageGameBGM.wav"))
	{
		m_pBackGroundMusic = I_Sound.Get().GetPtr(L"StageGameBGM.wav");
		m_pBackGroundMusic->Play(true);
	}

	m_pBackGroundMusic->Frame();
	
	if (JInput::Get().GetKey(VK_ADD) == KEY_HOLD)
	{
		m_pBackGroundMusic->VolumeUp(g_fSecPerFrame);
	}
	if (JInput::Get().GetKey(VK_SUBTRACT) == KEY_HOLD)
	{
		m_pBackGroundMusic->VolumeDown(g_fSecPerFrame);
	}
	
	if (JInput::Get().GetKey(VK_UP) == KEY_PUSH)// && (m_iCheck == 0 || m_iCheck == 1))
	{
		m_PlayerObj.m_pSprite = I_Sprite.GetPtr(L"level1_top");
		m_PlayerObj.SetRectSource(m_PlayerObj.m_pSprite->m_rtArray[0]);		
	}
	else if (JInput::Get().GetKey(VK_DOWN) == KEY_PUSH)// && (m_iCheck == 0 || m_iCheck == 2))
	{
		m_PlayerObj.m_pSprite = I_Sprite.GetPtr(L"level1_bottom");
		m_PlayerObj.SetRectSource(m_PlayerObj.m_pSprite->m_rtArray[0]);
		
	}
	else if (JInput::Get().GetKey(VK_LEFT) == KEY_PUSH)// && (m_iCheck == 0 || m_iCheck == 3))
	{
		m_PlayerObj.m_pSprite = I_Sprite.GetPtr(L"level1_left");
		m_PlayerObj.SetRectSource(m_PlayerObj.m_pSprite->m_rtArray[0]);
	
	}
	else if (JInput::Get().GetKey(VK_RIGHT) == KEY_PUSH)// && (m_iCheck == 0 || m_iCheck == 4))
	{
		m_PlayerObj.m_pSprite = I_Sprite.Get().GetPtr(L"level1_right");
		m_PlayerObj.SetRectSource(m_PlayerObj.m_pSprite->m_rtArray[0]);
	
	}
	m_AttackExplosionObj.SetTargetPosition(&m_PlayerObj.m_vMuzzlePosition);

	if (JInput::Get().GetKey('Z') == KEY_PUSH)
	{
		//pSound->Stop();
		//총알이 살아있으면 호출하지 않는다. 총알이 하나라도 죽어있으면 true반환
		if (m_PlayerObj.isCannonBall())
		{
			for (int i = 0; i<m_PlayerObj.m_CannonBallObj.size(); i++)
			{
				if (m_PlayerObj.m_CannonBallObj[i]->m_bDead == true)
				{
					m_PlayerObj.m_CannonBallObj[i]->m_bDead = false;
					break;
				}
			}
			JSound* pSound1 = I_Sound.GetPtr(L"Attack.wav");
			if (pSound1 != nullptr)
			{
				pSound1->PlayEffect();
			}
			m_AttackExplosionObj.m_bDead = false;
		}
	}
	m_AttackExplosionObj.Frame();
	m_PlayerObj.Frame();
	
	JWorld::Frame();
	//for (int iObj = 0; iObj < m_NpcLlist.size(); iObj++)
	//{
	//	//RECT rt = m_NpcLlist[iObj]->m_rtDraw;
	//	///rt.right = rt.right + (cos(g_fGameTimer) * 0.5f + 0.5f) * 50.0f;
	//	//rt.bottom = rt.bottom + (cos(g_fGameTimer) * 0.5f + 0.5f) * 50.0f;
	//	//m_NpcLlist[iObj]->UpdateRectDraw(rt);
	//	m_NpcLlist[iObj]->Frame();
	//	//충돌체크
	///*	if (JCollision::ToRect(m_PlayerObj.m_rtCollision, m_NpcLlist[iObj]->m_rtCollision))
	//	{
	//		m_NpcLlist[iObj]->m_bAlphaBlend = FALSE;
	//	}
	//	else
	//	{
	//		m_NpcLlist[iObj]->m_bAlphaBlend = TRUE;
	//	}*/
	//}
	return true;
}

bool JZoneWorld::Render()
{
	JWorld::Render();
	m_PlayerObj.Render();
	m_AttackExplosionObj.Render();
	return true;
}

bool JZoneWorld::Release()
{
	m_PlayerObj.Release();
	m_AttackExplosionObj.Release();
	return true;
}
