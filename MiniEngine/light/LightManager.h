#pragma once
#include "constLight.h"

namespace nsMyGame {

	namespace nsLight {

		//���C�g�̃f�[�^
		struct LigData {
			DirectionLigData directionLigData[c_maxDirectionLightNum];		//�f�B���N�V�������C�g�̃f�[�^
			PointLigData pointLigData[c_maxPointLightNum];					//�|�C���g���C�g�̃f�[�^
			CVector3 eyePos = CVector3::Zero;								//���_�̍��W
			int pointLightNum = 0;											//�|�C���g���C�g�̑���
			CMatrix m_viewProj;												//�v���W�F�N�V�����s��
		};

		//���C�g�Ǘ��N���X
		class CLightManager
		{
		public:
			/**
			 * @brief ���C�g�}�l�[�W���[�̃C���X�^���X���쐬����֐��B
			*/
			static void CreateInstance() {

				m_lightManager = new CLightManager;
			}

			/**
			 * @brief ���C�g�}�l�[�W���[�̃C���X�^���X���擾����֐��B
			 * @return �C���X�^���X
			*/
			static CLightManager* GetInstance() {

				return m_lightManager;
			}

			/**
			 * @brief ���C�g��ǉ�����֐��B
			 * @param light ���C�g�̃C���X�^���X
			*/
			void AddLight(CLightBase* light);

			/**
			 * @brief ���C�g���폜����֐��B
			 * @param light ���C�g�̃C���X�^���X
			*/
			void RemoveLight(CLightBase* light);

			/**
			 * @brief �o�^����Ă��郉�C�g��S�č폜����֐��B
			*/
			void RemoveLightAll();
			/**
			 * @brief ���C�g�̃f�[�^���擾����֐��B
			 * @return ���C�g�̃f�[�^
			*/
			LigData* GetLigData() { return &m_ligData; }

			/**
			 * @brief �X�V�֐��B
			*/
			void Update();
		private:
			LigData m_ligData;									//���C�g�̃f�[�^
			static CLightManager* m_lightManager;				//���C�g�}�l�[�W���[�̃C���X�^���X
			std::list<DirectionLigData*> m_directionLights;		//�f�B���N�V�������C�g�̃f�[�^
			std::list<PointLigData*> m_pointLights;				//�|�C���g���C�g�̃f�[�^
		};
	}
}

