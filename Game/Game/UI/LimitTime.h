//============================================================//
//*���@�O	LimitTime.h
//*���@�e	��������
//*���@�t	2017.7.28
//*�X�@�V	2017.7.28
//*�����	N.Shibayama
//============================================================//
#pragma once
#include <SpriteBatch.h>
#include <simplemath.h>

class LimitTime
{
private:
	//	���W
	static const float POS_X;
	static const float POS_Y;

public:
	LimitTime(float limitTime);
	~LimitTime();
	
	//	������
	void Initialize();
	//	�X�V
	void Update();
	//	�`��
	void Draw(std::unique_ptr<DirectX::SpriteBatch>& spriteBatch);
	//	���Z�b�g
	void Reset(float limitTime);
	//	���Ԃ�i�߂�
	void Forward();
	//	���Ԃ��~�߂�
	void Stop();
	//	�^�C���I�[�o�[���ǂ���
	bool IsTimeOver();
	//	���݂̎���
	float NowTime();
	//	�t���[���b�̎擾
	int GetTime();

private:
	//	��������
	float m_time;
	//	�j�𓮂���
	bool m_isHand;

	//	�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

};