#include "OdysseySelectLayer.hpp"
#include "SecretVaultLayer2.hpp"
#include "../nodes/InstantMenuItemSprite.hpp"
#include "../ui/OdysseyLevelPopup.hpp"
#include "../ui/LanguagePopup.hpp"
#include "../ui/ComicPopup.hpp"
#include "../utils/IconUtils.hpp"
#include "../utils/Utils.hpp"

bool OdysseySelectLayer::init(int page)
{
	if (!CCLayer::init())
		return false;

	m_currentPage = page;
	GameManager::sharedState()->setIntGameVariable("1001", page + 1);
	m_winSize = CCDirector::sharedDirector()->getWinSize();

	//  Game Manager
	auto GM = GameManager::sharedState();
	auto GSM = GameStatsManager::sharedState();

	// canción
	auto pageID = (page + 1 < 4) ? page + 1 : 4;
	std::string song = (page == 3) ? "SecretLoop02.mp3"_spr : fmt::format("IslandLoop{:02}.mp3"_spr, pageID);

	// fondo
	int bgID = 1;
	ccColor3B bgColor = {26, 12, 43};

	// islas
	const char *islandTexture = "MainIsland_01_001.png"_spr;
	CCPoint islandPosition = {m_winSize.width / 2, m_winSize.height / 2 - 20};
	ccColor3B islandColor = {255, 255, 255};
	float islandScale = 1.8f;
	int islandOpacity = 255;
	ccColor4B gradientColorTop = {0, 0, 0, 0};
	ccColor4B gradientColorBottom = {0, 0, 0, 0};

	switch (page)
	{
	case 0:
		bgID = 52;
		bgColor = {32, 39, 46};
		m_levelAmount = 4;
		break;

	case 1:
		bgID = 32;
		bgColor = {31, 0, 63};
		islandTexture = "MainIsland_02_001.png"_spr;
		// islandColor = {5, 5, 5};
		islandScale = 1.333f;
		m_levelAmount = 5;
		gradientColorBottom = {41, 19, 21, 74};
		break;

	case 2:
		bgID = 15;
		bgColor = {53, 7, 0};
		islandTexture = "BonusIsland_01_001.png"_spr;
		islandPosition = CCPoint{m_winSize.width / 2 - 100, islandPosition.y};
		islandScale = 1.333f;
		break;

	case 3:
		bgID = 57;
		bgColor = {0, 30, 0};
		gradientColorTop = {0, 60, 0, 30};
		islandTexture = "BonusIsland_01_001.png"_spr;
		islandPosition = CCPoint{m_winSize.width / 2 - 100, islandPosition.y};
		islandScale = .75f;
		break;

	default:
		islandColor = {0, 0, 0};
		break;
	}

	FMODAudioEngine::sharedEngine()->playMusic(song, true, .25f, 0);

	m_background = CCSprite::create(GameManager::sharedState()->getBGTexture(bgID));
	m_background->setColor(bgColor);
	m_background->setAnchorPoint({0, 0});
	m_background->setPositionY(-100);
	m_background->setScale(m_winSize.width / m_background->getContentWidth());
	addChild(m_background, -2);

#ifdef GEODE_IS_WINDOWS
	auto gradient = CCLayerGradient::create(gradientColorTop, gradientColorBottom);
	gradient->setBlendFunc({GL_ADD, GL_ADD});
	addChild(gradient, -1);
#endif

	auto backMenu = CCMenu::create();
	backMenu->setPosition(24, m_winSize.height - 24);

	auto backSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
	auto backButton = CCMenuItemSpriteExtra::create(backSpr, this, menu_selector(OdysseySelectLayer::onBack));

	backMenu->addChild(backButton);
	addChild(backMenu);

	auto buttonMenu = CCMenu::create();
	buttonMenu->setPosition({0, 0});
	buttonMenu->setZOrder(5);

	auto ropeSprite = CCSprite::createWithSpriteFrameName("garageRope_001.png");
	ropeSprite->setScale(1.f);

	auto ropeBtn = CCMenuItemSpriteExtra::create(ropeSprite, this, menu_selector(OdysseySelectLayer::onRope));
	ropeBtn->m_animationType = MenuAnimationType::Move;

	ropeBtn->m_startPosition = ropeSprite->getPosition();
	ropeBtn->m_offset = CCPoint(0, -10);

	ropeBtn->setPosition({m_winSize.width - 60, m_winSize.height - 25});
	buttonMenu->addChild(ropeBtn);
	addChild(buttonMenu);

	//  Bottom Left Menu
	auto bottomLeftMenu = CCMenu::create();
	bottomLeftMenu->setContentSize({40, 120});
	bottomLeftMenu->setLayout(ColumnLayout::create()
								  ->setGap(2.0f)
								  ->setAutoScale(false)
								  ->setAutoGrowAxis(true)
								  ->setGrowCrossAxis(false)
								  ->setCrossAxisOverflow(false)
								  ->setAxisAlignment(AxisAlignment::Start));
	bottomLeftMenu->setAnchorPoint({0.5, 0});
	bottomLeftMenu->setID("bottom-left-menu");
	bottomLeftMenu->setZOrder(5);

	//  Bottom Right Menu
	auto bottomRightMenu = CCMenu::create();
	bottomRightMenu->setContentSize({40, 120});
	bottomRightMenu->setLayout(ColumnLayout::create()
								   ->setGap(2.0f)
								   ->setAutoScale(false)
								   ->setAutoGrowAxis(true)
								   ->setGrowCrossAxis(false)
								   ->setCrossAxisOverflow(false)
								   ->setAxisAlignment(AxisAlignment::Start));
	bottomRightMenu->setAnchorPoint({0.5, 0});
	bottomRightMenu->setID("bottom-right-menu");
	bottomRightMenu->setZOrder(5);

	addChildAtPosition(bottomLeftMenu, Anchor::BottomLeft, ccp(30, 10), false);
	addChildAtPosition(bottomRightMenu, Anchor::BottomRight, ccp(-30, 10), false);

	//  Music Button
	auto musicSpr = CircleButtonSprite::createWithSpriteFrameName("GJ_musicIcon_001.png", 0.9f, CircleBaseColor::Green, CircleBaseSize::Small);
	auto musicBtn = CCMenuItemSpriteExtra::create(
		musicSpr,
		this,
		menu_selector(OdysseySelectLayer::onSongs));

	//  Settings Button
	auto settingsSpr = CircleButtonSprite::createWithSpriteFrameName("SettingsIcon_001.png"_spr, 1.1f, CircleBaseColor::Green, CircleBaseSize::Small);
	auto settingsBtn = CCMenuItemSpriteExtra::create(
		settingsSpr,
		this,
		menu_selector(OdysseySelectLayer::onSettings));

	//  Settings Button
	auto languageSpr = CircleButtonSprite::createWithSpriteFrameName("LanguageIcon_001.png"_spr, 1.f, CircleBaseColor::Green, CircleBaseSize::Small);
	auto languageBtn = CCMenuItemSpriteExtra::create(
		languageSpr,
		this,
		menu_selector(OdysseySelectLayer::onLanguage));

	//  Comics Button
	auto comicsSpr = CircleButtonSprite::createWithSpriteFrameName("ComicsIcon_001.png"_spr, 1, CircleBaseColor::Green, CircleBaseSize::Small);
	auto comicsBtn = CCMenuItemSpriteExtra::create(
		comicsSpr,
		this,
		menu_selector(OdysseySelectLayer::onComics));

	bottomLeftMenu->addChild(settingsBtn);
	bottomLeftMenu->addChild(languageBtn);
	bottomLeftMenu->updateLayout();

	bottomRightMenu->addChild(musicBtn);
	bottomRightMenu->addChild(comicsBtn);
	bottomRightMenu->updateLayout();

	//  Island Node
	m_islandNode = CCNode::create();
	m_islandNode->setContentSize(m_winSize);

	if (page == 2)
	{
		auto extra01_unlocked = GSM->isItemUnlocked(UnlockType::GJItem, 1) || GM->getUGV("237");
		auto extra02_unlocked = GSM->isItemUnlocked(UnlockType::GJItem, 2) || GM->getUGV("238");

		auto menu = CCMenu::create();
		menu->setPosition({0, 0});

		auto firstSprite = CCSprite::createWithSpriteFrameName(islandTexture);
		firstSprite->setScale(islandScale);

		auto firstIsland = CCMenuItemSpriteExtra::create(
			firstSprite,
			this,
			menu_selector(OdysseySelectLayer::onExtraLevel));

		firstIsland->setColor(islandColor);
		firstIsland->setPosition(islandPosition);
		firstIsland->m_scaleMultiplier = 1.1f;
		firstIsland->setTag(501);

		auto secondSprite = CCSprite::createWithSpriteFrameName("BonusIsland_02_001.png"_spr);
		secondSprite->setScale(islandScale);

		auto secondIsland = CCMenuItemSpriteExtra::create(
			secondSprite,
			this,
			menu_selector(OdysseySelectLayer::onExtraLevel));

		secondIsland->setPosition({m_winSize.width / 2 + 100, m_winSize.height / 2});
		secondIsland->m_scaleMultiplier = 1.1f;
		secondIsland->setTag(502);

		if (!extra01_unlocked)
		{
			auto lock = CCSprite::createWithSpriteFrameName("GJLargeLock_001.png");
			firstSprite->setColor({25, 25, 25});
			firstIsland->addChild(lock, 10);

			lock->setPosition(firstIsland->getContentSize() / 2);
		}

		if (!extra02_unlocked)
		{
			auto lock = CCSprite::createWithSpriteFrameName("GJLargeLock_001.png");
			secondSprite->setColor({25, 25, 25});
			secondIsland->addChild(lock, 10);

			lock->setPosition(secondIsland->getContentSize() / 2);
		}

		menu->addChild(firstIsland);
		menu->addChild(secondIsland);

		//  CONTEST ISLANDS
		m_islandNode->addChild(menu);
	}

	if (page == 3)
	{
		auto menu = CCMenu::create();
		menu->setPosition({0, 0});

		std::vector<CCPoint> m_islandPositions = {
			{-207, 0},
			{-103, -30},
			{0, 30},
			{103, 0},
			{207, -30}};

		for (int i = 0; i < 5; i++)
		{
			auto pos = m_islandPositions[i];

			auto smallIsland = CCSprite::createWithSpriteFrameName(fmt::format("OgrePathIsland_{:02}_001.png"_spr, i + 1).c_str());
			smallIsland->setScale(1.333f);

			auto smallIslandBtn = CCMenuItemSpriteExtra::create(
				smallIsland,
				this,
				menu_selector(OdysseySelectLayer::onExtraLevel));

			smallIslandBtn->setPosition({m_winSize.width / 2 + pos.x, m_winSize.height / 2 + +pos.y});
			smallIslandBtn->m_scaleMultiplier = 1.1f;
			smallIslandBtn->setTag(601 + i);
			menu->addChild(smallIslandBtn);
		}

		auto comingSoonLabel = CCLabelBMFont::create("Work in progress, subject to changes", "bigFont.fnt");
		comingSoonLabel->setPosition({m_winSize.width / 2, 20});
		comingSoonLabel->setOpacity(120);
		comingSoonLabel->setScale(.4f);
		//	addChild(comingSoonLabel, 999);
	}

	m_islandTexture = CCSprite::createWithSpriteFrameName(islandTexture);
	m_islandTexture->setOpacity(islandOpacity);
	m_islandTexture->setScale(islandScale);
	m_islandTexture->setColor(islandColor);

	m_islandTexture->setAnchorPoint({.5f, .5f});
	m_islandTexture->setPosition(islandPosition);

	if (page == 2)
		m_islandTexture->setVisible(false);

	if (page == 3)
		m_islandTexture->setVisible(false);

	m_islandNode->addChild(m_islandTexture);
	addChild(m_islandNode);

	//  Agrega los botones de niveles
	addLevelButtons();

	//  Agrega los puntos del camino de la isla
	addIslandDots();

	//  Animacion de flotando para la Isla
	auto moveUp = CCEaseInOut::create(CCMoveTo::create(2.0f, {0, 5}), 1.8f);
	auto moveDown = CCEaseInOut::create(CCMoveTo::create(2.0f, {0, 0}), 1.8f);
	m_islandNode->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(moveUp, moveDown)));

	//  Titulo de la Isla
	auto islandTitle = CCSprite::createWithSpriteFrameName(fmt::format("IslandTitle_{:02}_001.png"_spr, pageID).c_str());
	islandTitle->setScale(.75f);
	islandTitle->setPosition({m_winSize.width / 2, m_winSize.height - 30});
	addChild(islandTitle);

	auto switchMenu = CCMenu::create();

	if (page > 0 && page < 3)
	{
		auto navSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
		navSprite->setFlipX(true);

		auto leftButton = CCMenuItemSpriteExtra::create(navSprite, this, menu_selector(OdysseySelectLayer::onBackPage));
		leftButton->setPositionX(-m_winSize.width / 2 + 25);
		switchMenu->addChild(leftButton);
	}

	if (page < 2)
	{
		auto navSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");

		auto rightButton = CCMenuItemSpriteExtra::create(navSprite, this, menu_selector(OdysseySelectLayer::onNextPage));
		rightButton->setPositionX(m_winSize.width / 2 - 25);
		switchMenu->addChild(rightButton);
	}

	addChild(switchMenu);

	auto m_cornerBL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
	m_cornerBL->setPosition({-1, -1});
	m_cornerBL->setAnchorPoint({0, 0});
	m_cornerBL->setID("corner-bl"_spr);
	addChild(m_cornerBL, 2);

	auto m_cornerBR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
	m_cornerBR->setPosition({m_winSize.width + 1, -1});
	m_cornerBR->setAnchorPoint({1, 0});
	m_cornerBR->setFlipX(true);
	m_cornerBR->setID("corner-br"_spr);
	addChild(m_cornerBR, 2);

	//  Se reemplazara esto con el Game Manager, pero lo tengo para Desarrollo

	//  Evento 1: Entrar por primera vez al Mapa
	if (!GM->getUGV("203"))
	{
		this->runAction(CCSequence::create(
			CCDelayTime::create(0.5f),
			CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::getWizardDialog01)),
			0));
	};

	//  Evento 2: Completar The Dangerous Zones
	if (GM->getUGV("203") && !GM->getUGV("207") && GM->getUGV("216"))
	{
		this->runAction(CCSequence::create(
			CCDelayTime::create(0.5f),
			CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::getWizardDialog02)),
			0));
	}

	//  Evento 3: Completar Elemental Odyssey
	if (GM->getUGV("207") && !GM->getUGV("208") && GM->getUGV("222"))
	{
		this->runAction(CCSequence::create(
			CCDelayTime::create(0.5f),
			CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::getWizardDialog03)),
			0));
	}

	//  Evento 4: Inicio de la aventura Ogre
	if (GM->getUGV("208") && !GM->getUGV("280"))
	{
		m_ogreWillTalk = true;

		this->runAction(CCSequence::create(
			CCDelayTime::create(0.5f),
			CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::getOgreDialog)),
			0));
	}

	if (GM->getUGV("287") && !GM->getUGV("289"))
	{
		this->runAction(CCSequence::create(
			CCDelayTime::create(0.5f),
			CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::getFullCompletion)),
			0));
	}

	animateLevelCompletation();
	setKeyboardEnabled(true);
	setKeypadEnabled(true);
	return true;
};

