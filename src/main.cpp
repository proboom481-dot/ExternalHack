#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;


// ============================================================
// EXTERNALHACK MENU
// ============================================================

class ExternalHackMenu : public FLAlertLayer {
protected:

    CCMenu* m_categories = nullptr;
    CCMenu* m_features = nullptr;
    CCLayer* m_featureLabels = nullptr;
    CCLayerColor* m_selectedCategory = nullptr;

    bool m_states[128] = {};
    int m_currentCategory = 0;


    // ========================================================
    // INIT
    // ========================================================

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

        const float W = 540.f;
        const float H = 360.f;


        // ====================================================
        // BACKGROUND
        // ====================================================

        auto background = CCLayerColor::create(
            {10, 16, 25, 250}
        );

        background->setContentSize({
            W - 20.f,
            H - 20.f
        });

        background->setPosition(
            10.f,
            10.f
        );

        m_mainLayer->addChild(
            background,
            0
        );


        // ====================================================
        // TOP BORDER
        // ====================================================

        auto border = CCLayerColor::create(
            {35, 210, 220, 255}
        );

        border->setContentSize({
            W - 20.f,
            3.f
        });

        border->setPosition(
            10.f,
            H - 14.f
        );

        m_mainLayer->addChild(
            border,
            5
        );


        // ====================================================
        // HEADER
        // ====================================================

        auto header = CCLayerColor::create(
            {16, 25, 38, 255}
        );

        header->setContentSize({
            W - 20.f,
            48.f
        });

        header->setPosition(
            10.f,
            H - 62.f
        );

        m_mainLayer->addChild(
            header,
            1
        );


        // ====================================================
        // TITLE
        // ====================================================

        auto title = CCLabelBMFont::create(
            "EXTERNALHACK",
            "goldFont.fnt"
        );

        title->setPosition(
            W / 2.f,
            H - 31.f
        );

        title->setScale(
            0.48f
        );

        m_mainLayer->addChild(
            title,
            20
        );


        auto version = CCLabelBMFont::create(
            "v1.0.0",
            "bigFont.fnt"
        );

        version->setPosition(
            W / 2.f,
            H - 47.f
        );

        version->setScale(
            0.19f
        );

        m_mainLayer->addChild(
            version,
            20
        );


        // ====================================================
        // SIDEBAR
        // ====================================================

        auto sidebar = CCLayerColor::create(
            {14, 23, 35, 255}
        );

        sidebar->setContentSize({
            130.f,
            290.f
        });

        sidebar->setPosition(
            20.f,
            37.f
        );

        m_mainLayer->addChild(
            sidebar,
            3
        );


        // ====================================================
        // SIDEBAR LINE
        // ====================================================

        auto sidebarLine = CCLayerColor::create(
            {35, 210, 220, 255}
        );

        sidebarLine->setContentSize({
            2.f,
            290.f
        });

        sidebarLine->setPosition(
            150.f,
            37.f
        );

        m_mainLayer->addChild(
            sidebarLine,
            4
        );


        // ====================================================
        // SELECTED CATEGORY
        // ====================================================

        m_selectedCategory = CCLayerColor::create(
            {30, 190, 200, 65}
        );

        m_selectedCategory->setContentSize({
            116.f,
            25.f
        });

        m_selectedCategory->setPosition(
            27.f,
            290.5f
        );

        m_mainLayer->addChild(
            m_selectedCategory,
            5
        );


        // ====================================================
        // CATEGORY MENU
        // ====================================================

        m_categories = CCMenu::create();

        m_categories->setPosition(
            0.f,
            0.f
        );

        m_mainLayer->addChild(
            m_categories,
            100
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


        const float startY = 303.f;
        const float gap = 27.f;


        for (int i = 0; i < 10; i++) {

            createCategory(
                categories[i],
                i,
                85.f,
                startY - i * gap
            );
        }


        // ====================================================
        // FEATURE LABELS
        // ====================================================

        m_featureLabels = CCLayer::create();

        m_featureLabels->setPosition(
            0.f,
            0.f
        );

        m_mainLayer->addChild(
            m_featureLabels,
            20
        );


        // ====================================================
        // FEATURE MENU
        // ====================================================

        m_features = CCMenu::create();

        m_features->setPosition(
            0.f,
            0.f
        );

        m_mainLayer->addChild(
            m_features,
            100
        );


        // ====================================================
        // TOP MENU
        // ====================================================

        auto topMenu = CCMenu::create();

        topMenu->setPosition(
            0.f,
            0.f
        );

        m_mainLayer->addChild(
            topMenu,
            500
        );


        // ====================================================
        // TOP ARROW
        // ====================================================

        auto arrowSprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_arrow01_001.png"
            );

