#pragma once

namespace nsMyGame {

	//タイトルクラス
	class CTitle : public CIGameObject
	{
	private:
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

	private:
		CSpriteRender* m_backSprite = nullptr;		//背景画像
		
	};
}

