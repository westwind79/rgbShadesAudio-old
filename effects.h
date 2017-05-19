//   Graphical effects to run on the RGB Shades LED array
//   Each function should have the following components:
//    * Must be declared void with no parameters or will break function pointer array
//    * Check effectInit, if false then init any required settings and set effectInit true
//    * Set effectDelay (the time in milliseconds until the next run of this effect)
//    * All animation should be controlled with counters and effectDelay, no delay() or loops
//    * Pixel data should be written using leds[XY(x,y)] to map coordinates to the RGB Shades layout

void torch() {
   // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 5;
    fadingActive = true;
  }

  injectRandom();
  calcNextEnergy();
  calcNextColors();
  return 1;
}

// RotatingPlasma
void radiate() {
  static byte offset  = 0; // counter for radial color wave motion
  static int plasVector = 0; // counter for orbiting plasma center

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    selectRandomPalette();
    fadingActive = true;
  }
  // Calculate current center of plasma pattern (can be offscreen)
  //int xOffset = (cos8(plasVector)-127)/2;
  //int yOffset = (sin8(plasVector)-127)/2;

  int xOffset = 0;
  int yOffset = 4;

  // Draw one frame of the animation into the LED array
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      byte color = sin8(sqrt(sq(((float)x - 7.5) * 12 + xOffset) + sq(((float)y - 2) * 12 + yOffset)) + offset);
      leds[XY(x, y)] = ColorFromPalette(currentPalette, color, 255);
    }
  }
  offset++; // wraps at 255 for sin8
  plasVector += 1; // using an int for slower orbit (wraps at 65536)
}

// RotatingPlasma
void radiate2() {

  static byte offset  = 0; // counter for radial color wave motion
  static int plasVector = 4; // counter for orbiting plasma center

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    selectRandomPalette();
    fadingActive = true;
  }

  // Calculate current center of plasma pattern (can be offscreen)
  int xOffset = (cos8(plasVector)-127)/2;
  int yOffset = 0;

  //int xOffset = (cos8(plasVector)-127)/2;
  //int yOffset = (sin8(plasVector)-127)/2;

  //int xOffset = 0;
  //int yOffset = 0;
  
  // Draw one frame of the animation into the LED array
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      byte color = sin8(sqrt(sq(((float)x - 7.5) * 12 + xOffset) + sq(((float)y - 2) * 12 + yOffset)) + offset);
      leds[XY(x, y)] = ColorFromPalette(currentPalette, color, 255);
    }
  }
  offset++; // wraps at 255 for sin8
  plasVector += 1; // using an int for slower orbit (wraps at 65536)
}

// RotatingPlasma
void spinPlasma() {

  static byte offset  = 0; // counter for radial color wave motion
  static int plasVector = 0; // counter for orbiting plasma center

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    selectRandomPalette();
    fadingActive = true;
  }

  // Calculate current center of plasma pattern (can be offscreen)
  int xOffset = (cos8(plasVector)-127)/2;
  int yOffset = (sin8(plasVector)-127)/2;

  //int xOffset = 0;
  //int yOffset = 0;
  
  // Draw one frame of the animation into the LED array
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      byte color = sin8(sqrt(sq(((float)x - 7.5) * 12 + xOffset) + sq(((float)y - 2) * 12 + yOffset)) + offset);
      leds[XY(x, y)] = ColorFromPalette(currentPalette, color, 255);
    }
  }
  offset++; // wraps at 255 for sin8
  plasVector += 1; // using an int for slower orbit (wraps at 65536)
}

// Crossfading alternate colors
DEFINE_GRADIENT_PALETTE( checkermap_gp) {
    0,   0,   0,  0,
   63, 255,   0,  0,
  127,   0,   0,  0,
  191,   0, 255,  0,
  255,   0,   0,  0
 };

void checkerboard() {
  static byte checkerFader = 0;
  
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    currentPalette = checkermap_gp;
    // currentPalette = RainbowColors_p;
    fadingActive = true;
  }

  checkerFader+=2;
  
  CRGB colorOne = ColorFromPalette(currentPalette, checkerFader);
  CRGB colorTwo = ColorFromPalette(currentPalette, checkerFader+64);

  for (byte x = 0; x < kMatrixWidth; x++) {
    for (byte y = 0; y < kMatrixHeight; y++) {
          leds[XY(x,y)] = (((x % 2) + y) % 2) ? colorOne : colorTwo;
    }
  }  
}

// Hue Rotation
void colorRotation() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 60;
    fadingActive = true;
  }

  fillAll(CHSV(cycleHue, 255, 255));
}

