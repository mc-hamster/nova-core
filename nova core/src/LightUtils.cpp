#include <FastLED.h>
#include "LightUtils.h"
#include "configuration.h"
#include "main.h"
#include "utilities/PreferencesManager.h"

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

// White dot
// Used for testing Nova's LEDs
DEFINE_GRADIENT_PALETTE(white_dot){
    0, 255, 255, 255,
    1, 0, 0, 0,
    255, 0, 0, 0};

LightUtils::LightUtils()
{
    // Load the light configuration
    Serial.println("LightUtils starting up...");

    Serial.println("Loading stored brightness value...");
    uint8_t storedBrightness = getCfgBrightness();
    Serial.print("Loaded brightness value: ");
    Serial.println(storedBrightness);

    Serial.println("Configuring FastLED");
    FastLED.addLeds<APA102, APA102_DATA, APA102_CLOCK, COLOR_ORDER, DATA_RATE_KHZ(4000)>(leds, NUM_LEDS);
    FastLED.setBrightness(storedBrightness);
    Serial.print("FastLED brightness set to: ");
    Serial.println(storedBrightness);
    FastLED.setDither(0); // Disable dithering for faster performance and because we don't need it for the DMX lights.


    Serial.println("Loading light configuration - currentPalette");
    currentPalette = getPalette((PreferencesManager::getInt("cfgProgram", 1)), false);

    Serial.println("Loading light configuration - cfgSin");
    cfgSin = getCfgSin();

    Serial.println("Loading light configuration - cfgUpdates");
    cfgUpdates = getCfgUpdates() ? getCfgUpdates() : 30;

    Serial.println("Loading light configuration - cfgFire");
    cfgFire = getCfgFire();

    Serial.println("Loading light configuration - cfgReverse");
    cfgReverse = getCfgReverse();

    Serial.println("Loading light configuration - cfgAuto");
    cfgAuto = getCfgAuto();

    Serial.println("Loading light configuration - cfgAutoTime");
    cfgAutoTime = getCfgAutoTime() ? getCfgAutoTime() : 30;

    Serial.println("Loading light configuration - cfgReverseSecondRow");
    cfgReverseSecondRow = getCfgReverseSecondRow();
    
    Serial.println("Loading light configuration - cfgCircularMode");
    cfgCircularMode = getCfgCircularMode();

    // Setup goes in here
}

/**
 * The loop function of the LightUtils class.
 * This function is called repeatedly in the main loop of the program.
 */
void LightUtils::loop()
{

    static uint32_t lastAuto = 0;

    if (cfgAuto)
    {
        if (millis() - lastAuto > cfgAutoTime * 1000)
        {
            uint32_t randomPalette = random(1, 19);
            /*
            Serial.print("Auto changing palette to : ");
            Serial.println(randomPalette);

            Serial.print("Next palette change in : ");
            Serial.println(cfgAutoTime);
            */
            lastAuto = millis();
            getPalette(randomPalette, false);
        }
    }

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
        // FastLED.delay(1000 / cfgUpdates); // Enables temporal dithering
        delay(1000 / cfgUpdates);
    }
    else
    {
        // TODO: Set the output to all black before disabling
        FastLED.clear(true);
        delay(1000 / cfgUpdates);
    }
}

/**
 * Maps LED index based on strip configuration
 */
uint16_t LightUtils::mapLedIndex(uint16_t index) {
    if (!cfgReverseSecondRow) return index;
    
    // For a two-row setup where both rows start from right
    // First 12 LEDs (indices 0-11) are the first row
    // Next 18 LEDs (indices 12-29) are the second row
    if (index < 12) {
        return index; // first row stays as is
    } else {
        // Calculate the position within the second row (0 to 17)
        uint16_t secondRowPosition = index - 12;
        // Reverse the position within the second row (17 to 0)
        uint16_t reversedPosition = (NUM_LEDS - 12 - 1) - secondRowPosition;
        // Map back to the full LED strip index (12 to 29)
        return 12 + reversedPosition;
    }
}

/**
 * Fills the LED strip with colors from the current palette starting at the given color index.
 *
 * @param colorIndex The starting index in the current palette.
 */
