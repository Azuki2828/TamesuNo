#include "stdafx.h"
#include "system/system.h"
#include "Game.h"

namespace nsMyGame {

	BOOL APIENTRY DllMain(HMODULE hModule,
		DWORD  ul_reason_for_call,
		LPVOID lpReserved
	)
	{
		switch (ul_reason_for_call)
		{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
		}
		return TRUE;
	}

	/**
	 * @brief Python�̏������B
	*/
	void InitPython(wchar_t*& program)
	{
		program = Py_DecodeLocale("MyGame", nullptr);
		// ���W���[���̃p�X��ݒ�B
#ifdef MASTER
		Py_SetPath(L"./Python37_64/DLLs;./Python37_64/Lib;./EnemyState;./");
#else
#ifdef MY_DEBUG
		Py_SetPath(L"./Python37_64/DLLs;./Python37_64/Lib;./EnemyState;../x64/Debug/;./");
#else
		Py_SetPath(L"./Python37_64/DLLs;./Python37_64/Lib;./EnemyState;../x64/Release/;./");
#endif
#endif
		Py_SetProgramName(program);
		Py_Initialize();
	}
	/**
	 * @brief Python�̏I�������B
	*/
	void FinalPython(wchar_t* program)
	{
		Py_Finalize();
		PyMem_RawFree(program);
	}

	/**
	 * @brief �l�X�ȃC���X�^���X���쐬����֐��B
	*/
	void CreateInstance();

	/**
	 * @brief BGM��SE���ꊇ���[�h����֐��B
	*/
	void InitBGMAndSE();

	///////////////////////////////////////////////////////////////////
	// �E�B���h�E�v���O�����̃��C���֐��B
	///////////////////////////////////////////////////////////////////
	extern "C" __declspec(dllexport) int WINAPI AppMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
	{
		//�Q�[���̏������B
		InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

		// python���������B
		wchar_t* program;
		InitPython(program);

		//////////////////////////////////////
		// �������珉�������s���R�[�h���L�q����B
		//////////////////////////////////////

		//�l�X�ȃC���X�^���X���쐬����B
		CreateInstance();

		//BGM��SE���ꊇ���[�h�B
		InitBGMAndSE();

		//���C���[�t���[���\����ON�ɂ���B
		//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

		////////////////////////////////////////////////
		// ���������s���R�[�h�������̂͂����܂�
		////////////////////////////////////////////////
		
		//�^�C�g����ʂ���n�܂�B
		NewGO<CGame>(enPriority_Zeroth);

		// ��������Q�[�����[�v�B
		while (DispatchWindowMessage())
		{
			//�����_�����O�J�n�B
			g_engine->BeginFrame();

			//�Q�[���I�u�W�F�N�g���X�V�B
			CGameObjectManager::GetInstance()->ExecuteUpdate();

			//�G�t�F�N�g�G���W�����X�V�B
			EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());

			//���C�g���X�V�B
			nsLight::CLightManager::GetInstance()->Update();

			//�`��B
			CRenderingEngine::GetInstance()->Render();

			//�����_�����O�I���B
			g_engine->EndFrame();
		}

		//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
		CGameObjectManager::DeleteInstance();

		// python�̏I�������B
		FinalPython(program);

		return 0;
	}

	void CreateInstance() {

		CGameObjectManager::CreateInstance();				//�Q�[���I�u�W�F�N�g�Ǘ��N���X
		CPhysicsWorld::CreateInstance();					//�������[���h
		CSoundEngine::CreateInstance();						//�T�E���h�G���W��
		nsLight::CLightManager::CreateInstance();			//���C�g�Ǘ��N���X
		CCamera::CreateLightCamera();						//���C�g�J����
		CRenderingEngine::CreateRenderingEngine();			//�����_�����O�G���W��
		EffectEngine::CreateInstance();						//�G�t�F�N�g�G���W��
		CSoundManager::CreateInstance();					//�T�E���h�G���W��
		//NewGO<CFade>(enPriority_Zeroth, c_classNameFade);	//�t�F�[�h
	}

	void InitBGMAndSE() {

		//CSoundManager::GetInstance()->Init(c_filePathBGM_Boss, enBGM_Boss, true, SoundType::Type_BGM);
		//CSoundManager::GetInstance()->SetSoundSourceVolume(enBGM_Boss, 0.5f);
	}
}

