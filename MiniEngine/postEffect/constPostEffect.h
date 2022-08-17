#pragma once

namespace nsMyGame {

	namespace nsPostEffect {


		/*------PostEffectComponentBase------*/
		constexpr const char* c_fxFilePathCopySprite = "Assets/shader/sprite.fx";			//���C�������_�����O�^�[�Q�b�g�ɃR�s�[���鎞�Ɏg�p����V�F�[�_�[�̃t�@�C���p�X
		/*-----------------------------------*/


		/*------GaussianBlur------*/
		constexpr const char* c_fxFilePathGaussianBlur = "Assets/shader/gaussianBlur.fx";	//�K�E�V�A���u���[�Ŏg�p����V�F�[�_�[�̃t�@�C���p�X
		constexpr const char* c_vsEntryPointFuncXBlur = "VSXBlur";							//���u���[�p�̃X�v���C�g�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const char* c_vsEntryPointFuncYBlur = "VSYBlur";							//�c�u���[�p�̃X�v���C�g�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const char* c_psEntryPointFuncBlur = "PSBlur";							//�u���[�p�̃X�v���C�g�̃s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const int c_gaussianBlurNumWeight = 8;									//�K�E�V�A���u���[�̏d�݂̐�
		/*------------------------*/


		/*------Bloom------*/
		constexpr const int c_gaussianBlurNum = 4;												//�K�E�V�A���u���[�̐�
		constexpr const char* c_fxFilePathBloom = "Assets/shader/bloom.fx";						//�u���[���p�̃V�F�[�_�[�̃t�@�C���p�X
		constexpr const char* c_vsEntryPointFuncBloom = "VSMain";								//�u���[���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const char* c_psEntryPointFuncSamplingLuminance = "PSSamplingLuminance";		//�P�x���o�p�̃s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const char* c_psEntryPointFuncBloomFinal = "PSBloomFinal";					//�u���[���ŏI�̃s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g
		/*-----------------*/


		/*------FXAA------*/
		constexpr const char* c_fxFilePathFXAA = "Assets/shader/fxaa.fx";	//FXAA�Ŏg�p����V�F�[�_�[�̃t�@�C���p�X
		constexpr const char* c_vsEntryPointFuncFXAA = "VSMain";			//FXAA�p�̃X�v���C�g�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
		constexpr const char* c_psEntryPointFuncFXAA = "PSMain";			//FXAA�p�̃X�v���C�g�̃s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g
		/*----------------*/
	}
}