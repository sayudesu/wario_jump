#include "DxLib.h"
#include "SceneTest.h"

SceneTest::SceneTest()
{

}

SceneTest::~SceneTest()
{

}

//初期化処理、終了処理
void SceneTest::init()
{

}
void SceneTest::end()
{

}

//ゲーム処理
bool SceneTest::update()
{
	return false;
}
//描画
void SceneTest::draw()
{
	DrawString(0, 0, "SceneTest Now", GetColor(255, 255, 255));
}