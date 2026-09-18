#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class ExternalHackMenu : public FLAlertLayer {
protected:
    bool m_noclip = false;
    bool m_speedhack = false;
    bool m_noParticles = false;
    bool m_noShake = false;
    bool m_noTrail = false;

    CCMenu* m_menu = nullptr;

    bool init() {
        if (!FLAlertLayer::init(
            nullptr,
            "ExternalHack",
            "CLOSE",
            nullptr,
            nullptr
        )) {
            return false;
        }

        this->setTouchEnabled(true);

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto title = CCLabelBMFont::create(
            "ExternalHack",
            "goldFont.fnt"
        );

        title->setPosition(
            winSize.width / 2,
            winSize.height - 35.f
        );

        title->setScale(0.8f);
        this->m_mainLayer->addChild(title);

        m_menu = CCMenu::create();
        m_menu->setPosition(0, 0);
        this->m_mainLayer->addChild(m_menu);

        createButton("NOCLIP", 0, 90.f);
        createButton("SPEEDHACK", 1, 40.f);
        createButton("NO PARTICLES", 2, -10.f);
        createButton("NO SHAKE", 3, -60.f);
        createButton("NO TRAIL", 4, -110.f);

        auto info = CCLabelBMFont::create(
            "ExternalHack Android",
            "chatFont.fnt"
        );

        info->setPosition(
            winSize.width / 2,
            25.f
        );

        info->setScale(0.6f);
        this->m_mainLayer->addChild(info);

        return true;
    }

    void createButton(const char* text, int id, float y) {
        auto sprite = ButtonSprite::create(text);

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(ExternalHackMenu::onButton)
        );

        button->setTag(id);

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        button->setPosition(
            winSize.width / 2,
            winSize.height / 2 + y
        );

        m_menu->addChild(button);
    }

    void onButton(CCObject* sender) {
        auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
        int id = button->getTag();

        switch (id) {
            case 0:
                m_noclip = !m_noclip;
                showState("Noclip", m_noclip);
                break;

            case 1:
                m_speedhack = !m_speedhack;
                showState("Speedhack", m_speedhack);
                break;

            case 2:
                m_noParticles = !m_noParticles;
                showState("No Particles", m_noParticles);
                break;

            case 3:
                m_noShake = !m_noShake;
                showState("No Shake", m_noShake);
                break;

            case 4:
                m_noTrail = !m_noTrail;
                showState("No Trail", m_noTrail);
                break;
        }
    }

    void showState(const char* name, bool enabled) {
        FLAlertLayer::create(
            name,
            enabled ? "Enabled" : "Disabled",
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

        auto buttonSprite = ButtonSprite::create(
            "EXTERNAL"
        );

        auto button = CCMenuItemSpriteExtra::create(
            buttonSprite,
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

        if (popup) {
            popup->show();
        }
    }
};