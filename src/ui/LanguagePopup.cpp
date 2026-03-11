#include "LanguagePopup.hpp"
#include "../utils/Utils.hpp"
#include "../ui/AlertPopup.hpp"

bool LanguagePopup::init()
{
    if (!Popup::init(260.f, 140.f))
        return false;

    auto contentSize = m_mainLayer->getContentSize();
    m_toggled = Odyssey::isSpanish();

    auto m_background = CCScale9Sprite::create("square02b_001.png", {0, 0, 80, 80});
    m_background->setContentSize({240, 60});
    m_background->setColor({133, 68, 41});
    m_mainLayer->addChildAtPosition(m_background, Anchor::Center, ccp(0, 0), false);

    //  Menu
    auto menu = CCMenu::create();
    menu->setContentSize(m_mainLayer->getContentSize());
    m_mainLayer->addChildAtPosition(menu, Anchor::BottomLeft, ccp(0, 0), false);

    //  English Sprites
    m_englishBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GDO_EnglishBtn_001.png"_spr),
        this,
        menu_selector(LanguagePopup::onUpdate));
    m_englishBtn->m_scaleMultiplier = 1.1;
    m_englishBtn->setTag(0);

    //  Spanish Sprites
    m_spanishBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GDO_SpanishBtn_001.png"_spr),
        this,
        menu_selector(LanguagePopup::onUpdate));
    m_spanishBtn->m_scaleMultiplier = 1.1;
    m_spanishBtn->setTag(1);

    //  Adds the buttons
    menu->addChildAtPosition(m_englishBtn, Anchor::Center, ccp(-50, 0), false);
    menu->addChildAtPosition(m_spanishBtn, Anchor::Center, ccp(50, 0), false);

    //  Info Button
    m_infoButton = InfoAlertButton::create("Notice", "", 0.75f);
    menu->addChildAtPosition(m_infoButton, Anchor::TopRight, ccp(-20, -20), false);

    //  Repositions the close Btn
    m_closeBtn->setNormalImage(ButtonSprite::create("OK", 40, true, "goldFont.fnt", "GJ_button_01.png", 22.f, 0.6f));
    m_closeBtn->setPosition({contentSize.width / 2, 21.f});

    //  Calls the function to toggle the language
    toggle();

    this->m_reverseKeyBack = true;
    return true;
}

void LanguagePopup::toggle()
{
    if (m_toggled)
    {
        m_spanishBtn->setColor({255, 255, 255});
        m_englishBtn->setColor({100, 100, 100});
        this->setTitle("Elije un Lenguaje:");
    }
    else
    {
        m_spanishBtn->setColor({100, 100, 100});
        m_englishBtn->setColor({255, 255, 255});
        this->setTitle("Select a Language:");
    }

    auto desc = Odyssey::createText(
        "Most features of the mod have a <cy>spanish translation available</c> (such as story dialogs and comics), but some features from the base game don't.",
        "La mayoria del contenido del mod tienen una <cy>traduccion disponible</c> (como los dialogos de la historia y los comics), pero algunas partes del juego base no la tienen.");
    m_infoButton->m_description = desc;
    m_title->setScale(0.70f);

    Odyssey::setSpanish(m_toggled);
};

void LanguagePopup::onUpdate(CCObject *sender)
{
    m_toggled = sender->getTag();
    toggle();
};

void LanguagePopup::onClose(CCObject *)
{
    if (!Mod::get()->setSavedValue("shown-safevile-warning", true))
    {
        auto title = Odyssey::createText("Savefile Notice", "Aviso de Save-file");
        auto desc = Odyssey::createText(
            "<cr>Odyssey</c> stores the data in\na separate <cy>savefile</c>. Your data\nwill be <cg>restored</c> when you\n<cb>turn off</c> the Mod.",
            "<cr>Odyssey</c> guarda los datos en\nun <cy>savefile</c> aparte. Tus datos\nse <cg>restauran</c> cuando \n<cb>deshabilites</c> el Mod.");

        auto savefilePopup = AlertPopup::create(title, desc);
        savefilePopup->m_scene = CCDirector::sharedDirector()->getRunningScene();
        savefilePopup->setWarning(true, false);
        savefilePopup->setZOrder(105);
        savefilePopup->show();
    }

    if (Odyssey::isSpanish() && (!Mod::get()->setSavedValue("shown-translation-warning", true)))
    {
        auto translationPopup = AlertPopup::create("Aviso de Traduccion", "Dado a limitaciones de\ncaracteres en el juego, habran\n<cr>errores ortograficos</c>\n(como la falta de acentos)");
        translationPopup->m_scene = CCDirector::sharedDirector()->getRunningScene();
        translationPopup->setWarning(false, true);
        translationPopup->setZOrder(103);
        translationPopup->show();
    }

    removeFromParentAndCleanup(true);
};

LanguagePopup *LanguagePopup::create()
{
    auto ret = new LanguagePopup();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};