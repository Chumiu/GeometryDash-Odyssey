#include "OdysseyEndCreditsLayer.hpp"
#include "OdysseyLevelPopup.hpp"
#include "OdysseyComicLayer.hpp"
#include "SecretVaultLayer2.hpp"
#include "../utils/Utils.hpp"
#include "../nodes/OdysseyEndCreditNode.hpp"
using namespace geode::prelude;

bool OdysseyEndCreditsLayer::init()
{
    if (!CCLayer::init())
        return false;

    FMODAudioEngine::sharedEngine()->playMusic("StayInsideMe.mp3", true, 1.f, 0);

    m_winSize = CCDirector::sharedDirector()->getWinSize();
    m_background = CCSprite::create(GameManager::sharedState()->getBGTexture(32));
    
    auto size = m_background->getContentSize();

    constexpr float tintDur = 1.5f;

    auto bgSequence = CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(tintDur, 40, 100, 255),
        CCTintTo::create(tintDur, 40, 255, 133),
        CCTintTo::create(tintDur, 120, 255, 40),
        CCTintTo::create(tintDur, 255, 208, 40),
        CCTintTo::create(tintDur, 255, 47, 40),
        CCTintTo::create(tintDur, 255, 40, 241),
        CCTintTo::create(tintDur, 65, 40, 255),
        CCTintTo::create(tintDur, 40, 126, 255),
        nullptr
    ));

    m_background->setScale(m_winSize.width / size.width);
    m_background->setAnchorPoint({0, 0});
    m_background->setPosition({0, -75});
    m_background->setColor({40, 100, 255});
    m_background->setID("background"_spr);
    m_background->setOpacity(0);

    this->m_background->runAction(CCSequence::create(
        CCDelayTime::create(5.f),
        CCFadeIn::create(1.5f),
        nullptr
    ));

    this->m_background->runAction(bgSequence);

    addChild(m_background, -2);

    createEndCredits();

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(OdysseyEndCreditsLayer::onBack));

    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);

    auto menuBack = CCMenu::create();
    menuBack->addChild(backBtn);
    menuBack->setPosition({24, m_winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);
    
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    this->scheduleUpdate();
    return true;
};

void OdysseyEndCreditsLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1.f, MenuLayer::scene(false)));
    GameManager::sharedState()->fadeInMenuMusic();
};

void OdysseyEndCreditsLayer::backMenuLayer()
{
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1.f, MenuLayer::scene(false)));
    GameManager::sharedState()->fadeInMenuMusic();
};

void OdysseyEndCreditsLayer::onBack(CCObject *)
{
    keyBackClicked();
};

