/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVisualization module.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include "q3dtheme_p.h"

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

/*!
 * \class Q3DTheme
 * \inmodule QtDataVisualization
 * \brief Q3DTheme class provides a visual style for graphs.
 * \since Qt Data Visualization 1.0
 *
 * Q3DTheme is used to specify visual properties that affect the whole graph. There are several
 * built-in themes that can be used directly, or be modified freely. User can also create a theme
 * from scratch using \c ThemeUserDefined. Creating a theme using the default constructor
 * produces a new user-defined theme.
 *
 * \section1 Properties controlled by theme
 * \table
 *   \header
 *     \li Property
 *     \li Effect
 *     \li Default in ThemeUserDefined
 *   \row
 *     \li ambientLightStrength
 *     \li The strength of the ambient light in the graph. This affects how evenly and brightly the
 *         colors are shown throughout the graph regardless of light position.
 *     \li 0.25
 *   \row
 *     \li backgroundColor
 *     \li Color of the graph background.
 *     \li Qt::black
 *   \row
 *     \li backgroundEnabled
 *     \li Is the graph background drawn or not.
 *     \li true
 *   \row
 *     \li baseColor
 *     \li The color for the objects in the graph. The color in this property is used if colorStyle
 *         is ColorStyleUniform. This can be overridden by setting the baseColor explicitly in
 *         series.
 *     \li Qt::white
 *   \row
 *     \li baseGradient
 *     \li The gradient for the objects in the graph. The gradient in this property is used if
 *         colorStyle is ColorStyleObjectGradient or ColorStyleRangeGradient. This can be overridden
 *         by setting the baseGradient explicitly in series.
 *     \li QLinearGradient(). Essentially fully black.
 *   \row
 *     \li colorStyle
 *     \li The color style of the objects in the graph. See ColorStyle for detailed description of
 *         the styles. This can be overridden by setting the colorStyle explicitly in series.
 *     \li ColorStyleUniform
 *   \row
 *     \li \l font
 *     \li The font to be used for labels.
 *     \li QFont()
 *   \row
 *     \li gridEnabled
 *     \li Is the grid on the background drawn or not. This affects all grid lines.
 *     \li true
 *   \row
 *     \li gridLineColor
 *     \li The color for the grid lines.
 *     \li Qt::white
 *   \row
 *     \li highlightLightStrength
 *     \li The specular light strength for highlighted objects.
 *     \li 7.5
 *   \row
 *     \li labelBackgroundColor
 *     \li The color of the label background. This property has no effect if labelBackgroundEnabled
 *         is \c false.
 *     \li Qt::gray
 *   \row
 *     \li labelBackgroundEnabled
 *     \li Are the labels to be drawn with a background using labelBackgroundColor (including alpha),
 *         or with a fully transparent background. Labels with background are drawn to equal sizes
 *         per axis based on the longest label, and the text is centered in it. Labels without
 *         background are drawn as is and are left/right aligned based on their position in the
 *         graph.
 *     \li true
 *   \row
 *     \li labelBorderEnabled
 *     \li Are the labels to be drawn with a border or not. This property affects only labels with
 *         a background.
 *     \li true
 *   \row
 *     \li labelTextColor
 *     \li The color for the font used in labels.
 *     \li Qt::white
 *   \row
 *     \li lightColor
 *     \li The color of the specular light. Doesn't affect ambient light. \note Not yet supported
 *         in technology preview.
 *     \li Qt::white
 *   \row
 *     \li lightStrength
 *     \li The strength of the specular light in the graph. This affects the light specified in
 *         Q3DScene.
 *     \li 5.0
 *   \row
 *     \li multiHighlightColor
 *     \li The color to be used for highlighted objects, if \l{Q3DBars::selectionMode}{selectionMode}
 *         of the graph has \c QDataVis::SelectionRow or \c QDataVis::SelectionColumn flag set.
 *     \li Qt::blue
 *   \row
 *     \li multiHighlightGradient
 *     \li The gradient to be used for highlighted objects, if \l{Q3DBars::selectionMode}{selectionMode}
 *         of the graph has \c QDataVis::SelectionRow or \c QDataVis::SelectionColumn flag set.
 *     \li QLinearGradient(). Essentially fully black.
 *   \row
 *     \li singleHighlightColor
 *     \li The color to be used for a highlighted object, if \l{Q3DBars::selectionMode}{selectionMode}
 *         of the graph has \c QDataVis::SelectionItem flag set.
 *     \li Qt::red
 *   \row
 *     \li singleHighlightGradient
 *     \li The gradient to be used for a highlighted object, if \l{Q3DBars::selectionMode}{selectionMode}
 *         of the graph has \c QDataVis::SelectionItem flag set.
 *     \li QLinearGradient(). Essentially fully black.
 *   \row
 *     \li windowColor
 *     \li The color of the window the graph is drawn into.
 *     \li Qt::black
 * \endtable
 *
 * \section1 Usage examples
 *
 * Creating a built-in theme without any modifications:
 *
 * \snippet doc_src_q3dtheme.cpp 0
 *
 * Creating a built-in theme and modifying some properties:
 *
 * \snippet doc_src_q3dtheme.cpp 1
 *
 * Creating a user-defined theme:
 *
 * \snippet doc_src_q3dtheme.cpp 2
 *
 * Creating a built-in theme and modifying some properties after it has been set:
 *
 * \snippet doc_src_q3dtheme.cpp 3
 *
 */

