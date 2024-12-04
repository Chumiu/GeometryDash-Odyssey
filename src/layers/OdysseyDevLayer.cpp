#include "OdysseyDevLayer.hpp"
#include "OdysseyComicLayer.hpp"
#include "OdysseyLevelPopup.hpp"
#include "SecretVaultLayer2.hpp"
#include "../utils/Utils.hpp"

bool OdysseyDevLayer::init()
{
    if (!CCLayer::init())
        return false;

    m_background = CCSprite::create("game_bg_07_001.png");
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto size = m_background->getContentSize();

    m_background->setScale(winSize.width / size.width);
    m_background->setAnchorPoint({0, 0});
    m_background->setPosition({0, -75});
    m_background->setColor({0, 0, 60});
    m_background->setID("background"_spr);

    addChild(m_background, -2);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(OdysseyDevLayer::onBack));

    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);

    auto menuBack = CCMenu::create();
    menuBack->addChild(backBtn);
    menuBack->setPosition({24, winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);

    auto dialogMenu = CCMenu::create();
    dialogMenu->setID("dialog-menu"_spr);
    dialogMenu->setContentSize({480.0f, 140.0f});
    dialogMenu->setLayout(RowLayout::create()
                              ->setGap(14.0f)
                              ->setAutoScale(false)
                              ->setGrowCrossAxis(true)
                              ->setCrossAxisOverflow(false)
                              ->setCrossAxisLineAlignment(AxisAlignment::Even));
    dialogMenu->setPositionY(winSize.height / 2 + 40.0f);

    auto dialogLabel = CCLabelBMFont::create("Dialogs", "goldFont.fnt");
    dialogLabel->setPosition({winSize.width / 2, dialogMenu->getPositionY() + dialogMenu->getContentHeight() / 2 + 10.0f});
    dialogLabel->setScale(0.75f);
    addChild(dialogLabel);

    auto carp01 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (Shop)", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onCarp01));

    auto carp02 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (Extras)", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onCarp02));
    carp02->setTag(0);

    auto carp03 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (Comic)", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onCarp03));
    carp03->setTag(0);

    auto carp04 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (No Coins)", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onCarp04));
    carp04->setTag(0);

    auto wizard01 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Dumbledalf (Introduction)", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onWizard01));

    auto wizard02 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Dumbledalf (Island)", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onWizard02));

    auto wizard03 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Dumbledalf (Finale)", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onWizard03));

    auto wizard04 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Dumbledalf (Access)", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onWizard04));

    dialogMenu->addChild(carp01);
    dialogMenu->addChild(carp02);
    dialogMenu->addChild(carp03);
    dialogMenu->addChild(carp04);
    dialogMenu->addChild(wizard01);
    dialogMenu->addChild(wizard02);
    dialogMenu->addChild(wizard03);
    dialogMenu->addChild(wizard04);
    dialogMenu->updateLayout();
    addChild(dialogMenu);

    auto comicsMenu = CCMenu::create();
    comicsMenu->setID("comics-menu"_spr);
    comicsMenu->setContentSize({360.0f, 40.0f});
    comicsMenu->setLayout(RowLayout::create()
                              ->setGap(14.0f)
                              ->setAutoScale(false)
                              ->setGrowCrossAxis(true)
                              ->setCrossAxisOverflow(false)
                              ->setCrossAxisLineAlignment(AxisAlignment::Even));
    comicsMenu->setPositionY(90);

    auto comicsLabel = CCLabelBMFont::create("Comics", "goldFont.fnt");
    comicsLabel->setPosition({winSize.width / 2, comicsMenu->getPositionY() + comicsMenu->getContentHeight() / 2 + 10.0f});
    comicsLabel->setScale(0.75f);
    addChild(comicsLabel);

    auto comic01 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("1", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onComic));
    comic01->setTag(1);

    auto comic02 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("2", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onComic));
    comic02->setTag(2);

    auto comic03 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("3", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onComic));
    comic03->setTag(3);

    auto comic04 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("4", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onComic));
    comic04->setTag(4);

    auto comic05 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("5", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onComic));
    comic05->setTag(5);

    auto comic06 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("6", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onComic));
    comic06->setTag(6);

    auto comic07 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("?", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onComic));
    comic07->setTag(0);

    comicsMenu->addChild(comic01);
    comicsMenu->addChild(comic02);
    comicsMenu->addChild(comic03);
    comicsMenu->addChild(comic04);
    comicsMenu->addChild(comic05);
    comicsMenu->addChild(comic06);
    comicsMenu->addChild(comic07);
    comicsMenu->updateLayout();
    addChild(comicsMenu);

    auto levelsMenu = CCMenu::create();
    levelsMenu->setID("levels-menu"_spr);
    levelsMenu->setContentSize({350.0f, 40.0f});
    levelsMenu->setLayout(RowLayout::create()
                              ->setGap(14.0f)
                              ->setAutoScale(false)
                              ->setGrowCrossAxis(true)
                              ->setCrossAxisOverflow(false)
                              ->setCrossAxisLineAlignment(AxisAlignment::Even));
    levelsMenu->setPositionY(30);
    auto levelsLabel = CCLabelBMFont::create("levels", "goldFont.fnt");
    levelsLabel->setPosition({winSize.width / 2, levelsMenu->getPositionY() + levelsMenu->getContentHeight() / 2 + 10.0f});
    levelsLabel->setScale(0.75f);
    addChild(levelsLabel);
    auto level01 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Hellfire", 0.5f),
        this,
        menu_selector(OdysseyDevLayer::onLevel));
    level01->setTag(5);
    levelsMenu->addChild(level01);
    levelsMenu->updateLayout();
    addChild(levelsMenu);

    auto hollowSprite = CCSprite::createWithSpriteFrameName("HollowSkull_001.png"_spr);
    hollowSprite->setColor({50, 50, 50});
    hollowSprite->setOpacity(50);

    auto hollowBtn = CCMenuItemSpriteExtra::create(
        hollowSprite,
        this,
        menu_selector(OdysseyDevLayer::onOgre));

    hollowBtn->setPosition({winSize.width - 20, winSize.height - 20});
    hollowBtn->setTag(0);

    auto secretMenu = CCMenu::create();
    secretMenu->addChild(hollowBtn);
    secretMenu->setPosition({0, 0});
    addChild(secretMenu);

    setKeypadEnabled(true);
    return true;
};

