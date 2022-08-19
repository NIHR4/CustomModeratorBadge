#include "CommentCell.hpp"
#include <matdash.hpp>
#include <matdash/minhook.hpp>
#include <spdlog/spdlog.h>
#include "../CustomProfileBadges.hpp"
using namespace cocos2d;

CCSprite* CommentCell::getModBadgeSprite(){
    CCObject* layerChild;
    CCLayer* root = reinterpret_cast<CCLayer*>(this->getChildren()->objectAtIndex(1));
    CCARRAY_FOREACH(root->getChildren(), layerChild){
        if(auto sprite = dynamic_cast<CCSprite*>(layerChild)){
            auto badgeSprite1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("modBadge_01_001.png");
            auto badgeSprite2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("modBadge_02_001.png");
            if(sprite->isFrameDisplayed(badgeSprite2) || sprite->isFrameDisplayed(badgeSprite1)) return sprite;
        }
    }
    return nullptr;
}


void CommentCell::loadFromComment(GJComment* comment){
    
    if(comment->m_modBadgeValue == 0){
        matdash::orig<&CommentCell::loadFromComment, matdash::CallConv::Thiscall>(this, comment);
        spdlog::trace("User does not have a mod badge");
        return;
    }
    
    int realBadgeValue = comment->m_modBadgeValue;
    comment->m_modBadgeValue = 1;
    matdash::orig<&CommentCell::loadFromComment, matdash::CallConv::Thiscall>(this, comment); //force the badge to spawn
    
    CCSprite* originalBadge = getModBadgeSprite();
    if(originalBadge == nullptr){
        spdlog::warn("With a badgeID of value {} a custom badge should have been generated but the program was unable to replace the existing badge", realBadgeValue);
        return;
    }

    try{
        CCLayer* root = reinterpret_cast<CCLayer*>(this->getChildren()->objectAtIndex(1));
        spdlog::trace("User has a modBadge={}", realBadgeValue);
        CCSprite* newBadge = CCSprite::createWithSpriteFrameName(CustomBadgeManager::get().convertIdToSpriteName(realBadgeValue).c_str());
        CCPoint originalPosition = originalBadge->getPosition();
        originalBadge->removeFromParent();
        newBadge->setPosition(originalPosition);
        root->addChild(newBadge,10);
    }catch(const std::out_of_range& ex){
        //Handle the exception and do nothing
    }
        
}

bool CommentCell::hookInit(){
    std::size_t base = reinterpret_cast<std::size_t>(GetModuleHandleA(NULL));
    matdash::add_hook<&CommentCell::loadFromComment, matdash::CallConv::Thiscall>(base + 0x5F3D0);
    return true;
}