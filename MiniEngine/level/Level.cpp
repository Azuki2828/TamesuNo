#include "stdafx.h"
#include "Level.h"

namespace nsMyGame {


	void Level::Init(
		const char* filePath,
		std::function<bool(LevelObjectData& objData)> hookFunc
	)
	{
		//�X�P���g�������[�h����B
		//Skeleton skeleton;
		m_tklFile.Load(filePath);

		for (auto i = 1; i < m_tklFile.GetBoneNum(); i++) {
			auto bone = m_tklFile.GetBonePtr(i);

			if (bone->GetParentBoneNo() == 0) {
				LevelObjectData objData;
				CVector3 scale;
				bone->CalcWorldTRS(objData.position, objData.rotation, objData.scale);

				//3dsMax�Ƃ͎����Ⴄ�̂ŁA�␳������B
				auto t = objData.position.y;
				objData.position.y = objData.position.z;
				objData.position.z = t;



				t = objData.rotation.y;
				objData.rotation.y = -objData.rotation.z;
				objData.rotation.z = -t;
				objData.rotation.x *= -1.0f;


				objData.name = bone->GetName();

				std::swap(objData.scale.y, objData.scale.z);


				auto isHook = false;
				if (hookFunc != nullptr) {

					//hook�֐����w�肳��Ă���̂�hook�֐����Ăяo���B
					isHook = hookFunc(objData);
				}
				if (isHook == false) {
					//�}�b�v�`�b�v�����_���[���쐬����B

					m_mapChipPtrs.push_back(std::make_unique<MapChip>(objData));
				}
			}
		}


		////�\�z�\�z�B
		////0�Ԗڂ̓��[�g�I�u�W�F�N�g�Ȃ̂Ŕ�΂��B
		//for (auto i = 1; i < skeleton.GetNumBones(); i++) {
		//	//�����擾�B
		//	auto bone = skeleton.GetBone(i);
		//	if (bone->GetParentBoneNo() == 0) {	//�e�����[�g�̏ꍇ�����}�b�v�`�b�v�𐶐�����B
		//		LevelObjectData objData;
		//		Vector3 scale;
		//		bone->CalcWorldTRS(objData.position, objData.rotation, objData.scale);
		//		//3dsMax�Ƃ͎����Ⴄ�̂ŁA�␳������B
		//		auto t = objData.position.y;
		//		objData.position.y = objData.position.z;
		//		objData.position.z = -t;
		//
		//		t = objData.rotation.y;
		//		objData.rotation.y = objData.rotation.z;
		//		objData.rotation.z = -t;
		//		objData.name = bone->GetName();
		//
		//		std::swap(objData.scale.y, objData.scale.z);
		//
		//		auto isHook = false;
		//		if (hookFunc != nullptr) {
		//			//hook�֐����w�肳��Ă���̂�hook�֐����Ăяo���B
		//			isHook = hookFunc(objData);
		//		}
		//		if (isHook == false) {
		//			//�}�b�v�`�b�v�����_���[���쐬����B
		//
		//			m_mapChipPtrs.push_back(std::make_unique<MapChip>(objData));
		//			
		//		}
		//	}
		//}
	}

	void Level::Draw(CRenderContext& rc) {

		for (int i = 0; i < m_mapChipPtrs.size(); i++) {
			m_mapChipPtrs[i]->Draw(rc);
		}
	}
}