/*!
 * \enum Q3DTheme::ColorStyle
 *
 * Color styles.
 *
 * \value ColorStyleUniform
 *        Objects are rendered in a single color. The color used is specified in baseColor,
 *        singleHighlightColor and multiHighlightColor properties.
 * \value ColorStyleObjectGradient
 *        Objects are colored using a full gradient for each object regardless of object height. The
 *        gradient used is specified in baseGradient, singleHighlightGradient and
 *        multiHighlightGradient properties.
 * \value ColorStyleRangeGradient
 *        Objects are colored using a portion of the full gradient determined by the object's
 *        height and its position on the Y-axis. The gradient used is specified in baseGradient,
 *        singleHighlightGradient and multiHighlightGradient properties.
 */

/*!
 * \enum Q3DTheme::Theme
 *
 * Built-in themes.
 *
 * \value ThemeQt
 *        A light theme with green as the base color.
 * \value ThemePrimaryColors
 *        A light theme with yellow as the base color.
 * \value ThemeDigia
 *        A light theme with gray as the base color.
 * \value ThemeStoneMoss
 *        A medium dark theme with yellow as the base color.
 * \value ThemeArmyBlue
 *        A medium light theme with blue as the base color.
 * \value ThemeRetro
 *        A medium light theme with brown as the base color.
 * \value ThemeEbony
 *        A dark theme with white as the base color.
 * \value ThemeIsabelle
 *        A dark theme with yellow as the base color.
 * \value ThemeUserDefined
 *        A user-defined theme. See \l {Properties controlled by theme} for theme defaults.
 */

/*!
 * \qmltype Theme3D
 * \inqmlmodule QtDataVisualization
 * \since QtDataVisualization 1.0
 * \ingroup datavisualization_qml
 * \instantiates Q3DTheme
 * \brief A visual style for graphs.
 *
 * This type is used to specify visual properties that affect the whole graph. There are several
 * built-in themes that can be used directly, or be modified freely. User can also create a theme
 * from scratch using \c Theme3D.ThemeUserDefined.
 *
 * For a more complete description, see Q3DTheme.
 *
 * \section1 Usage examples
 *
 * Using a built-in theme without any modifications:
 *
 * \snippet doc_src_q3dtheme.cpp 4
 *
 * Using a built-in theme and modifying some properties:
 *
 * \snippet doc_src_q3dtheme.cpp 5
 *
 * Using a user-defined theme:
 *
 * \snippet doc_src_q3dtheme.cpp 6
 */

/*!
 * \qmlproperty Color Theme3D::baseColor
 *
 * Color to be used for all the objects in the graph. Has no immediate effect if colorStyle is not
 * \c Theme3D.ColorStyleUniform.
 */

/*!
 * \qmlproperty Color Theme3D::backgroundColor
 *
 * Color for the graph background.
 */

/*!
 * \qmlproperty Color Theme3D::windowColor
 *
 * Color for the application window.
 */

/*!
 * \qmlproperty Color Theme3D::labelTextColor
 *
 * Color for the font used for labels.
 */

/*!
 * \qmlproperty Color Theme3D::labelBackgroundColor
 *
 * Color for the label backgrounds. Has no effect if labelBackgroundEnabled is \c false.
 */

/*!
 * \qmlproperty Color Theme3D::gridLineColor
 *
 * Color for the grid lines.
 */

