#include "OdysseySelectLayer.hpp"
#include "OdysseyLevelPopup.hpp"
#include "OdysseyComicLayer.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

bool OdysseySelectLayer::init(int page)
{
    if (!CCLayer::init())
        return false;

    m_currentPage = page;
    GameManager::sharedState()->setIntGameVariable("1001", page + 1);
    m_winSize = CCDirector::sharedDirector()->getWinSize();

    //  Game Manager
    auto GSM = GameStatsManager::sharedState();

    // canción
    std::string song = fmt::format("IslandLoop{:02}.mp3"_spr, page + 1);

    // fondo
    int bgID = 1;
    ccColor3B bgColor = {26, 12, 43};

    // islas
    const char *islandTexture = "odyssey_island01.png"_spr;
    CCPoint islandPosition = {m_winSize.width / 2, m_winSize.height / 2 - 20};
    ccColor3B islandColor = {255, 255, 255};
    float islandScale = 1.8f;
    int islandOpacity = 255;
    ccColor4B gradientColorTop = { 0, 0, 0, 0};
    ccColor4B gradientColorBottom = { 0, 0, 0, 0};

    switch (page)
    {
    case 0:
        bgID = 52;
        bgColor = {32, 39, 46};
        m_levelAmount = 4;
        break;

    case 1:
        bgID = 32;
        bgColor = {31, 0, 63};
        islandTexture = "odyssey_island02.png"_spr;
        islandScale = .7f;
        m_levelAmount = 5;
        gradientColorBottom = {142, 0, 11, 75};
        break;

    case 2:
        bgID = 15;
        bgColor = {53, 7, 0};
        islandTexture = "island_extra_01.png"_spr;
        islandPosition = CCPoint{m_winSize.width / 2 - 100, islandPosition.y};
        islandScale = .5f;
        break;

    default:
        islandColor = {0, 0, 0};
        break;
    }

    FMODAudioEngine::sharedEngine()->playMusic(song, true, .25f, 0);

    m_background = CCSprite::create(GameManager::sharedState()->getBGTexture(bgID));
    m_background->setColor(bgColor);
    m_background->setAnchorPoint({0, 0});
    m_background->setPositionY(-100);
    m_background->setScale(m_winSize.width / m_background->getContentWidth());

    addChild(m_background, -2);

    auto gradient = CCLayerGradient::create(gradientColorTop, gradientColorBottom);
    gradient->setBlendFunc({GL_ADD, GL_ADD});
    addChild(gradient, -1);

    auto backMenu = CCMenu::create();
    backMenu->setPosition(24, m_winSize.height - 24);

    auto backSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    auto backButton = CCMenuItemSpriteExtra::create(backSpr, this, menu_selector(OdysseySelectLayer::onBack));

    backMenu->addChild(backButton);

    addChild(backMenu);

    m_islandNode = CCNode::create();

    if (page == 2)
    {
        auto extra01_unlocked = GSM->isItemUnlocked(UnlockType::GJItem, 1);
        auto extra02_unlocked = GSM->isItemUnlocked(UnlockType::GJItem, 2);

        auto menu = CCMenu::create();
        menu->setPosition({0, 0});

        auto firstSprite = CCSprite::createWithSpriteFrameName(islandTexture);
        firstSprite->setScale(islandScale);

        auto firstIsland = CCMenuItemSpriteExtra::create(
            firstSprite,
            this,
            menu_selector(OdysseySelectLayer::onExtraLevel));

        firstIsland->setColor(islandColor);
        firstIsland->setPosition(islandPosition);
        firstIsland->setTag(501);

        auto secondSprite = CCSprite::createWithSpriteFrameName("island_extra_02.png"_spr);
        secondSprite->setScale(islandScale);

        auto secondIsland = CCMenuItemSpriteExtra::create(
            secondSprite,
            this,
            menu_selector(OdysseySelectLayer::onExtraLevel));

        secondIsland->setPosition({m_winSize.width / 2 + 100, m_winSize.height / 2});
        secondIsland->setTag(502);

        if (!extra01_unlocked)
        {
            auto lock = CCSprite::createWithSpriteFrameName("GJLargeLock_001.png");
            firstSprite->setColor({25, 25, 25});
            firstIsland->addChild(lock, 10);

            lock->setPosition(firstIsland->getContentSize() / 2);
        }

        if (!extra02_unlocked)
        {
            auto lock = CCSprite::createWithSpriteFrameName("GJLargeLock_001.png");
            secondSprite->setColor({25, 25, 25});
            secondIsland->addChild(lock, 10);

            lock->setPosition(secondIsland->getContentSize() / 2);
        }

        menu->addChild(firstIsland);
        menu->addChild(secondIsland);

        m_islandNode->addChild(menu);
    }

    auto island = CCSprite::createWithSpriteFrameName(islandTexture);
    island->setOpacity(islandOpacity);
    island->setScale(islandScale);
    island->setColor(islandColor);

    island->setAnchorPoint({.5f, .5f});
    island->setPosition(islandPosition);

    if (page == 2)
        island->setVisible(false);

    m_islandNode->addChild(island);
    addChild(m_islandNode);

    //  Agrega los botones de niveles
    addLevelButtons();

    //  Agrega los puntos del camino de la isla
    addIslandDots();

    //  Animacion de flotando para la Isla
    auto moveUp = CCEaseInOut::create(CCMoveTo::create(2.0f, {0, 5}), 1.8f);
    auto moveDown = CCEaseInOut::create(CCMoveTo::create(2.0f, {0, 0}), 1.8f);
    m_islandNode->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(moveUp, moveDown)));

    //  Titulo de la Isla
    auto islandTitle = CCSprite::createWithSpriteFrameName(fmt::format("island_title{:02}.png"_spr, page + 1).c_str());
    islandTitle->setScale(.75f);
    islandTitle->setPosition({m_winSize.width / 2, m_winSize.height - 30});
    addChild(islandTitle);

    auto switchMenu = CCMenu::create();

    if (page > 0)
    {
        auto navSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
        navSprite->setFlipX(true);

        auto leftButton = CCMenuItemSpriteExtra::create(navSprite, this, menu_selector(OdysseySelectLayer::onBackPage));
        leftButton->setPositionX(-m_winSize.width / 2 + 45);
        switchMenu->addChild(leftButton);
    }

    if (page < m_pageAmount - 1)
    {
        auto navSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");

        auto rightButton = CCMenuItemSpriteExtra::create(navSprite, this, menu_selector(OdysseySelectLayer::onNextPage));
        rightButton->setPositionX(m_winSize.width / 2 - 45);
        switchMenu->addChild(rightButton);
    }

    addChild(switchMenu);

    auto ropeMenu = CCMenu::create();
    ropeMenu->setPosition(m_winSize / 2);

    auto ropeSprite = CCSprite::createWithSpriteFrameName("garageRope_001.png");
    ropeSprite->setScale(.7f);

    auto ropeBtn = CCMenuItemSpriteExtra::create(ropeSprite, this, menu_selector(OdysseySelectLayer::onRope));
    ropeBtn->m_animationType = MenuAnimationType::Move;

    ropeBtn->m_startPosition = ropeSprite->getPosition();
    ropeBtn->m_offset = CCPoint(0, -10);

    ropeBtn->setPosition({ m_winSize.width / 2 - 65, m_winSize.height / 2 - 15 });

    ropeMenu->addChild(ropeBtn);

    auto infoSprite = CCSpriteGrayscale::createWithSpriteFrameName("GJ_infoIcon_001.png");
    //infoSprite->setScale(.5f);

    auto infoButton = CCMenuItemSpriteExtra::create(infoSprite, this, menu_selector(OdysseySelectLayer::onSongs));

    infoButton->setPosition({ m_winSize.width / 2 - 25, m_winSize.height / 2 - 20 });

    ropeMenu->addChild(infoButton);
    
    addChild(ropeMenu);

    auto m_cornerBL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    m_cornerBL->setPosition({-1, -1});
    m_cornerBL->setAnchorPoint({0, 0});
    m_cornerBL->setID("corner-bl"_spr);
    addChild(m_cornerBL, 2);

    auto m_cornerBR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    m_cornerBR->setPosition({m_winSize.width + 1, -1});
    m_cornerBR->setAnchorPoint({1, 0});
    m_cornerBR->setFlipX(true);
    m_cornerBR->setID("corner-br"_spr);
    addChild(m_cornerBR, 2);

    //  Se reemplazara esto con el Game Manager, pero lo tengo para Desarrollo
    if (!GameManager::sharedState()->getUGV("203"))
    {
        this->runAction(CCSequence::create(
            CCDelayTime::create(0.5f),
            CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::getWizardDialog01)),
            0));
    };

    animateLevelCompletation();
    

    setKeyboardEnabled(true);
    setKeypadEnabled(true);
    return true;
};