void OdysseySelectLayer::getOgreDialog()
{
	if (!m_ogreWillTalk)
		return;

	std::vector<gd::string> dialogEvents = {
		"ogre-quest-intro",
		"ogre-quest-start", // Just to skip
		"ogre-first-clear",
		"ogre-second-clear",
		"ogre-third-clear",
		"ogre-fourth-clear",
		"ogre-quest-ending",
	};

	m_ogreWillTalk = false;
	auto dialog = Odyssey::createDialog(dialogEvents[m_ogreDialog].c_str(), 3);
	GameManager::sharedState()->setUGV(fmt::format("{}", m_ogreDialog + 280).c_str(), true);
	this->addChild(dialog, 10);
};

void OdysseySelectLayer::unlockOgreChest()
{
	CCArray *rewardsArray = CCArray::create();

	rewardsArray->addObject(GJRewardObject::createItemUnlock(UnlockType::Cube, 520));
	rewardsArray->addObject(GJRewardObject::createItemUnlock(UnlockType::GJItem, 4));
	rewardsArray->addObject(GJRewardObject::create(SpecialRewardItem::Orbs, 2500, 14));

	GJRewardItem *rewardItems = GJRewardItem::createWithObjects(GJRewardType::Key100Treasure, rewardsArray);
	RewardUnlockLayer *layer = RewardUnlockLayer::create(7, nullptr);
	layer->m_chestType = 8;

	GameStatsManager::get()->incrementStat("14", 2500);
	IconUtils::unlockReward(520, UnlockType::Cube);

	cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer);
	layer->showCollectReward(rewardItems);
	layer->setZOrder(500);

	//  Has collected Betsy
	GameManager::sharedState()->setUGV("286", true);
};

