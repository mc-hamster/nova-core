#include <FastLED.h>
#include "LightUtils.h"
#include "configuration.h"

#define NUM_LEDS 18
#define LED_TYPE APA102
#define COLOR_ORDER BGR
CRGB leds[NUM_LEDS];

CRGBPalette16 currentPalette(CRGB::Black);

CRGBPalette16 targetPalette;

LightUtils *lightUtils = NULL;

DEFINE_GRADIENT_PALETTE(heatmap_gp){
    0, 0, 0, 0,          // black
    128, 255, 0, 0,      // red
    224, 255, 255, 0,    // bright yellow
    255, 255, 255, 255}; // full white

// Gradient palette "quagga_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/quagga.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(quagga_gp){
    0, 1, 9, 84,
    40, 42, 24, 72,
    84, 6, 58, 2,
    168, 88, 169, 24,
    211, 42, 24, 72,
    255, 1, 9, 84};

// Gradient palette "purplefly_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/purplefly.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE(purplefly_gp){
    0, 0, 0, 0,
    63, 239, 0, 122,
    191, 252, 255, 78,
    255, 0, 0, 0};

// Gradient palette "butterflytalker_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/butterflytalker.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(butterflytalker_gp){
    0, 1, 1, 6,
    51, 6, 11, 52,
    89, 107, 107, 192,
    127, 101, 161, 192,
    165, 107, 107, 192,
    204, 6, 11, 52,
    255, 0, 0, 0};

// Gradient palette "carousel_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/carousel.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(carousel_gp){
    0, 2, 6, 37,
    101, 2, 6, 37,
    122, 177, 121, 9,
    127, 217, 149, 2,
    132, 177, 121, 9,
    153, 84, 13, 36,
    255, 84, 13, 36};

// Gradient palette "autumnrose_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/autumnrose.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(autumnrose_gp){
    0, 71, 3, 1,
    45, 128, 5, 2,
    84, 186, 11, 3,
    127, 215, 27, 8,
    153, 224, 69, 13,
    188, 229, 84, 6,
    226, 242, 135, 17,
    255, 247, 161, 79};

// Gradient palette "bhw1_33_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_33.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_33_gp){
    0, 2, 1, 8,
    94, 79, 2, 212,
    140, 110, 11, 197,
    255, 2, 1, 8};

// Gradient palette "bhw1_22_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_22.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_22_gp){
    0, 1, 1, 1,
    45, 30, 10, 1,
    96, 60, 9, 1,
    130, 197, 36, 12,
    188, 30, 10, 1,
    255, 1, 1, 1};

LightUtils::LightUtils()
{

    // delay( 1000 ); // power-up safety delay
    FastLED.addLeds<APA102, APA102_DATA, APA102_CLOCK, COLOR_ORDER, DATA_RATE_KHZ(2000)>(leds, NUM_LEDS);
    FastLED.setBrightness(cfgBrightness);

    currentPalette = getPalette(1);

    // Setup goes in here
}

void LightUtils::loop()
{
    yield();
    // Crossfade current palette slowly toward the target palette
    //
    // Each time that nblendPaletteTowardPalette is called, small changes
    // are made to currentPalette to bring it closer to matching targetPalette.
    // You can control how many changes are made in each call:
    //   - the default of 24 is a good balance
    //   - meaningful values are 1-48.  1=veeeeeeeery slow, 48=quickest
    //   - "0" means do not change the currentPalette at all; freeze

    uint8_t maxChanges = 12;
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);

    if (getCfgFire())
    {
        Fire2012WithPalette();
    }
    else
    {
        static uint8_t startIndex = 0;
        startIndex = startIndex + 1; /* motion speed */
        FillLEDsFromPaletteColors(startIndex);
    }

    FastLED.setBrightness(cfgBrightness);

    if (!getCfgLocalDisable())
    {
        FastLED.show();
        FastLED.delay(1000 / cfgUpdates);
    }
    else
    {
        // TODO: Set the output to all black before disabling
        FastLED.clear(true);
        delay(1000 / cfgUpdates);
    }
}

void LightUtils::FillLEDsFromPaletteColors(uint8_t colorIndex)
{
    uint8_t brightness = 255;

    if (!getCfgReverse())
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            if (cfgSin == 0)
            {
                leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness);
                colorIndex += 3;
            }
            else
            {
                leds[i] = ColorFromPalette(currentPalette, colorIndex + sin8(i * cfgSin), brightness);
                colorIndex += 3;
            }
        }
    }
    else
    {
        for (int i = NUM_LEDS - 1; i >= 0; i--)
        {
            if (cfgSin == 0)
            {
                leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness);
                colorIndex += 3;
            }
            else
            {
                leds[i] = ColorFromPalette(currentPalette, colorIndex + sin8((NUM_LEDS - 1 - i) * cfgSin), brightness);
                colorIndex += 3;
            }
        }
    }
}

