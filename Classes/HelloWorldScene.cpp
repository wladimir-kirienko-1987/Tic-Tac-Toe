#include "HelloWorldScene.h"
#include <iostream>

USING_NS_CC;

HelloWorld::HelloWorld() :__pLabel(NULL)
{
}


Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = HelloWorld::create();

	scene->addChild(layer);

	return scene;
}

void HelloWorld::setFiled(tCell CellType, int x, int y)
{

	float new_x = x * Board_FIELD_SIZE_x + x_begin + 65.6;
	float new_y = (480 - y_begin) - y * Board_FIELD_SIZE_y - 61;

	log("pressed at point (%f,%f)", new_x, new_y);

	if (CellType == _x){
		auto sprite = Sprite::create("cross.png");
		sprite->setPosition(new_x, new_y);
		this->addChild(sprite, 0);
	}
	else{
		auto sprite = Sprite::create("zero.png");
		sprite->setPosition(new_x, new_y);
		this->addChild(sprite, 0);
	}
}

bool HelloWorld::init()
{

	if (!Layer::init())
	{
		return false;
	}

	stillGaming = true;

	__pLabel = Label::createWithSystemFont("Hello World", "Arial", 50);
	__pLabel->setTextColor(Color4B::BLACK);
	__pLabel->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	__pLabel->setPosition(Vec2(150, 410));
	this->addChild(__pLabel, 1);
	
	__pLabel->setString("    Zero first");

	auto sprite = Sprite::create("bg2.png");
	sprite->setPosition(640/2, 480/2);
	this->addChild(sprite, 0);

	//Мышь
	auto listener = EventListenerMouse::create();
	
	listener->onMouseDown = [&](cocos2d::Event* event) {
		
		if (stillGaming){
			EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
			log("pressed at point (%f,%f)", mouseEvent->getLocation().x, mouseEvent->getLocation().y);
			log("pressed at point (%f,%f)", mouseEvent->getCursorX(), fabs(mouseEvent->getCursorY()));
			//Получили координаты куда попала мышка Диапазон X 0 - 640 0 - -480
			double x = mouseEvent->getCursorX();
			double y = fabs(mouseEvent->getCursorY());

			//If the mouse is over the button
			if ((x > x_begin) && (x < x_begin + board_w) && (y > y_begin) && (y < y_begin + board_h))
			{
				//Попали на доску

				//Приводим к дипазону x=0,1,2 y=0,1,2
				int x_total = (x - x_begin) / Board_FIELD_SIZE_x;
				int y_total = (y - y_begin) / Board_FIELD_SIZE_y;
				log("pressed at point (%d,%d)", x_total, y_total);

				stillGaming = Process(x_total, y_total);

			}
			else
			{
				//Не попали на доску 
			}
			log("click");

		}
		else{
		}
	};

	//listener->onMouseMove = [](Event* event) {
	//	log("Mouse moved event");
	//
	//	//std::cout << "pressed at point (" << mouseEvent->getLocation().x << "," << mouseEvent->getLocation().y << ")";
	//};

	listener->onMouseScroll = [&](Event* event) {
		log("Mouse wheel scrolled");
		auto *pScene = HelloWorld::createScene();
		//CCDirector::sharedDirector()->replaceScene(pScene);
		CCDirector::getInstance()->replaceScene(pScene);

	};

	//listener->onMouseUp = [](Event* event) {
	//	log("Mouse button released");
	//};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	return true;
}

bool HelloWorld::GetMove(tCell CellType, int x, int y)
{
	try{
		Model.Set(CellType, x, y);
	}
	catch (TTTModelExeption e){

		tModelExeption eType = e.GetType();

		switch (eType){
		case Default: log("Default"); break;
		case EmptySet: log("EmptySet"); break;
		case BoardOvf: log("BoardOvf"); break;
		case AlreadyFill:log("AlreadyFill"); break;
		default: log("default"); break;
		}

		return false;
	}

	setFiled(CellType, x, y);
		
	return true;
}

bool HelloWorld::Process(int x, int y)
{
	tGameState GameState;
	static tCell CellType = _0;

	bool success = GetMove(CellType, x, y);
	if (success)
		CellType = (tCell)((int)CellType ^ 1);

	GameState = Model.CheckState();

	switch (GameState){
	case _0_win: __pLabel->setString("     Zero win"); break;
	case _x_win: __pLabel->setString("    Cross win"); break;
	case _draw: __pLabel->setString("       Draw"); break;
	default: if (success && CellType == _0) __pLabel->setString("    Zero next");
			 else if (success && CellType == _x) __pLabel->setString("   Cross next");
			break;
	}
	
	if (GameState == _next) return true;
	else return false;
}

