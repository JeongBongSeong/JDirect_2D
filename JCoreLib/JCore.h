#pragma once
#include"JDevice.h"
#include"JDxObject.h"
#include"JInput.h"
#include"JTImer.h"
#include "JWriteFont.h"

class JCore : public JDevice
{
public:
	JTimer m_GameTimer;
	JWriteFont m_dxWrite;
	ID3D11SamplerState* m_pSamplerState = nullptr;
public:
	//���� �ݺ� �� ����
	bool CoreInit();

	// ���� ���� �ݺ�
	bool GameRun();
		bool CoreFrame();
		bool CoreRender();

	//���� �ݺ� ���� �� ����
	bool CoreRelease();

	//
public:
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) {};
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) {};
	void			ResizeDevice(UINT iWidth, UINT iHeight);
public:
	virtual bool	Init() { return true; };
	virtual bool	Frame() { return true; };
	virtual bool	Render() { return true; };
	virtual bool	Release() { return true; };
public:
	JCore();
	virtual ~JCore();
};
