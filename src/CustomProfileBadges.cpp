#include <iostream>
#include "Hooks/ProfilePage.hpp"
#include "Hooks/CommentCell.hpp"
#include "CustomProfileBadges.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>


#include <cocos2d.h>
#include <mutex>

std::mutex gMutex;

bool CustomBadgeManager::mapBadgeIdToSprite(int badgeId, const std::string& spriteName){
    
    if(!badgeId) {
        spdlog::warn("Failed to map badgeID={}. Mapping badge value '0' is disallowed");
        return false; //Forbid mapping ID zero
    }
    
    if(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteName.c_str()) == nullptr){
        spdlog::warn("Failed to map badgeID={}. '{}' has not been loaded into the game's sprite cache", badgeId, spriteName);
        return false;
    }
    spdlog::debug("Mapped badgeID={} to sprite '{}'", badgeId, spriteName);
    std::lock_guard<std::mutex> guard(gMutex);
    _idToSpriteDict[badgeId] = spriteName;
    return true;
}

bool CustomBadgeManager::removeSpriteMapping(int badgeId){
    std::lock_guard<std::mutex> guard(gMutex);
    for(auto it=_idToSpriteDict.begin(); it != _idToSpriteDict.end(); it++){
        if(it->first == badgeId) {
            it= _idToSpriteDict.erase(it);
            spdlog::debug("Removed mapping for badgeID={}", badgeId);
            return true;
        }
    }
    spdlog::warn("Could not remove sprite mapping. badgeID={} is not mapped to any sprites", badgeId);
    return false;
}

void CustomBadgeManager::removeAllSpriteMappings(){
    std::lock_guard<std::mutex> guard(gMutex);
    _idToSpriteDict.clear();
    spdlog::debug("Removed all of the custom id to badge sprite mappings");
}


std::string CustomBadgeManager::convertIdToSpriteName(int badgeId){
    try{
        std::lock_guard<std::mutex> guard(gMutex);
        return _idToSpriteDict.at(badgeId);
    }catch(const std::out_of_range& ex){
        spdlog::error("Out of bounds exception. badgeID={} hasn't been mapped to any sprites. Exception details: {}", badgeId, ex.what());
        throw ex;
    }
}

CustomBadgeManager& CustomBadgeManager::get(){
    static CustomBadgeManager instance;
    return instance;
}


void CustomBadgeManager::setDebugMode(bool debugEnabled){
    spdlog::set_level(debugEnabled ? spdlog::level::debug : spdlog::level::info);
}



//CTOR Code: Setup logger and hooks
CustomBadgeManager::CustomBadgeManager(){
    std::vector<spdlog::sink_ptr> sinks;
    const uint32_t megabyte = 1048576;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("Logs/CustomBadges", 1048576*5, 3));
    auto logger = std::make_shared<spdlog::logger>("CustomBadges", sinks.begin(), sinks.end());
    spdlog::set_default_logger(logger);

    ProfilePage::hookInit();
    CommentCell::hookInit();
}




//Boilerplate code
/*DWORD WINAPI modThread(void* hModule){
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
    spdlog::set_level(spdlog::level::trace);
    ProfilePage::hookInit();
    CommentCell::hookInit();
    return 0;
}*/


BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        //CreateThread(0, 0, modThread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}