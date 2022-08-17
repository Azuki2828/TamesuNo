#pragma once
#include "../../MiniEngine/SpringCamera.h"

namespace nsMyGame {

	//���C���J�����N���X
	class CMainCamera : public CIGameObject
	{
	private:
		/**
		 * @brief �ŏ��Ɉ�x�����Ă΂��֐��B
		 * @return ���������H
		*/
		bool Start()override final;

		/**
		 * @brief �X�V�֐��B
		*/
		void Update()override final;

		/**
		 * @brief �������֐��B
		*/
		void Init();
	private:
		SpringCamera m_springCamera;			//�΂˃J����
		CVector3 m_position = CVector3::Zero;	//���_
		CVector3 m_target = CVector3::Zero;		//�����_
	};
}

