#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//�҂�����
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;
	//�Ԃ̑��x
	constexpr float kSpeed = -50.0f;
	//�Ԃ̃W�����v��
	constexpr float kCarJumpAcc = -30.0f;
	//�Ԃ̏d��
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

	//�����̃o���G�[�V������I��
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

	//�����n�߂�܂ł̎��Ԃ�ݒ� 1�b����3�b�҂@60�t���[������180�t���[��
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
	//�Ԃ��A���Ă����ꍇ�摜�����]����
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

//�܂������i��
void Car::updateNormal()
{
	m_pos += m_vec;

	DrawString(0, 300, "updateNormal", GetColor(255, 255, 255));

}
//��U��~�t�F�C���g
void Car::updateStop()
{	
	m_pos += m_vec;
	
	if (m_pos.x <= Game::kScreenWidth / 2)
	{
		m_vec.x = 0;

		m_stopTimer++;
		//m_stopTimer��20�ɂȂ�����Ԃ������o��
		if (m_stopTimer > 20)
		{
			m_vec.x = kSpeed;
		}
	}
	DrawString(0, 300, "updateStop", GetColor(255, 255, 255));
}

//�W�����v����
void Car::updateJump()
{
	m_pos += m_vec;

	//�n�ʂƂ̓����蔻��
	bool isField = false;
	if (m_pos.x <= Game::kScreenWidth / 2)
	{
		//m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}

	if (isField)
	{
		m_vec.y = kCarJumpAcc; //�W�����v�J�n
	}

	m_vec.y += kCarGravity;//�d��

}

//�r���ň����Ԃ��i�K�������j
void Car::updateReturn()
{
	m_pos += m_vec;

	if (m_pos.x <= Game::kScreenWidth / 2)
	{	
		carReturn = true;
		m_vec.x++;
	}
}