void LightUtils::FillLEDsFromPaletteColors(uint8_t colorIndex)
{
    uint8_t brightness = getCfgBrightness();
    if (cfgCircularMode) {
        // Special handling for circular mode - imagine the LEDs are in a circle
        // We use sin/cos to create a circular effect instead of linear
        float angleStep = (2 * PI) / NUM_LEDS;
        float offset = colorIndex * 0.1; // Controls speed of rotation
        
        for (int i = 0; i < NUM_LEDS; i++) {
            uint16_t mappedIndex = mapLedIndex(i);
            
            // Skip this LED if it's protected
            if (protectedLeds[mappedIndex]) continue;
            
            // Calculate position in the circle
            float angle = i * angleStep + offset;
            
            // Use sine wave to create circular pattern
            uint8_t waveSin = sin8(i * 256 / NUM_LEDS + colorIndex);
            uint8_t waveCos = sin8(i * 256 / NUM_LEDS + colorIndex + 64); // offset by 90 degrees
            
            // Combine for a more interesting pattern
            uint8_t waveIndex = cfgSin == 0 ? colorIndex : colorIndex + (waveSin * cfgSin / 16);
            
            // Apply direction based on reverse setting
            if (cfgReverse) {
                waveIndex = colorIndex + (waveCos * cfgSin / 16);
            }
            
            leds[mappedIndex] = ColorFromPalette(currentPalette, waveIndex, brightness);
        }
    } else {
        // Original linear pattern code
        if (!getCfgReverse())
        {
            for (int i = 0; i < NUM_LEDS; i++)
            {
                uint16_t mappedIndex = mapLedIndex(i);
                
                // Skip this LED if it's protected
                if (protectedLeds[mappedIndex]) continue;
                
                if (cfgSin == 0)
                {
                    leds[mappedIndex] = ColorFromPalette(currentPalette, colorIndex, brightness);
                    colorIndex += 3;
                }
                else
                {
                    leds[mappedIndex] = ColorFromPalette(currentPalette, colorIndex + sin8(i * cfgSin), brightness);
                    colorIndex += 3;
                }
            }
        }
        else
        {
            for (int i = NUM_LEDS - 1; i >= 0; i--)
            {
                uint16_t mappedIndex = mapLedIndex(i);
                
                // Skip this LED if it's protected
                if (protectedLeds[mappedIndex]) continue;
                
                if (cfgSin == 0)
                {
                    leds[mappedIndex] = ColorFromPalette(currentPalette, colorIndex, brightness);
                    colorIndex += 3;
                }
                else
                {
                    leds[mappedIndex] = ColorFromPalette(currentPalette, colorIndex + sin8((NUM_LEDS - 1 - i) * cfgSin), brightness);
                    colorIndex += 3;
                }
            }
        }
    }
}

CRGBPalette16 LightUtils::getPalette(uint32_t paletteSelect, bool saveSelection)
{

    cfgProgram = paletteSelect;

    if (saveSelection)
    {
        PreferencesManager::setInt("cfgProgram", paletteSelect);
    }
    else
    {
        //Serial.println("Not saving palette selection");
    }

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

    case 21:

        fill_solid(targetPalette, 16, CRGB::Red);

        break;

    case 22:

        fill_solid(targetPalette, 16, CRGB::Green);

        break;

    case 23:

        fill_solid(targetPalette, 16, CRGB::Blue);

        break;

    case 24:

        fill_solid(targetPalette, 16, CRGB::Purple);

        break;

    case 25:

        fill_solid(targetPalette, 16, CRGB::Cyan);

        break;

    case 26:

        fill_solid(targetPalette, 16, CRGB::Yellow);

        break;

    case 50:

        targetPalette = white_dot;
        break;

    default:
        break;
    }

    return targetPalette;
}

void LightUtils::setCfgCircularMode(bool circularMode)
{
    cfgCircularMode = circularMode;
    PreferencesManager::setBool("cfgCircularMode", circularMode);
}

bool LightUtils::getCfgCircularMode(void)
{
    return PreferencesManager::getBool("cfgCircularMode", false);
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
        
        uint16_t mappedIndex = mapLedIndex(pixelnumber);
        
        // Skip this LED if it's protected
        if (!protectedLeds[mappedIndex]) {
            leds[mappedIndex] = color;
        }
    }
}

/**
 * Sets the brightness of the LED strip and saves the value to the configuration file.
 *
 * @param brightness The brightness value to set.
 */
void LightUtils::setCfgBrightness(uint8_t brightness)
{
    Serial.println("set brightness");
    cfgBrightness = brightness;
    PreferencesManager::setInt("cfgBrightness", brightness);
}

/**
 * Sets the number of updates per second for the LED strip and saves the value to the configuration file.
 *
 * @param updates The number of updates per second to set.
 */
void LightUtils::setCfgUpdates(uint16_t updates)
{
    cfgUpdates = updates;
    PreferencesManager::setInt("cfgUpdates", updates);
}

void LightUtils::setCfgAutoTime(uint32_t autoTime)
{
    cfgAutoTime = autoTime;
    PreferencesManager::setInt("cfgAutoTime", autoTime);
}

/**
 * Sets the sine value for the LED strip and saves the value to the configuration file.
 *
 * @param sin The sine value to set.
 */
void LightUtils::setCfgSin(uint8_t sin)
{
    cfgSin = sin;
    PreferencesManager::setInt("cfgSin", sin);
}

/**
 * Sets the current LED program based on the given program index and retrieves the corresponding color palette.
 *
 * @param program The index of the LED program to set.
 */
void LightUtils::setCfgProgram(uint8_t program)
{
    getPalette(program, true);
}

/**
 * Sets the reverse flag for the LED strip and saves the value to the configuration file.
 *
 * @param reverse The reverse flag value to set.
 */
void LightUtils::setCfgReverse(bool reverse)
{
    cfgReverse = reverse;
    PreferencesManager::setBool("cfgReverse", reverse);
}

