#include "BasementRoom1.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocostudio\CocoStudio.h"
#include "cocostudio\ActionTimeline\CCActionTimelineNode.h"
#include "2d\CCLight.h"
#include "MenuScene.h"
#include "level2.h"
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
LuaFunction<void> setHeldItem = luaPState->GetGlobal("setHeldItem");
LuaFunction<void> shiftInventoryRight = luaPState->GetGlobal("shiftInventoryRight");
LuaFunction<void> shiftInventoryLeft = luaPState->GetGlobal("shiftInventoryLeft");
LuaFunction<void> addItem = luaPState->GetGlobal("addItem");
LuaFunction<void> removeItem = luaPState->GetGlobal("removeItem");


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
void Basement::addBoxBodyForDynamicBottleT(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	bottleTB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = false;
	bottleTB->CreateFixture(&spriteShapeDef);
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
void Basement::addBoxBodyForStaticWALL(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	lockedwallB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = false;
	lockedwallB->CreateFixture(&spriteShapeDef);
}
void Basement::addBoxBodyForStaticArrow(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_staticBody;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	downArrowB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO / 2 * sprite->getScaleX(),
		sprite->getContentSize().height / PTM_RATIO / 2 * sprite->getScaleY());
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	downArrowB->CreateFixture(&spriteShapeDef);
}
void Basement::addBoxBodyForEnemy(Node * sprite)
{
	sprite->setAnchorPoint(Vec2(.5, .5));
	b2BodyDef spriteBodyDef;
	spriteBodyDef.type = b2_dynamicBody;
	spriteBodyDef.gravityScale = 0;
	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO,
		sprite->getPositionY() / PTM_RATIO);
	spriteBodyDef.userData = sprite;
	enemyB = world->CreateBody(&spriteBodyDef);

	b2PolygonShape spriteShape;
	spriteShape.SetAsBox(sprite->getContentSize().width / PTM_RATIO /6,
		sprite->getContentSize().height / PTM_RATIO /6 );
	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &spriteShape;
	spriteShapeDef.density = 1.0;
	spriteShapeDef.isSensor = true;
	enemyB->CreateFixture(&spriteShapeDef);
}
//simulates physics every frame and then moves everything in BOX2D , also handles collision
void Basement::tick()
{

	world->Step(1.0f / 60.0f, 10, 10);
	idleAnim->setPosition(sprite->getPosition());
	walkAnim->setPosition(sprite->getPosition());
	swingAnim->setPosition(sprite->getPosition());
	enemyIdle->setPosition(enemy->getPosition());
	enemyDying->setPosition(enemy->getPosition());
	heal->setPosition(sprite->getPosition());
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
	
	
	while (edge != NULL && edge->contact != NULL && destroyLUA == false)
	{
		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == downArrow)
		{
			downArrow->setOpacity(30);
			if (charMovingDown)
			{
				spriteBody->SetTransform(b2Vec2(12, 27), 0);

			}
		}
		

		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == upArrow)
		{
			upArrow->setOpacity(30);
			//audio->playEffect("helpsound.wav");
			if (charMovingUp)
			{
				spriteBody->SetTransform(b2Vec2(32, 5), 0);
			}
		}
		

		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == doorUp)
		{
			if (hasKey)
			{
				if (charMovingUp)
				{
					spriteBody->SetTransform(b2Vec2(41, 27), 0);

				}
			}
			else
				
				audio->playEffect("knock.wav");
		}
		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == downArrow2)
		{
			downArrow2->setOpacity(30);
			//audio->playEffect("helpsound.wav");
			if (charMovingDown)
			{
				spriteBody->SetTransform(b2Vec2(44, 5), 0);
			}

		}
		

		if (edge->contact->GetFixtureB()->GetBody()->GetUserData() == crowbar)
		{
			if (charUsing)
			{
				addItem(1);
				setHeldItem(1);
				crowbar->setOpacity(0);
				world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				audio->playEffect("pickup.wav");
				//crowbarB = edge->contact->GetFixtureB()->GetBody();
			}
		}

		if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == gasCan)
		{
			if (charUsing)
			{
				addItem(2);
				setHeldItem(2);
				gasCan->setOpacity(0);
				world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				auto action = FadeOut::create(1);
				girl1->setOpacity(175);
				//audio->playEffect("pickup.wav");
				audio->playEffect("girl1.wav");
				girl1->runAction(action);

				//gasCanB = edge->contact->GetFixtureB()->GetBody();
				// world->DestroyBody(gasCanB);
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == axe)
		{
			if (charUsing)
			{
				addItem(3);
				setHeldItem(3);
				axe->setOpacity(0);
				world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				auto action = FadeOut::create(2);
				girl2->setOpacity(175);
				//audio->playEffect("pickup.wav");
				audio->playEffect("girl2.wav");
				auto moveBy = MoveBy::create(2, Vec2(-100, 0));
				girl2->runAction(moveBy);
				girl2->runAction(action);
				//world->DestroyBody(gasCanB);
			}

		}
		if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == keyBottle)
		{
			if (charUsing)
			{
				addItem(5);
				setHeldItem(5);
				keyBottle->setOpacity(0);
				world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				audio->playEffect("pickup.wav");
				//world->DestroyBody(gasCanB);
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == keyBottleT && thrownBottle)
		{

			if (charUsing)
			{
				addItem(6);
				setHeldItem(6);
				// keyBottleT->setOpacity(0);
				world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				//audio->playEffect("pickup.wav");
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
				setHeldItem(4);
				bottle->setOpacity(0);
				world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				auto action = FadeOut::create(3);
				//audio->playEffect("pickup.wav");
				girl3->setOpacity(175);
				auto moveBy = MoveBy::create(2, Vec2(-100, 0));
				girl3->runAction(moveBy);
				audio->playEffect("girl3.wav");
				girl3->runAction(action);
				
				//world->DestroyBody(gasCanB);
			}
		}
		//if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == bottleT && thrownBottleT==true)
	//	{
		//	if (charUsing)
		//	{
		//		addItem(4);
		//		setHeldItem(4);
		//		bottleT->setOpacity(0);
				//world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				//addBoxBodyForDynamicBottleT(bottleT);
		//		thrownBottleT = false;
				//world->DestroyBody(gasCanB);
			//}
		//}
		if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == glass && display2->getOpacity() > 0)
		{
			if (charUsing)
			{
				
				//crowbar->runAction(moveBy);
				world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				glass->setOpacity(0);
				glassBroken = true;
				//world->DestroyBody(gasCanB);
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() ==logs && display3->getOpacity() > 0)
		{
			if (charUsing)
			{
				addItem(7);
				setHeldItem(7);
				logs->setOpacity(0);
				world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				//world->DestroyBody(gasCanB);
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == wallFire)
		{
			if (charUsing)
			{
				if (display4->getOpacity() > 0)
				{
					removeItem(2);
					display4->setOpacity(0);
					gasCanEXP->setOpacity(255);
					audio->playEffect("ritual.wav");
				}
				if (display->getOpacity() > 0)
				{
					removeItem(7);
					logsEXP->setOpacity(255);
					display->setOpacity(0);
					audio->playEffect("ritual.wav");
				}
				if (display5->getOpacity() > 0)
				{
					removeItem(4);
					bottleT->setOpacity(255);
					display5->setOpacity(0);
					audio->playEffect("ritual.wav");
				}

			}
			
		}
		if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == lightWin)
		{
			if (win)
			{
				kill = true;
				
				heal->setVisible(true);
			}
		}
		if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == enemy)
		{
			if (kill)
			{
				enemyB->SetLinearVelocity(b2Vec2(0, -2));
				enemyIdle->setOpacity(0);
				enemyDying->setOpacity(255);
				auto action = FadeOut::create(1);
				enemyDying->runAction(action);
				audio->playEffect("scary1.wav");
				world->DestroyBody(edge->contact->GetFixtureB()->GetBody());
				kill = false;
				audio->stopBackgroundMusic();
				audio->playBackgroundMusic("ambience.wav");
				leaveGame = true;
				
			}
			else
			{
				audio->stopAllEffects();
				auto scene = NFMenu::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
				destroyLUA = true;
				//LuaState::Destroy(luaPState);
				//removeItem(1);
				//removeItem(3);
			}
		}

		if (edge->contact->GetFixtureB()->GetBody() != NULL && edge->contact->GetFixtureB()->GetBody()->GetUserData() == leave)
		{
			if (leaveGame)
			{
				audio->stopAllEffects();
				//removeItem(1);
				//removeItem(3);
				//LuaState::Destroy(luaPState);
				destroyLUA = true;
				auto scene = level2::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
			}
		}


		edge = edge->next;
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

	audio->playBackgroundMusic("ambience.wav", true);

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

	logs = rootNode->getChildByName("logs");
	logsEXP= rootNode->getChildByName("logsEXP");
	wallFire = rootNode->getChildByName("wallfireSPOT");
	gasCanEXP = rootNode->getChildByName("gascanEXP");

	explosion = rootNode->getChildByName("explosion");
	explosionFire = rootNode->getChildByName("explosionFire");
	bottleT = rootNode->getChildByName("bottleT");

	enemy = rootNode->getChildByTag(57);
	enemyIdle = rootNode->getChildByTag(101);
	enemyDying = rootNode->getChildByTag(87);
	lightWin = rootNode->getChildByName("lightWin");
	heal = rootNode->getChildByName("heal");

	girl1 = rootNode->getChildByName("girl1");
	girl2 = rootNode->getChildByName("girl2");
	girl3 = rootNode->getChildByName("girl3");

	leave = rootNode->getChildByName("leave");
	

	girl1->setOpacity(0);
	girl2->setOpacity(0);
	girl3->setOpacity(0);
	lightWin->setOpacity(0);
	enemy->setOpacity(0);
	enemyDying->setOpacity(0);
	
	//enemyP = enemyB->GetPosition();
	map2 = rootNode->getChildByTag(69);
	map2->setOpacity(0);
	gasCanEXP->setOpacity(0);
	logsEXP->setOpacity(0);
	key->setOpacity(0);
	keyBottleT->setOpacity(0);
	explosion->setVisible(false);
	explosionFire->setVisible(false);
	bottleT->setOpacity(0);
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
	addBoxBodyForStatic(leftwall2, leftwall2B);
	addBoxBodyForStatic(leftwall3, leftwall3B);
	addBoxBodyForStatic(rightwall, rightwallB);
	addBoxBodyForStatic(rightwall2, rightwall2B);
	addBoxBodyForStatic(rightwall3, rightwall3B);
	addBoxBodyForStatic(leave, leaveB);
	addBoxBodyForStatic(ceiling, ceilingB);
	addBoxBodyForStatic(ceiling2, ceiling2B);
	addBoxBodyForStaticWALL(lockedwall);

	addBoxBodyForStaticArrow(downArrow);
	addBoxBodyForStaticNonWall(upArrow, upArrowB);
	//addBoxBodyForStaticNonWall(doorDown, doorDownB);
	addBoxBodyForStaticNonWall(doorUp, doorUpB);
	addBoxBodyForStaticNonWall(downArrow2, arrowDownB2);
	addBoxBodyForStaticNonWall(axe, axeB);
	addBoxBodyForStaticNonWall(wallFire, wallfireB);
	addBoxBodyForStaticNonWall(logs, logsB);
	addBoxBodyForStaticNonWall(crowbar, crowbarB);
	addBoxBodyForStaticNonWall(gasCan, gasCanB);
	addBoxBodyForStaticNonWall(glass, glassB);
	addBoxBodyForStaticNonWall(lightWin, lightB);
	addBoxBodyForEnemy(enemy);
	//addBoxBodyForKey(key);
	addBoxBodyForStaticNonWall(bottle, bottleB);
	addBoxBodyForDynamicBottle(keyBottleT);
	addBoxBodyForStaticNonWall(keyBottle, keyBottleB);
	//addBoxBodyForDynamicBottleT(bottleT);




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
	enemyIdle->setOpacity(0);


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


	cocostudio::timeline::ActionTimeline *timeLine4 = CSLoader::createTimeline("enemyIdle.csb");
	timeLine4->retain(); //released later on
	enemyIdle->runAction(timeLine4);
	timeLine4->gotoFrameAndPlay(0, 31, true);

	cocostudio::timeline::ActionTimeline *timeLine5 = CSLoader::createTimeline("enemyDying.csb");
	timeLine5->retain(); //released later on
	enemyDying->runAction(timeLine5);
	timeLine5->gotoFrameAndPlay(0, 83, true);

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
		//case EventKeyboard::KeyCode::KEY_Z:
			//invL = false;
			//break;
		//case EventKeyboard::KeyCode::KEY_X:
			//invR = false;
			//break;

		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, sprite);

	rootNode->setOpacity(255);

	//FOR INVENTORY ITEMS DISREGARD... FIRST ONE
	display = cocos2d::Sprite::create("logs.png");
	display2 = cocos2d::Sprite::create("crobar.png");
	display3 = cocos2d::Sprite::create("axe.png");
	display4 = cocos2d::Sprite::create("gascan.png");
	display5 = cocos2d::Sprite::create("bottle.png");
	display6 = cocos2d::Sprite::create("keyinglass.png");
	display7 = cocos2d::Sprite::create("key.png");

	//display->setOpacity(75);
	//display->setScale(.5);
	display->setOpacity(0);
	display2->setOpacity(0);
	display3->setOpacity(0);
	display4->setOpacity(0);
	display5->setOpacity(0);
	display6->setOpacity(0);
	display7->setOpacity(0);
	//keyBottleT->setOpacity(255);
	addChild(rootNode);
	//this->addChild(display);
	this->addChild(display);
	this->addChild(display2);
	this->addChild(display3);
	this->addChild(display4);
	this->addChild(display5);
	this->addChild(display6);
	this->addChild(display7);

	
	this->scheduleUpdate();


	return true;
}