CRGBPalette16 LightUtils::getPalette(uint32_t paletteSelect)
{

    cfgProgram = paletteSelect;
    // Serial.println(paletteSelect);

    switch (paletteSelect)
    {
    case 1:
        targetPalette = RainbowColors_p;
        break;

    case 2:
        targetPalette = RainbowStripeColors_p;
        break;

    case 3:
        targetPalette = CloudColors_p;
        break;

    case 4:
        targetPalette = PartyColors_p;
        break;

    case 5:
        // myRedWhiteBluePalette_p
        targetPalette = CRGBPalette16(
            CRGB::Red,
            CRGB::Gray, // 'white' is too bright compared to red and blue
            CRGB::Blue,
            CRGB::Black,

            CRGB::Red,
            CRGB::Gray,
            CRGB::Blue,
            CRGB::Black,

            CRGB::Red,
            CRGB::Red,
            CRGB::Gray,
            CRGB::Gray,
            CRGB::Blue,
            CRGB::Blue,
            CRGB::Black,
            CRGB::Black);
        break;

    case 6:
        // Random Palette
        for (int i = 0; i < 16; i++)
        {
            targetPalette[i] = CHSV(random8(), 255, random8());
        }
        break;

    case 7:
        // Black and White Stripped

        // 'black out' all 16 palette entries...
        fill_solid(targetPalette, 16, CRGB::Black);
        // and set every fourth one to white.
        targetPalette[0] = CRGB::White;
        targetPalette[4] = CRGB::White;
        targetPalette[8] = CRGB::White;
        targetPalette[12] = CRGB::White;

        break;

    case 8:

        targetPalette = quagga_gp;
        break;

    case 9:

        targetPalette = purplefly_gp;
        break;

    case 10:

        targetPalette = butterflytalker_gp;
        break;

    case 11:

        targetPalette = carousel_gp;
        break;

    case 12:

        targetPalette = autumnrose_gp;
        break;

    case 13:

        targetPalette = bhw1_33_gp;
        break;

    case 14:

        targetPalette = bhw1_22_gp;
        break;

    case 15:

        targetPalette = heatmap_gp;
        break;

    case 16:

        targetPalette = HeatColors_p;
        break;

    case 17:

        targetPalette = LavaColors_p;
        break;

    case 18:

        targetPalette = OceanColors_p;
        break;

    case 19:

        targetPalette = ForestColors_p;
        break;

    case 20:

        fill_solid(targetPalette, 16, CRGB::White);

        break;

    default:
        break;
    }

    return targetPalette;
}

void LightUtils::Fire2012WithPalette(void)
{
    // Array of temperature readings at each simulation cell
    static uint8_t heat[NUM_LEDS];

    // Step 1.  Cool down every cell a little
    for (int i = 0; i < NUM_LEDS; i++)
    {
        heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (int k = NUM_LEDS - 1; k >= 2; k--)
    {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if (random8() < SPARKING)
    {
        int y = random8(7);
        heat[y] = qadd8(heat[y], random8(160, 255));
    }

    // Step 4.  Map from heat cells to LED colors
    for (int j = 0; j < NUM_LEDS; j++)
    {
        // Scale the heat value from 0-255 down to 0-240
        // for best results with color palettes.
        uint8_t colorindex = scale8(heat[j], 240);
        CRGB color = ColorFromPalette(targetPalette, colorindex);
        int pixelnumber;
        if (cfgReverse)
        {
            pixelnumber = (NUM_LEDS - 1) - j;
        }
        else
        {
            pixelnumber = j;
        }
        leds[pixelnumber] = color;
    }
}

void LightUtils::setCfgBrightness(uint8_t brightness)
{
    cfgBrightness = brightness;
}

void LightUtils::setCfgUpdates(uint16_t updates)
{
    cfgUpdates = updates;
}

void LightUtils::setCfgSin(uint8_t sin)
{
    cfgSin = sin;
}

void LightUtils::setCfgProgram(uint8_t program)
{
    getPalette(program);
}

void LightUtils::setCfgReverse(bool reverse)
{
    cfgReverse = reverse;
}

void LightUtils::setCfgFire(bool fire)
{
    cfgFire = fire;
}

void LightUtils::setCfgLocalDisable(bool localDisable)
{
    cfgLocalDisable = localDisable;
}

uint8_t LightUtils::getCfgBrightness(void)
{
    return cfgBrightness;
}

uint16_t LightUtils::getCfgUpdates(void)
{
    return cfgUpdates;
}

uint8_t LightUtils::getCfgSin(void)
{
    return cfgSin;
}

uint8_t LightUtils::getCfgProgram(void)
{
    return cfgProgram;
}

bool LightUtils::getCfgReverse(void)
{
    return cfgReverse;
}

bool LightUtils::getCfgFire(void)
{
    return cfgFire;
}

bool LightUtils::getCfgLocalDisable(void)
{
    return cfgLocalDisable;
}
