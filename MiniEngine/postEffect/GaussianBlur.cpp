#include "stdafx.h"
#include "GaussianBlur.h"

namespace nsMyGame {

	namespace nsPostEffect {

		void CGaussianBlur::Init(Texture* originalTexture)
		{
			m_originalTexture = originalTexture;

			//�����_�����O�^�[�Q�b�g���������B
			InitRenderTargets();
			//�X�v���C�g���������B
			InitSprites();
		}


		void CGaussianBlur::ExecuteOnGPU(CRenderContext& rc, float blurPower)
		{
			//�d�݃e�[�u�����X�V����B
			UpdateWeightsTable(blurPower);

			//���u���[�����s�B
			ExecuteBesideBlur(rc);

			//�c�u���[�����s�B
			ExecuteVerticalBlur(rc);
		}

		void CGaussianBlur::InitRenderTargets()
		{
			//X�u���[�p�̃����_�����O�^�[�Q�b�g���쐬����B
			m_xBlurRenderTarget.Create(
				m_originalTexture->GetWidth() / 2,
				m_originalTexture->GetHeight(),
				1,
				1,
				m_originalTexture->GetFormat(),
				DXGI_FORMAT_D32_FLOAT
			);

			//Y�u���[�p�̃����_�����O�^�[�Q�b�g���쐬����B
			m_yBlurRenderTarget.Create(
				m_originalTexture->GetWidth() / 2,
				m_originalTexture->GetHeight() / 2,
				1,
				1,
				m_originalTexture->GetFormat(),
				DXGI_FORMAT_D32_FLOAT
			);
		}

		void CGaussianBlur::InitSprites()
		{
			//���u���[�p�̃X�v���C�g������������B
			{
				SpriteInitData xBlurSpriteInitData;
				xBlurSpriteInitData.m_fxFilePath = c_fxFilePathGaussianBlur;
				xBlurSpriteInitData.m_vsEntryPointFunc = c_vsEntryPointFuncXBlur;
				xBlurSpriteInitData.m_psEntryPoinFunc = c_psEntryPointFuncBlur;
				//�X�v���C�g�̉𑜓x��m_xBlurRenderTarget�Ɠ����B
				xBlurSpriteInitData.m_width = m_xBlurRenderTarget.GetWidth();
				xBlurSpriteInitData.m_height = m_xBlurRenderTarget.GetHeight();
				//�e�N�X�`���͋P�x�e�N�X�`���B
				xBlurSpriteInitData.m_textures[0] = m_originalTexture;
				//�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��B
				xBlurSpriteInitData.m_colorBufferFormat = m_xBlurRenderTarget.GetColorBufferFormat();
				//���[�U�[�g���̒萔�o�b�t�@�Ƀu���[�p�̃p�����[�^�[��ݒ肷��B
				xBlurSpriteInitData.m_expandConstantBuffer = &m_weights;
				xBlurSpriteInitData.m_expandConstantBufferSize = sizeof(m_weights);

				//�������������Ƃɉ��u���[�p�̃X�v���C�g������������B
				m_xBlurSprite.Init(xBlurSpriteInitData);
			}
			//�c�u���[�p�̃X�v���C�g������������B
			{
				SpriteInitData yBlurSpriteInitData;
				yBlurSpriteInitData.m_fxFilePath = c_fxFilePathGaussianBlur;
				yBlurSpriteInitData.m_vsEntryPointFunc = c_vsEntryPointFuncYBlur;
				yBlurSpriteInitData.m_psEntryPoinFunc = c_psEntryPointFuncBlur;
				//�X�v���C�g�̉𑜓x��m_yBlurRenderTarget�Ɠ����B
				yBlurSpriteInitData.m_width = m_yBlurRenderTarget.GetWidth();
				yBlurSpriteInitData.m_height = m_yBlurRenderTarget.GetHeight();
				//�e�N�X�`���͉��u���[�����������́B
				yBlurSpriteInitData.m_textures[0] = &m_xBlurRenderTarget.GetRenderTargetTexture();
				//�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��B
				yBlurSpriteInitData.m_colorBufferFormat = m_yBlurRenderTarget.GetColorBufferFormat();
				//���[�U�[�g���̒萔�o�b�t�@�Ƀu���[�p�̃p�����[�^�[��ݒ肷��B
				yBlurSpriteInitData.m_expandConstantBuffer = &m_weights;
				yBlurSpriteInitData.m_expandConstantBufferSize = sizeof(m_weights);

				//�������������Ƃɏc�u���[�p�̃X�v���C�g������������B
				m_yBlurSprite.Init(yBlurSpriteInitData);
			}
		}
		void CGaussianBlur::UpdateWeightsTable(float blurPower)
		{
			float total = 0;
			for (int i = 0; i < c_gaussianBlurNumWeight; i++) {
				m_weights[i] = expf(-0.5f * (float)(i * i) / blurPower);
				total += 2.0f * m_weights[i];

			}
			// �K�i��
			for (int i = 0; i < c_gaussianBlurNumWeight; i++) {
				m_weights[i] /= total;
			}
		}

		void CGaussianBlur::ExecuteVerticalBlur(CRenderContext& rc) {

			//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���悤�ɂȂ�܂�wait������B
			rc.WaitUntilToPossibleSetRenderTarget(m_yBlurRenderTarget);
			//�����_�����O�^�[�Q�b�g��ݒ�B
			rc.SetRenderTargetAndViewport(m_yBlurRenderTarget);
			//�����_�����O�^�[�Q�b�g���N���A�B
			rc.ClearRenderTargetView(m_yBlurRenderTarget);
			//�h���[�B
			m_yBlurSprite.Draw(rc);
			//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂��B
			rc.WaitUntilFinishDrawingToRenderTarget(m_yBlurRenderTarget);
		}

		void CGaussianBlur::ExecuteBesideBlur(CRenderContext& rc) {

			//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���悤�ɂȂ�܂�wait������B
			rc.WaitUntilToPossibleSetRenderTarget(m_xBlurRenderTarget);
			//�����_�����O�^�[�Q�b�g��ݒ�B
			rc.SetRenderTargetAndViewport(m_xBlurRenderTarget);
			//�����_�����O�^�[�Q�b�g���N���A�B
			rc.ClearRenderTargetView(m_xBlurRenderTarget);
			//�h���[�B
			m_xBlurSprite.Draw(rc);
			//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂��B
			rc.WaitUntilFinishDrawingToRenderTarget(m_xBlurRenderTarget);
		}
	}
}