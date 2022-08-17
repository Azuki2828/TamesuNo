#pragma once

namespace nsMyGame {

	//�{�^���N���X
	class CButton : public CIGameObject
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

	public:
		/**
		 * @brief �������֐��B
		*/
		void Init(const char* filePathTkm);

		/**
		 * @brief ���W��ݒ肷��֐��B
		 * @param position ���W
		*/
		void SetPosition(const CVector3& position) {

			m_position = position;
		}

		/**
		 * @brief �g�嗦��ݒ肷��֐��B
		 * @param scale �g�嗦
		*/
		void SetScale(const CVector3& scale) {

			m_modelRender->SetScale(scale);
		}
	private:
		CModelRender* m_modelRender = nullptr;		//���f�������_�[
		CVector3 m_position = CVector3::Zero;		//���W
	};
}

