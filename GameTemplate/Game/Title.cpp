#include "stdafx.h"
#include "Title.h"

namespace nsMyGame {

	namespace {

		constexpr const char* c_backSpriteName = "Assets/image/back.dds";	//�^�C�g���摜�i�w�i�摜�j
		const CVector2 c_backSpriteSize = { 1280.0f,720.0f };				//�w�i�摜�̃T�C�Y
	}

	bool CTitle::Start() {

		

		//�w�i�摜���쐬�B
		m_backSprite = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_backSprite->Init(c_backSpriteName, c_backSpriteSize.x, c_backSpriteSize.y);

		return true;
	}

	void CTitle::OnDestroy() {

		

		//�w�i���폜�B
		DeleteGO(m_backSprite);
		m_backSprite = nullptr;
	}

	void CTitle::Update() {


	}
}
