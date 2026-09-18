#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;


// ============================================================
// ExternalHack Menu
// ============================================================

class ExternalHackMenu : public FLAlertLayer {
protected:
    CCMenu* m_categories = nullptr;
    CCMenu* m_features = nullptr;

    bool init() {
        // Компактный размер.
        // На Android это будет примерно размером с референс.
        if (!FLAlertLayer::init(
            nullptr,
            "EXTERNALHACK",
            "",
            "CLOSE",
            nullptr,
            540.f,
            false,
            360.f,
            0.75f
        )) {
            return false;
        }

        // ----------------------------------------------------
        // ARROW - СТРОГО ПО ЦЕНТРУ СВЕРХУ
        // ----------------------------------------------------

        auto arrowMenu = CCMenu::create();
        arrowMenu->setPosition(0, 0);

        m_mainLayer->addChild(arrowMenu, 50);

        auto arrowSprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_arrow01_001.png"
            );

        auto arrow = CCMenuItemSpriteExtra::create(
            arrowSprite,
            this,
            menu_selector(
                ExternalHackMenu::onArrow
            )
        );

        arrow->setScale(0.55f);

        arrow->setPosition(
            270.f,
            330.f
        );

        arrowMenu->addChild(arrow);


        // ----------------------------------------------------
        // CATEGORIES
        // ----------------------------------------------------

        m_categories = CCMenu::create();
        m_categories->setPosition(0, 0);

        m_mainLayer->addChild(
            m_categories,
            20
        );

        const float categoryX = 82.f;

        createCategory("LEVEL",        0, categoryX, 295.f);
        createCategory("UNIVERSAL",    1, categoryX, 268.f);
        createCategory("CREATOR",      2, categoryX, 241.f);
        createCategory("COSMETIC",     3, categoryX, 214.f);
        createCategory("SPEEDHACK",    4, categoryX, 187.f);
        createCategory("ICON EFFECTS", 5, categoryX, 160.f);
        createCategory("LABELS",       6, categoryX, 133.f);
        createCategory("SHORTCUTS",    7, categoryX, 106.f);
        createCategory("CONFIG",       8, categoryX, 79.f);
        createCategory("SEARCH",       9, categoryX, 52.f);
        createCategory("FAVOURITES",  10, categoryX, 25.f);


        // ----------------------------------------------------
        // FEATURES
        // ----------------------------------------------------

        m_features = CCMenu::create();
        m_features->setPosition(0, 0);

        m_mainLayer->addChild(
            m_features,
            20
        );

        showLevel();


