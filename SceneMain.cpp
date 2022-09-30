#include "DxLib.h"
#include "SceneMain.h"
#include "game.h"

namespace
{
	// �n�ʂ̍���
	constexpr int kFieldY = Game::kScreenHeight - 64;
}

SceneMain::SceneMain()
{
	m_hPlayer = -1;
	m_hCar = -1;
}

SceneMain::	~SceneMain()
{
	
}


//�����������A�I������
void SceneMain::init()
{
	m_hPlayer = LoadGraph("data/player.png");
	m_hCar = LoadGraph("data/car.png");

	Player player;
	m_player.setGraphic(m_hPlayer);
	m_player.setup(kFieldY);

	Car car;
	m_car.setGraphic(m_hCar);
	m_car.setup(kFieldY);
}
void SceneMain::end()
{
	//�ǂݍ��񂾃f�[�^���폜����
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hCar);
}

//�Q�[������
bool SceneMain::update()
{
	SetFontSize(50);
	DrawString(0, 0, "<SPACE>�L�[�ŃW�����v", GetColor(255, 255, 255));
	DrawString(0, 50, "< A >�ŉE�ړ�  < D�@>�ō��ړ� ", GetColor(255, 255, 255));
	DrawString(0, 100, "< SHIFT > & A || & D �ŉ��� ", GetColor(255, 255, 255));
	//DrawString(Game::kScreenWidth / 2.5 - 300, Game::kScreenHeight / 2 , "�Ԃ�loop���ł��Ȃ�����", GetColor(255, 255, 255));

	m_player.update();
	m_car.update();

	//�����蔻��
	if (m_player.isCol(m_car))
	{
		m_player.setDead(true);
	}

	return false;
}
//�`��
void SceneMain::draw()
{

	// �n�ʂ̕`��
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_car.draw();
}