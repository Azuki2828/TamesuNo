#pragma once
#include "CameraCollisionSolver.h"


	/// <summary>
	/// �o�l�J�����B
	/// �o�l�Ɉ���������悤�ȃJ�����̋�������������N���X�ł��B
	/// SetTarget�֐���SetPosition�֐����g�p���āA
	/// �J�����̖ڕW�ƂȂ钍���_�Ǝ��_��ݒ肵�Ă��������B
	/// Update�֐������s���邱�ƂŁA�J�������ݒ肳�ꂽ�ڕW���W�ɒǏ]���Ă����܂��B
	/// </summary>
	class SpringCamera
	{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		SpringCamera();
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~SpringCamera();

		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="camera">�J�����B</param>
		/// <param name="maxMoveSpeed">�J�����̍ő呬�x�B</param>
		/// <param name="isEnableCollisionSolver">�R���W����������L���ɂ���?</param>
		/// <param name="sphereCollisionRadius">���̂̃R���W�����̔��a�BisEnableCollisionSolover��true�̎��ɗL���ɂȂ�܂��B</param>
		void Init(
			CCamera& camera,
			float maxMoveSpeed,
			bool isEnableCollisionSolver,
			float sphereCollisionRadius
		);
		/// <summary>
		/// �ڕW�ƂȂ钍���_��ݒ�B
		/// </summary>
		/// <param name="target">�����_�B</param>
		void SetTarget(const CVector3& target)
		{
			m_target = target;
		}
		/// <summary>
		/// �ڕW�ƂȂ鎋�_��ݒ�B
		/// </summary>
		/// <param name="position">���_�B</param>
		void SetPosition(const CVector3& position)
		{
			m_position = position;
		}
		/// <summary>
		/// �����ʂ�ݒ�B
		/// </summary>
		/// <param name="_far">�����ʁB</param>
		void SetFar(float _far)
		{
			if (m_camera == nullptr) {
				return;
			}
			m_camera->SetFar(_far);
		}
		/// <summary>
		/// �ߕ��ʁB
		/// </summary>
		/// <param name="_near">�ߕ��ʁB</param>
		void SetNear(float _near)
		{
			if (m_camera == nullptr) {
				return;
			}
			m_camera->SetNear(_near);
		}
		/// <summary>
		/// �J�����̉�]�s����擾�B
		/// </summary>
		/// <returns>�J�����̉�]�s��B</returns>
		const CMatrix& GetCameraRotation() const
		{
			if (m_camera == nullptr) {
				return CMatrix::Identity;
			}
			return m_camera->GetCameraRotation();
		}
		/// <summary>
		/// �ڕW�ƂȂ钍���_���擾�B
		/// ���̊֐����Ԃ��Ă��钍���_�́A���ۂ̒����_�ł͂Ȃ��̂Œ��ӂ��ĉ������B
		///	���ۂ̒����_���ق����ꍇ��GetRealTarget���g�p���Ă��������B
		/// </summary>
		/// <returns>�����_�B</returns>
		const CVector3& GetTarget() const
		{
			return m_target;
		}
		/// <summary>
		/// �ڕW�ƂȂ鎋�_���擾�B
		/// ���̊֐����Ԃ��Ă��鎋�_�́A���ۂ̎��_�ł͂Ȃ��̂Œ��ӂ��Ă��������B
		///	���ۂ̎n�_���ق����ꍇ��GetRealPosition���g�p���ĉ������B
		/// </summary>
		/// <returns>���_�B</returns>
		const CVector3& GetPosition() const
		{
			return m_position;
		}
		/// <summary>
		/// ���ۂ̒����_���擾�B
		/// </summary>
		/// <returns>�����_�B</returns>
		const CVector3& GetRealTarget() const
		{
			if (m_camera == nullptr) {
				return CVector3::Zero;
			}
			return m_camera->GetTarget();

		}
		/// <summary>
		/// ���ۂ̎��_���擾�B
		/// </summary>
		/// <returns>���_�B</returns>
		const CVector3& GetRealPosition() const
		{
			if (m_camera == nullptr) {
				return CVector3::Zero;
			}
			return m_camera->GetPosition();
		}
		/// <summary>
		/// �X�V�B
		/// </summary>
		void Update();
		/// <summary>
		/// �J�������擾�B
		/// </summary>
		/// <returns>�J�����B</returns>
		const CCamera* GetCamera() const
		{
			return m_camera;
		}
		/// <summary>
		/// �o�l�̌�������ݒ�B
		/// �l���傫���قǃJ�������x��ĕt���Ă��܂��B
		/// </summary>
		/// <param name="dampingRate">�o�l�̌������B</param>
		void SetDampingRate(float dampingRate)
		{
			m_targetDampingRate = dampingRate;
		}
		/// <summary>
		/// �J�������擾�B
		/// </summary>
		/// <returns></returns>
		CCamera* GetCamera()
		{
			return m_camera;
		}
		/// <summary>
		/// ��p��ݒ�B
		/// </summary>
		/// <param name="angle">��p�B</param>
		void SetViewAngle(float angle)
		{
			if (m_camera == nullptr) {
				return;
			}
			m_camera->SetViewAngle(angle);
		}
		/// <summary>
		/// ��p���擾�B
		/// </summary>
		/// <returns>��p�B</returns>
		float GetViewAngle() const
		{
			if (m_camera == nullptr) {
				return 0.0f;
			}
			return m_camera->GetViewAngle();
		}
		/// <summary>
		/// ���t���b�V���B
		/// ���̊֐����Ăяo���ƁA�o�l�̈ړ������t���b�V������āAUpdate�֐����Ăяo���ƃJ�����̈ʒu��
		///	�����ɖڕW���_�ƖڕW�����_�Ɉړ����܂��B�V�[�����؂�ւ���ăJ��������C�ɐ؂�ւ������Ƃ��Ȃǂ�
		/// �g�p���Ă��������B
		/// </summary>
		void Refresh()
		{
			m_targetMoveSpeed = CVector3::Zero;
			m_positionMoveSpeed = CVector3::Zero;
			m_isRefresh = true;
		}
		/// <summary>
		/// ���t���b�V�����Ӑ}�I�ɂ��Ȃ��悤�ɂ���Ƃ��Ɏg�p���Ă��������B
		/// </summary>
		void NonRefresh() {

			m_isRefresh = false;
		}
		/// <summary>
		/// �o�l�J�����̍X�V�����B
		/// Update�֐��ŌĂ΂�Ă��܂��B
		/// �o�l�J�����̍X�V���������ʂŌĂт����Ȃǂ̓���ȃP�[�X�Ŏg�p���Ă��������B
		/// </summary>
		void UpdateSpringCamera();
		/// <summary>
		/// �J�����̍X�V�B
		/// Update�֐�����Ă΂�Ă��܂��B
		/// �J�����̍X�V���������ʂŌĂт����Ȃǂ̓���ȃP�[�X�Ŏg�p���Ă��������B
		/// </summary>
		void UpdateCamera()
		{
			if (m_camera) {
				m_camera->Update();
			}
		}
	private:
		CCamera* m_camera = nullptr;						//�J�����B
		CVector3		m_target = CVector3::Zero;				//�ڕW�ƂȂ钍���_�B
		CVector3		m_position = CVector3::Zero;				//�ڕW�ƂȂ鎋�_�B
		CVector3		m_targetMoveSpeed = CVector3::Zero;		//�����_�̈ړ����x�B
		CVector3		m_positionMoveSpeed = CVector3::Zero;	//���_�̈ړ����x�B
		float		m_maxMoveSpeed = 0.0f;					//�ō��ړ����x�B
		float		m_targetDampingRate = 1.0f;				//�������B�l���傫���قǃJ�������x��t���Ă���B
		float		m_dampingRate = 1.0f;					//�������B
		float		m_dampingRateVel = 0.0f;
		bool		m_isEnableCollisionSolver = false;		//�R���W�����������L���H
		bool		m_isRefresh = true;						//���t���b�V�����K�v�H
		CameraCollisionSolver m_cameraCollisionSolver;
	};