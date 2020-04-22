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

// KF
#include <KCoreConfigSkeleton>
#include <KCModule>
#include <KLocalizedString>
#include <KSharedConfig>

// KDecoration
#include <KDecoration2/DecorationButton>

// Qt
#include <QDebug>
#include <QLoggingCategory>

// QWidget
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>

static const QLoggingCategory category("kdecoration.material");

namespace Material
{

static const QString s_configFilename = QStringLiteral("kdecoration_materialrc");
static const int s_indexMapper = 2;

ConfigurationModule::ConfigurationModule(QWidget *parent, const QVariantList &args)
    : KCModule(parent, args)
    , m_buttonSize(int(KDecoration2::BorderSize::Normal) - s_indexMapper)
{
    setLayout(new QVBoxLayout(this));
    init();
}

void ConfigurationModule::init()
{
    QWidget *form = new QWidget(this);
    form->setLayout(new QHBoxLayout(form));
    QComboBox *sizes = new QComboBox(form);
    sizes->addItem(i18nc("@item:inlistbox Button size:", "Tiny"));
    sizes->addItem(i18nc("@item:inlistbox Button size:", "Normal"));
    sizes->addItem(i18nc("@item:inlistbox Button size:", "Large"));
    sizes->addItem(i18nc("@item:inlistbox Button size:", "Very Large"));
    sizes->addItem(i18nc("@item:inlistbox Button size:", "Huge"));
    sizes->addItem(i18nc("@item:inlistbox Button size:", "Very Huge"));
    sizes->addItem(i18nc("@item:inlistbox Button size:", "Oversized"));
    sizes->setObjectName(QStringLiteral("kcfg_ButtonSize"));

    QLabel *label = new QLabel(i18n("Button size:"), form);
    label->setBuddy(sizes);
    form->layout()->addWidget(label);
    form->layout()->addWidget(sizes);

    layout()->addWidget(form);

    KCoreConfigSkeleton *skel = new KCoreConfigSkeleton(KSharedConfig::openConfig(s_configFilename), this);
    skel->setCurrentGroup(QStringLiteral("General"));
    skel->addItemInt(QStringLiteral("ButtonSize"),
                     m_buttonSize,
                     int(KDecoration2::BorderSize::Normal) - s_indexMapper,
                     QStringLiteral("ButtonSize"));
    addConfig(skel, form);
}

} // namespace Material
