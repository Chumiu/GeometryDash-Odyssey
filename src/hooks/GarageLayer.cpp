#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include "../utils/Utils.hpp"

class $modify(GDOGarageLayer, GJGarageLayer)
{
    bool init()
    {
        if (!GJGarageLayer::init())
            return false;

        auto gm = GameManager::get();

        log::info("{}\n", m_iconID);

        m_playerObject->updatePlayerFrame(Odyssey::currentVehicleID(), gm->m_playerIconType);

        auto menu = getChildByID("shards-menu");

        if (auto shards = menu->getChildByID("shards-button"))
            shards->setVisible(false);

        if (auto paint = menu->getChildByID("color-button"))
            paint->setPositionY(paint->getPositionY() + 25);

        if (auto shopButton = getChildByID("top-left-menu")->getChildByID("shop-button"))
            shopButton->setVisible(false);

        if (auto categoryMenu = static_cast<CCMenu *>(getChildByID("category-menu")))
        {
            auto arr = categoryMenu->getChildren();
            for (int i = 0; i < 4; i++)
            {
                const char* buttonName = "boat";

                switch (i)
                {
                case 1:
                    buttonName = "drone";
                    break;
                case 2:
                    buttonName = "slider";
                    break;
                case 3:
                    buttonName = "minecart";
                    break;
                }

                auto sprOff = CCSprite::createWithSpriteFrameName(fmt::format("gdo_{}Btn_off_001.png"_spr, buttonName).c_str());
                sprOff->setScale(.9f);
                
                auto sprOn = CCSprite::createWithSpriteFrameName(fmt::format("gdo_{}Btn_on_001.png"_spr, buttonName).c_str());
                sprOn->setScale(.9f);

                auto toggler = CCMenuItemToggler::create(sprOff, sprOn, this, menu_selector(GJGarageLayer::onSelectTab));

                toggler->setTag(900 + i);
                toggler->setEnabled(true);

                arr->insertObject(toggler, 9 + i);
            }
            categoryMenu->updateLayout();
        }
        return true;
    }

    void onSelectTab(CCObject *sender)
    {
        GJGarageLayer::onSelectTab(sender);
        auto tag = sender->getTag();

        auto arr = getChildByID("category-menu")->getChildren();

        if (arr)
        {
            for (auto child : CCArrayExt<CCMenuItemToggler*>(arr))
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

        auto size = CCDirector::sharedDirector()->getWinSize();

        if (sender->getTag() >= 900)
        {
            auto itemArray = CCArray::create();

            auto square = CCSprite::createWithSpriteFrameName("playerSquare_001.png");

            square->setOpacity(0);

            auto vehicleID = static_cast<IconType>(tag);

            auto itemIcon = SimplePlayer::create(0);
            itemIcon->updatePlayerFrame(1, vehicleID);

            itemIcon->setColor(GameManager::sharedState()->colorForIdx(17));
            itemIcon->setPosition(square->getContentSize() / 2);

            if (tag == 900) itemIcon->setScale(.7f);

            square->addChild(itemIcon);

            auto selectIcon = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
            selectIcon->setPosition(square->getContentSize() / 2);

            square->addChild(selectIcon);

            square->setScale(.8f);

            

            auto button = CCMenuItemSpriteExtra::create(square, this, menu_selector(GDOGarageLayer::onCustomSelect));
            button->setTag(tag);

            itemArray->addObject(button);

            auto buttonBar = m_iconSelection;
            
            auto extendedLayer = buttonBar->m_scrollLayer->m_extendedLayer;
            extendedLayer->removeAllChildrenWithCleanup(true);

            auto menu = CCMenu::create();
            menu->setPosition({size.width / 2 - 160, size.height / 2 - 40 });

            menu->addChild(button);

            extendedLayer->addChild(menu);
        }


    }

    void onCustomSelect(CCObject* sender)
    {
        auto icon = static_cast<IconType>(sender->getTag());
        auto iconUnlock = static_cast<UnlockType>(sender->getTag());

        m_playerObject->updatePlayerFrame(1, icon);

        ItemInfoPopup::create(1, iconUnlock)->show();
    }
};