// Draw a thing that sort of looks like a gift-wrapped box with a bow
void giftbox() {
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 85;
    currentPalette = RainbowColors_p;
  }
  fillAll(CRGB(0,50,0));

  byte numOrnaments = random8(5,12);
  CRGB ornamentColor = CRGB::Red;
  CRGB ribbonColor = CRGB::DarkRed;
  
  for (byte i = 0; i < numOrnaments; i++) {
    byte randomX = random8(0, kMatrixWidth);
    byte randomY = random8(0,kMatrixHeight);
    // leds[XY(randomX,randomY)] = CRGB(127,127,0);
    leds[XY(randomX,randomY)] = ColorFromPalette(currentPalette, random16(255), 255);
  }
  for (byte j = 0; j < kMatrixWidth; j++) {
    leds[XY(j,2)] = ornamentColor;
  }
  for (byte k = 0; k < kMatrixHeight; k++) {
    leds[XY(3,k)] = ornamentColor;
  }

  leds[XY(2,1)] = ribbonColor;
  leds[XY(2,3)] = ribbonColor;
  leds[XY(4,1)] = ribbonColor;
  leds[XY(4,3)] = ribbonColor;
  
}
void blueSnake() {

  static int mx = 0;
  static int lx = 0;

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    fadingActive = true;
    fillAll(CRGB::Black);

    // Reset corner LEDs to red
    leds[0] = CRGB::Red;
    leds[29] = CRGB::Red;
    leds[30] = CRGB::Red;
    leds[57] = CRGB::Red;
    leds[58] = CRGB::Red;
    leds[13] = CRGB::Red;
    leds[14] = CRGB::Red;
    leds[43] = CRGB::Red;
    leds[44] = CRGB::Red;
    leds[67] = CRGB::Red;

    // Reset counter
    mx = 0;
    lx = 0;

    // Effektens hastighet
    effectDelay = 20;
  }

  if (mx <= 67) {
    leds[mx].r = 0;
    leds[mx].g = 0;
    leds[mx].b = 255;
    mx++;
  }
  if (mx == 68) {
    if (lx <= 67) {
      leds[lx] = CRGB::Black;
      lx++;
    }
    if (lx == 68) {
      // Reset all
      effectInit = false;
    }
  }
}

// Draw jack-o'-lantern eyes with flickering orange pattern
const byte pumpkinBitmap[5] = {
  0b00010000,
  0b00111000,
  0b01111100,
  0b11111110,
  0b00000000
};

void pumpkin() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    fadingActive = true;
  }

  CRGB currentColor;
  CRGB flickerOrange;
  static int flickerBrightness = 200;
  int flickerIncrement = random(25) - 12;
  flickerBrightness += flickerIncrement;
  if (flickerBrightness < 50) flickerBrightness = 50;
  if (flickerBrightness > 255) flickerBrightness = 255;
  flickerOrange = 0xFF6000;
  flickerOrange.nscale8_video(flickerBrightness);

  for (byte y = 0; y < 5; y++) {
    for (byte x = 0; x < 8; x++) {
      if (bitRead(pumpkinBitmap[y], 7 - x) == 1) {
        currentColor = flickerOrange;
      } else {
        currentColor = CRGB::Black;
      }

      leds[XY(x, y)] = currentColor;
      leds[XY(15 - x, y)] = currentColor;
    }
  }
}

// Green upvote
const byte upvoteBitmap[5] = {
  0b00010000,
  0b00111000,
  0b01111100,
  0b00111000,
  0b00111000
};

void upvote() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    fadingActive = true;
  }
  CRGB currentColor;

  for (byte y = 0; y < 5; y++) {
    for (byte x = 0; x < 8; x++) {
      if (bitRead(upvoteBitmap[y], 7 - x) == 1) {
        currentColor = CRGB::Green;
      } else {
        currentColor = CRGB::Black;
      }

      leds[XY(x, y)] = currentColor;
      leds[XY(15 - x, y)] = currentColor;
    }
  }
}

// Orange downvote
const byte downvoteBitmap[5] = {
  0b00111000,
  0b00111000,
  0b01111100,
  0b00111000,
  0b00010000
};

void downvote() {
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    fadingActive = true;
  }

  CRGB currentColor;

  for (byte y = 0; y < 5; y++) {
    for (byte x = 0; x < 8; x++) {
      if (bitRead(downvoteBitmap[y], 7 - x) == 1) {
        currentColor = CRGB::Orange;
      } else {
        currentColor = CRGB::Black;
      }

      leds[XY(x, y)] = currentColor;
      leds[XY(15 - x, y)] = currentColor;
    }
  }
}

// Draw slanting bars scrolling across the array, uses current hue
void slantBars2() {

  static byte slantPos = 0;

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 5;
    fadingActive = true;
  }

  for (byte x = 0; x < kMatrixWidth; x++) {
    for (byte y = 0; y < kMatrixHeight; y++) {
      leds[XY(x, y)] = CHSV(cycleHue, 255, quadwave8(x * 64 + y * 64 + slantPos));
    }
  }

  slantPos -= 2;
}

void bpm() {
  bool gReverseDirection = false;
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 0;
    fadingActive = true;
  }

  uint8_t gHue = 120;
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 45;
  CRGBPalette16 palette = RainbowColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);

  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));

    int pixelnumber;
    
    if( gReverseDirection ) {
      pixelnumber = (NUM_LEDS - 1) - i;
    } else {
      pixelnumber = i;
    }
    leds[pixelnumber] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
//  byte scrollY = 0;
//  for (byte y = 0; y < kMatrixHeight; y++) {
//    if (scrollDir == 0) {
//      scrollY = kMatrixHeight - y;
//    } else if (scrollDir == 1) {
//      scrollY = y;
//    }
//    
//    for (byte x = 0; x < kMatrixWidth; x++) {
//      leds[XY(x, scrollY)] = leds[XY(x, scrollY + scrollDir * 2 - 1)];
//    }
//  }    
}

#define COOLING  71
#define SPARKING 130
void Fire2012WithPalette() {

  bool gReverseDirection = true;

  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  CRGBPalette16 gPal;
  gPal = HeatColors_p;

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 30;
    fadingActive = true;
  }

  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if( random8() < SPARKING ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with color palettes.
    byte colorindex = scale8( heat[j], 200);
    CRGB color = ColorFromPalette( gPal, colorindex);
    int pixelnumber;
    if( gReverseDirection ) {
      pixelnumber = (NUM_LEDS - 1) - j;
    } else {
      pixelnumber = j;
    }
    leds[pixelnumber] = color;
  }
}

