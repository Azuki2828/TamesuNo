/*!
 *@brief	�Q�[���I�u�W�F�N�g�̊��N���X�B
 */

#pragma once

#include <list>
#include <string>
class CRenderContext;

/*!
	*@brief	�Q�[���I�u�W�F�N�g�B
	*/
class CIGameObject {
public:
	/*!
		*@brief	�f�X�g���N�^
		*/
	virtual ~CIGameObject()
	{
		
	}
public:

	
	/*!
	*@brief	Update�̒��O�ŌĂ΂��J�n�����B
	*@details
	* 
	* �{�֐���true��Ԃ��ƃQ�[���I�u�W�F�N�g�̏��������������Ɣ��f�����</br>
	* Update�֐����Ă΂�o���܂��Btrue��Ԃ��Ĉȍ~��Start�֐��͌Ă΂�Ȃ��Ȃ�܂��B</br>
	* �Q�[���I�u�W�F�N�g�̏������ɕ����t���[��������ꍇ�Ȃǂ�false��Ԃ��āA�������X�e�b�v�Ȃǂ��g����</br>
	* �K�؂ɏ��������s���Ă��������B
	*/
	virtual bool Start() { return true; }

	/*!
	*@brief	�폜�����Ƃ��ɌĂ΂��B
	*@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
	* �f�X�g���N�^���O�Ɏ��s����܂��B
	*/
	virtual void OnDestroy() {}

	/*!
	*@brief	�X�V
	*/
	virtual void Update() {}


	/*-------------------------------------��펞�����g���֐�-------------------------------------------*/

	/**
	 * @brief ���W���擾����֐��B
	 * @return 
	*/
	virtual const CVector3& GetPosition() { return CVector3::Zero; }

	/**
	 * @brief �I����Ԃ��X�V����֐��B
	 * @param selectFlag �I����Ԃ��ǂ����̃t���O
	*/
	virtual void SetSelectFlag(const bool selectFlag) {}


	/*-------------------------------------------------------------------------------------------------*/


	/*!
	 *@brief	�`��
	*/
	virtual void Render(CRenderContext& renderContext)
	{
		(void)renderContext;
	}

	/*!
	 *@brief	�`��
	*/
	virtual void ForwardRender(CRenderContext& renderContext)
	{
		(void)renderContext;
	}
	virtual void Render2D(CRenderContext& renderContext)
	{
		(void)renderContext;
	}
	
public:
	/*!
	*@brief Start�֐������������H
	*/
	bool IsStart() const
	{
		return m_isStart;
	}
	/*!
	*@brief �A�N�e�B�u���ǂ����𔻒�B
	*/
	bool IsActive() const
	{
		return m_isActive;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g���A�N�e�B�u�ɂ���B
	/// </summary>
	void Activate()
	{
		m_isActive = true;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g���A�N�e�B�u�ɂ���B
	/// </summary>
	void Deactivate()
	{
		m_isActive = false;
	}
	
	/// <summary>
	/// ���S������B
	/// </summary>
	void Dead()
	{
		m_isDead = true;
	}
	/// <summary>
	/// ���S���Ă���H
	/// </summary>
	/// <returns>true���Ԃ��Ă����玀�S���Ă���</returns>
	bool IsDead() const
	{
		return m_isDead;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̖��O��ݒ�B
	/// </summary>
	/// <param name="name">���O</param>
	void SetName(const char* name)
	{
		if (name != nullptr) {
			m_name = name;
		}
	}
	/// <summary>
	/// �����œn���ꂽ���O���A���̃Q�[���I�u�W�F�N�g�̖��O�ƃ}�b�`���邩����B
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	bool IsMatchName(const char* name) const
	{
		if (strcmp(m_name.c_str(), name) == 0) {
			return true;
		}
		return false;
	}
public:

	void RenderWrapper(CRenderContext& renderContext)
	{
		if (m_isActive && m_isStart && !m_isDead ) {
			Render(renderContext);
		}
	}

	void ForwardRenderWrapper(CRenderContext& renderContext)
	{
		if (m_isActive && m_isStart && !m_isDead) {
			ForwardRender(renderContext);
		}
	}

	void Render2DWrapper(CRenderContext& renderContext)
	{
		if (m_isActive && m_isStart && !m_isDead) {
			Render2D(renderContext);
		}
	}
	
	void UpdateWrapper()
	{
		if (m_isActive && m_isStart && !m_isDead ) {
			Update();
		}
	}
	void StartWrapper()
	{
		if (m_isActive && !m_isStart && !m_isDead ) {
			if (Start()) {
				//���������������B
				m_isStart = true;
			}
		}
	}

	void OnDestroyWrapper()
	{
		//���񂾂Ƃ��p�̊֐����Ăяo���B
		m_destroyEventListener();

		OnDestroy();
	}

	/**
	 * @brief �C�x���g���X�i�[�ɃC�x���g��ǉ�����֐��B
	 * @param event �C�x���g
	*/
	void AddEventListener(std::function<void()> event)
	{
		m_destroyEventListener = event;
	}
		
	friend class CGameObjectManager;
protected:
	std::string m_name;										//�Q�[���I�u�W�F�N�g�̖��O
	bool m_isStart = false;									//Start�̊J�n�t���O�B
	bool m_isDead = false;									//���S�t���O�B
	bool m_isRegistDeadList = false;						//���S���X�g�ɐς܂�Ă���B
	bool m_isNewFromGameObjectManager;						//GameObjectManager��new���ꂽ�B
	bool m_isRegist = false;								//GameObjectManager�ɓo�^����Ă���H
	bool m_isActive = true;									//Active�t���O�B
	std::function<void()> m_destroyEventListener = [] {};	//���񂾂Ƃ��̃C�x���g���X�i�[
};