        if (arrowSprite) {

            arrowSprite->setScale(
                0.45f
            );

            arrowSprite->setRotation(
                -90.f
            );

            auto arrow =
                CCMenuItemSpriteExtra::create(
                    arrowSprite,
                    this,
                    menu_selector(
                        ExternalHackMenu::onExit
                    )
                );

            arrow->setPosition(
                W / 2.f,
                H - 8.f
            );

            topMenu->addChild(
                arrow
            );
        }


        // ====================================================
        // EXIT
        // ====================================================

        auto exitSprite = ButtonSprite::create(
            "EXIT",
            55,
            true,
            "bigFont.fnt",
            "GJ_button_06.png",
            18.f,
            0.42f
        );

        auto exit =
            CCMenuItemSpriteExtra::create(
                exitSprite,
                this,
                menu_selector(
                    ExternalHackMenu::onExit
                )
            );

        exit->setPosition(
            W - 48.f,
            25.f
        );

        topMenu->addChild(
            exit
        );


        // ====================================================
        // FIRST PAGE
        // ====================================================

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

        auto label = CCLabelBMFont::create(
            name,
            "bigFont.fnt"
        );

        label->setScale(
            0.29f
        );


        auto button =
            CCMenuItemLabel::create(
                label,
                this,
                menu_selector(
                    ExternalHackMenu::onCategory
                )
            );


        button->setTag(
            id
        );


        button->setContentSize({
            116.f,
            25.f
        });


        button->setPosition(
            x,
            y
        );


        m_categories->addChild(
            button
        );
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

        bool state = m_states[id];


        // ====================================================
        // CHECKBOX
        // ====================================================

        auto off =
            CCSprite::createWithSpriteFrameName(
                "GJ_checkOff_001.png"
            );

        auto on =
            CCSprite::createWithSpriteFrameName(
                "GJ_checkOn_001.png"
            );


        if (off && on) {

            auto toggle =
                CCMenuItemToggler::create(
                    off,
                    on,
                    this,
                    menu_selector(
                        ExternalHackMenu::onToggle
                    )
                );


            toggle->setTag(
                id
            );


            toggle->setScale(
                0.43f
            );


            toggle->toggle(
                state
            );


            toggle->setPosition(
                x,
                y
            );


            m_features->addChild(
                toggle
            );
        }


        // ====================================================
        // NAME
        // ====================================================

        auto label =
            CCLabelBMFont::create(
                name,
                "bigFont.fnt"
            );


        label->setAnchorPoint({
            0.f,
            0.5f
        });


        label->setPosition(
            x + 15.f,
            y
        );


        label->setScale(
            0.25f
        );


        m_featureLabels->addChild(
            label
        );


        // ====================================================
        // PLUS
        // ====================================================

        auto plusLabel =
            CCLabelBMFont::create(
                "+",
                "goldFont.fnt"
            );


        plusLabel->setScale(
            0.42f
        );


        auto plus =
            CCMenuItemLabel::create(
                plusLabel,
                this,
                menu_selector(
                    ExternalHackMenu::onPlus
                )
            );


        plus->setTag(
            id
        );


        plus->setPosition(
            x + 138.f,
            y
        );


        m_features->addChild(
            plus
        );


        // ====================================================
        // INFO
        // ====================================================

