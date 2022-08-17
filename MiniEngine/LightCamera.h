#pragma once
#include "stdafx.h"

class LightCamera : CCamera
{
	//���C�g�J�����̃C���X�^���X���쐬����֐��B
	static void CreateLightCamera() {

		m_lightCamera = new LightCamera;
	}
	//���C�g�J�����̃C���X�^���X���擾����֐��B
	static LightCamera* GetLightCamera() {

		return m_lightCamera;
	}
private:
	static LightCamera* m_lightCamera;		//���C�g�J�����̃C���X�^���X
	CVector3 m_pos = CVector3::Zero;			//���W
	CVector3 m_tar = CVector3::One;			//�^�[�Q�b�g
};

