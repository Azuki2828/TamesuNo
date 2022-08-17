#pragma once

namespace nsMyGame {

	//ボタンクラス
	class CButton : public CIGameObject
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

	public:
		/**
		 * @brief 初期化関数。
		*/
		void Init(const char* filePathTkm);

		/**
		 * @brief 座標を設定する関数。
		 * @param position 座標
		*/
		void SetPosition(const CVector3& position) {

			m_position = position;
		}

		/**
		 * @brief 拡大率を設定する関数。
		 * @param scale 拡大率
		*/
		void SetScale(const CVector3& scale) {

			m_modelRender->SetScale(scale);
		}
	private:
		CModelRender* m_modelRender = nullptr;		//モデルレンダー
		CVector3 m_position = CVector3::Zero;		//座標
	};
}

