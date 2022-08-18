#pragma once
#include <string>

#ifdef ProfileBadges_EXPORTS
#define PROFILEBADGES_API __declspec(dllexport)
#else
#define PROFILEBADGES_API __declspec(dllimport)
#endif

enum class PBCode{
    OK,
    HOOK_ERROR,
    TEXTURES_ERROR    
};

PROFILEBADGES_API void add_custom_badge(int internalID, const std::string& spriteName);
PROFILEBADGES_API void remove_custom_badge(int internalID);
PROFILEBADGES_API PBCode activate_custom_badges();
PROFILEBADGES_API PBCode deactivate_custom_badges();

