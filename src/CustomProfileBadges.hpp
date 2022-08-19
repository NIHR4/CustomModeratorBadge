#pragma once
#include <string>

#ifdef ProfileBadges_EXPORTS
#define PROFILEBADGES_API __declspec(dllexport)
#else
#define PROFILEBADGES_API __declspec(dllimport)
#endif


#include <string>
#include <unordered_map>

class PROFILEBADGES_API CustomBadgeManager{
private:
    std::unordered_map<int, std::string> _idToSpriteDict;
    CustomBadgeManager()=default;    
public:
    
    CustomBadgeManager(const CustomBadgeManager&)=delete;
    CustomBadgeManager(const CustomBadgeManager&&)=delete;
    
    bool mapBadgeIdToSprite(int badgeId, const std::string& spriteName);
    bool removeSpriteMapping(int badgeId);
    void removeAllSpriteMappings();
    std::string convertIdToSpriteName(int badgeId);
    
    void setDebugMode(bool debugEnabled);

    static CustomBadgeManager& get();
    
};


