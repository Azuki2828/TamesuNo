#include "stdafx.h"
#include "LightCulling.h"

namespace nsMyGame {

	void CLightCulling::Init() {

		// ���[�g�V�O�l�`���̏������B
		m_rootSignature.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP
		);

		//���C�g�J�����O�p�̃R���s���[�g�V�F�[�_�[�����[�h�B
		m_csLightCulling.LoadCS(L"Assets/shader/lightCulling.fx", "CSMain");

		//�p�C�v���C���X�e�[�g���������B
		InitPipelineState(m_rootSignature, m_lightCullingPipelineState, m_csLightCulling);

		//�^�C�����Ƃ̃|�C���g���C�g�̔ԍ��̃��X�g���o�͂���UAV���������B
		m_pointLightNoListInTileUAV.Init(
			sizeof(int),
			nsLight::c_maxPointLightNum * nsLight::c_tileNum,
			nullptr
		);

		//�|�C���g���C�g�̏��𑗂邽�߂̒萔�o�b�t�@���쐬�B
		UpdateLightCullingCameraData();
		m_cameraParamCB.Init(sizeof(m_lightCullingCameraData), &m_lightCullingCameraData);
		m_lightCB.Init(sizeof(*nsLight::CLightManager::GetInstance()->GetLigData()), nsLight::CLightManager::GetInstance()->GetLigData());

		//���C�g�J�����O�p�̃f�B�X�N���v�^�q�[�v���������B
		InitLightCullingDescriptorHeap();
	}

	void CLightCulling::Execute(CRenderContext& rc) {

		//�J�����̏����X�V�B
		UpdateLightCullingCameraData();
		
		//���C�g�J�����O�̃R���s���[�g�V�F�[�_�[���f�B�X�p�b�`
		rc.SetComputeRootSignature(m_rootSignature);
		auto ligData = *nsLight::CLightManager::GetInstance()->GetLigData();
		m_lightCB.CopyToVRAM(*nsLight::CLightManager::GetInstance()->GetLigData());
		rc.SetComputeDescriptorHeap(m_lightCullingDescriptorHeap);
		rc.SetPipelineState(m_lightCullingPipelineState);

		rc.Dispatch(
			c_frameBufferWidth / c_tileWidth,
			c_frameBufferHeight / c_tileHeight,
			1
		);

		// ���\�[�X�o���A
		rc.TransitionResourceState(
			m_pointLightNoListInTileUAV.GetD3DResoruce(),
			D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	}

	void CLightCulling::InitPipelineState(RootSignature& rs, PipelineState& pipelineState, Shader& cs)
	{
		// �p�C�v���C���X�e�[�g���쐬�B
		D3D12_COMPUTE_PIPELINE_STATE_DESC  psoDesc = { 0 };
		psoDesc.pRootSignature = rs.Get();
		psoDesc.CS = CD3DX12_SHADER_BYTECODE(cs.GetCompiledBlob());
		psoDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
		psoDesc.NodeMask = 0;

		pipelineState.Init(psoDesc);
	}

	void CLightCulling::UpdateLightCullingCameraData() {

		//�J�����̏����������B
		m_lightCullingCameraData.mProj = g_camera3D->GetProjectionMatrix();
		m_lightCullingCameraData.mProjInv.Inverse(g_camera3D->GetProjectionMatrix());
		m_lightCullingCameraData.mCameraRot = g_camera3D->GetCameraRotation();
		m_lightCullingCameraData.screenParam.x = g_camera3D->GetNear();
		m_lightCullingCameraData.screenParam.y = g_camera3D->GetFar();
		m_lightCullingCameraData.screenParam.z = c_frameBufferWidth;
		m_lightCullingCameraData.screenParam.w = c_frameBufferHeight;

		m_cameraParamCB.CopyToVRAM(&m_lightCullingCameraData);
	}

	void CLightCulling::InitLightCullingDescriptorHeap() {

		//�e�����f�B�X�N���v�^�q�[�v�ɓo�^�B
		m_lightCullingDescriptorHeap.RegistShaderResource(
			0,																	//t0
			CRenderTarget::GetGBufferRT(enDepthMap)->GetRenderTargetTexture()	//�[�x�l�e�N�X�`��
		);
		m_lightCullingDescriptorHeap.RegistUnorderAccessResource(
			0,																	//u0
			m_pointLightNoListInTileUAV											//�^�C�����Ƃ̃|�C���g���C�g�̔ԍ��̃��X�g���o�͂���UAV
		);
		m_lightCullingDescriptorHeap.RegistConstantBuffer(
			0,																	//b0
			m_cameraParamCB														//�J�����̏��
		);
		m_lightCullingDescriptorHeap.RegistConstantBuffer(
			1,																	//b1
			m_lightCB															//���C�g�̏��
		);

		//�o�^�B
		m_lightCullingDescriptorHeap.Commit();
	}
}