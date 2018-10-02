//============================================================//
//*名　前	World.cpp
//*内　容	背景世界
//*日　付	2018.4.10
//*更　新	2018.4.10
//*制作者	N.Shibayama
//============================================================//
#include "World.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

void World::Initialize()
{
	this->m_model.LoadModel(L"Resources/cubeworld.cmo");
	this->m_model.SetTranslation(Vector3(-5.0f, 0.0f, 0.0f));
	this->m_model.SetScale(Vector3(70, 70, 70));
	this->m_model.SetRotation(Vector3(0, 0, 0));
}

void World::Update()
{
}

void World::Draw()
{
	m_model.Draw();
}