void Basement::update(float delta) {
	tick(); // runs physics and collissions
	
	this->runAction(CCFollow::create(sprite, Rect(0, 0, 3000, 1200))); // camera follows player 
	
	display->setPosition(sprite->getPositionX()- 20 , sprite->getPositionY()-20 );      // sets position of the inventory image
	display2->setPosition(sprite->getPositionX()-20 , sprite->getPositionY()-20 );
	display3->setPosition(sprite->getPositionX()-20 , sprite->getPositionY()-20 );
	display4->setPosition(sprite->getPositionX()-20 , sprite->getPositionY()-20 );
	display5->setPosition(sprite->getPositionX()-20 , sprite->getPositionY()-20 );
	display6->setPosition(sprite->getPositionX()-20 , sprite->getPositionY()-20 );
	display7->setPosition(sprite->getPositionX()-20 , sprite->getPositionY()-20 );

	key->setPosition(keyBottleT->getPosition());
	
	if (gasCanEXP->getOpacity() > 0 && bottleT->getOpacity() > 0 && logsEXP->getOpacity() > 0)
	{
		bottleT->setOpacity(0);
		logsEXP->setOpacity(0);
		gasCanEXP->setOpacity(0);
			explosion->setVisible(true);
			explosionFire->setVisible(true);
			map2->setOpacity(255);
			world->DestroyBody(lockedwallB);
			world->DestroyBody(downArrowB);
			removeItem(6);
			//enemyB->SetTransform(enemyP,0);
			enemyIdle->setOpacity(255);
			enemyB->SetLinearVelocity(b2Vec2(-5, 0));
			audio->stopBackgroundMusic();
			audio->playBackgroundMusic("Horror.wav");
			win = true;
			
	}
	if (kill == true)
	{
		
		heal->setVisible(true);
		explosion->setVisible(false);
		explosionFire->setVisible(false);
	}

	id = getHeldItem();  // displays depending on invetory item
	if (id == 1)
	{
		display->setOpacity(0);
		display2->setOpacity(155);
		display3->setOpacity(0);
		display4->setOpacity(0);
		display5->setOpacity(0);
		display6->setOpacity(0);
		display7->setOpacity(0);

	}
	if (id == 2)

	{
		display->setOpacity(0);
		display2->setOpacity(0);
		display3->setOpacity(0);
		display4->setOpacity(155);
		display5->setOpacity(0);
		display6->setOpacity(0);
		display7->setOpacity(0);
	}
	if (id == 3)

	{
		display->setOpacity(0);
		display2->setOpacity(0);
		display3->setOpacity(155);
		display4->setOpacity(0);
		display5->setOpacity(0);
		display6->setOpacity(0);
		display7->setOpacity(0);
	}
	if (id == 4)

	{
		display->setOpacity(0);
		display2->setOpacity(0);
		display3->setOpacity(0);
		display4->setOpacity(0);
		display5->setOpacity(155);
		display6->setOpacity(0);
		display7->setOpacity(0);
	}
	if (id == 5)

	{
		display->setOpacity(0);
		display2->setOpacity(0);
		display3->setOpacity(0);
		display4->setOpacity(0);
		display5->setOpacity(0);
		display6->setOpacity(155);
		display7->setOpacity(0);
		
		
	}
	if (id == 6)
	{
		display->setOpacity(0);
		display2->setOpacity(0);
		display3->setOpacity(0);
		display4->setOpacity(0);
		display5->setOpacity(0);
		display6->setOpacity(0);
		display7->setOpacity(155);
		
	}
	if (id == 7)
	{
		display->setOpacity(155);
		display2->setOpacity(0);
		display3->setOpacity(0);
		display4->setOpacity(0);
		display5->setOpacity(0);
		display6->setOpacity(0);
		display7->setOpacity(0);

	}

	if (display6->getOpacity() > 0 && thrownBottle == false)
	{
		if (charSwing  )
		{
			keyBottleBT->SetTransform(spriteBody->GetPosition(), 1);
			keyBottleT->setOpacity(0);
			if (movedL)
				keyBottleBT->ApplyForce(b2Vec2(-15, 0), keyBottleBT->GetWorldCenter(), true);
			if (movedR)
				keyBottleBT->ApplyForce(b2Vec2(15, 0), keyBottleBT->GetWorldCenter(), true);
			key->setOpacity(255);
			removeItem(5);
			shiftInventoryLeft();
			display6->setOpacity(0);

			thrownBottle = true;
		}
	}
	if (display7->getOpacity() > 0)
		hasKey = true;
	else
		hasKey = false;

	//if (display5->getOpacity() > 0 && thrownBottleT == false)
	//{
		//if (charSwing)
		//{
		
		//	bottleTB->SetTransform(spriteBody->GetPosition(), 1);
		//	bottleT->setOpacity(255);
		//	if (movedL)
		//			bottleTB->ApplyForce(b2Vec2(-15, 0), keyBottleBT->GetWorldCenter(), true);
		//	if (movedR)
		//		bottleTB->ApplyForce(b2Vec2(15, 0), keyBottleBT->GetWorldCenter(), true);
		//	removeItem(4);
		//	shiftInventoryLeft();
		//	display5->setOpacity(0);

		//	thrownBottleT = true;
		//}
	//}
	if (invL)
	{
		shiftInventoryLeft();
		invL = false;
	}
	if (invR)
	{
		shiftInventoryRight();
		invR = false;
	}

	if (!((charMovingLeft && charMovingRight) || (!charMovingLeft && !charMovingRight))) {
		if (charMovingLeft) {
			//audio->playEffect("footsteps.wav");
			spriteBody->SetLinearVelocity(b2Vec2(-4.5, 0));
			walkAnim->setOpacity(255);
			walkAnim->setScaleX(1);
			swingAnim->setScaleX(1);
			//swingAnim->setOpacity(0);
			idleAnim->setOpacity(0);
			idleAnim->setScaleX(1);
			sprite->setOpacity(0);
			movedL = true;
			movedR = false;
			if (charRun)
				spriteBody->SetLinearVelocity(b2Vec2(-28, 0));
			//if (charSwing)
			//{
			//	walkAnim->setOpacity(0);
			//	swingAnim->setOpacity(255);

			//	}


		}
		if (charMovingRight) {
			//audio->playEffect("footsteps.wav");
			spriteBody->SetLinearVelocity(b2Vec2(4.5, 0));
			idleAnim->setOpacity(0);
			idleAnim->setScaleX(-1);
			sprite->setOpacity(0);
			walkAnim->setOpacity(255);
			walkAnim->setScaleX(-1);
			swingAnim->setScaleX(-1);
			//swingAnim->setOpacity(0);

			movedL = false;
			movedR = true;
			if (charRun)
				spriteBody->SetLinearVelocity(b2Vec2(28, 0));
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
			//swingAnim->setOpacity(0);
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
			//swingAnim->setOpacity(0);
			//if (charSwing)
			//{
			//	idleAnim->setOpacity(0);
			//	swingAnim->setOpacity(255);

			//	}

		}
	}
}