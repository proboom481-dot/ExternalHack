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
    CCMenu* m_topMenu = nullptr;

    bool m_noclip = false;
    bool m_hitboxes = false;
    bool m_hitboxTrail = false;
    bool m_trajectory = false;
    bool m_startpos = false;
    bool m_autoPractice = false;
    bool m_autoclicker = false;


    bool init() {

        if (!FLAlertLayer::init(
            nullptr,
            "",
            "",
            "",
            nullptr,
            540.f,
            false,
            360.f,
            0.75f
        )) {
            return false;
        }

        auto size = m_mainLayer->getContentSize();


        // ====================================================
        // BACKGROUND
        // ====================================================

        auto background = CCLayerColor::create(
            {15, 22, 32, 245},
            size.width - 20.f,
            size.height - 20.f
        );

        background->setPosition(
            10.f,
            10.f
        );

        m_mainLayer->addChild(
            background,
            0
        );


        // ====================================================
        // TOP LINE
        // ====================================================

        auto topLine = CCLayerColor::create(
            {45, 190, 205, 255},
            size.width - 20.f,
            3.f
        );

        topLine->setPosition(
            10.f,
            size.height - 13.f
        );

        m_mainLayer->addChild(
            topLine,
            2
        );


        // ====================================================
        // TITLE
        // ====================================================

        auto title = CCLabelBMFont::create(
            "EXTERNALHACK",
            "goldFont.fnt"
        );

        title->setPosition(
            size.width / 2.f,
            size.height - 32.f
        );

        title->setScale(0.52f);

        m_mainLayer->addChild(
            title,
            10
        );


        // ====================================================
        // TOP BUTTON MENU
        // ====================================================

        m_topMenu = CCMenu::create();
        m_topMenu->setPosition(0, 0);

        m_mainLayer->addChild(
            m_topMenu,
            500
        );


        // ====================================================
        // ARROW
        // ====================================================

        auto arrowSprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_arrow01_001.png"
            );

        auto arrow = CCMenuItemSpriteExtra::create(
            arrowSprite,
            this,
            menu_selector(
                ExternalHackMenu::onBack
            )
        );

        arrow->setScale(0.55f);

        // СТРОГО ПО ЦЕНТРУ
        arrow->setPosition(
            size.width / 2.f,
            size.height - 8.f
        );

        m_topMenu->addChild(arrow);


        // ====================================================
        // EXIT
        // ====================================================

        auto exitSprite = ButtonSprite::create(
            "EXIT",
            65,
            true,
            "bigFont.fnt",
            "GJ_button_06.png",
            20.f,
            0.48f
        );

        auto exit = CCMenuItemSpriteExtra::create(
            exitSprite,
            this,
            menu_selector(
                ExternalHackMenu::onExit
            )
        );

        exit->setScale(0.85f);

        // Нижний правый угол
        exit->setPosition(
            size.width - 48.f,
            25.f
        );

        m_topMenu->addChild(exit);


        // ====================================================
        // CATEGORY AREA
        // ====================================================

        auto categoryBg = CCLayerColor::create(
            {22, 32, 45, 255},
            130.f,
            size.height - 70.f
        );

        categoryBg->setPosition(
            20.f,
            35.f
        );

        m_mainLayer->addChild(
            categoryBg,
            1
        );


        // разделитель
        auto separator = CCLayerColor::create(
            {45, 190, 205, 255},
            2.f,
            size.height - 70.f
        );

        separator->setPosition(
            150.f,
            35.f
        );

        m_mainLayer->addChild(
            separator,
            2
        );


        // ====================================================
        // CATEGORIES MENU
        // ====================================================

        m_categories = CCMenu::create();
        m_categories->setPosition(0, 0);

        m_mainLayer->addChild(
            m_categories,
            300
        );


        const char* categories[] = {
            "LEVEL",
            "UNIVERSAL",
            "CREATOR",
            "COSMETIC",
            "SPEEDHACK",
            "ICON EFFECTS",
            "LABELS",
            "SHORTCUTS",
            "CONFIG",
            "SEARCH"
        };


        float startY = size.height - 75.f;

        for (int i = 0; i < 10; i++) {

            createCategory(
                categories[i],
                i,
                85.f,
                startY - i * 27.f
            );
        }


        // ====================================================
        // FEATURES MENU
        // ====================================================

        m_features = CCMenu::create();
        m_features->setPosition(0, 0);

        m_mainLayer->addChild(
            m_features,
            400
        );


        showLevel();

        return true;
    }


    // ========================================================
    // CATEGORY
    // ========================================================

    void createCategory(
        const char* name,
        int id,
        float x,
        float y
    ) {

        auto sprite = ButtonSprite::create(
            name,
            108,
            true,
            "bigFont.fnt",
            id == 0
                ? "GJ_button_02.png"
                : "GJ_button_04.png",
            20.f,
            0.34f
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

        // Увеличиваем hitbox
        button->setContentSize({
            120.f,
            27.f
        });

        m_categories->addChild(button);
    }


    // ========================================================
    // FEATURE
    // ========================================================

    void createFeature(
        const char* name,
        int id,
        float x,
        float y,
        bool value = false
    ) {

        // --------------------------------------------
        // TOGGLE
        // --------------------------------------------

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
                ExternalHackMenu::onToggle
            )
        );

        toggle->setTag(id);
        toggle->setScale(0.48f);

        toggle->toggle(value);

        toggle->setPosition(
            x,
            y
        );

        m_features->addChild(toggle);


        // --------------------------------------------
        // LABEL
        // --------------------------------------------

        auto label = CCLabelBMFont::create(
            name,
            "bigFont.fnt"
        );

        label->setAnchorPoint(
            {0.f, 0.5f}
        );

        label->setPosition(
            x + 13.f,
            y
        );

        label->setScale(0.27f);

        m_features->addChild(
            label,
            1
        );


        // --------------------------------------------
        // PLUS
        // --------------------------------------------

        auto plusSprite = ButtonSprite::create(
            "+",
            18,
            true,
            "bigFont.fnt",
            "GJ_button_01.png",
            13.f,
            0.45f
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
            x + 125.f,
            y
        );

        m_features->addChild(plus);


        // --------------------------------------------
        // INFO
        // --------------------------------------------

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

        info->setScale(0.42f);

        info->setPosition(
            x + 147.f,
            y
        );

        m_features->addChild(info);
    }


    // ========================================================
    // LEVEL
    // ========================================================

    void showLevel() {

        const float left = 180.f;
        const float right = 350.f;

        const float top = 270.f;
        const float gap = 27.f;


        createFeature(
            "NOCLIP",
            1,
            left,
            top,
            m_noclip
        );

        createFeature(
            "SHOW HITBOXES",
            2,
            left,
            top - gap,
            m_hitboxes
        );

        createFeature(
            "HITBOX TRAIL",
            3,
            left,
            top - gap * 2,
            m_hitboxTrail
        );

        createFeature(
            "SHOW TRAJECTORY",
            4,
            left,
            top - gap * 3,
            m_trajectory
        );

        createFeature(
            "ACCURATE HITBOXES",
            5,
            left,
            top - gap * 4
        );

        createFeature(
            "AUTO COLLECT COINS",
            6,
            left,
            top - gap * 5
        );

        createFeature(
            "AUTOCLICKER",
            7,
            left,
            top - gap * 6,
            m_autoclicker
        );

        createFeature(
            "CLASSIC PERCENTAGE",
            8,
            left,
            top - gap * 7
        );


        createFeature(
            "INSTANT COMPLETE",
            10,
            right,
            top
        );

        createFeature(
            "HITBOXES ON DEATH",
            11,
            right,
            top - gap
        );

        createFeature(
            "STARTPOS SWITCHER",
            12,
            right,
            top - gap * 2,
            m_startpos
        );

        createFeature(
            "ACCURATE PERCENTAGE",
            13,
            right,
            top - gap * 3
        );

        createFeature(
            "PLATFORMER MODE",
            14,
            right,
            top - gap * 4
        );

        createFeature(
            "AUTO PRACTICE",
            15,
            right,
            top - gap * 5,
            m_autoPractice
        );

        createFeature(
            "BEST PERCENTAGE",
            16,
            right,
            top - gap * 6
        );

        createFeature(
            "COIN TRACERS",
            17,
            right,
            top - gap * 7
        );
    }


    // ========================================================
    // CATEGORY CLICK
    // ========================================================

    void onCategory(CCObject* sender) {

        auto button =
            static_cast<CCMenuItemSpriteExtra*>(
                sender
            );

        int id = button->getTag();

        m_features->removeAllChildren();


        if (id == 0) {
            showLevel();
            return;
        }


        const char* title = "CATEGORY";

        switch (id) {

            case 1:
                title = "UNIVERSAL";
                break;

            case 2:
                title = "CREATOR";
                break;

            case 3:
                title = "COSMETIC";
                break;

            case 4:
                title = "SPEEDHACK";
                break;

            case 5:
                title = "ICON EFFECTS";
                break;

            case 6:
                title = "LABELS";
                break;

            case 7:
                title = "SHORTCUTS";
                break;

            case 8:
                title = "CONFIG";
                break;

            case 9:
                title = "SEARCH";
                break;
        }


        auto label = CCLabelBMFont::create(
            title,
            "bigFont.fnt"
        );

        label->setPosition(
            350.f,
            190.f
        );

        label->setScale(0.5f);

        m_features->addChild(label);


        auto coming = CCLabelBMFont::create(
            "FEATURES WILL BE ADDED HERE",
            "bigFont.fnt"
        );

        coming->setPosition(
            350.f,
            160.f
        );

        coming->setScale(0.28f);

        m_features->addChild(coming);
    }


    // ========================================================
    // TOGGLE
    // ========================================================

    void onToggle(CCObject* sender) {

        auto toggle =
            static_cast<CCMenuItemToggler*>(
                sender
            );

        bool enabled = toggle->isToggled();


        switch (toggle->getTag()) {

            case 1:
                m_noclip = enabled;
                break;

            case 2:
                m_hitboxes = enabled;
                break;

            case 3:
                m_hitboxTrail = enabled;
                break;

            case 4:
                m_trajectory = enabled;
                break;

            case 7:
                m_autoclicker = enabled;
                break;

            case 12:
                m_startpos = enabled;
                break;

            case 15:
                m_autoPractice = enabled;
                break;
        }


        log::info(
            "ExternalHack: feature {} = {}",
            toggle->getTag(),
            enabled
        );
    }


    // ========================================================
    // PLUS
    // ========================================================

    void onPlus(CCObject* sender) {

        auto button =
            static_cast<CCMenuItemSpriteExtra*>(
                sender
            );

        FLAlertLayer::create(
            "ExternalHack",
            fmt::format(
                "Settings for feature {}",
                button->getTag()
            ).c_str(),
            "OK"
        )->show();
    }


    // ========================================================
    // INFO
    // ========================================================

    void onInfo(CCObject* sender) {

        auto button =
            static_cast<CCMenuItemSpriteExtra*>(
                sender
            );

        FLAlertLayer::create(
            "ExternalHack",
            fmt::format(
                "ExternalHack feature ID: {}",
                button->getTag()
            ).c_str(),
            "OK"
        )->show();
    }


    // ========================================================
    // BACK
    // ========================================================

    void onBack(CCObject*) {
        this->keyBackClicked();
    }


    // ========================================================
    // EXIT
    // ========================================================

    void onExit(CCObject*) {
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
            1000
        );


        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(
                "EXTERNAL",
                80,
                true,
                "bigFont.fnt",
                "GJ_button_01.png",
                25.f,
                0.55f
            ),
            this,
            menu_selector(
                ExternalHackPauseLayer::openExternalHack
            )
        );


        auto size =
            CCDirector::sharedDirector()->getWinSize();


        button->setPosition(
            size.width - 75.f,
            45.f
        );


        menu->addChild(button);
    }


    void openExternalHack(CCObject*) {

        auto menu =
            ExternalHackMenu::create();

        if (menu)
            menu->show();
    }
};