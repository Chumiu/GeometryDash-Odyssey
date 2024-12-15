#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include "../layers/OdysseySelectLayer.hpp"
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
        return true;
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

            if (tag == 900)
                itemIcon->setScale(.7f);

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
            menu->setPosition({size.width / 2 - 160, size.height / 2 - 40});

            menu->addChild(button);

            extendedLayer->addChild(menu);
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