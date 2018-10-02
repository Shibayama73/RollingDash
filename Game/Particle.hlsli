//==============================//
//	�R���X�^���g�o�b�t�@
//==============================//
cbuffer global
{
	//	���[���h����ˉe�܂ł̕ϊ��s��(row_major=��D��)
    row_major matrix g_WVP;
	//	�r���{�[�h�s��(row_major=��D��)
    row_major matrix g_Billboard;
};

//==============================//
//	�e�N�X�`���ƃT���v���[
//==============================//
Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

//==============================//
//	�W�I���g���V�F�[�_�ւ̓���
//==============================//
struct GSInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 other : TEXCOORD;
};

//==============================//
//	�s�N�Z���V�F�[�_�ւ̓���
//==============================//
struct PSInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};
