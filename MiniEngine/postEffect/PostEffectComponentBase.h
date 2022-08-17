#pragma once
#include "constPostEffect.h"

namespace nsMyGame {

	namespace nsPostEffect {

		class CPostEffectComponentBase
		{
		public:
			/**
			 * @brief ���N���X�̏������֐��B�h���N���X�̏������ƁA���C�������_�����O�^�[�Q�b�g�ɕ`�悷�邽�߂̃X�v���C�g������������B
			*/
			void Init();

			/**
			 * @brief �`��֐��B�h���N���X�̃X�v���C�g��`�悵�A���C�������_�����O�^�[�Q�b�g�ɔ��f������B
			 * @param rc
			*/
			void Render(CRenderContext& rc);
		private:
			/**
			 * @brief �h���N���X�Œ�`���ׂ��������֐��B
			*/
			virtual void OnInit() = 0;

			/**
			 * @brief �h���N���X�Œ�`���ׂ��`��֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			virtual void OnRender(CRenderContext& rc) = 0;

			/**
			 * @brief �h���N���X�Œ�`���ׂ��A�e�N�X�`�����擾����֐��B
			 * @return �e�N�X�`��
			*/
			virtual Texture& GetResultTexture() = 0;

			/**
			 * @brief �|�X�g�̌��ʂ����C�������_�����O�^�[�Q�b�g�ɃR�s�[����H
			 * @return �R�s�[����H
			*/
			virtual bool IsCopyResultTextureToMainRenderTarget() const
			{
				return false;
			}

		private:
			CSprite m_copyMainRtSprite;		//���C�������_�����O�^�[�Q�b�g�ɕ`�悷�邽�߂̃X�v���C�g�B
		};
	}
}

