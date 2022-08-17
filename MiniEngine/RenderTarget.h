#pragma once
#pragma once

#include "Texture.h"
#include "../GameTemplate/Game/ConstValue.h"

class CGraphicsEngine;


//�����_�����O�^�[�Q�b�g�̃��X�g
enum EnRenderTargetList {
	enMainRT,

	enRenderTargetNum
};


//GBuffer�̃��X�g
enum EnGBufferList {
	enAlbedoAndShadowReceiverFlgMap,
	enNormalMap,
	enWorldPosMap,
	enDepthMap,
	enocclusionAndSmoothAndMetaricMap,

	enGBufferNum
};


/// �����_�����O�^�[�Q�b�g�N���X�B

class CRenderTarget {
public:
	
	/**
	 * @brief �f�X�g���N�^�B
	*/
	~CRenderTarget();

	/**
	 * @brief �����_�����O�^�[�Q�b�g�̍쐬�B
	 * @param w �����_�����O�^�[�Q�b�g�̕�
	 * @param h �����_�����O�^�[�Q�b�g�̍���
	 * @param mipLevel �~�b�v�}�b�v���x���B0���w�肵���ꍇ�̓~�b�v�}�b�v���T�|�[�g����Ă���GPU�ł�1*1�s�N�Z���܂ł̃~�b�v�}�b�v���쐬�����B
	 * @param arraySize �e�N�X�`���z��̃T�C�Y
	 * @param colorFormat �J���[�o�b�t�@�̃t�H�[�}�b�g�B
	 * @param depthStencilFormat �[�x�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B
	 * @param clearColor �����J���[
	 * @return �쐬�ɐ��������H
	*/
	bool Create(
		int w,
		int h,
		int mipLevel,
		int arraySize,
		DXGI_FORMAT colorFormat,
		DXGI_FORMAT depthStencilFormat,
		float clearColor[4] = nullptr
	);

