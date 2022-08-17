#pragma once

#include "tkFile/TksFile.h"

/// <summary>
/// �{�[���B
/// </summary>
class Bone {
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	/// <param name="boneName">�{�[���̖��O</param>
	/// <param name="bindPose">�o�C���h�|�[�Y�̍s��</param>
	/// <param name="invBindPose">�o�C���h�|�[�Y�̋t�s��</param>
	/// <param name="parentBoneNo">�e�̃{�[���ԍ�</param>
	/// <param name="boneId">�{�[���ԍ�</param>
	Bone(
		const wchar_t* boneName,
		const CMatrix& bindPose,
		const CMatrix& invBindPose,
		int parentBoneNo,
		int boneId
	) :
		m_boneName(boneName),
		m_bindPose(bindPose),
		m_invBindPose(invBindPose),
		m_parentBoneNo(parentBoneNo),
		m_worldMatrix(bindPose),
		m_boneId(boneId)
	{
	}
	/// <summary>
	/// ���[�J���s��(�e�̍��W�n�ł̍s��)��ݒ�B
	/// </summary>
	void SetLocalMatrix(const CMatrix& m)
	{
		m_localMatrix = m;
	}
	/// <summary>
	/// ���[�J���s��(�e�̍��W�n�ł̍s��)���擾�B
	/// </summary>
	const CMatrix& GetLocalMatrix() const
	{
		return m_localMatrix;
	}
	/// <summary>
	/// ���[���h�s���ݒ�B
	/// </summary>
	void SetWorldMatrix(const CMatrix& m)
	{
		m_worldMatrix = m;
	}
	/// <summary>
	/// ���[���h�s����擾�B
	/// </summary>
	const CMatrix& GetWorldMatrix() const
	{
		return m_worldMatrix;
	}
	/// <summary>
	/// �o�C���h�|�[�Y�̍s����擾�B
	/// </summary>
	const CMatrix& GetBindPoseMatrix() const
	{
		return m_bindPose;
	}
	/// <summary>
	/// �o�C���h�|�[�Y�̋t�s����擾�B
	/// </summary>
	const CMatrix& GetInvBindPoseMatrix() const
	{
		return m_invBindPose;
	}
	/// <summary>
	/// �e�̃{�[���ԍ����擾�B
	/// </summary>
	/// <returns></returns>
	int GetParentBoneNo() const
	{
		return m_parentBoneNo;
	}
	/// <summary>
	/// �{�[���ԍ����擾�B
	/// </summary>
	/// <returns></returns>
	int GetNo() const
	{
		return m_boneId;
	}

	/*!
	*@brief	�q����ǉ��B
	*/
	void AddChild(Bone* bone) 
	{
		m_children.push_back(bone);
	}
	/*!
	*@brief	�q�����擾�B
	*/
	std::list<Bone*>& GetChildren()
	{
		return m_children;
	}
	const CMatrix& GetOffsetLocalMatrix() const
	{
		return m_offsetLocalMatrix;
	}
	/*!
		*@brief	���O�̎擾�B
		*/
	const wchar_t* GetName() const
	{
		return m_boneName.c_str();
	}
	/*!
	*@brief	���̃{�[���̃��[���h��Ԃł̈ʒu�Ɖ�]�ƃX�P�[�����v�Z����B
	*@param[out]	trans		���s�ړ��ʂ̊i�[��B
	*@param[out]	rot			��]�ʂ̊i�[��B
	*@param[out]	scale		�g�嗦�̊i�[��B
	*/
	void CalcWorldTRS(CVector3& trans, CQuaternion& rot, CVector3& scale);
		
private:
	
	std::wstring	m_boneName;
	int				m_parentBoneNo = -1;	//�e�̃{�[���ԍ��B
	int				m_boneId = -1;			//�{�[���ԍ��B
	CMatrix			m_bindPose;				//�o�C���h�|�[�Y�B
	CMatrix			m_invBindPose;			//�o�C���h�|�[�Y�̋t�s��B
	CMatrix			m_localMatrix;			//���[�J���s��B
	CMatrix			m_worldMatrix;			//���[���h�s��B
	CMatrix			m_offsetLocalMatrix;
	CVector3			m_positoin;				//���̃{�[���̃��[���h��Ԃł̈ʒu�B�Ō��CalcWorldTRS�����s�����Ƃ��̌��ʂ��i�[����Ă���B
	CVector3			m_scale;				//���̃{�[���̊g�嗦�B�Ō��CalcWorldTRS�����s�����Ƃ��̌��ʂ��i�[����Ă���B
	CQuaternion		m_rotation;				//���̃{�[���̉�]�B�Ō��CalcWorldTRS�����s�����Ƃ��̌��ʂ��i�[����Ă���B
	std::list<Bone*>	m_children;			//�q���̃��X�g�B
};

/// <summary>
/// �X�P���g���N���X�B
/// </summary>
class Skeleton  {
public:
	using OnPostProcessSkeletonUpdate = std::function<void()>;

	Skeleton();
	~Skeleton();
		
