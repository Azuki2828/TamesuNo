#include "stdafx.h"
#include "Model.h"
#include "Material.h"

void CModel::Init(const ModelInitData& initData)
{
	MY_ASSERT(
		initData.m_fxFilePath, 
		"error : initData.m_fxFilePath���w�肳��Ă��܂���B"
	);
	MY_ASSERT(
		initData.m_tkmFilePath,
		"error : initData.m_tkmFilePath���w�肳��Ă��܂���B"
	);
	//�����̃V�F�[�_�[�����[�h���鏈�������߂Ă���̂�
	//wchar_t�^�̕�����Ȃ̂ŁA�����ŕϊ����Ă����B
	wchar_t wfxFilePath[256] = {L""};
	if (initData.m_fxFilePath != nullptr) {
		//MessageBoxA(nullptr, "fx�t�@�C���p�X���w�肳��Ă��܂���B", "�G���[", MB_OK);
		//std::abort();
		mbstowcs(wfxFilePath, initData.m_fxFilePath, 256);
	}
	
	if (initData.m_skeleton != nullptr) {
		//�X�P���g�����w�肳��Ă���B
		m_meshParts.BindSkeleton(*initData.m_skeleton);
	}
	
	m_modelUpAxis = initData.m_modelUpAxis;

	auto tkmFile = g_engine->GetTkmFileFromBank(initData.m_tkmFilePath);
	if (tkmFile == nullptr) {
		//���o�^
		tkmFile = new CTkmFile;
		tkmFile->Load(initData.m_tkmFilePath);
		g_engine->RegistTkmFileToBank(initData.m_tkmFilePath, tkmFile);
	}

	m_tkmFile = tkmFile;

	m_meshParts.InitFromTkmFile(
		*m_tkmFile, 
		wfxFilePath, 
		initData.m_vsEntryPointFunc,
		initData.m_vsSkinEntryPointFunc,
		initData.m_psEntryPointFunc,
		initData.m_expandConstantBuffer,
		initData.m_expandConstantBufferSize,
		initData.m_expandShaderResoruceView
	);

	UpdateWorldMatrix(g_vec3Zero, g_quatIdentity, g_vec3One);
	
}

void CModel::UpdateWorldMatrix(CVector3 pos, CQuaternion rot, CVector3 scale)
{
	CMatrix mBias;
	if (m_modelUpAxis == enModelUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world = mBias * mScale * mRot * mTrans;
}

void CModel::ChangeAlbedoMap(const char* materialName, Texture& albedoMap)
{
	m_meshParts.QueryMeshs([&](const SMesh& mesh) {
		//todo �}�e���A������tkm�t�@�C���ɏo�͂����Ȃ������E�E�E�B
		//todo ���͑S�}�e���A�������ւ��܂�
		for (Material* material : mesh.m_materials) {
			material->GetAlbedoMap().InitFromD3DResource(albedoMap.Get());
		}
	});
	//�f�B�X�N���v�^�q�[�v�̍č쐬�B
	m_meshParts.CreateDescriptorHeaps();
	
}
void CModel::Draw(CRenderContext& rc)
{
	m_meshParts.Draw(
		rc, 
		m_world, 
		g_camera3D->GetViewMatrix(), 
		g_camera3D->GetProjectionMatrix()
	);
}

void CModel::Draw(CRenderContext& rc, CCamera& camera)
{
	m_meshParts.Draw(
		rc,
		m_world,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix()
	);
}
