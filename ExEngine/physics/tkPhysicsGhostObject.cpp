/*!
 * @brief	�ÓI�I�u�W�F�N�g�B
 */

#include "stdafx.h"
#include "physics/tkPhysicsGhostObject.h"
#include "physics/BoxCollider.h"
#include "physics/SphereCollider.h"

using namespace std;

	void CPhysicsGhostObject::Release()
	{
		if (m_isRegistPhysicsWorld == true) {
			CPhysicsWorld::GetInstance()->RemoveCollisionObject(m_ghostObject);
			m_isRegistPhysicsWorld = false;
		}
	}
	void CPhysicsGhostObject::CreateCommon(CVector3 pos, CQuaternion rot)
	{
		m_ghostObject.setCollisionShape(m_collider->GetBody());
		btTransform btTrans;
		btTrans.setOrigin({ pos.x, pos.y, pos.z });
		btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
		m_ghostObject.setWorldTransform(btTrans);

		//�����G���W���ɓo�^�B
		CPhysicsWorld::GetInstance()->AddCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = true;
	}
