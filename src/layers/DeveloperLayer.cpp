#include "DeveloperLayer.hpp"
#include "ComicLayer.hpp"
#include "SecretVaultLayer2.hpp"
#include "../nodes/OdysseyLevelPopup.hpp"
#include "../nodes/AlertPopup.hpp"
#include "../utils/Utils.hpp"

bool DeveloperLayer::init()
{
    if (!CCLayer::init())
        return false;

    m_background = CCSprite::create("game_bg_08_001.png");
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto size = m_background->getContentSize();

    m_background->setScale(winSize.width / size.width);
    m_background->setAnchorPoint({0, 0});
    m_background->setPosition({0, -75});
    m_background->setColor({0, 0, 90});
    m_background->setID("background"_spr);
    addChild(m_background, -2);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(DeveloperLayer::onBack));

    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);

    auto menuBack = CCMenu::create();
    menuBack->addChild(backBtn);
    menuBack->setPosition({24, winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);

    //  Menu de dialogos
    auto dialogMenu = CCMenu::create();
    dialogMenu->setID("dialog-menu"_spr);
    dialogMenu->setContentSize({480.0f, 140.0f});
    dialogMenu->setLayout(RowLayout::create()
                              ->setGap(14.0f)
                              ->setAutoScale(false)
                              ->setGrowCrossAxis(true)
                              ->setCrossAxisOverflow(false)
                              ->setCrossAxisLineAlignment(AxisAlignment::Even));
    dialogMenu->setPositionY(winSize.height / 2 + 60.0f);

    auto dialogLabel = CCLabelBMFont::create("Events", "goldFont.fnt");
    dialogLabel->setPosition({winSize.width / 2, dialogMenu->getPositionY() + dialogMenu->getContentHeight() / 2 + 15.0f});
    dialogLabel->setScale(0.75f);
    addChild(dialogLabel);

    auto carp01 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (Shop)", 160, true, "goldFont.fnt", "GJ_button_01.png", 25.f, 0.5f),
        this,
        menu_selector(DeveloperLayer::onStoryDialog));
    carp01->setTag(0);

    auto wizard01 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Dumbledalf (Introduction)", 160, true, "goldFont.fnt", "GJ_button_01.png", 25.f, 0.5f),
        this,
        menu_selector(DeveloperLayer::onStoryDialog));
    wizard01->setTag(1);

    auto wizard02 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Dumbledalf (Island)", 160, true, "goldFont.fnt", "GJ_button_01.png", 25.f, 0.5f),
        this,
        menu_selector(DeveloperLayer::onStoryDialog));
    wizard02->setTag(2);

    auto wizard03 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Dumbledalf (Finale)", 160, true, "goldFont.fnt", "GJ_button_01.png", 25.f, 0.5f),
        this,
        menu_selector(DeveloperLayer::onStoryDialog));
    wizard03->setTag(3);

    auto hollow01 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Hollow (Introduction)", 160, true, "goldFont.fnt", "GJ_button_01.png", 25.f, 0.5f),
        this,
        menu_selector(DeveloperLayer::onStoryDialog));
    hollow01->setTag(4);

    auto hollow02 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Hollow (Coin quota)", 160, true, "goldFont.fnt", "GJ_button_01.png", 25.f, 0.5f),
        this,
        menu_selector(DeveloperLayer::onStoryDialog));
    hollow02->setTag(5);

    auto carp02 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (Extras)", 160, true, "goldFont.fnt", "GJ_button_02.png", 25.f, 0.5f),
        this,
        menu_selector(DeveloperLayer::onCarp02));
    carp02->setTag(0);

    auto carp03 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (Comic)", 160, true, "goldFont.fnt", "GJ_button_02.png", 25.f, 0.5f),
        this,
        menu_selector(DeveloperLayer::onCarp03));
    carp03->setTag(0);

    auto carp04 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (No Coins)", 160, true, "goldFont.fnt", "GJ_button_02.png", 25.f, 0.5f),
        this,
        menu_selector(DeveloperLayer::onCarp04));
    carp04->setTag(0);

    auto popup01 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Savefile Notice", 160, true, "goldFont.fnt", "GJ_button_04.png", 25.f, 0.5f),
        this,
        menu_selector(DeveloperLayer::onPopup));
    popup01->setTag(1);

    auto popup02 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Translation Notice", 160, true, "goldFont.fnt", "GJ_button_04.png", 25.f, 0.5f),
        this,
        menu_selector(DeveloperLayer::onPopup));
    popup02->setTag(2);

    dialogMenu->addChild(carp01);
    dialogMenu->addChild(wizard01);
    dialogMenu->addChild(wizard02);
    dialogMenu->addChild(wizard03);
    dialogMenu->addChild(hollow01);
    dialogMenu->addChild(hollow02);
    dialogMenu->addChild(carp02);
    dialogMenu->addChild(carp03);
    dialogMenu->addChild(popup01);
    dialogMenu->addChild(popup02);
    dialogMenu->updateLayout();
    addChild(dialogMenu);

    //  Menu de Comics
    auto comicsMenu = CCMenu::create();
    comicsMenu->setID("comics-menu"_spr);
    comicsMenu->setContentSize({400.0f, 65.0f});
    comicsMenu->setLayout(RowLayout::create()
                              ->setGap(8.0f)
                              ->setAutoScale(false)
                              ->setGrowCrossAxis(true)
                              ->setCrossAxisOverflow(false)
                              ->setCrossAxisLineAlignment(AxisAlignment::Even));
    comicsMenu->setPositionY(90);

    auto comicsLabel = CCLabelBMFont::create("Comics", "goldFont.fnt");
    comicsLabel->setPosition({winSize.width / 2, comicsMenu->getPositionY() + comicsMenu->getContentHeight() / 2 + 10.0f});
    comicsLabel->setScale(0.75f);
    addChild(comicsLabel);

    for (auto ii = 0; ii < 12; ii++)
    {
        auto seen = GameManager::sharedState()->getUGV(fmt::format("2{}", ii + 11).c_str());
        auto texture = seen ? "GJ_button_01.png" : "GJ_button_04.png";

        auto comic = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(fmt::format("#{:02}", ii + 1).c_str(), 40, true, "goldFont.fnt", texture, 22.5f, 0.4f),
            this,
            menu_selector(DeveloperLayer::onComic));

        comic->setTag(ii + 1);
        comicsMenu->addChild(comic);
    };

    comicsMenu->updateLayout();
    addChild(comicsMenu);

    //  Menu de Niveles
    auto levelsMenu = CCMenu::create();
    levelsMenu->setID("levels-menu"_spr);
    levelsMenu->setContentSize({500.0f, 40.0f});
    levelsMenu->setLayout(RowLayout::create()
                              ->setGap(14.0f)
                              ->setAutoScale(false)
                              ->setGrowCrossAxis(true)
                              ->setCrossAxisOverflow(false)
                              ->setCrossAxisLineAlignment(AxisAlignment::Even));
    levelsMenu->setPositionY(20);
    auto levelsLabel = CCLabelBMFont::create("contest levels (WIP)", "goldFont.fnt");
    levelsLabel->setPosition({winSize.width / 2, levelsMenu->getPositionY() + levelsMenu->getContentHeight() / 2 + 10.0f});
    levelsLabel->setScale(0.75f);
    addChild(levelsLabel);

    for (auto ii = 601; ii <= 605; ii++)
    {
        auto level = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(fmt::format("{}", LevelTools::getAudioTitle(ii)).c_str(), 80, true, "goldFont.fnt", "GJ_button_05.png", 22.5f, 0.4f),
            this,
            menu_selector(DeveloperLayer::onLevel));

        level->setTag(ii + 7000);
        levelsMenu->addChild(level);
    };
    levelsMenu->updateLayout();
    addChild(levelsMenu);

    setKeypadEnabled(true);
    return true;
};

