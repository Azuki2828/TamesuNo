/*!
*@brief	�X�P���g��
*/
#include "stdafx.h"
#include "Skeleton.h"
#include <comdef.h> 


void Bone::CalcWorldTRS(CVector3& trans, CQuaternion& rot, CVector3& scale)
{
	CMatrix mWorld = m_worldMatrix;
	//�s�񂩂�g�嗦���擾����B
	scale.x = mWorld.v[0].Length();
	scale.y = mWorld.v[1].Length();
	scale.z = mWorld.v[2].Length();
	m_scale = scale;
	//�s�񂩂畽�s�ړ��ʂ��擾����B
	trans.Set(mWorld.v[3]);
	m_positoin = trans;
	//�s�񂩂�g�嗦�ƕ��s�ړ��ʂ��������ĉ�]�ʂ��擾����B
	mWorld.v[0].Normalize();
	mWorld.v[1].Normalize();
	mWorld.v[2].Normalize();
	mWorld.v[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
	rot.SetRotation(mWorld);
	m_rotation = rot;
}
Skeleton::Skeleton()
{
	//���U�[�u�B
	m_bones.reserve(BONE_MAX);
}
Skeleton::~Skeleton()
{
}
void Skeleton::UpdateBoneWorldMatrix(Bone& bone, const CMatrix& parentMatrix)
{
	CMatrix mBoneWorld;
	CMatrix localMatrix = bone.GetLocalMatrix();
	mBoneWorld = localMatrix * parentMatrix;
	
	bone.SetWorldMatrix(mBoneWorld);
	for (auto childBone : bone.GetChildren()) {
		UpdateBoneWorldMatrix(*childBone, mBoneWorld);
	}
}
bool Skeleton::Init(const char* tksFilePath)
{
	//tks�t�@�C�������[�h����B
	m_tksFile.Load(tksFilePath);
	//�{�[���s����\�z����B
	BuildBoneMatrices();
	return true;
}
void Skeleton::CopyBoneMatrix(
	Skeleton& upperBody,
	Skeleton& lowerBody,
	const char* upperBodyBoneNameArray[],
	const char* lowerBodyBoneNameArray[],
	int upperBodyBoneNameArraySize,
	int lowerBodyBoneNameArraySize
)
{
	//�{�[���̐�����for���ŉ񂵂ăR�s�[����B
	for (int boneNum = 0; boneNum < m_bones.size(); boneNum++) {

		//�{�[���̖��O���擾����B
		const wchar_t* carentBoneName = m_bones[boneNum].get()->GetName();

		//�{�[���̖��O��const wchat_t����char�ɕϊ��B
		char carentBoneNameChar[c_nameSize];
		wcstombs(carentBoneNameChar, carentBoneName, c_nameSize);

		//�{�[�������������H
		bool findBone = false;

		//������̐������J��Ԃ��B
		for (int arrayNum = 0; arrayNum < upperBodyBoneNameArraySize; arrayNum++) {

			//��������r�B
			if (
				strcmp(
					static_cast<const char*>(carentBoneNameChar),
					upperBodyBoneNameArray[arrayNum]
				) == 0) {
				m_bones[boneNum]->SetLocalMatrix(upperBody.m_bones[boneNum]->GetLocalMatrix());
				// todo m_bones[boneNum].get()->SetLocalMatrix(upperBody.GetBone(boneNum)->GetLocalMatrix());
				findBone = true;
			}
		}

		for (int arrayNum = 0; arrayNum < lowerBodyBoneNameArraySize; arrayNum++) {

			//��������r�B
			if (
				strcmp(
					static_cast<const char*>(carentBoneNameChar),
					lowerBodyBoneNameArray[arrayNum]
				) == 0) {
				m_bones[boneNum]->SetLocalMatrix(lowerBody.m_bones[boneNum]->GetLocalMatrix());
				//todo m_bones[boneNum].get()->SetLocalMatrix(lowerBody.GetBone(boneNum)->GetLocalMatrix());
				findBone = true;
			}
		}

		//�{�[����������Ȃ������B
		if (!findBone) {

			m_boneMatrixs[boneNum] = upperBody.m_boneMatrixs[boneNum];
		}
	}
}
void Skeleton::BuildBoneMatrices()
{
	m_tksFile.QueryBone([&](CTksFile::SBone & tksBone) {
		//�o�C���h�|�[�Y�B
		CMatrix bindPoseMatrix;
		memcpy(bindPoseMatrix.m[0], &tksBone.bindPose[0], sizeof(tksBone.bindPose[0]));
		memcpy(bindPoseMatrix.m[1], &tksBone.bindPose[1], sizeof(tksBone.bindPose[1]));
		memcpy(bindPoseMatrix.m[2], &tksBone.bindPose[2], sizeof(tksBone.bindPose[2]));
		memcpy(bindPoseMatrix.m[3], &tksBone.bindPose[3], sizeof(tksBone.bindPose[3]));
		bindPoseMatrix.m[0][3] = 0.0f;
		bindPoseMatrix.m[1][3] = 0.0f;
		bindPoseMatrix.m[2][3] = 0.0f;
		bindPoseMatrix.m[3][3] = 1.0f;

		//�o�C���h�|�[�Y�̋t�s��B
		CMatrix invBindPoseMatrix;
		memcpy(invBindPoseMatrix.m[0], &tksBone.invBindPose[0], sizeof(tksBone.invBindPose[0]));
		memcpy(invBindPoseMatrix.m[1], &tksBone.invBindPose[1], sizeof(tksBone.invBindPose[1]));
		memcpy(invBindPoseMatrix.m[2], &tksBone.invBindPose[2], sizeof(tksBone.invBindPose[2]));
		memcpy(invBindPoseMatrix.m[3], &tksBone.invBindPose[3], sizeof(tksBone.invBindPose[3]));
		invBindPoseMatrix.m[0][3] = 0.0f;
		invBindPoseMatrix.m[1][3] = 0.0f;
		invBindPoseMatrix.m[2][3] = 0.0f;
		invBindPoseMatrix.m[3][3] = 1.0f;

		wchar_t boneName[256];
		mbstowcs(boneName, tksBone.name.get(), 256);
		BonePtr bone = std::make_unique<Bone>(
			boneName,
			bindPoseMatrix,
			invBindPoseMatrix,
			tksBone.parentNo,
			tksBone.no
			);
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		//�{�[���̃o���f�[�V�����`�F�b�N�B
		//maxScript�ł�肽���Ƃ���ł͂��邪�A�Ƃ肠�����������B
		auto it = std::find_if(m_bones.begin(), m_bones.end(), [&](auto & bone) {return wcscmp(boneName, bone->GetName()) == 0;  });
		if (it != m_bones.end()) {
			//�����̃{�[�������������B
			_bstr_t b(boneName);
			const char* c = b;
			TK_WARNING("�����̃{�[����������܂����B����̓���ł��B�f�[�^���C�����Ă��������B%s", c);
		}
#endif
		m_bones.push_back(std::move(bone));
		});
	for (auto& bone : m_bones) {
		if (bone->GetParentBoneNo() != -1) {
			m_bones.at(bone->GetParentBoneNo())->AddChild(bone.get());
			//���[�J���}�g���N�X���v�Z�B
			const CMatrix& parentMatrix = m_bones.at(bone->GetParentBoneNo())->GetInvBindPoseMatrix();
			CMatrix localMatrix;
			localMatrix = bone->GetBindPoseMatrix() * parentMatrix;
			bone->SetLocalMatrix(localMatrix);
		}
		else {
			bone->SetLocalMatrix(bone->GetBindPoseMatrix());
		}
	}


	//�{�[���s����m��
	m_boneMatrixs = std::make_unique<CMatrix[]>(m_bones.size());
	m_isInited = true;

}

void Skeleton::Update(const CMatrix& mWorld)
{
	
	//�A�j���[�V�������������܂�Ă���ƁA�{�[���s�񂪃��[�g�{�[����Ԃ�
	//�ϊ�����Ă��邪�A������Ă��Ȃ��Ɛe�̍��̍��W�n�̂܂܂Ȃ̂ŁA
	//���[�g�{�[����ԁ����[���h��Ԃւ̕ϊ����s���B
	for (auto& bone : m_bones) {
		if (bone->GetParentBoneNo() != -1) {
			continue;
		}
		//���[�g�B
		UpdateBoneWorldMatrix(*bone, mWorld);
	}

	//�{�[���s����v�Z�B
	int boneNo = 0;
	for (auto& bonePtr : m_bones) {
		CMatrix mBone;
		mBone = bonePtr->GetInvBindPoseMatrix() * bonePtr->GetWorldMatrix();
		m_boneMatrixs[boneNo] = mBone;
		boneNo++;
	}	
}

void Skeleton::UpdateHasVerUniqueAnimation(const CMatrix& mWorld){

	//�{�[���s������[�g�{�[���̋�Ԃ��烏�[���h��Ԃ��\�z���Ă����B
	for (auto& bone : m_bones) {
		CMatrix mBoneWorld;
		CMatrix localMatrix = bone->GetLocalMatrix();
		//�e�̍s��ƃ��[�J���s�����Z���āA���[���h�s����v�Z����B
		mBoneWorld = localMatrix * mWorld;
		bone->SetWorldMatrix(mBoneWorld);
	}
}
