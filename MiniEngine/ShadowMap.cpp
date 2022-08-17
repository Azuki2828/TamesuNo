#include "stdafx.h"
#include "ShadowMap.h"

namespace nsMyGame{

	void CShadowMap::Init() {

		//�����_�����O�^�[�Q�b�g���쐬�B
		m_shadowMap = new CRenderTarget;

		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		m_shadowMap->Create(
			c_shadowMapWH.x,
			c_shadowMapWH.y,
			c_mipLevel1,
			c_renderArraySize1,
			DXGI_FORMAT_R32G32_FLOAT,	//VSM�̂��߁Ax,y�ɐ[�x�l�A�[�x�l�̂Q����������ށB
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);

		//�V���h�E�}�b�v�ɂ�����u���[���������B
		m_shadowBlur.Init(&m_shadowMap->GetRenderTargetTexture());
	}

	void CShadowMap::ExecuteBlur(CRenderContext& rc) {

		//�V���h�E�}�b�v�Ƀu���[��������B
		m_shadowBlur.ExecuteOnGPU(rc, 5.0f);
	}
}