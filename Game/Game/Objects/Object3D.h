//============================================================//
//*���@�O	Player.h
//*���@�e	3D�I�u�W�F�N�g
//*���@�t	2017.8.01
//*�X�@�V	2017.8.01
//*�����	N.Shibayama
//============================================================//
#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <Effects.h>			//BasicEffect
#include <CommonStates.h>		//CommonStates
#include <SimpleMath.h>			//Vecter3
#include <Model.h>

#include "..\..\Library\Camera\Camera.h"
#include "..\..\Library\Devices\Devices.h"

class Object3D
{
public:
	//	�ÓI�����o�֐�
	static void InitializeStatic(Camera* camera);

private:
	//	�f�o�C�X���
	std::unique_ptr<Devices> device;

	//	�J����
	static Camera* m_Camera;
	//	�ėp�X�e�[�g�ݒ�
	static std::unique_ptr<DirectX::CommonStates> m_states;
	//	�G�t�F�N�g�t�@�N�g��
	static std::unique_ptr<DirectX::EffectFactory> m_factory;

public:
	//	�R���X�g���N�^
	Object3D();

	//	CMO���f����ǂݍ���
	void LoadModel(const wchar_t* fileName);
	//	�X�V
	void Update();
	//	�`��
	void Draw();

	//	�X�P�[�����O(XYZ)
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	//	��]�p(XYZ)���t���O���I�t
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation; m_UseQuaternion = false; }
	//	��]�p(�N�H�[�^�j�I��)���t���O���I��
	void SetRotationQ(const DirectX::SimpleMath::Quaternion& rotationQ) { m_rotationQ = rotationQ; m_UseQuaternion = true; }
	//	���s�ړ�(XYZ)
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation) { m_translation = translation; }
	//	���[���h�s��
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_world = world; }
	//	�e��3D�I�u�W�F�N�g
	void SetObjParent(Object3D* objParentle) { m_ObjParent = objParentle; }

	//	�X�P�[�����O(XYZ)�擾
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	//	��]�p(XYZ)�擾
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	//	���s�ړ�(XYZ)�擾
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_translation; }
	//	���[���h�s��擾
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }

private:
	//	���f��
	std::unique_ptr<DirectX::Model> m_model;
	//	�X�P�[�����O(XYZ)
	DirectX::SimpleMath::Vector3 m_scale;
	//	��]�p(XYZ)
	DirectX::SimpleMath::Vector3 m_rotation;
	//	��]�p(�N�H�[�^�j�I��)
	DirectX::SimpleMath::Quaternion m_rotationQ;
	//	���s�ړ�(XYZ)
	DirectX::SimpleMath::Vector3 m_translation;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	//	�e��Obj3d�ւ̃|�C���^
	Object3D* m_ObjParent;
	//	��]���N�H�[�^�j�I���ň����t���O
	bool m_UseQuaternion;

};