void OdysseySelectLayer::getWizardDialog01()
{
    auto dialog = Odyssey::createDialog("meetingWizard");
    GameManager::sharedState()->setUGV("203", true);
    this->addChild(dialog, 3);
};

void OdysseySelectLayer::keyBackClicked()
{
    GameManager::sharedState()->setIntGameVariable("1001", 0);
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, MenuLayer::scene(false)));
    GameManager::sharedState()->fadeInMenuMusic();
};

void OdysseySelectLayer::onBack(CCObject *)
{
    keyBackClicked();
};

std::vector<CCPoint> OdysseySelectLayer::getPositionForButtons()
{
    std::vector<CCPoint> arr;

    switch (m_currentPage)
    {
    case 0:
        return {
            {-70, 60},
            {130, 70},
            {40, 10},
            {-80, -55}};

    case 1:
        return {
            {-170, 35},
            {-57, 27},
            {30, 63},
            {141, -14},
            {149, 86}};
    }

    return arr;
}

std::vector<CCPoint> OdysseySelectLayer::getPositionForDots()
{
    std::vector<CCPoint> arr;

    switch (m_currentPage)
    {
    case 0:
        return {
            {-47, 55},
            {-32, 57},
            {-17, 55},
            {-4, 59},
            {9, 58},
            {22, 64},
            {38, 63},
            {50, 66},
            {67, 64},
            {81, 67},
            {96, 66},
            {111, 69}, 
            //camino 2
            {146, 58},
            {149, 50},
            {159, 43},
            {167, 35},
            {163, 22},
            {168, 12},
            {163, 2},
            {152, -4},
            {139, -2},
            {126, -7},
            {112, -3},
            {102, -10},
            {89, -14},
            {79, -21},
            {68, -22},
            {55, -24},
            {47, -16},
            {47, -8},
            //camino 3
            {27, -6},
            {17, -15},
            {4, -14},
            {-7, -25},
            {-22, -25},
            {-30, -37},
            {-47, -38},
            {-53, -52}
            };
    }
    return arr;

}

