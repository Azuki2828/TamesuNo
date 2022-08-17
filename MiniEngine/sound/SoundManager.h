#pragma once

namespace nsMyGame {

	//�T�E���h�̎��
	enum class SoundType {
		Type_BGM,
		Type_SE,
		Type_Effect,

		Type_Num
	};

	//�T�E���h�Ǘ��N���X
	class CSoundManager
	{
		struct SoundData {
			int soundNum = 0;							//�o�^�ԍ�
			bool roopFlg = false;						//���[�v�t���O
			const wchar_t* soundName = nullptr;			//�t�@�C���p�X
			float soundVolume = 1.0f;					//����
			CSoundSource* sound = nullptr;				//�T�E���h�\�[�X(����)
			SoundType soundType = SoundType::Type_BGM;	//�T�E���h�̎��
		};
	public:

		/**
		 * @brief �������֐��B
		 * @param filePath �t�@�C���p�X
		 * @param num �T�E���h�ԍ�
		 * @param flg ���[�v�Đ�����H
		 * @param sType �T�E���h�̎��
		 * @param vol ����
		*/
		void Init(const wchar_t* filePath, const int num, const bool flg = false, SoundType sType = SoundType::Type_BGM, const float vol = 1.0f);

		/**
		 * @brief �C���X�^���X�𐶐�����֐��B
		*/
		static void CreateInstance() {

			m_soundManager = new CSoundManager;
		}

		/**
		 * @brief �C���X�^���X���擾����֐��B
		 * @return �C���X�^���X
		*/
		static CSoundManager* GetInstance() {

			return m_soundManager;
		}

		/**
		 * @brief �C���X�^���X���폜����֐��B
		*/
		static void DeleteInstance() {

			//�T�E���h�f�[�^��S�폜�B
			m_soundManager->m_soundData.clear();

			//�C���X�^���X���폜�B
			delete m_soundManager;
		}

		/**
		 * @brief �X�V�֐��B
		*/
		void Update();

		/**
		 * @brief �T�E���h���폜����֐��B
		 * @param num �T�E���h�ԍ�
		*/
		void Release(const int num);

		/**
		 * @brief �T�E���h���Đ�����֐��B
		 * @param num �T�E���h�ԍ�
		*/
		void Play(const int num);

		/**
		 * @brief �T�E���h���~����֐��B
		 * @param num �T�E���h�ԍ�
		*/
		void Stop(const int num);

		/**
		 * @brief �Đ����H
		 * @param num �T�E���h�ԍ�
		 * @return �Đ������ǂ����̔���
		*/
		bool IsPlaying(const int num);
		
		/**
		 * @brief ���ʂ�ݒ肷��֐��B
		 * @param num  �T�E���h�ԍ�
		 * @param vol �T�E���h�{�����[�� (0.0f�`1.0f��ݒ�)
		*/
		void SetSoundSourceVolume(const int num, const float vol);

		/**
		 * @brief ���[�v�Đ����邩�ǂ����ݒ肷��֐��B
		 * @param num �T�E���h�ԍ�
		 * @param flg ���[�v�Đ����邩�ǂ����̃t���O
		*/
		void SetRoopFlg(const int num, const bool flg);

		/**
		 * @brief ���ʂ�ݒ肷��֐��B
		 * @param vol �T�E���h�{�����[��
		 * @param type �T�E���h�̎��
		*/
		void SetVolume(const float vol, SoundType type = SoundType::Type_BGM) {
			switch (type) {
			case SoundType::Type_BGM:
				m_bgmVolume = vol;
				break;
			case SoundType::Type_SE:
				m_seVolume = vol;
				break;
			case SoundType::Type_Effect:
				m_effectVolume = vol;
				break;
			}
		}

	private:
		static CSoundManager* m_soundManager;		//�C���X�^���X
		float m_bgmVolume = 1.0f;					//BGM����
		float m_seVolume = 1.0f;					//SE����
		float m_effectVolume = 1.0f;				//�G�t�F�N�g����
		std::vector<SoundData> m_soundData;			//�T�E���h�f�[�^
	};
}

