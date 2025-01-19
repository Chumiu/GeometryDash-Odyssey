#include <Geode/Geode.hpp>
#include <Geode/modify/OptionsLayer.hpp>
#include <Geode/modify/MoreOptionsLayer.hpp>

#include "../nodes/OdysseyPopup.hpp"

using namespace geode::prelude;

class $modify(GDO_OptionsLayer, OptionsLayer)
{
	virtual void customSetup()
	{
		OptionsLayer::customSetup();

		if (auto button = this->getChildByIDRecursive("vault-button"))
		{
			button->setVisible(false);
		}
	}

	void onAccount(CCObject *)
	{
		auto spanish = GameManager::sharedState()->getGameVariable("0201");
		auto info = spanish ? "Para evitar riesgos de sobrescribir tus datos por accidente, esta <cr>funcion esta desactivada</c>. Tus datos actuales se restauraran cuando desactives el mod." : "To avoid risks of accidentally overwriting your data, this <cr>feature is disabled</c>. Your actual data will be restored when you disable the mod.";

		auto alert = FLAlertLayer::create("Disabled", info, "OK");
		alert->show();
	}
};

class $modify(GDO_MoreOptionsLayer, MoreOptionsLayer)
{
	bool init()
	{
		if (!MoreOptionsLayer::init())
			return false;

		GameManager::sharedState()->setGameVariable("0201", Mod::get()->getSettingValue<bool>("spanish-language"));
		GameManager::sharedState()->setGameVariable("0202", Mod::get()->getSettingValue<bool>("hide-custom"));
		GameManager::sharedState()->setGameVariable("0203", Mod::get()->getSettingValue<bool>("updated-levels"));
		auto spanish = Mod::get()->getSettingValue<bool>("spanish-language");

		//	Aun en fase de prueba
		MoreOptionsLayer::addToggle("Spanish Translation", "0201", spanish ? "Traduce mayor parte del mod en lenguaje hispano. Por limitaciones de caracteres, habran errores ortograficos (Como la falta de acentos)" : "Translates most of the mod in spanish. Due to character limitations, there will be spelling errors");
		MoreOptionsLayer::addToggle("Hide Custom Modes", "0202", spanish ? "Oculta los botones de los gamemodes personalizados en el Icon Kit (porque solo tienen un icono, por ahora...)" : "Hides the icon kit buttons for the custom gamemodes (they only have one design, for now...)");
		MoreOptionsLayer::addToggle("Updated levels", "0203", spanish ? "Sustituye los niveles por una copia de su version online, para experimentar con las nuevas funciones de descargar assets de audio, que se agregaran en <cy>Actualizacion 1.1</c>." : "Replaces the levels with a copy of their online version, to experiment with the new audio asset features that will be added in <cy>Update 1.1</c>.");

		return true;
	}

	void goToPage(int p0)
	{
		MoreOptionsLayer::goToPage(p0);

		if (MoreOptionsLayer::m_page == 7)
			MoreOptionsLayer::m_categoryLabel->setString("GD Odyssey Options");
	}

	void onToggle(CCObject *sender)
	{
		MoreOptionsLayer::onToggle(sender);

		auto tag = sender->getTag();
		log::debug("TAG: {}", tag);

		if (sender->getTag() == 201)
		{
			Mod::get()->setSettingValue<bool>("spanish-language", GameManager::sharedState()->getGameVariable("0201"));

			if (!Mod::get()->setSavedValue("shown-translation-warning", true) && GameManager::sharedState()->getGameVariable("0201"))
			{
				auto popup = OdysseyPopup::create("Language Notice", "Dado a limitaciones de\ncaracteres en el juego, habran\n<cr>errores ortograficos</c>\n(como la falta de acentos)");
				popup->setWarning(false, true);
				popup->setZOrder(104);
				popup->m_scene = this;
				popup->show();
			};
		}

		if (sender->getTag() == 202)
			Mod::get()->setSettingValue<bool>("hide-custom", GameManager::sharedState()->getGameVariable("0202"));

		if (sender->getTag() == 203)
			Mod::get()->setSettingValue<bool>("updated-levels", GameManager::sharedState()->getGameVariable("0203"));
	}
};