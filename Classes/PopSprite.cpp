#include "PopSprite.h"
USING_NS_CC;

PopSprite *PopSprite::createPopSprite(int numbers, int width, int height, float PopSpriteX, float PopSpriteY) {
	PopSprite *enemy = new PopSprite();
	if (enemy && enemy->init()) {
		enemy->autorelease();
		enemy->enemyInit(numbers, width, height, PopSpriteX, PopSpriteY);
		return enemy;
	}

	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool PopSprite::init() {
	if (!Sprite::init()) {
		return false;
	}
	return true;
}

void PopSprite::enemyInit(int numbers, int width, int height, float PopSpriteX, float PopSpriteY) {
	//设置初始化值
	number = numbers;
	popX = 0;
	popY = 0;

	//加入游戏每个Pop的背景颜色
	layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(200, 190, 180, 255), width-5, height-5);
	layerColorBG->setPosition(cocos2d::Point(PopSpriteX, PopSpriteY));
	this->addChild(layerColorBG);
}

cocos2d::Point PopSprite::getColorBGPoint() {
	return layerColorBG->getPosition();
}

//获取数字
int PopSprite::getNumber() {
	return number;
}
//设置数字
void PopSprite::setNumber(int num) {
	number = num;
	
	//判断数字调整格子颜色
	if (number == -1) {
		layerColorBG->setColor(cocos2d::Color3B(200, 190, 180));
	}
	else if (number == 0) {
		layerColorBG->setColor(cocos2d::Color3B(250, 230, 40));
	}
	else if (number == 1) {
		layerColorBG->setColor(cocos2d::Color3B(40, 180, 250));
	}
	else if (number == 2) {
		layerColorBG->setColor(cocos2d::Color3B(130, 220, 110));
	}
	else if (number == 3) {
		layerColorBG->setColor(cocos2d::Color3B(250, 80, 130));
	}
	else if (number == 4) {
		layerColorBG->setColor(cocos2d::Color3B(180, 50, 250));
	}
}

int PopSprite::getPOPX() {
	return popX;
}
int PopSprite::getPOPY() {
	return popY;
}

void PopSprite::setPOPX(int x) {
	popX = x;
}
void PopSprite::setPOPY(int y) {
	popY = y;
}

