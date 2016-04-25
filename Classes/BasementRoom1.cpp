#include "BasementRoom1.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocostudio\CocoStudio.h"
#include "cocostudio\ActionTimeline\CCActionTimelineNode.h"
#include "2d\CCLight.h"

#include "luaplus.h"



using namespace LuaPlus;
USING_NS_CC;
#define PTM_RATIO 30

using namespace cocostudio::timeline;
auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
LuaState* luaPState = LuaState::Create();
int result = luaPState->DoFile("stats.lua");
LuaFunction<int >getCurSanity = luaPState->GetGlobal("getCurSanity");
LuaFunction<float>  decSanityByAmount = luaPState->GetGlobal("decSanityByAmount");
LuaFunction<void> restoreSanityToMax = luaPState->GetGlobal("restoreSanityToMax");
LuaFunction<int> getHeldItem = luaPState->GetGlobal("getHeldItem");
LuaFunction<void> shiftInventoryRight = luaPState->GetGlobal("shiftInventoryRight");
LuaFunction<void> shiftInventoryLeft = luaPState->GetGlobal("shiftInventoryLeft");
LuaFunction<void> addItem = luaPState->GetGlobal("addItem");

Scene* Basement::createScene()
{
	
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Basement::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

//adds dynamic body for player
void Basement::addBoxBodyForSprite(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
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
void Basement::addBoxBodyForStatic(Node * sprite, b2Body* body)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	body = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = false;
	body->CreateFixture(&spriteShapeDef);


}

void Basement::addBoxBodyForDynamicBottle(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	keyBottleBT = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = false;
	keyBottleBT->CreateFixture(&spriteShapeDef);
}
void Basement::addBoxBodyForKey(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	keyB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	keyB->CreateFixture(&spriteShapeDef);
}

void Basement::addBoxBodyForStaticNonWall(Node * sprite, b2Body* body)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	body = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	body->CreateFixture(&spriteShapeDef);


}
//simulates physics every frame and then moves everything in BOX2D , also handles collision
void Basement::tick()
{
	
	world->Step(1.0f / 60.0f, 10, 10);
	idleAnim->setPosition(sprite->getPosition());
	walkAnim->setPosition(sprite->getPosition());
	swingAnim->setPosition(sprite->getPosition());
	for (b2Body *b = world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			CCSprite *sprite = (CCSprite *)b->GetUserData();
			sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO));
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
	//EDGE IS YOUR GUY, FIXTURE B IS WHAT YOU ARE TOUCHING
	
	 edge = spriteBody->GetContactList();
	 if (edge != NULL && edge->contact != NULL)
	 {
		 if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == downArrow)
		 {
			 downArrow->setOpacity(155);
			 if (charMovingDown)
			 {
				 spriteBody->SetTransform(b2Vec2(12, 27), 0);
				 
			 }
		 }
		 else
		 {
			 downArrow->setOpacity(0);
		 }
		
		 if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == upArrow)
		 {
			 upArrow->setOpacity(155);
			 //audio->playEffect("helpsound.wav");
			 if (charMovingUp)
			 {
				 spriteBody->SetTransform(b2Vec2(32, 5), 0);
			 }
		 }
		 else
		 {
			 upArrow->setOpacity(0);

		 }

		 if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == doorUp )
		 {
			 if (hasKey)
			 {
				 if (charMovingUp)
				 {
					 spriteBody->SetTransform(b2Vec2(41, 27), 0);

				 }
			 }
		 }
		 if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == downArrow2)
		 {
			 downArrow2->setOpacity(155);
			 //audio->playEffect("helpsound.wav");
			 if (charMovingDown)
			 {
				 spriteBody->SetTransform(b2Vec2(44, 5), 0);
			 }
			
		 }
		 else
		 {
			 downArrow2->setOpacity(0);

		 }

		 if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == crowbar)
		 {
			 if (charUsing)
			 {
				 addItem(1);
				 crowbar->setOpacity(0);
				 world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				 //crowbarB = edge->contact->GetFixtureB()->GetBody();
			 }
		 }
		 
		  if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == gasCan)
		  {
			  if (charUsing)
			  {
				  addItem(2);
				  gasCan->setOpacity(0);
				  world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				  //gasCanB = edge->contact->GetFixtureB()->GetBody();
				 // world->DestroyBody(gasCanB);
			  }
		  }
		  if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == axe)
		  {
			  if (charUsing)
			  {
				  addItem(3);
				  axe->setOpacity(0);
				  world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				  //world->DestroyBody(gasCanB);
			  }
		  }
		  if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == keyBottle)
		  {
			  if (charUsing)
			  {
				  addItem(5);
				  keyBottle->setOpacity(0);
				  world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				  //world->DestroyBody(gasCanB);
			  }
		  }
		  if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == keyBottleT && thrownBottle)
		  {
			 
			  if (charUsing)
			  {
				  addItem(6);
				 // keyBottleT->setOpacity(0);
				  world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				 // world->DestroyBody(keyB);
				  key->setOpacity(0);
				  //world->DestroyBody(gasCanB);
			  }
		  }
		  if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == bottle && glassBroken == true)
		  {
			  if (charUsing)
			  {
				  addItem(4);
				  bottle->setOpacity(0);
				  world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				  //world->DestroyBody(gasCanB);
			  }
		  }
		
	 }
	
}

