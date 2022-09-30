#include "DxLib.h"
#include "SceneMain.h"
#include "game.h"

namespace
{
	// 地面の高さ
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


//初期化処理、終了処理
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
	//読み込んだデータを削除する
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hCar);
}

//ゲーム処理
bool SceneMain::update()
{
	SetFontSize(50);
	DrawString(0, 0, "<SPACE>キーでジャンプ", GetColor(255, 255, 255));
	DrawString(0, 50, "< A >で右移動  < D　>で左移動 ", GetColor(255, 255, 255));
	DrawString(0, 100, "< SHIFT > & A || & D で加速 ", GetColor(255, 255, 255));
	//DrawString(Game::kScreenWidth / 2.5 - 300, Game::kScreenHeight / 2 , "車のloopができないいい", GetColor(255, 255, 255));

	m_player.update();
	m_car.update();

	//当たり判定
	if (m_player.isCol(m_car))
	{
		m_player.setDead(true);
	}

	return false;
}
//描画
void SceneMain::draw()
{

	// 地面の描画
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_car.draw();
}