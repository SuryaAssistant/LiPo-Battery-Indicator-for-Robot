/*
 * Arduino Program for Indicating Battery Level
 * Created by Fandi Surya Adinata
 * Github : SuryaAssistant
 * 
 * 
 */
 
#define BAUDRATE 115200
#define BATTERY_PIN A0

// Set resistor value in ohm
#define R3 100000
#define R6 50000

// Set max - min battery voltage level (V) for each cell
float max_cell = 4.2;
float min_cell = 3.0;

// Set max - min battery voltage level (V)
float max_battery;
float min_battery;

// Set how many battery cell
double battery_cell = 3;

// Set max - min value of input voltage range in Volt
float max_range_voltage;
float min_range_voltage;

int max_adc;
int min_adc;

int adc_battery;
float battery_voltage;
int battery_percent;


void setup()
{
  Serial.begin(BAUDRATE);
  pinMode(BATTERY_PIN, INPUT);
  delay(20);
}

void loop()
{
  max_battery = max_cell * battery_cell;
  min_battery = min_cell * battery_cell;

  max_range_voltage = (R6/(R3+R6))*max_battery;
  min_range_voltage = (R6/(R3+R6))*min_battery;

  max_adc = (max_range_voltage / 5.0) * 1023;
  min_adc = (min_range_voltage / 5.0) * 1023;
  
  adc_battery = analogRead(BATTERY_PIN);

  battery_percent= map(adc_battery, max_adc, min_adc, 100, 0);
  
  if(battery_percent > 100){
    battery_percent = 100;
  }
  if(battery_percent < 100){
    battery_percent = 0;
    /*
     * Place your output here. Example : buzzer or led
     */
  }

  Serial.print("Battery ");
  Serial.print(battery_percent);
  Serial.println("%");
  
  delay(1000);
}

