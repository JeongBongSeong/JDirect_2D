#include "JObjectNpc2D.h"
void JObjectNpc2D::HitOverlap(JBaseObject* pObj, DWORD dwState)
{
    if (dwState == JCollisionType::Overlap)
    {
        //pObj->m_bAlphaBlend = !pObj->m_bAlphaBlend;
    }
}

void JObjectNpc2D::HitSelect(JBaseObject* pObj, DWORD dwState)
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
        INT K = 0;
        //m_bSelect = true;
        //m_bDead = true;
    }
}

bool JObjectNpc2D::Frame()
{
    JVector2 p;
    if (m_vPos.x > m_rtIngame.right - 30.0f)
    {
        m_vDirection.x = m_vDirection.x * -1.0f;
        m_vPos.x = m_rtIngame.right - 30.0f;
    }
    if (m_vPos.x < m_rtIngame.left + 30.0f)
    {
        m_vDirection.x = m_vDirection.x * -1.0f;
        m_vPos.x = m_rtIngame.left + 30.0f;
    }
    if (m_vPos.y > m_rtIngame.bottom - 30.0f)
    {
        m_vDirection.y = m_vDirection.y * -1.0f;
        m_vPos.y = m_rtIngame.bottom - 30.0f;
    }
    if (m_vPos.y < m_rtIngame.top + 30.0f)
    {
        m_vDirection.y = m_vDirection.y * -1.0f;
        m_vPos.y = m_rtIngame.top + 30.0f;
    }

    p = m_vDirection * (m_fSpeed * g_fSecPerFrame);

    AddPosition(p);
    return false;
}

JObjectNpc2D::JObjectNpc2D()
{
    m_vDirection.x = (rand()%2 == 0) ? 1.0f : -1.0f;
    m_vDirection.y = (rand() % 2 == 0) ? 1.0f : -1.0f;
    m_fSpeed = 20.0f + (rand() % 300); //50.0f;
    m_dwCollisionType = JCollisionType::Overlap;
    m_dwSelectType = JSelectType::Select_Overlap;
}

JObjectNpc2D::~JObjectNpc2D()
{
}
