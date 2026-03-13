#include <Geode/Geode.hpp>
#include <Geode/modify/GJShopLayer.hpp>
#include <Geode/modify/PurchaseItemPopup.hpp>
#include "../layers/OdysseySelectLayer.hpp"
#include "../ui/ShopPromoPopup.hpp"
#include "../utils/IconUtils.hpp"
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

		std::string info = Odyssey::createText(
			"Be aware to check your <cy>Icon Kit</c>, since the fangame uses custom icons above the vanilla limit, it's prone to issues.",
			"Pendiente en revisar tus <cy>Iconos</c>, como el fangame usa iconos custom arriba del limite de los que hay en Vanilla, esta sujeto a problemas");

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

		auto wantedPoster = CCSprite::createWithSpriteFrameName(fmt::format("ShopDeco_{:02}_001.png"_spr, rand).c_str());
		wantedPoster->setPosition({(winSize.width / 4) + (std::rand() % 3 * 30), winSize.height / 2 + 70.f});
		wantedPoster->setID("shop-decoration"_spr);
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

class $modify(PurchaseItemPopup)
{
	void onPurchase(CCObject *sender)
	{
		PurchaseItemPopup::onPurchase(sender);
		auto item = m_storeItem;

		log::debug("Item Purchased -- Index: {} / Type: {} / ID: {}", item->m_index.value(), item->m_unlockType.value(), item->m_typeID.value());

		//	I know this is terrible, but what else can I do?
		Mod::get()->setSavedValue<int>(fmt::format("store-item-{:02}", item->m_index), item->m_price);
		Mod::get()->setSavedValue<int>("Orbs", Mod::get()->getSavedValue<int>("Orbs") - item->m_price.value());

		//	"Conclusive Journey" key bought.
		if (item->m_unlockType.value() == 12 && item->m_typeID.value() == 1)
			GameManager::sharedState()->setUGV("237", true);

		//	"Burning Sands" key bought.
		if (item->m_unlockType.value() == 12 && item->m_typeID.value() == 2)
			GameManager::sharedState()->setUGV("238", true);

		IconUtils::unlockReward(item->m_typeID.value(), static_cast<UnlockType>(item->m_unlockType.value()));
	}
};