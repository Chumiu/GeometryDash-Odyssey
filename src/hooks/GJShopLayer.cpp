#include <Geode/Geode.hpp>
#include <Geode/modify/GJShopLayer.hpp>
#include "../layers/OdysseySelectLayer.hpp"
#include "../ui/PromoPopup.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyShopLayer, GJShopLayer)
{
	bool init(ShopType p0)
	{
		if (!GJShopLayer::init(ShopType{6}))
			return false;

		FMODAudioEngine::sharedEngine()->playMusic("Shop.mp3"_spr, true, 0.1f, 0);

		auto extraMenu = CCMenu::create();
		extraMenu->setID("shop-tv-menu"_spr);
		extraMenu->setPosition({0, 0});
		extraMenu->setZOrder(3);

		auto spriteTV = CCSprite::createWithSpriteFrameName("gj_videoRewardBtn_001.png");
		spriteTV->setScale(0.9f);

		auto buttonTV = CCMenuItemSpriteExtra::create(
			spriteTV,
			this,
			menu_selector(OdysseyShopLayer::onPlayVideo));

		std::string info = GameManager::sharedState()->getGameVariable("0201") ? "Revisa tus <cy>Iconos</c>. A veces los iconos que ya has desbloqueado apareceran aqui como no comprados" : "Be aware to check your <cy>Icon kit</c>, icons you already unlocked might show here as not bought.";
		auto infoButton = InfoAlertButton::create("Warning", info, 1);
		infoButton->setPosition({30, 30});
		extraMenu->addChild(infoButton);

		buttonTV->setID("shop-tv-button"_spr);
		buttonTV->setPosition({280, 222});
		buttonTV->m_scaleMultiplier = 1;
		buttonTV->m_colorEnabled = true;
		buttonTV->m_colorDip = 100;

		extraMenu->addChild(buttonTV);
		this->addChild(extraMenu);

		auto particle = static_cast<CCParticleSystemQuad *>(getChildren()->objectAtIndex(7));
		particle->setStartColor({193, 122, 5, 255});
		particle->setEndColor({255, 122, 0, 0});

		auto winSize = CCDirector::sharedDirector()->getWinSize();
		int rand = (std::rand() % 6) + 1;

		auto wantedPoster = CCSprite::createWithSpriteFrameName(fmt::format("GDO_Wanted0{}_001.png"_spr, rand).c_str());
		wantedPoster->setPosition({(winSize.width / 4) + (std::rand() % 3 * 30), winSize.height / 2 + 70.f});
		wantedPoster->setID("wanted-poster"_spr);
		wantedPoster->setScale(0.8f);
		wantedPoster->setZOrder(-1);
		this->addChild(wantedPoster);

		auto GSM = GameStatsManager::sharedState();

		if (!GameManager::sharedState()->getUGV("204"))
		{
			this->runAction(CCSequence::create(
				CCDelayTime::create(0.5f),
				CCCallFunc::create(this, callfunc_selector(OdysseyShopLayer::getCarpDialog)),
				0));
		};

		return true;
	}

	void onPlayVideo(CCObject *)
	{
		auto promo = PromoPopup::create();
		promo->show();
	}

	void getCarpDialog()
	{
		auto dialog = Odyssey::createDialog("carp-introduction", 2, false);
		GameManager::sharedState()->setUGV("204", true);
		this->addChild(dialog, 200);
	}

	void onBack(CCObject *)
	{
		auto director = CCDirector::sharedDirector();
		auto winSize = director->getWinSize();

		this->retain();
		this->removeFromParentAndCleanup(false);

		auto selectLayer = OdysseySelectLayer::scene(GameManager::sharedState()->getIntGameVariable("1001") - 1);
		director->replaceScene(selectLayer);
		selectLayer->addChild(this, 1000);

		this->release();

		auto moveTo = CCMoveTo::create(0.3f, ccp(0, winSize.height));
		auto easeIn = CCEaseIn::create(moveTo, 2.0f);
		auto callFunc = CCCallFunc::create(this, callfunc_selector(OdysseyShopLayer::removeFromParent));

		auto ccSeq = CCSequence::create(easeIn, callFunc, 0);
		this->runAction(ccSeq);

		setKeyboardEnabled(false);
		setKeypadEnabled(false);
	}
};