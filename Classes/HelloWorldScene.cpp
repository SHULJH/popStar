#include "HelloWorldScene.h"
#include "PopSprite.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

	//创建游戏运行背景
	auto layerColorBG = cocos2d::LayerColor::create(Color4B(180, 170, 160, 255));
	this->addChild(layerColorBG);

	autoCreatePopSprite(visibleSize);

	//设置监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
	//初始化
	poparr = cocos2d::__Array::create();
	
	//获取触摸的x值和y值
	Point touchPO = touch->getLocation();

	//获取屏幕大小
	Size visibleSize = Director::getInstance()->getVisibleSize();

	PopSprite *pops = getPopSprite(visibleSize, touchPO);

	if (pops != NULL) {
		//点击的时候检测
		poparr = checkPopUDLR(pops);

		if (poparr->count() >= 2) {
			checkPopISNEW(poparr);
		}
		else {
			return true;
		}
	}

	return true;
}

void HelloWorld::checkPopISNEW(cocos2d::__Array * arrold) {
	//获取到新的数据
	cocos2d::__Array *arrnew = cocos2d::__Array::create();

	for (int i = 0; i < arrold->count(); i++) {
		PopSprite *pop = (PopSprite *)arrold->getObjectAtIndex(i);
		cocos2d::__Array *arrnews = checkPopUDLR(pop);

		for (int j = 0; j < arrnews->count(); j++) {
			bool isSave = false;
			PopSprite *popnew = (PopSprite *)arrnews->getObjectAtIndex(j);

			for (int k = 0; k < poparr->count(); k++) {
				PopSprite *popold = (PopSprite *)poparr->getObjectAtIndex(k);

				if ((popnew->getPOPY() == popold->getPOPY()) && (popnew->getPOPX() == popold->getPOPX())) {
					isSave = true;
					break;
				}
			}

			if (!isSave) {
				arrnew->addObject(popnew);
			}
		}
	}

	if (arrnew->count() > 0) {
		for (int f = 0; f < arrnew->count(); f++) {
			poparr->addObject(arrnew->getObjectAtIndex(f));
		}
		checkPopISNEW(arrnew);
	}
	else {
		//清空数据
		for (int s = 0; s < poparr->count(); s++) {
			PopSprite *sp = (PopSprite *)poparr->getObjectAtIndex(s);
			sp->setNumber(-1);
		}

		//让空白部分被填充
		reDiessPopStar();
	}
}

void HelloWorld::reDiessPopStar() {
	for (int x = 0; x < 10; x++) {
		reDiessPopStarRun(x);
	}
	//判断是否需要右移动
	reDiessPopStarRT();

	//检测游戏结束
	reGameOver();
}

bool HelloWorld::reGameOver() {
	bool isGameOver = true;

	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			if (checkPopUDLR(popStarSprite[j][i])->count() > 0 && popStarSprite[j][i]->getNumber() != -1) {
				isGameOver = false;
				break;
			}
		}
		if (isGameOver == false) {
			break;
		}
	}

	if (isGameOver) {
		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
	}
	else {
		//continue
	}

	return isGameOver;
}

void HelloWorld::reDiessPopStarRT() {
	for (int x = 0; x < 10-column; x++) {
		//检测出每列的空格数
		int number = 0;
		for (int k = 0; k < 10; k++) {
			if (popStarSprite[x][k]->getNumber() == -1) {
				number++;
			}
		}
		log("%d:%d",x, number);
		if (number == 10) {
			column++;
			for (int z = 0; z < 10; z++) {
				for (int s = x; s < 9; s++) {
					popStarSprite[s][z]->setNumber(popStarSprite[s+1][z]->getNumber());
					popStarSprite[s + 1][z]->setNumber(-1);
				}
			}
			x--;
		}
	}
}

void HelloWorld::reDiessPopStarRun(int x) {
	//检测出每列的空格数
	int number = 0;
	for (int k = 0; k < 10; k++) {
		if (popStarSprite[x][k]->getNumber() == -1) {
			number++;
		}
	}

	//判断空格是否大于1
	if (number > 0) {
		for (int y = 0; y < 10; y++) {
			//判断是否继续回调
			if (popStarSprite[x][y]->getNumber() == -1) {
				if (10 - popStarSprite[x][y]->getPOPY() > number) {
					for (int s = y; s < 10; s++) {
						if (s + 1 == 10) {
							popStarSprite[x][s]->setNumber(-1);
						}
						else {
							popStarSprite[x][s]->setNumber(popStarSprite[x][s+1]->getNumber());
						}
					}
					reDiessPopStarRun(x);
				}
				else {
					break;
				}
			}
		}
	}
}