const byte heartBitmap[5] = {
  0b01101100,
  0b11111110,
  0b01111100,
  0b00111000,
  0b00010000
};

void heart() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    fadingActive = true;
  }

  CRGB currentColor;

  for (byte y = 0; y < 5; y++) {
    for (byte x = 0; x < 8; x++) {
      if (bitRead(heartBitmap[y], 7 - x) == 1) {
        currentColor = CRGB::Red;
      } else {
        currentColor = CRGB::Black;
      }

      leds[XY(x, y)] = currentColor;
      leds[XY(15 - x, y)] = currentColor;
    }
  }
}

const byte eyeBitmap[5] = {
  0b00111000,
  0b01111100,
  0b01100100,
  0b01100100,
  0b00111000
};

void eyes() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    fadingActive = true;

    CRGB currentColor;

    for (byte y = 0; y < 6; y++) {
      for (byte x = 0; x < 8; x++) {
        if (bitRead(eyeBitmap[y], 7 - x) == 1) {
          currentColor = CRGB(150, 150, 160);
        } else {
          currentColor = CHSV(224, 180, 255);
        }

        leds[XY(x, y)] = currentColor;
        leds[XY(15 - x, y)] = currentColor;
        leds[XY(4, 3)] = CRGB::Black;
        leds[XY(4, 2)] = CHSV(160, 180, 255);
        leds[XY(3, 2)] = CHSV(160, 180, 255);
        leds[XY(3, 3)] = CHSV(160, 180, 255);
        leds[XY(11, 2)] = CHSV(160, 180, 255);
        leds[XY(11, 3)] = CRGB::Black;
        leds[XY(12, 2)] = CHSV(160, 180, 255);
        leds[XY(12, 3)] = CHSV(160, 180, 255);
      }
    }
  }
}

void redBorder() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    fillAll(CRGB::Black);
    effectDelay = 50;
    fadingActive = true;
  }
  // leds[ XY(13,2) ] == CRGB::Red;

  leds[0] = CRGB::Red;
  leds[1] = CRGB::Red;
  leds[2] = CRGB::Red;
  leds[3] = CRGB::Red;
  leds[4] = CRGB::Red;
  leds[5] = CRGB::Red;
  leds[6] = CRGB::Red;
  leds[7] = CRGB::Red;
  leds[8] = CRGB::Red;
  leds[9] = CRGB::Red;
  leds[10] = CRGB::Red;
  leds[11] = CRGB::Red;
  leds[12] = CRGB::Red;
  leds[13] = CRGB::Red;
  leds[16] = CRGB::Red;
  leds[18] = CRGB::Red;
  leds[41] = CRGB::Red;
  leds[39] = CRGB::Red;
  leds[20] = CRGB::Red;
  leds[48] = CRGB::Red;
  leds[46] = CRGB::Red;
  leds[25] = CRGB::Red;
  leds[37] = CRGB::Red;
  leds[50] = CRGB::Red;
  leds[67] = CRGB::Red;
  leds[66] = CRGB::Red;
  leds[65] = CRGB::Red;
  leds[64] = CRGB::Red;
  leds[63] = CRGB::Red;
  leds[50] = CRGB::Red;
  leds[23] = CRGB::Red;
  leds[27] = CRGB::Red;
  leds[29] = CRGB::Red;
  leds[30] = CRGB::Red;
  leds[32] = CRGB::Red;
  leds[34] = CRGB::Red;
  leds[36] = CRGB::Red;
  leds[51] = CRGB::Red;
  leds[53] = CRGB::Red;
  leds[55] = CRGB::Red;
  leds[57] = CRGB::Red;
  leds[58] = CRGB::Red;
  leds[59] = CRGB::Red;
  leds[60] = CRGB::Red;
  leds[61] = CRGB::Red;
  leds[62] = CRGB::Red;
  leds[14] = CRGB::Red;
  leds[43] = CRGB::Red;
  leds[44] = CRGB::Red;
  leds[67] = CRGB::Red;
}

void redBorder2() {
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    fillAll(CRGB::Black);
    effectDelay = 50;
    fadingActive = true;
  }
  // leds[ XY(13,2) ] == CRGB::Red;
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Red;
  leds[2] = CRGB::Red;
  leds[3] = CRGB::Red;
  leds[4] = CRGB::Red;
  leds[5] = CRGB::Red;
  leds[6] = CRGB::Red;
  leds[7] = CRGB::Red;
  leds[8] = CRGB::Red;
  leds[9] = CRGB::Red;
  leds[10] = CRGB::Red;
  leds[11] = CRGB::Red;
  leds[12] = CRGB::Red;
  leds[13] = CRGB::Red;
  leds[21] = CRGB::Red;
  leds[22] = CRGB::Red;
  leds[37] = CRGB::Red;
  leds[50] = CRGB::Red;
  leds[67] = CRGB::Red;
  leds[66] = CRGB::Red;
  leds[65] = CRGB::Red;
  leds[64] = CRGB::Red;
  leds[63] = CRGB::Red;
  leds[50] = CRGB::Red;
  leds[29] = CRGB::Red;
  leds[30] = CRGB::Red;
  leds[36] = CRGB::Red;
  leds[51] = CRGB::Red;
  leds[57] = CRGB::Red;
  leds[58] = CRGB::Red;
  leds[59] = CRGB::Red;
  leds[60] = CRGB::Red;
  leds[61] = CRGB::Red;
  leds[62] = CRGB::Red;
  leds[14] = CRGB::Red;
  leds[43] = CRGB::Red;
  leds[44] = CRGB::Red;
  leds[67] = CRGB::Red;
}

