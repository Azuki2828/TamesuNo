#include "stdafx.h"
#include "MainCamera.h"

namespace nsMyGame{

	namespace {

		CVector3 c_startPosition = { 0.0f,200.0f,-500.0f };	//初期視点
		CVector3 c_startTarget = { 0.0f,0.0f,0.0f };		//初期注視点
	}

	bool CMainCamera::Start() {

		//カメラを初期化。
		Init();

		//ばねカメラの初期化。
		m_springCamera.Init(
			*g_camera3D,						// ばねカメラの処理を行うカメラを指定する。
			2500.0f,			// カメラの移動速度の最大値。
			/*isEnableCollisionSolve=*/true,	// カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
			5.0f				// カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
		);
		m_springCamera.SetDampingRate(0.8f);

		return true;
	}

	void CMainCamera::Update() {

		/*if (g_pad[0]->IsPress(enButtonRight)) {

			m_position.x += 20.0f;
		}
		if (g_pad[0]->IsPress(enButtonLeft)) {

			m_position.x -= 20.0f;
		}
		if (g_pad[0]->IsPress(enButtonUp)) {

			m_position.z += 20.0f;
		}
		if (g_pad[0]->IsPress(enButtonDown)) {

			m_position.z -= 20.0f;
		}*/

		m_springCamera.SetPosition(m_position);
		m_springCamera.SetTarget(m_target);
		m_springCamera.SetFar(10000.0f);
		m_springCamera.Update();
	}

	void CMainCamera::Init() {

		//カメラを初期化。
		m_position = c_startPosition;
		m_target = c_startTarget;

		g_camera3D->SetTarget(m_target);
		g_camera3D->SetPosition(m_position);
		g_camera3D->Update();
	}
}