//============================================================//
//*���@�O	Heart.h
//*���@�e	�S�[���̃n�[�g
//*���@�t	2017.5.21
//*�X�@�V	2017.5.21
//*�����	N.Shibayama
//============================================================//
#pragma once
#include "Object3D.h"
#include "..\..\Library\Collision\Sphere\SphereNode.h"

class Heart
{
public:
	//	������
	void Initialize();
	//	�X�V
	void Update();
	//	�`��
	void Draw();

	//	���W�擾
	DirectX::SimpleMath::Vector3 GetTranslation() { return m_model.GetTranslation(); }
	//	���W�ύX
	void ChangePos(DirectX::SimpleMath::Vector3 pos);

private:
	Object3D m_model;

	//	��]
	DirectX::SimpleMath::Vector3 m_rotation;

};
