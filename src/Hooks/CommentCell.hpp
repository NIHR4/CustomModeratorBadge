#pragma once
#include <cocos2d.h>

class GJComment{
    char padding_00[0x154];
public:
    int m_modBadgeValue;
};


class CommentCell : cocos2d::CCLayer{
private:
    cocos2d::CCSprite* getModBadgeSprite();
public:
    void loadFromComment(GJComment* comment);
    static bool hookInit();
};