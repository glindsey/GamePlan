#ifndef GUIENUMS_H
#define GUIENUMS_H

/// Horizontal control alignment.
enum class GUIHorizAlign
{
  Left,     ///< Align the left edge of the control with that of the parent.
  Center,   ///< Align the X center of the control with that of the parent.
  Right     ///< Align the right edge of the control with that of the parent.
};

enum class GUIVertAlign
{
  Top,      ///< Align the top edge of the control with that of the parent.
  Center,   ///< Align the Y center of the control with that of the parent.
  Bottom    ///< Align the bottom edge of the control with that of the parent.
};

enum class GUIScalingType
{
  None,     ///< Target is not scaled at all.
  Stretch,  ///< Target is scaled to fit the container.
  Aspect    ///< Target is scaled to fit while maintaining proper aspect ratio.
};

enum class GUIOrientation
{
  Horizontal,   ///< Target is oriented on the horizontal (X) axis.
  Vertical      ///< Target is oriented on the vertical (Y) axis.
};

struct GUIAlign
{
  GUIHorizAlign horiz;
  GUIVertAlign vert;
};

#endif // GUIENUMS_H
