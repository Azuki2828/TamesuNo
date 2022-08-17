#include "stdafx.h"
#include "ModelRender.h"

namespace nsMyGame {

	void CModelRender::Init() {

		//tkm�t�@�C����tks�t�@�C���̃p�X��ݒ�B
		SetFilePathTkmAndTks();

		//���_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
		m_modelInitData.m_vsEntryPointFunc = c_entryPointVSMain;
		m_modelInitData.m_vsSkinEntryPointFunc = c_entryPointVSSkinMain;

		//fx�t�@�C���p�X���w��B
		m_modelInitData.m_fxFilePath = c_fxFilePath_Model;

		//�R���X�^���g�o�b�t�@�Ƀ��f���f�[�^������B
		m_modelInitData.m_expandConstantBuffer = &m_modelData;
		m_modelInitData.m_expandConstantBufferSize = sizeof(m_modelData);

		//���W�X�^��t10�ɃV���h�E�}�b�v��ݒ�B
		m_modelInitData.m_expandShaderResoruceView = &CRenderingEngine::GetInstance()->GetShadowMap().GetRenderTargetTexture();

		//�X�P���g����ݒ�B
		if (m_skeleton.IsInited()) {
			m_modelInitData.m_skeleton = &m_skeleton;
		}

		//�V���h�E�L���X�^�[�t���O��true�Ȃ�V���h�E���f�����쐬����B
		if (m_shadowCasterFlag) { CreateShadowModel(); }

		//���f���f�[�^�����Ƀ��f�����������B
		m_model.Init(m_modelInitData);

		//�A�j���[�V�������������B
		m_animation.Init(m_skeleton, m_animationClip, m_animNum);
	}

	void CModelRender::Init(ModelInitData& modelInitData) {

		//tkm�t�@�C���̃��[�h�B
		if (modelInitData.m_tkmFilePath == nullptr) {

			//���[�h�G���[�B
			MessageBox(nullptr, L"tkm�t�@�C�����ǂݍ��܂�Ă��܂���B", L"�x��", MB_OK);
		}

		//tks�t�@�C���̃��[�h�B
		if (modelInitData.m_tksFilePath != nullptr) {
			m_skeleton.Init(modelInitData.m_tksFilePath);
		}

		//�X�P���g����ݒ�B
		if (m_skeleton.IsInited()) {
			m_modelInitData.m_skeleton = &m_skeleton;
		}

		//�V���h�E�L���X�^�[�t���O��true�Ȃ�V���h�E���f�����쐬����B
		if (m_shadowCasterFlag) { CreateShadowModel(); }

		//���f���f�[�^�����Ƀ��f�����������B
		m_model.Init(modelInitData);

		//�A�j���[�V�������������B
		m_animation.Init(m_skeleton, m_animationClip, m_animNum);
	}

	void CModelRender::InitForwardRenderingModel() {

		//tkm�t�@�C����tks�t�@�C���̃p�X��ݒ�B
		SetFilePathTkmAndTks();

		//���_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
		m_modelInitData.m_vsEntryPointFunc = c_entryPointVSMain;
		m_modelInitData.m_vsSkinEntryPointFunc = c_entryPointVSSkinMain;

		//fx�t�@�C���p�X���w��B
		m_modelInitData.m_fxFilePath = m_filePathFx;

		//�R���X�^���g�o�b�t�@�Ƀ��f���f�[�^������B
		m_modelInitData.m_expandConstantBuffer = &m_modelData;
		m_modelInitData.m_expandConstantBufferSize = sizeof(m_modelData);

		//���W�X�^��t10�ɃV���h�E�}�b�v��ݒ�B
		m_modelInitData.m_expandShaderResoruceView = &CRenderingEngine::GetInstance()->GetShadowMap().GetRenderTargetTexture();

		//�X�P���g����ݒ�B
		if (m_skeleton.IsInited()) {
			m_modelInitData.m_skeleton = &m_skeleton;
		}

		//�V���h�E�L���X�^�[�t���O��true�Ȃ�V���h�E���f�����쐬����B
		if (m_shadowCasterFlag) { CreateShadowModel(); }

		//���f���f�[�^�����Ƀ��f�����������B
		m_forwardRenderModel.Init(m_modelInitData);

		//�A�j���[�V�������������B
		m_animation.Init(m_skeleton, m_animationClip, m_animNum);
	}

