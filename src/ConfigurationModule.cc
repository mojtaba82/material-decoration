/*
 * Copyright (C) 2020 Chris Holland <zrenfire@gmail.com>
 * Copyright (C) 2012 Martin Gräßlin <mgraesslin@kde.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// own
#include "ConfigurationModule.h"
#include "Material.h"
#include "InternalSettings.h"

// KF
#include <KColorButton>
#include <KConfigSkeleton>
#include <KCoreConfigSkeleton>
#include <KCModule>
#include <KLocalizedString>
#include <KSharedConfig>

// KDecoration
#include <KDecoration2/DecorationButton>

// Qt
#include <QDebug>

// QWidget
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>

namespace Material
{


ConfigurationModule::ConfigurationModule(QWidget *parent, const QVariantList &args)
    : KCModule(parent, args)
    , m_buttonSize(InternalSettings::ButtonDefault)
    , m_shadowSize(InternalSettings::ShadowVeryLarge)
{
    init();
}

void ConfigurationModule::init()
{
    KCoreConfigSkeleton *skel = new KCoreConfigSkeleton(KSharedConfig::openConfig(s_configFilename), this);
    skel->setCurrentGroup(QStringLiteral("Windeco"));

    // See fr.po for the messages we can reuse from breeze:
    // https://websvn.kde.org/*checkout*/trunk/l10n-kf5/fr/messages/breeze/breeze_kwin_deco.po

    //--- Tabs
    QTabWidget *tabWidget = new QTabWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    //--- General
    QWidget *generalTab = new QWidget(tabWidget);
    tabWidget->addTab(generalTab, i18nd("breeze_kwin_deco", "General"));
    QFormLayout *generalForm = new QFormLayout(generalTab);
    generalTab->setLayout(generalForm);

    QComboBox *buttonSizes = new QComboBox(generalTab);
    buttonSizes->addItem(i18nd("breeze_kwin_deco", "Tiny"));
    buttonSizes->addItem(i18ndc("breeze_kwin_deco", "@item:inlistbox Button size:", "Small"));
    buttonSizes->addItem(i18ndc("breeze_kwin_deco", "@item:inlistbox Button size:", "Medium"));
    buttonSizes->addItem(i18ndc("breeze_kwin_deco", "@item:inlistbox Button size:", "Large"));
    buttonSizes->addItem(i18ndc("breeze_kwin_deco", "@item:inlistbox Button size:", "Very Large"));
    buttonSizes->setObjectName(QStringLiteral("kcfg_ButtonSize"));
    generalForm->addRow(i18nd("breeze_kwin_deco", "B&utton size:"), buttonSizes);

    QDoubleSpinBox *activeOpacity = new QDoubleSpinBox(generalTab);
    activeOpacity->setMinimum(0.0);
    activeOpacity->setMaximum(1.0);
    activeOpacity->setSingleStep(0.05);
    activeOpacity->setObjectName(QStringLiteral("kcfg_ActiveOpacity"));
    generalForm->addRow(i18n("Active Opacity:"), activeOpacity);

    QDoubleSpinBox *inactiveOpacity = new QDoubleSpinBox(generalTab);
    inactiveOpacity->setMinimum(0.0);
    inactiveOpacity->setMaximum(1.0);
    inactiveOpacity->setSingleStep(0.05);
    inactiveOpacity->setObjectName(QStringLiteral("kcfg_InactiveOpacity"));
    generalForm->addRow(i18n("Inactive Opacity:"), inactiveOpacity);


    //--- Animations
    QWidget *animationsTab = new QWidget(tabWidget);
    tabWidget->addTab(animationsTab, i18nd("breeze_kwin_deco", "Animations"));
    QFormLayout *animationsForm = new QFormLayout(animationsTab);
    animationsTab->setLayout(animationsForm);

    QCheckBox *animationsEnabled = new QCheckBox(animationsTab);
    animationsEnabled->setText(i18nd("breeze_kwin_deco", "Enable animations"));
    animationsEnabled->setObjectName(QStringLiteral("kcfg_AnimationsEnabled"));
    animationsForm->addRow(QStringLiteral(""), animationsEnabled);

    QSpinBox *animationsDuration = new QSpinBox(animationsTab);
    animationsDuration->setMinimum(0);
    animationsDuration->setMaximum(INT_MAX);
    animationsDuration->setSuffix(i18nd("breeze_kwin_deco", " ms"));
    animationsDuration->setObjectName(QStringLiteral("kcfg_AnimationsDuration"));
    animationsForm->addRow(i18nd("breeze_kwin_deco", "Animations:"), animationsDuration);


    //--- Shadows
    QWidget *shadowTab = new QWidget(tabWidget);
    tabWidget->addTab(shadowTab, i18nd("breeze_kwin_deco", "Shadows"));
    QFormLayout *shadowForm = new QFormLayout(shadowTab);
    shadowTab->setLayout(shadowForm);

    QComboBox *shadowSizes = new QComboBox(shadowTab);
    shadowSizes->addItem(i18ndc("breeze_kwin_deco", "@item:inlistbox Button size:", "None"));
    shadowSizes->addItem(i18ndc("breeze_kwin_deco", "@item:inlistbox Button size:", "Small"));
    shadowSizes->addItem(i18ndc("breeze_kwin_deco", "@item:inlistbox Button size:", "Medium"));
    shadowSizes->addItem(i18ndc("breeze_kwin_deco", "@item:inlistbox Button size:", "Large"));
    shadowSizes->addItem(i18ndc("breeze_kwin_deco", "@item:inlistbox Button size:", "Very Large"));
    shadowSizes->setObjectName(QStringLiteral("kcfg_ShadowSize"));
    shadowForm->addRow(i18nd("breeze_kwin_deco", "Si&ze:"), shadowSizes);

    QSpinBox *shadowStrength = new QSpinBox(shadowTab);
    shadowStrength->setMinimum(25);
    shadowStrength->setMaximum(255);
    // shadowStrength->setSuffix(i18nd("breeze_kwin_deco", "%"));
    shadowStrength->setObjectName(QStringLiteral("kcfg_ShadowStrength"));
    shadowForm->addRow(i18ndc("breeze_kwin_deco", "strength of the shadow (from transparent to opaque)", "S&trength:"), shadowStrength);

    KColorButton *shadowColor = new KColorButton(shadowTab);
    shadowColor->setObjectName(QStringLiteral("kcfg_ShadowColor"));
    shadowForm->addRow(i18nd("breeze_kwin_deco", "Color:"), shadowColor);
    
    //--- Margins
    QWidget *marginTab = new QWidget(tabWidget);
    tabWidget->addTab(marginTab, i18nd("breeze_kwin_deco", "Margins"));
    QFormLayout *marginForm = new QFormLayout(marginTab);
    marginTab->setLayout(marginForm);

    QSpinBox *marginLeft = new QSpinBox(marginTab);
    marginLeft->setMinimum(0);
    marginLeft->setMaximum(999);
    marginLeft->setObjectName(QStringLiteral("kcfg_MarginLeft"));
    marginForm->addRow(i18ndc("breeze_kwin_deco", "margin left", "Margin Left:"), marginLeft);
    
    QSpinBox *marginLeftMaximized = new QSpinBox(marginTab);
    marginLeftMaximized->setMinimum(0);
    marginLeftMaximized->setMaximum(999);
    marginLeftMaximized->setObjectName(QStringLiteral("kcfg_MarginLeftMaximized"));
    marginForm->addRow(i18ndc("breeze_kwin_deco", "margin left aximized", "Margin Left Maximized:"), marginLeftMaximized);
    
    QSpinBox *marginRight = new QSpinBox(marginTab);
    marginRight->setMinimum(0);
    marginRight->setMaximum(999);
    marginRight->setObjectName(QStringLiteral("kcfg_MarginRight"));
    marginForm->addRow(i18ndc("breeze_kwin_deco", "margin right", "Margin Right:"), marginRight);
    
    QSpinBox *marginRightMaximized = new QSpinBox(marginTab);
    marginRightMaximized->setMinimum(0);
    marginRightMaximized->setMaximum(999);
    marginRightMaximized->setObjectName(QStringLiteral("kcfg_MarginRightMaximized"));
    marginForm->addRow(i18ndc("breeze_kwin_deco", "margin right maximized", "Margin Right Maximized:"), marginRightMaximized);

    //--- Config Bindings
    skel->addItemInt(
        QStringLiteral("ButtonSize"),
        m_buttonSize,
        InternalSettings::ButtonDefault,
        QStringLiteral("ButtonSize")
    );
    skel->addItemDouble(
        QStringLiteral("ActiveOpacity"),
        m_activeOpacity,
        0.75,
        QStringLiteral("ActiveOpacity")
    );
    skel->addItemDouble(
        QStringLiteral("InactiveOpacity"),
        m_inactiveOpacity,
        0.85,
        QStringLiteral("InactiveOpacity")
    );
    skel->addItemBool(
        QStringLiteral("AnimationsEnabled"),
        m_animationsEnabled,
        true,
        QStringLiteral("AnimationsEnabled")
    );
    skel->addItemInt(
        QStringLiteral("AnimationsDuration"),
        m_animationsDuration,
        150,
        QStringLiteral("AnimationsDuration")
    );
    skel->addItemInt(
        QStringLiteral("ShadowSize"),
        m_shadowSize,
        InternalSettings::ShadowVeryLarge,
        QStringLiteral("ShadowSize")
    );
    skel->addItemInt(
        QStringLiteral("ShadowStrength"),
        m_shadowStrength,
        255,
        QStringLiteral("ShadowStrength")
    );
    skel->addItem(new KConfigSkeleton::ItemColor(
        skel->currentGroup(),
        QStringLiteral("ShadowColor"),
        m_shadowColor,
        QColor(33, 33, 33)
    ), QStringLiteral("ShadowColor"));
    skel->addItemInt(
        QStringLiteral("MarginLeft"),
        m_marginLeft,
        0,
        QStringLiteral("MarginLeft")
    );
    skel->addItemInt(
        QStringLiteral("MarginLeftMaximized"),
        m_marginLeftMaximized,
        0,
        QStringLiteral("MarginLeftMaximized")
    );
    skel->addItemInt(
        QStringLiteral("MarginRight"),
        m_marginRight,
        0,
        QStringLiteral("MarginRight")
    );
    skel->addItemInt(
        QStringLiteral("MarginRightMaximized"),
        m_marginRightMaximized,
        0,
        QStringLiteral("MarginRightMaximized")
    );

    //---
    addConfig(skel, this);
}

} // namespace Material
