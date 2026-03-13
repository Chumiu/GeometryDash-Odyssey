#include <Geode/Geode.hpp>
#include <Geode/modify/OptionsLayer.hpp>
#include <Geode/modify/MoreOptionsLayer.hpp>
#include "../ui/AlertPopup.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(GDO_OptionsLayer, OptionsLayer)
{
	virtual void customSetup()
	{
		OptionsLayer::customSetup();

		if (auto button = this->getChildByIDRecursive("vault-button"))
			button->setVisible(false);
	}

	void onAccount(CCObject *)
	{
		auto info = Odyssey::createText(
			"To avoid risks of accidentally overwriting your data with modified stats, this <cr>feature is disabled</c>. Your actual data will be restored when you disable the mod.",
			"Para evitar riesgos de sobrescribir tus datos con stats modificados por accidente, esta <cr>funcion esta desactivada</c>. Tus datos actuales se restauraran cuando desactives el mod.");

		auto alert = FLAlertLayer::create("Disabled", info, "OK");
		alert->show();
	}
};