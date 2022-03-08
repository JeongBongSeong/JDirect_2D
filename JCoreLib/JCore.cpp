#include "JCore.h"
#include "JObjectMgr.h"
bool JCore::CoreInit()
{
    m_GameTimer.Init();
    JInput::Get().Init();
    if (SUCCEEDED(InitDeivice()))
    {
        I_Shader.Set(m_pd3dDevice);
        I_Texture.Set(m_pd3dDevice);

        if (m_dxWrite.Init())
        {
            IDXGISurface1* pSurface = nullptr;
            HRESULT hr = m_pSwapChain->GetBuffer(0,
                __uuidof(IDXGISurface1),
                (void**)&pSurface);
            if (SUCCEEDED(hr))
            {
                m_dxWrite.SetRenderTarget(pSurface);
            }
            if (pSurface) pSurface->Release();
        }
    }
    Init();

    //
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.MinLOD = FLT_MAX;
    sd.MaxLOD = FLT_MIN;
    HRESULT hr = m_pd3dDevice->CreateSamplerState(&sd, &m_pSamplerState);

    return true;
}

bool JCore::GameRun()
{
    // 
    CoreInit();
    //
    while (WinRun())
    {
        CoreFrame();
        CoreRender();
    }
    CoreRelease();
    return true;
}


bool JCore::CoreFrame()
{
    m_GameTimer.Frame();
    JInput::Get().Frame();
    I_ObjectMgr.Frame();
    Frame();
    m_dxWrite.Frame();
    return true;
}

bool JCore::CoreRender()
{
    //float color[4] = { 0.7543f, 0.33421f, 0.8323f,1.0f };
    float color[4] = { 1,0,1,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);
    m_pImmediateContext->PSSetSamplers(0, 1, &m_pSamplerState);

    Render();
    m_GameTimer.Render();
    JInput::Get().Render();
    m_dxWrite.Render();
    m_pSwapChain->Present(0, 0);

    return true;
}

bool JCore::CoreRelease()
{
    Release();
    if (m_pSamplerState)m_pSamplerState->Release();
    m_dxWrite.Release();
    m_GameTimer.Release();
    JInput::Get().Release();
    CleapupDevice();
    return true;
}

void     JCore::ResizeDevice(UINT iWidth, UINT iHeight)
{
    if (m_pd3dDevice == nullptr) return;
    DeleteResizeDevice(iWidth, iHeight);

    m_dxWrite.DeleteDeviceResize();

    JDevice::ResizeDevice(iWidth, iHeight);

    IDXGISurface1* pSurface = nullptr;
    HRESULT hr = m_pSwapChain->GetBuffer(0,
        __uuidof(IDXGISurface1),
        (void**)&pSurface);
    if (SUCCEEDED(hr))
    {
        m_dxWrite.SetRenderTarget(pSurface);
    }
    if (pSurface) pSurface->Release();

    CreateResizeDevice(iWidth, iHeight);
}

JCore::JCore()
{
}

JCore::~JCore()
{
}

