#include "stdafx.h"
#include "Button.h"

namespace nsMyGame {

	bool CButton::Start() {


		return true;
	}

	void CButton::Init(const char* filePathTkm) {

		//モデルを作成。
		m_modelRender = NewGO<CModelRender>(enPriority_Zeroth);
		m_modelRender->SetFilePathTkm(filePathTkm);
		m_modelRender->SetPosition(m_position);
		m_modelRender->Init();
	}

	void CButton::OnDestroy() {

		//モデルを削除。
		DeleteGO(m_modelRender);
		m_modelRender = nullptr;
	}

	void CButton::Update() {

		//座標を更新。
		m_modelRender->SetPosition(m_position);
	}
}