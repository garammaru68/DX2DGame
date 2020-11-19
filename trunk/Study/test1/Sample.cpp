#include "Sample.h"

bool Sample::Init()
{
	HRESULT hr;
	SAFE_NEW(m_pLine, TLineShape);
	if (FAILED(m_pLine->Create(GetDevice(), L"../../data/shader/line.hlsl")))
	{
		MessageBox(0, _T("m_pLIne 실패"), _T("Fatal error"), MB_OK);
		return false;
	}

	//--------------------------------------------------------------------------------------
	// 박스 오브젝트 생성( 100개 박스가 공유해서 사용함)
	//--------------------------------------------------------------------------------------
	SAFE_NEW(m_pBoxShape, TBoxShape);
	if (FAILED(m_pBoxShape->Create(GetDevice(), L"../../data/shader/box.hlsl", L"../../data/obj/checker_with_numbers.bmp")))
	{
		MessageBox(0, _T("m_LineShape 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	//--------------------------------------------------------------------------------------
	// 카메라 프로스텀 랜더링용 박스 오브젝트 생성
	//--------------------------------------------------------------------------------------
	m_MainCamera.CreateRenderBox(GetDevice(), m_pImmediateContext);
	m_pPixelShader.Attach(DX::LoadPixelShaderFile(GetDevice(), L"../../data/shader/box.hlsl", "PS_Color"));

	m_TBoxBase.vCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TBoxBase.vMax = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_TBoxBase.vMin = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);

	//--------------------------------------------------------------------------------------
	// 100개 박스의 위치를 세팅함
	//--------------------------------------------------------------------------------------
	D3DXMATRIX matScale, matRotation, matWorld;
	for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
	{
		m_vBoxPosition[iBox] = D3DXVECTOR3(25 - rand() % 50, 25 - rand() % 50, 25 - rand() % 50);
		m_vBoxColor[iBox] = D3DXVECTOR4((rand() % 256) / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f, 1.0f);

		// g_matWorld Matrix = S * R
		D3DXMatrixScaling(&matScale, (rand() % 256) / 255.0f * 3.0f, (rand() % 256) / 255.0f * 3.0f, (rand() % 256) / 255.0f * 3.0f);
		D3DXMatrixRotationYawPitchRoll(&matRotation, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f);
		D3DXMatrixMultiply(&matWorld, &matScale, &matRotation);

		// OBB 기저벡터 변환( 회전 변환 이후 정규화 )
		m_TBox[iBox].vCenter = m_vBoxPosition[iBox];
		D3DXVECTOR3 vMax, vMin, vHalf;
		D3DXVec3TransformCoord(&m_TBox[iBox].vAxis[0], &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &matWorld);
		D3DXVec3TransformCoord(&m_TBox[iBox].vAxis[1], &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &matWorld);
		D3DXVec3TransformCoord(&m_TBox[iBox].vAxis[2], &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &matWorld);
		D3DXVec3Normalize(&m_TBox[iBox].vAxis[0], &m_TBox[iBox].vAxis[0]);
		D3DXVec3Normalize(&m_TBox[iBox].vAxis[1], &m_TBox[iBox].vAxis[1]);
		D3DXVec3Normalize(&m_TBox[iBox].vAxis[2], &m_TBox[iBox].vAxis[2]);

		// g_matWorld Matrix = S * R * T
		matWorld._41 = m_vBoxPosition[iBox].x;
		matWorld._42 = m_vBoxPosition[iBox].y;
		matWorld._43 = m_vBoxPosition[iBox].z;

		// OBB 기저벡터의 크기 계산
		D3DXVec3TransformCoord(&vMax, &m_TBoxBase.vMax, &matWorld);
		D3DXVec3TransformCoord(&vMin, &m_TBoxBase.vMin, &matWorld);
		vHalf = vMax - m_TBox[iBox].vCenter;
		m_TBox[iBox].fExtent[0] = D3DXVec3Dot(&m_TBox[iBox].vAxis[0], &vHalf);
		m_TBox[iBox].fExtent[1] = D3DXVec3Dot(&m_TBox[iBox].vAxis[1], &vHalf);
		m_TBox[iBox].fExtent[2] = D3DXVec3Dot(&m_TBox[iBox].vAxis[2], &vHalf);

		m_matBoxWorld[iBox] = matWorld;
	}

	//--------------------------------------------------------------------------------------
	// 미니맵 영역에 랜더링할 랜더타켓용 텍스처 생성( 기본 카메라 : 탑뷰 ) 
	//--------------------------------------------------------------------------------------
	if (!m_MiniMap.Create(GetDevice(), L"../../data/shader/plane.hlsl"))
	{
		return false;
	}
	m_MiniMap.Set(GetDevice(), 0, m_SwapChainDesc.BufferDesc.Height - 300, 300, 300);

	//--------------------------------------------------------------------------------------
	// 메인 카메라의 뷰 및 투영 행렬 세팅
	//--------------------------------------------------------------------------------------
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);
	// 메인 카메라 뷰 행렬 세팅
	m_MainCamera.SetViewMatrix(D3DXVECTOR3(0.0f, 0.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), vUpVector);
	m_fRadius = D3DXVec3Length(&(m_MainCamera.m_vCameraPos - m_MainCamera.m_vTargetPos));
	m_fCameraYaw = m_MainCamera.m_fCameraYawAngle;
	m_fCameraPitch = m_MainCamera.m_fCameraPitchAngle;
	// 투영행렬 세팅
	DXGI_SWAP_CHAIN_DESC Desc;
	if (FAILED(GetSwapChain()->GetDesc(&Desc)))
	{
		return false;
	}
	m_MainCamera.SetProjMatrix(D3DX_PI * 0.25f,
		Desc.BufferDesc.Width / (float)(Desc.BufferDesc.Height),
		0.1f, 50.0f);

	return true;
}
bool Sample::Frame()
{
	// 2초당 1회전( 1 초 * D3DX_PI = 3.14 )
	float t = m_Timer.GetElapsedTime() * D3DX_PI;

	//--------------------------------------------------------------------------------------
	// 카메라 포지션 전후 좌우 이동
	//--------------------------------------------------------------------------------------
	m_fRadius = 0;
	if (I_Input.KeyCheck(DIK_W))
	{
		m_MainCamera.MoveLook(m_Timer.GetSPF() * 2.0f);
	}
	if (I_Input.KeyCheck(DIK_S))
	{
		m_MainCamera.MoveLook(-m_Timer.GetSPF() * 2.0f);
	}
	if (I_Input.KeyCheck(DIK_D))
	{
		m_MainCamera.MoveSide(m_Timer.GetSPF() * 2.0f);
	}
	if (I_Input.KeyCheck(DIK_A))
	{
		m_MainCamera.MoveSide(-m_Timer.GetSPF() * 2.0f);
	}
	if (I_Input.KeyCheck(DIK_Q))
	{
		m_MainCamera.MoveUp(m_Timer.GetSPF() * 2.0f);
	}
	if (I_Input.KeyCheck(DIK_E))
	{
		m_MainCamera.MoveUp(-m_Timer.GetSPF() * 2.0f);
	}
	//--------------------------------------------------------------------------------------
	// 카메라 회전
	//--------------------------------------------------------------------------------------
	if (I_Input.m_DIMouseState.rgbButtons[0])
	{
		m_fCameraYaw += D3DXToRadian(g_InputData.iMouseValue[0] * 0.1f);
		m_fCameraPitch += D3DXToRadian(g_InputData.iMouseValue[1] * 0.1f);
	}
	if (I_Input.m_DIMouseState.lZ != 0)
	{
		m_fRadius = -1.0f * (m_Timer.GetSPF() * I_Input.m_DIMouseState.lZ);
	}

	m_MainCamera.Update(D3DXVECTOR4(m_fCameraPitch, m_fCameraYaw, m_fCameraRoll, m_fRadius));
	//--------------------------------------------------------------------------------------
	// 미니맵 갱신
	//--------------------------------------------------------------------------------------
	return m_MiniMap.Frame();
}
bool Sample::Render()
{
	HRESULT hr;
	ApplyBS(m_pImmediateContext, TDxState::g_pAlphaBlend);
	ApplyDSS(m_pImmediateContext, TDxState::g_pDSSDepthEnable);
	ApplyRS(m_pImmediateContext, TDxState::g_pRSBackCullSolid);
	//--------------------------------------------------------------------------------------
	// 박스 랜더링
	//--------------------------------------------------------------------------------------
	D3DXMATRIX matScale, matRotation;
	for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
	{
		m_pBoxShape->m_cbData.Color = m_vBoxColor[iBox];
		m_pBoxShape->SetMatrix(&m_matBoxWorld[iBox], m_MainCamera.GetViewMatrix(), m_MainCamera.GetProjMatrix());
		// OBB와 프로스텀 박스의 제외처리( 걸쳐 있어도 TRUE가 됨. )
		if (m_MainCamera.CheckOBBInPlane(&m_TBox[iBox]))
		{
			m_pBoxShape->Render(m_pImmediateContext);
		}
	}
	//--------------------------------------------------------------------------------------
	// 미니맵의 랜더타켓 텍스처에 100개 오브젝트를 탑뷰로 랜더링
	//--------------------------------------------------------------------------------------
	DrawMiniMap();
	return true;
}
void Sample::DrawMiniMap()
{
	D3DXMATRIX matScale, matRotation;
	if (m_MiniMap.BeginRender(m_pImmediateContext))
	{
		for (int iBox = 0; iBox < NUM_OBJECTS; iBox++)
		{
			m_pBoxShape->SetMatrix(&m_matBoxWorld[iBox], &m_MiniMap.m_matView, &m_MiniMap.m_matProj);

			// 프러스텀 박스의 내부에 박수의 원점이 존재할 경우.
			if (m_MainCamera.ClassifyPoint(&m_vBoxPosition[iBox]))
			{
				float fDistance = D3DXVec3Length(&(*m_MainCamera.GetEyePt() - m_vBoxPosition[iBox])) / 100.0f;
				m_pBoxShape->m_cbData.Color = D3DXVECTOR4(fDistance, fDistance, fDistance, 1.0f);
				m_pBoxShape->Render(m_pImmediateContext);
			}
			else
			{
				// 박스의 원점이 프로스텀 외부에 위치하고 있으나 프러스텀 평면에 걸쳐 있을 경우
				if (m_MainCamera.CheckOBBInPlane(&m_TBox[iBox]))
				{
					m_pBoxShape->m_cbData.Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
					m_pBoxShape->Render(m_pImmediateContext);
				}
				else
				{
					// 프로스텀 박스의 외부에 존재할 경우
					//m_pBoxShape->m_cbData.Color = m_vBoxColor[iBox];	
					m_pBoxShape->m_cbData.Color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);

					m_pBoxShape->Render(m_pImmediateContext);
				}
			}
		}

		// 프로스텀 랜더링
		//ApplyBS(m_pImmediateContext, TDxState::g_pBSOneOne);
		m_MainCamera.SetMatrix(NULL, &m_MiniMap.m_matView, &m_MiniMap.m_matProj);
		ApplyBS(m_pImmediateContext, TDxState::g_pAlphaBlend);// ::g_pBSOneOne);
		m_MainCamera.m_pBoxShape->m_cbData.Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f);
		m_MainCamera.PreRender(m_pImmediateContext);
		{
			m_pImmediateContext->PSSetShader(m_pPixelShader.Get(), NULL, 0);
			m_MainCamera.PostRender(m_pImmediateContext);
		}
		m_MiniMap.EndRender(m_pImmediateContext);
	}

	//--------------------------------------------------------------------------------------
	// 랜더타켓의 텍스처를 미니맵 영역에 랜더링
	//--------------------------------------------------------------------------------------
	ApplyDSS(m_pImmediateContext, TDxState::g_pDSSDepthDisable);
	ApplyBS(m_pImmediateContext, TDxState::g_pBSOneZero);
	m_MiniMap.Render(m_pImmediateContext);
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT Sample::CreateResource()
{
	HRESULT hr;
	{
		float fAspectRatio = m_SwapChainDesc.BufferDesc.Width /
			(float)m_SwapChainDesc.BufferDesc.Height;
		m_MainCamera.SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 500.0f);
	}
	return S_OK;
}
//--------------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------------
HRESULT Sample::DeleteResource()
{
	HRESULT hr = S_OK;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}
