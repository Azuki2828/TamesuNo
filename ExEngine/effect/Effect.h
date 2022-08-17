/*!
* @brief	�G�t�F�N�g
*/

#pragma once
#include "EffectEngine.h"
/*!
* @brief	�G�t�F�N�g�B
*/
class Effect : public CIGameObject{
public:
	Effect();
	~Effect();
	
	/// <summary>
	/// �������B
	/// </summary>
	/// <remark>
	/// �G�t�F�N�g�Đ��̂��߂̏������s���܂��B
	/// </remark>
	/// <param name="filePath">�t�@�C���p�X</param>
	void Init(const char16_t* filePath);
	/// <summary>
	/// �Đ��J�n
	/// </summary>
	/// <remark>
	/// ���̊֐����Ăяo���ƃG�t�F�N�g�̍Đ����J�n����܂��B
	/// </remark>
	void Play();

	void Stop();
	/*!
	*@brief	���W��ݒ�B
	*/
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ���W���擾�B
	/// </summary>
	/// <returns></returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/*!
	*@brief	��]�N�H�[�^�j�I����ݒ�B
	*/
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]�N�H�[�^�j�I�����擾�B
	/// </summary>
	/// <returns></returns>
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}
	/*!
		*@brief	�g�嗦��ݒ�B
		*/
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// �g�嗦���擾�B
	/// </summary>
	/// <returns></returns>
	const CVector3& GetScale() const
	{
		return m_scale;
	}
	/// <summary>
	/// �G�t�F�N�g���Đ���������B
	/// </summary>
	bool IsPlay() const
	{
		return EffectEngine::GetInstance()->IsPlay(m_handle);
	}
	/*!
	 *@brief	�X�V�B
	 */
	void Update() override;
private:
	Effekseer::EffectRef m_effect;	//�G�t�F�N�g
	int	m_handle = -1;				//�Đ����̃G�t�F�N�g�̃n���h���B
	CVector3 m_position;				//���W�B
	CQuaternion m_rotation;;			//��]�B
	CVector3 m_scale = g_vec3One;	//�g�嗦�B
};
