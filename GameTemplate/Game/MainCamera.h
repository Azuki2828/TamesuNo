#pragma once
#include "../../MiniEngine/SpringCamera.h"

namespace nsMyGame {

	//メインカメラクラス
	class CMainCamera : public CIGameObject
	{
	private:
		/**
		 * @brief 最初に一度だけ呼ばれる関数。
		 * @return 成功した？
		*/
		bool Start()override final;

		/**
		 * @brief 更新関数。
		*/
		void Update()override final;

		/**
		 * @brief 初期化関数。
		*/
		void Init();
	private:
		SpringCamera m_springCamera;			//ばねカメラ
		CVector3 m_position = CVector3::Zero;	//視点
		CVector3 m_target = CVector3::Zero;		//注視点
	};
}