/*!
 * \qmlproperty Color Theme3D::singleHighlightColor
 *
 * Highlight color for a highlighted object. Used if \l{AbstractGraph3D::selectionMode}{selectionMode}
 * has \c AbstractGraph3D.SelectionItem flag set.
 */

/*!
 * \qmlproperty Color Theme3D::multiHighlightColor
 *
 * Highlight color for highlighted objects. Used if \l{AbstractGraph3D::selectionMode}{selectionMode}
 * has \c AbstractGraph3D.SelectionRow or \c AbstractGraph3D.SelectionColumn flag set.
 */

/*!
 * \qmlproperty Color Theme3D::lightColor
 *
 * Color for the specular light defined in Scene3D.
 *
 * \warning Not supported in technology preview.
 */

/*!
 * \qmlproperty ColorGradient Theme3D::baseGradient
 *
 * Base gradient to be used for all the objects in the graph. Has no immediate effect if colorStyle
 * is \c Theme3D.ColorStyleUniform.
 */

/*!
 * \qmlproperty ColorGradient Theme3D::singleHighlightGradient
 *
 * Highlight gradient for a highlighted object. Used if \l{AbstractGraph3D::selectionMode}{selectionMode}
 * has \c AbstractGraph3D.SelectionItem flag set.
 */

/*!
 * \qmlproperty ColorGradient Theme3D::multiHighlightGradient
 *
 * Highlight gradient for highlighted objects. Used if \l{AbstractGraph3D::selectionMode}{selectionMode}
 * has \c AbstractGraph3D.SelectionRow or \c AbstractGraph3D.SelectionColumn flag set.
 */

/*!
 * \qmlproperty float Theme3D::lightStrength
 *
 * Specular light strength for the whole graph. Value must be between 0.0 and 1.0.
 */

/*!
 * \qmlproperty float Theme3D::ambientLightStrength
 *
 * Ambient light strength for the whole graph. Value must be between 0.0 and 1.0.
 */

/*!
 * \qmlproperty float Theme3D::highlightLightStrength
 *
 * Specular light strength for highlighted objects. Value must be between 0.0 and 1.0.
 */

/*!
 * \qmlproperty bool Theme3D::labelBorderEnabled
 *
 * Set label borders enabled or disabled. Has no effect if labelBackgroundEnabled is \c false.
 */

/*!
 * \qmlproperty Font Theme3D::font
 *
 * Set \a font to be used for labels.
 */

/*!
 * \qmlproperty bool Theme3D::backgroundEnabled
 *
 * Set background enabled or disabled.
 */

/*!
 * \qmlproperty bool Theme3D::gridEnabled
 *
 * Set grid lines enabled or disabled.
 */

/*!
 * \qmlproperty bool Theme3D::labelBackgroundEnabled
 *
 * Set label backgrounds enabled or disabled.
 */

/*!
 * \qmlproperty Theme3D.ColorStyle Theme3D::colorStyle
 *
 * The \a style of the graph colors. One of \c Theme3D.ColorStyle.
 */

/*!
 * \qmlproperty Theme3D.Theme Theme3D::type
 *
 * The type of the theme. If no type is set, the type is \c Theme3D.ThemeUserDefined.
 */

/*!
 * Constructs a new theme of type ThemeUserDefined. An optional \a parent parameter
 * can be given and is then passed to QObject constructor.
 */
Q3DTheme::Q3DTheme(QObject *parent)
    : QObject(parent),
      d_ptr(new Q3DThemePrivate(this, ThemeUserDefined))
{
}

/*!
 * Constructs a new theme with \a themeType, which can be one of the built-in themes from
 * \l Theme. An optional \a parent parameter can be given and is then passed to QObject
 * constructor.
 */
Q3DTheme::Q3DTheme(Theme themeType, QObject *parent)
    : QObject(parent),
      d_ptr(new Q3DThemePrivate(this, themeType))
{
}

/*!
 * \internal
 */
Q3DTheme::Q3DTheme(Q3DThemePrivate *d, Theme themeType,
                   QObject *parent) :
    QObject(parent),
    d_ptr(d)
{
    d_ptr->m_themeId = themeType;
}

/*!
 * Destroys the theme.
 */
Q3DTheme::~Q3DTheme()
{
}

