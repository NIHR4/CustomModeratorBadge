#include "ProfilePage.hpp"
#include <matdash.hpp>
#include <matdash/minhook.hpp>
#include <Windows.h>
#include <string>
void ProfilePage::loadPageFromUserInfo(GJUserScore* userScore){
    using namespace std::string_literals;
    //MessageBoxA(NULL,  ("Badge ID: "s + std::to_string(userScore->m_modBadgeValue)).c_str(), "ProfileBadge", MB_OK);
    matdash::orig<&ProfilePage::loadPageFromUserInfo, matdash::CallConv::Thiscall>(this, userScore);
}

bool ProfilePage::hookInit(){
    std::size_t base = reinterpret_cast<std::size_t>(GetModuleHandleA(NULL));
    matdash::add_hook<&ProfilePage::loadPageFromUserInfo, matdash::CallConv::Thiscall>(base+0x210040);
    return true;
}