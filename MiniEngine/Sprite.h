#pragma once

#include "Indexbuffer.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"

class Texture;

//�X�v���C�g�ɐݒ�ł���ő�e�N�X�`�����B
const int MAX_TEXTURE = 16;	
//�g��SRV���ݒ肳��郌�W�X�^�̊J�n�ԍ��B
const int EXPAND_SRV_REG__START_NO = 10;
const int EXPAND_SRV_REG__START_NO2 = 11;

class IShaderResource;

/// <summary>
/// �A���t�@�u�����f�B���O���[�h
/// </summary>
enum AlphaBlendMode {
	AlphaBlendMode_None,	//�A���t�@�u�����f�B���O�Ȃ�(�㏑��)�B
	AlphaBlendMode_Trans,	//����������
	AlphaBlendMode_Add,		//���Z����
};
/// <summary>
/// �X�v���C�g�̏������f�[�^�B
/// </summary>
struct SpriteInitData {
	const char* m_ddsFilePath[MAX_TEXTURE]= {nullptr};		//DDS�t�@�C���̃t�@�C���p�X�B
	Texture* m_textures[MAX_TEXTURE] = { nullptr };			//�g�p����e�N�X�`���BDDS�t�@�C���̃p�X���w�肳��Ă���ꍇ�́A���̃p�����[�^�͖�������܂��B
	const char* m_vsEntryPointFunc = "VSMain";				//���_�V�F�[�_�[�̃G���g���[�|�C���g�B
	const char* m_psEntryPoinFunc = "PSMain";				//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g�B
	const char* m_fxFilePath = nullptr;						//.fx�t�@�C���̃t�@�C���p�X�B
	UINT m_width = 0;										//�X�v���C�g�̕��B
	UINT m_height = 0;										//�X�v���C�g�̍����B
	void* m_expandConstantBuffer = nullptr;					//���[�U�[�g���̒萔�o�b�t�@
	int m_expandConstantBufferSize = 0;						//���[�U�[�g���̒萔�o�b�t�@�̃T�C�Y�B
	IShaderResource* m_expandShaderResoruceView = nullptr;	//���[�U�[�g���̃V�F�[�_�[���\�[�X�B
	IShaderResource* m_expandShaderResoruceView2 = nullptr;	//���[�U�[�g���̃V�F�[�_�[���\�[�X�B
	AlphaBlendMode m_alphaBlendMode = AlphaBlendMode_None;	//�A���t�@�u�����f�B���O���[�h�B
	DXGI_FORMAT m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
};
/// <summary>
/// �X�v���C�g�N���X�B
/// </summary>
class CSprite  {
public:
	static const CVector2	DEFAULT_PIVOT;					//!<�s�{�b�g�B
	virtual ~CSprite();
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="initData">�������f�[�^</param>
	void Init(const SpriteInitData& initData);
	/// <summary>
	/// �X�V�B
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="pivot">
	/// �s�{�b�g
	/// 0.5, 0.5�ŉ摜�̒��S����_�B
	/// 0.0, 0.0�ŉ摜�̍����B
	/// 1.0, 1.0�ŉ摜�̉E��B
	/// Unity��uGUI�ɏ����B
	/// </param>
	void Update(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = DEFAULT_PIVOT);
	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="renderContext">�����_�����O�R���e�L�X�g/param>
	void Draw(CRenderContext& renderContext);
	/// <summary>
	/// ����������Ă��邩����B
	/// </summary>
	/// <returns></returns>
	bool IsInited() const
	{
		return m_isInited;
	}
private:
	/// <summary>
	/// �e�N�X�`�����������B
	/// </summary>
	/// <param name="initData"></param>
	void InitTextures(const SpriteInitData& initData);
	/// <summary>
	/// �V�F�[�_�[���������B
	/// </summary>
	/// <param name="initData"></param>
	void InitShader( const SpriteInitData& initData );
	/// <summary>
	/// �f�B�X�N���v�^�q�[�v���������B
	/// </summary>
	/// <param name="initData"></param>
	void InitDescriptorHeap(const SpriteInitData& initData);
	/// <summary>
	/// ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@���������B
	/// </summary>
	/// <param name="initData"></param>
	void InitVertexBufferAndIndexBuffer(const SpriteInitData& initData);
	/// <summary>
	/// �p�C�v���C���X�e�[�g������������B
	/// </summary>
	void InitPipelineState(const SpriteInitData& initData);
	/// <summary>
	/// �萔�o�b�t�@���������B
	/// </summary>
	/// <param name="initData"></param>
	void InitConstantBuffer(const SpriteInitData& initData);

public:
	void SetPosition(const CVector3& pos) {
		m_position = pos;
	}
	void SetRotation(const CQuaternion& rot) {
		m_rotation = rot;
	}
	void SetScale(const CVector3& sca) {
		m_scale = sca;
	}
	void SetMulColor(const CVector4& mulCol) {

		m_mulColor = mulCol;
	}
private:
	IndexBuffer m_indexBuffer;			//�C���f�b�N�X�o�b�t�@�B
	VertexBuffer m_vertexBuffer;		//���_�o�b�t�@�B
	int m_numTexture = 0;				//�e�N�X�`���̖����B
	Texture m_textures[MAX_TEXTURE];	//�e�N�X�`���B
	Texture* m_textureExternal[MAX_TEXTURE] = {nullptr};	//�O������w�肳�ꂽ�e�N�X�`��
	CVector3 m_position;				//���W�B
	CVector3 m_scale;				//�g�嗦�B
	CVector2 m_size;						//�T�C�Y�B
	CQuaternion m_rotation ;			//��]�B
	CVector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };		//��Z�J���[�B
	CMatrix m_world;					//���[���h�s��B

	struct LocalConstantBuffer {
		CMatrix mvp;
		CVector4 mulColor;
		CVector4 screenParam;
	};
	LocalConstantBuffer m_constantBufferCPU;	//CPU���̒萔�o�b�t�@�B
	ConstantBuffer		m_constantBufferGPU;	//GPU���̒萔�o�b�t�@�B
	ConstantBuffer		m_userExpandConstantBufferGPU;	//���[�U�[�g���̒萔�o�b�t�@(GPU��)
	void* m_userExpandConstantBufferCPU = nullptr;		//���[�U�[�g���̒萔�o�b�t�@(CPU��)
	DescriptorHeap		m_descriptorHeap;		//�f�B�X�N���v�^�q�[�v�B
	RootSignature		m_rootSignature;		//���[�g�V�O�l�`���B
	PipelineState		m_pipelineState;		//�p�C�v���C���X�e�[�g�B
	Shader				m_vs;					//���_�V�F�[�_�[�B
	Shader				m_ps;					//�s�N�Z���V�F�[�_�[�B
	bool				m_isInited = false;		//�������ς݁H
};