void OdysseySelectLayer::getWizardDialog01()
{
	auto dialog = Odyssey::createDialog("wizard-introduction", 4);
	GameManager::sharedState()->setUGV("203", true);
	this->addChild(dialog, 10);
};

void OdysseySelectLayer::getWizardDialog02()
{
	auto dialog = Odyssey::createDialog("first-island-clear", 4);
	GameManager::sharedState()->setUGV("207", true);
	this->addChild(dialog, 10);
};

void OdysseySelectLayer::getWizardDialog03()
{
	auto dialog = Odyssey::createDialog("main-ending", 4);
	GameManager::sharedState()->setUGV("208", true);
	this->addChild(dialog, 10);
};

void OdysseySelectLayer::getFullCompletion()
{
	auto GSM = GameStatsManager::sharedState();
	auto GM = GameManager::sharedState();

	auto allCoins = GSM->getStat("08") == 48;
	auto ogreUnlocked = GM->getUGV("288");
	auto hollowUnlocked = GM->getUGV("210");

	std::vector<std::pair<int, int>> IconRanges = {
		{486, 520},
		{170, 179},
		{119, 130},
		{150, 159},
		{97, 102},
		{44, 48},
		{9, 9},
	};

	std::vector<int> IconTypes = {
		0,
		1,
		2,
		3,
		4,
		7,
		8,
	};

	auto allIcons = true;
	for (auto ii = 0; ii < IconTypes.size(); ii++)
	{
		auto type = IconType(IconTypes[ii]);
		for (auto jj = IconRanges[ii].first; jj <= IconRanges[ii].second; jj++)
		{
			if (!GM->isIconUnlocked(jj, type))
				allIcons = false;
		}
	}

	if (!hollowUnlocked)
	{
		auto text = Odyssey::createText(
			"You feel like something's missing...",
			"Sientes que te falta algo...");

		auto text2 = Odyssey::createText(
			"Maybe there's another vault somewhere...",
			"Tal vez halla otro Vault por aqui...");

		if (m_notify)
		{
			Notification::create(text, NotificationIcon::Info, 2.f)->show();
			Notification::create(text2, NotificationIcon::Info, 2.f)->show();
		}
	}
	else if (!allCoins)
	{
		auto text = Odyssey::createText(
			"You feel like something's missing...",
			"Sientes que te falta algo...");

		auto text2 = Odyssey::createText(
			"Did you get all the Secret Coins?",
			"Haz coleccionado todas las monedas?");

		if (m_notify)
		{
			Notification::create(text, NotificationIcon::Info, 2.f)->show();
			Notification::create(text2, NotificationIcon::Info, 2.f)->show();
		}
	}
	else if (!allIcons)
	{
		auto text = Odyssey::createText(
			"You feel like something's missing...",
			"Sientes que te falta algo...");

		auto text2 = Odyssey::createText(
			"Did you get all the Icons?",
			"Haz coleccionado todos los Iconos?");

		if (m_notify)
		{
			Notification::create(text, NotificationIcon::Info, 2.f)->show();
			Notification::create(text2, NotificationIcon::Info, 2.f)->show();
		}
	}
	else
	{
		auto dialog = Odyssey::createDialog("full-completion", 4);
		GameManager::sharedState()->setUGV("289", true);
		this->addChild(dialog, 10);
	}
};