// TODO: Add needRenders if necessary after color api has been added to series (QTRD-2200/2557)
// TODO: Basecolors as a list, containing one for each series?
/*!
 * \property Q3DTheme::baseColor
 *
 * Color to be used for all the objects in the graph. Has no immediate effect if colorStyle is not
 * ColorStyleUniform.
 */
void Q3DTheme::setBaseColor(const QColor &color)
{
    if (d_ptr->m_baseColor != color) {
        d_ptr->m_dirtyBits.baseColorDirty = true;
        d_ptr->m_baseColor = color;
        emit baseColorChanged(color);
    }
}

QColor Q3DTheme::baseColor() const
{
    return d_ptr->m_baseColor;
}

/*!
 * \property Q3DTheme::backgroundColor
 *
 * Color for the graph background.
 */
void Q3DTheme::setBackgroundColor(const QColor &color)
{
    if (d_ptr->m_backgroundColor != color) {
        d_ptr->m_dirtyBits.backgroundColorDirty = true;
        d_ptr->m_backgroundColor = color;
        emit backgroundColorChanged(color);
        emit d_ptr->needRender();
    }
}

QColor Q3DTheme::backgroundColor() const
{
    return d_ptr->m_backgroundColor;
}

/*!
 * \property Q3DTheme::windowColor
 *
 * Color for the application window.
 */
void Q3DTheme::setWindowColor(const QColor &color)
{
    if (d_ptr->m_windowColor != color) {
        d_ptr->m_dirtyBits.windowColorDirty = true;
        d_ptr->m_windowColor = color;
        emit windowColorChanged(color);
        emit d_ptr->needRender();
    }
}

QColor Q3DTheme::windowColor() const
{
    return d_ptr->m_windowColor;
}

/*!
 * \property Q3DTheme::labelTextColor
 *
 * Color for the font used for labels.
 */
void Q3DTheme::setLabelTextColor(const QColor &color)
{
    if (d_ptr->m_textColor != color) {
        d_ptr->m_dirtyBits.labelTextColorDirty = true;
        d_ptr->m_textColor = color;
        emit labelTextColorChanged(color);
        emit d_ptr->needRender();
    }
}

QColor Q3DTheme::labelTextColor() const
{
    return d_ptr->m_textColor;
}

/*!
 * \property Q3DTheme::labelBackgroundColor
 *
 * Color for the label backgrounds. Has no effect if labelBackgroundEnabled is \c false.
 */
void Q3DTheme::setLabelBackgroundColor(const QColor &color)
{
    if (d_ptr->m_textBackgroundColor != color) {
        d_ptr->m_dirtyBits.labelBackgroundColorDirty = true;
        d_ptr->m_textBackgroundColor = color;
        emit labelBackgroundColorChanged(color);
        emit d_ptr->needRender();
    }
}

QColor Q3DTheme::labelBackgroundColor() const
{
    return d_ptr->m_textBackgroundColor;
}

/*!
 * \property Q3DTheme::gridLineColor
 *
 * Color for the grid lines.
 */
void Q3DTheme::setGridLineColor(const QColor &color)
{
    if (d_ptr->m_gridLineColor != color) {
        d_ptr->m_dirtyBits.gridLineColorDirty = true;
        d_ptr->m_gridLineColor = color;
        emit gridLineColorChanged(color);
        emit d_ptr->needRender();
    }
}

QColor Q3DTheme::gridLineColor() const
{
    return d_ptr->m_gridLineColor;
}

/*!
 * \property Q3DTheme::singleHighlightColor
 *
 * Highlight color for a highlighted object. Used if \l{Q3DBars::selectionMode}{selectionMode} has
 * \c QDataVis::SelectionItem flag set.
 */
void Q3DTheme::setSingleHighlightColor(const QColor &color)
{
    if (d_ptr->m_singleHighlightColor != color) {
        d_ptr->m_dirtyBits.singleHighlightColorDirty = true;
        d_ptr->m_singleHighlightColor = color;
        emit singleHighlightColorChanged(color);
    }
}

QColor Q3DTheme::singleHighlightColor() const
{
    return d_ptr->m_singleHighlightColor;
}

/*!
 * \property Q3DTheme::multiHighlightColor
 *
 * Highlight color for highlighted objects. Used if \l{Q3DBars::selectionMode}{selectionMode} has
 * \c QDataVis::SelectionRow or \c QDataVis::SelectionColumn flag set.
 */
