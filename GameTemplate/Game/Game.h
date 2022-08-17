#pragma once

namespace nsMyGame {

	class CTitle;
	class CMainCamera;
	class CButton;

	//ゲームクラス
	class CGame: public CIGameObject
	{
	private:

		//ボタンの種類
		enum EnButton {
			enButton_Red,		//赤ボタン
			enButton_Blue,		//青ボタン
			enButton_Yellow,	//黄ボタン
			enButton_Green,		//緑ボタン

			enButton_Num
		};
		/**
		 * @brief 最初に一度だけ呼ばれる関数。
		 * @return 成功した？
		*/
		bool Start()override final;

		/**
		 * @brief 削除関数。
		*/
		void OnDestroy()override final;

		/**
		 * @brief 更新関数。
		*/
		void Update()override final;

		/**
		 * @brief ボタンのtkmファイルのファイルパスを取得する関数。
		 * @param buttonNum ボタン番号
		 * @return ボタンのtkmファイルのファイルパス
		*/
		const char* GetTkmFilePath(const int buttonNum);
	private:

		CButton* m_button[enButton_Num] = { nullptr };	//ボタンクラス
		CTitle* m_title = nullptr;						//タイトルクラス
		CMainCamera* m_mainCamera = nullptr;		//メインカメラ
		nsLight::CDirectionLight* m_directionLight = nullptr;	//ディレクションライト
	};
}

