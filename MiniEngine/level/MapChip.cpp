#include "stdafx.h"
#include "MapChip.h"
#include "Level.h"
#include "Material.h"


namespace nsMyGame {

	struct LevelObjectData;

	MapChip::MapChip(const LevelObjectData& objData) {

		char objName[256];
		wcstombs(objName, objData.name, 256);

		//ファイルパスを決定。
		char filePathtkm[c_nameSize];
		sprintf(filePathtkm, "Assets/modelData/backGround/%s.tkm", objName);

		//モデルを生成。
		m_modelRender = NewGO<CModelRender>(enPriority_Zeroth);

		//ファイルパスを指定。
		m_modelRender->SetFilePathTkm(filePathtkm);

		//シャドウレシーバーフラグを設定。
		m_modelRender->SetShadowReceiverFlag(true);

		//初期化。
		m_modelRender->Init();

		//各パラメータを設定。
		m_modelRender->SetPosition(objData.position);	//座標
		m_modelRender->SetRotation(objData.rotation);	//回転
		m_modelRender->SetScale(objData.scale);			//拡大

		//パラメータを更新。
		m_modelRender->UpdateWorldMatrix();

		//コリジョンを生成。
		m_physicsStaticObject.CreateFromModel(
			*m_modelRender->GetModel(),
			m_modelRender->GetModel()->GetWorldMatrix()
		);

		//摩擦を設定。
		m_physicsStaticObject.SetFriction(10.0f);
	}

	MapChip::~MapChip() {
		if (m_modelRender != nullptr) {
			DeleteGO(m_modelRender);
			m_modelRender = nullptr;
		}
	}

	void MapChip::Draw(CRenderContext& rc) {
		//Draw(rc,
		//	m_skinModelRender->GetModel()->GetWorldMatrix(),
		//	g_camera3D->GetViewMatrix(),
		//	g_camera3D->GetProjectionMatrix());

	}

	void MapChip::Draw(CRenderContext& rc,
		const CMatrix& mWorld,
		const CMatrix& mView,
		const CMatrix& mProj) {
		//メッシュごとにドロー
		//プリミティブのトポロジーはトライアングルリストのみ。
		rc.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//定数バッファを更新する。
		MConstantBuffer cb;
		cb.mWorld = mWorld;
		cb.mView = mView;
		cb.mProj = mProj;

		m_constantBuffer.CopyToVRAM(&cb);

		//if (m_expandData) {
		//	m_expandConstantBuffer.CopyToVRAM(m_expandData);
		//}
		//if (m_boneMatricesStructureBuffer.IsInited()) {
		//	//ボーン行列を更新する。
		//	m_boneMatricesStructureBuffer.Update(m_skeleton->GetBoneMatricesTopAddress());
		//}
		int descriptorHeapNo = 0;
		for (auto& mesh : m_meshs) {
			//1. 頂点バッファを設定。
			rc.SetVertexBuffer(mesh->m_vertexBuffer);
			//マテリアルごとにドロー。
			for (int matNo = 0; matNo < mesh->m_materials.size(); matNo++) {
				//このマテリアルが貼られているメッシュの描画開始。
				mesh->m_materials[matNo]->BeginRender(rc, mesh->skinFlags[matNo]);
				//2. ディスクリプタヒープを設定。
				rc.SetDescriptorHeap(m_descriptorHeap.at(descriptorHeapNo));
				//3. インデックスバッファを設定。
				auto& ib = mesh->m_indexBufferArray[matNo];
				rc.SetIndexBuffer(*ib);

				//4. ドローコールを実行。
				rc.DrawIndexed(ib->GetCount());
				descriptorHeapNo++;
			}
		}
	}
}