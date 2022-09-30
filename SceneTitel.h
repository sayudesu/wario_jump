#pragma once

#include "player.h"
#include "car.h"


class SceneTitel
{
public:
	SceneTitel();
	virtual ~SceneTitel();

	//初期化処理、終了処理
	void init();
	void end();

	//ゲーム処理、シーン切り替えはtrue
	bool update();
	//描画
	void draw();

private:
	//フェード処理
	int m_fadeBright;
	//フェード速度
	int m_fadeSpeed;

};
