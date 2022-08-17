#pragma once

namespace nsMyGame {

	//�V���h�E�}�b�v�N���X
	class CShadowMap
	{
	public:
		/**
		 * @brief �������֐��B
		*/
		void Init();

		/**
		 * @brief �V���h�E�}�b�v�Ƀu���[��������֐��B
		*/
		void ExecuteBlur(CRenderContext& rc);

		/**
		 * @brief �V���h�E�}�b�v�̃����_�����O�^�[�Q�b�g���擾����֐��B
		 * @return  �V���h�E�}�b�v�̃����_�����O�^�[�Q�b�g
		*/
		CRenderTarget& GetRenderTarget() {

			return *m_shadowMap;
		}

		/**
		 * @brief �{�P�摜���擾����֐��B
		 * @return �{�P�摜
		*/
		Texture& GetBokeShadowTexture() {

			return m_shadowBlur.GetBokeTexture();
		}
	private:
		CRenderTarget* m_shadowMap = nullptr;			//�V���h�E�}�b�v
		nsPostEffect::CGaussianBlur m_shadowBlur;		//�V���h�E�}�b�v�ɂ�����u���[
	};
}