void OdysseySelectLayer::keyBackClicked()
{
	// volver al ogro si está en la pagina de los niveles contest
	if (m_currentPage == 3)
	{
		auto scene = CCScene::create();
		scene->addChild(SecretVaultLayer2::create());
		CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
		return;
	}

	GameManager::sharedState()->setIntGameVariable("1001", 0);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MenuLayer::scene(false)));
	GameManager::sharedState()->fadeInMenuMusic();
};

void OdysseySelectLayer::onBack(CCObject *)
{
	keyBackClicked();
};

std::vector<CCPoint> OdysseySelectLayer::getPositionForButtons()
{
	std::vector<CCPoint> arr;

	switch (m_currentPage)
	{
	case 0:
		return {
			{-70, 60},
			{130, 70},
			{40, 10},
			{-80, -55}};

	case 1:
		return {
			{-170, 35},
			{-57, 27},
			{30, 63},
			{141, -14},
			{150, 82}};

	case 3:
		return {
			{-180, -68},
			{-90, 38},
			{0, -68},
			{90, 38},
			{180, -68}};
	}

	return arr;
}

std::vector<CCPoint> OdysseySelectLayer::getPositionForDots()
{
	std::vector<CCPoint> arr;

	switch (m_currentPage)
	{
	case 0:
		return {
			{-47, 55},
			{-32, 57},
			{-17, 55},
			{-4, 59},
			{9, 58},
			{22, 64},
			{38, 63},
			{50, 66},
			{67, 64},
			{81, 67},
			{96, 66},
			{111, 69},
			// camino 2
			{146, 58},
			{149, 50},
			{159, 43},
			{167, 35},
			{163, 22},
			{168, 12},
			{163, 2},
			{152, -4},
			{139, -2},
			{126, -7},
			{112, -3},
			{102, -10},
			{89, -14},
			{79, -21},
			{68, -22},
			{55, -24},
			{47, -16},
			{47, -8},
			// camino 3
			{27, -6},
			{17, -15},
			{4, -14},
			{-7, -25},
			{-22, -25},
			{-30, -37},
			{-47, -38},
			{-53, -52}};
		break;
	case 1:
		return {
			{-152, 29},
			{-135, 8},
			{-91, -36},
			{-78, -33},
			{-66, -26},
			{-71, -14},
			{-82, -4},
			{-92, 9},
			{-85, 23},
			{-71, 26},
			// camino 2
			{-41, 23},
			{-26, 15},
			{-18, 5},
			{-7, -9},
			{8, -25},
			{27, -20},
			{30, -7},
			{25, 11},
			{29, 25},
			{26, 39},
			{32, 47},
			// camino 3
			{39, -27},
			{52, -42},
			{68, -52},
			{86, -58},
			{98, -53},
			{120, -35},
			{129, -29},
			// camino 4
			{152, -5},
			{147, 8},
			{140, 18},
			{134, 28},
			{135, 41},
			{145, 52},
			{154, 61},
			{161, 68}};
		break;
	case 3:
		return {
			// camino 1
			{-141, -80}, // -141 -80  | 282  178
			{-131, -71},
			{-126, -56},
			{-130, -41},
			{-136, -26},
			{-140, -11},
			{-142, 3},
			{-126, 14},
			// camino 2
			{-50, 14},
			{-39, 3},
			{-35, -11},
			{-40, -26},
			{-45, -41},
			{-50, -56},
			{-46, -71},
			{-35, -80},
			// camino 3
			{39, -80},
			{50, -71},
			{54, -56},
			{50, -41},
			{54, -26},
			{40, -11},
			{44, 3},
			{54, 14},
			// camino 4
			{130, 14},
			{141, 3},
			{145, -11},
			{140, 152},
			{135, 137},
			{130, 122},
			{134, 107},
			{145, -80},
		};
	}
	return arr;
}

