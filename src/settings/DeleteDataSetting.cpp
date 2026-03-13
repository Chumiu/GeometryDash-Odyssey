#include <Geode/loader/SettingV3.hpp>
#include <Geode/loader/Mod.hpp>
#include "../utils/Utils.hpp"
using namespace geode::prelude;

//  Yes, this was taken from the example in the Geode Documents
class DeleteDataSetting : public SettingV3
{
public:
    static Result<std::shared_ptr<SettingV3>> parse(std::string const &key, std::string const &modID, matjson::Value const &json)
    {
        auto res = std::make_shared<DeleteDataSetting>();
        auto root = checkJson(json, "DeleteDataSetting");

        res->init(key, modID, root);
        res->parseNameAndDescription(root);
        res->parseEnableIf(root);

        root.checkUnknownKeys();
        return root.ok(std::static_pointer_cast<SettingV3>(res));
    }

    bool load(matjson::Value const &json) override
    {
        return true;
    }

    bool save(matjson::Value &json) const override
    {
        return true;
    }

    bool isDefaultValue() const override
    {
        return true;
    }

    void reset() override {}

    SettingNodeV3 *createNode(float width) override;
};

class DeleteDataNode : public SettingNodeV3
{
protected:
    ButtonSprite *m_buttonSprite;
    CCMenuItemSpriteExtra *m_button;

    bool init(std::shared_ptr<DeleteDataSetting> setting, float width)
    {
        if (!SettingNodeV3::init(setting, width))
            return false;

        this->setContentSize({width, 35.f});
        this->getNameLabel()->setVisible(false);

        //  Menu
        auto m_buttonMenu = this->getButtonMenu();
        m_buttonMenu->setAnchorPoint({0.5, 0.5});
        m_buttonMenu->setPositionX(width / 2);
        m_buttonMenu->setContentWidth(60);
        m_buttonMenu->updateLayout();

        //  Button
        m_buttonSprite = ButtonSprite::create("Delete Save Data", "goldFont.fnt", "GJ_button_06.png", .8f);
        m_buttonSprite->setScale(.75f);
        m_button = CCMenuItemSpriteExtra::create(
            m_buttonSprite,
            this,
            menu_selector(DeleteDataNode::onButton));
        m_buttonMenu->addChildAtPosition(m_button, Anchor::Center);

        this->updateState(nullptr);
        return true;
    }

    void updateState(CCNode *invoker) override
    {
        SettingNodeV3::updateState(invoker);

        auto shouldEnable = this->getSetting()->shouldEnable();
        m_button->setEnabled(shouldEnable);
        m_buttonSprite->setCascadeColorEnabled(true);
        m_buttonSprite->setCascadeOpacityEnabled(true);
        m_buttonSprite->setOpacity(shouldEnable ? 255 : 155);
        m_buttonSprite->setColor(shouldEnable ? ccWHITE : ccGRAY);
    }

    void onButton(CCObject *)
    {
        auto title = Odyssey::createText("Delete Data?", "Borrar Datos");
        auto warning = Odyssey::createText(
            "Are you sure you want to <cr>delete your save data</c> of <cy>Geometry Dash Odyssey</c>?",
            "Estas seguro que quieres <cr>eliminar los datos guardados</c> de <cy>Geometry Dash Odyssey</c>?");

        auto popup = createQuickPopup(
            title.c_str(),
            warning,
            "No",
            Odyssey::createText("Yes", "Si").c_str(),
            [this](auto, bool btn)
            {
                auto title = Odyssey::createText("Absolutely Sure?", "Muy Seguro?");
                auto warning = Odyssey::createText(
                    "Do you really want to <cr>delete the fangame's data</c>?\nThe <cg>main game's</c> save data will remain untoched.",
                    "En serio quieres <cr>borrar los datos del Fangame</c>?\nLos datos del <cg>juego principal</c> aun quedaran intactos.");

                if (btn)
                {
                    auto popup = createQuickPopup(
                        title.c_str(),
                        warning,
                        Odyssey::createText("Cancel", "Cancelar").c_str(),
                        Odyssey::createText("Confirm", "Confirmar").c_str(),
                        [this](auto, bool btn)
                        {
                            auto title = Odyssey::createText("Last warning", "Ultima advertencia");
                            auto warning = Odyssey::createText(
                                "Please confirm one last time. <cr>Once you delete this save data, it cannot be restored.</c>",
                                "Por favor confirma una ultima vez. <cr>Una vez que se borren los datos, no pueden recuperarse.</c>");

                            if (btn)
                            {
                                auto popup = createQuickPopup(
                                    title.c_str(),
                                    warning,
                                    Odyssey::createText("Nevermind", "Olvidalo").c_str(),
                                    Odyssey::createText("DELETE IT", "YA BORRALO").c_str(),
                                    [this](auto, bool btn)
                                    {
                                        auto title = Odyssey::createText("The choice was made", "La decicion fue tomada");
                                        auto description = Odyssey::createText(
                                            "Your fangame save data <cr>will be deleted when you exit the game</c>, thank you for playing with <cy>Geometry Dash Odyssey</c>!",
                                            "Tus datos guardados del fangame <cr>se borraran cuando salgas del juego</c>, gracias por jugar <cy>Geometry Dash Odyssey</c>!");

                                        if (btn)
                                        {
                                            auto popup = createQuickPopup(
                                                title.c_str(),
                                                description,
                                                ":)",
                                                nullptr,
                                                [](auto, auto) {});

                                            Mod::get()->setSavedValue<bool>("purge-save", true);
                                        }
                                    });
                            }
                        });
                }
            });
    }

    void onCommit() override {}
    void onResetToDefault() override {}

public:
    static DeleteDataNode *create(std::shared_ptr<DeleteDataSetting> setting, float width)
    {
        auto ret = new DeleteDataNode();
        if (ret->init(setting, width))
        {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }

    bool hasUncommittedChanges() const override
    {
        return false;
    }
    bool hasNonDefaultValue() const override
    {
        return false;
    }

    std::shared_ptr<DeleteDataSetting> getSetting() const
    {
        return std::static_pointer_cast<DeleteDataSetting>(SettingNodeV3::getSetting());
    }
};

SettingNodeV3 *DeleteDataSetting::createNode(float width)
{
    return DeleteDataNode::create(
        std::static_pointer_cast<DeleteDataSetting>(shared_from_this()),
        width);
}

$execute
{
    (void)Mod::get()->registerCustomSettingType("delete-data-button", &DeleteDataSetting::parse);
}