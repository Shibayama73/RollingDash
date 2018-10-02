//============================================================//
//*���@�O	Player.cpp
//*���@�e	3D�I�u�W�F�N�g
//*���@�t	2017.8.01
//*�X�@�V	2017.8.01
//*�����	N.Shibayama
//============================================================//
#include "Object3D.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//	�J����
Camera* Object3D::m_Camera;
//	�ėp�X�e�[�g�ݒ�
std::unique_ptr<DirectX::CommonStates> Object3D::m_states;
//	�G�t�F�N�g�t�@�N�g��
std::unique_ptr<DirectX::EffectFactory> Object3D::m_factory;

void Object3D::InitializeStatic(Camera * camera)
{
	auto& device = Devices::GetInstance();

	m_Camera = camera;

	//	�ėp�X�e�[�g�ݒ萶��
	m_states = std::make_unique<CommonStates>(device.GetDevice().Get());
	//	�G�t�F�N�g�t�@�N�g���쐬
	m_factory = std::make_unique<EffectFactory>(device.GetDevice().Get());
	//	�e�N�X�`���t�@�C���w��
	m_factory->SetDirectory(L"Resources");

}

Object3D::Object3D()
{
	//	�����o�ϐ��̏�����
	m_scale = Vector3(1, 1, 1);
	m_ObjParent = nullptr;

	//	�f�t�H���g�ł̓I�C���[�p���g�p
	m_UseQuaternion = false;

}


void Object3D::LoadModel(const wchar_t * fileName)
{
	auto& device = Devices::GetInstance();
	//	CMO���烂�f���̓ǂݍ���
	m_model = Model::CreateFromCMO(device.GetDevice().Get(), fileName, *m_factory);

}

void Object3D::Update()
{
	//	���[���h�s��̌v�Z
	Matrix scalemat = Matrix::CreateScale(m_scale);
	Matrix rotmat;
	if (m_UseQuaternion)
	{
		//	�N�H�[�^�j�I���ŉ�]���v�Z
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{
		//	�I�C���[�p�ŉ�]���v�Z
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
		rotmat = rotmatZ * rotmatX * rotmatY;
	}
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//	���[���h���W�̍���
	m_world = scalemat * rotmat * transmat;
	//	�e�̍s����|����(�q���̍s�񁖐e�̍s��)
	if (m_ObjParent)
	{
		m_world *= m_ObjParent->GetWorld();
	}

}

void Object3D::Draw()
{
	if (m_model)
	{
		auto& device = Devices::GetInstance();

		m_model->Draw(device.GetDeviceContext().Get(), *m_states, m_world, m_Camera->GetViewMatrix(), m_Camera->GetProjectionMatrix());
	}

}
