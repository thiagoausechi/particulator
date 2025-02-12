#ifndef COLORS_H
#define COLORS_H

#include <allegro5/allegro_color.h>

struct Color {
  float hue; // 0.0 to 360.0
  float saturation; // 0.0 to 100.0
  float lightness; // 0.0 to 100.0

  auto toAllegro() const {
    return al_color_hsl(this->hue, this->saturation, this->lightness);
  }
};

struct Colors {
  constexpr static auto Black = Color(0.0f, 0.0f, 0.0f);
  constexpr static auto White = Color(0.0f, 0.0f, 100.0);
};

#endif //COLORS_H
