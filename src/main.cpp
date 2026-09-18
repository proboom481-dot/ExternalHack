#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;


// ============================================================
// EXTERNALHACK UI
// ============================================================

class ExternalHackLayer : public CCLayerColor {
protected:

    CCMenu* m_categoryMenu = nullptr;
    CCMenu* m_featureMenu = nullptr;
    CCMenu* m_topMenu = nullptr;

    CCLayerColor* m_panel = nullptr;
    CCLayerColor* m_selectedCategory = nullptr;

    int m_category = 0;

    bool m_states[128] = {};


    // ========================================================
    // INIT
    // ========================================================

    bool init() {

        if (!CCLayerColor::initWithColor({0, 0, 0, 175}))
            return false;

        auto screen =
            CCDirector::sharedDirector()->getWinSize();

        float panelW = screen.width * 0.78f;
        float panelH = screen.height * 0.80f;

        if (panelW > 1050.f)
            panelW = 1050.f;

        if (panelH > 650.f)
            panelH = 650.f;

        if (panelW < 650.f)
            panelW = screen.width * 0.88f;

        if (panelH < 420.f)
            panelH = screen.height * 0.88f;


        // ====================================================
        // BORDER
        // ====================================================

        auto border = CCLayerColor::create(
            {35, 210, 220, 255}
        );

        border->setContentSize({
            panelW,
            panelH
        });

        border->setPosition({
            (screen.width - panelW) / 2.f,
            (screen.height - panelH) / 2.f
        });

        this->addChild(
            border,
            1
        );


        // ====================================================
        // PANEL
        // ====================================================

        auto panel = CCLayerColor::create(
            {12, 18, 27, 252}
        );

        panel->setContentSize({
            panelW - 4.f,
            panelH - 4.f
        });

        panel->setPosition({
            2.f,
            2.f
        });

        border->addChild(
            panel,
            2
        );

        m_panel = panel;


        // ====================================================
        // HEADER
        // ====================================================

        auto header = CCLayerColor::create(
            {17, 27, 39, 255}
        );

        header->setContentSize({
            panelW - 4.f,
            55.f
        });

        header->setPosition({
            0.f,
            panelH - 59.f
        });

        panel->addChild(
            header,
            3
        );


        auto headerLine = CCLayerColor::create(
            {35, 210, 220, 255}
        );

        headerLine->setContentSize({
            panelW - 4.f,
            2.f
        });

        headerLine->setPosition(
            0.f,
            0.f
        );

        header->addChild(
            headerLine
        );


        // ====================================================
        // TITLE
        // ====================================================

        auto title = CCLabelBMFont::create(
            "EXTERNALHACK",
            "goldFont.fnt"
        );

        title->setPosition({
            panelW / 2.f,
            panelH - 27.f
        });

        title->setScale(
            0.48f
        );

        panel->addChild(
            title,
            20
        );


        auto version = CCLabelBMFont::create(
            "v1.0.0",
            "bigFont.fnt"
        );

        version->setPosition({
            panelW / 2.f,
            panelH - 44.f
        });

        version->setScale(
            0.20f
        );

        panel->addChild(
            version,
            20
        );


        // ====================================================
        // TOP MENU
        // ====================================================

        m_topMenu = CCMenu::create();

        m_topMenu->setPosition(
            0.f,
            0.f
        );

        panel->addChild(
            m_topMenu,
            1000
        );


        // ====================================================
        // ARROW
        // ====================================================

        auto arrowSprite =
            CCSprite::createWithSpriteFrameName(
                "GJ_arrow01_001.png"
            );

        if (arrowSprite) {

            arrowSprite->setScale(
                0.50f
            );

            arrowSprite->setRotation(
                -90.f
            );

            auto arrow = CCMenuItemSpriteExtra::create(
                arrowSprite,
                this,
                menu_selector(
                    ExternalHackLayer::onExit
                )
            );

            arrow->setPosition({
                panelW / 2.f,
                panelH - 8.f
            });

            m_topMenu->addChild(
                arrow
            );
        }


        // ====================================================
        // EXIT
        // ====================================================

        auto exitLabel = CCLabelBMFont::create(
            "EXIT",
            "goldFont.fnt"
        );

        exitLabel->setScale(
            0.38f
        );

        auto exit = CCMenuItemLabel::create(
            exitLabel,
            this,
            menu_selector(
                ExternalHackLayer::onExit
            )
        );

        exit->setPosition({
            panelW - 42.f,
            20.f
        });

        m_topMenu->addChild(
            exit
        );


        // ====================================================
        // SIDEBAR
        // ====================================================

        const float sidebarW = 145.f;

        auto sidebar = CCLayerColor::create(
            {15, 24, 36, 255}
        );

        sidebar->setContentSize({
            sidebarW,
            panelH - 75.f
        });

        sidebar->setPosition({
            8.f,
            38.f
        });

        panel->addChild(
            sidebar,
            4
        );


        // ====================================================
        // SEPARATOR
        // ====================================================

        auto separator = CCLayerColor::create(
            {35, 210, 220, 255}
        );

        separator->setContentSize({
            2.f,
            panelH - 75.f
        });

        separator->setPosition({
            sidebarW + 8.f,
            38.f
        });

        panel->addChild(
            separator,
            5
        );


        // ====================================================
        // SELECTED CATEGORY
        // ====================================================

        m_selectedCategory = CCLayerColor::create(
            {30, 175, 185, 100}
        );

        m_selectedCategory->setContentSize({
            sidebarW - 20.f,
            28.f
        });

        m_selectedCategory->setPosition({
            18.f,
            panelH - 106.f
        });

        panel->addChild(
            m_selectedCategory,
            6
        );


        // ====================================================
        // CATEGORY MENU
        // ====================================================

        m_categoryMenu = CCMenu::create();

        m_categoryMenu->setPosition(
            0.f,
            0.f
        );

        panel->addChild(
            m_categoryMenu,
            20
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


        float categoryStartY =
            panelH - 92.f;


        for (int i = 0; i < 10; i++) {

            createCategory(
                categories[i],
                i,
                88.f,
                categoryStartY - i * 32.f
            );
        }


        // ====================================================
        // FEATURE MENU
        // ====================================================

        m_featureMenu = CCMenu::create();

        m_featureMenu->setPosition(
            0.f,
            0.f
        );

        panel->addChild(
            m_featureMenu,
            50
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

        auto label = CCLabelBMFont::create(
            name,
            "bigFont.fnt"
        );

        label->setScale(
            0.28f
        );

        auto button = CCMenuItemLabel::create(
            label,
            this,
            menu_selector(
                ExternalHackLayer::onCategory
            )
        );

        button->setTag(
            id
        );

        button->setPosition({
            x,
            y
        });

        m_categoryMenu->addChild(
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

            auto toggle = CCMenuItemToggler::create(
                off,
                on,
                this,
                menu_selector(
                    ExternalHackLayer::onToggle
                )
            );

            toggle->setTag(
                id
            );

            toggle->setScale(
                0.45f
            );

            toggle->toggle(
                state
            );

            toggle->setPosition({
                x,
                y
            });

            m_featureMenu->addChild(
                toggle
            );
        }


        // ====================================================
        // NAME
        // ====================================================

        auto label = CCLabelBMFont::create(
            name,
            "bigFont.fnt"
        );

        label->setAnchorPoint({
            0.f,
            0.5f
        });

        label->setScale(
            0.255f
        );

        label->setPosition({
            x + 18.f,
            y
        });

        m_featureMenu->addChild(
            label
        );


        // ====================================================
        // PLUS
        // ====================================================

        auto plusLabel = CCLabelBMFont::create(
            "+",
            "goldFont.fnt"
        );

        plusLabel->setScale(
            0.38f
        );

        auto plus = CCMenuItemLabel::create(
            plusLabel,
            this,
            menu_selector(
                ExternalHackLayer::onPlus
            )
        );

        plus->setTag(
            id
        );

        plus->setPosition({
            x + 132.f,
            y
        });

        m_featureMenu->addChild(
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

            auto info = CCMenuItemSpriteExtra::create(
                infoSprite,
                this,
                menu_selector(
                    ExternalHackLayer::onInfo
                )
            );

            info->setTag(
                id
            );

            info->setScale(
                0.38f
            );

            info->setPosition({
                x + 151.f,
                y
            });

            m_featureMenu->addChild(
                info
            );
        }
    }


    // ========================================================
    // LEVEL
    // ========================================================

    void showLevel() {

        const float leftX = 180.f;
        const float rightX = 435.f;

        const float startY = 295.f;
        const float gap = 32.f;


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
            startY - gap
        );

        createFeature(
            "HITBOX TRAIL",
            3,
            leftX,
            startY - gap * 2
        );

        createFeature(
            "SHOW TRAJECTORY",
            4,
            leftX,
            startY - gap * 3
        );

        createFeature(
            "ACCURATE HITBOXES",
            5,
            leftX,
            startY - gap * 4
        );

        createFeature(
            "AUTO COLLECT COINS",
            6,
            leftX,
            startY - gap * 5
        );

        createFeature(
            "AUTOCLICKER",
            7,
            leftX,
            startY - gap * 6
        );

        createFeature(
            "CLASSIC PERCENTAGE",
            8,
            leftX,
            startY - gap * 7
        );


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
            startY - gap
        );

        createFeature(
            "STARTPOS SWITCHER",
            12,
            rightX,
            startY - gap * 2
        );

        createFeature(
            "ACCURATE PERCENTAGE",
            13,
            rightX,
            startY - gap * 3
        );

        createFeature(
            "PLATFORMER MODE",
            14,
            rightX,
            startY - gap * 4
        );

        createFeature(
            "AUTO PRACTICE",
            15,
            rightX,
            startY - gap * 5
        );

        createFeature(
            "BEST PERCENTAGE",
            16,
            rightX,
            startY - gap * 6
        );

        createFeature(
            "COIN TRACERS",
            17,
            rightX,
            startY - gap * 7
        );
    }


