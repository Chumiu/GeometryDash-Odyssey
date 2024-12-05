#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/MoreOptionsLayer.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/GManager.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include <Geode/modify/LocalLevelManager.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>

using namespace geode::prelude;

class $modify(CCSprite)
{
	static CCSprite *create(const char *pszFileName)
	{
		if (std::string_view(pszFileName) == std::string_view("dialogIcon_019.png"))
		{
			return CCSprite::create("GDO_DialogIcon_005.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_020.png"))
		{
			return CCSprite::create("GDO_DialogIcon_006.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_021.png"))
		{
			return CCSprite::create("GDO_DialogIcon_007.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_022.png"))
		{
			return CCSprite::create("GDO_DialogIcon_008.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_023.png"))
		{
			return CCSprite::create("GDO_DialogIcon_009.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_024.png"))
		{
			return CCSprite::create("GDO_DialogIcon_010.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_025.png"))
		{
			return CCSprite::create("GDO_DialogIcon_011.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_026.png"))
		{
			return CCSprite::create("GDO_DialogIcon_012.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_053.png"))
		{
			return CCSprite::create("GDO_DialogIcon_001.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_054.png"))
		{
			return CCSprite::create("GDO_DialogIcon_002.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_055.png"))
		{
			return CCSprite::create("GDO_DialogIcon_003.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_056.png"))
		{
			return CCSprite::create("GDO_DialogIcon_004.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_028.png"))
		{
			return CCSprite::create("GDO_DialogIcon_013.png"_spr);
		}

		return CCSprite::create(pszFileName);
	}
};

/*
class $modify(GDOMoreOptionsLayer, MoreOptionsLayer)
{
	bool init()
	{
		if (!MoreOptionsLayer::init())
			return false;

		//	Aun en fase de prueba
		MoreOptionsLayer::addToggle("Pizza", "Pasta", "Ravioli");
		MoreOptionsLayer::addToggle("Burger", "Pasta", "Ravioli");
		MoreOptionsLayer::addToggle("Hot Dog", "Pasta", "Ravioli");
		MoreOptionsLayer::addToggle("Soup", "Pasta", "Ravioli");

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
*/

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