#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "BasementRoom1.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* NFMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = NFMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool NFMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//load the csb
	auto rootNode = CSLoader::createNode("MenuScene.csb");
	
	//set the variables
	player = rootNode->getChildByName("player");
	play = rootNode->getChildByName("play");
	help = rootNode->getChildByName("help");
	quit = rootNode->getChildByName("quit");

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
			if (playLit) {
				_eventDispatcher->removeAllEventListeners();
				auto scene = BasementR1::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
			}
			if (helpLit) {
				//show help image
			}
			if (quitLit) {
				exit(0);
			}
			break;
		}

	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, player);

	addChild(rootNode);

	this->scheduleUpdate();

	return true;
}

void NFMenu::update(float delta) {
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

	if (position.x >= 0 && position.x < 290) {
		play->setOpacity(255);
		playLit = true;
	}
	else if (position.x > 405 && position.x < 640) {
		help->setOpacity(255);
		helpLit = true;
	}
	else if (position.x > 770 && position.x < 1000) {
		quit->setOpacity(255);
		quitLit = true;
	}
	else {
		play->setOpacity(100);
		playLit = false;
		help->setOpacity(100);
		helpLit = false;
		quit->setOpacity(100);
		quitLit = false;
	}

}