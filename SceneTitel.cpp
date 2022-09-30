#include "DxLib.h"
#include "SceneTitel.h"
#include "game.h"

SceneTitel::SceneTitel()
{
	m_fadeBright = 0;
	m_fadeSpeed  = 0;
}

SceneTitel::~SceneTitel()
{

}

//�����������A�I������
void SceneTitel::init()
{
	m_fadeBright = 0;
	m_fadeSpeed  = 8;
}
void SceneTitel::end()
{
	SetDrawBright(255, 255, 255);
}

//�Q�[������
bool SceneTitel::update()
{
	m_fadeBright += m_fadeSpeed;
	if (m_fadeBright > 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if ((m_fadeBright <= 0)&&(m_fadeSpeed < 0))
	{
		//�t�F�[�h�A�E�g���������玟�̃V�[����
		m_fadeBright = 0;
		return true;
	}

	if (m_fadeSpeed == 0)
	{
		//�L�[����(�X�؁[�X)
		if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		{
			//return true;
			m_fadeSpeed = -8;
		}
	}

	return false;
}
//�`��
void SceneTitel::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);

	DrawString(0, 0, "SceneTitel Now", GetColor(255, 255, 255));
	DrawString(Game::kScreenWidth / 2 - 200, Game::kScreenHeight / 2 , "< s p a c e >�������ăQ�[�����J�n", GetColor(255, 255, 255));
}