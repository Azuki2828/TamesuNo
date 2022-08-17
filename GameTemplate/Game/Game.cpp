#include "stdafx.h"
#include "Game.h"
#include "Button.h"
#include "Title.h"
#include "MainCamera.h"

namespace nsMyGame {

	namespace {

		const CVector3 c_buttonRedPosition = { -100.0f,100.0f,100.0f };			//赤ボタンの座標
		const CVector3 c_buttonBluePosition = { 100.0f,100.0f,100.0f };			//青ボタンの座標
		const CVector3 c_buttonYellowPosition = { -100.0f,100.0f,-100.0f };		//黄ボタンの座標
		const CVector3 c_buttonGreenPosition = { 100.0f,100.0f,-100.0f };		//緑ボタンの座標
	}
	bool CGame::Start() {

		//タイトル画面を作成。
		m_title = NewGO<CTitle>(enPriority_Zeroth);

		//メインカメラを作成。
		m_mainCamera = NewGO<CMainCamera>(enPriority_Zeroth);

		//各ボタンを作成。
		for (int buttonNum = 0; buttonNum < enButton_Num; buttonNum++) {

			m_button[buttonNum] = NewGO<CButton>(enPriority_First);
			m_button[buttonNum]->Init(GetTkmFilePath(buttonNum));
		}

		//各ボタンの座標を設定。
		m_button[enButton_Red]->SetPosition(c_buttonRedPosition);
		m_button[enButton_Blue]->SetPosition(c_buttonBluePosition);
		m_button[enButton_Yellow]->SetPosition(c_buttonYellowPosition);
		m_button[enButton_Green]->SetPosition(c_buttonGreenPosition);

		return true;
	}

	void CGame::OnDestroy() {

		//タイトルを削除。
		DeleteGO(m_title);
		m_title = nullptr;

		//メインカメラを削除。
		DeleteGO(m_mainCamera);
		m_mainCamera = nullptr;

		//ボタンを削除。
		for (int buttonNum = 0; buttonNum < enButton_Num; buttonNum++) {
			DeleteGO(m_button[buttonNum]);
			m_button[buttonNum] = nullptr;
		}
	}

	void CGame::Update() {


	}

	const char* CGame::GetTkmFilePath(const int buttonNum)
	{
		const char* tkmFilePath = nullptr;

		//ボタン番号からtkmファイルパスを取得。
		switch (static_cast<EnButton>(buttonNum)) {

		case enButton_Red:
			tkmFilePath = "Assets/modelData/button/button_Red.tkm";
			break;
		case enButton_Blue:
			tkmFilePath = "Assets/modelData/button/button_Blue.tkm";
			break;
		case enButton_Yellow:
			tkmFilePath = "Assets/modelData/button/button_Yellow.tkm";
			break;
		case enButton_Green:
			tkmFilePath = "Assets/modelData/button/button_Green.tkm";
			break;
		default:
			//取得失敗。
			MessageBox(nullptr, L"ファイルパスの取得に失敗しました。", L"エラー", MB_OK);
			break;
		}

		//取得したパスを返す。
		return tkmFilePath;
	}
}