//  Boton del Ogro
void DeveloperLayer::onOgre(CCObject *)
{
    auto scene = CCScene::create();
    scene->addChild(SecretVaultLayer2::create());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
};

//  En Nivel
void DeveloperLayer::onLevel(CCObject *sender)
{
    auto scene = CCScene::create();
    auto tag = sender->getTag();
    auto popup = OdysseyLevelPopup::create(sender->getTag());
    popup->show();
};

//  En Comic
void DeveloperLayer::onComic(CCObject *sender)
{
    auto comic = ComicLayer::create(sender->getTag(), false);
    comic->m_fromPopup = true;

    auto button = static_cast<CCMenuItemSpriteExtra *>(sender);
    button->setSprite(ButtonSprite::create(fmt::format("#{:02}", sender->getTag()).c_str(), 40, true, "goldFont.fnt", "GJ_button_01.png", 22.5f, 0.4f));

    auto scene = CCScene::create();
    scene->addChild(comic);

    GameManager::sharedState()->fadeInMusic(fmt::format("comic_{:02}.mp3"_spr, sender->getTag()).c_str());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
};

//  En dialogo de historia
void DeveloperLayer::onStoryDialog(CCObject *sender)
{
    std::vector<const char *> events = {
        "meetingShopkeeper",
        "meetingWizard",
        "firstIslandClear",
        "end",
        "meetingHollow",
        "hollowQuotaReached",
    };

    auto dialog = Odyssey::createDialog(events[sender->getTag()]);
    this->addChild(dialog, 10);
}

