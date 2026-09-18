#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class ExternalHackMenu : public FLAlertLayer {
protected:
    bool init() {
        if (!FLAlertLayer::init(
            nullptr,
            "ExternalHack",
            "ExternalHack menu",
            "CLOSE",
            nullptr,
            420.f,
            false,
            220.f,
            1.0f
        )) {
            return false;
        }

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto menu = CCMenu::create();
        menu->setPosition(0, 0);
        this->m_mainLayer->addChild(menu);

        auto noclip = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("NOCLIP"),
            this,
            menu_selector(ExternalHackMenu::onNoclip)
        );

        noclip->setPosition(
            winSize.width / 2.f - 100.f,
            winSize.height / 2.f + 35.f
        );

        menu->addChild(noclip);

        auto speedhack = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("SPEEDHACK"),
            this,
            menu_selector(ExternalHackMenu::onSpeedhack)
        );

        speedhack->setPosition(
            winSize.width / 2.f + 100.f,
            winSize.height / 2.f + 35.f
        );

        menu->addChild(speedhack);

        auto particles = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("NO PARTICLES"),
            this,
            menu_selector(ExternalHackMenu::onParticles)
        );

        particles->setPosition(
            winSize.width / 2.f - 100.f,
            winSize.height / 2.f - 25.f
        );

        menu->addChild(particles);

        auto shake = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("NO SHAKE"),
            this,
            menu_selector(ExternalHackMenu::onShake)
        );

        shake->setPosition(
            winSize.width / 2.f + 100.f,
            winSize.height / 2.f - 25.f
        );

        menu->addChild(shake);

        return true;
    }

    void onNoclip(CCObject*) {
        FLAlertLayer::create(
            "ExternalHack",
            "Noclip: test button",
            "OK"
        )->show();
    }

    void onSpeedhack(CCObject*) {
        FLAlertLayer::create(
            "ExternalHack",
            "Speedhack: test button",
            "OK"
        )->show();
    }

    void onParticles(CCObject*) {
        FLAlertLayer::create(
            "ExternalHack",
            "No Particles: test button",
            "OK"
        )->show();
    }

    void onShake(CCObject*) {
        FLAlertLayer::create(
            "ExternalHack",
            "No Shake: test button",
            "OK"
        )->show();
    }

public:
    static ExternalHackMenu* create() {
        auto ret = new ExternalHackMenu();

        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};


class $modify(ExternalHackPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto menu = CCMenu::create();
        menu->setPosition(0, 0);
        this->addChild(menu, 100);

        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("EXTERNAL"),
            this,
            menu_selector(ExternalHackPauseLayer::onExternalHack)
        );

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        button->setPosition(
            winSize.width - 70.f,
            45.f
        );

        menu->addChild(button);
    }

    void onExternalHack(CCObject*) {
        auto popup = ExternalHackMenu::create();

        if (popup)
            popup->show();
    }
};