//  Agrega los botones de niveles
void OdysseySelectLayer::addLevelButtons()
{
    m_levelMenu = CCMenu::create();
    m_levelMenu->setPosition(m_winSize / 2);
    auto offSet = (m_currentPage * 4);

    //  Agrega los niveles con un ciclo
    if (m_levelAmount > 0)
    {
        for (int ii = 0; ii < m_levelAmount; ii++)
        {
            auto levelSprite = CCSprite::createWithSpriteFrameName("worldLevelBtn_locked_001.png"_spr);
            auto levelButton = CCMenuItemSpriteExtra::create(levelSprite, this, menu_selector(OdysseySelectLayer::onLevel));

            levelButton->setID(fmt::format("Level {}"_spr, offSet + ii + 1));
            levelButton->setTag(offSet + ii + 1);

            levelButton->setPosition(getPositionForButtons()[ii]);
            m_levelMenu->addChild(levelButton);
        }
    }

    if (m_currentPage == 0)
    {
        auto shopSprite = CCSprite::createWithSpriteFrameName("GDO_shopButton.png"_spr);
        shopSprite->setScale(.3f);

        auto shopSpriteSel = CCSprite::createWithSpriteFrameName("GDO_shopButton.png"_spr);
        shopSpriteSel->setScale(.3f);
        shopSpriteSel->setColor({ 100, 100, 100 });
        
        m_shopButton = CCMenuItemSpriteExtra::create(shopSprite, this, menu_selector(OdysseySelectLayer::onShop));
        m_shopButton->setSelectedImage(shopSpriteSel);
        m_shopButton->m_animationType = MenuAnimationType::Move;
        m_shopButton->m_startPosition = shopSprite->getPosition();
        m_shopButton->setPosition({25, 85});

        m_levelMenu->addChild(m_shopButton);

        m_shopButton->setVisible(isLevelComplete(1));
    }



    m_islandNode->addChild(m_levelMenu);
};

void OdysseySelectLayer::addIslandDots()
{
    m_dotNode = CCNode::create();
    m_dotNode->setPosition(m_winSize / 2);

    //agrega los puntos de camino entre niveles

    for (int ii = 0; ii < getPositionForDots().size(); ii++)
    {
        auto dot = CCSprite::createWithSpriteFrameName("worldDot_001.png"_spr);
        dot->setPosition(getPositionForDots()[ii]);
        m_dotNode->addChild(dot);
    }

    m_islandNode->addChild(m_dotNode);
    
}

