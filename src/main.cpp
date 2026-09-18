#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;


// ============================================================
// ExternalHack Menu
// ============================================================

class ExternalHackMenu : public FLAlertLayer {
protected:

    int m_category = 0;
    CCMenu* m_categoryMenu = nullptr;
    CCMenu* m_featureMenu = nullptr;

    bool init() {
        if (!FLAlertLayer::init(
            nullptr,
            "ExternalHack",
            "",
            "CLOSE",
            nullptr,
            850.f,
            false,
            500.f,
            1.0f
        )) {
            return false;
        }

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // ----------------------------------------------------
        // Title
        // ----------------------------------------------------

        auto title = CCLabelBMFont::create(
            "EXTERNALHACK",
            "goldFont.fnt"
        );

        title->setPosition(
            winSize.width / 2.f,
            winSize.height - 35.f
        );

        title->setScale(0.8f);

        this->m_mainLayer->addChild(title);


        // ----------------------------------------------------
        // UP ARROW - CENTER TOP
        // ----------------------------------------------------

        auto arrowMenu = CCMenu::create();
        arrowMenu->setPosition(0, 0);

        this->m_mainLayer->addChild(
            arrowMenu,
            20
        );

        auto arrow = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName(
                "GJ_arrow01_001.png"
            ),
            this,
            menu_selector(ExternalHackMenu::onArrow)
        );

        arrow->setScale(0.7f);

        arrow->setPosition(
            winSize.width / 2.f,
            winSize.height - 78.f
        );

        arrowMenu->addChild(arrow);


        // ----------------------------------------------------
        // LEFT CATEGORY MENU
        // ----------------------------------------------------

        m_categoryMenu = CCMenu::create();
        m_categoryMenu->setPosition(0, 0);

        this->m_mainLayer->addChild(
            m_categoryMenu,
            10
        );

        createCategory("LEVEL", 0, 175.f);
        createCategory("UNIVERSAL", 1, 130.f);
        createCategory("CREATOR", 2, 85.f);
        createCategory("COSMETIC", 3, 40.f);
        createCategory("SPEEDHACK", 4, -5.f);
        createCategory("ICON EFFECTS", 5, -50.f);
        createCategory("LABELS", 6, -95.f);
        createCategory("SHORTCUTS", 7, -140.f);
        createCategory("CONFIG", 8, -185.f);
        createCategory("SEARCH", 9, -230.f);
        createCategory("FAVOURITES", 10, -275.f);


        // ----------------------------------------------------
        // FEATURE MENU
        // ----------------------------------------------------

        m_featureMenu = CCMenu::create();
        m_featureMenu->setPosition(0, 0);

        this->m_mainLayer->addChild(
            m_featureMenu,
            10
        );

        showLevelFeatures();