//  Agrega los botones de niveles
void OdysseySelectLayer::addLevelButtons()
{
	m_levelMenu = CCMenu::create();
	m_levelMenu->setPosition(m_winSize / 2);
	auto offSet = 0;

	if (m_currentPage == 1)
		offSet = 4;

	//  Agrega los niveles con un ciclo
	if (m_levelAmount > 0 && m_currentPage != 3)
	{
		for (int ii = 0; ii < m_levelAmount; ii++)
		{
			auto levelSprite = CCSprite::createWithSpriteFrameName("LevelBtn_01_Locked_001.png"_spr);

			if (m_currentPage == 1 && ii == 4)
				levelSprite = CCSpriteGrayscale::createWithSpriteFrameName("LevelBtn_02_001.png"_spr);

			auto levelButton = CCMenuItemSpriteExtra::create(levelSprite, this, menu_selector(OdysseySelectLayer::onLevel));

			log::info("{}\n", offSet + ii + 1);

			levelButton->setID(fmt::format("Level {}"_spr, offSet + ii + 1));
			levelButton->setTag(offSet + ii + 1);

			levelButton->setPosition(getPositionForButtons()[ii]);
			m_levelMenu->addChild(levelButton);
		}
	}

	if (m_currentPage == 0)
	{
		auto shopSprite = CCSprite::createWithSpriteFrameName("ShopButton_001.png"_spr);
		shopSprite->setScale(0.9f);

		m_shopButton = CCMenuItemSpriteExtra::create(shopSprite, this, menu_selector(OdysseySelectLayer::onShop));
		m_shopButton->m_scaleMultiplier = 1;
		m_shopButton->m_colorEnabled = true;
		m_shopButton->m_colorDip = 100;

		m_shopButton->setPosition({25, 85});

		m_levelMenu->addChild(m_shopButton);

		m_shopButton->setVisible(isLevelComplete(1));
	}

	if (m_currentPage == 1)
	{
		auto volcanoLight = CCSprite::createWithSpriteFrameName("MainIsland_LightOff_001.png"_spr);
		if (isLevelComplete(8))
			CCSprite::createWithSpriteFrameName("MainIsland_LightOn_001.png"_spr);

		volcanoLight->setID("volcano-light-sprite"_spr);

		// 284 - 432 160 - 254

		volcanoLight->setPosition({m_winSize.width / 2 + 148, m_winSize.height / 2 + 94});
		volcanoLight->setZOrder(-1);
		m_islandNode->addChild(volcanoLight);

		//  Button for the Ogre
		auto ogreSprite = CCSprite::createWithSpriteFrameName("OgreCaveBtn_001.png"_spr);
		auto ogreButton = CCMenuItemSpriteExtra::create(
			ogreSprite,
			this,
			menu_selector(OdysseySelectLayer::onOgre));
		ogreButton->m_scaleMultiplier = 1;
		ogreButton->m_colorEnabled = true;
		ogreButton->m_colorDip = 100;
		ogreSprite->setScale(0.7f);

		auto secretMenu = CCMenu::create();
		secretMenu->setZOrder(10);
		secretMenu->setContentSize(ogreButton->getContentSize());
		secretMenu->addChildAtPosition(ogreButton, Anchor::Center, ccp(-255, -71), false);

		m_islandNode->addChildAtPosition(secretMenu, Anchor::Center, ccp(0, 0), false);
	}
	if (m_currentPage == 3)
	{
		for (int i = 0; i < 5; i++)
		{
			std::string extraIslandTexture = fmt::format("OgrePathIsland_{:02}_001.png"_spr, i + 1).c_str();

			auto smallIsland = isLevelComplete(i + 600) ? CCSprite::createWithSpriteFrameName(extraIslandTexture.c_str()) : CCSpriteGrayscale::createWithSpriteFrameName(extraIslandTexture.c_str());
			smallIsland->setScale(1.333f);

			auto smallIslandBtn = CCMenuItemSpriteExtra::create(
				smallIsland,
				this,
				menu_selector(OdysseySelectLayer::onExtraLevel));

			smallIslandBtn->setPosition(getPositionForButtons()[i]);
			smallIslandBtn->m_scaleMultiplier = 1.1f;
			smallIslandBtn->setTag(601 + i);
			m_levelMenu->addChild(smallIslandBtn);
		}
	}

	m_islandNode->addChild(m_levelMenu);
};

