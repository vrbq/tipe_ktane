const char text[] PROGMEM = "Bonjour Locoduino";

void setup()
{
  Serial.begin(9600);

  char buffer[50];
  strcpy_P(buffer, text);
  Serial.println(buffer);
}

void loop()
{
}

//http://www.locoduino.org/spip.php?article131
