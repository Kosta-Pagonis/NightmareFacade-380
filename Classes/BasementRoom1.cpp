#include "BasementRoom1.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* BasementR1::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BasementR1::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool BasementR1::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//load the csb
	auto rootNode = CSLoader::createNode("BasementRoom1.csb");

	//set the variables
	player = rootNode->getChildByName("player");
	leftarrow = rootNode->getChildByName("leftarrow");
	downarrow = rootNode->getChildByName("downarrow");
	crowbar = rootNode->getChildByName("crowbar");

	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {

		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_A:
			charMovingLeft = true;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			charMovingRight = true;
			break;
		}

	};

	eventListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {

		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_A:
			charMovingLeft = false;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			charMovingRight = false;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			break;
		}

	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, player);

	addChild(rootNode);

	this->scheduleUpdate();

	return true;
}

void BasementR1::update(float delta) {
	auto position = player->getPosition();

	if (!((charMovingLeft && charMovingRight) || (!charMovingLeft && !charMovingRight))) {
		if (charMovingLeft) {
			position.x -= 200 * delta;
			if (position.x < 0)
				position.x = 0;
		}
		if (charMovingRight) {
			position.x += 200 * delta;
			if (position.x + 94 > 1000)
				position.x = 906;
		}
		player->setPosition(position);
	}

}