void OdysseySelectLayer::addIslandDots()
{
	m_dotNode = CCNode::create();
	m_dotNode->setPosition(m_winSize / 2);

	// agrega los puntos de camino entre niveles

	for (int ii = 0; ii < getPositionForDots().size(); ii++)
	{
		auto dot = CCSprite::createWithSpriteFrameName("LevelPathDot_001.png"_spr);

		dot->setPosition(getPositionForDots()[ii]);

		m_dotNode->addChild(dot);
	}

	m_islandNode->addChild(m_dotNode);
}

bool OdysseySelectLayer::isLevelComplete(int level)
{
	if (level < 1 || level == 600)
		return true;

	return GameManager::sharedState()->getUGV(fmt::format("{}", level + 240).c_str());
}

void OdysseySelectLayer::setLevelComplete(int level)
{
	GameManager::sharedState()->setUGV(fmt::format("{}", level + 240).c_str(), true);
}

void OdysseySelectLayer::enableLevelAnimation(CCObject *p0)
{
	auto btn = static_cast<CCMenuItemSpriteExtra *>(p0);

	btn->setNormalImage(CCSprite::createWithSpriteFrameName("LevelBtn_01_001.png"_spr));

	if (btn->getTag() == 9)
		btn->setNormalImage(CCSprite::createWithSpriteFrameName("LevelBtn_02_001.png"_spr));

	if (btn->getTag() > 600)
	{
		auto islandTexture = CCSprite::createWithSpriteFrameName(fmt::format("OgrePathIsland_{:02}_001.png"_spr, btn->getTag() - 600).c_str());
		islandTexture->setScale(1.333f);

		btn->setNormalImage(islandTexture);
		btn->setContentSize(islandTexture->getScaledContentSize());
	}

	btn->setScale(1.2f);
	btn->runAction(CCSequence::createWithTwoActions(
		CCFadeIn::create(.1f),
		CCEaseBounceOut::create(CCEaseBounceOut::create(CCScaleTo::create(0.5, 1)))));

	if (btn->getTag() > 600)
		return;

	auto particle = CCParticleSystemQuad::create("coinPickupEffect.plist", true);
	particle->setAnchorPoint({0.5f, 0.5f});
	particle->setScale(0.5f);
	particle->setZOrder(3);

	auto circlewave = CCCircleWave::create(16.0, 30, 0.3, 0, 1);
	circlewave->setAnchorPoint({0.5f, 0.5f});
	circlewave->setScale(0.5f);
	circlewave->setZOrder(3);

	auto circlewave2 = CCCircleWave::create(16, 80, 0.3, 1, 1);
	circlewave2->setAnchorPoint({0.5f, 0.5f});
	circlewave2->setScale(0.5f);
	circlewave->setZOrder(3);

	particle->init();

	particle->addChild(circlewave, 2);
	particle->addChild(circlewave2, 2);

	particle->setPosition(btn->getPosition());
	btn->getParent()->addChild(particle);

	if (btn->getTag() == 9)
	{
		auto volcanoLight = static_cast<CCSprite *>(btn->getParent()->getParent()->getChildByID("volcano-light-sprite"_spr));

		if (volcanoLight)
			volcanoLight->setDisplayFrame(CCSprite::createWithSpriteFrameName("MainIsland_LightOn_001.png"_spr)->displayFrame());
	}
}

void OdysseySelectLayer::animateShopUnlock()
{
	m_shopButton->setScale(1.2f);
	m_shopButton->runAction(CCSequence::createWithTwoActions(
		CCFadeIn::create(.1f),
		CCEaseBounceOut::create(CCEaseBounceOut::create(CCScaleTo::create(0.5, 1)))));

	m_shopButton->setVisible(isLevelComplete(1));
}

