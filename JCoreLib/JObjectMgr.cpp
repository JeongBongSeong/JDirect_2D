#include "JObjectMgr.h"
#include "JInput.h"

void JObjectMgr::AddCollisionExecute(JBaseObject* owner, CollisionFunction func)
{
	owner->m_iCollisionID = m_iExecuteCollisionID++;
	//1번부터 들어간다.
	m_ObjectList.insert(std::make_pair(owner->m_iCollisionID, owner));
	m_fnCollisionExecute.insert(std::make_pair(owner->m_iCollisionID, func));
}
void JObjectMgr::AddSelectExecute(JBaseObject* owner, CollisionFunction func)
{
	owner->m_iSelectID = m_iExecuteSelectID++;
	//1번부터 들어간다.
	m_SelectList.insert(std::make_pair(owner->m_iSelectID, owner));
	m_fnSelectExecute.insert(std::make_pair(owner->m_iSelectID, func));
}

void JObjectMgr::DeleteCollisionExecute(JBaseObject* owner)
{
	std::map<int, JBaseObject*>::iterator objiter;
	objiter = m_ObjectList.find(owner->m_iCollisionID);
	if (objiter != m_ObjectList.end())
	{
		m_ObjectList.erase(objiter);
	}

	FunctionIterator colliter = m_fnCollisionExecute.find(owner->m_iCollisionID);
	if (colliter != m_fnCollisionExecute.end())
	{
		m_fnCollisionExecute.erase(colliter);
	}
}
void JObjectMgr::DeleteSelectExecute(JBaseObject* owner)
{
	std::map<int, JBaseObject*>::iterator objiter;
	objiter = m_SelectList.find(owner->m_iCollisionID);
	if (objiter != m_SelectList.end())
	{
		m_SelectList.erase(objiter);
	}

	FunctionIterator colliter = m_fnSelectExecute.find(owner->m_iCollisionID);
	if (colliter != m_fnSelectExecute.end())
	{
		m_fnSelectExecute.erase(colliter);
	}
}
bool JObjectMgr::Init()
{
	return true;
}
void JObjectMgr::CallRecursive(JBaseObject* pSrcObj, DWORD dwState)
{
	if (pSrcObj->m_pParent == nullptr)
	{
		return;
	}
	CallRecursive(pSrcObj->m_pParent, dwState);
	pSrcObj->HitSelect(pSrcObj, dwState);
}
bool JObjectMgr::Frame()
{
	// collision check
	for (auto src : m_ObjectList)
	{
		JBaseObject* pObjSrc = (JBaseObject*)src.second;
		if (pObjSrc->m_dwCollisionType == JSelectType::Select_Ignore) continue;
		DWORD dwState = JSelectState::J_DEFAULT;



		for (auto dest : m_ObjectList)
		{
			JBaseObject* pObjDest = (JBaseObject*)dest.second;
			if (pObjSrc == pObjDest) continue;
			if (JCollision::ToRect(pObjSrc->m_rtCollision, pObjDest->m_rtCollision))
			{
				FunctionIterator colliter = m_fnCollisionExecute.find(pObjSrc->m_iCollisionID);
				if (colliter != m_fnCollisionExecute.end())
				{
					CollisionFunction call = colliter->second;
					call(pObjDest, dwState);
				}
			}
		}
	}

	//Mouse Select
	for (auto src : m_SelectList)
	{
		JBaseObject* pObjSrc = (JBaseObject*)src.second;
		//if (pObjSrc->m_dwSelectType == JSelectType::Select_Ignore) continue;
		DWORD dwState = JSelectState::J_DEFAULT;

		if (pObjSrc->m_dwSelectType != JSelectType::Select_Ignore && JCollision::RectToPoint(pObjSrc->m_rtCollision, (float)g_ptMouse.x, (float)g_ptMouse.y))
		{
			DWORD dwKeyState = JInput::Get().m_dwMouseState[0];
				pObjSrc->m_dwSelectState = JSelectState::J_HOVER;
			if (dwKeyState == KEY_PUSH)
			{
				pObjSrc->m_dwSelectState = JSelectState::J_ACTIVE;
			}
			if (dwKeyState == KEY_HOLD)
			{
				pObjSrc->m_dwSelectState = JSelectState::J_FOCUS;
			}
			if (dwKeyState == KEY_UP)
			{
				pObjSrc->m_dwSelectState = JSelectState::J_SELECTED;
			}

			CallRecursive(pObjSrc, dwState);
			FunctionIterator colliter = m_fnSelectExecute.find(pObjSrc->m_iSelectID);
			if (colliter != m_fnSelectExecute.end())
			{
				CollisionFunction call = colliter->second;
				call(pObjSrc, dwState);
			}
		}
		else
		{
			if (pObjSrc->m_dwSelectState != JSelectState::J_DEFAULT)
			{
				pObjSrc->m_dwSelectState = JSelectState::J_DEFAULT;
				FunctionIterator colliter = m_fnSelectExecute.find(pObjSrc->m_iSelectID);
				if (colliter != m_fnSelectExecute.end())
				{
					CollisionFunction call = colliter->second;
					call(pObjSrc, dwState);
				}
			}
		}
	}
	return true;
}

bool JObjectMgr::Release()
{
	m_ObjectList.clear();
	m_SelectList.clear();
	return true;
}
JObjectMgr::JObjectMgr()
{
	m_iExecuteCollisionID = 0;
	m_iExecuteSelectID = 0;
};
JObjectMgr::~JObjectMgr()
{
	Release();
};