void blueBorder() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    fillAll(CRGB(50, 60, 50));
    effectDelay = 50;
    fadingActive = true;
  }

  leds[0] = CRGB::Blue;
  leds[1] = CRGB::Blue;
  leds[2] = CRGB::Blue;
  leds[3] = CRGB::Blue;
  leds[4] = CRGB::Blue;
  leds[5] = CRGB::Blue;
  leds[6] = CRGB::Blue;
  leds[7] = CRGB::Blue;
  leds[8] = CRGB::Blue;
  leds[9] = CRGB::Blue;
  leds[10] = CRGB::Blue;
  leds[11] = CRGB::Blue;
  leds[12] = CRGB::Blue;
  leds[13] = CRGB::Blue;
  leds[21] = CRGB::Blue;
  leds[37] = CRGB::Blue;
  leds[50] = CRGB::Blue;
  leds[67] = CRGB::Blue;
  leds[66] = CRGB::Blue;
  leds[65] = CRGB::Blue;
  leds[64] = CRGB::Blue;
  leds[63] = CRGB::Blue;
  leds[50] = CRGB::Blue;
  leds[22] = CRGB::Blue;
  leds[29] = CRGB::Blue;
  leds[30] = CRGB::Blue;
  leds[36] = CRGB::Blue;
  leds[51] = CRGB::Blue;
  leds[57] = CRGB::Blue;
  leds[58] = CRGB::Blue;
  leds[59] = CRGB::Blue;
  leds[60] = CRGB::Blue;
  leds[61] = CRGB::Blue;
  leds[62] = CRGB::Blue;
  leds[14] = CRGB::Blue;
  leds[43] = CRGB::Blue;
  leds[44] = CRGB::Blue;
  leds[67] = CRGB::Blue;
}

void greenBorder() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    fillAll(CRGB::Black);
    effectDelay = 50;
    fadingActive = true;
  }

  leds[0] = CRGB::Green;
  leds[1] = CRGB::Green;
  leds[2] = CRGB::Green;
  leds[3] = CRGB::Green;
  leds[4] = CRGB::Green;
  leds[5] = CRGB::Green;
  leds[6] = CRGB::Green;
  leds[7] = CRGB::Green;
  leds[8] = CRGB::Green;
  leds[9] = CRGB::Green;
  leds[10] = CRGB::Green;
  leds[11] = CRGB::Green;
  leds[12] = CRGB::Green;
  leds[13] = CRGB::Green;
  leds[21] = CRGB::Green;
  leds[37] = CRGB::Green;
  leds[50] = CRGB::Green;
  leds[67] = CRGB::Green;
  leds[66] = CRGB::Green;
  leds[65] = CRGB::Green;
  leds[64] = CRGB::Green;
  leds[63] = CRGB::Green;
  leds[50] = CRGB::Green;
  leds[22] = CRGB::Green;
  leds[29] = CRGB::Green;
  leds[30] = CRGB::Green;
  leds[36] = CRGB::Green;
  leds[51] = CRGB::Green;
  leds[57] = CRGB::Green;
  leds[58] = CRGB::Green;
  leds[59] = CRGB::Green;
  leds[60] = CRGB::Green;
  leds[61] = CRGB::Green;
  leds[62] = CRGB::Green;
  leds[14] = CRGB::Green;
  leds[43] = CRGB::Green;
  leds[44] = CRGB::Green;
  leds[67] = CRGB::Green;
}

// Smoothly falling white dots
void snow() {

  static unsigned int snowCols[kMatrixWidth] = {0};

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 20;
    fadingActive = true;
  }

  CRGB snowColor = CRGB::White;

  FastLED.clear();

  for (byte i = 0; i < kMatrixWidth; i++) {
    if (snowCols[i] > 0) {
      snowCols[i] += random(4,16);
    } else {
      if (random8(0,100) == 0) snowCols[i] = 1;
    }
    byte tempY = snowCols[i] >> 8;
    byte tempRem = snowCols[i] & 0xFF;
    if (tempY <= kMatrixHeight) leds[XY(i,tempY-1)] = snowColor % dim8_raw(255-tempRem);
    if (tempY < kMatrixHeight) leds[XY(i,tempY)] = snowColor % dim8_raw(tempRem);
    if (tempY > kMatrixHeight) snowCols[i] = 0;
  }
}

#define rainDir4 0
void rainDown2() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 60;
    fadingActive = true;
  }

static uint8_t hue = 0;
CRGBPalette16 palette = CloudColors_p;

  scrollArray2(rainDir4);
  byte randPixel = random8(kMatrixWidth);
  for (byte x = 0; x < kMatrixWidth; x++) {
    leds[XY(x, (kMatrixHeight - 1) * rainDir4)] = CRGB::Black;
  }
  leds[XY(randPixel, (kMatrixHeight - 1)*rainDir4)] = ColorFromPalette(palette, 240, 240);
}

#define rainDir2 1
void sideRain2() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 30;
    fadingActive = true;
  }

  scrollArray(rainDir2);
  byte randPixel = random8(kMatrixHeight);
  for (byte y = 0; y < kMatrixHeight; y++) leds[XY((kMatrixWidth - 1) * rainDir2, y)] = CRGB::Black;
  leds[XY((kMatrixWidth - 1)*rainDir2, randPixel)] = CHSV(cycleHue, 255, 255);

}

