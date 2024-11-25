#include <GUVA-S12SD.h>
GUVAS12SD uv(A3);

void setup()
{
    // Nothing TODO
    Serial.begin(9600);
}

void loop()
{
  float mV = uv.read();
  float uv_index = uv.index(mV);
  Serial.println(uv_index);
}
