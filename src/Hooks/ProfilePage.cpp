#include "ProfilePage.hpp"
#include <matdash.hpp>
#include <matdash/minhook.hpp>
#include <Windows.h>
#include <string>
#include <spdlog/spdlog.h>

using namespace cocos2d;

cocos2d::CCSprite* ProfilePage::getModBadgeSprite(){
    CCObject* layerChild;
    CCLayer* root = reinterpret_cast<CCLayer*>(this->getChildren()->objectAtIndex(0));
    CCARRAY_FOREACH(root->getChildren(), layerChild){
        if(auto sprite = dynamic_cast<CCSprite*>(layerChild)){
            auto badgeSprite1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("modBadge_01_001.png");
            auto badgeSprite2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("modBadge_02_001.png");
            if(sprite->isFrameDisplayed(badgeSprite2) || sprite->isFrameDisplayed(badgeSprite1)) return sprite;
        }
    }
    return nullptr;
}

cocos2d::CCPoint ProfilePage::getModBadgePosition(){
    CCLabelBMFont* playerNameLabel = *reinterpret_cast<CCLabelBMFont**>(((uint32_t)this)+0x210);
    CCSize labelSize   = playerNameLabel->getScaledContentSize();
    CCPoint offset   = {(labelSize.width * -0.5f)- 16.0f, -1.0f};
    return playerNameLabel->getPosition() + offset;
}

void ProfilePage::loadPageFromUserInfo(GJUserScore* userScore){
    using namespace std::string_literals;
    using namespace cocos2d;
    matdash::orig<&ProfilePage::loadPageFromUserInfo, matdash::CallConv::Thiscall>(this, userScore);
    if(auto originalModBadge = getModBadgeSprite()) originalModBadge->removeFromParent(); //Delete the original badge    
    
    //test code
    CCLayer* root = reinterpret_cast<CCLayer*>(this->getChildren()->objectAtIndex(0));
    auto newBadge = CCSprite::createWithSpriteFrameName("modBadge_01_001.png");
    root->addChild(newBadge, 10);
    newBadge->setPosition(getModBadgePosition());
    //MessageBoxA(NULL,  ("Badge ID: "s + std::to_string(userScore->m_modBadgeValue)).c_str(), "ProfileBadge", MB_OK);
}

bool ProfilePage::hookInit(){
    std::size_t base = reinterpret_cast<std::size_t>(GetModuleHandleA(NULL));
    matdash::add_hook<&ProfilePage::loadPageFromUserInfo, matdash::CallConv::Thiscall>(base+0x210040);
    return true;
}