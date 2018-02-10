#pragma once

#include "cocos2d.h"
#include "TTTModel.h"

class HelloWorld : public cocos2d::Layer
{
public:
	const int x_begin = 116;
	const int y_begin = 80;
	const int board_w = 390;
	const int board_h = 350;
	const int Board_FIELD_SIZE_x = 130;
	const int Board_FIELD_SIZE_y = 117;

	static cocos2d::Scene* createScene();
	virtual bool init();

	HelloWorld();

	void setFiled(tCell CellType, int x, int y);
	bool GetMove(tCell CellType, int x, int y);
	bool Process(int x, int y);
	void RestartGame();
	void onMouseDown_(cocos2d::EventMouse* event);

	bool stillGaming;

	TTTModel Model;

	cocos2d::Label* __pLabel;


	CREATE_FUNC(HelloWorld);
};

