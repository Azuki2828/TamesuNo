#pragma once
#include "stdafx.h"

namespace nsMyGame {

	//�D��x�BenPriority_Zeroth���ł���ɕ`�悳���B
	enum PriorityNum {
		enPriority_Zeroth,
		enPriority_First,
		enPriority_Second,
		enPriority_Third,
		enPriority_Fourth,
		enPriority_Fifth
	};

	/*------�N���X�̖��O------*/
	constexpr const char* c_classNameFade = "fade";										//�t�F�[�h�N���X�̖��O
	constexpr const char* c_classNameSkyCube = "skycube";								//��N���X�̖��O
	/*------------------------*/

	/*--------�T�E���h���X�g--------*/
	enum EnSoundList {

		enSound_Num
	};
	/*-----------------------------*/

	/*------�T�E���h�̃t�@�C���p�X------*/

	/*----------------------------------*/

	/*----------�V�F�[�_�[�֌W----------*/
	constexpr const char* c_entryPointVSMain = "VSMain";						//���_�V�F�[�_�[�̃G���g���[�|�C���g
	constexpr const char* c_entryPointVSSkinMain = "VSSkinMain";				//�X�L������̒��_�V�F�[�_�[�̃G���g���[�|�C���g
	constexpr const char* c_fxFilePath_Model = "Assets/shader/model.fx";		//G-Buffer�쐬�Ɏg���V�F�[�_�[�̃t�@�C���p�X
	constexpr UINT c_frameBufferWidth = 1280;									//�t���[���o�b�t�@�̕�
	constexpr UINT c_frameBufferHeight = 720;									//�t���[���o�b�t�@�̍���
	constexpr int c_tileWidth = 16;												//TBR�ŕ�������^�C���̉��̐�
	constexpr int c_tileHeight = 16;											//TBR�ŕ�������^�C���̏c�̐�
	/*----------------------------------*/

	constexpr float c_skyCubeLumminance = 0.2f;		//��̋P�x

	constexpr const char* c_filePathFadeSprite = "Assets/image/fade.dds";			//�t�F�[�h�摜�̃t�@�C���p�X
}





/**
 * @brief HUD�ɓo�^����Ă���X�v���C�g
*/
enum HUDList {

	enSprite_HUDNum
};

namespace {

	const int c_pad0 = 0;											//0�Ԗڂ̃p�b�h
	const int c_nameSize = 256;										//���O�̍ő�̃T�C�Y
	const int c_textSize = 64;										//�e�L�X�g�̕W���T�C�Y
	const float c_textBitSize = 16.0f;								//�e�L�X�g�̃r�b�g�T�C�Y

	const CVector3 c_gravityScale = { 0.0f,-300.0f,0.0f };			//�W���̏d��

	const CVector3 c_cameraUp = { 0.0f,1.0f,0.0f };					//�J�����̕W���̏����

	const CVector2 c_renderTargetW1280H720 = { 1280.0f,720.0f };						//�����_�����O�^�[�Q�b�g�Ŏg�p���镝�ƍ���
	const CVector2 c_shadowMapWH = { 4096.0f,4096.0f };									//�V���h�E�}�b�v�̕��ƍ���
	const int c_mipLevel1 = 1;															//�����_�����O�^�[�Q�b�g�Ŏg�p����~�b�v�}�b�v���x��
	const int c_renderArraySize1 = 1;													//�����_�����O�^�[�Q�b�g�Ŏg�p����e�N�X�`���z��̃T�C�Y
	const int c_gaussianBlurNum = 4;													//�K�E�V�A���u���[���������
	const int c_blurPower = 10;															//�u���[�̋���
	const char* c_fxFilePath_DeferredLighting = "Assets/shader/deferredLighting.fx";	//�f�B�t�@�[�h���C�e�B���O�Ɏg���V�F�[�_�[�̃t�@�C���p�X
	const char* c_fxFilePath_Sprite = "Assets/shader/sprite.fx";						//�X�v���C�g�V�F�[�_�[�̃t�@�C���p�X
	const char* c_fxFilePath_ShadowMap = "Assets/shader/drawShadowMap.fx";				//�V���h�E�}�b�v�`��Ɏg���V�F�[�_�[�̃t�@�C���p�X

	const int c_initializeTime = 0;
	const int c_restInitialTime = 0;		//�X�s�����b�N���̑҂��^�C���̏�������
	const int c_spinLockCriteria = 16;		//�X�s�����b�N���̊�ƂȂ鎞��

	const CVector4 c_translucentValue_Half = { 1.0f,1.0f,1.0f,0.5f };		//������50%
	const CVector4 c_translucentValue_OneThird = { 1.0f,1.0f,1.0f,0.3f };	//������70%
	const CVector4 c_translucentValue_Zero = { 1.0f,1.0f,1.0f,0.0f };		//������100%
	const CVector4 c_translucentValue_Max = { 1.0f,1.0f,1.0f,1.0f };		//������0%

	const float c_textShadowThickness = 1.0f;								//�e�L�X�g�̉e�i�g���j�̌���

	const float c_appearSpriteTranslucent = 5.0f;							//AppearSprite�N���X�Ŏg���A�����x�̒萔�l
	

	const CVector3 c_scaleValue_Half = { 0.5f,0.5f,0.5f };					//�g�嗦50%
	const CVector3 c_scaleValue_ATenth = { 0.1f,0.1f,0.1f };				//�g�嗦10%
	const CVector3 c_scaleValue_AFifth = { 0.2f,0.2f,0.2f };				//�g�嗦20%
}

/**
 * @brief �����̌������擾����֐�
 * @tparam Num �e���v���[�g
 * @param num �������m���߂�������
 * @return ����
*/
template<typename Num>
int GetDigit(Num num) {

	int digit = 0;
	while (num >= 1) {
		num /= 10;
		digit++;
	}

	return digit;
}