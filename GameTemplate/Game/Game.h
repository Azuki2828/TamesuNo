#pragma once

namespace nsMyGame {

	class CTitle;
	class CMainCamera;
	class CButton;

	//�Q�[���N���X
	class CGame: public CIGameObject
	{
	private:

		//�{�^���̎��
		enum EnButton {
			enButton_Red,		//�ԃ{�^��
			enButton_Blue,		//�{�^��
			enButton_Yellow,	//���{�^��
			enButton_Green,		//�΃{�^��

			enButton_Num
		};
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

		/**
		 * @brief �{�^����tkm�t�@�C���̃t�@�C���p�X���擾����֐��B
		 * @param buttonNum �{�^���ԍ�
		 * @return �{�^����tkm�t�@�C���̃t�@�C���p�X
		*/
		const char* GetTkmFilePath(const int buttonNum);
	private:

		CButton* m_button[enButton_Num] = { nullptr };	//�{�^���N���X
		CTitle* m_title = nullptr;						//�^�C�g���N���X
		CMainCamera* m_mainCamera = nullptr;		//���C���J����
		nsLight::CDirectionLight* m_directionLight = nullptr;	//�f�B���N�V�������C�g
	};
}

