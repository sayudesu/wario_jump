#pragma once

#include "player.h"
#include "car.h"


class SceneTitel
{
public:
	SceneTitel();
	virtual ~SceneTitel();

	//�����������A�I������
	void init();
	void end();

	//�Q�[�������A�V�[���؂�ւ���true
	bool update();
	//�`��
	void draw();

private:
	//�t�F�[�h����
	int m_fadeBright;
	//�t�F�[�h���x
	int m_fadeSpeed;

};
