#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;


// ============================================================
// ExternalHack
// ============================================================

class ExternalHackMenu : public FLAlertLayer {
protected:

    CCMenu* m_categoryMenu = nullptr;
    CCMenu* m_featureMenu = nullptr;

    bool init() {

        if (!FLAlertLayer::init(
            nullptr,
            "ExternalHack",
            "",
            "CLOSE",
            nullptr,
            760.f,
            false,
            430.f,
            0.8f
        )) {
            return false;
        }

        // ----------------------------------------------------
        // WINDOW SIZE
        // ----------------------------------------------------

        constexpr float W = 760.f;
        constexpr float H = 430.f;


        // ----------------------------------------------------
        // TITLE
        // ----------------------------------------------------

        auto title = CCLabelBMFont::create(
            "EXTERNALHACK",
            "goldFont.fnt"
        );

        title->setPosition(
            W / 2.f,
            H - 25.f
        );

        title->setScale(0.55f);

        m_mainLayer->addChild(
            title,
            20
        );


        // ----------------------------------------------------
        // UP ARROW - CENTER
        // ----------------------------------------------------

        auto arrowMenu = CCMenu::create();
        arrowMenu->setPosition(0, 0);

        m_mainLayer->addChild(
            arrowMenu,
            30
        );

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
            W / 2.f,
            H - 60.f
        );

        arrowMenu->addChild(arrow);


        // ----------------------------------------------------
        // CATEGORY MENU
        // ----------------------------------------------------

        m_categoryMenu = CCMenu::create();
        m_categoryMenu->setPosition(0, 0);

        m_mainLayer->addChild(
            m_categoryMenu,
            10
        );


        const float categoryX = 92.f;

        createCategory(
            "LEVEL",
            0,
            categoryX,
            335.f
        );

        createCategory(
            "UNIVERSAL",
            1,
            categoryX,
            300.f
        );

        createCategory(
            "CREATOR",
            2,
            categoryX,
            265.f
        );

        createCategory(
            "COSMETIC",
            3,
            categoryX,
            230.f
        );

        createCategory(
            "SPEEDHACK",
            4,
            categoryX,
            195.f
        );

        createCategory(
            "ICON EFFECTS",
            5,
            categoryX,
            160.f
        );

        createCategory(
            "LABELS",
            6,
            categoryX,
            125.f
        );

        createCategory(
            "SHORTCUTS",
            7,
            categoryX,
            90.f
        );

        createCategory(
            "CONFIG",
            8,
            categoryX,
            55.f
        );

        createCategory(
            "SEARCH",
            9,
            categoryX,
            20.f
        );


        // ----------------------------------------------------
        // FEATURES
        // ----------------------------------------------------

        m_featureMenu = CCMenu::create();
        m_featureMenu->setPosition(0, 0);

        m_mainLayer->addChild(
            m_featureMenu,
            10
        );

        showLevelFeatures();


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
            125,
            true,
            "bigFont.fnt",
            "GJ_button_04.png",
            20.f,
            0.55f
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

        m_categoryMenu->addChild(button);
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

        // CHECKBOX

        auto off =
            CCSprite::createWithSpriteFrameName(
                "GJ_checkOff_001.png"
            );

        auto on =
            CCSprite::createWithSpriteFrameName(
                "GJ_checkOn_001.png"
            );

        auto checkbox = CCMenuItemToggler::create(
            off,
            on,
            this,
            menu_selector(
                ExternalHackMenu::onFeature
            )
        );

        checkbox->setTag(id);
        checkbox->setScale(0.55f);

        checkbox->setPosition(
            x,
            y
        );

        m_featureMenu->addChild(
            checkbox
        );


        // LABEL

        auto label = CCLabelBMFont::create(
            name,
            "bigFont.fnt"
        );

        label->setScale(0.40f);

        label->setAnchorPoint(
            {0.f, 0.5f}
        );

        label->setPosition(
            x + 17.f,
            y
        );

        m_featureMenu->addChild(
            label
        );


        // PLUS

