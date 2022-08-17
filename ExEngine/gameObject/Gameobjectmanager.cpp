/*!
 *@brief	CGameObject�̃}�l�[�W��
 */
#include "stdafx.h"
#include "ExEngine.h"
#include "GameObjectManager.h"

CGameObjectManager* CGameObjectManager::m_instance = nullptr;

CGameObjectManager::CGameObjectManager()
{
	if (m_instance != nullptr) {
		//�C���X�^���X�����łɍ���Ă���B
		std::abort();
	}
	m_instance = this;
}
CGameObjectManager::~CGameObjectManager()
{
	m_instance = nullptr;
}
void CGameObjectManager::ExecuteUpdate()
{	
	//���S�t���O�����Ă���Q�[���I�u�W�F�N�g��j������B
	for (auto& goList : m_gameObjectListArray) {
		goList.remove_if([&](CIGameObject* go) {	
			if (go->IsDead()) {
				delete go;
				return true;
			}
			return false;	 
		});
	}

	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->StartWrapper();
		}
	}


	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->UpdateWrapper();
		}
	}
	//�����G���W���̃A�b�v�f�[�g���Ăяo���B
	CPhysicsWorld::GetInstance()->Update(1.0f / 60.0f);
}
void CGameObjectManager::ExecuteRender(CRenderContext& rc)
{
	//�����_���[��ύX����Ȃ炱�����������Ă����Ɨǂ��B
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}
}

void CGameObjectManager::ExecuteForwardRender(CRenderContext& rc)
{
	//�����_���[��ύX����Ȃ炱�����������Ă����Ɨǂ��B
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->ForwardRenderWrapper(rc);
		}
	}
}

void CGameObjectManager::Execute2DRender(CRenderContext& rc)
{
	//�����_���[��ύX����Ȃ炱�����������Ă����Ɨǂ��B
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->Render2DWrapper(rc);
		}
	}
}