cocos2d::__Array *HelloWorld::checkPopUDLR(PopSprite *pop) {
	cocos2d::__Array *arr = cocos2d::__Array::create();
	bool isDoublePop = false;

	//判断点击位置往上的相同数
	int up = pop->getPOPY();
	for (int yu = up + 1; yu < 10; yu++) {
		if ((popStarSprite[pop->getPOPX()][yu])->getNumber() == (popStarSprite[pop->getPOPX()][up])->getNumber()) {
			arr->addObject(popStarSprite[pop->getPOPX()][yu]);
			//popStarSprite[pop->getPOPX()][yu]->setNumber(-1);
			isDoublePop = true;
		}
		else {
			break;
		}
	}

	//判断点击位置往下的相同数
	int ud = pop->getPOPY();
	for (int yd = ud - 1; yd >= 0; yd--) {
		if ((popStarSprite[pop->getPOPX()][yd])->getNumber() == (popStarSprite[pop->getPOPX()][ud])->getNumber()) {
			arr->addObject(popStarSprite[pop->getPOPX()][yd]);
			//popStarSprite[pop->getPOPX()][yd]->setNumber(-1);
			isDoublePop = true;
		}
		else {
			break;
		}
	}

	//判断点击位置往左的相同数
	int ul = pop->getPOPX();
	for (int xl = ul - 1; xl >= 0; xl--) {
		if ((popStarSprite[xl][pop->getPOPY()])->getNumber() == (popStarSprite[ul][pop->getPOPY()])->getNumber()) {
			arr->addObject(popStarSprite[xl][pop->getPOPY()]);
			//popStarSprite[xl][pop->getPOPY()]->setNumber(-1);
			isDoublePop = true;
		}
		else {
			break;
		}
	}

	//判断点击位置往右的相同数
	int ur = pop->getPOPX();
	for (int xr = ur + 1; xr < 10; xr++) {
		if ((popStarSprite[xr][pop->getPOPY()])->getNumber() == (popStarSprite[ur][pop->getPOPY()])->getNumber()) {
			arr->addObject(popStarSprite[xr][pop->getPOPY()]);
			//popStarSprite[xr][pop->getPOPY()]->setNumber(-1);
			isDoublePop = true;
		}
		else {
			break;
		}
	}

	if (isDoublePop) {
		arr->addObject(popStarSprite[pop->getPOPX()][pop->getPOPY()]);
	}

	return arr;
}

PopSprite *HelloWorld::getPopSprite(cocos2d::Size size, cocos2d::Point touch) {
	int lon = (size.height - 28) / 10;

	//求出点击的x位置
	float x = ((touch.x-100) - 28 + lon)/lon;
	//求出点击的y位置
	float y = ((touch.y-20) - 28 + lon)/lon;
	//log("original:%f:%f", x, y);
	//log("touch:%f:%f", touch.x, touch.y);
	if (x < 10 && y < 10 && x >= 0 && y >= 0) {	
		int x1 = ((touch.x - 100) - 28 + lon) / lon;
		int y1 = ((touch.y - 20) - 28 + lon) / lon;

		//log("%d:%d", x1, y1);

		return popStarSprite[x1][y1];
	}else{
		return NULL;
	}
}

void HelloWorld::autoCreatePopSprite(cocos2d::Size size) {
	srand((unsigned)time(NULL));

	//求出每个pop的宽度和高度
	int lon = (size.height - 28) / 10;

	//10*10的pop单元格创建
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			int maxX = 5;
			int minX = 0;

			int rangeX = maxX - minX;
			int actualX = (rand() % rangeX) + minX;

			PopSprite *pop = PopSprite::createPopSprite(-1, lon, lon, lon*j+100, lon*i+20);
			pop->setPOPX(j);
			pop->setPOPY(i);
			pop->setNumber(actualX);
			addChild(pop);

			//pop加入到数组中
			popStarSprite[j][i] = pop;
		}
	}

}