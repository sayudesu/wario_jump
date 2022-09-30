#pragma once

#include "player.h"
#include "car.h"


class SceneTest
{
public:
	SceneTest();
	virtual ~SceneTest();

	//初期化処理、終了処理
	void init();
	void end();

	//ゲーム処理、シーン切り替えはtrue
	bool update();
	//描画
	void draw();

};

