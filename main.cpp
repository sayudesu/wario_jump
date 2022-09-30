#include "DxLib.h"
#include "game.h"

#include"SceneMain.h"
#include "SceneTitel.h" 
#include "SceneTest.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	//���݂̃V�[���ԍ� 0:Title 1:Main 2:Test
	int sceneNo = 0;

	SceneMain sceneMain;
	SceneTitel sceneTitel;
	SceneTest sceneTest;

	switch (sceneNo)
	{
	case 0:
		sceneTitel.init();
		break;
	case 1:
		sceneMain.init();
		break;
	case 2:
		sceneTest.init();
		break;
	} 

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();
		//�V�[���ύX�t���O
		bool isChange = false;

		switch (sceneNo)
		{
		case 0:
			isChange = sceneTitel.update();
			sceneTitel.draw();
			if (isChange)
			{
				sceneTitel.end();

				sceneMain.init();
				sceneNo = 1;
			}
			break;
		case 1:
			sceneMain.update();
			sceneMain.draw();
			break;
		case 2:
			sceneTest.update();
			sceneTest.draw();
			break;
		}

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	switch (sceneNo)
	{
	case 0:
		sceneTitel.end();
		break;
	case 1:
		sceneMain.end();
		break;
	case 2:
		sceneTest.end();
		break;
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}