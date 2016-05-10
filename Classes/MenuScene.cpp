#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "BasementRoom1.h"
#include "SimpleAudioEngine.h"
#include "cocostudio\CocoStudio.h"
#include "cocostudio\ActionTimeline\CCActionTimelineNode.h"
#include "level2.h"
#include "level3.h"

#define PTM_RATIO 30
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
//adds dynamic body for player
void NFMenu::addBoxBodyForSprite(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5,.5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO ,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	spriteBody = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2,
		sprite->getContentSize().height / PTM_RATIO / 2);
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = false;
	spriteBody->CreateFixture(&spriteShapeDef);
	

}
//adds body for static object
void NFMenu::addBoxBodyForStatic(Node * sprite, b2Body* body)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	body = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2,
		sprite->getContentSize().height / PTM_RATIO / 2);
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	body->CreateFixture(&spriteShapeDef);


}
//simulates physics every frame and then moves everything in BOX2D , also handles collision
void NFMenu::tick()
{
	world->Step(1.0f / 60.0f, 10, 10);
	idleAnim->setPosition(sprite->getPosition());
	leftAnim->setPosition(sprite->getPosition());
	rightAnim->setPosition(sprite->getPosition());
	for (b2Body *b = world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			CCSprite *sprite = (CCSprite *)b->GetUserData();
			sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO));
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	
	b2ContactEdge* edge = spriteBody->GetContactList();
	
		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == door)
		{
			quitLit = true;
			quit->setOpacity(255);
		//	audio->playEffect("exitsound.wav");
		}
		else
		{
			quitLit = false;
			quit->setOpacity(50);
		}
		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == desk)
		{
			helpLit = true;
			help->setOpacity(255);
			tips->setOpacity(200);
			//audio->playEffect("helpsound.wav");
		}
		else
		{
			tips->setOpacity(0);
			helpLit = false;
			help->setOpacity(50);
			
		}
		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == bed)
		{
			playLit = true;
			play->setOpacity(255);
			//audio->playEffect("playsound.wav");
		}
		else
		{
			playLit = false;
			play->setOpacity(50);
		}
		
	
}

//for debugging
void NFMenu::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	kmGLPushMatrix();
	world->DrawDebugData();
	kmGLPopMatrix();
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
	sprite = rootNode->getChildByName("player");
	play = rootNode->getChildByName("play");
	help = rootNode->getChildByName("help");
	quit = rootNode->getChildByName("quit");
	bed = rootNode->getChildByName("bedPic");
	desk = rootNode->getChildByName("deskPic");
	door = rootNode->getChildByName("doorPic");
	tips = rootNode->getChildByName("tips");

	idleAnim = rootNode->getChildByName("idleAnim");
	leftAnim = rootNode->getChildByName("leftAnim");
	rightAnim = rootNode->getChildByName("rightAnim");
	
	
	//Creates World
	b2Vec2 gravity = b2Vec2(0.0f, -9.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(false);
	world->SetContinuousPhysics(true);
	contactListener = new b2ContactListener();
	world->SetContactListener(contactListener);
	
	//Creates Ground and Walls
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(0,1.5);
	_groundBody = world->CreateBody(&groundBodyDef);

	b2EdgeShape groundBox;
	b2FixtureDef groundBoxDef;
	groundBoxDef.shape = &groundBox;

	groundBox.Set(b2Vec2(0, 0), b2Vec2(1000 / PTM_RATIO, 0));
	_bottomFixture = _groundBody->CreateFixture(&groundBoxDef);

	groundBox.Set(b2Vec2(0, 0), b2Vec2(0, 600 / PTM_RATIO));
	_groundBody->CreateFixture(&groundBoxDef);

	groundBox.Set(b2Vec2(0, 1000 / PTM_RATIO), b2Vec2(1000 / PTM_RATIO,
	600 / PTM_RATIO));
	_groundBody->CreateFixture(&groundBoxDef);

	groundBox.Set(b2Vec2(1000 / PTM_RATIO, 600 / PTM_RATIO),
	b2Vec2(1000 / PTM_RATIO, 0));
	_groundBody->CreateFixture(&groundBoxDef);

	//Creates body for Sprite and objects
	addBoxBodyForSprite(sprite);
	addBoxBodyForStatic(bed, bedBody);
	addBoxBodyForStatic(desk, deskBody);
	addBoxBodyForStatic(door, doorBody);

	//THE DEBUGGER FOR SHOWING SHAPES
	b2Draw *m_debugDraw = new  GLESDebugDraw(PTM_RATIO);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	m_debugDraw->SetFlags(flags);
	world->SetDebugDraw(m_debugDraw);


	//animation opacities for now
	leftAnim->setOpacity(255);
	idleAnim->setOpacity(255);
	rightAnim->setOpacity(255);
	sprite->setOpacity(255); 

	//running animations from cocos studio
	cocostudio::timeline::ActionTimeline *timeLine = CSLoader::createTimeline("idleAnimMenu.csb");
	timeLine->retain(); //released later on
	idleAnim->runAction(timeLine);
	timeLine->gotoFrameAndPlay(0,89, true);
	
	cocostudio::timeline::ActionTimeline *timeLine2 = CSLoader::createTimeline("leftAnimMenu.csb");
	timeLine2->retain(); //released later on
	leftAnim->runAction(timeLine2);
	timeLine2->gotoFrameAndPlay(0, 39, true);
	
	cocostudio::timeline::ActionTimeline *timeLine3 = CSLoader::createTimeline("rightAnimMenu.csb");
	timeLine3->retain(); //released later on
	rightAnim->runAction(timeLine3);
	timeLine3->gotoFrameAndPlay(0, 39, true);
	
	
	


auto eventListener = EventListenerKeyboard::create();

eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_A:
		charMovingLeft = true;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		charMovingRight = true;
		break;
	case EventKeyboard::KeyCode::KEY_2:
		if (playLit)
		{
				_eventDispatcher->removeAllEventListeners();
				auto scene = level2::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
		}
		
	case EventKeyboard::KeyCode::KEY_3:
		if (playLit)
		{
				_eventDispatcher->removeAllEventListeners();
				auto scene = level3::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
			
		}
		
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
			auto scene = Basement::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
		}
		
		if (quitLit) {
		exit(0);
		}
		break;
	}

};

this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, sprite);


	addChild(rootNode);
	
	this->scheduleUpdate();
	return true;


}
void NFMenu::update(float delta) {
	//Activates continuous physics
	tick();



	if (!((charMovingLeft && charMovingRight) || (!charMovingLeft && !charMovingRight))) {
		if (charMovingLeft) {

			spriteBody->SetLinearVelocity(b2Vec2(-4, 0));
			leftAnim->setOpacity(255);
			idleAnim->setOpacity(0);
			rightAnim->setOpacity(0);
			sprite->setOpacity(0);


		}
		if (charMovingRight) {

			spriteBody->SetLinearVelocity(b2Vec2(4, 0));
			leftAnim->setOpacity(0);
			idleAnim->setOpacity(0);
			rightAnim->setOpacity(255);
			sprite->setOpacity(0);
		}


	}
	else
		{
			spriteBody->SetLinearVelocity(b2Vec2(0, 0));
			leftAnim->setOpacity(0);
			idleAnim->setOpacity(255);
			rightAnim->setOpacity(0);
			sprite->setOpacity(0);
        }
		
}

