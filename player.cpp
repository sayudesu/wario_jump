#include "DxLib.h"
#include "game.h"
#include "player.h"

namespace
{
	//キャラクターのサイズ
	constexpr float kSizeX = 128.0f;
	constexpr float kSizeY = 128.0f;
	//ジャンプ力
	constexpr float kJumpAcc = -25.0f;
	//重力
	constexpr float kGravity = 0.8f;
	//キャラクター走りスピード
	constexpr float kRunSpeed = 10.0f;
}

Player::Player()
{
	m_handle = -1;
	m_fieldY = 0.0f;

	m_isDead = false;
}

void Player::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle ,&m_graphSize.x, &m_graphSize.y);
	m_colSize = m_graphSize;
}

void Player:: setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = 64.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
}

void Player::update()
{
	//死んだら右上に飛ぶ
	if (m_isDead)
	{
		m_pos.x -= 10;
		m_pos.y -= 10;
		return;
	}

	m_pos += m_vec;
	//地面との当たり判定
	bool isField = false;
	if (m_pos.y > m_fieldY - m_graphSize.y)
	{
		m_pos.y = m_fieldY - m_graphSize.y;
		isField = true;
	}

	// キー入力処理
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if(CheckHitKey(KEY_INPUT_SPACE) == 1)
	//if (padState & PAD_INPUT_1)
	{
		if (isField)
		{
			m_vec.y = kJumpAcc; //ジャンプ開始
		}
	}
	m_vec.y += kGravity; //重力

	//キャラクターの横移動
	if (CheckHitKey(KEY_INPUT_D) == 1)//右
	{
		m_pos.x += kRunSpeed;

		if (CheckHitKey(KEY_INPUT_LSHIFT) == 1)//右に走るスピードアップ
		{
			m_pos.x += kRunSpeed;
		}

		if (m_pos.x == Game::kScreenWidth)
		{
			m_vec.x = 0;
		}

	}
	if (CheckHitKey(KEY_INPUT_A) == 1)//左
	{
		m_pos.x -= kRunSpeed;

		if (CheckHitKey(KEY_INPUT_LSHIFT) == 1)//左に走るスピードアップ
		{
			m_pos.x -= kRunSpeed;
		}
	}

}

void Player::draw()
{
	//生きている場合死んでいる場合の画像表示位置を変更
	if (m_isDead)
	{
		DrawRectGraph(m_pos.x, m_pos.y, m_graphSize.x / 2, 0, m_graphSize.x , m_graphSize.y, m_handle, true);
	}
	else
	{
		DrawRectGraph(m_pos.x, m_pos.y, 0, 0, m_graphSize.x / 2, m_graphSize.y, m_handle, true);
	}
}

bool Player::isCol(Car& car)
{
	float playerLeft = getPos().x;
	float playerRight = getPos().x + kSizeX;
	float playerTop = getPos().y;
	float playerBottom = getPos().y + kSizeY;

	float carLeft = car.getPos().x;
	float carRight = car.getPos().x + car.getSize().x;
	float carTop = car.getPos().y;
	float carBottom = car.getPos().y + car.getSize().y;

	if (playerLeft > carRight)	return false;
	if (playerRight < carLeft)	return false;
	if (playerTop > carBottom)	return false;
	if (playerBottom < carTop)	return false;

	return true;
}
