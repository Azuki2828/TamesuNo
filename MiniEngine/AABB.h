#pragma once

	/// <summary>
	/// AABB
	/// </summary>
	class AABB {
	private:
		CVector3 m_max;					// AABB���\������{�b�N�X�̍ő���W�B
		CVector3 m_min;					// AABB���\������{�b�N�X�̍ŏ����W�B
		CVector3 m_centerPos;			// ���S���W�B
		CVector3 m_vertexPosition[8];	// AABB���\������8���_�̍��W�B
	public:
		/// <summary>
		/// AABB�̏�������������B
		/// </summary>
		/// <param name="vMax">�ő�l</param>
		/// <param name="vMin">�ŏ��l</param>
		void Init(const CVector3& vMax, const CVector3& vMin);
		/// <summary>
		/// AABB���\������8���_�̃��[���h��Ԃł̍��W���v�Z����B
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="mWorld"></param>
		void CalcVertexPositions(CVector3* pos, const CMatrix& mWorld);
		/// <summary>
		/// AABB�̍ő�l���擾�B
		/// </summary>
		const CVector3& GetMax() const
		{
			return m_max;
		}
		/// <summary>
		/// AABB�̍ŏ��l���擾�B
		/// </summary>
		/// <returns>�ŏ��l</returns>
		const CVector3& GetMin() const
		{
			return m_min;
		}
		/// <summary>
		/// ���S���W���擾�B
		/// </summary>
		/// <returns>���S���W</returns>
		const CVector3& GetCenter() const
		{
			return m_centerPos;
		}
	};