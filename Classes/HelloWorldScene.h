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

	//�Զ�����������Ϸ�е�pop10*10�ľ��η���
	void autoCreatePopSprite(cocos2d::Size size);

	//��������ʶ��
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	//����pop����
	PopSprite *popStarSprite[10][10];

	//����õ���POP����
	PopSprite *getPopSprite(cocos2d::Size size, cocos2d::Point touch);

	//����һ�������ŵ����POP
	cocos2d::__Array *poparr;

	//ͨ�����ݹ����ĵ��pop�����ȡ���������ҵ�����
	cocos2d::__Array *checkPopUDLR(PopSprite *pop);

	//ͨ����⵽���������ҵ�������ѭ�����ÿһ������������
	void checkPopISNEW(cocos2d::__Array * arrold);

	//�ÿհײ��ֱ��������
	void reDiessPopStar();
	void reDiessPopStarRun(int x);

	int column = 0;
	void reDiessPopStarRT();

	//�����Ϸ�Ƿ���Լ���
	bool reGameOver();
};

#endif
