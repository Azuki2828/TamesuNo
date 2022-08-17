#pragma once

namespace nsMyGame {

	//���f���Ǘ��N���X
	class CModelRender : public CIGameObject
	{
		//�R���X�^���g�o�b�t�@�ɓ]������f�[�^
		struct SModelData {

			int shadowReceiverFlg = 0;		//�V���h�E���V�[�o�[�t���O
		};
	public:
		/**
		 * @brief �X�V�֐��B
		*/
		void Update()override final;

		/**
		 * @brief �`��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void Render(CRenderContext& rc)override final;

		/**
		 * @brief �t�H���[�h�����_�����O�p�̕`��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void ForwardRender(CRenderContext& rc)override final;
	public:
		/**
		 * @brief �������֐��B
		*/
		void Init();

		/**
		 * @brief �f�[�^�t���������֐��B
		 * @param modelInitData ���f���f�[�^
		*/
		void Init(ModelInitData& modelInitData);

		/**
		 * @brief �t�H���[�h�����_�����O�p�̃��f���̏������֐��B
		*/
		void InitForwardRenderingModel();

		/**
		 * @brief �f�[�^�t���t�H���[�h�����_�����O�p�̃��f���̏������֐��B
		*/
		void InitForwardRenderingModel(ModelInitData& modelInitData);

		/**
		 * @brief tkm�t�@�C����ݒ肷��֐��B
		 * @param filePathTkm �t�@�C����(.tkm)
		*/
		void SetFilePathTkm(const char* filePathTkm) {
			m_filePathTkm = filePathTkm;
		}

		/**
		 * @brief tks�t�@�C����ݒ肷��֐��B
		 * @param filePathTks �t�@�C����(.tks)
		*/
		void SetFilePathTks(const char* filePathTks) {
			m_filePathTks = filePathTks;
		}

		/**
		 * @brief tks�t�@�C���̃p�X���擾����֐��B
		 * @return tks�t�@�C���̃t�@�C���p�X
		*/
		const char* GetFilePathTks()const {

			return m_filePathTks;
		}

		/**
		 * @brief fx�t�@�C���p�X��ݒ肷��֐��B
		 * @param filePathFx �t�@�C����(.fx)
		*/
		void SetFilePathFx(const char* filePathFx) {

			m_filePathFx = filePathFx;
		}

		/**
		 * @brief �A�j���[�V������ݒ肷��֐��B
		 * @param animClip �A�j���[�V�����N���b�v
		 * @param animNum �A�j���[�V�������B
		*/
		void InitAnimation(CAnimationClip* animClip, int animNum) {
			m_animationClip = animClip;
			m_animNum = animNum;
			SetAnimFlg(true);
		}

		/**
		 * @brief �A�j���[�V�������Đ�����t���O
		 * @param flg �A�j���[�V�����t���O
		*/
		void SetAnimFlg(bool flg) {
			m_animFlg = flg;
		}

		/**
		 * @brief �A�j���[�V�����̍Đ��B
		 * @param animNo �A�j���[�V�����N���b�v�̔ԍ�
		 * @param interpolateTime �⊮����
		*/
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		/**
		 * @brief �A�j���[�V�����C�x���g��ݒ肷��֐��B
		 * @param eventListener �C�x���g���X�i�[
		*/
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}

		/**
		 * @brief �A�j���[�V�����C�x���g��ݒ肷��֐��B
		 * @param animation �A�j���[�V����
		 * @param eventListener �C�x���g���X�i�[
		*/
		void AddAnimationEvent(Animation& animation, AnimationEventListener eventListener)
		{
			animation.AddAnimationEventListener(eventListener);
		}

		/**
		 * @brief ���[���h�s����X�V����֐��B(��������)
		 * @param pos ���W
		 * @param rot ��]
		 * @param sca �g�嗦
		*/
		void UpdateWorldMatrix(const CVector3& pos, const CQuaternion& rot, const CVector3& sca)
		{
			m_model.UpdateWorldMatrix(pos, rot, sca);
		}

		/**
		 * @brief ���[���h�s����X�V����֐��B(�����Ȃ�)
		*/
		void UpdateWorldMatrix()
		{
			m_model.UpdateWorldMatrix(m_pos, m_rot, m_sca);
		}

		/**
		 * @brief ���W��ݒ肷��֐��B
		 * @param pos ���W
		*/
		void SetPosition(const CVector3& pos) {
			m_pos = pos;
		}

		/**
		 * @brief ���W���擾����֐��B
		 * @return ���W
		*/
		const CVector3& GetPosition()const {

			return m_pos;
		}

		/**
		 * @brief ��]����ݒ肷��֐��B
		 * @param rot ��]��
		*/
		void SetRotation(const CQuaternion& rot) {

			m_rot = rot;
		}

		/**
		 * @brief ��]�����擾����֐��B
		 * @return ��]��
		*/
		const CQuaternion& GetRotation()const {

			return m_rot;
		}

		/**
		 * @brief �g�嗦��ݒ肷��֐��B
		 * @param sca �g�嗦
		*/
		void SetScale(const CVector3& sca) {

			m_sca = sca;
		}

		/**
		 * @brief �g�嗦���擾����֐��B
		 * @return �g�嗦
		*/
		const CVector3& GetScale()const {

			return m_sca;
		}

