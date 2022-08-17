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
	 * @brief Pythonの初期化。
	*/
	void InitPython(wchar_t*& program)
	{
		program = Py_DecodeLocale("MyGame", nullptr);
		// モジュールのパスを設定。
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
	 * @brief Pythonの終了処理。
	*/
	void FinalPython(wchar_t* program)
	{
		Py_Finalize();
		PyMem_RawFree(program);
	}

	/**
	 * @brief 様々なインスタンスを作成する関数。
	*/
	void CreateInstance();

	/**
	 * @brief BGMとSEを一括ロードする関数。
	*/
	void InitBGMAndSE();

	///////////////////////////////////////////////////////////////////
	// ウィンドウプログラムのメイン関数。
	///////////////////////////////////////////////////////////////////
	extern "C" __declspec(dllexport) int WINAPI AppMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
	{
		//ゲームの初期化。
		InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

		// pythonを初期化。
		wchar_t* program;
		InitPython(program);

		//////////////////////////////////////
		// ここから初期化を行うコードを記述する。
		//////////////////////////////////////

		//様々なインスタンスを作成する。
		CreateInstance();

		//BGMとSEを一括ロード。
		InitBGMAndSE();

		//ワイヤーフレーム表示をONにする。
		//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

		////////////////////////////////////////////////
		// 初期化を行うコードを書くのはここまで
		////////////////////////////////////////////////
		
		//タイトル画面から始まる。
		NewGO<CGame>(enPriority_Zeroth);

		// ここからゲームループ。
		while (DispatchWindowMessage())
		{
			//レンダリング開始。
			g_engine->BeginFrame();

			//ゲームオブジェクトを更新。
			CGameObjectManager::GetInstance()->ExecuteUpdate();

			//エフェクトエンジンを更新。
			EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());

			//ライトを更新。
			nsLight::CLightManager::GetInstance()->Update();

			//描画。
			CRenderingEngine::GetInstance()->Render();

			//レンダリング終了。
			g_engine->EndFrame();
		}

		//ゲームオブジェクトマネージャーを削除。
		CGameObjectManager::DeleteInstance();

		// pythonの終了処理。
		FinalPython(program);

		return 0;
	}

	void CreateInstance() {

		CGameObjectManager::CreateInstance();				//ゲームオブジェクト管理クラス
		CPhysicsWorld::CreateInstance();					//物理ワールド
		CSoundEngine::CreateInstance();						//サウンドエンジン
		nsLight::CLightManager::CreateInstance();			//ライト管理クラス
		CCamera::CreateLightCamera();						//ライトカメラ
		CRenderingEngine::CreateRenderingEngine();			//レンダリングエンジン
		EffectEngine::CreateInstance();						//エフェクトエンジン
		CSoundManager::CreateInstance();					//サウンドエンジン
		//NewGO<CFade>(enPriority_Zeroth, c_classNameFade);	//フェード
	}

	void InitBGMAndSE() {

		//CSoundManager::GetInstance()->Init(c_filePathBGM_Boss, enBGM_Boss, true, SoundType::Type_BGM);
		//CSoundManager::GetInstance()->SetSoundSourceVolume(enBGM_Boss, 0.5f);
	}
}