#define rainDir4 0
void rainDown() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 30;
    fadingActive = true;
  }

static uint8_t hue = 0;

  scrollArray2(rainDir4);
  byte randPixel = random8(kMatrixWidth);
  for (byte x = 0; x < kMatrixWidth; x++) {
    leds[XY(x, (kMatrixHeight - 1) * rainDir4)] = CRGB::Black;
  }
  leds[XY(randPixel, (kMatrixHeight - 1)*rainDir4)] = CHSV(cycleHue, 255, 255);
}

#define rainDir3 1
void rainUp() { 
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 30;
    currentPalette = CloudColors_p;
    fadingActive = true;
  }
  
  static uint8_t hue = 0;

  scrollArray2(rainDir3);
  byte randPixel = random8(kMatrixWidth);
  for (byte x = 0; x < kMatrixWidth; x++) {
    leds[XY(x, (kMatrixHeight - 1) * rainDir3)] = CRGB::Black;
  }
  // leds[XY(randPixel, (kMatrixHeight - 1)*rainDir3)] = CHSV(cycleHue, 255, 255);
  leds[XY(randPixel, (kMatrixHeight - 1)*rainDir3)] = ColorFromPalette(currentPalette, 240, 255);
}

// leds run around the periphery of the shades, changing color every go 'round
// modified from code by @terrag42
void shadesOutline() {
  static boolean erase = false;
  static uint8_t x, y = 0;
  static uint8_t currentColor = 0;
  //startup tasks
  if (effectInit == false) {
    effectInit = true;
    erase = false;
    x = 0;
    effectDelay = 15;
    FastLED.clear();
    currentPalette = RainbowColors_p;
    fadingActive = true;
  }

  const uint8_t OutlineTable[] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 43,
    44, 67, 66, 65, 64, 63, 50, 37, 21, 22, 36, 51, 62, 61, 60, 59,
    58, 57, 30, 29
  };
  leds[OutlineTable[x]] = currentPalette[currentColor];
  if (erase)
    leds[OutlineTable[x]] = CRGB::Black;
  x++;
  if (x == (sizeof(OutlineTable))) {
    erase = !erase;
    x = 0;
    currentColor += random8(3, 6);
    if (currentColor > 15) currentColor -= 16;
  }
}

void shadesOutline2() {
  static boolean erase = false;
  static uint8_t x, y, z = 0;
  static uint8_t currentColor = 0;
  //startup tasks
  if (effectInit == false) {
    effectInit = true;
    erase = false;
    x = 0;
    y = 0;
    z = 0;
    effectDelay = 15;
    FastLED.clear();
    currentPalette = RainbowColors_p;
    fadingActive = true;
  }  
  const uint8_t OutlineTable[] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 43,
    44, 67, 66, 65, 64, 63, 50, 37, 21, 22, 36, 51, 62, 61, 60, 59,
    58, 57, 30, 29
  };
  const uint8_t OutlineTable2[] = {
    23, 24, 25, 26, 27, 28, 31, 56, 55, 54, 53, 52, 35, 34, 33, 32
  };  
  const uint8_t OutlineTable3[] = {
    20, 19, 18, 17, 16, 15, 42, 45, 46, 47, 48, 49, 38, 39, 40, 41
  };
  
  leds[OutlineTable[x]] = currentPalette[currentColor];
  if (erase)
    leds[OutlineTable[x]] = currentPalette[currentColor];
  x++;
  if (x == (sizeof(OutlineTable))) {
    erase = !erase;
    x = 0; 
    currentColor += random8(3, 6);
     if (currentColor > 15) currentColor -= 16;
  }

  leds[OutlineTable2[y]] = currentPalette[currentColor];
  if (erase)
    leds[OutlineTable2[y]] = currentPalette[currentColor];
  y++;
  if (y == (sizeof(OutlineTable2))) {
    erase = !erase;
    y = 0;
//    currentColor += random8(3, 3);
//     if (currentColor > 6) currentColor -= 7;
  }
  
  leds[OutlineTable3[z]] = currentPalette[currentColor];
  if (erase)
    leds[OutlineTable3[z]] = currentPalette[currentColor];
  z++;
  if (z == (sizeof(OutlineTable3))) {
    erase = !erase;
    z = 0;
//    currentColor += random8(1, 1);
//    if (currentColor > 6) currentColor -= 7;
  }
}

void shadesOutline3() {
  static boolean erase = false;
  static uint8_t x, y, z = 0;
  static uint8_t currentColor = 0;
  //startup tasks
  if (effectInit == false) {
    effectInit = true;
    erase = false;
    x = 0;
    y = 0;
    z = 0;
    effectDelay = 15;
    FastLED.clear();
    // selectRandomPalette();
    currentPalette = RainbowColors_p;
    fadingActive = true;
  }
  
  const uint8_t OutlineTable[] = {
    6,5,4,3,2,1,0,29,30,57,58,59,60,61,62,51,36,22,23,24,25,26,27,28,31,56,55,54,53,52,35,34,33,32,31
  };
  const uint8_t OutlineTable2[] = {
    7,8,9,10,11,12,13,14,43,44,67,66,65,64,63,50,37,21,20,19,18,17,16,15,42,45,46,47,48,49,38,39,40,41
  };
  
  leds[OutlineTable[x]] = currentPalette[currentColor];
  leds[OutlineTable2[y]] = currentPalette[currentColor];
  if (erase)    
    leds[OutlineTable[x]] = currentPalette[currentColor];
    leds[OutlineTable2[y]] = currentPalette[currentColor];
  x++;
  y++;
  if (x == (sizeof(OutlineTable)) || y == (sizeof(OutlineTable2))) {
    erase = !erase;
    x = 0; 
    y = 0;
    currentColor += random8(3, 6);
     if (currentColor > 15) currentColor -= 16;
  }
}
// Crossfading alternate colors
DEFINE_GRADIENT_PALETTE( outline_gp) {
   0,   0,   35,  0,
   0, 255,   0,  0,
  255,   0,   0,  0,
  0,   0, 255,  0,
  255,   0,   0,  0
 };