	/// <summary>
	/// �{�[���̃��[�J���s���ݒ�B
	/// </summary>
	/// <param name="boneNo">�{�[���ԍ�</param>
	/// <param name="m">�s��</param>
	void SetBoneLocalMatrix(int boneNo, const CMatrix& m)
	{
		if (boneNo > (int)m_bones.size() - 1) {
			MessageBoxA(nullptr, "boneNo is over m_bones.size() ", "error", MB_OK);
			return;
		}
		m_bones[boneNo]->SetLocalMatrix(m);
	}

	/// <summary>
	/// �{�[���̐����擾�B
	/// </summary>
	/// <returns></returns>
	int GetNumBones() const
	{
		return static_cast<int>(m_bones.size());
	}
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="tksFilePath">tks�t�@�C���̃t�@�C���p�X</param>
	/// <returns>true���Ԃ��Ă����烍�[�h�����B</returns>
	bool Init(const char* tksFilePath);

	/// <summary>
	/// �������ς݂�����B
/// </summary>
/// <returns></returns>
bool IsInited() const
{
	return m_isInited;
}
/// <summary>
/// �{�[���s��̍\�z�B
/// �ǂݍ��݂�����������ŌĂяo���Ă��������B
/// </summary>
void BuildBoneMatrices();
/// <summary>
/// �{�[���̖��O����{�[���ԍ��������B
/// </summary>
/// <param name="boneName">�{�[���̖��O</param>
/// <returns>�{�[���ԍ��B������Ȃ������ꍇ��-1���Ԃ��Ă��܂��B</returns>
int FindBoneID(const wchar_t* boneName) const
{
	for (int i = 0; i < (int)m_bones.size(); i++) {
		if (wcscmp(m_bones[i]->GetName(), boneName) == 0) {
			return i;
		}
	}
	//������Ȃ������B
	return -1;
}
/// <summary>
/// �{�[���ԍ�����{�[�����擾�B
/// </summary>
/// <param name="boneNo">�{�[���ԍ�</param>
/// <returns>�{�[��</returns>
Bone* GetBone(int boneNo) const
{
	return m_bones[boneNo].get();
}

/// <summary>
/// �w��̃{�[���s����擾�B
/// </summary>
/// <returns></returns>
CMatrix* GetBoneMatrix(const int boneNo)const
{
	return &m_boneMatrixs[boneNo];
}
/// <summary>
/// �{�[���s��̐擪�A�h���X���擾�B
/// </summary>
/// <returns></returns>
CMatrix* GetBoneMatricesTopAddress() const
{
	return m_boneMatrixs.get();
}
/// <summary>
/// �A�j���[�V�������Đ�����Ă���}�[�N��t����B
/// </summary>
void SetMarkPlayAnimation()
{
	m_isPlayAnimation = true;
}
public:

	/**
	 * @brief �{�[���s����R�s�[����֐��B
	 * @param skeletonBase �R�s�[���ƂȂ�{�[��
	*/
	void CopyBoneMatrix(
		Skeleton& upperBody,
		Skeleton& lowerBody,
		const char* upperBodyBoneNameArray[],
		const char* lowerBodyBoneNameArray[],
		int upperBodyBoneNameArraySize,
		int lowerBodyBoneNameArraySize
	);
	

	void SetBoneLocalMatrix(
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
					m_bones[boneNum].get()->SetLocalMatrix(upperBody.GetBone(boneNum)->GetLocalMatrix());
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
					m_bones[boneNum].get()->SetLocalMatrix(lowerBody.GetBone(boneNum)->GetLocalMatrix());
					findBone = true;
				}
			}

			//�{�[����������Ȃ������B
			if (!findBone) {

				m_bones[boneNum].get()->SetLocalMatrix(upperBody.GetBone(boneNum)->GetLocalMatrix());
			}
		}
	}
	
	/// <summary>
	/// �X�V�B
	/// </summary>
	/// <param name="mWorld"></param>
	void Update(const CMatrix& mWorld);

	/// <summary>
	/// �X�V�B�ŗL�̃A�j���[�V�����������Ă���i�A�j���[�V�����u�����h������j�ꍇ�̓{�[���s��̍X�V�����Ȃ��B
	/// </summary>
	/// <param name="mWorld"></param>
	void UpdateHasVerUniqueAnimation(const CMatrix& mWorld);
	
	/// <summary>
	/// �{�[���̃��[���h�s��̍X�V�֐��B
	/// </summary>
	/// <remarks>
	/// �ʏ�̓��[�U�[�����̊֐����Ăяo���K�v�͂���܂���B
	/// </remarks>
	/// <param name="bone">�X�V����{�[���B</param>
	/// <param name="parentMatrix">�e�̃{�[���̃��[���h�s��B</param>
	static 	void UpdateBoneWorldMatrix(Bone& bone, const CMatrix& parentMatrix);

private:
	CTksFile m_tksFile;										//TKS�t�@�C���B
	static const int BONE_MAX = 512;				//�{�[���̍ő吔�B
	using BonePtr = std::unique_ptr<Bone>;
	std::vector<BonePtr>	m_bones;				//�{�[���̔z��B
	std::unique_ptr<CMatrix[]>	m_boneMatrixs;	//�{�[���s��B
	bool m_isInited = false;								//�������ς݁H
	bool m_isPlayAnimation = false;					//�A�j���[�V�������������܂�Ă���H
};