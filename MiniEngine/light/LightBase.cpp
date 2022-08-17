#include "stdafx.h"
#include "LightBase.h"

namespace nsMyGame {

	namespace nsLight {

		bool CLightBase::Start() {

			//���C�g�}�l�[�W���[�Ƀ��C�g��ǉ�����B
			CLightManager::GetInstance()->AddLight(this);
			return StartSub();
		}

		void CLightBase::OnDestroy() {

			//���C�g�}�l�[�W���[���烉�C�g���폜����B
			CLightManager::GetInstance()->RemoveLight(this);
		}
	}
}
