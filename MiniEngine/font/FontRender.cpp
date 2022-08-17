#include "stdafx.h"
#include "FontRender.h"


namespace nsMyGame {

	namespace nsFont {

		void CFontRender::Init(
			const wchar_t* text,
			const CVector2& position,
			const CVector4& color,
			const float rotation,
			const float scale,
			const CVector2& pivot
		) {
			//�e�X�̃p�����[�^�[��ݒ�B
			swprintf_s(m_fontValue.text, text);
			m_fontValue.position = position;
			m_fontValue.color = color;
			m_fontValue.rotation = rotation;
			m_fontValue.scale = scale;
			m_fontValue.pivot = pivot;
		}

		void CFontRender::Render(CRenderContext& rc) {


			//�`�惂�[�h���t�H���g�p�̎������`�悷��B
			if (rc.GetRenderMode() == CRenderContext::EnRender_Mode::enRenderMode_Font) {
				m_font.Begin(rc);

				//�t�H���g��`��B
				m_font.Draw(
					m_fontValue.text,
					m_fontValue.position,
					m_fontValue.color,
					m_fontValue.rotation,
					m_fontValue.scale,
					m_fontValue.pivot
				);

				m_font.End(rc);
			}
		}
	}
}