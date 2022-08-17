#pragma once

struct CaslData;
/// <summary>
/// �}�b�v�`�b�v2D�B
/// </summary>
class MapChip2D
{
public:
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="caslData">Casl�f�[�^�B</param>
	void Init(CaslData* caslData);
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update()
	{
		m_sprite.Update(m_position, m_rotation, m_scale);
	}
	/// <summary>
	/// �X�v���C�g��`�悷��B
	/// </summary>
	/// <param name="renderContext">�����_�[�R���e�L�X�g�B</param>
	void Draw(CRenderContext& renderContext)
	{
		m_sprite.Draw(renderContext);
	}
private:
	CVector3 m_position;					//���W�B
	CQuaternion m_rotation;				//��]�B
	CVector3 m_scale = g_vec3One;	//�傫���B
	CSprite m_sprite;						//�X�v���C�g�B
};

