#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/MoreOptionsLayer.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/GManager.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include <Geode/modify/LocalLevelManager.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
#include <Geode/modify/SongsLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/GJItemIcon.hpp>
#include <Geode/modify/CurrencySprite.hpp>
#include "utils/Utils.hpp"

using namespace geode::prelude;

$on_mod(Loaded)
{
#ifdef GEODE_IS_WINDOWS
	auto zipFilePath = geode::Mod::get()->getResourcesDir().string() + "\\" + "Assets.zip";
#endif
#ifdef GEODE_IS_ANDROID
	auto zipFilePath = geode::Mod::get()->getResourcesDir().string() + "/" + "Assets.zip";
#endif
	auto unzipDir = geode::Mod::get()->getResourcesDir().string();
	auto result = geode::utils::file::Unzip::intoDir(zipFilePath, unzipDir);

	CCFileUtils::get()->addTexturePack(CCTexturePack{
		.m_id = Mod::get()->getID(),
		.m_paths = {geode::Mod::get()->getResourcesDir().string()}});
};

class $modify(OdysseyGManager, GManager)
{
	void setup()
	{
		auto compare = std::string(m_fileName);
		compare.insert(std::string_view(compare).find(".dat"), "Odyssey");
		m_fileName = compare;
		GManager::setup();
	}
};

class $modify(PauseLayer)
{
	void onQuit(CCObject *sender)
	{
		PauseLayer::onQuit(sender);

		int page = Odyssey::islandPageForLevelID(PlayLayer::get()->m_level->m_levelID);

        GameManager::sharedState()->fadeInMusic(fmt::format("IslandLoop{:02}.mp3"_spr, page));
	}
};

class $modify(GDOMoreOptionsLayer, MoreOptionsLayer)
{
	bool init()
	{
		if (!MoreOptionsLayer::init())
			return false;

		//	Aun en fase de prueba
		MoreOptionsLayer::addToggle("Spanish", "0201", "<cy>ENG</c>: Translates most of the mod's dialogue in Spanish. Due to character limitations, there will be spelling errors.\n\n<cy>ESP</c>: Traduce mayor parte del dialogo del mod en Espanol. Dado a las limitaciones de caracteres en el juego, habran errores ortograficos (como la falta de acentos)");
		MoreOptionsLayer::addToggle("Hide upcoming", "0202", "<cy>ENG</c>: Hides icons that are tagged as upcoming (thus impossible to get for now).\n\n<cy>SPA</c>: Oculta los iconos etiquetados como proximos (por tanto, imposibles de conseguir por ahora).");

		return true;
	}

	void goToPage(int p0)
	{
		MoreOptionsLayer::goToPage(p0);

		if (MoreOptionsLayer::m_page == 7)
		{
			MoreOptionsLayer::m_categoryLabel->setString("GD Odyssey Options");
		}
	}
};

class $modify(OdysseyEditorUI, EditorUI)
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

class $modify(OdysseyEditorPauseLayer, EditorPauseLayer)
{
	bool init(LevelEditorLayer *editorLayer)
	{
		if (!EditorPauseLayer::init(editorLayer))
			return false;

		auto copySpr = ButtonSprite::create("Save\nString", 50, 30, 0.4f, true, "bigFont.fnt", "GJ_button_04.png");
		copySpr->setScale(0.8);

		auto copyBtn = CCMenuItemSpriteExtra::create(copySpr, this, menu_selector(OdysseyEditorPauseLayer::copyStringToClipboard));
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

class $modify(GDOLocalLevelManager, LocalLevelManager)
{
	$override gd::string getMainLevelString(int id)
	{
		auto file = CCString::createWithFormat("level-%i.txt"_spr, id);
		if (file == nullptr)
			return "";

		auto content = CCString::createWithContentsOfFile(file->getCString());
		if (content == nullptr)
			return "";

		return gd::string(content->getCString());
	}
};

class $modify(GDOMusicDownloadManager, MusicDownloadManager)
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
		songObjectArray->addObject(SongObject::create(501));
		songObjectArray->addObject(SongObject::create(502));
		songObjectArray->addObject(SongObject::create(-1));

		m_listLayer->m_listView = CustomListView::create(songObjectArray, nullptr, 220.0, 356.0, 0, BoomListType::Song, 0.0);
		m_listLayer->addChild(m_listLayer->m_listView);
	}
};