#include <Geode/Geode.hpp>
#include <Geode/modify/CCSpriteFrameCache.hpp>
#include <Geode/modify/CCSpriteBatchNode.hpp>

using namespace geode::prelude;

class $modify(MyCCSpriteFrameCache, CCSpriteFrameCache)
{
    cocos2d::CCSpriteFrame *spriteFrameByName(const char *pszName)
    {
        //  I HATE BATCH NODES
        // if (std::string_view(pszName) == std::string_view("currencyOrbIcon_001.png"))
        //    return CCSpriteFrameCache::spriteFrameByName("GDO_CoinIcon.png"_spr);

        // if (std::string_view(pszName) == std::string_view("currencyOrb_001.png"))
        //     return CCSpriteFrameCache::spriteFrameByName("GDO_Coin.png"_spr);

        if (std::string_view(pszName) == std::string_view("gjItem_01_001.png"))
            return CCSpriteFrameCache::spriteFrameByName("GDO_Key01_001.png"_spr);

        if (std::string_view(pszName) == std::string_view("gjItem_02_001.png"))
            return CCSpriteFrameCache::spriteFrameByName("GDO_Key02_001.png"_spr);

        if (std::string_view(pszName) == std::string_view("gjItem_04_001.png"))
            return CCSpriteFrameCache::spriteFrameByName("Betsy_001.png"_spr);

        return CCSpriteFrameCache::spriteFrameByName(pszName);
    }
};