void LightUtils::setCfgReverseSecondRow(bool reverse) {
    cfgReverseSecondRow = reverse;
    PreferencesManager::setBool("cfgReverseSecondRow", reverse);
}

bool LightUtils::getCfgReverseSecondRow(void) {
    return PreferencesManager::getBool("cfgReverseSecondRow", false);
}

void LightUtils::setCfgAuto(bool autoLight)
{
    cfgAuto = autoLight;
    PreferencesManager::setBool("cfgAuto", autoLight);
}

/**
 * Sets the fire flag for the LED strip and saves the value to the configuration file.
 *
 * @param fire The fire flag value to set.
 */
void LightUtils::setCfgFire(bool fire)
{
    cfgFire = fire;
    PreferencesManager::setBool("cfgFire", fire);
}

/**
 * Sets the local disable flag for the LED strip and saves the value to the configuration file.
 *
 * @param localDisable The local disable flag value to set.
 */
void LightUtils::setCfgLocalDisable(bool localDisable)
{
    cfgLocalDisable = localDisable;
    PreferencesManager::setBool("cfgLocalDisable", localDisable);
}

/**
 * Retrieves the brightness value from the configuration file.
 *
 * @return The brightness value.
 */
uint8_t LightUtils::getCfgBrightness(void)
{
    //Serial.println("getCfgBrightness called");
    uint8_t brightness = PreferencesManager::getInt("cfgBrightness", 255);
    //Serial.print("Preference value for cfgBrightness: ");
    //Serial.println(brightness);
    return brightness;
}

/**
 * Retrieves the number of updates from the configuration file.
 *
 * @return The number of updates.
 */
uint16_t LightUtils::getCfgUpdates(void)
{
    return PreferencesManager::getInt("cfgUpdates", 100);
}

/**
 * Retrieves the sine value from the configuration file.
 *
 * @return The sine value.
 */
uint8_t LightUtils::getCfgSin(void)
{
    return PreferencesManager::getInt("cfgSin", 0);
}

/**
 * Retrieves the LED program index from the configuration file.
 *
 * @return The LED program index.
 */
uint8_t LightUtils::getCfgProgram(void)
{
    return PreferencesManager::getInt("cfgProgram", 1);
}

uint32_t LightUtils::getCfgAutoTime(void)
{
    return PreferencesManager::getInt("cfgAutoTime", 0);
}

/**
 * Retrieves the reverse flag from the configuration file.
 *
 * @return The reverse flag value.
 */
bool LightUtils::getCfgReverse(void)
{
    return PreferencesManager::getBool("cfgReverse", false);
}

bool LightUtils::getCfgAuto(void)
{
    return PreferencesManager::getBool("cfgAuto", false);
}

/**
 * Retrieves the fire flag from the configuration file.
 *
 * @return The fire flag value.
 */
bool LightUtils::getCfgFire(void)
{
    return PreferencesManager::getBool("cfgFire", false);
}

/**
 * Retrieves the local disable flag from the configuration file.
 *
 * @return The local disable flag value.
 */
bool LightUtils::getCfgLocalDisable(void)
{
    return PreferencesManager::getBool("cfgLocalDisable", false);
}

/**
 * Returns a pointer to the array of CRGB objects representing the LED strip.
 *
 * @return A pointer to the array of CRGB objects representing the LED strip.
 */
CRGB *LightUtils::getLeds(void)
{

    return leds;
}

/**
 * Returns the number of LEDs in the LED strip.
 *
 * @return The number of LEDs in the LED strip.
 */
uint16_t LightUtils::getNumberOfLeds(void)
{

    return NUM_LEDS;
}


// New methods for protected LEDs

/**
 * Protect a range of LEDs from being updated by pattern generators
 * and set them to a specific color.
 * 
 * @param start The starting index of the range (inclusive)
 * @param end The ending index of the range (inclusive)
 * @param color The color to set the protected LEDs to
 */
void LightUtils::protectLedRange(uint16_t start, uint16_t end, CRGB color) {
    if (start >= NUM_LEDS || end >= NUM_LEDS || start > end) {
        Serial.println("Invalid LED range specified for protection");
        return;
    }
    
    for (uint16_t i = start; i <= end; i++) {
        protectedLeds[i] = true;
        leds[i] = color;
    }
    
    // Log the protection for debugging
    /*
    Serial.print("Protected LEDs ");
    Serial.print(start);
    Serial.print(" through ");
    Serial.println(end);
    */
}

/**
 * Unprotect all LEDs, allowing them to be updated by pattern generators
 */
void LightUtils::unprotectAllLeds() {
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        protectedLeds[i] = false;
    }
    Serial.println("Unprotected all LEDs");
}

/**
 * Check if an LED is protected
 * 
 * @param index The index of the LED to check
 * @return true if the LED is protected, false otherwise
 */
bool LightUtils::isLedProtected(uint16_t index) {
    if (index >= NUM_LEDS) return false;
    return protectedLeds[index];
}