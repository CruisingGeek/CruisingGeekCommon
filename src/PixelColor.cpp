#include "PixelColor.h"
#include "MathUtils.h"

const uint8_t shift_WS2812b[]     = { 16, 24, 8, 0 };
const uint8_t shift_WS2813[]      = { 16, 24, 8, 0 };
const uint8_t shift_SK6812[]      = { 16, 24, 8, 0 };
const uint8_t shift_SK6812_RGBW[] = { 24, 16, 8, 0 };

PixelColor::PixelColor()
    : PixelColor(0, 0, 0, 0)
{
}

PixelColor::PixelColor(uint8_t red, uint8_t green, uint8_t blue)
    : PixelColor(red, green, blue, 0)
{
}

PixelColor::PixelColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
    : _r(red)
    , _g(green)
    , _b(blue)
    , _w(white)
{
}

uint8_t PixelColor::Red() const { return this->_r; }
uint8_t PixelColor::Green() const { return this->_g; }
uint8_t PixelColor::Blue() const { return this->_b; }
uint8_t PixelColor::White() const { return this->_w; }

void PixelColor::SetRed(uint8_t red) { this->_r = red; }
void PixelColor::SetGreen(uint8_t green) { this->_g = green; }
void PixelColor::SetBlue(uint8_t blue) { this->_b = blue; }
void PixelColor::SetWhite(uint8_t white) { this->_w = white; }

PixelColor *PixelColor::ScaleColor(float percent)
{
    if (percent < 0.0f || percent > 1.0f) { return this; }

    _r = (uint8_t)((float)_r * percent);
    _g = (uint8_t)((float)_g * percent);
    _b = (uint8_t)((float)_b *percent);
    _w = (uint8_t)((float)_w * percent);

    return this;
}

PixelColor *PixelColor::CopyFromColor(const PixelColor *other, float percent)
{
    this->SetRed((uint8_t)((float)other->Red() * percent));
    this->SetGreen((uint8_t)((float)other->Green() * percent));
    this->SetBlue((uint8_t)((float)other->Blue() * percent));
    this->SetWhite((uint8_t)((float)other->White() * percent));

    return this;
}

PixelColor *PixelColor::Morph(const PixelColor *other, float alpha)
{
    return Morph(this, other, alpha);
}

PixelColor *PixelColor::Morph(const PixelColor *c1, const PixelColor *c2, float alpha)
{
    if (alpha == 0.0f)
    {
        CopyFromColor(c1);
        return this;
    }

    if (alpha == 1.0f)
    {
        CopyFromColor(c2);
        return this;
    }

    float beta = 1.0f - alpha;
    SetRed(minimum(255, (uint8_t)((beta * (float)c1->Red()) + (alpha * (float)c2->Red()))));
    SetGreen(minimum(255, (uint8_t)((beta * (float)c1->Green()) + (alpha * (float)c2->Green()))));
    SetBlue(minimum(255, (uint8_t)((beta * (float)c1->Blue()) + (alpha * (float)c2->Blue()))));
    SetWhite(minimum(255, (uint8_t)((beta * (float)c1->White()) + (alpha * (float)c2->White()))));

    return this;
}

uint32_t PixelColor::PackedValue(PixelType type) const
{
    const uint8_t *shiftArray = GetShiftArray(type);

    // Ensure that non-RGBW types always read zero (0) for w so the or operation below is correct.
    uint8_t w = type == PixelType::SK6812_RGBW
        ? this->_w
        : 0;

    bool isGR = type == PixelType::WS2812b_GR || type == PixelType::SK6812_GR;

    int indexRed = isGR ? 1 : 0;
    int indexGreen = isGR ? 0 : 1;

    uint32_t result =
        (this->_r << shiftArray[indexRed]) |
        (this->_g << shiftArray[indexGreen]) |
        (this->_b << shiftArray[2]) |
        (w << shiftArray[3]);

    return result;
}

const uint8_t* PixelColor::GetShiftArray(PixelType type) const
{
    switch(type)
    {
        case PixelType::WS2813:
            return &shift_WS2813[0];
        case PixelType::SK6812:
            return &shift_SK6812[0];
        case PixelType::SK6812_RGBW:
            return &shift_SK6812_RGBW[0];
        case PixelType::WS2812b:
        default:
            return &shift_WS2812b[0];
    }
}
