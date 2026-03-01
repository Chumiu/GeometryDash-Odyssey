#include <Geode/Geode.hpp>
#include <Geode/modify/LocalLevelManager.hpp>
#include <Geode/modify/SongsLayer.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PurchaseItemPopup.hpp>

#include "utils/Utils.hpp"
#include "utils/IconUtils.hpp"

#ifdef DEVELOPER_MODE
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#endif

using namespace geode::prelude;

$on_mod(Loaded)
{
	if (!Odyssey::getEarlyLoadBreakingMods().empty())
	{
		auto mod = Loader::get()->getLoadedMod("teamtcm.geometry-dash-odyssey");

		for (Hook *hook : mod->getHooks())
		{
			if (hook->getDisplayName() == "MenuLayer::init")
				continue;

			if (hook->getDisplayName() == "LoadingLayer::init")
				continue;

			(void)hook->disable();
		}

		return;
	}
};

class $modify(PauseLayer)
{
	void onQuit(CCObject *sender)
	{
		PauseLayer::onQuit(sender);
		int page = Odyssey::islandPageForLevelID(PlayLayer::get()->m_level->m_levelID);

		auto pageID = (page + 1 < 3) ? page + 1 : 3;
		GameManager::sharedState()->fadeInMusic(fmt::format("IslandLoop{:02}.mp3"_spr, pageID));
	}
};

#ifdef DEVELOPER_MODE
class $modify(GDO_EditorUI, EditorUI)
{
	void setupCreateMenu()
	{
		EditorUI::setupCreateMenu();

		auto m_tab8 = static_cast<EditButtonBar *>(this->m_createButtonBars->objectAtIndex(8));
		m_tab8->m_buttonArray->insertObject(this->getCreateBtn(142, 4), 1);

		int rowCount = GameManager::get()->getIntGameVariable("0049");
		int columnCount = GameManager::get()->getIntGameVariable("0050");

		m_tab8->reloadItems(rowCount, columnCount);
	}
};

class $modify(GDO_EditorPauseLayer, EditorPauseLayer)
{
	bool init(LevelEditorLayer *editorLayer)
	{
		if (!EditorPauseLayer::init(editorLayer))
			return false;

		auto copySpr = ButtonSprite::create("Save\nString", 50, 30, 0.4f, true, "bigFont.fnt", "GJ_button_04.png");
		copySpr->setScale(0.8);

		auto copyBtn = CCMenuItemSpriteExtra::create(copySpr, this, menu_selector(GDO_EditorPauseLayer::copyStringToClipboard));
		copyBtn->setPositionX(70);

		auto menu = static_cast<CCMenu *>(this->getChildren()->objectAtIndex(1));
		menu->addChild(copyBtn);

		return true;
	}

	void copyStringToClipboard(CCObject *)
	{
		log::debug("{}", m_editorLayer->m_level->m_levelString);
		clipboard::write(m_editorLayer->m_level->m_levelString);
	}
};
#endif

class $modify(GDO_LocalLevelManager, LocalLevelManager)
{
	$override gd::string getMainLevelString(int id)
	{
		// auto file = CCString::createWithFormat("level-%i.txt"_spr, id);
		auto file = Mod::get()->getSettingValue<bool>("empty-levels") ? CCString::create("base.txt"_spr) : (Mod::get()->getSettingValue<bool>("updated-levels") && id < 7600) ? CCString::createWithFormat("level-%iB.txt"_spr, id)
																																							   : CCString::createWithFormat("level-%i.txt"_spr, id);
		if (file == nullptr)
			return "";

		auto content = CCString::createWithContentsOfFile(file->getCString());
		if (content == nullptr)
			return "";

		return gd::string(content->getCString());
		return LocalLevelManager::getMainLevelString(id);
	}
};

class $modify(GDO_MusicDownloadManager, MusicDownloadManager)
{
	gd::string pathForSFXFolder(int sfxID)
	{
		std::string path = MusicDownloadManager::pathForSFXFolder(sfxID);

		if (path == "sfx/")
			path = "/"_spr;

		return path;
	}

	gd::string pathForSongFolder(int songID)
	{
		std::string path = MusicDownloadManager::pathForSongFolder(songID);

		if (path == "songs/")
			path = "/"_spr;

		return path;
	}
};

class $modify(SongsLayer)
{
	void customSetup()
	{
		CCArray *songObjectArray = CCArray::create();
		songObjectArray->addObject(SongObject::create(101));
		songObjectArray->addObject(SongObject::create(102));
		songObjectArray->addObject(SongObject::create(103));
		songObjectArray->addObject(SongObject::create(104));
		songObjectArray->addObject(SongObject::create(105));
		songObjectArray->addObject(SongObject::create(106));
		songObjectArray->addObject(SongObject::create(107));
		songObjectArray->addObject(SongObject::create(108));
		songObjectArray->addObject(SongObject::create(109));
		songObjectArray->addObject(SongObject::create(501));
		songObjectArray->addObject(SongObject::create(502));
		songObjectArray->addObject(SongObject::create(601));
		songObjectArray->addObject(SongObject::create(602));
		songObjectArray->addObject(SongObject::create(603));
		songObjectArray->addObject(SongObject::create(604));
		songObjectArray->addObject(SongObject::create(-1));

		m_listLayer->m_listView = CustomListView::create(songObjectArray, nullptr, 220.0, 356.0, 0, BoomListType::Song, 0.0);
		m_listLayer->addChild(m_listLayer->m_listView);
	}
};

class $modify(PurchaseItemPopup)
{
	void onPurchase(CCObject *sender)
	{
		PurchaseItemPopup::onPurchase(sender);
		// log::info("Purchased! {}", "\n");
		// log::info("Type: {} ID: {}", m_storeItem->m_typeID.value(), m_storeItem->m_unlockType.value());

		if (m_storeItem->m_unlockType.value() == 12)
		{
			if (m_storeItem->m_typeID.value() == 1)
				GameManager::sharedState()->setUGV("237", true);
			if (m_storeItem->m_typeID.value() == 2)
				GameManager::sharedState()->setUGV("238", true);
		}

		IconUtils::unlockObject(m_storeItem->m_typeID.value(), m_storeItem->m_unlockType.value());
	}
};