	/**
	 * @brief ���C�������_�����O�^�[�Q�b�g���쐬����֐��B
	*/
	static void CreateMainRenderTarget() {

		m_renderTarget[enMainRT] = new CRenderTarget;

		m_renderTarget[enMainRT]->Create(
			c_renderTargetW1280H720.x,
			c_renderTargetW1280H720.y,
			c_mipLevel1,
			c_renderArraySize1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}


	/**
	 * @brief �A���x�h�J���[�ƃV���h�E���V�[�o�[�t���O��ۊǂ���GBuffer���쐬����֐��B
	*/
	static void CreateAlbedoAndShadowReceiverFlagRenderTarget() {

		m_GBuffer[enAlbedoAndShadowReceiverFlgMap] = new CRenderTarget;

		m_GBuffer[enAlbedoAndShadowReceiverFlgMap]->Create(
			c_renderTargetW1280H720.x,
			c_renderTargetW1280H720.y,
			c_mipLevel1,
			c_renderArraySize1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	/**
	 * @brief �@���Ɛ[�x�l��ۊǂ���GBuffer���쐬����֐��B
	*/
	static void CreateNormalMapRenderTarget() {

		m_GBuffer[enNormalMap] = new CRenderTarget;

		m_GBuffer[enNormalMap]->Create(
			c_renderTargetW1280H720.x,
			c_renderTargetW1280H720.y,
			c_mipLevel1,
			c_renderArraySize1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);
	}

	/**
	 * @brief ���[���h���W��ۊǂ���GBuffer���쐬����֐��B
	*/
	static void CreateWorldPosRenderTarget() {

		m_GBuffer[enWorldPosMap] = new CRenderTarget;

		m_GBuffer[enWorldPosMap]->Create(
			c_renderTargetW1280H720.x,
			c_renderTargetW1280H720.y,
			c_mipLevel1,
			c_renderArraySize1,
			DXGI_FORMAT_R32G32B32A32_FLOAT, // ���[���h���W���L�^����̂ŁA32�r�b�g���������_�o�b�t�@�𗘗p����
			DXGI_FORMAT_UNKNOWN
		);
	}

	/**
	 * @brief �[�x�l��ۊǂ���GBuffer���쐬����֐��B
	*/
	static void CreateDepthRenderTarget() {

		m_GBuffer[enDepthMap] = new CRenderTarget;

		m_GBuffer[enDepthMap]->Create(
			c_renderTargetW1280H720.x,
			c_renderTargetW1280H720.y,
			c_mipLevel1,
			c_renderArraySize1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);
	}

	static void CreateSpecularRenderTarget() {

		m_GBuffer[enocclusionAndSmoothAndMetaricMap] = new CRenderTarget;

		m_GBuffer[enocclusionAndSmoothAndMetaricMap]->Create(
			c_renderTargetW1280H720.x,
			c_renderTargetW1280H720.y,
			c_mipLevel1,
			c_renderArraySize1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	/**
	 * @brief �����_�����O�^�[�Q�b�g���擾����֐��B
	 * @param renderTarget �w�肷�郌���_�����O�^�[�Q�b�g
	 * @return �w�肵�������_�����O�^�[�Q�b�g
	*/
	static CRenderTarget* GetRenderTarget(EnRenderTargetList renderTarget) {

		return m_renderTarget[renderTarget];
	}

	/**
	 * @brief GBuffer�p�̃����_�����O�^�[�Q�b�g���擾����֐��B
	 * @param gBufferRT �w�肷�郌���_�����O�^�[�Q�b�g
	 * @return �w�肵�������_�����O�^�[�Q�b�g
	*/
	static CRenderTarget* GetGBufferRT(EnGBufferList gBufferRT) {

		return m_GBuffer[gBufferRT];
	}

	/**
	 * @brief CPU���̃����_�����O�^�[�Q�b�g�̃f�B�X�N���v�^�n���h�����擾�B
	 * @return CPU���̃����_�����O�^�[�Q�b�g�̃f�B�X�N���v�^�n���h��
	*/
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCpuDescriptorHandle() const
	{
		return m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	}

	/**
	 * @brief CPU���̃f�v�X�X�e���V���o�b�t�@�̃f�B�X�N���v�^�n���h�����擾�B
	 * @return CPU���̃f�v�X�X�e���V���o�b�t�@�̃f�B�X�N���v�^�n���h��
	*/
	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCpuDescriptorHandle() const
	{
		return m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
	}

	/**
	 * @brief �����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`�����擾�B
	 * @return �����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`��
	*/
	Texture& GetRenderTargetTexture()
	{
		return m_renderTargetTexture;
	}

	/**
	 * @brief �f�v�X�X�e���V���o�b�t�@�����݂��Ă��邩����
	 * @return �f�v�X�X�e���V���o�b�t�@�����݂��Ă���?
	*/
	bool IsExsitDepthStencilBuffer() const
	{
		return m_depthStencilTexture;
	}

	/**
	 * @brief �����_�����O�^�[�Q�b�g�̕����擾�B
	 * @return �����_�����O�^�[�Q�b�g�̕�
	*/
	int GetWidth() const
	{
		return m_width;
	}

	/**
	 * @brief �����_�����O�^�[�Q�b�g�̍������擾�B
	 * @return �����_�����O�^�[�Q�b�g�̍���
	*/
	int GetHeight() const
	{
		return m_height;
	}

	/**
	 * @brief �J���[�o�b�t�@�̃t�H�[�}�b�g���擾�B
	 * @return �J���[�o�b�t�@�̃t�H�[�}�b�g
	*/
	DXGI_FORMAT GetColorBufferFormat() const
	{
		return m_renderTargetTexture.GetFormat();
	}

	/**
	 * @brief �����_�����O�^�[�Q�b�g�r���[�̃N���A�J���[���擾����֐��B
	 * @return �����_�����O�^�[�Q�b�g�r���[�̃N���A�J���[
	*/
	const float* GetRTVClearColor() const
	{
		return m_rtvClearColor;
	}

	/**
	 * @brief DSV�̃N���A�J���[���擾����֐��B
	 * @return DSV�̃N���A�J���[
	*/
	float GetDSVClearValue() const
	{
		return m_dsvClearValue;
	}
private:

	/**
	 * @brief �f�B�X�N���v�^�q�[�v���쐬�B
	 * @param ge �O���t�B�b�N�G���W��
	 * @param d3dDevice D3D�f�o�C�X
	 * @return �쐬�ɐ��������H
	*/
	bool CreateDescriptorHeap(CGraphicsEngine& ge, ID3D12Device5*& d3dDevice);

	/**
	 * @brief �����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬�B
	 * @param ge �O���t�B�b�N�G���W��
	 * @param d3dDevice D3D�f�o�C�X
	 * @param w �e�N�X�`���̕�
	 * @param h �e�N�X�`���̍���
	 * @param mipLevel �~�b�v�}�b�v���x��
	 * @param arraySize �e�N�X�`���z��̃T�C�Y
	 * @param format �e�N�X�`���̃t�H�[�}�b�g
	 * @param clearColor �����J���[
	 * @return �쐬�ɐ��������H
	*/
	bool CreateRenderTargetTexture(
		CGraphicsEngine& ge,
		ID3D12Device5*& d3dDevice,
		int w, 
		int h,
		int mipLevel,
		int arraySize,
		DXGI_FORMAT format,
		float clearColor[4]
	);

	/**
	 * @brief �[�x�X�e���V���o�b�t�@�ƂȂ�e�N�X�`�����쐬�B
	 * @param ge �O���t�B�b�N�G���W��
	 * @param d3dDevice D3D�f�o�C�X
	 * @param w �e�N�X�`���̕�
	 * @param h �e�N�X�`���̍���
	 * @param format �e�N�X�`���̃t�H�[�}�b�g
	 * @return �쐬�ɐ��������H
	*/
	bool CreateDepthStencilTexture(
		CGraphicsEngine& ge,
		ID3D12Device5*& d3dDevice,
		int w,
		int h,
		DXGI_FORMAT format);

	/**
	 * @brief �f�B�X�N���v�^�̍쐬�B
	 * @param d3dDevice D3D�f�o�C�X
	*/
	void CreateDescriptor(ID3D12Device5*& d3dDevice);
private:
	static CRenderTarget* m_renderTarget[enRenderTargetNum];		//�����_�����O�^�[�Q�b�g
	static CRenderTarget* m_GBuffer[enGBufferNum];				//GBuffer�p�̃����_�����O�^�[�Q�b�g

	Texture m_renderTargetTexture;				//�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���B
	ID3D12Resource* m_renderTargetTextureDx12;	//�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���B
	ID3D12Resource* m_depthStencilTexture;		//�[�x�X�e���V���o�b�t�@�ƂȂ�e�N�X�`���B
	ID3D12DescriptorHeap*		m_rtvHeap;		//RTV�p�̃f�B�X�N���v�^�q�[�v�B
	ID3D12DescriptorHeap*		m_dsvHeap;		//�[�x�X�e���V���o�b�t�@�r���[�̃f�B�X�N���v�^�q�[�v�B
	UINT m_rtvDescriptorSize = 0;				//�t���[���o�b�t�@�̃f�B�X�N���v�^�̃T�C�Y�B
	UINT m_dsvDescriptorSize = 0;				//�[�x�X�e���V���o�b�t�@�̃f�B�X�N���v�^�̃T�C�Y�B
	int m_width = 0;							//�����_�����O�^�[�Q�b�g�̕��B
	int m_height = 0;							//�����_�����O�^�[�Q�b�g�̍����B
	float m_rtvClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	//�����_�����O�^�[�Q�b�g�r���[�̃N���A�J���[�B
	float m_dsvClearValue = 1.0f;							//DSV�̃N���A�J���[�B
};