void OdysseyDevLayer::onOgre(CCObject *)
{

    if (!Mod::get()->getSettingValue<bool>("meet-hollow"))
    {
        auto dialog = Odyssey::createDialog("hollowMeeting");
        Mod::get()->setSettingValue("meet-hollow", true);
        //  GM->setUGV("52", true);
        this->addChild(dialog, 3);
    }
    else
    {
        auto scene = CCScene::create();
        scene->addChild(SecretVaultLayer2::create());

        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    }
};

void OdysseyDevLayer::onLevel(CCObject *sender)
{
    auto scene = CCScene::create();
    auto tag = sender->getTag();
    auto popup = OdysseyLevelPopup::create(sender->getTag());
    popup->show();
};

void OdysseyDevLayer::onComic(CCObject *sender)
{
    auto scene = CCScene::create();
    auto tag = sender->getTag();

    scene->addChild(OdysseyComicLayer::create(tag));

    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
};

void OdysseyDevLayer::onCarp01(CCObject *)
{
    auto dialog = Odyssey::createDialog("shopIntroduction");
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onCarp02(CCObject *sender)
{
    auto dialog = Odyssey::createDialogResponse("extraIslandLocked", sender->getTag());

    int tag = (sender->getTag() == 0)   ? 1
              : (sender->getTag() == 1) ? 2
                                        : 0;

    sender->setTag(tag);

    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onCarp03(CCObject *sender)
{
    auto dialog = Odyssey::createDialogResponse("finalComicLocked", sender->getTag());

    int tag = (sender->getTag() == 0)   ? 1
              : (sender->getTag() == 1) ? 2
              : (sender->getTag() == 2) ? 3
              : (sender->getTag() == 3) ? 4
              : (sender->getTag() == 4) ? 5
                                        : 0;
    sender->setTag(tag);
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onCarp04(CCObject *sender)
{
    auto dialog = Odyssey::createDialogResponse("playerIsPoor", sender->getTag());

    int tag = (sender->getTag() == 0)   ? 1
              : (sender->getTag() == 1) ? 2
                                        : 0;

    sender->setTag(tag);

    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onWizard01(CCObject *)
{
    auto dialog = Odyssey::createDialog("wizardIntroduction");
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onWizard02(CCObject *)
{
    auto dialog = Odyssey::createDialog("wizardIslandComplete");
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onWizard03(CCObject *)
{
    auto dialog = Odyssey::createDialog("wizardEnding");
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onWizard04(CCObject *)
{
    auto dialog = Odyssey::createDialog("blockedAccess");
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
};

void OdysseyDevLayer::onBack(CCObject *)
{
    keyBackClicked();
};

OdysseyDevLayer *OdysseyDevLayer::create()
{
    auto ret = new OdysseyDevLayer();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *OdysseyDevLayer::scene()
{
    auto layer = OdysseyDevLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};