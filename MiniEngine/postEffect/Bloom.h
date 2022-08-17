#pragma once
#include "constPostEffect.h"
#include "PostEffectComponentBase.h"
#include "GaussianBlur.h"


namespace nsMyGame {

	namespace nsPostEffect {

		//�u���[���N���X

		class CBloom : public CPostEffectComponentBase
		{
		public:
			/**
			 * @brief �������֐��B
			*/
			void OnInit()override final;

			/**
			 * @brief �`��֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void OnRender(CRenderContext& rc)override final;

			/**
			 * @brief �P�x�e�N�X�`�����擾����֐��B
			 * @return �P�x�e�N�X�`��
			*/
			Texture& GetResultTexture()override final {

				return m_luminanceRT.GetRenderTargetTexture();
			}

		private:
			/**
			 * @brief �P�x���o�Ɏg�p����X�v���C�g������������֐��B
			*/
			void InitLuminanceSprite();

			/**
			 * @brief �K�E�V�A���u���[�Ɏg�p����X�v���C�g������������֐��B
			*/
			void InitGaussianBlurSprite();

			/**
			 * @brief �P�x���o�����s����֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void ExecuteDrawLuminanceSprite(CRenderContext& rc);

			/**
			 * @brief �K�E�V�A���u���[�����s����֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void ExecuteGaussianBlur(CRenderContext& rc);

		private:
			CRenderTarget m_luminanceRT;							//�P�x���o�p�̃����_�����O�^�[�Q�b�g
			CGaussianBlur m_gaussianBlur[c_gaussianBlurNum];		//�K�E�V�A���u���[�N���X�̃C���X�^���X
			CSprite m_luminanceSprite;							//�P�x���o�p�̃X�v���C�g
			CSprite m_bloomFinalSprite;							//�u���[���̍ŏI�X�v���C�g
		};
	}
}