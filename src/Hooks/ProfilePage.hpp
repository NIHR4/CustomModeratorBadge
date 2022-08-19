#pragma once
#include <cocos2d.h>

class GJUserScore{
    char padding_00[0x1D4];
public:
    int m_modBadgeValue;
};


class ProfilePage : public cocos2d::CCLayer{
private:
    cocos2d::CCSprite* getModBadgeSprite();
    cocos2d::CCPoint getModBadgePosition();
public:
    void loadPageFromUserInfo(GJUserScore* userScore);
    static bool hookInit();
};
