#include "stdafx.h"
#include "Bloom.h"

namespace nsMyGame {

	namespace nsPostEffect {

		void CBloom::OnInit() {

			//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬�B
			m_luminanceRT.Create(
				c_renderTargetW1280H720.x,       // �𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ���
				c_renderTargetW1280H720.y,        // �𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ���
				c_mipLevel1,
				c_renderArraySize1,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				DXGI_FORMAT_D32_FLOAT
			);

			//�P�x���o�p�̃X�v���C�g���������B
			InitLuminanceSprite();

			//�K�E�V�A���u���[�p�̃X�v���C�g���������B
			InitGaussianBlurSprite();
		}

		void CBloom::OnRender(CRenderContext& rc) {

			//�P�x���o
			ExecuteDrawLuminanceSprite(rc);

			//�K�E�V�A���u���[
			ExecuteGaussianBlur(rc);
		}

		void CBloom::InitLuminanceSprite() {

			//�P�x���o�p�̃X�v���C�g��������
			//�����������쐬����
			SpriteInitData luminanceSpriteInitData;

			//�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
			luminanceSpriteInitData.m_fxFilePath = c_fxFilePathBloom;

			//���_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
			luminanceSpriteInitData.m_vsEntryPointFunc = c_vsEntryPointFuncBloom;

			//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
			luminanceSpriteInitData.m_psEntryPoinFunc = c_psEntryPointFuncSamplingLuminance;

			//�X�v���C�g�̕��ƍ����͋P�x���o�p�̃����_�����O�^�[�Q�b�g�Ɠ����B
			luminanceSpriteInitData.m_width = m_luminanceRT.GetWidth();
			luminanceSpriteInitData.m_height = m_luminanceRT.GetHeight();

			//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�[�B
			luminanceSpriteInitData.m_textures[0] = &CRenderTarget::GetRenderTarget(enMainRT)->GetRenderTargetTexture();

			//�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��B
			luminanceSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

			//�쐬�����������������ƂɃX�v���C�g������������B
			m_luminanceSprite.Init(luminanceSpriteInitData);
		}

		void CBloom::InitGaussianBlurSprite() {

			//�K�E�V�A���u���[�N���X�̃C���X�^���X���������B
			m_gaussianBlur[0].Init(&m_luminanceRT.GetRenderTargetTexture());
			m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());
			m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());
			m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

			//�{�P�摜���������ď������ނ��߂̃X�v���C�g��������
			SpriteInitData finalSpriteInitData;

			//�K�E�V�A���u���[�p�̃e�N�X�`����ݒ�B
			finalSpriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();
			finalSpriteInitData.m_textures[1] = &m_gaussianBlur[1].GetBokeTexture();
			finalSpriteInitData.m_textures[2] = &m_gaussianBlur[2].GetBokeTexture();
			finalSpriteInitData.m_textures[3] = &m_gaussianBlur[3].GetBokeTexture();

			//�X�v���C�g�̕��ƍ����̓��C�������_�����O�^�[�Q�b�g�Ɠ���
			finalSpriteInitData.m_width = CRenderTarget::GetRenderTarget(enMainRT)->GetWidth();
			finalSpriteInitData.m_height = CRenderTarget::GetRenderTarget(enMainRT)->GetHeight();

			//�K�E�V�A���u���[�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
			finalSpriteInitData.m_fxFilePath = c_fxFilePathBloom;

			//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
			finalSpriteInitData.m_psEntryPoinFunc = c_psEntryPointFuncBloomFinal;

			//�A���t�@�u�����f�B���O���[�h�͉��Z������I������B
			finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;

			//�J���[�o�b�t�@�̃t�H�[�}�b�g�̓��C�������_�����O�^�[�Q�b�g�Ɠ����ɂ���B
			finalSpriteInitData.m_colorBufferFormat = CRenderTarget::GetRenderTarget(enMainRT)->GetColorBufferFormat();

			//�X�v���C�g���������B
			m_bloomFinalSprite.Init(finalSpriteInitData);
		}

		void CBloom::ExecuteDrawLuminanceSprite(CRenderContext& rc) {

			// �P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
			rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRT);

			// �����_�����O�^�[�Q�b�g��ݒ�
			rc.SetRenderTargetAndViewport(m_luminanceRT);

			// �����_�����O�^�[�Q�b�g���N���A
			rc.ClearRenderTargetView(m_luminanceRT);

			// �P�x���o���s��
			m_luminanceSprite.Draw(rc);

			// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
			rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRT);
		}

		void CBloom::ExecuteGaussianBlur(CRenderContext& rc) {

			//�K�E�V�A���u���[��4����s����
			for (int i = 0; i < c_gaussianBlurNum; i++) {

				m_gaussianBlur[i].ExecuteOnGPU(rc, c_blurPower);
			}

			//4���̃{�P�摜���������ă��C�������_�����O�^�[�Q�b�g�ɉ��Z����
			rc.WaitUntilToPossibleSetRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));

			//�����_�����O�^�[�Q�b�g�ƃr���[�|�[�g��ݒ�B
			rc.SetRenderTargetAndViewport(*CRenderTarget::GetRenderTarget(enMainRT));

			//�ŏI�X�v���C�g��`��B
			m_bloomFinalSprite.Draw(rc);

			//�`�����ݏI���҂��B
			rc.WaitUntilFinishDrawingToRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));
		}
	}
}