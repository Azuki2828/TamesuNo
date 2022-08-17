#include "stdafx.h"
#include "RenderingEngine.h"

namespace nsMyGame {

	//�����_�����O�G���W���̃C���X�^���X
	CRenderingEngine* CRenderingEngine::m_renderingEngine = nullptr;

	void CRenderingEngine::Init() {

		//�����_�����O�^�[�Q�b�g���쐬�B
		CreateRenderTarget();

		//�V���h�E�}�b�v��p�ӁB
		m_shadowMap.Init();

		//�|�X�g�G�t�F�N�g���������B
		m_postEffect.Init();

		//���C�g�J�����O���������B
		m_lightCulling.Init();

		//�X�J�C�L���[�u���������B
		InitSkyCube();

		//�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g���������B
		InitDeferredLightingSprite();

		//���C�������_�����O�^�[�Q�b�g�̃X�v���C�g���������B
		InitCopyToMainRenderTargetSprite();
	}

	void CRenderingEngine::Render() {

		//���C�g�����X�V�B
		m_deferredLightingCB.ligData = *nsLight::CLightManager::GetInstance()->GetLigData();

		//�����_�[�R���e�L�X�g���擾�B
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		//�V���h�E�}�b�v���쐬�B
		DrawShadowMap(renderContext);

		//G-Buffer���쐬�B
		CreateGBuffer(renderContext);

		//���C�g�J�����O�B
		m_lightCulling.Execute(renderContext);

		//�f�B�t�@�[�h���C�e�B���O(TBDR)�B
		ExecuteDeferredLighting(renderContext);

		//���C�������_�����O�^�[�Q�b�g�̊G���X�i�b�v�V���b�g�B
		SnapShotMainRenderTarget(renderContext);

		//�t�H���[�h�����_�����O�B
		ExecuteForwardRendering(renderContext);

		//�|�X�g�G�t�F�N�g�B
		m_postEffect.Render(renderContext);

		//�G�t�F�N�g���f����`��B
		DrawEffect(renderContext);

		//�X�v���C�g��`��B
		RenderSprite(renderContext);

		//�t�H���g��`��B
		DrawFont(renderContext);

		//���C���[�t���[����`��B
		DrawWireFrame(renderContext);

		//�t���[���o�b�t�@�ɕ`��B
		CopyToFrameBuffer(renderContext);
	}

	void CRenderingEngine::InitIbl(const wchar_t* iblTexFilePath, float luminance) {

		//IBL�̃f�[�^���������B
		InitIblData(iblTexFilePath, luminance);
	}

	void CRenderingEngine::CreateRenderTarget() {

		//�����_�����O�^�[�Q�b�g���쐬�B
		CRenderTarget::CreateMainRenderTarget();
		CRenderTarget::CreateAlbedoAndShadowReceiverFlagRenderTarget();
		CRenderTarget::CreateNormalMapRenderTarget();
		CRenderTarget::CreateWorldPosRenderTarget();
		CRenderTarget::CreateSpecularRenderTarget();
		CRenderTarget::CreateDepthRenderTarget();
		CreateSnapShotMainRT();
	}

	void CRenderingEngine::InitDeferredLightingSprite() {

		//�f�B�t�@�[�h�����_�����O�ɕK�v�ȃf�[�^��ݒ肷��B
		SpriteInitData spriteInitData;

		int texNo = 0;

		spriteInitData.m_textures[texNo++] = &CRenderTarget::GetGBufferRT(enAlbedoAndShadowReceiverFlgMap)->GetRenderTargetTexture();
		spriteInitData.m_textures[texNo++] = &CRenderTarget::GetGBufferRT(enNormalMap)->GetRenderTargetTexture();
		spriteInitData.m_textures[texNo++] = &CRenderTarget::GetGBufferRT(enWorldPosMap)->GetRenderTargetTexture();
		spriteInitData.m_textures[texNo++] = &CRenderTarget::GetGBufferRT(enDepthMap)->GetRenderTargetTexture();
		spriteInitData.m_textures[texNo++] = &CRenderTarget::GetGBufferRT(enocclusionAndSmoothAndMetaricMap)->GetRenderTargetTexture();
		spriteInitData.m_width = c_renderTargetW1280H720.x;
		spriteInitData.m_height = c_renderTargetW1280H720.y;
		spriteInitData.m_fxFilePath = c_fxFilePath_DeferredLighting;
		m_deferredLightingCB.ligData = *nsLight::CLightManager::GetInstance()->GetLigData();

		if (m_iblData.texture.IsValid()) {
			spriteInitData.m_textures[texNo++] = &m_iblData.texture;
			m_deferredLightingCB.isIbl = 1;
			m_deferredLightingCB.iblLuminance = m_iblData.luminance;
		}
		spriteInitData.m_expandConstantBuffer = &m_deferredLightingCB;
		spriteInitData.m_expandConstantBufferSize = sizeof(m_deferredLightingCB);
		spriteInitData.m_expandShaderResoruceView = &m_shadowMap.GetBokeShadowTexture();
		spriteInitData.m_expandShaderResoruceView2 = &m_lightCulling.GetPointLightNoListInTileUAV();

		// �������I�u�W�F�N�g���g���āA�X�v���C�g������������
		m_deferredLightingSprite.Init(spriteInitData);
	}