//for debugging
void Basement::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	kmGLPushMatrix();
	world->DrawDebugData();
	kmGLPopMatrix();
}




// on "init" you need to initialize your instance
bool Basement::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//load the csb
	auto rootNode = CSLoader::createNode("BasementRoom1.csb");
	
	audio->playBackgroundMusic("ambience.wav",true);

	//set the variables
	sprite = rootNode->getChildByName("player");
	upArrow = rootNode->getChildByName("upArrow");
	downArrow = rootNode->getChildByName("downArrow");
	downArrow2 = rootNode->getChildByName("downArrow2");
	doorUp = rootNode->getChildByName("doorUp");
	doorDown = rootNode->getChildByName("doorDown");
	

	crowbar = rootNode->getChildByName("crobar");
	axe = rootNode->getChildByName("axe");
	bottle = rootNode->getChildByName("bottle");
	glass = rootNode->getChildByName("glass");
	keyBottle = rootNode->getChildByName("keyinglass");
	keyBottleT = rootNode->getChildByName("keyinglassT");
	key = rootNode->getChildByTag(46);
	gasCan = rootNode->getChildByName("gascan");

	idleAnim = rootNode->getChildByName("idleLeft");
	walkAnim = rootNode->getChildByName("walkLeft");
	swingAnim = rootNode->getChildByName("swingLeft");
	

	floor = rootNode->getChildByName("floor");
	
	leftwall = rootNode->getChildByName("leftwall");
	rightwall = rootNode->getChildByName("rightwall");
	ceiling = rootNode->getChildByName("ceiling");

	floor2 = rootNode->getChildByName("floor2");
	leftwall2 = rootNode->getChildByName("leftwall2");
	rightwall2 = rootNode->getChildByName("rightwall2");
	ceiling2 = rootNode->getChildByName("ceiling2");

	lockedwall = rootNode->getChildByName("lockedwall");
	leftwall3 = rootNode->getChildByName("leftwall3");
	rightwall3 = rootNode->getChildByName("rightwall3");
	key->setOpacity(0);
	keyBottleT->setOpacity(0);
	//Creates World
	b2Vec2 gravity = b2Vec2(0.0f, -9.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(false);
	world->SetContinuousPhysics(true);
	contactListener = new b2ContactListener();
	world->SetContactListener(contactListener);
	
	//ADD BODIES TO EVERYthING
	addBoxBodyForSprite(sprite);
	
	addBoxBodyForStatic(floor, floorB);
	addBoxBodyForStatic(floor2, floor2B);
	addBoxBodyForStatic(leftwall, leftwallB);
	addBoxBodyForStatic(leftwall2,leftwall2B);
	addBoxBodyForStatic(leftwall3, leftwall3B);
	addBoxBodyForStatic(rightwall, rightwallB);
	addBoxBodyForStatic(rightwall2, rightwall2B);
	addBoxBodyForStatic(rightwall3, rightwall3B);
	addBoxBodyForStatic(ceiling, ceilingB);
	addBoxBodyForStatic(ceiling2, ceiling2B);
	addBoxBodyForStatic(lockedwall, lockedwallB);
	
	addBoxBodyForStaticNonWall(downArrow, downArrowB);
	addBoxBodyForStaticNonWall(upArrow, upArrowB);
	addBoxBodyForStaticNonWall(doorDown, doorDownB);
	addBoxBodyForStaticNonWall(doorUp, doorUpB);
	addBoxBodyForStaticNonWall(downArrow2, arrowDownB2);
	addBoxBodyForStaticNonWall(axe, axeB);
	addBoxBodyForStaticNonWall(crowbar, crowbarB);
	addBoxBodyForStaticNonWall(gasCan, gasCanB);
	addBoxBodyForStaticNonWall(glass, glassB);
	//addBoxBodyForKey(key);
	addBoxBodyForStaticNonWall(bottle, bottleB);
	addBoxBodyForDynamicBottle(keyBottleT);
	addBoxBodyForStaticNonWall(keyBottle, keyBottleB);
	

	
	
	//DEBUGGER
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
	idleAnim->setOpacity(255);
	walkAnim->setOpacity(0);
	swingAnim->setOpacity(0);
	sprite->setOpacity(0);

	

	//running animations from cocos studio
	cocostudio::timeline::ActionTimeline *timeLine = CSLoader::createTimeline("detectiveIdle.csb");
	timeLine->retain(); //released later on
	idleAnim->runAction(timeLine);
	timeLine->gotoFrameAndPlay(0, 33, true);

	cocostudio::timeline::ActionTimeline *timeLine2 = CSLoader::createTimeline("detectiveWalk.csb");
	timeLine2->retain(); //released later on
	walkAnim->runAction(timeLine2);
	timeLine2->gotoFrameAndPlay(0, 19, true);

	cocostudio::timeline::ActionTimeline *timeLine3 = CSLoader::createTimeline("detectiveSwing.csb");
	timeLine3->retain(); //released later on
	swingAnim->runAction(timeLine3);
	timeLine3->gotoFrameAndPlay(0, 38, true);

	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {

		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_A:
			charMovingLeft = true;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			charMovingRight = true;
			break;
		case EventKeyboard::KeyCode::KEY_W:
			charMovingUp = true;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			charMovingDown = true;
			break;
		case EventKeyboard::KeyCode::KEY_E:
			charUsing = true;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			charRun = true;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			charSwing = true;
			break;
		case EventKeyboard::KeyCode::KEY_Z:
			invL = true;
			break;
		case EventKeyboard::KeyCode::KEY_X:
			invR = true;
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
		case EventKeyboard::KeyCode::KEY_W:
			charMovingUp = false;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			charMovingDown = false;
			break;
		case EventKeyboard::KeyCode::KEY_E:
			charUsing = false;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			charRun = false;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			charSwing = false;
			break;
		case EventKeyboard::KeyCode::KEY_Z:
			invL = false;
			break;
		case EventKeyboard::KeyCode::KEY_X:
			invR = false;
			break;
		
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, sprite);
	
	rootNode->setOpacity(255);

	//FOR INVENTORY ITEMS DISREGARD... FIRST ONE
	display = cocos2d::Sprite::create("glass.png");
	display2 = cocos2d::Sprite::create("crobar.png");
	display3 = cocos2d::Sprite::create("axe.png");
	display4 = cocos2d::Sprite::create("gascan.png");
	display5 = cocos2d::Sprite::create("bottle.png");
	display6 = cocos2d::Sprite::create("keyinglass.png");
	display7 = cocos2d::Sprite::create("key.png");

	display->setOpacity(75);
	display->setScale(.5);
	display2->setOpacity(0);
	display3->setOpacity(0);
	display4->setOpacity(0);
	display5->setOpacity(0);
	display6->setOpacity(0);
	display7->setOpacity(0);
	//keyBottleT->setOpacity(255);
	addChild(rootNode);
	this->addChild(display);
	this->addChild(display2);
	this->addChild(display3);
	this->addChild(display4);
	this->addChild(display5);
	this->addChild(display6);
	this->addChild(display7);


	this->scheduleUpdate();
	


	
	//LuaFunction<int> getCurSanity = luaPState->GetGlobal("getCurSanity"); //getCurSanity returns an int.
	//int sanity = getCurSanity();
	
	//
	//sanity = decSanityByAmount(50); //Sanity is now 50.
									//Restore sanity
	//LuaFunction<void> restoreSanityToMax = luaPState->GetGlobal("restoreSanityToMax");
	//restoreSanityToMax(); //Sanity is now 100.
	//sanity = getCurSanity(); //Get the current sanity.
							 
	// //Returns an int.
	//LuaFunction<void> shiftInventoryRight = luaPState->GetGlobal("shiftInventoryRight"); //Shifts the inventory to the right.
	//LuaFunction<void> shiftInventoryLeft = luaPState->GetGlobal("shiftInventoryLeft"); //Shifts the inventory to the left.
	//LuaFunction<void> addItem = luaPState->GetGlobal("addItem");
	//addItem();
	//shiftInventoryLeft(); //Moves the pointer left until it finds a non negative-1 value.
	//shiftInventoryRight(); //Moves the pointer right until it finds a non negative-1 value.

	//LuaState::Destroy(luaPState); //Close lua file.
	
	return true;
}

