#include "stdafx.h"
#include "MainCamera.h"

namespace nsMyGame{

	namespace {

		CVector3 c_startPosition = { 0.0f,200.0f,-500.0f };	//�������_
		CVector3 c_startTarget = { 0.0f,0.0f,0.0f };		//���������_
	}

	bool CMainCamera::Start() {

		//�J�������������B
		Init();

		//�΂˃J�����̏������B
		m_springCamera.Init(
			*g_camera3D,						// �΂˃J�����̏������s���J�������w�肷��B
			2500.0f,			// �J�����̈ړ����x�̍ő�l�B
			/*isEnableCollisionSolve=*/true,	// �J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
			5.0f				// �J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
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

		//�J�������������B
		m_position = c_startPosition;
		m_target = c_startTarget;

		g_camera3D->SetTarget(m_target);
		g_camera3D->SetPosition(m_position);
		g_camera3D->Update();
	}
}