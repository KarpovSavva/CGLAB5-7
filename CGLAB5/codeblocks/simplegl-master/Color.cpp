#include "Color.h"

const Color Color::WHITE(0.8, 0.8, 0.8);
const Color Color::GRAY(0.5, 0.5, 0.5);
const Color Color::GRAY_DARK(0.3, 0.3, 0.3);
const Color Color::BLUE(0.3, 0.3, 0.8);
const Color Color::GREEN(0.3, 0.8, 0.3);
const Color Color::RED(0.8, 0.3, 0.3);
const Color Color::ORANGE(1, 0.5, 0.3);
const Color Color::YELLOW(0.8, 0.8, 0.3);

Color::Color()
{
    rgb[0] = rgb[1] = rgb[2] = rgb[3] = 1;
}

Color::Color(float r, float g, float b)
{
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
    rgb[3] = 1;
}

Color::Color(float r, float g, float b, float a)
{       
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
    rgb[3] = a;
}

Color::~Color()
{
    
}

Color Color::brighter(float p) const
{
    float r = rgb[0] + p;
    float g = rgb[1] + p;
    float b = rgb[2] + p;
    
    if(r > 1) r = 1;
    if(g > 1) g = 1;
    if(b > 1) b = 1;
    
    return Color(r, g, b, rgb[3]);
}

Color Color::darker(float p) const
{
    float r = rgb[0] - p;
    float g = rgb[1] - p;
    float b = rgb[2] - p;
    
    if(r < 0) r = 0;
    if(g < 0) g = 0;
    if(b < 0) b = 0;
    
    return Color(r, g, b, rgb[3]);
}
