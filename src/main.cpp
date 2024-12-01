#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

#include <alphalaneous.editortab_api/include/EditorTabs.hpp>

using namespace geode::prelude;

$execute {
    EditorTabs::get()->registerTab(TabType::BUILD, "rawr"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler) -> CCNode* { //create

        auto arr = CCArray::create();
        auto label = CCLabelBMFont::create("meow", "bigFont.fnt");
        arr->addObject(label);

        CCLabelBMFont* textLabel = CCLabelBMFont::create("G", "bigFont.fnt");
        textLabel->setScale(0.4f);

        EditorTabUtils::setTabIcons(toggler, textLabel, textLabel);

        return EditorTabUtils::createEditButtonBar(arr, ui);
        
    }, [](EditorUI*, bool state, CCNode*) { //toggled the tab (activates on every tab click)

        log::info(":3");

    });
}

/*

class $modify(MyLevelEditorLayer, LevelEditorLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelEditorLayer::init(p0, p1)) {
			return false;
		}

		return true;
	}
};

*/