void Basement::update(float delta) {
	tick(); // runs physics and collissions

	this->runAction(CCFollow::create(sprite, Rect(0, 0, 3000, 1200))); // camera follows player 

	display->setPosition(sprite->getPositionX() - 200, sprite->getPositionY() + 300);      // sets position of the inventory image
	display2->setPosition(sprite->getPositionX() - 200, sprite->getPositionY() + 300);
	display3->setPosition(sprite->getPositionX() - 200, sprite->getPositionY() + 300);
	display4->setPosition(sprite->getPositionX() - 200, sprite->getPositionY() + 300);
	display5->setPosition(sprite->getPositionX() - 200, sprite->getPositionY() + 300);
	display6->setPosition(sprite->getPositionX() - 200, sprite->getPositionY() + 300);
	display7->setPosition(sprite->getPositionX() - 200, sprite->getPositionY() + 300);
	
	key->setPosition(keyBottleT->getPosition());
	//if (keyBottleBT != NULL)
	//{
	//
		//keyB->SetTransform(keyBottleBT->GetPosition(), 0);
		//if (thrownBottle)
		//{
	//		keyBottleT->setOpacity(0);
			
		//}
		
	//}
	
	id = getHeldItem();  // displays depending on invetory item
	if (id == 1)
	{
		
		display2->setOpacity(155);
		display3->setOpacity(0);
		display4->setOpacity(0);
		display5->setOpacity(0);
		display6->setOpacity(0);
		display7->setOpacity(0);
		
	}
	if (id == 2)

	{
		
		display2->setOpacity(0);
		display3->setOpacity(0);
		display4->setOpacity(155);
		display5->setOpacity(0);
		display6->setOpacity(0);
		display7->setOpacity(0);
	}
	if (id == 3)

	{
		
		display2->setOpacity(0);
		display3->setOpacity(155);
		display4->setOpacity(0);
		display5->setOpacity(0);
		display6->setOpacity(0);
		display7->setOpacity(0);
	}
	if (id == 4)

	{
		
		display2->setOpacity(0);
		display3->setOpacity(0);
		display4->setOpacity(0);
		display5->setOpacity(155);
		display6->setOpacity(0);
		display7->setOpacity(0);
	}
	if (id == 5)

	{

		display2->setOpacity(0);
		display3->setOpacity(0);
		display4->setOpacity(0);
		display5->setOpacity(0);
		display6->setOpacity(155);
		display7->setOpacity(0);
		if (charSwing && thrownBottle == false)
		{
			keyBottleBT->SetTransform(spriteBody->GetPosition(), 0);
			keyBottleT->setOpacity(0);
			if (movedL)
				keyBottleBT->ApplyForce(b2Vec2(-15, 0), keyBottleBT->GetWorldCenter(), true);
			if (movedR)
				keyBottleBT->ApplyForce(b2Vec2(15, 0), keyBottleBT->GetWorldCenter(), true);
			key->setOpacity(255);
			
			thrownBottle = true;
			
		}
	}
	if (id == 6)
	{
		display2->setOpacity(0);
		display3->setOpacity(0);
		display4->setOpacity(0);
		display5->setOpacity(0);
		display6->setOpacity(0);
		display7->setOpacity(155);
		hasKey = true;
	}
	
	if (invL)
	{
		shiftInventoryLeft();
	}
	if (invR)
	{
		shiftInventoryRight();
		
	}

	if (!((charMovingLeft && charMovingRight) || (!charMovingLeft && !charMovingRight))) {
		if (charMovingLeft) {
			
			spriteBody->SetLinearVelocity(b2Vec2(-4, 0));
			walkAnim->setOpacity(255);
			walkAnim->setScaleX(1);
			swingAnim->setScaleX(1);
			swingAnim->setOpacity(0);
			idleAnim->setOpacity(0);
			idleAnim->setScaleX(1);
			sprite->setOpacity(0);
			movedL = true;
			movedR = false;
			if(charRun)
				spriteBody->SetLinearVelocity(b2Vec2(-8, 0));
			//if (charSwing)
			//{
			//	walkAnim->setOpacity(0);
			//	swingAnim->setOpacity(255);
				
		//	}
			

		}
		if (charMovingRight) {
			
			spriteBody->SetLinearVelocity(b2Vec2(4, 0));
			idleAnim->setOpacity(0);
			idleAnim->setScaleX(-1);
			sprite->setOpacity(0);
			walkAnim->setOpacity(255);
			walkAnim->setScaleX(-1);
			swingAnim->setScaleX(-1);
			swingAnim->setOpacity(0);
			
			movedL = false;
			movedR = true;
			if (charRun)
				spriteBody->SetLinearVelocity(b2Vec2(8, 0));
			//if (charSwing)
			//{
			//	walkAnim->setOpacity(0);
			//	swingAnim->setOpacity(255);
			//}
			
		}


	}
	else
	{
		spriteBody->SetLinearVelocity(b2Vec2(0, 0));
		walkAnim->setOpacity(0);
		
		sprite->setOpacity(0);

		if (movedL)
		{
			idleAnim->setOpacity(255);
			idleAnim->setScaleX(1);
			swingAnim->setOpacity(0);
			swingAnim->setScaleX(1);
		//	if (charSwing)
		//	{
		//		idleAnim->setOpacity(0);
		//		swingAnim->setOpacity(255);
				
		//	}
			
		}
		if (movedR)
		{
			idleAnim->setOpacity(255);
			idleAnim->setScaleX(-1);
			swingAnim->setScaleX(-1);
			swingAnim->setOpacity(0);
			//if (charSwing)
			//{
			//	idleAnim->setOpacity(0);
			//	swingAnim->setOpacity(255);
				
		//	}
			
		}
	}
	


}