#pragma once

namespace nsMyGame {

	//���C�g�J�����O�N���X
	class CLightCulling
	{
	private:
		// ���C�g�J�����O�Ŏg�p����J�������
		struct alignas(16) LightCullingCameraData
		{
			CMatrix mProj;           // �v���W�F�N�V�����s��
			CMatrix mProjInv;        // �v���W�F�N�V�����s��̋t�s��
			CMatrix mCameraRot;      // �J�����̉�]�s��
			CVector4 screenParam;    // �X�N���[�����
		};
	public:
		/**
		 * @brief �������֐��B
		*/
		void Init();

		/**
		 * @brief ���C�g�J�����O���s�֐��B
		*/
		void Execute(CRenderContext& rc);

		/**
		 * @brief �^�C�����Ƃ̃|�C���g���C�g�̔ԍ��̃��X�g���o�͂���UAV���擾����֐��B
		 * @return �^�C�����Ƃ̃|�C���g���C�g�̔ԍ��̃��X�g���o�͂���UAV
		*/
		RWStructuredBuffer& GetPointLightNoListInTileUAV() {

			return m_pointLightNoListInTileUAV;
		}
	private:
		/**
		 * @brief �p�C�v���C���X�e�[�g������������֐��B
		*/
		void InitPipelineState(RootSignature& rs, PipelineState& pipelineState, Shader& cs);

		/**
		 * @brief ���C�g�J�����O�Ɏg�p����J�����̃f�[�^������������֐��B
		*/
		void UpdateLightCullingCameraData();

		/**
		 * @brief ���C�g�J�����O�p�̃f�B�X�N���v�^�q�[�v������������֐��B
		*/
		void InitLightCullingDescriptorHeap();
	private:
		Shader m_csLightCulling;							//���C�g�J�����O�p�̃R���s���[�g�V�F�[�_�[
		PipelineState m_lightCullingPipelineState;			//�p�C�v���C���X�e�[�g
		RootSignature m_rootSignature;						//���[�g�V�O�l�`��
		RWStructuredBuffer m_pointLightNoListInTileUAV;		//�^�C�����Ƃ̃|�C���g���C�g�̔ԍ��̃��X�g���o�͂���UAV
		LightCullingCameraData m_lightCullingCameraData;	//���C�g�J�����O�Ɏg�p����J�����̃f�[�^
		ConstantBuffer m_cameraParamCB;						//�|�C���g���C�g�̏��𑗂邽�߂̒萔�o�b�t�@
		ConstantBuffer m_lightCB;							//�|�C���g���C�g�̏��𑗂邽�߂̒萔�o�b�t�@
		DescriptorHeap m_lightCullingDescriptorHeap;		//���C�g�J�����O�p�̃f�B�X�N���v�^�q�[�v
	};
}

