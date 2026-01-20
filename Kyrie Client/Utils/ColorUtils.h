#pragma once
#include <Windows.h>
#include <cmath>

struct Color {
    int r = 255;
    int g = 255;
    int b = 255;
    int a = 255;
    Color(int red, int green, int blue, int alpha = 255) {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }
};

class ColorUtils {
private:
    inline static unsigned __int64 getCurrentMs() {
        FILETIME f;
        GetSystemTimeAsFileTime(&f);
        unsigned __int64 nano = ((unsigned __int64)f.dwHighDateTime << 32) | (unsigned __int64)f.dwLowDateTime;
        return (nano - 116444736000000000ULL) / 10000ULL;
    }

    static inline void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b) {
        if (s == 0.0f) {
            out_r = out_g = out_b = v;
            return;
        }

        h = fmodf(h, 1.0f) * 6.0f;
        int i = static_cast<int>(h);
        float f = h - static_cast<float>(i);
        float p = v * (1.0f - s);
        float q = v * (1.0f - s * f);
        float t = v * (1.0f - s * (1.0f - f));

        switch (i % 6) {
        case 0: out_r = v; out_g = t; out_b = p; break;
        case 1: out_r = q; out_g = v; out_b = p; break;
        case 2: out_r = p; out_g = v; out_b = t; break;
        case 3: out_r = p; out_g = q; out_b = v; break;
        case 4: out_r = t; out_g = p; out_b = v; break;
        case 5: out_r = v; out_g = p; out_b = q; break;
        }
    }

public:
    static Color lerp(const Color& startColor, const Color& endColor, const float& duration) {
        int r = static_cast<int>(startColor.r + (endColor.r - startColor.r) * duration);
        int g = static_cast<int>(startColor.g + (endColor.g - startColor.g) * duration);
        int b = static_cast<int>(startColor.b + (endColor.b - startColor.b) * duration);
        int a = static_cast<int>(startColor.a + (endColor.a - startColor.a) * duration);
        return Color(r, g, b, a);
    }

    static Color getRainbowColor(float seconds, float saturation, float brightness, long index) {
        float currentHue = static_cast<float>((getCurrentMs() + index) % static_cast<long long>(seconds * 1000)) / (seconds * 1000.0f);
        float red, green, blue;
        ColorConvertHSVtoRGB(currentHue, saturation, brightness, red, green, blue);
        return Color(static_cast<int>(red * 255.0f), static_cast<int>(green * 255.0f), static_cast<int>(blue * 255.0f));
    }

    static Color getWaveColor(const int& red, const int& green, const int& blue, const int& red2, const int& green2, const int& blue2, long index) {
        double progress = fmod(static_cast<double>(getCurrentMs() - index) / 1000.0, 1.0);
        double cycle = fmod(static_cast<double>(getCurrentMs() - index) / 2000.0, 1.0) * 2.0;
        progress = static_cast<int>(cycle) % 2 == 0 ? progress : 1.0 - progress;
        double inverse = 1.0 - progress;

        int r = static_cast<int>(red * inverse + red2 * progress);
        int g = static_cast<int>(green * inverse + green2 * progress);
        int b = static_cast<int>(blue * inverse + blue2 * progress);
        return Color(r, g, b);
    }
};
