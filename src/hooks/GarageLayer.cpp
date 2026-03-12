#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include "../layers/OdysseySelectLayer.hpp"
#include "../utils/IconUtils.hpp"

using namespace geode::prelude;

class $modify(GDOGarageLayer, GJGarageLayer)
{
    struct Fields
    {
        ListButtonBar *m_customButtonbar;
    };

    bool init()
    {
        if (!GJGarageLayer::init())
            return false;

        auto gm = GameManager::get();

        m_playerObject->updatePlayerFrame(IconUtils::currentVehicleID(), gm->m_playerIconType);

        auto menu = getChildByID("shards-menu");

        if (auto shards = menu->getChildByID("shards-button"))
            shards->setVisible(false);

        if (auto paint = menu->getChildByID("color-button"))
            paint->setPositionY(paint->getPositionY() + 25);

        if (auto shopButton = getChildByID("top-left-menu")->getChildByID("shop-button"))
            shopButton->setVisible(false);

#ifndef GEODE_IS_IOS

        //  Si la opcion de "Esconder gamemodes custom" esta deshabilitado, agrega los botones de los gamemodes personalizados
        if (!GameManager::sharedState()->getGameVariable("0202"))
        {
            //  Agregar los botones de gamemodes nuevos al menu de categorias
            if (auto categoryMenu = static_cast<CCMenu *>(getChildByID("category-menu")))
            {
                //  Quita temporalmente los botones de efecto y trail
                auto trailButton = categoryMenu->getChildByID("trail-button");
                auto effectButton = categoryMenu->getChildByID("death-effect-button");
                effectButton->removeFromParentAndCleanup(false);
                trailButton->removeFromParentAndCleanup(false);

                //  Agrega los botones de los gamemodes custom
                for (int ii = 0; ii < 4; ii++)
                {
                    const char *buttonName[4] = {"Boat", "Drone", "Slider", "Minecart"};
                    //  log::debug("gamemode: {}", buttonName[ii]);

                    auto sprOff = IconSelectButtonSprite::createWithSpriteFrameName(fmt::format("GDO_{}Icon_001.png"_spr, buttonName[ii]).c_str(), 1.5, IconSelectBaseColor::Unselected);
                    sprOff->setScale(.9f);

                    auto sprOn = IconSelectButtonSprite::createWithSpriteFrameName(fmt::format("GDO_{}Icon_001.png"_spr, buttonName[ii]).c_str(), 1.5, IconSelectBaseColor::Selected);
                    sprOn->setScale(.9f);

                    auto toggler = CCMenuItemToggler::create(sprOff, sprOn, this, menu_selector(GJGarageLayer::onSelectTab));
                    toggler->setID(fmt::format("{}-button"_spr, buttonName[ii]));
                    toggler->setTag(900 + ii);
                    toggler->setEnabled(true);

                    categoryMenu->addChild(toggler);
                }

                categoryMenu->addChild(trailButton);
                categoryMenu->addChild(effectButton);
                categoryMenu->updateLayout();
            }
        }

#endif

        return true;
    }

    void setupPage(int p0, IconType p1)
    {

        GJGarageLayer::setupPage(p0, p1);

        m_selectedIconType = p1;
        m_iconID = 0;

        auto size = CCDirector::get()->getWinSize();

        int vehicleID = IconUtils::iconTypeToInt(p1);
        if (vehicleID >= 900)
        {
            m_iconSelection->m_scrollLayer->m_extendedLayer->removeAllChildrenWithCleanup(true);

            auto arr = CCArray::create();

            for (int i = 0; i < 1; i++)
            {
                auto icon = GJItemIcon::createBrowserItem(IconUtils::intToUnlockType(vehicleID), i + 1);
                icon->setScale(icon->scaleForType(IconUtils::intToUnlockType(vehicleID)));

                if (!GameManager::get()->isIconUnlocked(i + 1, p1))
                    icon->changeToLockedState(1.f - icon->getScale() + 1.f);

                auto btn = CCMenuItemSpriteExtra::create(icon, this, menu_selector(GJGarageLayer::onSelect));
                btn->setTag(i + 1);

                arr->addObject(btn);
            }

            auto page = ListButtonPage::create(arr, {.5f, 0}, 12, 3, 0, 0, 30);
            page->setPosition({size.width / 2, 95});
            page->setID("icon-page"_spr);
            m_iconSelection->m_scrollLayer->m_extendedLayer->addChild(page);
            m_iconSelection->goToPage(0);

            auto menu = static_cast<CCMenu *>(page->getChildren()->objectAtIndex(0));

            auto btn = static_cast<CCNode *>(menu->getChildren()->objectAtIndex(0));

            updateCursorPos(IconUtils::currentIdForVehicle(vehicleID));

            return;
        }
    }