void Q3DTheme::setMultiHighlightColor(const QColor &color)
{
    if (d_ptr->m_multiHighlightColor != color) {
        d_ptr->m_dirtyBits.multiHighlightColorDirty = true;
        d_ptr->m_multiHighlightColor = color;
        emit multiHighlightColorChanged(color);
    }
}

QColor Q3DTheme::multiHighlightColor() const
{
    return d_ptr->m_multiHighlightColor;
}

/*!
 * \property Q3DTheme::lightColor
 *
 * Color for the specular light defined in Q3DScene.
 *
 * \warning Not supported in technology preview.
 */
void Q3DTheme::setLightColor(const QColor &color)
{
    if (d_ptr->m_lightColor != color) {
        d_ptr->m_dirtyBits.lightColorDirty = true;
        d_ptr->m_lightColor = color;
        emit lightColorChanged(color);
        emit d_ptr->needRender();
    }
}

QColor Q3DTheme::lightColor() const
{
    return d_ptr->m_lightColor;
}

// TODO: Surfacegradients as a list, containing one for each series?
/*!
 * \property Q3DTheme::baseGradient
 *
 * Base gradient to be used for all the objects in the graph. Has no immediate effect if colorStyle
 * is ColorStyleUniform.
 */
void Q3DTheme::setBaseGradient(const QLinearGradient &gradient)
{
    if (d_ptr->m_baseGradient != gradient) {
        d_ptr->m_dirtyBits.baseGradientDirty = true;
        d_ptr->m_baseGradient = gradient;
        emit baseGradientChanged(gradient);
    }
}

QLinearGradient Q3DTheme::baseGradient() const
{
    return d_ptr->m_baseGradient;
}

/*!
 * \property Q3DTheme::singleHighlightGradient
 *
 * Highlight gradient for a highlighted object. Used if \l{Q3DBars::selectionMode}{selectionMode}
 * has \c QDataVis::SelectionItem flag set.
 */
void Q3DTheme::setSingleHighlightGradient(const QLinearGradient &gradient)
{
    if (d_ptr->m_singleHighlightGradient != gradient) {
        d_ptr->m_dirtyBits.singleHighlightGradientDirty = true;
        d_ptr->m_singleHighlightGradient = gradient;
        emit singleHighlightGradientChanged(gradient);
    }
}

QLinearGradient Q3DTheme::singleHighlightGradient() const
{
    return d_ptr->m_singleHighlightGradient;
}

/*!
 * \property Q3DTheme::multiHighlightGradient
 *
 * Highlight gradient for highlighted objects. Used if \l{Q3DBars::selectionMode}{selectionMode}
 * has \c QDataVis::SelectionRow or \c QDataVis::SelectionColumn flag set.
 */
void Q3DTheme::setMultiHighlightGradient(const QLinearGradient &gradient)
{
    if (d_ptr->m_multiHighlightGradient != gradient) {
        d_ptr->m_dirtyBits.multiHighlightGradientDirty = true;
        d_ptr->m_multiHighlightGradient = gradient;
        emit multiHighlightGradientChanged(gradient);
    }
}

QLinearGradient Q3DTheme::multiHighlightGradient() const
{
    return d_ptr->m_multiHighlightGradient;
}

/*!
 * \property Q3DTheme::lightStrength
 *
 * Specular light strength for the whole graph. Value must be 0.0f and 10.0f.
 */
void Q3DTheme::setLightStrength(float strength)
{
    if (strength < 0.0f || strength > 10.0f) {
        qWarning("Invalid value. Valid range for lightStrength is between 0.0f and 10.0f");
    } else if (d_ptr->m_lightStrength != strength) {
        d_ptr->m_dirtyBits.lightStrengthDirty = true;
        d_ptr->m_lightStrength = strength;
        emit lightStrengthChanged(strength);
        emit d_ptr->needRender();
    }
}

float Q3DTheme::lightStrength() const
{
    return d_ptr->m_lightStrength;
}

/*!
 * \property Q3DTheme::ambientLightStrength
 *
 * Ambient light strength for the whole graph. Value must be between 0.0f and 1.0f.
 */
void Q3DTheme::setAmbientLightStrength(float strength)
{
    if (strength < 0.0f || strength > 1.0f) {
        qWarning("Invalid value. Valid range for ambientLightStrength is between 0.0f and 1.0f");
    } else if (d_ptr->m_ambientLightStrength != strength) {
        d_ptr->m_dirtyBits.ambientLightStrengthDirty = true;
        d_ptr->m_ambientLightStrength = strength;
        emit ambientLightStrengthChanged(strength);
        emit d_ptr->needRender();
    }
}

