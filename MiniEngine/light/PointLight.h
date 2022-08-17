#pragma once
#include "constLight.h"
#include "LightBase.h"

namespace nsMyGame {

	namespace nsLight {

		//�|�C���g���C�g�̃f�[�^
		struct PointLigData {
			CVector3 pos = CVector3::Zero;		//���W
			float pad1;							//�p�f�B���O
			CVector3 positionInView;			// �J������Ԃł̍��W
			float pad2;							//�p�f�B���O
			CVector4 color = CVector4::White;	//�J���[
			CVector2 attn;						//�����p�����[�^�Bx�ɉe���͈́Ay�ɂ͉e�����ɗݏ悷��p�����[�^
			CVector2 pad3;						//�p�f�B���O
		};

		//�_�����N���X
		class CPointLight : public CLightBase
		{
			/**
			 * @brief �J�n�����֐��B
			*/
			bool StartSub();
			~CPointLight();
		public:

			/**
			 * @brief ���W��ݒ肷��֐��B
			 * @param pos ���W
			*/
			void SetPosition(const CVector3& pos) {
				m_poiLigData.pos = pos;
			}

			/**
			 * @brief ���W���擾����֐��B
			 * @return ���W
			*/
			const CVector3 GetPosition()const {

				return m_poiLigData.pos;
			}

			/**
			 * @brief �J���[��ݒ肷��֐��B
			 * @param color �J���[
			*/
			void SetColor(const CVector3& color) {

				m_poiLigData.color.x = color.x;
				m_poiLigData.color.y = color.y;
				m_poiLigData.color.z = color.z;
			}

			/**
			 * @brief �J���[��ݒ肷��֐��B
			 * @param color �J���[
			*/
			void SetColor(const float red, const float green, const float blue) {

				m_poiLigData.color.x = red;
				m_poiLigData.color.y = green;
				m_poiLigData.color.z = blue;
			}

			/**
			 * @brief �J���[���擾����֐��B
			 * @return �J���[
			*/
			const CVector4& GetColor()const {

				return m_poiLigData.color;
			}

			/**
			 * @brief �e���͈͂�ݒ肷��֐��B
			 * @param range �e���͈�
			*/
			void SetRange(const float range) {

				m_poiLigData.attn.x = range;
			}

			/**
			 * @brief �e���͈͂��擾����֐��B
			 * @return �e���͈�
			*/
			const float GetRange()const {

				return m_poiLigData.attn.x;
			}

			/**
			 * @brief �e�����̗ݏ搔��ݒ肷��֐��B
			 * @param powParam �e�����̗ݏ搔
			*/
			void SetAffectPowParam(const float powParam) {

				m_poiLigData.attn.y = powParam;
			}

			/**
			 * @brief �e�����̗ݏ搔���擾����֐��B
			 * @return �e�����̗ݏ搔
			*/
			const float GetAffectpowParam()const {

				return m_poiLigData.attn.y;
			}

			/**
			 * @brief ���C�g�̃f�[�^���擾�B
			 * @return ���C�g�̃f�[�^
			*/
			void* GetLigData() { return &m_poiLigData; }

		private:
			PointLigData m_poiLigData;		//�|�C���g���C�g�̃f�[�^
		};
	}
}