void shadesOutline4() {
  static boolean erase = false;
  static uint8_t x, y, z = 0;
  static uint8_t currentColor = 0;
  //startup tasks
  if (effectInit == false) {
    effectInit = true;
    erase = false;
    x = 0;
    y = 0;
    z = 0;
    effectDelay = 15;
    FastLED.clear();
    // selectRandomPalette();
    // currentPalette = RainbowColors_p;
    currentPalette = outline_gp;
    fadingActive = true;
  }
  const uint8_t OutlineTable[] = {
   30,31,27,2,26,33,54,60,53,35,36,37,38,18,11,17,40,47,65,46,42,43
  };
  
//  const uint8_t OutlineTable[] = {
//   29,30,57,58,59,55,32,27,1,2,3,25,34,53,61,62,51,36,23,5,6,7,8,20,37,50,63,64,48,39,18,10,11,12,16,41,46,66,67,44,43,14
//  };
//  const uint8_t OutlineTable2[] = {
//    7,8,9,10,11,12,13,14,43,44,67,66,65,64,63,50,37,21,20,19,18,17,16,15,42,45,46,47,48,49,38,39,40,41
//  };
//  
  leds[OutlineTable[x]] = currentPalette[currentColor];
//  leds[OutlineTable2[y]] = currentPalette[currentColor];
  if (erase)    
    leds[OutlineTable[x]] = currentPalette[currentColor];
//    leds[OutlineTable2[y]] = currentPalette[currentColor];
  x++;
//  y++;
// if (x == (sizeof(OutlineTable)) || y == (sizeof(OutlineTable2))) {
  if (x == (sizeof(OutlineTable))) {
    erase = !erase;
    x = 0; 
   // y = 0;
    currentColor += random8(3, 6);
     if (currentColor > 15) currentColor -= 16;
  }
}
// Display bursts of sparks
void fireworks() {

  byte sparksDone = 0;
  static int sparkLife = 50;
  static boolean boom = false;

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 5;
    gSkyburst = 1;
    fadingActive = true;
  }
  if (boom) {
    FastLED.clear();
    boom = false;
  } else {
    fadeAll(40);
  }  
  if (sparkLife > 0) sparkLife--;

  for( byte b = 0; b < NUM_SPARKS; b++) {
    if (sparkLife <= 0) gSparks[b].show = 0;
    gSparks[b].Move();
    gSparks[b].Draw();
    sparksDone += gSparks[b].show;
  }

  if (sparksDone == 0) gSkyburst = 1;
  //Serial.println(sparksDone);

  if( gSkyburst) {
    effectDelay = 5;
    sparkLife = random(16,150);
    CRGB color;
    hsv2rgb_rainbow( CHSV( random8(), 255, 255), color);
    accum88 sx = random(127-64,127+64)<<8;
    accum88 sy = random(127-16,127+16)<<8;
    for( byte b = 0; b < NUM_SPARKS; b++) {
      gSparks[b].Skyburst(sx, sy, 0, color);
    }
    gSkyburst = 0;
    sparksDone = 0;
    fillAll(CRGB::Gray);
    boom = true;
  }
}

// Triple Sine Waves
void threeSine() {

  static byte sineOffset = 0; // counter for current position of sine waves

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 20;
    fadingActive = true;
  }

  // Draw one frame of the animation into the LED array
  for (byte x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {

      // Calculate "sine" waves with varying periods
      // sin8 is used for speed; cos8, quadwave8, or triwave8 would also work here
      byte sinDistanceR = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 9 + x * 16)), 2);
      byte sinDistanceG = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 10 + x * 16)), 2);
      byte sinDistanceB = qmul8(abs(y * (255 / kMatrixHeight) - sin8(sineOffset * 11 + x * 16)), 2);

      leds[XY(x, y)] = CRGB(255 - sinDistanceR, 255 - sinDistanceG, 255 - sinDistanceB);
    }
  }
  sineOffset++; // byte will wrap from 255 to 0, matching sin8 0-255 cycle
}


// RGB Plasma
void plasma() {

  static byte offset  = 0; // counter for radial color wave motion
  static int plasVector = 0; // counter for orbiting plasma center

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    fadingActive = true;
  }

  // Calculate current center of plasma pattern (can be offscreen)
  int xOffset = cos8(plasVector / 256);
  int yOffset = sin8(plasVector / 256);

  // Draw one frame of the animation into the LED array
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      byte color = sin8(sqrt(sq(((float)x - 7.5) * 10 + xOffset - 127) + sq(((float)y - 2) * 10 + yOffset - 127)) + offset);
      leds[XY(x, y)] = CHSV(color, 255, 255);
    }
  }
  offset++; // wraps at 255 for sin8
  plasVector += 16; // using an int for slower orbit (wraps at 65536)
}