float Q3DTheme::ambientLightStrength() const
{
    return d_ptr->m_ambientLightStrength;
}

/*!
 * \property Q3DTheme::highlightLightStrength
 *
 * Specular light strength for highlighted objects. Value must be between 0.0f and 10.0f.
 */
void Q3DTheme::setHighlightLightStrength(float strength)
{
    if (strength < 0.0f || strength > 10.0f) {
        qWarning("Invalid value. Valid range for highlightLightStrength is between 0.0f and 10.0f");
    } else if (d_ptr->m_highlightLightStrength != strength) {
        d_ptr->m_dirtyBits.highlightLightStrengthDirty = true;
        d_ptr->m_highlightLightStrength = strength;
        emit highlightLightStrengthChanged(strength);
        emit d_ptr->needRender();
    }
}

float Q3DTheme::highlightLightStrength() const
{
    return d_ptr->m_highlightLightStrength;
}

/*!
 * \property Q3DTheme::labelBorderEnabled
 *
 * Set label borders enabled or disabled. Has no effect if labelBackgroundEnabled is \c false.
 */
void Q3DTheme::setLabelBorderEnabled(bool enabled)
{
    if (d_ptr->m_labelBorders != enabled) {
        d_ptr->m_dirtyBits.labelBorderEnabledDirty = true;
        d_ptr->m_labelBorders = enabled;
        emit labelBorderEnabledChanged(enabled);
        emit d_ptr->needRender();
    }
}

bool Q3DTheme::isLabelBorderEnabled() const
{
    return d_ptr->m_labelBorders;
}

/*!
 * \property Q3DTheme::font
 *
 * Set \a font to be used for labels.
 */
void Q3DTheme::setFont(const QFont &font)
{
    if (d_ptr->m_font != font) {
        d_ptr->m_dirtyBits.fontDirty = true;
        d_ptr->m_font = font;
        emit fontChanged(font);
        emit d_ptr->needRender();
    }
}

QFont Q3DTheme::font() const
{
    return d_ptr->m_font;
}

/*!
 * \property Q3DTheme::backgroundEnabled
 *
 * Set background enabled or disabled.
 */
void Q3DTheme::setBackgroundEnabled(bool enabled)
{
    if (d_ptr->m_backgoundEnabled != enabled) {
        d_ptr->m_dirtyBits.backgroundEnabledDirty = true;
        d_ptr->m_backgoundEnabled = enabled;
        emit backgroundEnabledChanged(enabled);
        emit d_ptr->needRender();
    }
}

bool Q3DTheme::isBackgroundEnabled() const
{
    return d_ptr->m_backgoundEnabled;
}

/*!
 * \property Q3DTheme::gridEnabled
 *
 * Set grid lines enabled or disabled.
 */
void Q3DTheme::setGridEnabled(bool enabled)
{
    if (d_ptr->m_gridEnabled != enabled) {
        d_ptr->m_dirtyBits.gridEnabledDirty = true;
        d_ptr->m_gridEnabled = enabled;
        emit gridEnabledChanged(enabled);
        emit d_ptr->needRender();
    }
}

bool Q3DTheme::isGridEnabled() const
{
    return d_ptr->m_gridEnabled;
}

/*!
 * \property Q3DTheme::labelBackgroundEnabled
 *
 * Set label backgrounds enabled or disabled.
 */
void Q3DTheme::setLabelBackgroundEnabled(bool enabled)
{
    if (d_ptr->m_labelBackground != enabled) {
        d_ptr->m_dirtyBits.labelBackgroundEnabledDirty = true;
        d_ptr->m_labelBackground = enabled;
        emit labelBackgroundEnabledChanged(enabled);
        emit d_ptr->needRender();
    }
}

bool Q3DTheme::isLabelBackgroundEnabled() const
{
    return d_ptr->m_labelBackground;
}

/*!
 * \property Q3DTheme::colorStyle
 *
 * The \a style of the graph colors. One of ColorStyle.
 */
void Q3DTheme::setColorStyle(ColorStyle style)
{
    if (d_ptr->m_colorStyle != style) {
        d_ptr->m_dirtyBits.colorStyleDirty = true;
        d_ptr->m_colorStyle = style;
        emit colorStyleChanged(style);
    }
}

