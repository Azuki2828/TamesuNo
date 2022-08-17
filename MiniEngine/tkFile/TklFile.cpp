#include "stdafx.h"
#include "TklFile.h"

void CTklFile::Load(const char* filePath)
{
	int ThrowNum = 0;
	float* ThrowNumF = 0;
	int version;
	//std::vector<int>ThrowNumVec;
	auto fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		return;
	}
	fread(&version, sizeof(version), 1, fp);
	//���̐����擾�B
	fread(&m_numBone, sizeof(m_numBone), 1, fp);
	m_bones.resize(m_numBone);
	for (int i = 0; i < m_numBone; i++) {
		auto& bone = m_bones.at(i);
		size_t nameCount = 0;
		//���̖��O���擾�B
		fread(&nameCount, 1, 1, fp);
		bone.name = std::make_unique<char[]>(nameCount + 1);
		fread(bone.name.get(), nameCount + 1, 1, fp);
		//�e��ID���擾�B
		fread(&bone.parentNo, sizeof(bone.parentNo), 1, fp);
		//�o�C���h�|�[�Y���擾�B
		fread(bone.bindPose, sizeof(bone.bindPose), 1, fp);
		//�o�C���h�|�[�Y�̋t�����擾�B
		fread(bone.invBindPose, sizeof(bone.invBindPose), 1, fp);

		char shadowFlag;
		fread(&shadowFlag, sizeof(shadowFlag), 1, fp);
		fread(&shadowFlag, sizeof(shadowFlag), 1, fp);
		int buffer;
		fread(&buffer, sizeof(buffer), 1, fp);
		//ThrowNumVec.resize(ThrowNum);
		for (int i = 0; i < ThrowNum; i++) {
			fread(&buffer, sizeof(ThrowNum), 1, fp);
		}
		fread(&buffer, sizeof(ThrowNum), 1, fp);
		for (int i = 0; i < ThrowNum; i++) {
			fread(&buffer, sizeof(ThrowNumF), 1, fp);
		}
		fread(&buffer, sizeof(ThrowNum), 1, fp);
		for (int i = 0; i < ThrowNum; i++) {
			fread(&buffer, sizeof(ThrowNum), 1, fp);
			fread(&buffer, sizeof(ThrowNum), 1, fp);
		}
		fread(&buffer, sizeof(ThrowNum), 1, fp);
		for (int i = 0; i < ThrowNum; i++) {
			fread(&buffer, sizeof(ThrowNum), 1, fp);
		}
		//�{�[���̔ԍ��B
		bone.no = i;
	}

	fclose(fp);


	//�{�[���s����\�z����B
	BuildBoneMatrices();
}

void CTklFile::BuildBoneMatrices()
{
	QueryBone([&](CTklFile::SBone& tksBone) {
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
		auto it = std::find_if(m_bones.begin(), m_bones.end(), [&](auto& bone) {return wcscmp(boneName, bone->GetName()) == 0;  });
		if (it != m_bones.end()) {
			//�����̃{�[�������������B
			_bstr_t b(boneName);
			const char* c = b;
			TK_WARNING("�����̃{�[����������܂����B����̓���ł��B�f�[�^���C�����Ă��������B%s", c);
		}
#endif
		m_bones2.push_back(std::move(bone));
		});
	for (auto& bone : m_bones2) {
		if (bone->GetParentBoneNo() != -1) {
			m_bones2.at(bone->GetParentBoneNo())->AddChild(bone.get());
			//���[�J���}�g���N�X���v�Z�B
			const CMatrix& parentMatrix = m_bones2.at(bone->GetParentBoneNo())->GetInvBindPoseMatrix();
			CMatrix localMatrix;
			localMatrix = bone->GetBindPoseMatrix() * parentMatrix;
			bone->SetLocalMatrix(localMatrix);
		}
		else {
			bone->SetLocalMatrix(bone->GetBindPoseMatrix());
		}
	}


	//�{�[���s����m��
	m_boneMatrixs = std::make_unique<CMatrix[]>(m_bones2.size());
	m_isInited = true;

}

void CTklFile::CalcWorldTRS(CVector3& trans, CQuaternion& rot, CVector3& scale)
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