        return true;
    }


    // ========================================================
    // CATEGORY BUTTON
    // ========================================================

    void createCategory(
        const char* name,
        int id,
        float x,
        float y
    ) {
        auto sprite = ButtonSprite::create(
            name,
            105,
            true,
            "bigFont.fnt",
            "GJ_button_04.png",
            18.f,
            0.45f
        );

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(
                ExternalHackMenu::onCategory
            )
        );

        button->setTag(id);

        button->setPosition(
            x,
            y
        );

        m_categories->addChild(button);
    }


    // ========================================================
    // FEATURE
    // ========================================================

    void createFeature(
        const char* name,
        int id,
        float x,
        float y
    ) {
        // Checkbox

        auto off =
            CCSprite::createWithSpriteFrameName(
                "GJ_checkOff_001.png"
            );

        auto on =
            CCSprite::createWithSpriteFrameName(
                "GJ_checkOn_001.png"
            );

        auto toggle = CCMenuItemToggler::create(
            off,
            on,
            this,
            menu_selector(
                ExternalHackMenu::onFeature
            )
        );

        toggle->setTag(id);
        toggle->setScale(0.43f);

        toggle->setPosition(
            x,
            y
        );

        m_features->addChild(toggle);


        // Text

        auto label = CCLabelBMFont::create(
            name,
            "bigFont.fnt"
        );

        label->setAnchorPoint(
            {0.f, 0.5f}
        );

        label->setScale(0.31f);

        label->setPosition(
            x + 13.f,
            y
        );

        m_features->addChild(label);


        // Plus

        auto plusSprite = ButtonSprite::create(
            "+",
            21,
            true,
            "bigFont.fnt",
            "GJ_button_01.png",
            15.f,
            0.55f
        );

        auto plus = CCMenuItemSpriteExtra::create(
            plusSprite,
            this,
            menu_selector(
                ExternalHackMenu::onPlus
            )
        );

        plus->setTag(id);

        plus->setPosition(
            x + 137.f,
            y
        );

        m_features->addChild(plus);


        // Info

        auto infoSprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_infoIcon_001.png"
            );

        auto info = CCMenuItemSpriteExtra::create(
            infoSprite,
            this,
            menu_selector(
                ExternalHackMenu::onInfo
            )
        );

        info->setTag(id);
        info->setScale(0.43f);

        info->setPosition(
            x + 159.f,
            y
        );

        m_features->addChild(info);
    }


    // ========================================================
    // LEVEL
    // ========================================================

    void showLevel() {
        const float leftX = 220.f;
        const float rightX = 410.f;

        const float top = 292.f;
        const float gap = 30.f;


        // LEFT

        createFeature(
            "NOCLIP",
            1,
            leftX,
            top
        );

        createFeature(
            "SHOW HITBOXES",
            2,
            leftX,
            top - gap
        );

        createFeature(
            "HITBOX TRAIL",
            3,
            leftX,
            top - gap * 2
        );

        createFeature(
            "SHOW TRAJECTORY",
            4,
            leftX,
            top - gap * 3
        );

        createFeature(
            "ACCURATE HITBOXES",
            5,
            leftX,
            top - gap * 4
        );

        createFeature(
            "AUTO COLLECT COINS",
            6,
            leftX,
            top - gap * 5
        );

        createFeature(
            "AUTOCLICKER",
            7,
            leftX,
            top - gap * 6
        );

        createFeature(
            "CLASSIC PERCENTAGE",
            8,
            leftX,
            top - gap * 7
        );

        createFeature(
            "CONFIRM PRACTICE",
            9,
            leftX,
            top - gap * 8
        );


        // RIGHT

        createFeature(
            "INSTANT COMPLETE",
            10,
            rightX,
            top
        );

        createFeature(
            "HITBOXES ON DEATH",
            11,
            rightX,
            top - gap
        );

        createFeature(
            "STARTPOS SWITCHER",
            12,
            rightX,
            top - gap * 2
        );

        createFeature(
            "ACCURATE PERCENTAGE",
            13,
            rightX,
            top - gap * 3
        );

        createFeature(
            "PLATFORMER MODE",
            14,
            rightX,
            top - gap * 4
        );

        createFeature(
            "AUTO PRACTICE",
            15,
            rightX,
            top - gap * 5
        );

        createFeature(
            "BEST PERCENTAGE",
            16,
            rightX,
            top - gap * 6
        );

        createFeature(
            "COIN TRACERS",
            17,
            rightX,
            top - gap * 7
        );

        createFeature(
            "CONFIRM RESTART",
            18,
            rightX,
            top - gap * 8
        );
    }


    // ========================================================
    // CATEGORY
    // ========================================================

    void onCategory(CCObject* sender) {
        auto button =
            static_cast<CCMenuItemSpriteExtra*>(sender);

        int id = button->getTag();

        m_features->removeAllChildren();

        if (id == 0) {
            showLevel();
            return;
        }

        auto text = CCLabelBMFont::create(
            "NO FEATURES YET",
            "bigFont.fnt"
        );

        text->setPosition(
            365.f,
            180.f
        );

        text->setScale(0.45f);

        m_features->addChild(text);
    }


    // ========================================================
    // FEATURE TOGGLE
    // ========================================================

    void onFeature(CCObject* sender) {
        auto toggle =
            static_cast<CCMenuItemToggler*>(sender);

        log::info(
            "ExternalHack feature {} -> {}",
            toggle->getTag(),
            toggle->isToggled()
        );
    }


    // ========================================================
    // PLUS
    // ========================================================

    void onPlus(CCObject* sender) {
        auto button =
            static_cast<CCMenuItemSpriteExtra*>(sender);

        log::info(
            "ExternalHack settings: {}",
            button->getTag()
        );
    }


    // ========================================================
    // INFO
    // ========================================================

    void onInfo(CCObject* sender) {
        auto button =
            static_cast<CCMenuItemSpriteExtra*>(sender);

        FLAlertLayer::create(
            "ExternalHack",
            fmt::format(
                "Feature ID: {}",
                button->getTag()
            ).c_str(),
            "OK"
        )->show();
    }


    // ========================================================
    // ARROW
    // ========================================================

    void onArrow(CCObject*) {
        this->keyBackClicked();
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


// ============================================================
// PAUSE LAYER
// ============================================================

class $modify(
    ExternalHackPauseLayer,
    PauseLayer
) {
    void customSetup() {
        PauseLayer::customSetup();

        auto menu = CCMenu::create();
        menu->setPosition(0, 0);

        this->addChild(
            menu,
            100
        );

        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("EXTERNAL"),
            this,
            menu_selector(
                ExternalHackPauseLayer::onExternalHack
            )
        );

        auto size =
            CCDirector::sharedDirector()->getWinSize();

        button->setPosition(
            size.width - 65.f,
            45.f
        );

        menu->addChild(button);
    }


    void onExternalHack(CCObject*) {
        auto menu =
            ExternalHackMenu::create();

        if (menu)
            menu->show();
    }
};