	void CModelRender::InitForwardRenderingModel(ModelInitData& modelInitData) {

		//tkm�t�@�C���̃��[�h�B
		if (modelInitData.m_tkmFilePath == nullptr) {

			//���[�h�G���[�B
			MessageBox(nullptr, L"tkm�t�@�C�����ǂݍ��܂�Ă��܂���B", L"�x��", MB_OK);
		}

		//tks�t�@�C���̃��[�h�B
		if (modelInitData.m_tksFilePath != nullptr) {
			m_skeleton.Init(modelInitData.m_tksFilePath);
		}

		//�X�P���g����ݒ�B
		if (m_skeleton.IsInited()) {
			modelInitData.m_skeleton = &m_skeleton;
		}

		//�V���h�E�L���X�^�[�t���O��true�Ȃ�V���h�E���f�����쐬����B
		if (m_shadowCasterFlag) { CreateShadowModel(); }

		//���f���f�[�^�����Ƀ��f�����������B
		m_forwardRenderModel.Init(modelInitData);

		//�A�j���[�V�������������B
		m_animation.Init(m_skeleton, m_animationClip, m_animNum);
	}

	void CModelRender::CreateShadowModel() {

		//�V���h�E���f���̃f�[�^���������B
		ModelInitData ShadowModelInitData;
		ShadowModelInitData.m_fxFilePath = c_fxFilePath_ShadowMap;
		ShadowModelInitData.m_tkmFilePath = m_filePathTkm;
		ShadowModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32_FLOAT;
		ShadowModelInitData.m_vsEntryPointFunc = c_entryPointVSMain;
		ShadowModelInitData.m_vsSkinEntryPointFunc = c_entryPointVSSkinMain;

		//�X�P���g����ݒ�B
		if (m_skeleton.IsInited()) {
			ShadowModelInitData.m_skeleton = &m_skeleton;
		}
		//�V���h�E���f�����������B
		m_shadowModel.Init(ShadowModelInitData);

		//�V���h�E���f���̍��W�A��]���A�g�嗦���X�V�B
		m_shadowModel.UpdateWorldMatrix(
			m_pos,
			m_rot,
			m_sca
		);
	}

	void CModelRender::SetFilePathTkmAndTks() {

		//tkm�t�@�C���̃��[�h�B
		if (m_filePathTkm != nullptr) {
			m_modelInitData.m_tkmFilePath = m_filePathTkm;
		}
		else {
			//���[�h�G���[�B
			MessageBox(nullptr, L"tkm�t�@�C�����ǂݍ��܂�Ă��܂���B", L"�x��", MB_OK);
		}

		//tks�t�@�C���̃��[�h�B
		if (m_filePathTks != nullptr) {
			m_skeleton.Init(m_filePathTks);
		}
	}

	void CModelRender::Update() {

		//�X�P���g�����X�V�B
		if (!m_hasUniqueAnimation) {
			m_skeleton.Update(m_model.GetWorldMatrix());
		}
		else {
			m_skeleton.SetMarkPlayAnimation();
			m_skeleton.UpdateHasVerUniqueAnimation(m_model.GetWorldMatrix());
		}

		//�A�j���[�V������i�߂�B
		if (m_animFlg) {
			m_animation.Progress(m_animationSpeed / 30.0f);
		}

		//���f���̍��W�A��]���A�g�嗦���X�V�B
		m_model.UpdateWorldMatrix(
			m_pos,
			m_rot,
			m_sca
		);

		//���f���̍��W�A��]���A�g�嗦���X�V�B
		m_forwardRenderModel.UpdateWorldMatrix(
			m_pos,
			m_rot,
			m_sca
		);

		//�V���h�E���f���̍��W�A��]���A�g�嗦���X�V�B
		m_shadowModel.UpdateWorldMatrix(
			m_pos,
			m_rot,
			m_sca
		);
	}

	void CModelRender::Render(CRenderContext& rc) {

		//�`�惂�[�h�ɉ����ĕ`�悷�郂�f����ς���B
		switch (rc.GetRenderMode()) {
		case CRenderContext::EnRender_Mode::enRenderMode_Normal:
			//���f����`��B
			if (!IsCollisionModel()) {
				m_model.Draw(rc);
			}
			break;
		case CRenderContext::EnRender_Mode::enRenderMode_Shadow:
			//�V���h�E���f����`��B
			m_shadowModel.Draw(rc, *CCamera::GetLightCamera());
			break;
		}
	}

	void CModelRender::ForwardRender(CRenderContext& rc) {

		//���f����`��B
		if (!IsCollisionModel()) {
			m_forwardRenderModel.Draw(rc);
		}
	}
}