        auto infoSprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_infoIcon_001.png"
            );


        if (infoSprite) {

            auto info =
                CCMenuItemSpriteExtra::create(
                    infoSprite,
                    this,
                    menu_selector(
                        ExternalHackMenu::onInfo
                    )
                );


            info->setTag(
                id
            );


            info->setScale(
                0.38f
            );


            info->setPosition(
                x + 158.f,
                y
            );


            m_features->addChild(
                info
            );
        }
    }


    // ========================================================
    // DIVIDER
    // ========================================================

    void createDivider(
        float y
    ) {

        auto divider =
            CCLayerColor::create(
                {40, 65, 82, 130}
            );


        divider->setContentSize({
            335.f,
            1.f
        });


        divider->setPosition(
            180.f,
            y
        );


        m_featureLabels->addChild(
            divider
        );
    }


    // ========================================================
    // LEVEL
    // ========================================================

    void showLevel() {

        m_featureLabels->removeAllChildren();
        m_features->removeAllChildren();


        const float left = 180.f;
        const float right = 350.f;

        const float top = 285.f;
        const float gap = 28.f;


        createFeature(
            "NOCLIP",
            1,
            left,
            top
        );

        createFeature(
            "SHOW HITBOXES",
            2,
            left,
            top - gap
        );

        createFeature(
            "HITBOX TRAIL",
            3,
            left,
            top - gap * 2
        );

        createFeature(
            "SHOW TRAJECTORY",
            4,
            left,
            top - gap * 3
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
            top - gap * 6
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
            top - gap * 2
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
            top - gap * 5
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


        createDivider(268.f);
        createDivider(212.f);
        createDivider(156.f);
        createDivider(100.f);
    }


    // ========================================================
    // UNIVERSAL
    // ========================================================

    void showUniversal() {

        m_featureLabels->removeAllChildren();
        m_features->removeAllChildren();


        const float left = 180.f;
        const float right = 350.f;

        const float top = 285.f;
        const float gap = 28.f;


        createFeature(
            "NO SHADERS",
            20,
            left,
            top
        );

        createFeature(
            "NO PARTICLES",
            21,
            left,
            top - gap
        );

        createFeature(
            "NO SHAKE",
            22,
            left,
            top - gap * 2
        );

        createFeature(
            "NO TRAIL",
            23,
            left,
            top - gap * 3
        );

        createFeature(
            "NO CAMERA MOVE",
            24,
            left,
            top - gap * 4
        );

        createFeature(
            "NO CAMERA ZOOM",
            25,
            left,
            top - gap * 5
        );

        createFeature(
            "NO DEATH EFFECT",
            26,
            left,
            top - gap * 6
        );

        createFeature(
            "PRACTICE MUSIC",
            27,
            left,
            top - gap * 7
        );


        createFeature(
            "FPS BYPASS",
            28,
            right,
            top
        );

        createFeature(
            "TPS BYPASS",
            29,
            right,
            top - gap
        );

        createFeature(
            "LOW DETAIL MODE",
            30,
            right,
            top - gap * 2
        );

        createFeature(
            "NO GLOW",
            31,
            right,
            top - gap * 3
        );

        createFeature(
            "NO BLENDING",
            32,
            right,
            top - gap * 4
        );

        createFeature(
            "HIDE PAUSE",
            33,
            right,
            top - gap * 5
        );
    }


    // ========================================================
    // SPEEDHACK
    // ========================================================

    void showSpeedhack() {

        m_featureLabels->removeAllChildren();
        m_features->removeAllChildren();


        const float left = 180.f;
        const float right = 350.f;

        const float top = 285.f;
        const float gap = 28.f;


        createFeature(
            "SPEEDHACK",
            40,
            left,
            top
        );

        createFeature(
            "0.5X SPEED",
            41,
            left,
            top - gap
        );

        createFeature(
            "1.5X SPEED",
            42,
            left,
            top - gap * 2
        );

        createFeature(
            "2X SPEED",
            43,
            left,
            top - gap * 3
        );

        createFeature(
            "3X SPEED",
            44,
            left,
            top - gap * 4
        );

        createFeature(
            "4X SPEED",
            45,
            left,
            top - gap * 5
        );


        createFeature(
            "CUSTOM SPEED",
            46,
            right,
            top
        );

        createFeature(
            "FREEZE",
            47,
            right,
            top - gap
        );
    }


    // ========================================================
    // OTHER CATEGORIES
    // ========================================================

    void showCategoryTitle(
        int id
    ) {

        m_featureLabels->removeAllChildren();
        m_features->removeAllChildren();


        const char* title = "CATEGORY";


        if (id == 2)
            title = "CREATOR";

        else if (id == 3)
            title = "COSMETIC";

        else if (id == 5)
            title = "ICON EFFECTS";

        else if (id == 6)
            title =