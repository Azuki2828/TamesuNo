#pragma once

/// <summary>
/// �p�C�v���C���X�e�[�g�B
/// </summary>
class PipelineState {
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~PipelineState()
	{
		if (m_pipelineState) {
			m_pipelineState->Release();
		}
	}
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="desc"></param>
	void Init(D3D12_GRAPHICS_PIPELINE_STATE_DESC desc);
	void Init(D3D12_COMPUTE_PIPELINE_STATE_DESC desc);
	ID3D12PipelineState* Get()
	{
		return m_pipelineState;
	}
private:
	ID3D12PipelineState* m_pipelineState = nullptr;	//�p�C�v���C���X�e�[�g�B
};