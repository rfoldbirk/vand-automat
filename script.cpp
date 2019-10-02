// her deklarerer vi variablerne
// variabler der kan ændres har småt begyndelsesbogstav
// konstanter har et stort begyndelsesbogstav


// inputs
const int Moist_sensor_in = A0;     // input fra fugtighedssensoren
const int abort_in = A1;

// outputs
const int LED_wet_indicator = 13; // output til en LED, som lyser hvis der er får vådt.
const int Pump = 6;           // output til vand pumpen.
const int Moist_sensor = 4;     // output til fugtighedssensoren. Dette bruger vi til at tænde og slukke for den. (se funktion: initiate_moist_read() )

// andet
const int Moist_pwm = 229;        // Vi indstiller her hvor mange volt vi giver til fugtighedssensoren. I dette tilfælde svarer det til ca. 4.5 Volt.
const int Too_dry = 400;        // Værdien som fugtigheden skal være under, for at udløse pumpen.
const int Too_wet = 750;        // Værdien som fugtigheden skal være over, før programmet ved at der er for meget vand.
int wetness; // denne variable får en ny værdi hver gang vi måler fugtigheden.


void setup() {
  // Vi indstiller hvilke 'pins', der bliver brugt.
  pinMode(Moist_sensor, OUTPUT);
  pinMode(Pump, OUTPUT);
  pinMode(LED_wet_indicator, OUTPUT);
  Serial.begin(9600);
}

void initiate_moist_read() {
  // det er vigtigt at vi udelukkende tænder for fugtighedssensoren,
  // når vi skal bruge den! Ellers kan der opstå korrosion, hvilket vi gerne vil undgå!
  
  // vi tænder for strømmen via pulse width modulation (pwm), på den måde kan vi kontrollere hvor mange volt vi sender igennem.
  analogWrite(Moist_sensor, Moist_pwm);

  // her læser vi fugtigheden fra jorden.
  wetness = analogRead(Moist_sensor_in);

  // vi slukker for strømmen, sådan at den forbliver beskyttet.
  analogWrite(Moist_sensor, 0);
}

bool check_abort() {
  // denne funktion tjekker om der kommer strøm ind i input A1
  // vi bruger denne funktion til at slå programmet midlertidiget fra.

  int power = analogRead(abort_in);

  if (power > 50) {
    return true;
  } else {
    return false;
  }
}

void loop() {
  if (check_abort()) {
    return; // Dette stopper programmet i tilfælde af at check_abort() returnerer true
  }

  initiate_moist_read(); // funktionen forklarer sig selv.

  // hvis fugtigheden ikke er fugtig nok, så begynder vi at pumpe.
  if (wetness <= Too_dry) {
    digitalWrite(LED_wet_indicator, LOW);   // vi slukker også for led'en som indikerer at der er for meget vand.
    digitalWrite(Pump, HIGH);             // Vi tænder for pumpen.
    delay(5000);                  // Den vander i 5 sekunder af gangen.
    digitalWrite(Pump, LOW);          // Vi slukker for pumpen.
  }

  // hvis der er alt for vådt, så tændes den røde LED.
  // hvis ikke, så slukkes den.
  if (wetness >= Too_wet) {
    digitalWrite(LED_wet_indicator, HIGH);  // vi tænder for LED'en
  } else {
    digitalWrite(LED_wet_indicator, LOW); // vi slukker for LED'en
  }

  // Der er et delay på 1 sekund, før vi tjekker igen.
  delay(1000);
}