bool Sample::Release()
{
	SAFE_DEL(m_pBoxShape);
	SAFE_DEL(m_pLine);
	return true;
}
bool Sample::DrawDebug(bool bDrawString, bool bDrawLine)
{
	/* OBB 의 기저벡터 드로우
	D3DXVECTOR3 vEnd;
	for( int iBox=0;iBox < NUM_OBJECTS; iBox++ )
	{
		m_pLine->SetMatrix( NULL, &m_matView, &m_matProj);
		vEnd = m_TBox[iBox].vCenter + m_TBox[iBox].vAxis[0] * m_TBox[iBox].fExtent[0];
		m_pLine->Draw(	m_TBox[iBox].vCenter,vEnd, D3DXVECTOR4( 1.0f, 1.0f, 0.0f, 1.0f ) );
		vEnd = m_TBox[iBox].vCenter + m_TBox[iBox].vAxis[1] * m_TBox[iBox].fExtent[1];
		m_pLine->Draw(	m_TBox[iBox].vCenter,vEnd, D3DXVECTOR4( 1.0f, 1.0f, 0.0f, 1.0f ) );
		vEnd = m_TBox[iBox].vCenter + m_TBox[iBox].vAxis[2] * m_TBox[iBox].fExtent[2];
		m_pLine->Draw(	m_TBox[iBox].vCenter,vEnd, D3DXVECTOR4( 1.0f, 1.0f, 0.0f, 1.0f ) );
	}*/

	//-----------------------------------------------------------------------
	// 적용되어 있는 카메라의 방향벡터 표시
	//-----------------------------------------------------------------------
	T_STR	str;
	RECT			rc;
	str.clear();
	TCHAR pBuffer[256];
	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("Look:%10.4f,%10.4f,%10.4f \n"), m_MainCamera.m_vLookVector.x,
		m_MainCamera.m_vLookVector.y,
		m_MainCamera.m_vLookVector.z);
	str += pBuffer;

	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("Up:%10.4f,%10.4f,%10.4f \n"), m_MainCamera.m_vUpVector.x,
		m_MainCamera.m_vUpVector.y,
		m_MainCamera.m_vUpVector.z);
	str += pBuffer;

	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("Right:%10.4f,%10.4f,%10.4f \n"), m_MainCamera.m_vRightVector.x,
		m_MainCamera.m_vRightVector.y,
		m_MainCamera.m_vRightVector.z);
	str += pBuffer;

	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("p:%10.4f,%10.4f,%10.4f "), m_MainCamera.m_vCameraPos.x,
		m_MainCamera.m_vCameraPos.y,
		m_MainCamera.m_vCameraPos.z);
	str += pBuffer;

	rc.left = m_DefaultRT.m_vp.TopLeftX + m_DefaultRT.m_vp.Width*0.5f;
	rc.top = m_DefaultRT.m_vp.Height - 80;
	rc.right = 0;
	rc.bottom = 0;
	DrawDebugRect(&rc, const_cast<TCHAR*>(str.c_str()), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	return TBasisLib::DrawDebug();
}
HRESULT Sample::ScreenViewPort(UINT iWidth, UINT iHeight)
{
	HRESULT hr = S_OK;
	UINT iRectWidth = iWidth / 3;
	UINT iRectHeight = iHeight / 3;
	//--------------------------------------------------------------------------------------
	// 미니맵 영역 설정
	//--------------------------------------------------------------------------------------
	m_MiniMapVP.Set(0, iHeight - iRectHeight, iRectWidth, iRectHeight, 0.0f, 1.0f);
	return hr;
}

Sample::Sample(void)
{
	m_fCameraYaw = 0.0f;
	m_fCameraPitch = 0.0f;
	m_fCameraRoll = 0.0f;
	m_fRadius = 0.0f;
	SAFE_ZERO(m_pBoxShape);
	SAFE_ZERO(m_pLine);
}

Sample::~Sample(void)
{
	Release();
}
TBASIS_RUN(L"TBasisSample Frustum Culling");
