#include <Arduino.h>    // comment this line when working with Arduino IDE
#include <TimerOne.h>

// don't change
#define SELECT_FREQUENCY_PIN    2
#define SELECT_DUTY_CYCLE_PIN   3
#define OSCILLATOR_OUT_PIN      9

#define PERIOD_F_1_MHZ          1
#define PERIOD_F_500_KHZ        2
#define DUTY_CYCLE_50_PCT       512
#define DUTY_CYCLE_25_PCT       256

uint16_t prev_period = 0;
uint16_t prev_duty_cycle = 0;

int get_level(int adc_val) {
  return -1; // todo
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(SELECT_FREQUENCY_PIN, INPUT_PULLUP);
  pinMode(SELECT_DUTY_CYCLE_PIN, INPUT_PULLUP);
  pinMode(OSCILLATOR_OUT_PIN, OUTPUT);

   Timer1.initialize();
}

void loop() {
  uint16_t period, duty_cycle;

  // check frequency selection pin
  if(digitalRead(SELECT_FREQUENCY_PIN)){
    period = PERIOD_F_1_MHZ;
  }
  else{
    period = PERIOD_F_500_KHZ;
  }

  // check duty cycle selection pin
  if(digitalRead(SELECT_DUTY_CYCLE_PIN)){
    duty_cycle = DUTY_CYCLE_50_PCT;
  }
  else{
    duty_cycle = DUTY_CYCLE_25_PCT;
  }

  // set changes
  if((period != prev_period) || (duty_cycle != prev_duty_cycle)){
    // update both period and duty cycle
    Timer1.setPeriod(period);
    if(period == PERIOD_F_1_MHZ){
      Serial.println(F("Frequency = 1 MHz."));
    }
    else{
      Serial.println(F("Frequency = 500 kHz."));
    }
    Timer1.pwm(OSCILLATOR_OUT_PIN, duty_cycle);
    if(duty_cycle == DUTY_CYCLE_50_PCT){
      Serial.println(F("Duty cycle = 50%."));
    }
    else{
      Serial.println(F("Duty cycle = 25%."));
    }
  }

  // store new values
  prev_period = period;
  prev_duty_cycle = duty_cycle;

  // todo: read analog value and translate to water level
  int adc_in = analogRead(A0);
  int level_in_mm = get_level(adc_in);
  Serial.print("adc: ");
  Serial.println(adc_in);
  Serial.print(level_in_mm);
  Serial.println(" mm");
  delay(500);
}