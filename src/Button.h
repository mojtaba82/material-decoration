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

// KDecoration
#include <KDecoration2/Decoration>
#include <KDecoration2/DecorationButton>

// Qt
#include <QVariantAnimation>

namespace Material
{

class Decoration;

class Button : public KDecoration2::DecorationButton
{
    Q_OBJECT

public:
    Button(KDecoration2::DecorationButtonType type, Decoration *decoration, QObject *parent = nullptr);
    ~Button() override;

    Q_PROPERTY(bool animationEnabled READ animationEnabled WRITE setAnimationEnabled NOTIFY animationEnabledChanged)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration NOTIFY animationDurationChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(qreal transitionValue READ transitionValue WRITE setTransitionValue NOTIFY transitionValueChanged)

    // Passed to DecorationButtonGroup in Decoration
    static KDecoration2::DecorationButton *create(KDecoration2::DecorationButtonType type, KDecoration2::Decoration *decoration, QObject *parent = nullptr);

    // This is called by:
    // registerPlugin<Material::Button>(QStringLiteral("button"))
    // It is needed to create buttons for applet-window-buttons.
    explicit Button(QObject *parent, const QVariantList &args);


    void paint(QPainter *painter, const QRect &repaintRegion) override;
    virtual void paintIcon(QPainter *painter, const QRectF &iconRect, const qreal gridUnit);

    virtual void setHeight(int buttonHeight);

    virtual qreal iconLineWidth(const qreal gridUnit) const;
    void setPenWidth(QPainter *painter, const qreal gridUnit, const qreal scale);

    virtual QColor backgroundColor() const;
    virtual QColor foregroundColor() const;

    bool animationEnabled() const;
    void setAnimationEnabled(bool value);

    int animationDuration() const;
    void setAnimationDuration(int duration);

    qreal opacity() const;
    void setOpacity(qreal value);

    qreal transitionValue() const;
    void setTransitionValue(qreal value);

private Q_SLOTS:
    void updateAnimationState(bool hovered);

signals:
    void animationEnabledChanged();
    void animationDurationChanged();
    void opacityChanged();
    void transitionValueChanged(qreal);

private:
    bool m_animationEnabled;
    QVariantAnimation *m_animation;
    qreal m_opacity;
    qreal m_transitionValue;
    bool m_isGtkButton;
};

} // namespace Material