Q3DTheme::ColorStyle Q3DTheme::colorStyle() const
{
    return d_ptr->m_colorStyle;
}

/*!
 * \property Q3DTheme::type
 *
 * The type of the theme. Type is automatically set when constructing a theme. User should not
 * need to use this when using C++ API.
 */
void Q3DTheme::setType(Theme themeType)
{
    if (d_ptr->m_themeId != themeType) {
        d_ptr->m_dirtyBits.themeIdDirty = true;
        d_ptr->m_themeId = themeType;
        emit typeChanged(themeType);
    }
}

Q3DTheme::Theme Q3DTheme::type() const
{
    return d_ptr->m_themeId;
}

// Q3DThemePrivate

Q3DThemePrivate::Q3DThemePrivate(Q3DTheme *q, Q3DTheme::Theme theme_id)
    : QObject(0),
      m_themeId(theme_id),
      m_baseColor(Qt::white),
      m_backgroundColor(Qt::black),
      m_windowColor(Qt::black),
      m_textColor(Qt::white),
      m_textBackgroundColor(Qt::gray),
      m_gridLineColor(Qt::white),
      m_singleHighlightColor(Qt::red),
      m_multiHighlightColor(Qt::blue),
      m_lightColor(Qt::white),
      m_baseGradient(QLinearGradient(qreal(gradientTextureWidth),
                                     qreal(gradientTextureHeight),
                                     0.0, 0.0)),
      m_singleHighlightGradient(QLinearGradient(qreal(gradientTextureWidth),
                                                qreal(gradientTextureHeight),
                                                0.0, 0.0)),
      m_multiHighlightGradient(QLinearGradient(qreal(gradientTextureWidth),
                                               qreal(gradientTextureHeight),
                                               0.0, 0.0)),
      m_lightStrength(5.0f),
      m_ambientLightStrength(0.25f),
      m_highlightLightStrength(7.5f),
      m_labelBorders(true),
      m_colorStyle(Q3DTheme::ColorStyleUniform),
      m_font(QFont()),
      m_backgoundEnabled(true),
      m_gridEnabled(true),
      m_labelBackground(true),
      q_ptr(q)
{
}

Q3DThemePrivate::~Q3DThemePrivate()
{
}

void Q3DThemePrivate::resetDirtyBits()
{
    m_dirtyBits.ambientLightStrengthDirty = true;
    m_dirtyBits.backgroundColorDirty = true;
    m_dirtyBits.backgroundEnabledDirty = true;
    m_dirtyBits.baseColorDirty = true;
    m_dirtyBits.baseGradientDirty = true;
    m_dirtyBits.colorStyleDirty = true;
    m_dirtyBits.fontDirty = true;
    m_dirtyBits.gridEnabledDirty = true;
    m_dirtyBits.gridLineColorDirty = true;
    m_dirtyBits.highlightLightStrengthDirty = true;
    m_dirtyBits.labelBackgroundColorDirty = true;
    m_dirtyBits.labelBackgroundEnabledDirty = true;
    m_dirtyBits.labelBorderEnabledDirty = true;
    m_dirtyBits.labelTextColorDirty = true;
    m_dirtyBits.lightColorDirty = true;
    m_dirtyBits.lightStrengthDirty = true;
    m_dirtyBits.multiHighlightColorDirty = true;
    m_dirtyBits.multiHighlightGradientDirty = true;
    m_dirtyBits.singleHighlightColorDirty = true;
    m_dirtyBits.singleHighlightGradientDirty = true;
    m_dirtyBits.themeIdDirty = true;
    m_dirtyBits.windowColorDirty = true;
}

