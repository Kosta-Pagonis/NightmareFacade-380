#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "BasementRoom1.h"
#include "LuaPlus.h"
using namespace LuaPlus;
#include "stdio.h"
using namespace std;

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

	//lua stuff testing
	// Init Lua
	LuaState* luaPState = LuaState::Create();
	//Until the lua file is closed, any changes we make to the lua file should stay.
	//When the lua file is closed, any changes made should revert to their original values.

	// Open the Lua Script File
	int result = luaPState->DoFile("stats.lua");


	// Get the current sanity and current light.
	LuaFunction<int> getCurSanity = luaPState->GetGlobal("getCurSanity"); //getCurSanity returns an int.
	int sanity = getCurSanity();
	LuaFunction<int> getCurLight = luaPState->GetGlobal("getCurLight"); //getCurLight returns an int.
	int light = getCurLight();

	//These don't print to the console properly, but nevertheless are correctly calculated.

	// Let's call the stats.lua's decSanityByAmount function
	LuaFunction<float> decSanityByAmount = luaPState->GetGlobal("decSanityByAmount");
	sanity = decSanityByAmount(50); //Sanity is now 50.
	sanity = decSanityByAmount(50); //Sanity is now 0.
									//Restore sanity
	LuaFunction<void> restoreSanityToMax = luaPState->GetGlobal("restoreSanityToMax");
	restoreSanityToMax(); //Sanity is now 100.
	sanity = getCurSanity(); //Get the current sanity.
	//100

	//Let's decrease the light and sanity through the decLightByOne fucntion
	LuaFunction<void> decLightByOne = luaPState->GetGlobal("decLightByOne"); //Decreases the light by 1, and by extension the sanity by 1.
	decLightByOne();
	light = getCurLight(); //99
	sanity = getCurSanity(); //99
	//These don't print to the console properly, but nevertheless are correctly calculated.

	//Let's print out the currently held item from the inventory.
	LuaFunction<int> getHeldItem = luaPState->GetGlobal("getHeldItem");  //Returns an int.
	LuaFunction<void> shiftInventoryRight = luaPState->GetGlobal("shiftInventoryRight"); //Shifts the inventory to the right.
	LuaFunction<void> shiftInventoryLeft = luaPState->GetGlobal("shiftInventoryLeft"); //Shifts the inventory to the left.
	shiftInventoryLeft(); //Moves the pointer left until it finds a non negative-1 value.
	shiftInventoryRight(); //Moves the pointer right until it finds a non negative-1 value.

	LuaState::Destroy(luaPState); //Close lua file.
	//end of lua stuff 

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