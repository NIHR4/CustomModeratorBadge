#pragma once
#include <string>

#ifdef ProfileBadges_EXPORTS
#define PROFILEBADGES_API __declspec(dllexport)
#else
#define PROFILEBADGES_API __declspec(dllimport)
#endif


#include <string>
#include <unordered_map>

class CustomBadgeManager{
private:
    std::unordered_map<int, std::string> _idToSpriteDict;
    CustomBadgeManager();    
public:
    
    PROFILEBADGES_API CustomBadgeManager(const CustomBadgeManager&)=delete;
    PROFILEBADGES_API CustomBadgeManager(const CustomBadgeManager&&)=delete;
    
    /*
    Singleton getter method
    */
    PROFILEBADGES_API static CustomBadgeManager& get();
    
    
    
    /*
    Indicates the game what sprite to use when encountering custom modBadgeLevel levels
    Parameters:
    [in, badgeId]: This parameter corresponds to the modBadgeLevel you want to your custom sprite to show up for

    [in, spriteName]: This parameters indicates the sprite that will be rendered in the place of a mod badge when a user's modBadgeLevel is equal
    to the one specified in the badgeId parameter

    Returns:
    TRUE in case the badgeId was mapped to a custom sprite.
    FALSE if the badgeId was not mapped to a custom sprite because the sprite wasn't loaded into the game's memory
    or because the badgeId is equal to a reserved value, such is the case of the value '0'
    */ 
    PROFILEBADGES_API bool mapBadgeIdToSprite(int badgeId, const std::string& spriteName);
    
    
    /*
    Removes a custom mod badge from the game.
    Parameters:
    [in badgeId]: This parameter indicates the modBadgeLevel that you want a custom sprite to no longer show up for.
    //Return:
    TRUE in case the badge ID was unmapped from the custom sprite.
    FALSE if the badge ID was not mapped to any sprites in the first place
    */
    PROFILEBADGES_API bool removeSpriteMapping(int badgeId);
    
    
    /*
    Allows you to check whether a badge ID has been mapped to a custom sprite
    Parameters:
    [in, badgeId]: the badge ID you want to check
    //Return:
    TRUE if the badge ID has a custom sprite assigned to it
    FALSE if the badge ID does not has a custom sprite assigned to it
    */
    PROFILEBADGES_API bool idIsMappedToSprite(int badgeId);


    /*
    Removes ALL custom mod badges from the game.
    */
    PROFILEBADGES_API void removeAllSpriteMappings();
    
    
    /*
    Returns the sprite name of the sprite that will be displayed when encountering a custom badge ID
    Parameters:
    [in badgeId]: This parameter allows you to specify the sprite name you want to fetch
    Returns:
    Returns a string which contains the name of the sprite that will be displayed when Geomtry Dash encounters users 
    with a modBadgeLevel equal to that of the badgeId parameter
    */
    PROFILEBADGES_API std::string convertIdToSpriteName(int badgeId);
    
    
    /*
    Logs additional information that is useful to debug the application.
    //Paramters:
    [in, debugEnabled]: Setting this to TRUE will enable extra logging, while setting it to FALSE will disable this extra logging
    */
    PROFILEBADGES_API void setDebugMode(bool debugEnabled);

    
};


