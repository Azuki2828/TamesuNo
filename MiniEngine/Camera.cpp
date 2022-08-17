/*!
* @brief	�J����
*/
#include "stdafx.h"
#include "Camera.h"

CCamera* CCamera::m_lightCamera = nullptr;

void CCamera::Update()
{
	//�A�X�y�N�g����v�Z����B
	m_aspect = (float)g_graphicsEngine->GetFrameBufferWidth() / (float)g_graphicsEngine->GetFrameBufferHeight();
	if(m_isNeedUpdateProjectionMatrix){
		if (m_updateProjMatrixFunc == enUpdateProjMatrixFunc_Perspective) {
			//�����ϊ��s����v�Z�B
			m_projectionMatrix.MakeProjectionMatrix(
				m_viewAngle,
				m_aspect,
				m_near,
				m_far
			);
		}
		else {
			//���s���e�s����v�Z�B
			m_projectionMatrix.MakeOrthoProjectionMatrix(m_width, m_height, m_near, m_far);
		}
	}
	//�r���[�s��̎Z�o
	m_viewMatrix.MakeLookAt( m_position, m_target, m_up );
	//�r���[�v���W�F�N�V�����s��̍쐬�B
	m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
	//�r���[�s��̋t�s����v�Z�B
	m_viewMatrixInv.Inverse( m_viewMatrix );

	m_forward.Set(m_viewMatrixInv.m[2][0], m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2]);
	m_right.Set(m_viewMatrixInv.m[0][0], m_viewMatrixInv.m[0][1], m_viewMatrixInv.m[0][2]);
	//�J�����̉�]�s����擾�B
	m_cameraRotation = m_viewMatrixInv;
	m_cameraRotation.m[3][0] = 0.0f;
	m_cameraRotation.m[3][1] = 0.0f;
	m_cameraRotation.m[3][2] = 0.0f;
	m_cameraRotation.m[3][3] = 1.0f;

	CVector3 toPos;
	toPos.Subtract(m_position, m_target);
	m_targetToPositionLen = toPos.Length();

	m_isDirty = false;
}
void CCamera::CalcScreenPositionFromWorldPosition(CVector2& screenPos, const CVector3& worldPos) const
{
	float half_w = (float)g_graphicsEngine->GetFrameBufferWidth() * 0.5f;
	float half_h = (float)g_graphicsEngine->GetFrameBufferHeight() * 0.5f;
	CVector4 _screenPos;
	_screenPos.Set(worldPos.x, worldPos.y, worldPos.z, 1.0f);
	m_viewProjectionMatrix.Apply(_screenPos);
	screenPos.x = (_screenPos.x / _screenPos.w)*half_w;
	screenPos.y = (_screenPos.y / _screenPos.w)*half_h;
}
void CCamera::RotateOriginTarget(const CQuaternion& qRot)
{
	CVector3 cameraPos = m_position;
	CVector3 cameraTarget = m_target;
	CVector3 toPos = cameraPos - cameraTarget;
	qRot.Apply(toPos);
	m_position = m_target + toPos;
	m_isDirty = true;
}