    // ========================================================
    // OTHER CATEGORIES
    // ========================================================

    void showOtherCategory(int id) {

        const float leftX = 180.f;
        const float rightX = 435.f;

        const float startY = 295.f;
        const float gap = 32.f;


        if (id == 1) {

            createFeature(
                "NO SHADERS",
                20,
                leftX,
                startY
            );

            createFeature(
                "NO PARTICLES",
                21,
                leftX,
                startY - gap
            );

            createFeature(
                "NO SHAKE",
                22,
                leftX,
                startY - gap * 2
            );

            createFeature(
                "NO TRAIL",
                23,
                leftX,
                startY - gap * 3
            );

            createFeature(
                "NO CAMERA MOVE",
                24,
                leftX,
                startY - gap * 4
            );

            createFeature(
                "NO CAMERA ZOOM",
                25,
                leftX,
                startY - gap * 5
            );

            createFeature(
                "NO DEATH EFFECT",
                26,
                leftX,
                startY - gap * 6
            );

            createFeature(
                "PRACTICE MUSIC",
                27,
                leftX,
                startY - gap * 7
            );


            createFeature(
                "FPS BYPASS",
                28,
                rightX,
                startY
            );

            createFeature(
                "TPS BYPASS",
                29,
                rightX,
                startY - gap
            );

            createFeature(
                "FORCE LOW DETAIL",
                30,
                rightX,
                startY - gap * 2
            );

            createFeature(
                "NO GLOW",
                31,
                rightX,
                startY - gap * 3
            );

            createFeature(
                "NO BLENDING",
                32,
                rightX,
                startY - gap * 4
            );

            createFeature(
                "HIDE PAUSE BUTTON",
                33,
                rightX,
                startY - gap * 5
            );
        }

        else if (id == 4) {

            createFeature(
                "SPEEDHACK",
                40,
                leftX,
                startY
            );

            createFeature(
                "0.5X SPEED",
                41,
                leftX,
                startY - gap
            );

            createFeature(
                "1.5X SPEED",
                42,
                leftX,
                startY - gap * 2
            );

            createFeature(
                "2X SPEED",
                43,
                leftX,
                startY - gap * 3
            );

            createFeature(
                "3X SPEED",
                44,
                leftX,
                startY - gap * 4
            );

            createFeature(
                "4X SPEED",
                45,
                leftX,
                startY - gap * 5
            );


            createFeature(
                "CUSTOM SPEED",
                46,
                rightX,
                startY
            );

            createFeature(
                "FREEZE",
                47,
                rightX,
                startY - gap
            );
        }

        else {

            const char* title = "CATEGORY";


            switch (id) {

                case 2:
                    title = "CREATOR";
                    break;

                case 3:
                    title = "COSMETIC";
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


            auto titleLabel =
                CCLabelBMFont::create(
                    title,
                    "goldFont.fnt"
                );

            titleLabel->setPosition({
                390.f,
                210.f
            });

            titleLabel->setScale(
                0.48f
            );

            m_featureMenu->addChild(
                titleLabel
            );


            auto text =
                CCLabelBMFont::create(
                    "MORE FEATURES COMING",
     