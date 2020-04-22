/*
 * Copyright (C) 2020 Chris Holland <zrenfire@gmail.com>
 * Copyright (C) 2018 Vlad Zagorodniy <vladzzag@gmail.com>
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

#pragma once

// own
#include "AppMenuButtonGroup.h"

// KDecoration
#include <KDecoration2/Decoration>
#include <KDecoration2/DecorationButton>
#include <KDecoration2/DecorationButtonGroup>

// Qt
#include <QVariant>

namespace Material
{

class Button;
class TextButton;
class MenuOverflowButton;

class Decoration : public KDecoration2::Decoration
{
    Q_OBJECT

public:
    Decoration(QObject *parent = nullptr, const QVariantList &args = QVariantList());
    ~Decoration() override;

    void paint(QPainter *painter, const QRect &repaintRegion) override;

public slots:
    void init() override;
    void reconfigure();

private:
    void updateBorders();
    void updateResizeBorders();
    void updateTitleBar();
    void updateButtonHeight(KDecoration2::DecorationButtonGroup *buttonGroup, int titleBarHeight);
    void updateButtonsGeometry();
    void updateShadow();

    int buttonHeight() const;
    int titleBarHeight() const;
    int captionMinWidth() const;
    int getTextWidth(const QString text, bool showMnemonic = false) const;
    QPoint windowPos() const;

    QColor titleBarBackgroundColor() const;
    QColor titleBarForegroundColor() const;

    void paintFrameBackground(QPainter *painter, const QRect &repaintRegion) const;
    void paintTitleBarBackground(QPainter *painter, const QRect &repaintRegion) const;
    void paintCaption(QPainter *painter, const QRect &repaintRegion) const;
    void paintButtons(QPainter *painter, const QRect &repaintRegion) const;

    KDecoration2::DecorationButtonGroup *m_leftButtons;
    KDecoration2::DecorationButtonGroup *m_rightButtons;
    AppMenuButtonGroup *m_menuButtons;

    KDecoration2::BorderSize m_buttonSize;

    friend class AppMenuButtonGroup;
    friend class Button;
    friend class TextButton;
    // friend class MenuOverflowButton;
};

} // namespace Material
