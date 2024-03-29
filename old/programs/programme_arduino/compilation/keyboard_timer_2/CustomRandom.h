#ifndef CustomRandom_h
#define CustomRandom_h

//#include <EEPROM.h> / EEPROM is unfortunately not included in Arduino Due
// We have to deal with this library : https://github.com/sebnil/DueFlashStorage/blob/master/examples/DueFlashStorageExample/DueFlashStorageExample.ino

#include <DueFlashStorage.h>
DueFlashStorage dueFlashStorage;

// Taken from: http://forum.arduino.cc/index.php/topic,66206.0.html
void reseedRandom( void )
{
  static const uint32_t HappyPrime = 937;
  union
  {
    uint32_t i;
    uint8_t b[4];
  }
  raw;
  int8_t i;
  unsigned int seed;
 
  for ( i=0; i < sizeof(raw.b); ++i )
  {
    raw.b[i] = dueFlashStorage.read( i );
  }

  do
  {
    raw.i += HappyPrime;
    seed = raw.i & 0x7FFFFFFF;
  }
  while ( (seed < 1) || (seed > 2147483646) );

  randomSeed( seed ); 

  for ( i=0; i < sizeof(raw.b); ++i )
  {
    dueFlashStorage.write( i, raw.b[i] );
  }
}

#endif //CustomRandom_h / QUESTION POUR HENRI : 
