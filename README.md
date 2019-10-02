# Vand-automat

Koden ligger i filen script.cpp :)

Hvis i har ideer eller noget i gerne vil lave om på, kan i enten selv gøre det eller gå ind under [*Issues*](https://github.com/rfoldbirk/vand-automat/issues) og lave en To-Do.

:pray:


### Interessante små ting i koden

**Funktionen: initiate_moist_read()**
```cpp
const int Moist_pwm = 230; // 4,5V / 5V = 0,9 <--> 255 * 0,9 ≈ 230

void initiate_moist_read() {
  analogWrite(Moist_sensor, Moist_pwm);
  
  wetness = analogRead(Moist_sensor_in);
  
  analogWrite(Moist_sensor, 0);
}
```
Her bliver der gjort brug af analogWrite frem for DigitalWrite, fordi det tillader os at indstille hvor mange Volt vi lader løbe igennem. SparkFun foreslog at bruge imellem 3,3 og 5 Volt. Vi har sat vores på ca. 4,5 V.

Bemærk også at vi tænder og slukker før og efter måling af fugtigheden i jorden. Dette er for at undgå korrosion
