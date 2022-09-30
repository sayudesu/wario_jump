#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//待ち時間
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;
	//車の速度
	constexpr float kSpeed = -50.0f;
	//車のジャンプ力
	constexpr float kCarJumpAcc = -30.0f;
	//車の重力
	constexpr float kCarGravity = 0.8f;
}

Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	m_moveType;// = kMoveTypeNormal;
	m_waitFrame = 0;
	m_carLoop = 0;
	m_stopTimer = 0;

	carReturn = false;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

int Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

	//動きのバリエーションを選択
	int randNum = GetRand(99);

	if (randNum < 38)
	{
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum < 38 + 30)
	{
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 38 + 30 + 30)
	{
		m_moveType = kMoveTypeJump;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}

	//動き始めるまでの時間を設定 1秒から3秒待つ　60フレームから180フレーム
	m_waitFrame = GetRand(kWaitFrameMax) + kWaitFrameMin;

	return m_moveType;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

	switch (m_moveType)
	{
	case kMoveTypeNormal:
		updateNormal();
		break;
	case kMoveTypeStop:
		updateStop();
		break;
	case kMoveTypeJump:
		updateJump();
		break;
	case kMoveTypeReturn:
		updateReturn();
		break;
	}
}

void Car::draw()
{
	//車が帰っていく場合画像が反転する
	if (carReturn)
	{
		DrawRectGraph(m_pos.x, m_pos.y, 0, 0, m_size.x, m_size.y, m_handle, true, true);
	}
	else
	{
		DrawRectGraph(m_pos.x, m_pos.y, 0, 0, m_size.x, m_size.y, m_handle, true, false);
	}
}

//private///////////////////////////////////////////////////////////

//まっすぐ進む
void Car::updateNormal()
{
	m_pos += m_vec;

	DrawString(0, 300, "updateNormal", GetColor(255, 255, 255));

}
//一旦停止フェイント
void Car::updateStop()
{	
	m_pos += m_vec;
	
	if (m_pos.x <= Game::kScreenWidth / 2)
	{
		m_vec.x = 0;

		m_stopTimer++;
		//m_stopTimerが20になったら車が動き出す
		if (m_stopTimer > 20)
		{
			m_vec.x = kSpeed;
		}
	}
	DrawString(0, 300, "updateStop", GetColor(255, 255, 255));
}

//ジャンプする
void Car::updateJump()
{
	m_pos += m_vec;

	//地面との当たり判定
	bool isField = false;
	if (m_pos.x <= Game::kScreenWidth / 2)
	{
		//m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}

	if (isField)
	{
		m_vec.y = kCarJumpAcc; //ジャンプ開始
	}

	m_vec.y += kCarGravity;//重力

}

//途中で引き返す（必ず成功）
void Car::updateReturn()
{
	m_pos += m_vec;

	if (m_pos.x <= Game::kScreenWidth / 2)
	{	
		carReturn = true;
		m_vec.x++;
	}
}