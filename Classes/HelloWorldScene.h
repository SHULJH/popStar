#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PopSprite.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(HelloWorld);

	//自动创建我们游戏中的pop10*10的矩形方阵
	void autoCreatePopSprite(cocos2d::Size size);

	//监听手势识别
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	//定于pop数据
	PopSprite *popStarSprite[10][10];

	//点击得到的POP对象
	PopSprite *getPopSprite(cocos2d::Size size, cocos2d::Point touch);

	//创建一个数组存放点击的POP
	cocos2d::__Array *poparr;

	//通过传递过来的点击pop对象获取他上下左右的数据
	cocos2d::__Array *checkPopUDLR(PopSprite *pop);

	//通过检测到的上下左右的数据来循环检测每一个的上下左右
	void checkPopISNEW(cocos2d::__Array * arrold);

	//让空白部分被上面填充
	void reDiessPopStar();
	void reDiessPopStarRun(int x);

	int column = 0;
	void reDiessPopStarRT();

	//检测游戏是否可以继续
	bool reGameOver();
};

#endif
