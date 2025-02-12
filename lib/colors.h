#ifndef COLORS_H
#define COLORS_H

#include "utils.h"
#include <allegro5/allegro_color.h>

struct Color {
  float hue; // 0.0 to 360.0
  float saturation; // 0.0 to 100.0
  float lightness; // 0.0 to 100.0

  auto toAllegro() const {
    return al_color_hsl(this->hue, this->saturation, this->lightness);
  }

  static auto fromRGB(const int r, const int g, const int b) {
    float h, s, l;
    al_color_rgb_to_hsl(r, g, b, &h, &s, &l);
    return Color(h, s, l);
  }
};

struct ColorModifiers {
  std::function<int()> hueFn;
  std::function<int()> satFn;
  std::function<int()> lightFn;

  explicit ColorModifiers(const std::function<int()> &hueFn = []() { return 0; },
                          const std::function<int()> &satFn = []() { return randomInRange(-20, 0); },
                          const std::function<int()> &lightFn = []() { return randomInRange(-10, 10); })
    : hueFn(hueFn), satFn(satFn), lightFn(lightFn) {
  }
};

struct Colors {
  static Color varyColor(const Color &color, const ColorModifiers &modifiers = ColorModifiers()) {
    float hue = color.hue + modifiers.hueFn();
    hue = std::fmod(hue, 360.0f);

    float saturation = color.saturation + static_cast<float>(modifiers.satFn());
    saturation = std::fmax(0.0f, std::fmin(saturation / 100.0f, 1.0f));

    float lightness = color.lightness + static_cast<float>(modifiers.lightFn());
    lightness = std::fmax(0.0f, std::fmin(lightness / 100.0f, 1.0f));

    return {hue, saturation, lightness};
  }

  constexpr static Color Black = {0.0f, 0.0f, 0.0f};
  constexpr static Color White = {0.0f, 0.0f, 100.0f};
};

#endif //COLORS_H
