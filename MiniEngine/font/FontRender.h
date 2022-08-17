#pragma once
#include "constFont.h"
#include "stdafx.h"

namespace nsMyGame {

	namespace nsFont {

		class CFontRender : public CIGameObject
		{
		public:
			/**
			 * @brief �t�H���g�̃f�[�^
			*/
			struct SFontValue {
				wchar_t text[c_maxTextSize];	//�e�L�X�g
				CVector2 position = CVector2::Zero;	//���W
				CVector4 color = CVector4::White;		//�F
				float rotation = 0.0f;		//��]
				float scale = 1.0f;		//�g�嗦
				CVector2 pivot = CVector2::Half;		//�s�{�b�g
			};

			/**
			 * @brief �e�L�X�g��ݒ肷��֐�
			 * @param text �e�L�X�g
			*/
			void SetText(const wchar_t* text)
			{
				swprintf_s(m_fontValue.text, text);
			}

			/**
			 * @brief ���W��ݒ肷��֐�
			 * @param pos ���W
			*/
			void SetPosition(const CVector2& pos) {
				m_fontValue.position = pos;
			}

			/**
			 * @brief �g�嗦��ݒ肷��֐�
			 * @param sca �g�嗦
			*/
			void SetScale(const float sca) {
				m_fontValue.scale = sca;
			}

			/**
			 * @brief �t�H���g�̐F��ݒ肷��֐�
			 * @param col �F
			*/
			void SetColor(const CVector4& col) {
				m_fontValue.color = col;
			}

			/**
			 * @brief �s�{�b�g��ݒ肷��֐�
			 * @param piv �s�{�b�g
			*/
			void SetPivot(const CVector2& piv) {
				m_fontValue.pivot = piv;
			}

			/**
			 * @brief �������֐�
			 * @param text �e�L�X�g
			 * @param position ���W
			 * @param color �F
			 * @param rotation ��]
			 * @param scale �g�嗦
			 * @param pivot �s�{�b�g
			*/
			void Init(
				const wchar_t* text,
				const CVector2& position = CVector2::Zero,
				const CVector4& color = CVector4::Black,
				const float rotation = 0.0f,
				const float scale = 1.0f,
				const CVector2& pivot = { 0.5f,0.5f }
			);

			/**
			 * @brief �g�̉e��t����֐�
			 * @param isDrawShadow �g�̉e��t���邩�ǂ����̃t���O
			 * @param shadowOffset �g�̉e�̑���
			 * @param shadowColor �g�̉e�̐F
			*/
			void SetShadowParam(bool isDrawShadow, float shadowOffset, const CVector4& shadowColor)
			{
				m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
			}

			/**
			 * @brief �`��֐�
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void Render(CRenderContext& rc)override final;

		private:
			CFont m_font;			//�t�H���g
			SFontValue m_fontValue;	//�t�H���g�̃f�[�^
		};
	}
}

