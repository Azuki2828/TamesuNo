#pragma once

namespace nsMyGame {

	//�^�C�g���N���X
	class CTitle : public CIGameObject
	{
	private:
		/**
		 * @brief �ŏ��Ɉ�x�����Ă΂��֐��B
		 * @return ���������H
		*/
		bool Start()override final;

		/**
		 * @brief �폜�֐��B
		*/
		void OnDestroy()override final;

		/**
		 * @brief �X�V�֐��B
		*/
		void Update()override final;

	private:
		CSpriteRender* m_backSprite = nullptr;		//�w�i�摜
		
	};
}

