#pragma once

#include <memory>
#include "DebugWireframe.h"
#include "CharacterController.h"
class CharacterController;

class CPhysicsWorld
{
	static CPhysicsWorld* m_instance;	//�B��̃C���X�^���X�B
	std::unique_ptr<btDefaultCollisionConfiguration> 	 m_collisionConfig;
	std::unique_ptr<btCollisionDispatcher>				 m_collisionDispatcher;	//!<�Փˉ��������B
	std::unique_ptr<btBroadphaseInterface>				 m_overlappingPairCache;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
	std::unique_ptr<btSequentialImpulseConstraintSolver> m_constraintSolver;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
	std::unique_ptr<btDiscreteDynamicsWorld>			 m_dynamicWorld;			//!<���[���h�B

	DebugWireframe m_debugWireFrame;
	bool m_isDrawDebugWireFrame = false;

#if BUILD_LEVEL!=BUILD_LEVEL_MASTER
	CPhysicsDebugDraw									 m_debugDraw;
#endif

public:
	static void CreateInstance()
	{
		m_instance = new CPhysicsWorld();
	}
	static CPhysicsWorld* GetInstance()
	{
		return m_instance;
	}
	static void DeleteInstance()
	{
		delete m_instance;
	}
	
	void Update(float deltaTime);
	void DebubDrawWorld(CRenderContext& rc);

	//�����蔻��`���L���ɂ���B
	void EnableDrawDebugWireFrame()
	{

		m_isDrawDebugWireFrame = true;

	}

	//�����蔻��`��𖳌��ɂ���B
	void DisableDrawDebugWireFrame()
	{

		m_isDrawDebugWireFrame = false;

	}

	void Release();
	/*!
	* @brief	�d�͂�ݒ�B�B
	*/
	void SetGravity(CVector3 g)
	{
		m_dynamicWorld->setGravity(btVector3(g.x, g.y, g.z));
	}
	/*!
	* @brief	�_�C�i�~�b�N���[���h���擾�B
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return m_dynamicWorld.get();
	}

	/*!
	* @brief	���̂�o�^�B
	*/
	void AddRigidBody(RigidBody& rb)
	{
		m_dynamicWorld->addRigidBody(rb.GetBody());
	}

	
	/*!
	* @brief	���̂�j���B
	*/
	void RemoveRigidBody(RigidBody& rb)
	{
		m_dynamicWorld->removeRigidBody(rb.GetBody());
	}
	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f
	)
	{
		m_dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
#if 1
	/*!
	* @brief	�R���W�����I�u�W�F�N�g�����[���h�ɓo�^�B
	*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
	*/
	void AddCollisionObject(btCollisionObject& colliObj)
	{
		m_dynamicWorld->addCollisionObject(&colliObj);
	}
	/*!
	* @brief	�R���W�����I�u�W�F�N�g�����[���h����폜�B
	*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
	*/
	void RemoveCollisionObject(btCollisionObject& colliObj)
	{
		m_dynamicWorld->removeCollisionObject(&colliObj);
	}
	
	void ContactTest(
		btCollisionObject* colObj,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
	void ContactTest(
		RigidBody& rb,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
		
	void ContactTest(
		CharacterController& charaCon,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
#endif		
private:
	CPhysicsWorld();
	~CPhysicsWorld();
	void Init();
};
	
