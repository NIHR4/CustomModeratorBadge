#include "ReplacementLogic.hpp"
#include "../CustomProfileBadges.hpp"

bool shouldRenderBadgeNormally(int badgeId){
    if(badgeId == 0) return true;
    if(badgeId == 1 || badgeId == 2) return !CustomBadgeManager::get().idIsMappedToSprite(badgeId);
    return false;
}