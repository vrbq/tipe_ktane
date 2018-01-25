#include "pitches.h"

#include <Tone.h>

Tone tone1;

void setup()
{
  tone1.begin(13);
  tone1.play(NOTE_A4);
}

void loop()
{
}

void setup(void)
{
  tone1.begin(13);
}
