#include "stdafx.h"
#include "Fade.h"

namespace nsMyGame {

	bool CFade::Start()
	{
		//�t�F�[�h�p�̃X�v���C�g���������B
		m_fadeSprite = NewGO<CSpriteRender>(enPriority_Fifth);
		m_fadeSprite->Init(c_filePathFadeSprite, FRAME_BUFFER_W, FRAME_BUFFER_H);

		return true;
	}
	void CFade::Update()
	{
		//��Ԃ𒲂ׂ�B
		switch (m_state) {
		case enState_FadeIn:

			//���X�Ƀt�F�[�h�C���B
			m_currentAlpha -= 0.5f * GameTime().GameTimeFunc().GetFrameDeltaTime();

			//�I�������ҋ@��Ԃɐݒ�B
			if (m_currentAlpha <= 0.0f) {
				m_currentAlpha = 0.0f;
				m_state = enState_Idle;
			}
			break;
		case enState_FadeOut:

			//���X�Ƀt�F�[�h�A�E�g�B
			m_currentAlpha += 0.5f * GameTime().GameTimeFunc().GetFrameDeltaTime();

			//�I�������ҋ@��Ԃɐݒ�B
			if (m_currentAlpha >= 1.0f) {
				m_currentAlpha = 1.0f;
				m_state = enState_Idle;
			}
			break;
		case enState_Idle:

			//�ҋ@��ԂȂ炻�̂܂܁B
			break;
		}

		//�����x��ݒ�B
		m_fadeSprite->SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
	}
}