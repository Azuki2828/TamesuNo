#include "stdafx.h"
#include "Game.h"
#include "Button.h"
#include "Title.h"
#include "MainCamera.h"

namespace nsMyGame {

	namespace {

		const CVector3 c_buttonRedPosition = { -100.0f,100.0f,100.0f };			//�ԃ{�^���̍��W
		const CVector3 c_buttonBluePosition = { 100.0f,100.0f,100.0f };			//�{�^���̍��W
		const CVector3 c_buttonYellowPosition = { -100.0f,100.0f,-100.0f };		//���{�^���̍��W
		const CVector3 c_buttonGreenPosition = { 100.0f,100.0f,-100.0f };		//�΃{�^���̍��W
	}
	bool CGame::Start() {

		//�^�C�g����ʂ��쐬�B
		m_title = NewGO<CTitle>(enPriority_Zeroth);

		//���C���J�������쐬�B
		m_mainCamera = NewGO<CMainCamera>(enPriority_Zeroth);

		//�e�{�^�����쐬�B
		for (int buttonNum = 0; buttonNum < enButton_Num; buttonNum++) {

			m_button[buttonNum] = NewGO<CButton>(enPriority_First);
			m_button[buttonNum]->Init(GetTkmFilePath(buttonNum));
		}

		//�e�{�^���̍��W��ݒ�B
		m_button[enButton_Red]->SetPosition(c_buttonRedPosition);
		m_button[enButton_Blue]->SetPosition(c_buttonBluePosition);
		m_button[enButton_Yellow]->SetPosition(c_buttonYellowPosition);
		m_button[enButton_Green]->SetPosition(c_buttonGreenPosition);

		return true;
	}

	void CGame::OnDestroy() {

		//�^�C�g�����폜�B
		DeleteGO(m_title);
		m_title = nullptr;

		//���C���J�������폜�B
		DeleteGO(m_mainCamera);
		m_mainCamera = nullptr;

		//�{�^�����폜�B
		for (int buttonNum = 0; buttonNum < enButton_Num; buttonNum++) {
			DeleteGO(m_button[buttonNum]);
			m_button[buttonNum] = nullptr;
		}
	}

	void CGame::Update() {


	}

	const char* CGame::GetTkmFilePath(const int buttonNum)
	{
		const char* tkmFilePath = nullptr;

		//�{�^���ԍ�����tkm�t�@�C���p�X���擾�B
		switch (static_cast<EnButton>(buttonNum)) {

		case enButton_Red:
			tkmFilePath = "Assets/modelData/button/button_Red.tkm";
			break;
		case enButton_Blue:
			tkmFilePath = "Assets/modelData/button/button_Blue.tkm";
			break;
		case enButton_Yellow:
			tkmFilePath = "Assets/modelData/button/button_Yellow.tkm";
			break;
		case enButton_Green:
			tkmFilePath = "Assets/modelData/button/button_Green.tkm";
			break;
		default:
			//�擾���s�B
			MessageBox(nullptr, L"�t�@�C���p�X�̎擾�Ɏ��s���܂����B", L"�G���[", MB_OK);
			break;
		}

		//�擾�����p�X��Ԃ��B
		return tkmFilePath;
	}
}