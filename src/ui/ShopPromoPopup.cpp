#include "ShopPromoPopup.hpp"
#include "../utils/Utils.hpp"

bool PromoPopup::init()
{
    if (!Popup::init(400.f, 240.f, "GJ_square02.png"))
        return false;

    auto contentSize = m_mainLayer->getContentSize();
    auto spanish = Odyssey::isSpanish();

    //  Popup textarea background
    auto m_background = CCScale9Sprite::create("square02b_001.png", {0, 0, 80, 80});
    m_background->setPosition({contentSize.width / 2, contentSize.height / 2 + 40});
    m_background->setContentSize({contentSize.width - 20.f, 80});
    m_background->setColor({0, 0, 120});
    m_background->setOpacity(120);
    m_mainLayer->addChild(m_background);

    //  Content
    std::string content = Odyssey::createText(
        "You can watch an animation made by\n<co>MasterTheCube5</c>\nTo get an extra orbs.",
        "Puedes ver una animacion hecha por\n<co>MasterTheCube5</c>\nPara tener orbes extra.");

    //  Text Area
    m_textArea = TextArea::create(content, "bigFont.fnt", 1.f, 760.f, {0.5, 0.5}, 32.f, false);
    m_textArea->setPosition(m_background->getPosition());
    m_textArea->setID("promo-text-area");
    m_mainLayer->addChild(m_textArea);
    m_textArea->setScale(0.5f);

    //  Cube sprite
    m_masterSpr = CCSprite::createWithSpriteFrameName("MasterTheCube_01_001.png"_spr);
    m_masterSpr->setPosition({contentSize.width / 2, 45});
    m_masterSpr->setID("master-cube-sprite");
    m_mainLayer->addChild(m_masterSpr);

    //  Button
    auto buttonMenu = CCMenu::create();
    buttonMenu->setContentSize(contentSize);
    buttonMenu->setPosition(contentSize / 2);
    m_mainLayer->addChild(buttonMenu);

    m_button = CCMenuItemSpriteExtra::create(
        ButtonSprite::create(spanish ? "Ver video" : "Watch Video", 160, true, "goldFont.fnt", "GJ_button_01.png", 28.f, .75f),
        this,
        menu_selector(PromoPopup::onClick));
    m_button->setPositionY(-20);
    m_button->setID("promo-button");
    buttonMenu->addChild(m_button);

    std::string info = Odyssey::createText(
        "This is to make it up for some players losing orbs upon game reloading in <cy>Version 1.0</c> of the fangame, it might not give as much but hopefully it can make it up for the issues.",
        "Esto es para compensar a algunos jugadores que perdieron orbes al recargar el juego en la <cy>Version 1.0</c> del fangame, puede que no de tanto pero esperemos que pueda compensar los problemas.");

    //  Info button at the top right corner
    auto infoButton = InfoAlertButton::create("Note", info, 1);
    infoButton->setPosition({contentSize.width / 2 - 25, contentSize.height / 2 - 20});
    buttonMenu->addChild(infoButton);

    this->setTitle("Bonus Rewards");
    this->setID("promo-popup");
    m_title->setScale(1.0f);

    return true;
};

void PromoPopup::onClick(CCObject *sender)
{
    if (m_isRewardAvailable)
    {
        auto GSM = GameStatsManager::sharedState();
        GSM->incrementStat("14", 50 * m_random);

        //  Creates the rewards for the chest
        GJRewardObject *orbs = GJRewardObject::create(SpecialRewardItem::Orbs, 50, 0);
        CCArray *rewards = CCArray::create();
        rewards->addObject(orbs);

        //  Creates the layer
        GJRewardItem *item = GJRewardItem::createWithObjects(GJRewardType::Small, rewards);
        RewardUnlockLayer *layer = RewardUnlockLayer::create(2, nullptr);
        layer->m_chestType = 2;
        layer->setZOrder(200);

        //  Adds the Reward unlock scene
        cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer);
        layer->showCollectReward(item);
        keyBackClicked();
        return;
    };

    //  Gives a randomized time
    m_random = std::rand() % 3 + 1;
    m_countdown = m_random * 10;

    //  Disables the button and triggers the countdown
    m_button->setEnabled(false);
    m_button->runAction(CCSequence::create(
        CCCallFunc::create(this, callfunc_selector(PromoPopup::onCountdown)),
        nullptr));

    //  Opens the URL of a random animation from MasterTheCube
    std::vector<gd::string> videoLinks = {
        "https://youtu.be/34ajXNmtI4U?si=cLptfnth-uhYDq9E",
        "https://youtu.be/aRdpABVEKho?si=2huyHafEWQFz1R58",
        "https://youtu.be/uvN5OGo_fcY?si=piU_ncFAZvQJCUUD",
        "https://youtu.be/abB1-zyyHSI?si=1XBhha5sC1ho9MqU",
        "https://youtu.be/pxwycKKARaA?si=60AH9WuwpmV7U-75"};

    CCApplication::sharedApplication()->openURL(videoLinks.at(rand() % videoLinks.size()).c_str());
}

void PromoPopup::onCountdown()
{
    m_button->setSprite(ButtonSprite::create(fmt::format("Wait... ({:02})", m_countdown).c_str(), 160, true, "goldFont.fnt", "GJ_button_05.png", 28.f, .75f));

    if (m_countdown > 0)
    {
        m_button->runAction(CCSequence::create(
            CCDelayTime::create(1),
            CCCallFunc::create(this, callfunc_selector(PromoPopup::onCountdown)),
            nullptr));

        m_countdown--;
    }
    else
    {
        auto contentSize = m_mainLayer->getContentSize();
        m_isRewardAvailable = true;

        //  Quita y recrea el sprite de Master de nuevo
        m_masterSpr->removeFromParentAndCleanup(true);
        m_masterSpr = CCSprite::createWithSpriteFrameName("MasterTheCube_02_001.png"_spr);
        m_masterSpr->setPosition({contentSize.width / 2, 45});
        m_mainLayer->addChild(m_masterSpr);

        //  Recrea el Text Area de nuevo
        m_textArea->removeFromParentAndCleanup(true);
        m_textArea = TextArea::create(Odyssey::createText("Thank you for your patience.", "Gracias por su paciencia."), "bigFont.fnt", 1.f, 760.f, {0.5, 0.5}, 32.f, false);
        m_textArea->setPosition({contentSize.width / 2, contentSize.height / 2 + 40});
        m_textArea->setScale(0.5f);
        m_mainLayer->addChild(m_textArea);

        //  Cambia el sprite del boton
        m_button->setSprite(ButtonSprite::create(Odyssey::createText("Claim Bonus!", "Reclamar Bonus!").c_str(), 160, true, "goldFont.fnt", "GJ_button_02.png", 28.f, .75f));
        m_button->setEnabled(true);
    }
};

PromoPopup *PromoPopup::create()
{
    auto ret = new PromoPopup();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};