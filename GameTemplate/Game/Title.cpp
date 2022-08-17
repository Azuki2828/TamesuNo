#include "stdafx.h"
#include "Title.h"

namespace nsMyGame {

	namespace {

		constexpr const char* c_backSpriteName = "Assets/image/back.dds";	//ƒ^ƒCƒgƒ‹‰æ‘œi”wŒi‰æ‘œj
		const CVector2 c_backSpriteSize = { 1280.0f,720.0f };				//”wŒi‰æ‘œ‚ÌƒTƒCƒY
	}

	bool CTitle::Start() {

		

		//”wŒi‰æ‘œ‚ğì¬B
		m_backSprite = NewGO<CSpriteRender>(enPriority_Zeroth);
		m_backSprite->Init(c_backSpriteName, c_backSpriteSize.x, c_backSpriteSize.y);

		return true;
	}

	void CTitle::OnDestroy() {

		

		//”wŒi‚ğíœB
		DeleteGO(m_backSprite);
		m_backSprite = nullptr;
	}

	void CTitle::Update() {


	}
}
