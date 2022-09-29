#pragma once

#include "Vec2.h"

class Car
{
public:
	Car();
	virtual ~Car() {}

	// グラフィックデータの設定	内部でサイズも取得する
	void setGraphic(int handle);

	// 初期設定	地面の高さを与える
	int setup(float fieldY);

	// 更新
	void update();
	// 描画
	void draw();

	// 位置の取得
	Vec2 getPos() const { return m_pos; }
	// サイズの取得
	Vec2 getSize() const { return m_size; }

private:
	//車の挙動のバリエーション
	typedef enum MoveType
	{
		kMoveTypeNormal,
		kMoveTypeStop,
		kMoveTypeJump,
		kMoveTypeReturn,

		kMoveTypeNum
	}MoveType;


private:
	void updateNormal();	//まっすぐ進む
	void updateStop();      //一旦停止フェイント
	void updateJump();		//ジャンプする
	void updateReturn();    //途中で引き返す（必ず成功）

private:
	// グラフィックハンドル
	int m_handle;
	// グラフィックの幅と高さ	当たり判定にも使用する
	Vec2 m_size;

	//車の動き
	int m_moveType;

	//移動開始までの待ち時間(フレーム数)
	int m_waitFrame;
	//車を出し続ける
	int m_carLoop;
	//車が一旦停止したあと動き出す
	int m_stopTimer;

	bool m_isRestart;

	// 位置
	Vec2 m_pos;
	// ベクトル
	Vec2 m_vec;
	// 地面の高さ
	float m_fieldY;

	bool carReturn;
};