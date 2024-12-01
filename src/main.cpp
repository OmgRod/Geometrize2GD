#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

#include <alphalaneous.editortab_api/include/EditorTabs.hpp>
#include <hjfod.gmd-api/include/GMD.hpp>

using namespace geode::prelude;

// Declare the global variable to store the GJGameLevel pointer
GJGameLevel* g_currentLevel = nullptr;

class $modify(MyLevelEditorLayer, LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1) {
        log::debug("Initializing MyLevelEditorLayer");

        if (!LevelEditorLayer::init(p0, p1)) {
            log::debug("Failed to initialize base LevelEditorLayer");
            return false;
        }

        // Store the GJGameLevel pointer in the global variable
        g_currentLevel = p0;
        log::debug("GJGameLevel pointer stored successfully");

        return true;
    }

    // The geometrize method that exports the level as a GMD file
    void geometrize(CCObject*) {
        log::debug("Geometrize method triggered");

        if (g_currentLevel) {
            log::debug("Exporting level as GMD file");

            std::filesystem::path path = Mod::get()->getTempDir() / "level.gmd";
            log::debug("Export path: {}", path.string());

            gmd::exportLevelAsGmd(g_currentLevel, path);
            log::debug("Level export completed");
        } else {
            log::debug("No current level found, skipping export");
        }
    }
};

$execute {
    EditorTabs::get()->registerTab(TabType::BUILD, "geometrize2gd"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler) -> CCNode* {
        log::debug("Creating geometrize button...");

        auto arr = CCArray::create();
        
        // Create the button and log it
        auto btn = CCMenuItemSpriteExtra::create(
            CCSprite::create("geometrizeBtn.png"_spr),
            nullptr,
            menu_selector(MyLevelEditorLayer::geometrize)
        );
        
        // Add logging for button creation
        if (btn) {
            log::debug("Geometrize button created successfully");
        } else {
            log::debug("Failed to create geometrize button");
        }
        
        arr->addObject(btn);

        CCLabelBMFont* textLabel = CCLabelBMFont::create("G", "bigFont.fnt");
        textLabel->setScale(0.4f);

        EditorTabUtils::setTabIcons(toggler, textLabel, textLabel);

        return EditorTabUtils::createEditButtonBar(arr, ui);
    }, [&](EditorUI*, bool state, CCNode*) {
        // No additional functionality needed here
    });
}
