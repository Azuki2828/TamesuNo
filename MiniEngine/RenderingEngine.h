#pragma once
#include "../MiniEngine/postEffect/PostEffect.h"
#include "LightCulling.h"
#include "ShadowMap.h"

namespace nsMyGame {

	//�����_�����O�G���W���N���X
	class CRenderingEngine
	{
		//IBL�̃f�[�^
		struct SIblData {
			Texture texture;
			float luminance = 1.0f;
		};

		//�f�B�t�@�[�h���C�e�B���O�̃f�[�^
		struct SDeferredLightingCB {

			nsLight::LigData ligData;		//���C�g�̃f�[�^
			int isIbl = 0;					//IBL���s���H
			float iblLuminance = 1.0f;		//IBL�̖��邳
		};
	public:
		/**
		 * @brief �����_�����O�G���W�����쐬����֐��B
		*/
		static void CreateRenderingEngine() {

			m_renderingEngine = new CRenderingEngine;

			//�����_�����O�G���W���̏������B
			m_renderingEngine->Init();
		}

		/**
		 * @brief �����_�����O�G���W�����擾����֐��B
		 * @return �����_�����O�G���W��
		*/
		static CRenderingEngine* GetInstance() {

			return m_renderingEngine;
		}

		/**
		 * @brief �V���h�E�}�b�v���擾����֐��B
		 * @return �V���h�E�}�b�v
		*/
		CRenderTarget& GetShadowMap() {

			return m_shadowMap.GetRenderTarget();
		}

		/**
		 * @brief �������֐��B
		*/
		void Init();

		/**
		 * @brief �`��֐��B
		*/
		void Render();

		/**
		 * @brief IBL�̂��߂̏������֐��B
		*/
		void InitIbl(const wchar_t* iblTexFilePath, float luminance);

		/**
		 * @brief �X�J�C�L���[�u�̏������֐��B
		*/
		void InitSkyCube();
	private:
		/**
		 * @brief �����_�����O�^�[�Q�b�g���쐬����֐��B
		*/
		void CreateRenderTarget();

		/**
		 * @brief �f�B�t�@�[�h���C�e�B���O�Ŏg�p����X�v���C�g������������֐��B
		*/
		void InitDeferredLightingSprite();

		/**
		 * @brief ���C�������_�����O�^�[�Q�b�g�̃R�s�[����邽�߂̃����_�[�^�[�Q�b�g���쐬����֐��B
		*/
		void CreateSnapShotMainRT();

		/**
		 * @brief �t���[���o�b�t�@�ɃR�s�[����X�v���C�g���쐬����֐��B
		*/
		void InitCopyToMainRenderTargetSprite();

		/**
		 * @brief IBL�̃f�[�^�̏������֐��B
		*/
		void InitIblData(const wchar_t* iblTexFilePath, float luminance);

		/**
		 * @brief �V���h�E�}�b�v��`�悷��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void DrawShadowMap(CRenderContext& rc);

		/**
		 * @brief �X�v���C�g��`�悷��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void RenderSprite(CRenderContext& rc);

		/**
		 * @brief �t�H���g��`�悷��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void DrawFont(CRenderContext& rc);

		/**
		 * @brief �G�t�F�N�g��`�悷��֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void DrawEffect(CRenderContext& rc);

		/**
		 * @brief ���C���[�t���[����`��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void DrawWireFrame(CRenderContext& rc);

		/**
		 * @brief G-Buffer���쐬����֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void CreateGBuffer(CRenderContext& rc);

		/**
		 * @brief �f�B�t�@�[�h���C�e�B���O�����s����֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void ExecuteDeferredLighting(CRenderContext& rc);

		/**
		 * @brief �t�H���[�h�����_�����O�����s����֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void ExecuteForwardRendering(CRenderContext& rc);

		/**
		 * @brief �t���[���o�b�t�@�p�ɁA���C�������_�����O�^�[�Q�b�g�̓��e���R�s�[����֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void SnapShotMainRenderTarget(CRenderContext& rc);


		/**
		 * @brief �t���[���o�b�t�@�ɃX�v���C�g���R�s�[����֐��B
		 * @param rc �����_�[�R���e�L�X�g
		*/
		void CopyToFrameBuffer(CRenderContext& rc);

	private:
		static CRenderingEngine* m_renderingEngine;	//�����_�����O�G���W���̃C���X�^���X
		CLightCulling m_lightCulling;				//���C�g�J�����O
		CRenderTarget m_snapShotMainRT;				//���C�������_�����O�^�[�Q�b�g�̃X�i�b�v�V���b�g����邽�߂̃����_�����O�^�[�Q�b�g
		nsPostEffect::CPostEffect m_postEffect;		//�|�X�g�G�t�F�N�g
		CShadowMap m_shadowMap;						//�V���h�E�}�b�v
		CSprite m_copyToMainRenderTargetSprite;		//���C�������_�����O�^�[�Q�b�g�̃X�v���C�g
		CSprite m_deferredLightingSprite;			//�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g
		SIblData m_iblData;							//IBL�̃f�[�^
		SDeferredLightingCB m_deferredLightingCB;	//�f�B�t�@�[�h���C�e�B���O�Ɏg�p����萔�o�b�t�@
	};
}

