#ifndef SIDBOX_GAMEDESIGNER_LIMITS_H
#define SIDBOX_GAMEDESIGNER_LIMITS_H

// Editor coordinate limits shared by the canvas and .sbgm loader.
// LCD dimensions must match SIDBOX V1 hardware.
namespace SidboxGameDesignerLimits {
inline constexpr int LCD_WIDTH = 480;
inline constexpr int LCD_HEIGHT = 320;
inline constexpr int MAX_WORLD = 131072; // 4096 tiles x 32 pixels
}

#endif