// Scanning pattern left/right, uses global hue cycle
void rider() {

  static byte riderPos = 0;

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 5;
    riderPos = 0;
    fadingActive = true;
  }

  // Draw one frame of the animation into the LED array
  for (byte x = 0; x < kMatrixWidth; x++) {
    int brightness = abs(x * (256 / kMatrixWidth) - triwave8(riderPos) * 2 + 127) * 3;
    if (brightness > 255) brightness = 255;
    brightness = 255 - brightness;
    CRGB riderColor = CHSV(cycleHue, 255, brightness);
    for (byte y = 0; y < kMatrixHeight; y++) {
      leds[XY(x, y)] = riderColor;
    }
  }
  riderPos++; // byte wraps to 0 at 255, triwave8 is also 0-255 periodic
}

// Shimmering noise, uses global hue cycle
void glitter() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 15;
    fadingActive = true;
  }

  // Draw one frame of the animation into the LED array
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      leds[XY(x, y)] = CHSV(cycleHue, 255, random8(5) * 63);
    }
  }
}

// Fills saturated colors into the array from alternating directions
void colorFill() {

  static byte currentColor = 0;
  static byte currentRow = 0;
  static byte currentDirection = 0;

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 45;
    currentColor = 0;
    currentRow = 0;
    currentDirection = 0;
    currentPalette = RainbowColors_p;
    fadingActive = true;
  }
  // test a bitmask to fill up or down when currentDirection is 0 or 2 (0b00 or 0b10)
  if (!(currentDirection & 1)) {
    effectDelay = 45; // slower since vertical has fewer pixels
    for (byte x = 0; x < kMatrixWidth; x++) {
      byte y = currentRow;
      if (currentDirection == 2) y = kMatrixHeight - 1 - currentRow;
      leds[XY(x, y)] = currentPalette[currentColor];
    }
  }

  // test a bitmask to fill left or right when currentDirection is 1 or 3 (0b01 or 0b11)
  if (currentDirection & 1) {
    effectDelay = 20; // faster since horizontal has more pixels
    for (byte y = 0; y < kMatrixHeight; y++) {
      byte x = currentRow;
      if (currentDirection == 3) x = kMatrixWidth - 1 - currentRow;
      leds[XY(x, y)] = currentPalette[currentColor];
    }
  }

  currentRow++;

  // detect when a fill is complete, change color and direction
  if ((!(currentDirection & 1) && currentRow >= kMatrixHeight) || ((currentDirection & 1) && currentRow >= kMatrixWidth)) {
    currentRow = 0;
    currentColor += random8(3, 6);
    if (currentColor > 15) currentColor -= 16;
    currentDirection++;
    if (currentDirection > 3) currentDirection = 0;
    effectDelay = 300; // wait a little bit longer after completing a fill
  }
}

// Emulate 3D anaglyph glasses
void threeDee() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 50;
    fadingActive = true;
  }

  for (byte x = 0; x < kMatrixWidth; x++) {
    for (byte y = 0; y < kMatrixHeight; y++) {
      if (x < 7) {
        leds[XY(x, y)] = CRGB::Blue;
      } else if (x > 8) {
        leds[XY(x, y)] = CRGB::Red;
      } else {
        leds[XY(x, y)] = CRGB::Black;
      }
    }
  }
  leds[XY(6, 0)] = CRGB::Black;
  leds[XY(9, 0)] = CRGB::Black;
}

// Random pixels scroll sideways, uses current hue
#define rainDir 0
void sideRain() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 30;
    fadingActive = true;
  }

  scrollArray(rainDir);
  byte randPixel = random8(kMatrixHeight);
  for (byte y = 0; y < kMatrixHeight; y++) leds[XY((kMatrixWidth - 1) * rainDir, y)] = CRGB::Black;
  leds[XY((kMatrixWidth - 1)*rainDir, randPixel)] = CHSV(cycleHue, 255, 255);

}

// Pixels with random locations and random colors selected from a palette
// Use with the fadeAll function to allow old pixels to decay
void confetti() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    selectRandomPalette();
    fadingActive = true;
  }

  // scatter random colored pixels at several random coordinates
  for (byte i = 0; i < 4; i++) {
    leds[XY(random16(kMatrixWidth), random16(kMatrixHeight))] = ColorFromPalette(currentPalette, random16(255), 255); //CHSV(random16(255), 255, 255);
    random16_add_entropy(1);
  }
}


// Draw slanting bars scrolling across the array, uses current hue
void slantBars() {

  static byte slantPos = 0;

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 5;
    fadingActive = true;
  }

  for (byte x = 0; x < kMatrixWidth; x++) {
    for (byte y = 0; y < kMatrixHeight; y++) {
      leds[XY(x, y)] = CHSV(cycleHue, 255, quadwave8(x * 32 + y * 32 + slantPos));
    }
  }
  slantPos -= 4;
}


