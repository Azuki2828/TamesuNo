#pragma once

#include "physics/PhysicsStaticObject.h"


namespace nsMyGame {

	struct LevelObjectData;

	class Material;

	class MapChip
	{
	public:
		MapChip(const LevelObjectData& objData);
		~MapChip();
		void Draw(CRenderContext& rc);
		void Draw(CRenderContext& rc,
			const CMatrix& mWorld,
			const CMatrix& mView,
			const CMatrix& mProj);

	private:

		struct MConstantBuffer {
			CMatrix mWorld;		//���[���h�s��B
			CMatrix mView;		//�r���[�s��B
			CMatrix mProj;		//�v���W�F�N�V�����s��B
		};
		ConstantBuffer m_constantBuffer;					//�萔�o�b�t�@�B
		//PhysicsStaticObject m_physicsStaticObject;

		std::vector< SMesh* > m_meshs;							//���b�V���B
		std::vector< DescriptorHeap > m_descriptorHeap;		//�f�B�X�N���v�^�q�[�v�B

		CModelRender* m_modelRender = nullptr;
		PhysicsStaticObject m_physicsStaticObject;
	};
}