    void updateCursorPos(int btnTag)
    {
        if (btnTag == 0)
            btnTag = 1;
        auto page = m_iconSelection->m_scrollLayer->m_extendedLayer->getChildByID("icon-page"_spr);

        auto menu = static_cast<CCMenu *>(page->getChildren()->objectAtIndex(0));
        auto btn = static_cast<CCMenu *>(menu->getChildByTag(btnTag));
        if (!btn)
        {
            m_cursor1->setVisible(false);
            return;
        }

        m_cursor1->setVisible(true);
        m_cursor1->setPosition(menu->convertToWorldSpace(btn->getPosition()));
    }

    void onSelect(CCObject *sender)
    {
        int iconID = IconUtils::iconTypeToInt(m_selectedIconType);
        if (iconID >= 900)
        {
            bool isSelected = m_selectedIconType == m_iconType && m_iconID == sender->getTag();
            bool isUnlocked = GameManager::get()->isIconUnlocked(sender->getTag(), m_selectedIconType);
            log::info("Unlocked: {} {}", isUnlocked, iconID);
            log::info("Selected: {}", isSelected);

            if (isSelected || (!isUnlocked && !isSelected))
            {
                ItemInfoPopup::create(sender->getTag(), IconUtils::intToUnlockType(iconID))->show();
                return;
            }

            updateCursorPos(sender->getTag());
            IconUtils::setVehicleSaveId(sender->getTag(), IconUtils::iconTypeToInt(m_selectedIconType));
            m_playerObject->updatePlayerFrame(sender->getTag(), m_selectedIconType);
            m_iconID = sender->getTag();
            m_iconType = m_selectedIconType;
        }
        else
        {
            GJGarageLayer::onSelect(sender);
        }
    }

    void onSelectTab(CCObject *sender)
    {
        GJGarageLayer::onSelectTab(sender);

        auto tag = sender->getTag();

        auto arr = getChildByID("category-menu")->getChildren();

        if (arr)
        {
            for (auto child : CCArrayExt<CCMenuItemToggler *>(arr))
            {
                child->toggle(false);
                child->setEnabled(true);
                if (child->getTag() == tag)
                {
                    child->toggle(true);
                    child->setEnabled(false);
                }
            }
        }
    }

    void onCustomSelect(CCObject *sender)
    {
        auto icon = static_cast<IconType>(sender->getTag());
        auto iconUnlock = static_cast<UnlockType>(sender->getTag());

        m_playerObject->updatePlayerFrame(1, icon);

        ItemInfoPopup::create(1, iconUnlock)->show();
    }

    void onBack(CCObject *sender)
    {
        if (GameManager::sharedState()->getIntGameVariable("1001") > 0)
        {
            auto director = CCDirector::sharedDirector();
            auto winSize = director->getWinSize();

            this->retain();
            this->removeFromParentAndCleanup(false);

            auto selectLayer = OdysseySelectLayer::scene(GameManager::sharedState()->getIntGameVariable("1001") - 1);
            director->replaceScene(selectLayer);
            selectLayer->addChild(this, 1000);

            this->release();

            auto moveTo = CCMoveTo::create(0.3f, ccp(0, winSize.height));
            auto easeIn = CCEaseIn::create(moveTo, 2.0f);
            auto callFunc = CCCallFunc::create(this, callfunc_selector(GJGarageLayer::removeFromParent));

            auto ccSeq = CCSequence::create(easeIn, callFunc, 0);
            this->runAction(ccSeq);
            setKeyboardEnabled(false);
            setKeypadEnabled(false);
            return;
        }

        GJGarageLayer::onBack(sender);
    }
};