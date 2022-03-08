#pragma once
#include"JTextureMgr.h"
#include"JShaderMgr.h"

struct SimpleVertex
{
	JVector2 v;
	JVector2 t;
};
enum JCollisionType
{
	Block = 0,
	Overlap,
	Ignore,
}; 

enum JSelectType
{
	Select_Block = 0,
	Select_Overlap,
	Select_Ignore,
};
// 0001  - �⺻
// 0010  - ����
// 0100  - ����
// 1000  - ����ź
// 0111 = 7(�Ӽ�)
// 1111 = 15
enum TSelectState
{
	T_DEFAULT = 0,  // Ŀ���� ���� ���� ��(T_FOCUS���¿��� �ٸ� ���� T_ACTIVE�ϸ� ��ȯ�ȴ�.)
	T_HOVER = 1,	// Ŀ���� ���� ���� ��
	T_FOCUS = 2,	// T_ACTIVE���¿��� ���� ��ư�� �ٸ� ������ ������ ��(���)
	T_ACTIVE = 4,	// ���콺 ���� ��ư ������ ���� ��
	T_SELECTED = 8, // T_ACTIVE ���¿��� ���ɹ�ư ������ ��
};

class JBaseObject
{
public:
	bool m_bDead;
	int m_iCollisionID;
	int m_iSelectID;
	float   m_fSpeed;
	JVector2 m_vPos;
	JVector2 m_vDirection;
	float		m_fWidth;
	float		m_fHeight;
	JRect		m_rtCollision;
	DWORD m_dwCollisionType;
	DWORD m_dwSelectType;
	DWORD		m_dwSelectState;
	bool		m_bSelect;
	bool m_bAlphaBlend = TRUE;

public:
	virtual void HitOverlap(JBaseObject* pObj, DWORD dwState);
	virtual void HitSelect(JBaseObject* pObj, DWORD dwState);

public:
	JBaseObject()
	{
		m_bDead = false;
		m_bSelect = false;
		m_dwSelectState = T_DEFAULT;
		m_iCollisionID = -1;
		m_iSelectID = -1;
		m_vDirection.x = 0.0f;
		m_vDirection.y = 0.0f;
		m_dwCollisionType = JCollisionType::Overlap;
		m_dwSelectType = JCollisionType::Overlap;
	}

};

struct JIndex
{
	DWORD _0;
	DWORD _1;
	DWORD _2;
};

struct JConstantData
{
	JVector4 Color;
	JVector4 Timer;
};

class JDxObject : public JBaseObject
{
public:
	JTexture* m_pColorTex = nullptr;
	JTexture* m_pMaskTex = nullptr;
	JShader* m_pVShader = nullptr;
	JShader* m_pPShader = nullptr;
public:
	ID3D11BlendState* m_pAlphaBlend;
	ID3D11BlendState* m_pAlphaBlendDisable;
	D3D11_TEXTURE2D_DESC m_TextureDesc;
	

public:
	std::vector<SimpleVertex> m_InitScreenList;
	std::vector<SimpleVertex> m_VertexList;
	ID3D11Buffer* m_pVertexBuffer;

	std::vector<DWORD> m_IndexList;
	ID3D11Buffer* m_pIndexBuffer;

	JConstantData    m_ConstantList;
	ID3D11Buffer* m_pConstantBuffer;

	ID3D11InputLayout* m_pVertexLayout;

	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pContext;

public:
	void    SetDevice(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext);
	virtual bool LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName);
	virtual bool    SetVertexData();
	virtual bool	SetIndexData();
	virtual bool	SetConstantData();
	virtual bool	Create(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext, const TCHAR* szShaderFileName = nullptr, const TCHAR* szColorFileName = nullptr, const TCHAR* szMaskFileName = nullptr);
public:
	virtual bool	CreateVertexBuffer();
	virtual bool    CreateIndexBuffer();
	virtual bool	CreateConstantBuffer();
	virtual bool    CreateVertexShader(const TCHAR* szFile);
	virtual bool    CreatePixelShader(const TCHAR* szFile);
	virtual bool    CreateInputLayout();
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	JDxObject();
	~JDxObject();
};