void OdysseySelectLayer::animateLevelCompletation()
{
	if (m_currentPage == 2)
		return;

	auto GM = GameManager::sharedState();
	auto GLM = GameLevelManager::sharedState();
	auto level1 = GLM->getMainLevel(7001, false);
	auto level2 = GLM->getMainLevel(7002, false);
	auto level3 = GLM->getMainLevel(7003, false);
	auto level4 = GLM->getMainLevel(7004, false);
	auto level5 = GLM->getMainLevel(7005, false);
	auto level6 = GLM->getMainLevel(7006, false);
	auto level7 = GLM->getMainLevel(7007, false);
	auto level8 = GLM->getMainLevel(7008, false);
	auto level9 = GLM->getMainLevel(7009, false);

	auto extraLevel1 = GLM->getMainLevel(7601, false);
	auto extraLevel2 = GLM->getMainLevel(7602, false);
	auto extraLevel3 = GLM->getMainLevel(7603, false);
	auto extraLevel4 = GLM->getMainLevel(7604, false);
	auto extraLevel5 = GLM->getMainLevel(7605, false);

	auto buttonSprite = CCSprite::createWithSpriteFrameName("LevelBtn_01_001.png"_spr);
	int offset = 0;

	if (m_currentPage == 1)
		offset = 4;

	if (m_currentPage == 3)
		offset = 600;

	for (int i = 0; i < m_levelMenu->getChildrenCount(); i++)
	{
		// log::info("{}, {}, {}", i, i + offset, i + offset - 1);
		auto levelButton = static_cast<CCMenuItemSpriteExtra *>(m_levelMenu->getChildByTag(i + offset + 1));

		if (m_currentPage == 1 && i == 4)
			buttonSprite = CCSprite::createWithSpriteFrameName("LevelBtn_02_001.png"_spr);

		if (m_currentPage == 3)
		{
			buttonSprite = CCSprite::createWithSpriteFrameName(fmt::format("OgrePathIsland_{:02}_001.png"_spr, i + 1).c_str());
			buttonSprite->setScale(1.333f);
		}

		// log::info("{}", i + offset + 240);
		if (levelButton)
		{
			if (GameManager::sharedState()->getUGV(fmt::format("{}", i + offset + 240).c_str()) || (i == 0 && m_currentPage == 0))
			{
				levelButton->setNormalImage(buttonSprite);
				levelButton->setContentSize(buttonSprite->getScaledContentSize());
			}
		}
	}

	int firstDot = 0;
	int lastDot = 0;
	int nextLevel = 1;
	bool shouldAnimate = false;

	auto scaleAction = CCScaleTo::create(0.5, 1, 0.5); // Escala al 60% durante 0.5 segundos
	auto scaleWithBounce = CCEaseBounceOut::create(scaleAction);

	if (m_currentPage == 0)
	{
		if (level1->m_normalPercent == 100 && level2->m_normalPercent < 100)
		{
			firstDot = 0;
			lastDot = 11;
			nextLevel = 2;
		}

		if (level2->m_normalPercent == 100 && level3->m_normalPercent < 100)
		{
			firstDot = 12;
			lastDot = 29;
			nextLevel = 3;
		}

		if (level3->m_normalPercent == 100)
		{
			firstDot = 30;
			lastDot = 37;
			nextLevel = 4;
		}
	}

	if (level4->m_normalPercent == 100)
		nextLevel = 5;

	if (m_currentPage == 1)
	{

		if (level5->m_normalPercent == 100 && level6->m_normalPercent < 100)
		{
			firstDot = 0;
			lastDot = 9;
			nextLevel = 6;
		}

		if (level6->m_normalPercent == 100 && level7->m_normalPercent < 100)
		{
			firstDot = 10;
			lastDot = 20;
			nextLevel = 7;
		}

		if (level7->m_normalPercent == 100 && level8->m_normalPercent < 100)
		{
			firstDot = 21;
			lastDot = 27;
			nextLevel = 8;
		}

		if (level8->m_normalPercent == 100)
		{
			firstDot = 28;
			lastDot = 35;
			nextLevel = 9;
		}
	}

	if (m_currentPage == 3)
	{
		if (extraLevel1->m_normalPercent == 100 && extraLevel2->m_normalPercent < 100)
		{
			firstDot = 0;
			lastDot = 7;
			nextLevel = 602;

			if (!GM->getUGV("282"))
			{
				m_ogreDialog = 2;
				m_ogreWillTalk = true;
			}
		}

		if (extraLevel2->m_normalPercent == 100 && extraLevel3->m_normalPercent < 100)
		{
			firstDot = 8;
			lastDot = 15;
			nextLevel = 603;

			if (!GM->getUGV("283"))
			{
				m_ogreDialog = 3;
				m_ogreWillTalk = true;
			}
		}

		if (extraLevel3->m_normalPercent == 100 && extraLevel4->m_normalPercent < 100)
		{
			firstDot = 16;
			lastDot = 23;
			nextLevel = 604;

			if (!GM->getUGV("284"))
			{
				m_ogreDialog = 4;
				m_ogreWillTalk = true;
			}
		}

		if (extraLevel4->m_normalPercent == 100)
		{
			firstDot = 24;
			lastDot = 31;
			nextLevel = 605;

			if (!GM->getUGV("285"))
			{
				m_ogreDialog = 5;
				m_ogreWillTalk = true;
			}
		}

		if (extraLevel5->m_normalPercent == 100)
		{
			if (!GM->getUGV("286"))
			{
				this->runAction(CCSequence::create(
					CCDelayTime::create(2.f),
					CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::unlockOgreChest)),
					0));
			}
		}
	}

	//log::info("Next level: {}", nextLevel);

	if (!isLevelComplete(nextLevel - 1))
	{
		setLevelComplete(nextLevel - 1);

		if (nextLevel != 5)
			shouldAnimate = true;
	}

	//log::info("Page: {}", m_currentPage);

	for (int ii = 0; ii < m_dotNode->getChildrenCount(); ii++)
	{
		auto children = static_cast<CCSprite *>(m_dotNode->getChildren()->objectAtIndex(ii));
		GLubyte opacity = 255;
		float scale = 1.f;

		float delayTime = 0.2 * (ii - firstDot + 1);

		if (ii >= firstDot)
		{
			if (shouldAnimate || ii > lastDot)
			{
				opacity = 0;
				scale = 1.2f;
			}

			if (shouldAnimate)
			{
				m_animating = true;

				if (ii == 7 && nextLevel == 2 && m_currentPage == 0)
				{
					this->runAction(CCSequence::createWithTwoActions(
						CCDelayTime::create(delayTime),
						CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::animateShopUnlock))));
				}
				if (ii < lastDot + 1)
					children->runAction(CCSequence::create(CCDelayTime::create(delayTime), CCFadeIn::create(0.1), CCEaseBounceOut::create(scaleWithBounce), nullptr));

				if (ii == lastDot)
				{
					log::info("Next Level: {}", nextLevel);
					auto levelButton = static_cast<CCMenuItemSpriteExtra *>(m_levelMenu->getChildByTag(nextLevel));

					//  The level button is enabled
					if (levelButton)
						levelButton->runAction(CCSequence::createWithTwoActions(
							CCDelayTime::create(delayTime + .3f),
							CCCallFuncO::create(levelButton, callfuncO_selector(OdysseySelectLayer::enableLevelAnimation), levelButton)));

					//  When the animation is done, the ogre will talk
					this->runAction(CCSequence::create(
						CCDelayTime::create(delayTime + .3f),
						CCDelayTime::create(.5f),
						CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::getOgreDialog)),
						CCCallFunc::create(this, callfunc_selector(OdysseySelectLayer::enableButtonTouch)),
						0));
				}
			}
		}

		if (lastDot == 0)
			opacity = 0;

		if (children)
		{
			children->setOpacity(opacity);
			children->setScale(scale);
		}
	}
}

