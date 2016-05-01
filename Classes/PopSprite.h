#pragma once
#include <cocos2d.h>

class PopSprite : public cocos2d::Sprite {
public:
	//游戏初始化数值，宽度，高度，x轴，y轴
	static PopSprite *createPopSprite(int numbers, int width, int height, float PopSpriteX, float PopSpriteY);
	virtual bool init();
	CREATE_FUNC(PopSprite);

	//获取数字
	int getNumber();
	//设置数字
	void setNumber(int num);

	//获取色块坐标
	cocos2d::Point getColorBGPoint();

	//获取pop的位置
	int popX, popY;
	int getPOPX();
	int getPOPY();

	void setPOPX(int x);
	void setPOPY(int y);



private:
	//显示颜色
	int number;
	void enemyInit(int numbers, int width, int height, float PopSpriteX, float PopSpriteY);
	cocos2d::LayerColor *layerColorBG;
};