#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(GDOProfilePage, ProfilePage)
{
    void loadPageFromUserInfo(GJUserScore *p0)
    {
        ProfilePage::loadPageFromUserInfo(p0);

        //  Esconde los hints dado a que no se pueden acceder estos lugares
        if (auto myLevelsHint = m_mainLayer->getChildByID("my-levels-hint"))
            myLevelsHint->setVisible(false);

        if (auto myListsHint = m_mainLayer->getChildByID("my-lists-hint"))
            myListsHint->setVisible(false);

        if (auto commentHistoryBtn = m_mainLayer->getChildByIDRecursive("comment-history-button"))
            commentHistoryBtn->setVisible(false);

        //  Esconde los botones que permita el Jugador acceder al resto del juego
        if (auto menu = m_mainLayer->getChildByID("main-menu"))
        {
            if (auto levelsButton = menu->getChildByID("my-levels-button"))
                levelsButton->setVisible(false);
            if (auto listsButton = menu->getChildByID("my-lists-button"))
                listsButton->setVisible(false);
        }

        auto AM = AchievementManager::sharedState();
        auto GM = GameManager::sharedState();

        //  Para el award secreto de "Programmer"
        if (p0->m_accountID == 25521533 && GM->getUGV("209") && !AM->isAchievementEarned("geometry.ach.odyssey.secret20"))
        {
            auto menu = CCMenu::create();
            menu->setZOrder(10);

            auto sprite = CCSprite::createWithSpriteFrameName("chest_02_02_001.png");
            sprite->setScale(0.5);

            auto button = CCMenuItemSpriteExtra::create(
                sprite,
                this,
                menu_selector(GDOProfilePage::onSecret));

            button->m_selectSound = "chestClick.ogg";
            button->m_scaleMultiplier = 1;
            button->m_colorEnabled = true;
            button->m_colorDip = 100.f;
            button->setPositionY(-55);

            menu->addChild(button);
            m_mainLayer->addChild(menu);
        };
    }

    //  Al encontrar el secreto, se le asigna al usuario orbes gratis
    void onSecret(CCObject *sender)
    {
        auto GM = GameManager::sharedState();
        auto GSM = GameStatsManager::sharedState();

        //  Da el achievement y incrementa la cantidad de orbes para el Jugador
        GM->reportAchievementWithID("geometry.ach.odyssey.secret20", 100, false);
        GSM->incrementStat("14", 500);

        //  Crea el cofre que da los stats
        GJRewardObject *orbs = GJRewardObject::create(SpecialRewardItem::Orbs, 500, 0);
        CCArray *rewards = CCArray::create();
        rewards->addObject(orbs);

        //  Crea el layer que da el award
        GJRewardItem *item = GJRewardItem::createWithObjects(GJRewardType::Large, rewards);
        RewardUnlockLayer *layer = RewardUnlockLayer::create(2, nullptr);
        layer->m_chestType = 2;
        layer->setZOrder(200);

        //  Pone la escena
        cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer);
        layer->showCollectReward(item);

        //  Al abrirse el cofre, se reemplaza su textura y se deshabilita el boton
        auto chestTop = CCSprite::createWithSpriteFrameName("chest_02_04_001.png");
        auto chestBottom = CCSprite::createWithSpriteFrameName("chest_02_04_back_001.png");
        chestTop->setOpacity(100);
        chestBottom->setOpacity(100);

        auto sprite = CCSprite::create();
        sprite->addChild(chestTop);
        sprite->addChild(chestBottom, -1);
        sprite->setScale(0.5);

        auto btn = static_cast<CCMenuItemSpriteExtra *>(sender);
        btn->setEnabled(false);
        btn->setSprite(sprite);
    };
};