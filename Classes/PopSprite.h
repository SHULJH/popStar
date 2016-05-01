#pragma once
#include <cocos2d.h>

class PopSprite : public cocos2d::Sprite {
public:
	//��Ϸ��ʼ����ֵ����ȣ��߶ȣ�x�ᣬy��
	static PopSprite *createPopSprite(int numbers, int width, int height, float PopSpriteX, float PopSpriteY);
	virtual bool init();
	CREATE_FUNC(PopSprite);

	//��ȡ����
	int getNumber();
	//��������
	void setNumber(int num);

	//��ȡɫ������
	cocos2d::Point getColorBGPoint();

	//��ȡpop��λ��
	int popX, popY;
	int getPOPX();
	int getPOPY();

	void setPOPX(int x);
	void setPOPY(int y);



private:
	//��ʾ��ɫ
	int number;
	void enemyInit(int numbers, int width, int height, float PopSpriteX, float PopSpriteY);
	cocos2d::LayerColor *layerColorBG;
};