# Custom Moderator Badge


## What is this?

This is a library that allows you to modify Geometry Dash to display custom moderator badges in user profiles and comments. Normally the game can only process two hardcoded moderator levels(which are sent back from the game's servers), however, this library provides you with the necessary tools to display different badges for as many moderator levels you desire.


## Quickstart

All of the functionality of this library is provided through the `CustomBadgeManager` class. This class is a [singleton](https://en.wikipedia.org/wiki/Singleton_pattern) and as such can only be accessed throught the method `CustomBadgeManager::get`.

### To add a new moderator badge:
Call the method `mapBadgeIdToSprite`. The first parameter is the "moderator level" you want the custom badge sprite to be associated with. The second parameter is the name of the sprite you want to display to the user. **NOTE: The sprite must already be loaded into the game's texture cache before calling this method**.
```cpp
CustomBadgeManager::get().mapBadgeIdToSprite(modLevel, "customSpriteName");
```

## Documentation

You can find documentation for all the methods of this library inside the "CustomProfileBadges.hpp" header file.