	void CRenderingEngine::CreateSnapShotMainRT() {

		//���C�������_�����O�^�[�Q�b�g�̓��e���R�s�[���郌���_�����O�^�[�Q�b�g���쐬�B
		m_snapShotMainRT.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN
		);
	}

	void CRenderingEngine::InitCopyToMainRenderTargetSprite() {

		SpriteInitData copyToMainRenderTargetSpriteInitData;

		//�e�N�X�`���ɂ̓��C�������_�����O�^�[�Q�b�g�̃e�N�X�`���J���[���w��B
		copyToMainRenderTargetSpriteInitData.m_textures[0] = &CRenderTarget::GetRenderTarget(enMainRT)->GetRenderTargetTexture();
		copyToMainRenderTargetSpriteInitData.m_width = c_renderTargetW1280H720.x;
		copyToMainRenderTargetSpriteInitData.m_height = c_renderTargetW1280H720.y;
		copyToMainRenderTargetSpriteInitData.m_fxFilePath = c_fxFilePath_Sprite;
		copyToMainRenderTargetSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

		m_copyToMainRenderTargetSprite.Init(copyToMainRenderTargetSpriteInitData);
	}

	void CRenderingEngine::InitIblData(const wchar_t* iblTexFilePath, float luminance) {

		m_iblData.texture.InitFromDDSFile(iblTexFilePath);
		m_iblData.luminance = luminance;
	}

	void CRenderingEngine::InitSkyCube() {

		auto skyCube = NewGO<SkyCube>(enPriority_Zeroth, c_classNameSkyCube);

		skyCube->SetLuminance(c_skyCubeLumminance);

		skyCube->SetType(enSkyCubeType_NightToon_2);

		// �����̌v�Z�̂��߂�IBL�e�N�X�`�����Z�b�g����B
		CRenderingEngine::GetInstance()->InitIbl(skyCube->GetTextureFilePath(), c_skyCubeLumminance);
	}

	void CRenderingEngine::DrawShadowMap(CRenderContext& rc) {

		//�`�惂�[�h���V���h�E�}�b�v�p�ɐݒ肷��B
		rc.SetRenderMode(CRenderContext::EnRender_Mode::enRenderMode_Shadow);

		//�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂őҋ@�B
		rc.WaitUntilToPossibleSetRenderTarget(m_shadowMap.GetRenderTarget());

		//�����_�[�^�[�Q�b�g�ƃr���[�|�[�g��ݒ�B
		rc.SetRenderTargetAndViewport(m_shadowMap.GetRenderTarget());

		//�����_�[�^�[�Q�b�g���N���A�B
		rc.ClearRenderTargetView(m_shadowMap.GetRenderTarget());

		//�V���h�E���f����`��B
		CGameObjectManager::GetInstance()->ExecuteRender(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMap.GetRenderTarget());

		//�V���h�E�}�b�v�Ƀu���[��������B
		m_shadowMap.ExecuteBlur(rc);
	}

	void CRenderingEngine::RenderSprite(CRenderContext& rc) {

		//�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂őҋ@�B
		rc.WaitUntilToPossibleSetRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));

		//�����_�[�^�[�Q�b�g�ƃr���[�|�[�g��ݒ�B
		rc.SetRenderTargetAndViewport(*CRenderTarget::GetRenderTarget(enMainRT));

		//2D���f����`��B
		CGameObjectManager::GetInstance()->Execute2DRender(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));
	}

	void CRenderingEngine::DrawFont(CRenderContext& rc) {

		//�����_�[���[�h���t�H���g�p�ɂ���B
		rc.SetRenderMode(CRenderContext::EnRender_Mode::enRenderMode_Font);

		//�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂őҋ@�B
		rc.WaitUntilToPossibleSetRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));

		//�����_�[�^�[�Q�b�g�ƃr���[�|�[�g��ݒ�B
		rc.SetRenderTargetAndViewport(*CRenderTarget::GetRenderTarget(enMainRT));

		//�t�H���g��`��B
		CGameObjectManager::GetInstance()->ExecuteRender(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));
	}

	void CRenderingEngine::DrawEffect(CRenderContext& rc) {

		//�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂őҋ@�B
		rc.WaitUntilToPossibleSetRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));
		
		//�����_�[�^�[�Q�b�g��ݒ�B
		rc.SetRenderTarget(
			CRenderTarget::GetRenderTarget(enMainRT)->GetRTVCpuDescriptorHandle(),
			CRenderTarget::GetGBufferRT(enAlbedoAndShadowReceiverFlgMap)->GetDSVCpuDescriptorHandle()
		);

		//�r���[�|�[�g��ݒ�B
		D3D12_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<float>(CRenderTarget::GetRenderTarget(enMainRT)->GetWidth());
		viewport.Height = static_cast<float>(CRenderTarget::GetRenderTarget(enMainRT)->GetHeight());
		viewport.MinDepth = D3D12_MIN_DEPTH;
		viewport.MaxDepth = D3D12_MAX_DEPTH;
		rc.SetViewportAndScissor(viewport);

		//�G�t�F�N�g��`��B
		EffectEngine::GetInstance()->Draw();

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));
	}

	void CRenderingEngine::DrawWireFrame(CRenderContext& rc) {

		//�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂őҋ@�B
		rc.WaitUntilToPossibleSetRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));

		//�����_�[�^�[�Q�b�g��ݒ�B
		rc.SetRenderTarget(
			CRenderTarget::GetRenderTarget(enMainRT)->GetRTVCpuDescriptorHandle(),
			CRenderTarget::GetGBufferRT(enAlbedoAndShadowReceiverFlgMap)->GetDSVCpuDescriptorHandle()
		);

		//���C���[�t���[����`��B
		CPhysicsWorld::GetInstance()->DebubDrawWorld(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));
	}

	void CRenderingEngine::CreateGBuffer(CRenderContext& rc) {

		//�����_�����O�^�[�Q�b�g���쐬�B
		CRenderTarget* rts[] = {
				CRenderTarget::GetGBufferRT(enAlbedoAndShadowReceiverFlgMap),   // 0�Ԗڂ̃����_�����O�^�[�Q�b�g
				CRenderTarget::GetGBufferRT(enNormalMap),  // 1�Ԗڂ̃����_�����O�^�[�Q�b�g
				CRenderTarget::GetGBufferRT(enWorldPosMap), // 2�Ԗڂ̃����_�����O�^�[�Q�b�g
				CRenderTarget::GetGBufferRT(enDepthMap), // 3�Ԗڂ̃����_�����O�^�[�Q�b�g
				CRenderTarget::GetGBufferRT(enocclusionAndSmoothAndMetaricMap) // 4�Ԗڂ̃����_�����O�^�[�Q�b�g
		};

		//�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂őҋ@�B
		rc.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(rts), rts);

		//�����_�[�^�[�Q�b�g��ݒ�B
		rc.SetRenderTargets(ARRAYSIZE(rts), rts);

		//�r���[�|�[�g��ݒ�B
		D3D12_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		//�A���x�h�}�b�v�Ɠ������ƍ����ɐݒ肷��B
		viewport.Width = static_cast<float>(rts[0]->GetWidth());
		viewport.Height = static_cast<float>(rts[0]->GetHeight());
		viewport.MinDepth = D3D12_MIN_DEPTH;
		viewport.MaxDepth = D3D12_MAX_DEPTH;
		rc.SetViewportAndScissor(viewport);

		// �����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetViews(ARRAYSIZE(rts), rts);

		//���f���̕`��
		rc.SetRenderMode(CRenderContext::EnRender_Mode::enRenderMode_Normal);
		CGameObjectManager::GetInstance()->ExecuteRender(rc);

		// �����_�����O�^�[�Q�b�g�ւ̏������ݑ҂�
		rc.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(rts), rts);
	}

	void CRenderingEngine::ExecuteDeferredLighting(CRenderContext& rc) {

		//�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂őҋ@�B
		rc.WaitUntilToPossibleSetRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));

		//�����_�[�^�[�Q�b�g�ƃr���[�|�[�g��ݒ�B
		rc.SetRenderTargetAndViewport(*CRenderTarget::GetRenderTarget(enMainRT));

		//�f�B�t�@�[�h���C�e�B���O�B
		m_deferredLightingSprite.Draw(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));
	}

	void CRenderingEngine::ExecuteForwardRendering(CRenderContext& rc) {

		//�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂őҋ@�B
		rc.WaitUntilToPossibleSetRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));

		//�����_�����O�^�[�Q�b�g��ݒ�B
		rc.SetRenderTarget(
			CRenderTarget::GetRenderTarget(enMainRT)->GetRTVCpuDescriptorHandle(),
			CRenderTarget::GetGBufferRT(enAlbedoAndShadowReceiverFlgMap)->GetDSVCpuDescriptorHandle()
		);

		//�t�H���[�h�����_�����O�B
		CGameObjectManager::GetInstance()->ExecuteForwardRender(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(*CRenderTarget::GetRenderTarget(enMainRT));
	}

	void CRenderingEngine::SnapShotMainRenderTarget(CRenderContext& rc) {

		//�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂őҋ@�B
		rc.WaitUntilToPossibleSetRenderTarget(m_snapShotMainRT);

		//�����_�[�^�[�Q�b�g�ƃr���[�|�[�g��ݒ�B
		rc.SetRenderTargetAndViewport(m_snapShotMainRT);

		//���C�������_�����O�^�[�Q�b�g�̊G���X�i�b�v�V���b�g�B
		m_copyToMainRenderTargetSprite.Draw(rc);

		//�`�����ݏI���҂��B
		rc.WaitUntilFinishDrawingToRenderTarget(m_snapShotMainRT);
	}

	void CRenderingEngine::CopyToFrameBuffer(CRenderContext& rc) {

		//���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		
		//�ŏI�X�v���C�g��`��B
		m_copyToMainRenderTargetSprite.Draw(rc);
	}
}