bool OdysseySelectLayer::isLevelComplete(int level)
{
    if (level < 1) return true;
    return GameManager::sharedState()->getUGV(fmt::format("{}", level + 240).c_str());
}

void OdysseySelectLayer::setLevelComplete(int level)
{
    GameManager::sharedState()->setUGV(fmt::format("{}", level + 240).c_str(), true);
}

void OdysseySelectLayer::enableLevelAnimation(CCObject* p0)
{
    auto btn = static_cast<CCMenuItemSpriteExtra*>(p0);

    btn->setNormalImage(CCSprite::createWithSpriteFrameName("worldLevelBtn_001.png"_spr));
    btn->setScale(1.2f);
    btn->runAction(CCSequence::createWithTwoActions(
        CCFadeIn::create(.1f),
        CCEaseBounceOut::create(CCEaseBounceOut::create(CCScaleTo::create(0.5, 1)))
    ));

    auto particle = CCParticleSystemQuad::create("coinPickupEffect.plist", true);
    particle->setAnchorPoint({ 0.5f, 0.5f });
    particle->setScale(0.5f);
    particle->setZOrder(3);

    auto circlewave = CCCircleWave::create(16.0, 30, 0.3, 0,1);
    circlewave->setAnchorPoint({ 0.5f, 0.5f });
    circlewave->setScale(0.5f);
    circlewave->setZOrder(3);

    auto circlewave2 = CCCircleWave::create(16, 80, 0.3, 1, 1);
    circlewave2->setAnchorPoint({ 0.5f, 0.5f });
    circlewave2->setScale(0.5f);
    circlewave->setZOrder(3);

    particle->init();

    particle->addChild(circlewave, 2);
    particle->addChild(circlewave2, 2);

    particle->setPosition(btn->getPosition());
    btn->getParent()->addChild(particle);
    
}

void OdysseySelectLayer::animateShopUnlock()
{
    m_shopButton->setScale(1.2f);
    m_shopButton->runAction(CCSequence::createWithTwoActions(
        CCFadeIn::create(.1f),
        CCEaseBounceOut::create(CCEaseBounceOut::create(CCScaleTo::create(0.5, 1)))
    ));

    m_shopButton->setVisible(isLevelComplete(1));
}

void OdysseySelectLayer::animateLevelCompletation()
{
    //esto se quitará luego
    if (m_currentPage != 0) return;

    auto GLM = GameLevelManager::sharedState();
    auto level1 = GLM->getMainLevel(1, false);
    auto level2 = GLM->getMainLevel(2, false);
    auto level3 = GLM->getMainLevel(3, false);
    auto level4 = GLM->getMainLevel(4, false);

    auto buttonSprite = CCSprite::createWithSpriteFrameName("worldLevelBtn_001.png"_spr);
    for (int i = 0; i < m_levelMenu->getChildrenCount(); i++)
    {
        auto levelButton = static_cast<CCMenuItemSpriteExtra*>(m_levelMenu->getChildByTag(i + 1));
        
        if (levelButton)
        {
            if (GameManager::sharedState()->getUGV(fmt::format("{}", i + 240).c_str()) || i == 0)
            {
                levelButton->setNormalImage(buttonSprite);
            } 
        }

    }
    

    int firstDot = 0;
    int lastDot = 0;
    int nextLevel = 1;

    bool shouldAnimate = false;

    auto scaleAction = CCScaleTo::create(0.5,1, 0.5); // Escala al 60% durante 0.5 segundos
    auto scaleWithBounce = CCEaseBounceOut::create(scaleAction);

    if (m_currentPage == 0)
    {        
        if (level1->m_normalPercent == 100 && level2->m_normalPercent == 0)
        {
            firstDot = 0;
            lastDot = 11;
            nextLevel = 2;
        }

        if (level2->m_normalPercent == 100 && level3->m_normalPercent == 0)
        {
            firstDot = 12;
            lastDot = 29;
            nextLevel = 3;
        }

        if (level3->m_normalPercent == 100 && level4->m_normalPercent == 0)
        {
            firstDot = 30;
            lastDot = 37;
            nextLevel = 4;
        }

        if (!isLevelComplete(nextLevel - 1)) {
            setLevelComplete(nextLevel - 1);
            shouldAnimate = true;
        } 
    }

    log::info("Count: {}", m_dotNode->getChildrenCount());

    for (int ii = 0; ii < m_dotNode->getChildrenCount(); ii++)
    {
        auto children = static_cast<CCSprite*>(m_dotNode->getChildren()->objectAtIndex(ii));
        GLubyte opacity = 255;
        float scale = 1.f;

        float delayTime = 0.3 * (ii - firstDot + 1);

        if (ii >= firstDot)
        {
            if (shouldAnimate || ii > lastDot)
            {
                opacity = 0;
                scale = 1.2f;
            }
            
            if (shouldAnimate)
            {
                m_animating = true;

                if (ii == 7 && nextLevel == 2)
                {
                    this->runAction(CCSequence::createWithTwoActions(
                        CCDelayTime::create(delayTime),
                        CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::animateShopUnlock))
                    ));
                }
                if (ii < lastDot + 1)  children->runAction(CCSequence::create(CCDelayTime::create(delayTime), CCFadeIn::create(0.1), CCEaseBounceOut::create(scaleWithBounce), nullptr));
                if (ii == lastDot) 
                {
                    auto levelButton = static_cast<CCMenuItemSpriteExtra*>(m_levelMenu->getChildByTag(nextLevel));
                    levelButton->runAction(CCSequence::createWithTwoActions(
                        CCDelayTime::create(delayTime + .3f),
                        CCCallFuncO::create(levelButton, callfuncO_selector(OdysseySelectLayer::enableLevelAnimation), levelButton)
                    ));

                    this->runAction(CCSequence::createWithTwoActions(
                        CCDelayTime::create(delayTime + .3f),
                        CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::enableButtonTouch))
                    ));
                }
            }

            
        }

        if (lastDot == 0) opacity = 0;
        
        if (children)
        {
            children->setOpacity(opacity);
            children->setScale(scale);
        }

    }
    
}

