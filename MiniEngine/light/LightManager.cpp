#include "stdafx.h"
#include "LightManager.h"

namespace nsMyGame {

	namespace nsLight {

		CLightManager* CLightManager::m_lightManager = nullptr;

		void CLightManager::AddLight(CLightBase* light) {

			//�N���X�̖��O�𒲂ׂ�
			const std::type_info& typeInfo = typeid(*light);

			//�f�B���N�V�������C�g��������
			if (typeInfo == typeid(CDirectionLight)) {

				//�����K�肳��Ă��鐔�ɒB���Ă�����u���Ȃ�
				if (m_directionLights.size() >= c_maxDirectionLightNum) {
					MessageBoxA(nullptr, "����ȏ�f�B���N�V�������C�g�͒u���܂���", "�G���[", MB_OK);
					return;
				}

				//�o�^�ς݂����ׂ�B
				auto findIt = std::find(m_directionLights.begin(), m_directionLights.end(), light->GetLigData());
				if (findIt == m_directionLights.end()) {
					//�V�K�o�^�B
					m_directionLights.push_back(reinterpret_cast<DirectionLigData*>(light->GetLigData()));

					int a = 0;
					std::list<DirectionLigData*>::iterator itr;
					itr = m_directionLights.begin();

					//for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
					//	m_ligData.m_directionLigData[i] = nullptr;
					//}
					for (auto itr = m_directionLights.begin(); itr != m_directionLights.end(); ++itr) {

						m_ligData.directionLigData[a] = *(*itr);
						a++;
					}
				}
				else {
					//���ɓo�^����Ă���B
					MessageBoxA(nullptr, "���ɓo�^����Ă��܂�", "�G���[", MB_OK);
					return;
				}
			}
			//�|�C���g���C�g��������
			else if (typeInfo == typeid(CPointLight)) {

				//�����K�肳��Ă��鐔�ɒB���Ă�����u���Ȃ�
				if (m_pointLights.size() >= c_maxPointLightNum) {
					MessageBoxA(nullptr, "����ȏ�f�B���N�V�������C�g�͒u���܂���", "�G���[", MB_OK);
					return;
				}

				//�o�^�ς݂����ׂ�B
				auto findIt = std::find(m_pointLights.begin(), m_pointLights.end(), light->GetLigData());
				if (findIt == m_pointLights.end()) {
					//�V�K�o�^�B
					m_pointLights.push_back(reinterpret_cast<PointLigData*>(light->GetLigData()));

					int a = 0;
					std::list<PointLigData*>::iterator itr;
					itr = m_pointLights.begin();

					for (auto itr = m_pointLights.begin(); itr != m_pointLights.end(); ++itr) {

						m_ligData.pointLigData[a] = *(*itr);
						a++;
					}
					m_ligData.pointLightNum++;
				}
				else {
					//���ɓo�^����Ă���B
					MessageBoxA(nullptr, "���ɓo�^����Ă��܂�", "�G���[", MB_OK);
					return;
				}
			}
		}

		void CLightManager::RemoveLight(CLightBase* light)
		{
			//�N���X�̖��O�𒲂ׂ�
			const std::type_info& typeInfo = typeid(*light);

			//�f�B���N�V�������C�g��������
			if (typeInfo == typeid(CDirectionLight)) {

				//���C�g���폜
				m_directionLights.erase(
					std::remove(m_directionLights.begin(), m_directionLights.end(), light->GetLigData()),
					m_directionLights.end()
				);

				int a = 0;

				//for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
				//	m_ligData.m_directionLigData[i] = nullptr;
				//}

				for (auto itr = m_directionLights.begin(); itr != m_directionLights.end(); ++itr) {

					m_ligData.directionLigData[a] = *(*itr);
					a++;
				}
			}
			//�|�C���g���C�g��������
			else if (typeInfo == typeid(CPointLight)) {

				//���C�g���폜
				m_pointLights.erase(
					std::remove(m_pointLights.begin(), m_pointLights.end(), light->GetLigData()),
					m_pointLights.end()
				);

				int a = 0;

				for (auto itr = m_pointLights.begin(); itr != m_pointLights.end(); ++itr) {

					m_ligData.pointLigData[a] = *(*itr);
					a++;
				}
				m_ligData.pointLightNum--;
			}
		}
		void CLightManager::RemoveLightAll()
		{
			//���C�g�����ׂč폜����B
			m_directionLights.clear();
			m_pointLights.clear();
		}
		void CLightManager::Update() {

			//�J�����̍��W���X�V
			m_lightManager->m_ligData.eyePos = g_camera3D->GetPosition();
			//���C�g�J��������v���W�F�N�V�����s����擾�B
			m_lightManager->m_ligData.m_viewProj = CCamera::GetLightCamera()->GetViewProjectionMatrix();

			int a = 0;
			for (auto itr = m_directionLights.begin(); itr != m_directionLights.end(); ++itr) {

				m_ligData.directionLigData[a] = *(*itr);
				a++;
			}

			CMatrix mView = g_camera3D->GetViewMatrix();
			a = 0;
			for (auto itr = m_pointLights.begin(); itr != m_pointLights.end(); itr++) {
			
				m_ligData.pointLigData[a] = *(*itr);
				m_ligData.pointLigData[a].positionInView = m_ligData.pointLigData[a].pos;
				mView.Apply(m_ligData.pointLigData[a].positionInView);
				a++;
			}
		}
	}
}