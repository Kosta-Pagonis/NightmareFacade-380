#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

	//Move the clouds
	auto sc1MoveTo = MoveTo::create(5, Vec2(70, 537));
	auto sc2MoveTo = MoveTo::create(5, Vec2(144, 534));
	auto lcMoveTo = MoveTo::create(5, Vec2(103, 486));
	rootNode->getChildByName("smallcloud1")->runAction(sc1MoveTo);
	rootNode->getChildByName("smallcloud2")->runAction(sc2MoveTo);
	rootNode->getChildByName("largecloud")->runAction(lcMoveTo);

	//Setup a mouse listener
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	_eventDispatcher->addEventListenerWithFixedPriority(mouseListener, 1);


    addChild(rootNode);

    return true;
}

void HelloWorld::onMouseUp(Event* event) 
{
	_eventDispatcher->removeAllEventListeners();
	auto scene = NFMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
}
