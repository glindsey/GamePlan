#ifndef GUIENUMS_H
#define GUIENUMS_H

namespace GUI {

/// Horizontal control alignment.
enum class HorizAlign
{
  Left,     ///< Align the left edge of the control with that of the parent.
  Center,   ///< Align the X center of the control with that of the parent.
  Right     ///< Align the right edge of the control with that of the parent.
};

enum class VertAlign
{
  Top,      ///< Align the top edge of the control with that of the parent.
  Center,   ///< Align the Y center of the control with that of the parent.
  Bottom    ///< Align the bottom edge of the control with that of the parent.
};

enum class ScalingType
{
  None,     ///< Target is not scaled at all.
  Stretch,  ///< Target is scaled to fit the container.
  Aspect    ///< Target is scaled to fit while maintaining proper aspect ratio.
};

enum class Orientation
{
  Horizontal,   ///< Target is oriented on the horizontal (X) axis.
  Vertical      ///< Target is oriented on the vertical (Y) axis.
};

enum class VisibilityState
{
  Hidden = 0,
  Appearing = 1,
  Visible = 2,
  Disappearing = 3
};

struct Align
{
  HorizAlign horiz;
  VertAlign vert;
};

} // end namespace GUI

#endif // GUIENUMS_H
