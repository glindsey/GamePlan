#ifndef CONFIGSETTINGS_H
#define CONFIGSETTINGS_H

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

/// Class that contains configuration settings for the entire game.  The class
/// is instantiated as a lazy-initialized singleton.
class ConfigSettings
{
  public:
    virtual ~ConfigSettings();

    /// Get the singleton instance of the class.
    /// If the instance does not yet exist, it is constructed and initialized.
    static ConfigSettings& instance();

    bool debug_control_borders;             ///< If true, borders are drawn around borderless controls.
    sf::Color window_border_color;          ///< Window border color.
    sf::Color window_focused_border_color;  ///< Focused window border color.
    sf::Color window_bg_color;              ///< Window background color.
    sf::Color window_focused_bg_color;      ///< Focused window bg color.
    float window_border_width;              ///< Window border width.
    sf::Color button_focused_border_color;  ///< Button focused border color.
    sf::Color button_border_bl_color;       ///< Button border color, bottom/left.
    sf::Color button_border_tr_color;       ///< Button border color, top/right.
    sf::Color button_bg_color;              ///< Button background color.
    float button_border_width;              ///< Button border width.
    std::string font_name_default;          ///< Default font name.
    std::string font_name_bold;             ///< Default bold font name.
    std::string font_name_mono;             ///< Default mono font name.
    sf::Color text_color;                   ///< Text color.
    sf::Color text_highlight_color;         ///< Text highlight color.
    sf::Color text_warning_color;           ///< Text color for warning messages
    sf::Color text_danger_color;            ///< Text color for danger messages
    unsigned int text_default_size;         ///< Default text size.
    unsigned int text_title_size;           ///< Title text size.
    unsigned int text_mono_default_size;    ///< Default monospaced text size.
    sf::Color cursor_border_color;          ///< Cursor border color.
    sf::Color cursor_bg_color;              ///< Cursor background color.
    float tile_highlight_border_width;      ///< Highlight border width.
    unsigned int inventory_area_width;      ///< Width of inventory areas.
    unsigned int status_area_height;        ///< Height of the status area.
    unsigned int map_tile_size;             ///< Size of a map tile, in pixels.

  protected:
  private:
    /// Constructor.  Private because this is a singleton.
    ConfigSettings();

    /// Unique pointer to singleton instance.
    static std::unique_ptr<ConfigSettings> instance_;
};

/// Shortcut to the singleton instance, to save on typing.
#define Settings ConfigSettings::instance()

#endif // CONFIGSETTINGS_H