void OdysseySelectLayer::enableButtonTouch()
{
    this->m_animating = false;
}

void OdysseySelectLayer::switchToPage(int page)
{
    auto scene = OdysseySelectLayer::scene(page);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(0.5f, scene));
}

void OdysseySelectLayer::onNextPage(CCObject *)
{
    switchToPage(m_currentPage + 1);
}

void OdysseySelectLayer::onBackPage(CCObject *)
{
    switchToPage(m_currentPage - 1);
}

void OdysseySelectLayer::onLevel(CCObject *sender)
{
    if (m_animating) return;
    log::info("Tag: {}", sender->getTag());

    if (sender->getTag() != 1 && !isLevelComplete(sender->getTag() - 1)) return;

    auto popup = OdysseyLevelPopup::create(sender->getTag());
    popup->show();
}

void OdysseySelectLayer::onExtraLevel(CCObject *sender)
{
    //  Game Manager
    auto GSM = GameStatsManager::sharedState();
    auto extra01_unlocked = GSM->isItemUnlocked(UnlockType::GJItem, 1);
    auto extra02_unlocked = GSM->isItemUnlocked(UnlockType::GJItem, 2);

    if ((extra01_unlocked && sender->getTag() == 501) || (extra02_unlocked && sender->getTag() == 502))
    {
        auto popup = OdysseyLevelPopup::create(sender->getTag());
        popup->show();
    }
    else
    {
        auto dialog = Odyssey::createDialogResponse("onExtraLevel", m_extraTimes);
        //  GM->setUGV("52", true);
        this->addChild(dialog, 3);

        int tag = (m_extraTimes == 0)   ? 1
                  : (m_extraTimes == 1) ? 2
                                        : 0;
        m_extraTimes = tag;
    }
}

void OdysseySelectLayer::onRope(CCObject*)
{
    auto garage = GJGarageLayer::scene();

    CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInT::create(.63f, garage));
}

void OdysseySelectLayer::onSongs(CCObject*)
{
    auto layer = SongsLayer::create();
    this->addChild(layer);
    layer->showLayer(false);
    
}

void OdysseySelectLayer::onShop(CCObject*)
{
    auto shop = GJShopLayer::scene(static_cast<ShopType>(6));

    CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInT::create(.63f, shop));
}

OdysseySelectLayer *OdysseySelectLayer::create(int page)
{
    OdysseySelectLayer *pRet = new OdysseySelectLayer();
    if (pRet->init(page))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

CCScene *OdysseySelectLayer::scene(int page)
{
    auto scene = CCScene::create();
    scene->addChild(OdysseySelectLayer::create(page));
    return scene;
}
