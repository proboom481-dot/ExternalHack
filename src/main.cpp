#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(ExternalHackEditorUI, EditorUI) {
    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorUI::init(editorLayer))
            return false;

        auto menu = CCMenu::create();
        menu->setPosition(0, 0);

        auto sprite = ButtonSprite::create("EXTERNAL");

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(ExternalHackEditorUI::onExternalHack)
        );

        button->setPosition(100, 100);

        menu->addChild(button);
        this->addChild(menu);

        return true;
    }

    void onExternalHack(CCObject*) {
        FLAlertLayer::create(
            "ExternalHack",
            "ExternalHack is working!",
            "OK"
        )->show();
    }
};