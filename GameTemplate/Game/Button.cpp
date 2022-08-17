#include "stdafx.h"
#include "Button.h"

namespace nsMyGame {

	bool CButton::Start() {


		return true;
	}

	void CButton::Init(const char* filePathTkm) {

		//���f�����쐬�B
		m_modelRender = NewGO<CModelRender>(enPriority_Zeroth);
		m_modelRender->SetFilePathTkm(filePathTkm);
		m_modelRender->SetPosition(m_position);
		m_modelRender->Init();
	}

	void CButton::OnDestroy() {

		//���f�����폜�B
		DeleteGO(m_modelRender);
		m_modelRender = nullptr;
	}

	void CButton::Update() {

		//���W���X�V�B
		m_modelRender->SetPosition(m_position);
	}
}