/**************************************************************************************
 * Copyright Naigon's Electronic Creations 2021. All rights reserved.
 **************************************************************************************/

/**
  *************************************************************************************
  * @file    PixelColor.h
  * @author  Naigon's Electronic Creations
  * @brief   PixelColor
  *          Definition for a single pixel color of a blade. It can represent the
  *          entire blade in the case of in-hilt LED blades.
  *************************************************************************************
**/

#ifndef __PixelColor_H_
#define __PixelColor_H_

#include "Arduino.h"

// Pixel Type that is entered into the config.
//
// While most config enums live at the NEC layer this special one needs to be here since
// it affects  code utilized by the PixelDriver.
//
enum PixelType : uint8_t
{
    WS2812b = 0,
    WS2812b_GR = 1,
    WS2813 = 2,
    SK6812 = 3,
    SK6812_GR = 4,
    SK6812_RGBW = 5,
    PIXEL_TYPE_Count = 6,
    // Not a pixel at all; just a normal LED. This is after count since it is a special
    // meaning that isn't used by pixel functions.
    Standard = 6,
};

class PixelColor
{
public:
    /**
     * @brief   Constructs a new instance of the PixelColor class, with all colors set
     *          to zero (0).
     **/
    PixelColor();

    /**
     * @brief   Constructs a new instance of the PixelColor class with RGB data.
     **/
    PixelColor(uint8_t red, uint8_t green, uint8_t blue);

    /**
     * @brief   Constructs a new instance of the PIxelColor class with RGBW data.
     **/
    PixelColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

    /**
     * @brief   Red value.
     **/
    uint8_t Red() const;

    /**
     * @brief   Green value.
     **/
    uint8_t Green() const;

    /**
     * @brief   Blue value.
     **/
    uint8_t Blue() const;

    /**
     * @brief   White value.
     **/
    uint8_t White() const;

    /**
     * @brief   Set the red value with new color red.
     **/
    void SetRed(uint8_t red);

    /**
     * @brief   Set the red value with new color green.
     **/
    void SetGreen(uint8_t green);

    /**
     * @brief   Set the red value with new color blue.
     **/
    void SetBlue(uint8_t blue);

    /**
     * @brief   Set the red value with new color white.
     **/
    void SetWhite(uint8_t white);

    /**
     * @brief   Scale all RGBW values by percent. The current object will be
     *          modified.
     * 
     * @param   percent
     *          Amount to scale. Should be between 0.0f and 1.0f inclusively.
     * 
     * @return  Pointer to the modifed object (this ptr).
     **/
    PixelColor* ScaleColor(float percent);

    /**
     * @brief   Copy color from another color. The current object will be
     *          modified.
     * 
     * @param   other
     *          The source color
     * 
     * @param   percent
     *          Amount to scale. Default is 1.0f, or full scaling.
     * 
     * @return  Pointer to the modified object (this ptr).
     **/
    PixelColor* CopyFromColor(const PixelColor *other, float percent = 1.0f);

    /**
     * @brief   Morphs one color into another, mixing them together. This operation
     *          is destructive as it modifies the original color.
     * 
     * @param   other
     *          Color that will be used to morph with the current one.
     * 
     * @param   alpha
     *          Number in the range [0, 1] to define the mix.
     * 
     *          Zero (0) means 100% the original color. One (1) means all the
     *          other color.
     * 
     * @return  Pointer to this object which has been morphed.
     **/
    PixelColor* Morph(const PixelColor *other, float alpha);

    /**
     * @brief   Morphs the two passed colors into one combined color. This operation is
     *          destructive as it overrides the color with the combined output.
     * 
     * @param   c1
     *          The first color
     * 
     * @param   c2
     *          The second color
     * 
     * @param   alpha
     *          Number in the range [0, 1] to define the mix.
     * 
     *          Zero (0) means 100% the original color. One (1) means all the
     *          other color.
     * 
     * @return  Pointer to this object which has been morphed.
     **/
    PixelColor* Morph(const PixelColor *c1, const PixelColor *c2, float alpha);

    /**
     * @brief   32-bit packed color value of all RGBW data.
     * 
     * @param   type
     *          The pixel type used to construct the packing.
     **/
    uint32_t PackedValue(PixelType type) const;

private:
    const uint8_t* GetShiftArray(PixelType type) const;
    uint8_t _r, _g, _b, _w;
};

#endif