void DeveloperLayer::onPopup(CCObject *sender)
{
    auto tag = sender->getTag();

    if (tag == 1)
    {
        auto popup = AlertPopup::create("Savefile Notice", "<cr>Odyssey</c> stores the data in\na separate <cy>savefile</c>. Your data\nwill be <cg>restored</c> when you\n<cb>turn off</c> the Mod.");
        popup->setWarning(true, false);
        popup->m_scene = this;
        popup->show();
    }

    if (tag == 2)
    {
        auto popup = AlertPopup::create("Language Notice", "Dado a limitaciones de\ncaracteres en el juego, habran\n<cr>errores ortograficos</c>\n(como la falta de acentos)");
        popup->setWarning(false, true);
        popup->m_scene = this;
        popup->setZOrder(104);
        popup->show();
    }
};

void DeveloperLayer::onCarp02(CCObject *sender)
{
    auto dialog = Odyssey::createDialogResponse("onExtraLevel", sender->getTag());

    int tag = (sender->getTag() == 0)   ? 1
              : (sender->getTag() == 1) ? 2
                                        : 0;

    sender->setTag(tag);

    this->addChild(dialog, 3);
};

void DeveloperLayer::onCarp03(CCObject *sender)
{
    auto dialog = Odyssey::createDialogResponse("onFinalComic", sender->getTag());

    int tag = (sender->getTag() == 0)   ? 1
              : (sender->getTag() == 1) ? 2
              : (sender->getTag() == 2) ? 3
              : (sender->getTag() == 3) ? 4
              : (sender->getTag() == 4) ? 5
                                        : 0;
    sender->setTag(tag);
    this->addChild(dialog, 3);
};

void DeveloperLayer::onCarp04(CCObject *sender)
{
    auto dialog = Odyssey::createDialogResponse("onShopItem", sender->getTag());

    int tag = (sender->getTag() == 0)   ? 1
              : (sender->getTag() == 1) ? 2
                                        : 0;

    sender->setTag(tag);
    this->addChild(dialog, 3);
};

void DeveloperLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
};

void DeveloperLayer::onBack(CCObject *)
{
    keyBackClicked();
};

DeveloperLayer *DeveloperLayer::create()
{
    auto ret = new DeveloperLayer();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *DeveloperLayer::scene()
{
    auto layer = DeveloperLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};