void OdysseySelectLayer::enableButtonTouch()
{
	this->m_animating = false;
}

void OdysseySelectLayer::switchToPage(int page)
{
	auto scene = OdysseySelectLayer::scene(page);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
}

void OdysseySelectLayer::onNextPage(CCObject *)
{
	switchToPage(m_currentPage + 1);
}

void OdysseySelectLayer::onBackPage(CCObject *)
{
	switchToPage(m_currentPage - 1);
}

void OdysseySelectLayer::onLevel(CCObject *sender)
{
	if (m_animating)
		return;

	if (sender->getTag() != 1 && !isLevelComplete(sender->getTag() - 1) && !Mod::get()->getSettingValue<bool>("bypass-levels"))
	{
		auto dialog = Odyssey::createDialog("main-level-locked", 4);
		this->addChild(dialog, 10);
		return;
	}

	auto popup = OdysseyLevelPopup::create(sender->getTag() + 7000);
	popup->show();
}

//  Boton del Ogro
void OdysseySelectLayer::onOgre(CCObject *)
{
	//  If the ogre hasn't been unlocked yet
	if (!AchievementManager::sharedState()->isAchievementEarned("geometry.ach.level05b") && !Mod::get()->getSettingValue<bool>("bypass-vaults"))
	{
		log::info("LOCKED OGRE");
		auto dialog = Odyssey::createDialog("ogre-locked", 3, true);
		this->addChild(dialog, 10);
		return;
	}

	//  First dialogue when meeting the Ogre
	if (!GameManager::sharedState()->getUGV("288"))
	{
		auto dialog = Odyssey::createDialog("ogre-meeting", 3, true);
		this->addChild(dialog, 10);
		GameManager::sharedState()->setUGV("288", true);
		return;
	}

	auto scene = CCScene::create();
	scene->addChild(SecretVaultLayer2::create());
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
};

void OdysseySelectLayer::onExtraLevel(CCObject *sender)
{
	//  Game Manager
	auto GM = GameManager::sharedState();
	auto GSM = GameStatsManager::sharedState();
	auto extra01_unlocked = GSM->isItemUnlocked(UnlockType::GJItem, 1) || GM->getUGV("237");
	auto extra02_unlocked = GSM->isItemUnlocked(UnlockType::GJItem, 2) || GM->getUGV("238");

	//log::info("Tag: {}", sender->getTag());

	if ((extra01_unlocked && sender->getTag() == 501) || (extra02_unlocked && sender->getTag() == 502) || (sender->getTag() > 600 && isLevelComplete(sender->getTag() - 1)) || Mod::get()->getSettingValue<bool>("bypass-levels"))
	{
		auto popup = OdysseyLevelPopup::create(sender->getTag() + 7000);
		popup->show();
	}
	else
	{
		if (sender->getTag() > 600)
		{
			auto dialog = Odyssey::createDialog("ogre-level-locked", 3);
			this->addChild(dialog, 10);
			return;
		}

		auto dialog = Odyssey::createDialog("extra-level-locked", 4);
		this->addChild(dialog, 10);
	}
}

void OdysseySelectLayer::onRope(CCObject *)
{
	auto garage = GJGarageLayer::scene();

	CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInT::create(.63f, garage));
}

void OdysseySelectLayer::onSongs(CCObject *)
{
	auto layer = SongsLayer::create();
	layer->m_delegate = this;
	this->addChild(layer);
	layer->showLayer(false);
}

void OdysseySelectLayer::onShop(CCObject *)
{
	auto shop = GJShopLayer::scene(static_cast<ShopType>(6));

	CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInT::create(.63f, shop));
}

void OdysseySelectLayer::onSettings(CCObject *)
{
	geode::openSettingsPopup(Mod::get());
}

void OdysseySelectLayer::onComics(CCObject *)
{
	auto comicPopup = ComicPopup::create(m_currentPage);
	comicPopup->show();
}

void OdysseySelectLayer::onLanguage(CCObject *)
{
	auto popup = LanguagePopup::create();
	popup->m_scene = this;
	popup->setZOrder(104);
	popup->show();
}

OdysseySelectLayer *OdysseySelectLayer::create(int page)
{
	OdysseySelectLayer *pRet = new OdysseySelectLayer();
	if (pRet->init(page))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

CCScene *OdysseySelectLayer::scene(int page)
{
	auto scene = CCScene::create();
	scene->addChild(OdysseySelectLayer::create(page));
	return scene;
}