void OdysseyEndCreditsLayer::createEndCredits() {
    endCreditsLayer = CCLayer::create();
    auto endCreditsMenu01 = CCMenu::create();
    auto endCreditsMenu02 = CCMenu::create();
    auto endCreditsMenu03 = CCMenu::create();
    auto endCreditsMenu04 = CCMenu::create();
    auto endCreditsMenu05 = CCMenu::create();
    auto endCreditsMenu06 = CCMenu::create();
    auto endCreditsMenu07 = CCMenu::create();

    row1CreditArray = CCArray::create();
    row2CreditArray = CCArray::create();
    row3CreditArray = CCArray::create();
    row4CreditArray = CCArray::create();
    row5CreditArray = CCArray::create();
    row6CreditArray = CCArray::create();
    row7CreditArray = CCArray::create();
    row8CreditArray = CCArray::create();
    row9CreditArray = CCArray::create();
    row10CreditArray = CCArray::create();
    row11CreditArray = CCArray::create();

    auto m_textArea = TextArea::create("A <co>TCM Team</c> Productions", "bigFont.fnt", 1.f, 1000.f, {0.5, 0.5}, 40.f, false);
    m_textArea->setScale(0.75f);
    m_textArea->setOpacity(0);

    auto m_sprite = CCSprite::createWithSpriteFrameName("GDO_MainLogo_001.png"_spr);
    m_sprite->setOpacity(0);
    m_sprite->setPosition(ccp(m_textArea->getPositionX(), m_textArea->getPositionY()));

    m_textArea->runAction(CCSequence::create(
        CCDelayTime::create(1.5f),
        CCFadeTo::create(1.5f, 255),
        CCDelayTime::create(1.f),
        CCFadeTo::create(1.5f, 0),
        nullptr
    ));

    m_sprite->runAction(CCSequence::create(
        CCDelayTime::create(5.5f),
        CCFadeIn::create(1.5f),
        nullptr
    ));

    auto creditsReason = CCLabelBMFont::create("Management and Organization", "goldFont.fnt");
    creditsReason->setScale(0.8f);
    creditsReason->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    creditsReason->setPosition(ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - m_winSize.height) + 125));

    auto SwitchStepUser = OdysseyEndCreditNode::create("SwitchStepGDYT", 106, 18, 12, 9, true);
    auto ZapManiacUser = OdysseyEndCreditNode::create("ZapManiac", 80, 6, 0, 8, true);
    auto MathisCreatorUser = OdysseyEndCreditNode::create("MathisCreator", 263, 8, 11, 3, true);
    auto SearUser = OdysseyEndCreditNode::create("Sear15", 51, 7, 12, 3, true);

    row1CreditArray->addObject(SwitchStepUser);
    row1CreditArray->addObject(ZapManiacUser);
    row1CreditArray->addObject(MathisCreatorUser);
    row1CreditArray->addObject(SearUser);

    //endCreditsMenu->setPosition({m_winSize.width/2, m_winSize.height/2});

    GameToolbox::alignItemsHorisontally(row1CreditArray, 95.f, ccp(m_sprite->getPositionX(), m_sprite->getPositionY() - m_winSize.height), false);

    auto creditsReason02 = CCLabelBMFont::create("Level Creators", "goldFont.fnt");
    creditsReason02->setScale(0.8f);
    creditsReason02->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    creditsReason02->setPosition(ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - (m_winSize.height * 2)) + 125));

    auto MathisCreatorUser02 = OdysseyEndCreditNode::create("MathisCreator", 263, 8, 11, 3, true);
    MathisCreatorUser02->setScale(0.85);

    auto SwitchStepUser02 = OdysseyEndCreditNode::create("SwitchStepGDYT", 106, 18, 12, 9, true);
    SwitchStepUser02->setScale(0.85);

    auto ZapManiacUser02 = OdysseyEndCreditNode::create("ZapManiac", 80, 6, 0, 8, true);
    ZapManiacUser02->setScale(0.85);

    auto JintaUser = OdysseyEndCreditNode::create("Jinta22", 231, 18, 9, 3, true);
    JintaUser->setScale(0.85);

    auto KoromiGDUser = OdysseyEndCreditNode::create("KoromiGD", 98, 17, 2, 44, true);
    KoromiGDUser->setScale(0.85);

    auto DankyUser = OdysseyEndCreditNode::create("Danky99", 88, 9, 11, 3, true);
    DankyUser->setScale(0.85);

    auto MasterTheCubeUser = OdysseyEndCreditNode::create("MasterTheCube5", 107, 6, 10, 11, true);
    MasterTheCubeUser->setScale(0.85);

    auto GenaUser = OdysseyEndCreditNode::create("GenaMorphosis", 467, 6, 83, 40, true);
    GenaUser->setScale(0.85);

    auto NKUser = OdysseyEndCreditNode::create("NotKaizer", 135, 41, 11, 12, true);
    NKUser->setScale(0.85);

    auto DogneRUser = OdysseyEndCreditNode::create("DogneR", 12, 33, 2, 2, true);
    DogneRUser->setScale(0.85);

    auto JoshuaUser = OdysseyEndCreditNode::create("JoshuaGD23", 459, 12, 12, 12, true);
    JoshuaUser->setScale(0.85);

    auto BonntuUser = OdysseyEndCreditNode::create("Bonntu", 35, 12, 17, 70, true);
    BonntuUser->setScale(0.85);

    auto SearUser02 = OdysseyEndCreditNode::create("Sear15", 51, 7, 12, 3, true);
    SearUser02->setScale(0.85);

    auto BreadUser = OdysseyEndCreditNode::create("TheBreadCat24", 371, 12, 3, 3, true);
    BreadUser->setScale(0.85);
    
    auto BenUser = OdysseyEndCreditNode::create("ReyBenGDYT", 1, 86, 0, 0, true);
    BenUser->setScale(0.85);

    row2CreditArray->addObject(MathisCreatorUser02);
    row2CreditArray->addObject(SwitchStepUser02);
    row2CreditArray->addObject(ZapManiacUser02);
    row2CreditArray->addObject(JintaUser);
    row2CreditArray->addObject(KoromiGDUser);

    row3CreditArray->addObject(DankyUser);
    row3CreditArray->addObject(MasterTheCubeUser);
    row3CreditArray->addObject(GenaUser);
    row3CreditArray->addObject(NKUser);
    row3CreditArray->addObject(DogneRUser);

    row4CreditArray->addObject(JoshuaUser);
    row4CreditArray->addObject(BonntuUser);
    row4CreditArray->addObject(SearUser02);
    row4CreditArray->addObject(BreadUser);
    row4CreditArray->addObject(BenUser);

    GameToolbox::alignItemsHorisontally(row2CreditArray, 95.f, ccp(m_sprite->getPositionX(), m_sprite->getPositionY() - (m_winSize.height * 2) + 40), false);
    GameToolbox::alignItemsHorisontally(row3CreditArray, 95.f, ccp(m_sprite->getPositionX(), m_sprite->getPositionY() - (m_winSize.height * 2) - 17), false);
    GameToolbox::alignItemsHorisontally(row4CreditArray, 95.f, ccp(m_sprite->getPositionX(), m_sprite->getPositionY() - (m_winSize.height * 2) - 75), false);

    auto creditsReason03 = CCLabelBMFont::create("Artists", "goldFont.fnt");
    creditsReason03->setScale(0.8f);
    creditsReason03->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    creditsReason03->setPosition(ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - (m_winSize.height * 3)) + 125));

    auto DankyUser02 = OdysseyEndCreditNode::create("Danky99", 88, 9, 11, 3, true);
    DankyUser02->setScale(0.85);

    auto BenUser02 = OdysseyEndCreditNode::create("ReyBenGDYT", 1, 86, 0, 0, true);
    BenUser02->setScale(0.85);

    auto _3lipngUser = OdysseyEndCreditNode::create("3lipng", 465, 12, 17, 17, true);
    _3lipngUser->setScale(0.85);

    auto VaughnersUser = OdysseyEndCreditNode::create("Vaughners", 350, 87, 3, 40, true);
    VaughnersUser->setScale(0.85);

    auto MinoX29User = OdysseyEndCreditNode::create("MinoX28", 283, 94, 12, 12, true);
    MinoX29User->setScale(0.85);

    auto ML5User02 = OdysseyEndCreditNode::create("ML500", 296, 22, 106, 106, true);
    ML5User02->setScale(0.85);

    auto cyanflowerUser = OdysseyEndCreditNode::create("cyanflower", 2, 12, 3, 3, true);
    cyanflowerUser->setScale(0.85);

    auto AngelozDDUser = OdysseyEndCreditNode::create("AngelozDD", 431, 0, 3, 12, true);
    AngelozDDUser->setScale(0.85);

    auto MasterTheCubeUser02 = OdysseyEndCreditNode::create("MasterTheCube5", 107, 6, 10, 11, true);
    MasterTheCubeUser02->setScale(0.85);

    auto SweeSwagUser = OdysseyEndCreditNode::create("SweeSwag", 102, 12, 8, 8, true);
    SweeSwagUser->setScale(0.85);

    row5CreditArray->addObject(DankyUser02);
    row5CreditArray->addObject(BenUser02);
    row5CreditArray->addObject(_3lipngUser);
    row5CreditArray->addObject(VaughnersUser);
    row5CreditArray->addObject(MinoX29User);

    row6CreditArray->addObject(ML5User02);
    row6CreditArray->addObject(cyanflowerUser);
    row6CreditArray->addObject(AngelozDDUser);
    row6CreditArray->addObject(MasterTheCubeUser02);
    row6CreditArray->addObject(SweeSwagUser);

    GameToolbox::alignItemsHorisontally(row5CreditArray, 95.f, ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - (m_winSize.height * 3)) + 30), false);
    GameToolbox::alignItemsHorisontally(row6CreditArray, 95.f, ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - (m_winSize.height * 3)) - 55), false);

    auto creditsReason04 = CCLabelBMFont::create("Playtesters", "goldFont.fnt");
    creditsReason04->setScale(0.8f);
    creditsReason04->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    creditsReason04->setPosition(ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - (m_winSize.height * 4)) + 125));

    auto DAPixelheroUser = OdysseyEndCreditNode::create("DAPixelhero", 72, 5, 9, 12, true);
    DAPixelheroUser->setScale(0.85);

    auto AndrexelUser = OdysseyEndCreditNode::create("Andrexel", 114, 8, 11, 11, true);
    AndrexelUser->setScale(0.85);

    auto cyanflowerUser02 = OdysseyEndCreditNode::create("cyanflower", 2, 12, 3, 3, true);
    cyanflowerUser02->setScale(0.85);

    auto ZerkGMDUser = OdysseyEndCreditNode::create("ZerkGMD", 37, 12, 15, 12, true);
    ZerkGMDUser->setScale(0.85);

    auto ObsidianAJUser = OdysseyEndCreditNode::create("ObsidianAJ", 48, 6, 3, 44, true);
    ObsidianAJUser->setScale(0.85);

    auto Emmmanuel2014User = OdysseyEndCreditNode::create("Emmmanuel2014", 42, 15, 3, 3, true);
    Emmmanuel2014User->setScale(0.85);

    auto DolphinOFFICIALUser = OdysseyEndCreditNode::create("DolphinOFFICIAL", 371, 4, 14, 14, true);
    DolphinOFFICIALUser->setScale(0.85);

    auto TochyGMDUser = OdysseyEndCreditNode::create("TochyGMD", 98, 12, 12, 3, true);
    TochyGMDUser->setScale(0.85);

    auto MichTopGDMTUser = OdysseyEndCreditNode::create("MichTopGDMT", 22, 3, 12, 3, true);
    MichTopGDMTUser->setScale(0.85);

    auto dreenUser = OdysseyEndCreditNode::create("dreen", 1, 0, 3, 3, true);
    dreenUser->setScale(0.85);

    row7CreditArray->addObject(DAPixelheroUser);
    row7CreditArray->addObject(AndrexelUser);
    row7CreditArray->addObject(cyanflowerUser02);
    row7CreditArray->addObject(ZerkGMDUser);
    row7CreditArray->addObject(ObsidianAJUser);

    row8CreditArray->addObject(Emmmanuel2014User);
    row8CreditArray->addObject(DolphinOFFICIALUser);
    row8CreditArray->addObject(TochyGMDUser);
    row8CreditArray->addObject(MichTopGDMTUser);
    row8CreditArray->addObject(dreenUser);

    GameToolbox::alignItemsHorisontally(row7CreditArray, 95.f, ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - (m_winSize.height * 4)) + 30), false);
    GameToolbox::alignItemsHorisontally(row8CreditArray, 95.f, ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - (m_winSize.height * 4)) - 55), false);

    auto creditsReason05 = CCLabelBMFont::create("Special Thanks", "goldFont.fnt");
    creditsReason05->setScale(0.8f);
    creditsReason05->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    creditsReason05->setPosition(ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - (m_winSize.height * 5)) + 125));

    auto RobTopUser = OdysseyEndCreditNode::create("RobTop", 275, 6, 3, 1, true);
    RobTopUser->setScale(0.85);

    auto EVWUser = OdysseyEndCreditNode::create("EVW", 28, 12, 9, 9, true);
    EVWUser->setScale(0.85);

    auto ImFernandoUser = OdysseyEndCreditNode::create("im fernando", 56, 35, 3, 3, true);
    ImFernandoUser->setScale(0.85);

    auto StivenelXDUser = OdysseyEndCreditNode::create("StivenelXD", 50, 12, 3, 3, true);
    StivenelXDUser->setScale(0.85);

    auto CapelingUser = OdysseyEndCreditNode::create("Capeling", 70, 41, 12, 12, true);
    CapelingUser->setScale(0.85);

    auto LimeGradientUser = OdysseyEndCreditNode::create("LimeGradient", 46, 98, 12, 43, true);
    LimeGradientUser->setScale(0.85);

    auto MXSTOUser = OdysseyEndCreditNode::create("Mxst0", 296, 89, 2, 44, true);
    MXSTOUser->setScale(0.85);

    auto BlueSpaceUser = OdysseyEndCreditNode::create("Bluespace", 37, 3, 6, 6, true);
    BlueSpaceUser->setScale(0.85);

    row9CreditArray->addObject(RobTopUser);

    row10CreditArray->addObject(EVWUser);
    row10CreditArray->addObject(ImFernandoUser);
    row10CreditArray->addObject(StivenelXDUser);

    row11CreditArray->addObject(CapelingUser);
    row11CreditArray->addObject(LimeGradientUser);
    row11CreditArray->addObject(MXSTOUser);
    row11CreditArray->addObject(BlueSpaceUser);

    GameToolbox::alignItemsHorisontally(row9CreditArray, 95.f, ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - (m_winSize.height * 5)) + 40), false);
    GameToolbox::alignItemsHorisontally(row10CreditArray, 95.f, ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - (m_winSize.height * 5)) - 17), false);
    GameToolbox::alignItemsHorisontally(row11CreditArray, 95.f, ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - (m_winSize.height * 5)) - 75), false);

    auto creditsReason06 = CCLabelBMFont::create("Thanks for playing :D", "goldFont.fnt");
    creditsReason06->setScale(0.8f);
    creditsReason06->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    creditsReason06->setPosition(ccp(m_sprite->getPositionX(), (m_sprite->getPositionY() - m_winSize.height * 6)));

    endCreditsMenu01->setID("menu-title"_spr);
    endCreditsMenu02->setID("one-section"_spr);
    endCreditsMenu03->setID("two-section"_spr);
    endCreditsMenu04->setID("three-section"_spr);
    endCreditsMenu05->setID("four-section"_spr);
    endCreditsMenu06->setID("five-section"_spr);
    endCreditsMenu07->setID("six-section"_spr);

    endCreditsMenu01->addChild(m_sprite);
    endCreditsMenu01->addChild(m_textArea);

    endCreditsMenu02->addChild(creditsReason);
    endCreditsMenu02->addChild(SwitchStepUser);
    endCreditsMenu02->addChild(ZapManiacUser);
    endCreditsMenu02->addChild(MathisCreatorUser);
    endCreditsMenu02->addChild(SearUser);

    endCreditsMenu03->addChild(creditsReason02);
    endCreditsMenu03->addChild(SwitchStepUser02, 4);
    endCreditsMenu03->addChild(ZapManiacUser02, 4);
    endCreditsMenu03->addChild(MathisCreatorUser02, 4);
    endCreditsMenu03->addChild(JintaUser, 4);

    endCreditsMenu03->addChild(KoromiGDUser, 4);
    endCreditsMenu03->addChild(DankyUser, 4);
    endCreditsMenu03->addChild(MasterTheCubeUser, 4);
    endCreditsMenu03->addChild(GenaUser, 4);

    endCreditsMenu03->addChild(NKUser, 4);
    endCreditsMenu03->addChild(DogneRUser, 4);
    endCreditsMenu03->addChild(JoshuaUser, 4);
    endCreditsMenu03->addChild(BonntuUser, 4);

    endCreditsMenu03->addChild(SearUser02, 4);
    endCreditsMenu03->addChild(BreadUser, 4);
    endCreditsMenu03->addChild(BenUser, 4);

    endCreditsMenu04->addChild(creditsReason03);
    endCreditsMenu04->addChild(DankyUser02, 4);
    endCreditsMenu04->addChild(BenUser02, 4);
    endCreditsMenu04->addChild(_3lipngUser, 4);
    endCreditsMenu04->addChild(VaughnersUser, 4);
    endCreditsMenu04->addChild(MinoX29User, 4);

    endCreditsMenu04->addChild(ML5User02, 4);
    endCreditsMenu04->addChild(cyanflowerUser, 4);
    endCreditsMenu04->addChild(AngelozDDUser, 4);
    endCreditsMenu04->addChild(MasterTheCubeUser02, 4);
    endCreditsMenu04->addChild(SweeSwagUser, 4);

    endCreditsMenu05->addChild(creditsReason04);
    endCreditsMenu05->addChild(DAPixelheroUser, 4);
    endCreditsMenu05->addChild(AndrexelUser, 4);
    endCreditsMenu05->addChild(cyanflowerUser02, 4);
    endCreditsMenu05->addChild(ZerkGMDUser, 4);
    endCreditsMenu05->addChild(ObsidianAJUser, 4);

    endCreditsMenu05->addChild(Emmmanuel2014User, 4);
    endCreditsMenu05->addChild(DolphinOFFICIALUser, 4);
    endCreditsMenu05->addChild(TochyGMDUser, 4);
    endCreditsMenu05->addChild(MichTopGDMTUser, 4);
    endCreditsMenu05->addChild(dreenUser, 4);

    endCreditsMenu06->addChild(creditsReason05);
    endCreditsMenu06->addChild(RobTopUser, 4);
    endCreditsMenu06->addChild(EVWUser, 4);
    endCreditsMenu06->addChild(ImFernandoUser, 4);
    endCreditsMenu06->addChild(StivenelXDUser, 4);
    endCreditsMenu06->addChild(CapelingUser, 4);
    endCreditsMenu06->addChild(LimeGradientUser, 4);
    endCreditsMenu06->addChild(MXSTOUser, 4);
    endCreditsMenu06->addChild(BlueSpaceUser, 4);

    endCreditsMenu07->addChild(creditsReason06);
    
    endCreditsLayer->addChild(endCreditsMenu01);
    endCreditsLayer->addChild(endCreditsMenu02);
    endCreditsLayer->addChild(endCreditsMenu03);
    endCreditsLayer->addChild(endCreditsMenu04);
    endCreditsLayer->addChild(endCreditsMenu05);
    endCreditsLayer->addChild(endCreditsMenu06);
    endCreditsLayer->addChild(endCreditsMenu07);

    this->endCreditsLayer->runAction(CCSequence::create(
        CCDelayTime::create(8.5f),
        CCMoveBy::create(25.f, {endCreditsLayer->getPositionX(), endCreditsLayer->getPositionY() + m_winSize.height * 6}),
        CCDelayTime::create(1.5f),
        CCCallFunc::create(this, callfunc_selector(OdysseyEndCreditsLayer::backMenuLayer)),
        nullptr
    ));

    addChild(endCreditsLayer);
};

OdysseyEndCreditsLayer *OdysseyEndCreditsLayer::create()
{
    OdysseyEndCreditsLayer *pRet = new OdysseyEndCreditsLayer();
    if (pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

CCScene *OdysseyEndCreditsLayer::scene()
{
    auto layer = OdysseyEndCreditsLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
}