        auto plusSprite = ButtonSprite::create(
            "+",
            24,
            true,
            "bigFont.fnt",
            "GJ_button_01.png",
            18.f,
            0.65f
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
            x + 175.f,
            y
        );

        m_featureMenu->addChild(
            plus
        );


        // INFO

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
        info->setScale(0.55f);

        info->setPosition(
            x + 202.f,
            y
        );

        m_featureMenu->addChild(
            info
        );
    }


    // ========================================================
    // LEVEL FEATURES
    // ========================================================

    void showLevelFeatures() {

        const float leftX = 300.f;
        const float rightX = 510.f;

        const float firstY = 320.f;
        const float gap = 34.f;


        // LEFT

        createFeature(
            "NOCLIP",
            1,
            leftX,
            firstY
        );

        createFeature(
            "SHOW HITBOXES",
            2,
            leftX,
            firstY - gap
        );

        createFeature(
            "HITBOX TRAIL",
            3,
            leftX,
            firstY - gap * 2
        );

        createFeature(
            "SHOW TRAJECTORY",
            4,
            leftX,
            firstY - gap * 3
        );

        createFeature(
            "ACCURATE HITBOXES",
            5,
            leftX,
            firstY - gap * 4
        );

        createFeature(
            "AUTO COLLECT COINS",
            6,
            leftX,
            firstY - gap * 5
        );

        createFeature(
            "AUTOCLICKER",
            7,
            leftX,
            firstY - gap * 6
        );

        createFeature(
            "CLASSIC PERCENTAGE",
            8,
            leftX,
            firstY - gap * 7
        );


        // RIGHT

        createFeature(
            "INSTANT COMPLETE",
            10,
            rightX,
            firstY
        );

        createFeature(
            "HITBOXES ON DEATH",
            11,
            rightX,
            firstY - gap
        );

        createFeature(
            "STARTPOS SWITCHER",
            12,
            rightX,
            firstY - gap * 2
        );

        createFeature(
            "ACCURATE PERCENTAGE",
            13,
            rightX,
            firstY - gap * 3
        );

        createFeature(
            "PLATFORMER MODE",
            14,
            rightX,
            firstY - gap * 4
        );

        createFeature(
            "AUTO PRACTICE",
            15,
            rightX,
            firstY - gap * 5
        );

        createFeature(
            "BEST PERCENTAGE",
            16,
            rightX,
            firstY - gap * 6
        );

        createFeature(
            "COIN TRACERS",
            17,
            rightX,
            firstY - gap * 7
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

        int category =
            button->getTag();

        m_featureMenu->removeAllChildren();


        if (category == 0) {

            showLevelFeatures();

        } else {

            auto text =
                CCLabelBMFont::create(
                    "MORE FEATURES COMING",
                    "bigFont.fnt"
                );

            text->setPosition(
                510.f,
                210.f
            );

            text->setScale(0.5f);

            m_featureMenu->addChild(
                text
            );
        }
    }


    // ========================================================
    // TOGGLE
    // ========================================================

    void onFeature(CCObject* sender) {

        auto toggle =
            static_cast<CCMenuItemToggler*>(
                sender
            );

        log::info(
            "ExternalHack feature {} = {}",
            toggle->getTag(),
            toggle->isToggled()
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

        log::info(
            "Settings for feature {}",
            button->getTag()
        );
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

        auto ret =
            new ExternalHackMenu();

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

        auto menu =
            CCMenu::create();

        menu->setPosition(
            0,
            0
        );

        this->addChild(
            menu,
            100
        );


        auto button =
            CCMenuItemSpriteExtra::create(
                ButtonSprite::create(
                    "EXTERNAL"
                ),
                this,
                menu_selector(
                    ExternalHackPauseLayer::
                    onExternalHack
                )
            );


        auto size =
            CCDirector::
            sharedDirector()->
            getWinSize();


        button->setPosition(
            size.width - 65.f,
            45.f
        );


        menu->addChild(
            button
        );
    }


    void onExternalHack(CCObject*) {

        auto menu =
            ExternalHackMenu::create();

        if (menu)
            menu->show();
    }
};