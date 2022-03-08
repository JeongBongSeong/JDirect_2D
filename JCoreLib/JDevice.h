#pragma once
#include "JWindow.h"
class JDevice : public JWindow
{
public:
	ID3D11Device* m_pd3dDevice;// ����̽� ��ü
	IDXGISwapChain* m_pSwapChain;// ����ü�� ��ü
	ID3D11RenderTargetView* m_pRenderTargetView;// ���� ����Ÿ�� �� //�������� ����۰� ���� �� ��� ���۸� �Ѹ� ���� �����ϴ� ��
	IDXGIFactory* m_pGIFactory;
	ID3D11DeviceContext* m_pImmediateContext;// �ٺ��̽� ���ؽ�Ʈ ��ü

	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;	// ����ü�� �Ӽ���
	D3D11_VIEWPORT m_ViewPort;// �� ��Ʈ �Ӽ���
	D3D_DRIVER_TYPE m_driverType;
	D3D_DRIVER_TYPE m_DriverType;
	D3D_FEATURE_LEVEL m_FeatureLevel;	// Direct3D Ư������ �Ӽ���	
	// ����ü�� �Ӽ���
public:
	virtual HRESULT InitDeivice();
	virtual bool	CreateDevice();
	virtual bool	CreateRenderTargetView();
	virtual bool	SetViewport();
	virtual bool	CleapupDevice();
public:
	void			ResizeDevice(UINT iWidth, UINT iHeight);
public:
	JDevice();
	virtual ~JDevice();
};