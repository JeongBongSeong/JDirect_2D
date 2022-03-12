#include "JAttackObj2D.h"



void JAttackObj2D::HitOverlap(JBaseObject* pObj, DWORD dwState)
{
    if (dwState == JCollisionType::Overlap)
    {
        pObj->m_bDead = true;
    }
}

void JAttackObj2D::HitSelect(JBaseObject* pObj, DWORD dwState)
{
    if (m_dwSelectState & J_HOVER)
    {
        INT K = 0;
    }
    if (m_dwSelectState & J_FOCUS)
    {
        INT K = 0;
    }
    if (m_dwSelectState & J_ACTIVE)
    {
        INT K = 0;
    }
    if (m_dwSelectState & J_SELECTED)
    {
        m_bSelect = true;
        m_bDead = true;
    }
}
void JAttackObj2D::SettingPosition(JVector2* pos,JVector2 *dir)
{
    m_vPos = *pos;
    m_vDirection = *dir;

}
bool JAttackObj2D::Frame()
{
    JVector2 p;
    //if (m_vPos.y < g_rtClient.top)      //위로
    //{
    //    m_vDirection.y = m_vDirection.y * -1.0f;
    //    m_vPos.y = g_rtClient.top + 40.0f;
    //}
    //if (m_vPos.x > g_rtClient.right)    //오른쪽
    //{
    //    m_vDirection.x = m_vDirection.x * -1.0f;
    //    m_vPos.x = g_rtClient.right - 40.0f;
    //}
    //if (m_vPos.x < g_rtClient.left)     //왼쪽
    //{
    //    m_vDirection.x = m_vDirection.x * -1.0f;
    //    m_vPos.x = g_rtClient.left + 40.0f;
    //}
    //
  
    //if (m_vPos.y > g_rtClient.bottom)   //아래로
    //{
    //    m_vDirection.y = m_vDirection.y * -1.0f;
    //    m_vPos.y = g_rtClient.bottom - 40.0f;
    //}
    p = m_vDirection * (m_fSpeed * g_fSecPerFrame);

    AddPosition(p);
    return false;
}

JAttackObj2D::JAttackObj2D()
{
    m_vDirection = JVector2(0, -1);
    m_fSpeed = 300.0f; //50.0f;
    m_dwCollisionType = JCollisionType::Overlap;
    m_dwSelectType = JSelectType::Select_Overlap;
}

JAttackObj2D::~JAttackObj2D()
{
}