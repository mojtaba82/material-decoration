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
#include "InternalSettings.h"

// KDecoration
#include <KDecoration2/Decoration>
#include <KDecoration2/DecorationButton>
#include <KDecoration2/DecorationButtonGroup>

// Qt
#include <QHoverEvent>
#include <QMouseEvent>
#include <QSharedPointer>
#include <QWheelEvent>
#include <QVariant>

// X11
#include <xcb/xcb.h>


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

protected:
    void hoverEnterEvent(QHoverEvent *event) override;
    void hoverMoveEvent(QHoverEvent *event) override;
    void hoverLeaveEvent(QHoverEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void onSectionUnderMouseChanged(const Qt::WindowFrameSection value);

private:
    void updateBorders();
    void updateResizeBorders();
    void updateTitleBar();
    void updateTitleBarHoverState();
    void setButtonGroupHeight(KDecoration2::DecorationButtonGroup *buttonGroup, int buttonHeight);
    void updateButtonHeight();
    void updateButtonsGeometry();
    void setButtonGroupAnimation(KDecoration2::DecorationButtonGroup *buttonGroup, bool enabled, int duration);
    void updateButtonAnimation();
    void updateShadow();

    bool animationsEnabled() const;
    int animationsDuration() const;
    int buttonPadding() const;
    int titleBarHeight() const;
    int appMenuCaptionSpacing() const;
    int captionMinWidth() const;

    bool titleBarIsHovered() const;
    int getTextWidth(const QString text, bool showMnemonic = false) const;
    QPoint windowPos() const;

    void initDragMove(const QPoint pos);
    void resetDragMove();
    bool dragMoveTick(const QPoint pos);
    void sendMoveEvent(const QPoint pos);

    QColor titleBarBackgroundColor() const;
    QColor titleBarForegroundColor() const;

    void paintFrameBackground(QPainter *painter, const QRect &repaintRegion) const;
    void paintTitleBarBackground(QPainter *painter, const QRect &repaintRegion) const;
    void paintCaption(QPainter *painter, const QRect &repaintRegion) const;
    void paintButtons(QPainter *painter, const QRect &repaintRegion) const;

    KDecoration2::DecorationButtonGroup *m_leftButtons;
    KDecoration2::DecorationButtonGroup *m_rightButtons;
    AppMenuButtonGroup *m_menuButtons;

    QSharedPointer<InternalSettings> m_internalSettings;

    QPoint m_pressedPoint;
    xcb_atom_t m_moveResizeAtom = 0;

    friend class AppMenuButtonGroup;
    friend class Button;
    friend class AppIconButton;
    friend class AppMenuButton;
    friend class TextButton;
    // friend class MenuOverflowButton;
};

} // namespace Material