#define NORMAL 0
#define RAINBOW 1
#define charSpacing 2
// Scroll a text string
void scrollText(byte message, byte style, CRGB fgColor, CRGB bgColor) {
  static byte currentMessageChar = 0;
  static byte currentCharColumn = 0;
  static byte paletteCycle = 0;
  static CRGB currentColor;
  static byte bitBuffer[16] = {0};
  static byte bitBufferPointer = 0;

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 35;
    currentMessageChar = 0;
    currentCharColumn = 0;
    selectFlashString(message);
    loadCharBuffer(loadStringChar(message, currentMessageChar));
    currentPalette = RainbowColors_p;
    fadingActive = true;
    for (byte i = 0; i < kMatrixWidth; i++) bitBuffer[i] = 0;
  }

  paletteCycle += 15;

  if (currentCharColumn < 5) { // characters are 5 pixels wide
    bitBuffer[(bitBufferPointer + kMatrixWidth - 1) % kMatrixWidth] = charBuffer[currentCharColumn]; // character
  } else {
    bitBuffer[(bitBufferPointer + kMatrixWidth - 1) % kMatrixWidth] = 0; // space
  }

  CRGB pixelColor;
  for (byte x = 0; x < kMatrixWidth; x++) {
    for (byte y = 0; y < 5; y++) { // characters are 5 pixels tall
      if (bitRead(bitBuffer[(bitBufferPointer + x) % kMatrixWidth], y) == 1) {
        if (style == RAINBOW) {
          pixelColor = ColorFromPalette(currentPalette, paletteCycle+y*16, 255);
        } else {
          pixelColor = fgColor;
        }
      } else {
        pixelColor = bgColor;
      }
      leds[XY(x, y)] = pixelColor;
    }
  }

  currentCharColumn++;
  if (currentCharColumn > (4 + charSpacing)) {
    currentCharColumn = 0;
    currentMessageChar++;
    char nextChar = loadStringChar(message, currentMessageChar);
    if (nextChar == 0) { // null character at end of strong
      currentMessageChar = 0;
      nextChar = loadStringChar(message, currentMessageChar);
    }
    loadCharBuffer(nextChar);
  }
  bitBufferPointer++;
  if (bitBufferPointer > 15) bitBufferPointer = 0;
}


 void scrollTextZero() {
   scrollText(0, NORMAL, CRGB::Red, CRGB::Black);
 }

void scrollTextOne() {
  scrollText(1, RAINBOW, 0, CRGB::Black);
}

void scrollTextTwo() {
  scrollText(2, RAINBOW, CRGB::Green, CRGB(0,0,8));
}

void scrollTextThree() {
  scrollText(3, NORMAL, CRGB::Green, CRGB(0,0,8));
}

#define analyzerFadeFactor 5
#define analyzerScaleFactor 1.5
#define analyzerPaletteFactor 2
void drawAnalyzer() {
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    fadingActive = true;
    selectRandomPalette();
  }

  CRGB pixelColor;

  const float yScale = 255.0 / kMatrixHeight;

  for (byte x = 0; x < kMatrixWidth / 2; x++) {
    byte newX = x;
    int freqVal;
    if (x < 2) {
      newX = 0;
      freqVal = spectrumDecay[newX] / 2;
    } else {
      newX = x - 1;
      freqVal = spectrumDecay[newX];
    }
    
    for (byte y = 0; y < kMatrixHeight; y++) {
      if (x > 6) {
        pixelColor = ColorFromPalette(currentPalette, 0, 0);
      } else {
        int senseValue = freqVal / analyzerScaleFactor - yScale * (kMatrixHeight - 1 - y);
        int pixelBrightness = senseValue * analyzerFadeFactor;
        if (pixelBrightness > 255) pixelBrightness = 255;
        if (pixelBrightness < 0) pixelBrightness = 0;

        int pixelPaletteIndex = senseValue / analyzerPaletteFactor - 15;
        if (pixelPaletteIndex > 240) pixelPaletteIndex = 240;
        if (pixelPaletteIndex < 0) pixelPaletteIndex = 0;

        pixelColor = ColorFromPalette(currentPalette, pixelPaletteIndex, pixelBrightness);
      }
      leds[XY(x, y)] = pixelColor;
      leds[XY(kMatrixWidth - x - 1, y)] = pixelColor;
    }
  }
}

#define VUFadeFactor 5
#define VUScaleFactor 2.0
#define VUPaletteFactor 1.5
void drawVU() {
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    fadingActive = true;
    effectDelay = 10;
    selectRandomPalette();
  }

  CRGB pixelColor;

  const float xScale = 255.0 / (kMatrixWidth / 2);
  float specCombo = (spectrumDecay[0] + spectrumDecay[1] + spectrumDecay[2] + spectrumDecay[3]) / 4.0;

  for (byte x = 0; x < kMatrixWidth / 2; x++) {
    int senseValue = specCombo / VUScaleFactor - xScale * x;
    int pixelBrightness = senseValue * VUFadeFactor;
    if (pixelBrightness > 255) pixelBrightness = 255;
    if (pixelBrightness < 0) pixelBrightness = 0;

    int pixelPaletteIndex = senseValue / VUPaletteFactor - 15;
    if (pixelPaletteIndex > 240) pixelPaletteIndex = 240;
    if (pixelPaletteIndex < 0) pixelPaletteIndex = 0;

    pixelColor = ColorFromPalette(currentPalette, pixelPaletteIndex, pixelBrightness);

    for (byte y = 0; y < kMatrixHeight; y++) {
      leds[XY(x, y)] = pixelColor;
      leds[XY(kMatrixWidth - x - 1, y)] = pixelColor;
    }
  }
}

void RGBpulse() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    fadingActive = true;
    effectDelay = 1;
  }

  static byte RGBcycle = 0;

  fadeAll(1);

  if (beatDetect()) {

    switch (RGBcycle) {
      case 0:
        fillAll(CRGB::OrangeRed);
        break;
      case 1:
        fillAll(CRGB::Lime);
        break;
      case 2:
        fillAll(CRGB::MediumBlue);
        break;
    }

    RGBcycle++;
    if (RGBcycle > 2) RGBcycle = 0;
  }
}