		/**
		 * @brief �V���h�E�L���X�^�[�t���O��ݒ肷��֐��B
		 * @param flg �V���h�E�L���X�^�[�t���O�B
		*/
		void SetShadowCasterFlag(bool flg) {

			m_shadowCasterFlag = flg;
		}

		/**
		 * @brief �V���h�E���V�[�o�[�t���O��ݒ肷��֐��B
		 * @param flg �V���h�E���V�[�o�[�t���O
		*/
		void SetShadowReceiverFlag(bool flg) {

			m_modelData.shadowReceiverFlg = flg;
		}

		/**
		 * @brief ���f���̏㎲��ݒ肷��֐��B
		 * @param modelUpAxis ��ɂ�������
		*/
		void SetModelUpAxis(EnModelUpAxis modelUpAxis) {

			m_modelInitData.m_modelUpAxis = modelUpAxis;
		}

		/**
		 * @brief ���f�����擾����֐��B
		 * @return ���f��
		*/
		CModel* GetModel() { return &m_model; }

		/**
		 * @brief �X�P���g�����擾����֐��B
		 * @return �X�P���g��
		*/
		Skeleton* GetSkeleton() {

			return &m_skeleton;
		}

		/**
		 * @brief �A�j���[�V�������Đ������ǂ����H
		 * @return �A�j���[�V�����Đ����H
		*/
		bool IsPlayingAnimation() {

			return m_animation.IsPlaying();
		}

		/**
		 * @brief �A�j���[�V�����̍Đ����x��ݒ肷��֐��B
		 * @param animSpeed �A�j���[�V�����̍Đ����x
		*/
		void SetAnimationSpeed(const float animSpeed) {

			m_animationSpeed = animSpeed;
		}

		/**
		 * @brief �R���W�������f�����ǂ����̃t���O��ݒ肷��֐��B
		 * @param collisionModelFlag �R���W�������f�����ǂ����̃t���O
		*/
		void SetCollisionModelFlag(const bool collisionModelFlag) {

			m_isCollisionModel = collisionModelFlag;
		}

		/**
		 * @brief �����蔻��p�̃��f���H
		 * @return �����蔻��p�̃��f�����ǂ����̃t���O
		*/
		const bool IsCollisionModel()const {

			return m_isCollisionModel;
		}

		/**
		 * @brief �{�[�����R�s�[����֐��B
		 * @param skeleton �R�s�[���ƂȂ�X�P���g��
		*/
		void CopyBone(
			Skeleton& upperBody,
			Skeleton& lowerBody, 
			const char* upperBodyBoneNameArray[],
			const char* lowerBodyBoneNameArray[],
			int upperBodyBoneNameArraySize,
			int lowerBodyBoneNameArraySize
		) {

			m_skeleton.CopyBoneMatrix(upperBody, lowerBody,upperBodyBoneNameArray, lowerBodyBoneNameArray, upperBodyBoneNameArraySize, lowerBodyBoneNameArraySize);
			//m_skeleton.SetBoneLocalMatrix(upperBody, lowerBody, upperBodyBoneNameArray, lowerBodyBoneNameArray, upperBodyBoneNameArraySize, lowerBodyBoneNameArraySize);
		}

		/**
		 * @brief �ŗL�̃A�j���[�V��������������B
		*/
		void GiveUniqueAnimation() {

			m_hasUniqueAnimation = true;
		}

	private:
		/**
		 * @brief �V���h�E���f�����쐬����֐��B
		*/
		void CreateShadowModel();

		/**
		 * @brief tkm�t�@�C����tks�t�@�C���̃p�X��ݒ肷��֐��B
		*/
		void SetFilePathTkmAndTks();
	private:
		const char* m_filePathTkm = nullptr;		//tkm�t�@�C���p�X
		const char* m_filePathTks = nullptr;		//tks�t�@�C���p�X
		const char* m_filePathFx = nullptr;			//fx�t�@�C���p�X

		bool m_shadowCasterFlag = false;			//�V���h�E�L���X�^�[�t���O
		bool m_isCollisionModel = false;			//�����蔻��p�̃��f���H

		CVector3 m_pos = CVector3::Zero;			//���W
		CQuaternion m_rot = CQuaternion::Identity;	//��]��
		CVector3 m_sca = CVector3::One;				//�g�嗦

		CModel m_model;								//���f��
		CModel m_forwardRenderModel;				//�t�H���[�h�����_�����O�p�̃��f��
		CModel m_shadowModel;						//�V���h�E�쐬�p�̃��f��
		SModelData m_modelData;						//�R���X�^���g�o�b�t�@�ɓ]������f�[�^
		ModelInitData m_modelInitData;				//���f���f�[�^
		Skeleton m_skeleton;						//�X�P���g��

		bool m_hasUniqueAnimation = false;			//�ŗL�̃A�j���[�V������ێ����Ă���H

		bool m_animFlg = false;						//�A�j���[�V�����Đ��t���O
		int m_animNum = 0;							//�A�j���[�V������
		float m_animationSpeed = 1.0f;				//�A�j���[�V�����̍Đ����x
		Animation m_animation;						//�A�j���[�V����
		CAnimationClip* m_animationClip = nullptr;	//�A�j���[�V�����N���b�v
	};
}

