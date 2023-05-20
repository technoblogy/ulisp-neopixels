/*
  NeoPixel uLisp Extension - Version 1 - Unreleased
  See http://www.ulisp.com/show?282B
*/

#include <Adafruit_NeoPixel.h>

#if defined(ARDUINO_PYBADGE_M4) || defined(ARDUINO_PYGAMER_M4)
  #define NEOPIXEL_NUM 5
  #define PIN_NEOPIXEL 8
#elif defined(ARDUINO_NRF52840_CIRCUITPLAY)
  // Defined in core
#elif defined(ARDUINO_QTPY_M0)
  #define NEOPIXEL_NUM 1
#endif

Adafruit_NeoPixel pixels(NEOPIXEL_NUM, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

/*
  (pixels-begin)
  Configures the NeoPixel pin for output.
*/
object *fn_PixelsBegin (object *args, object *env) {
  (void) args, (void) env;
  pixels.begin();
  return nil;
}

/*
  (pixels-clear)
  Sets all pixel colors to off.
*/
object *fn_PixelsClear (object *args, object *env) {
  (void) env;
  pixels.clear();
  return nil;
}

/*
  (pixels-fill [rgbw] [first] [fill])
  Fills all or part of the NeoPixel strip with a fixed 32-bit packed RGB or RGBW value (default 0).
  first, default 0, the first NeoPixel to fill.
  fill, default all, the number of NeoPixels to fill.
*/
object *fn_PixelsFill (object *args, object *env) {
  (void) env;
  uint32_t rgbw = 0;
  int first = 0, fill = 0;
  if (args != NULL) {
    first = checkinteger(first(args));
    args = cdr(args);
    if (args != NULL) {
      fill = checkinteger(first(args));
    }
  }
  pixels.fill(rgbw, first, fill);
  return nil;
}

/*
  (pixels-set-pixel-color index rgbw)
  (pixels-set-pixel-color index red green blue [white])
  Set a pixel's color using either a 32-bit packed RGB or RGBW value,
  or separate red, green, blue, and optionally white components.
*/
object *fn_PixelsSetPixelColor (object *args, object *env) {
  (void) env;
  int nargs = listlength(args);
  int i = checkinteger(first(args));
  if (nargs == 2) pixels.setPixelColor(i, checkinteger(second(args)));
  else {
    int w = 0;
    args = cdr(args);
    int r = checkinteger(first(args)), g = checkinteger(second(args)), b = checkinteger(third(args));
    args = cddr(cdr(args));
    if (args != NULL) w = checkinteger(first(args));
    pixels.setPixelColor(i, r, g, b, w);
  }
  return nil;
}

/*
  (pixels-color red green blue [white])
  Converts separate red, green, blue, and optionally white values into
  a single packed 32-bit RGB or RGBW color.
*/
object *fn_PixelsColor (object *args, object *env) {
  (void) env;
  int w = 0;
  int r = checkinteger(first(args)), g = checkinteger(second(args)), b = checkinteger(third(args));
  args = cddr(cdr(args));
  if (args != NULL) w = checkinteger(first(args));
  return number(pixels.Color(r, g, b, w));
}

/*
  (pixels-color-hsv hue sat val)
  Converts separate hue (0 to 65535), saturation (0 to 255), and value (0 to 255) values into
  a single packed 32-bit RGB or RGBW color.
*/
object *fn_PixelsColorHSV (object *args, object *env) {
  (void) env;
  int hue = checkinteger(first(args)), sat = checkinteger(second(args)), val = checkinteger(third(args));
  return number(pixels.ColorHSV(hue, sat, val));
}

/*
  (pixels-show)
  Transmits the pixel data to the NeoPixels.
*/
object *fn_PixelsShow (object *args, object *env) {
  (void) env;
  pixels.show();
  return nil;
}

/*
  (pixels-rainbow [first-hue] [cycles] [saturation] [brightness] [gammify])
  Fills the NeoPixel strip with one or more cycles of hues. 
  first-hue, default 0, is the hue of the first pixel (0 to 65535).
  cycles, default 1, is the number of cycles.
  saturation, default 255, is the saturation (0 to 255).
  brightness, default 255, is the brightness (0 to 255).
  gammify, default true, applies gamma correction to colours.
*/
object *fn_PixelsRainbow (object *args, object *env) {
  (void) env;
  int firstHue = 0, cycles = 1, saturation = 255, brightness = 255, gammify = 1;
  if (args != NULL) {
    firstHue = checkinteger(first(args));
    args = cdr(args);
    if (args != NULL) {
      cycles = checkinteger(first(args));
      args = cdr(args);
      if (args != NULL) {
        saturation = checkinteger(first(args));
        args = cdr(args);
        if (args != NULL) {
          brightness = checkinteger(first(args));
          args = cdr(args);
          if (args != NULL) {
            gammify = (first(args) == nil) ? false : true;
          }
        }
      }
    }
  }
  pixels.rainbow(firstHue, cycles, saturation, brightness, gammify);
  return nil;
}

// Symbol names
const char stringPixelsBegin[] PROGMEM = "pixels-begin";
const char stringPixelsClear[] PROGMEM = "pixels-clear";
const char stringPixelsFill[] PROGMEM = "pixels-fill";
const char stringPixelsSetPixelColor[] PROGMEM = "pixels-set-pixel-color";
const char stringPixelsColor[] PROGMEM = "pixels-color";
const char stringPixelsColorHSV[] PROGMEM = "pixels-color-hsv";
const char stringPixelsShow[] PROGMEM = "pixels-show";
const char stringPixelsRainbow[] PROGMEM = "pixels-rainbow";

// Documentation strings
const char docPixelsBegin[] PROGMEM = "(pixels-begin)\n"
"Configures the NeoPixel pin for output.";
const char docPixelsClear[] PROGMEM = "(pixels-clear)\n"
"Sets all pixel colors to 'off'.";
const char docPixelsFill[] PROGMEM = "(pixels-fill [rgbw] [first] [fill])\n"
"Fills all or part of the NeoPixel strip with a fixed 32-bit packed RGB or RGBW value (default 0).\n"
"first, default 0, the first NeoPixel to fill.\n"
"fill, default all, the number of NeoPixels to fill.";
const char docPixelsSetPixelColor[] PROGMEM = "(pixels-set-pixel-color index rgbw)\n"
"(pixels-set-pixel-color index red green blue [white])\n"
"Sets a pixel's color using either a 32-bit packed RGB or RGBW value,\n"
"or separate red, green, blue, and optionally white components.";
const char docPixelsColor[] PROGMEM = "(pixels-color red green blue [white])\n"
"Converts separate red, green, blue, and optionally white values into\n"
"a single packed 32-bit RGB or RGBW color.";
const char docPixelsColorHSV[] PROGMEM = "(pixels-color-hsv hue sat val)\n"
"Converts separate hue (0 to 65535), saturation (0 to 255), and value (0 to 255) values into\n"
"a single packed 32-bit RGB or RGBW color.";
const char docPixelsShow[] PROGMEM = "(pixels-show)\n"
"Transmits the pixel data to the NeoPixels.";
const char docPixelsRainbow[] PROGMEM = "(pixels-rainbow [first-hue] [cycles] [saturation] [brightness] [gammify])\n"
"Fills the NeoPixel strip with one or more cycles of hues.\n"
"first-hue, default 0, is the hue of the first pixel (0 to 65535).\n"
"cycles, default 1, is the number of cycles.\n"
"saturation, default 255, is the saturation (0 to 255).\n"
"brightness, default 255, is the brightness (0 to 255).\n"
"gammify, default true, applies gamma correction to colours.";

// Symbol lookup table
const tbl_entry_t lookup_table2[] PROGMEM = {
  { stringPixelsBegin, fn_PixelsBegin, 0200, docPixelsBegin },
  { stringPixelsClear, fn_PixelsClear, 0200, docPixelsClear },
  { stringPixelsFill, fn_PixelsFill, 0203, docPixelsFill },
  { stringPixelsSetPixelColor, fn_PixelsSetPixelColor, 0225, docPixelsSetPixelColor },
  { stringPixelsColor, fn_PixelsColor, 0234, docPixelsColor },
  { stringPixelsColorHSV, fn_PixelsColorHSV, 0233, docPixelsColorHSV },
  { stringPixelsShow, fn_PixelsShow, 0200, docPixelsShow },
  { stringPixelsRainbow, fn_PixelsRainbow, 0205, docPixelsRainbow },
};

// Table cross-reference functions - do not edit below this line

tbl_entry_t *tables[] = {lookup_table, lookup_table2};
const unsigned int tablesizes[] = { arraysize(lookup_table), arraysize(lookup_table2) };

const tbl_entry_t *table (int n) {
  return tables[n];
}

unsigned int tablesize (int n) {
  return tablesizes[n];
}