bool Q3DThemePrivate::sync(Q3DThemePrivate &other)
{
    bool changed = false;
    if (m_dirtyBits.ambientLightStrengthDirty) {
        other.q_ptr->setAmbientLightStrength(m_ambientLightStrength);
        m_dirtyBits.ambientLightStrengthDirty = false;
        changed = true;
    }
    if (m_dirtyBits.backgroundColorDirty) {
        other.q_ptr->setBackgroundColor(m_backgroundColor);
        m_dirtyBits.backgroundColorDirty = false;
        changed = true;
    }
    if (m_dirtyBits.backgroundEnabledDirty) {
        other.q_ptr->setBackgroundEnabled(m_backgoundEnabled);
        m_dirtyBits.backgroundEnabledDirty = false;
        changed = true;
    }
    if (m_dirtyBits.baseColorDirty) {
        other.q_ptr->setBaseColor(m_baseColor);
        m_dirtyBits.baseColorDirty = false;
        changed = true;
    }
    if (m_dirtyBits.baseGradientDirty) {
        other.q_ptr->setBaseGradient(m_baseGradient);
        m_dirtyBits.baseGradientDirty = false;
        changed = true;
    }
    if (m_dirtyBits.colorStyleDirty) {
        other.q_ptr->setColorStyle(m_colorStyle);
        m_dirtyBits.colorStyleDirty = false;
        changed = true;
    }
    if (m_dirtyBits.fontDirty) {
        other.q_ptr->setFont(m_font);
        m_dirtyBits.fontDirty = false;
        changed = true;
    }
    if (m_dirtyBits.gridEnabledDirty) {
        other.q_ptr->setGridEnabled(m_gridEnabled);
        m_dirtyBits.gridEnabledDirty = false;
        changed = true;
    }
    if (m_dirtyBits.gridLineColorDirty) {
        other.q_ptr->setGridLineColor(m_gridLineColor);
        m_dirtyBits.gridLineColorDirty = false;
        changed = true;
    }
    if (m_dirtyBits.highlightLightStrengthDirty) {
        other.q_ptr->setHighlightLightStrength(m_highlightLightStrength);
        m_dirtyBits.highlightLightStrengthDirty = false;
        changed = true;
    }
    if (m_dirtyBits.labelBackgroundColorDirty) {
        other.q_ptr->setLabelBackgroundColor(m_textBackgroundColor);
        m_dirtyBits.labelBackgroundColorDirty = false;
        changed = true;
    }
    if (m_dirtyBits.labelBackgroundEnabledDirty) {
        other.q_ptr->setLabelBackgroundEnabled(m_labelBackground);
        m_dirtyBits.labelBackgroundEnabledDirty = false;
        changed = true;
    }
    if (m_dirtyBits.labelBorderEnabledDirty) {
        other.q_ptr->setLabelBorderEnabled(m_labelBorders);
        m_dirtyBits.labelBorderEnabledDirty = false;
        changed = true;
    }
    if (m_dirtyBits.labelTextColorDirty) {
        other.q_ptr->setLabelTextColor(m_textColor);
        m_dirtyBits.labelTextColorDirty = false;
        changed = true;
    }
    if (m_dirtyBits.lightColorDirty) {
        other.q_ptr->setLightColor(m_lightColor);
        m_dirtyBits.lightColorDirty = false;
        changed = true;
    }
    if (m_dirtyBits.lightStrengthDirty) {
        other.q_ptr->setLightStrength(m_lightStrength);
        m_dirtyBits.lightStrengthDirty = false;
        changed = true;
    }
    if (m_dirtyBits.multiHighlightColorDirty) {
        other.q_ptr->setMultiHighlightColor(m_multiHighlightColor);
        m_dirtyBits.multiHighlightColorDirty = false;
        changed = true;
    }
    if (m_dirtyBits.multiHighlightGradientDirty) {
        other.q_ptr->setMultiHighlightGradient(m_multiHighlightGradient);
        m_dirtyBits.multiHighlightGradientDirty = false;
        changed = true;
    }
    if (m_dirtyBits.singleHighlightColorDirty) {
        other.q_ptr->setSingleHighlightColor(m_singleHighlightColor);
        m_dirtyBits.singleHighlightColorDirty = false;
        changed = true;
    }
    if (m_dirtyBits.singleHighlightGradientDirty) {
        other.q_ptr->setSingleHighlightGradient(m_singleHighlightGradient);
        m_dirtyBits.singleHighlightGradientDirty = false;
        changed = true;
    }
    if (m_dirtyBits.themeIdDirty) {
        other.m_themeId = m_themeId; // Set directly to avoid a call to ThemeManager's useTheme()
        m_dirtyBits.themeIdDirty = false;
        changed = true;
    }
    if (m_dirtyBits.windowColorDirty) {
        other.q_ptr->setWindowColor(m_windowColor);
        m_dirtyBits.windowColorDirty = false;
        changed = true;
    }
    return changed;
}

QT_DATAVISUALIZATION_END_NAMESPACE