        return true;
    }


    // ========================================================
    // CATEGORY BUTTON
    // ========================================================

    void createCategory(
        const char* name,
        int id,
        float y
    ) {
        auto button = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(
                name,
                150,
                true,
                "bigFont.fnt",
                "GJ_button_04.png",
                25.f,
                0.6f
            ),
            this,
            menu_selector(ExternalHackMenu::onCategory)
        );

        button->setTag(id);

        button->setPosition(
            105.f,
            250.f + y
        );

        m_categoryMenu->addChild(button);
    }


    // ========================================================
    // FEATURE BUTTON
    // ========================================================

    void createFeature(
        const char* name,
        int id,
        float x,
        float y
    ) {
        auto checkbox = CCMenuItemToggler::create(
            CCSprite::createWithSpriteFrameName(
                "GJ_checkOff_001.png"
            ),
            CCSprite::createWithSpriteFrameName(
                "GJ_checkOn_001.png"
            ),
            this,
            menu_selector(ExternalHackMenu::onFeature)
        );

        checkbox->setTag(id);

        checkbox->setPosition(
            x,
            y
        );

        m_featureMenu->addChild(checkbox);


        auto label = CCLabelBMFont::create(
            name,
            "bigFont.fnt"
        );

        label->setScale(0.55f);

        label->setAnchorPoint(
            {0.f, 0.5f}
        );

        label->setPosition(
            x + 22.f,
            y
        );

        m_featureMenu->addChild(label);


        // + button

        auto plusSprite = ButtonSprite::create(
            "+",
            30,
            true,
            "bigFont.fnt",
            "GJ_button_01.png",
            25.f,
            0.8f
        );

        auto plus = CCMenuItemSpriteExtra::create(
            plusSprite,
            this,
            menu_selector(ExternalHackMenu::onPlus)
        );

        plus->setTag(id);

        plus->setPosition(
            x + 170.f,
            y
        );

        m_featureMenu->addChild(plus);


        // info button

        auto infoSprite = CCSprite::createWithSpriteFrameName(
            "GJ_infoIcon_001.png"
        );

        auto info = CCMenuItemSpriteExtra::create(
            infoSprite,
            this,
            menu_selector(ExternalHackMenu::onInfo)
        );

        info->setScale(0.7f);

        info->setTag(id);

        info->setPosition(
            x + 205.f,
            y
        );

        m_featureMenu->addChild(info);
    }


    // ========================================================
    // LEVEL FEATURES
    // ========================================================

    void showLevelFeatures() {

        float leftX = 350.f;
        float rightX = 650.f;

        float startY = 375.f;
        float spacing = 48.f;


        // LEFT

        createFeature(
            "NOCLIP",
            1,
            leftX,
            startY
        );

        createFeature(
            "SHOW HITBOXES",
            2,
            leftX,
            startY - spacing
        );

        createFeature(
            "HITBOX TRAIL",
            3,
            leftX,
            startY - spacing * 2
        );

        createFeature(
            "SHOW TRAJECTORY",
            4,
            leftX,
            startY - spacing * 3
        );

        createFeature(
            "ACCURATE HITBOXES",
            5,
            leftX,
            startY - spacing * 4
        );

        createFeature(
            "AUTO COLLECT COINS",
            6,
            leftX,
            startY - spacing * 5
        );

        createFeature(
            "AUTOCLICKER",
            7,
            leftX,
            startY - spacing * 6
        );

        createFeature(
            "CLASSIC PERCENTAGE",
            8,
            leftX,
            startY - spacing * 7
        );

        createFeature(
            "CONFIRM PRACTICE",
            9,
            leftX,
            startY - spacing * 8
        );


        // RIGHT

        createFeature(
            "INSTANT COMPLETE",
            10,
            rightX,
            startY
        );

        createFeature(
            "HITBOXES ON DEATH",
            11,
            rightX,
            startY - spacing
        );

        createFeature(
            "STARTPOS SWITCHER",
            12,
            rightX,
            startY - spacing * 2
        );

        createFeature(
            "ACCURATE PERCENTAGE",
            13,
            rightX,
            startY - spacing * 3
        );

        createFeature(
            "ALL MODES PLATFORMER",
            14,
            rightX,
            startY - spacing * 4
        );

        createFeature(
            "AUTO PRACTICE MODE",
            15,
            rightX,
            startY - spacing * 5
        );

        createFeature(
            "BEST IN PERCENTAGE",
            16,
            rightX,
            startY - spacing * 6
        );

        createFeature(
            "COIN TRACERS",
            17,
            rightX,
            startY - spacing * 7
        );

        createFeature(
            "CONFIRM RESTART",
            18,
            rightX,
            startY - spacing * 8
        );
    }


    // ========================================================
    // CATEGORY CLICK
    // ========================================================

    void onCategory(CCObject* sender) {

        auto button =
            static_cast<CCMenuItemSpriteExtra*>(sender);

        m_category = button->getTag();

        m_featureMenu->removeAllChildren();

        if (m_category == 0) {
            showLevelFeatures();
        }
        else {
            showComingSoon();
        }
    }


    // ========================================================
    // OTHER CATEGORIES
    // ========================================================

    void showComingSoon() {

        auto winSize =
            CCDirector::sharedDirector()->getWinSize();

        auto text = CCLabelBMFont::create(
            "FEATURES WILL BE ADDED HERE",
            "bigFont.fnt"
        );

        text->setPosition(
            winSize.width / 2.f + 100.f,
            winSize.height / 2.f
        );

        text->setScale(0.65f);

        m_featureMenu->addChild(text);
    }


    // ========================================================
    // FEATURE TOGGLE
    // ========================================================

    void onFeature(CCObject* sender) {

        auto toggle =
            static_cast<CCMenuItemToggler*>(sender);

        int id = toggle->getTag();

        log::info(
            "ExternalHack feature {} toggled",
            id
        );
    }


    // ========================================================
    // PLUS
    // ========================================================

    void onPlus(CCObject* sender) {

        auto button =
            static_cast<CCMenuItemSpriteExtra*>(sender);

        int id = button->getTag();

        log::info(
            "ExternalHack settings for feature {}",
            id
        );

        FLAlertLayer::create(
            "ExternalHack",
            "Additional settings will be added here.",
            "OK"
        )->show();
    }


    // ========================================================
    // INFO
    // ========================================================

    void onInfo(CCObject* sender) {

        auto button =
            static_cast<CCMenuItemSpriteExtra*>(sender);

        int id = button->getTag();

        FLAlertLayer::create(
            "ExternalHack",
            fmt::format(
                "Feature ID: {}",
                id
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


        auto sprite =
            ButtonSprite::create("EXTERNAL");

        auto button =
            CCMenuItemSpriteExtra::create(
                sprite,
                this,
                menu_selector(
                    ExternalHackPauseLayer::onExternalHack
                )
            );

        auto winSize =
            CCDirector::sharedDirector()->getWinSize();

        button->setPosition(
            winSize.width - 70.f,
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