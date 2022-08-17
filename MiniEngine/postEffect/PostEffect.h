#pragma once
#include "constPostEffect.h"
#include "Bloom.h"
#include "FXAA.h"

namespace nsMyGame {

	namespace nsPostEffect {

		//�|�X�g�G�t�F�N�g�N���X

		class CPostEffect
		{
		public:
			/**
			 * @brief �������֐��B
			*/
			void Init();

			/**
			 * @brief �`��֐��B
			 * @param rc �����_�[�R���e�L�X�g
			*/
			void Render(CRenderContext& rc);
		private:
			CBloom m_bloom;		//�u���[��
			CFXAA m_fxaa;		//FXAA
		};
	}
}

