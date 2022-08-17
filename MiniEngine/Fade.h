#pragma once

namespace nsMyGame {

	//�t�F�[�h�N���X
	class CFade : public CIGameObject
	{
	public:
		/**
		 * @brief Update()�֐��̑O�Ɉ�x�����Ă΂��֐��B
		 * @return ���������H
		*/
		bool Start() override final;

		/**
		 * @brief �X�V�֐��B
		*/
		void Update() override final;

		/**
		 * @brief �t�F�[�h�C�����n�߂�֐��B
		*/
		void StartFadeIn()
		{
			m_state = enState_FadeIn;
		}

		/**
		 * @brief �t�F�[�h�A�E�g���n�߂�֐��B
		*/
		void StartFadeOut()
		{
			m_state = enState_FadeOut;
		}

		/**
		 * @brief �t�F�[�h���H
		 * @return �t�F�[�h�����ǂ����̔��茋��
		*/
		bool IsFade() const
		{
			return m_state != enState_Idle;
		}

		/**
		 * @brief �t�F�[�h�摜�̓����x���擾����֐��B
		 * @return �t�F�[�h�摜�̓����x
		*/
		float GetCurrentAlpha() const
		{
			return m_currentAlpha;
		}

	private:
		//�t�F�[�h�̃X�e�[�g
		enum EnState {
			enState_FadeIn,		//�t�F�[�h�C����
			enState_FadeOut,	//�t�F�[�h�A�E�g��
			enState_Idle,		//�A�C�h����
		};
		CSpriteRender* m_fadeSprite = nullptr;	//�t�F�[�h�̃X�v���C�g
		EnState m_state = enState_Idle;			//���
		float m_currentAlpha = 1.0f;			//���݂̓����x
	};
}

