#include <Arduino.h>
#include <Wire.h>
#include <stdlib.h>

#define I2C_SLAVE_ADDRESS 12

// // GLOBAL variable
// Define a buffer for receiving data
char data_to_echo = 0;
int buffer[15] = {};
int counter = 1;
char flag_activity = 0;

// assign digital pins on FireBeetle
// for motorDriver1
const int step_MD1 = D2;
const int dir_MD1 = D3;
const int enable_MD1 = D4;

// for motorDriver2
const int step_MD2 = D5;
const int dir_MD2 = D6;
const int enable_MD2 = D7;

// put function declarations here:
void reset_pins()
{
  // MD1
  digitalWrite(step_MD1, LOW);
  digitalWrite(dir_MD1, LOW);
  digitalWrite(enable_MD1, LOW);
  // MD2
  digitalWrite(step_MD2, LOW);
  digitalWrite(dir_MD2, LOW);
  digitalWrite(enable_MD2, LOW);
}

// For I2C communication
void sendData()
{
  Serial.println("----> SENDING");
  int array_len = sizeof(buffer) / sizeof(int);
  flag_activity = 0;
  for (char j = 0; j < array_len; j++)
  {
    Wire.write(buffer[j]);
    Serial.print("sending buffer: ");
    Serial.println(buffer[j]);
    //  if has "g" in word then is activated
    if (buffer[j] == 103 && counter % 2 == 0)
    {
      Serial.println("EURIKA!");
      // PRESSURE FUNCTION HERE!
      flag_activity = 1;
      // breath_signals(5);
    }
  }
  counter++;
}

// For I2C communication
void receiveData(int numBytes)
{
  Serial.print(numBytes);
  Serial.println(" bytes recieved");
  Serial.println(F("----> recieved events"));
  for (int i = 0; i < numBytes; i++)
  {
    data_to_echo = Wire.read();
    Serial.print("recieved value : ");
    Serial.println(data_to_echo);
    buffer[i] = data_to_echo;
  }
  Serial.println("BUFFER that is read");
  for (char m = 0; m < numBytes; m++)
  {
    Serial.print(buffer[m]);
    Serial.print(" ");
  }
  Serial.println();
}

// ---- Moving motors ----
void MD1_quarter_cycle_CW()
{
  digitalWrite(enable_MD1, LOW);
  digitalWrite(enable_MD2, LOW);

  digitalWrite(dir_MD1, HIGH); // clockwise
  digitalWrite(dir_MD2, LOW);  // counter clockwise

  for (int x = 0; x < (50 * 8); x++)
  {
    digitalWrite(step_MD1, HIGH);
    digitalWrite(step_MD2, HIGH);
    delayMicroseconds(1000); // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(step_MD1, LOW);
    digitalWrite(step_MD2, LOW);
    delayMicroseconds(1000);
  }
  delay(400);
}

void MD1_quarter_cycle_CCW()
{
  digitalWrite(enable_MD1, LOW);
  digitalWrite(enable_MD2, LOW);

  digitalWrite(dir_MD1, LOW);  // counter clockwise
  digitalWrite(dir_MD2, HIGH); // clockwise

  for (int x = 0; x < (50 * 8); x++)
  {
    digitalWrite(step_MD1, HIGH);
    digitalWrite(step_MD2, HIGH);
    delayMicroseconds(1000); // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(step_MD1, LOW);
    digitalWrite(step_MD2, LOW);
    delayMicroseconds(1000);
  }
  delay(400);
}

void MD1_half_cycle_CW()
{
  digitalWrite(enable_MD1, LOW);
  digitalWrite(enable_MD2, LOW);

  digitalWrite(dir_MD1, HIGH); // clockwise
  digitalWrite(dir_MD2, LOW);  // counter clockwise

  for (int x = 0; x < (100 * 8); x++)
  {
    digitalWrite(step_MD1, HIGH);
    digitalWrite(step_MD2, HIGH);
    delayMicroseconds(1000); // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(step_MD1, LOW);
    digitalWrite(step_MD2, LOW);
    delayMicroseconds(1000);
  }
  delay(400);
}

void MD1_half_cycle_CCW()
{
  digitalWrite(enable_MD1, LOW);
  digitalWrite(enable_MD2, LOW);

  digitalWrite(dir_MD1, LOW);  // counter clockwise
  digitalWrite(dir_MD2, HIGH); // clockwise

  for (int x = 0; x < (100 * 8); x++)
  {
    digitalWrite(step_MD1, HIGH);
    digitalWrite(step_MD2, HIGH);
    delayMicroseconds(1000); // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(step_MD1, LOW);
    digitalWrite(step_MD2, LOW);
    delayMicroseconds(1000);
  }
  delay(400);
}

void MD1_step_deg_cycle_CW()
{
  digitalWrite(enable_MD1, LOW);
  digitalWrite(enable_MD2, LOW);

  digitalWrite(dir_MD1, HIGH); // clockwise
  digitalWrite(dir_MD2, LOW);  // counter clockwise

  for (int x = 0; x < (10 * 8); x++)
  {
    digitalWrite(step_MD1, HIGH);
    digitalWrite(step_MD2, HIGH);
    delayMicroseconds(200); // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(step_MD1, LOW);
    digitalWrite(step_MD2, LOW);
    delayMicroseconds(200);
  }
  delay(400);
}

void MD2_quarter_cycle_CW()
{
  digitalWrite(enable_MD1, LOW);
  digitalWrite(enable_MD2, LOW);

  digitalWrite(dir_MD2, HIGH); // clockwise

  for (int x = 0; x < (50 * 8); x++)
  {
    digitalWrite(step_MD2, HIGH);
    delayMicroseconds(1000); // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(step_MD2, LOW);
    delayMicroseconds(1000);
  }
  delay(400);
}

void MD2_quarter_cycle_CCW()
{
  digitalWrite(enable_MD1, LOW);
  digitalWrite(enable_MD2, LOW);

  digitalWrite(dir_MD2, LOW); // counter clockwise

  for (int x = 0; x < (50 * 8); x++)
  {
    digitalWrite(step_MD2, HIGH);
    delayMicroseconds(1000); // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(step_MD2, LOW);
    delayMicroseconds(1000);
  }
  delay(400);
}

void MD2_half_cycle_CCW()
{
  digitalWrite(enable_MD1, LOW);
  digitalWrite(enable_MD2, LOW);

  digitalWrite(dir_MD2, LOW); // counter clockwise

  for (int x = 0; x < (100 * 8); x++)
  {
    digitalWrite(step_MD2, HIGH);
    delayMicroseconds(1000); // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(step_MD2, LOW);
    delayMicroseconds(1000);
  }
  delay(400);
}

void MD2_half_cycle_CW()
{
  digitalWrite(enable_MD1, LOW);
  digitalWrite(enable_MD2, LOW);

  digitalWrite(dir_MD2, HIGH); // clockwise

  for (int x = 0; x < (100 * 8); x++)
  {
    digitalWrite(step_MD2, HIGH);
    delayMicroseconds(1000); // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(step_MD2, LOW);
    delayMicroseconds(1000);
  }
  delay(400);
}

void MD2_step_deg_cycle_CW()
{
  digitalWrite(enable_MD1, LOW);
  digitalWrite(enable_MD2, LOW);

  digitalWrite(dir_MD2, HIGH); // clockwise

  for (int x = 0; x < (10 * 8); x++)
  {
    digitalWrite(step_MD2, HIGH);
    delayMicroseconds(200); // by changing this time delay between the steps we can change the rotation speed
    digitalWrite(step_MD2, LOW);
    delayMicroseconds(200);
  }
  delay(400);
}

// initializing all pins and functions
void setup()
{
  Wire.begin(I2C_SLAVE_ADDRESS);
  Serial.begin(9600);
  delay(200);

  // MotorDriver 1
  pinMode(step_MD1, OUTPUT);
  pinMode(dir_MD1, OUTPUT);
  pinMode(enable_MD1, OUTPUT);
  // MotorDriver 2
  pinMode(step_MD2, OUTPUT);
  pinMode(dir_MD2, OUTPUT);
  pinMode(enable_MD2, OUTPUT);
  reset_pins();

  Serial.println(F("----------I am Slave2----------"));
  delay(100);
  Wire.onRequest(sendData);
  Wire.onReceive(receiveData);
}

void test_cycle(int value)
{
  for (int i = 0; i < value; i++)
  {
    // rest position of device is in SUPINE
    // PRONE position
    MD1_half_cycle_CCW();
    delay(1000);
    // RIGHT LATERAL position
    MD1_quarter_cycle_CW();
    delay(200);
    MD2_quarter_cycle_CW();
    delay(1000);
    // LEFT LATERAL position
    MD2_half_cycle_CW();
    delay(1000);
    // resting position, SUPINE, motors sleeping
    MD2_quarter_cycle_CW();
    MD1_quarter_cycle_CW();
    digitalWrite(enable_MD1, HIGH);
    digitalWrite(enable_MD2, HIGH);
    // If want to increase time interval between cycle then change sleep input
    // 5*60 is 5 minutes
    sleep((4 * 60) + (1 * 45));
  }
}

void loop()
{
  //   --- MOTORS SLEEPING ---
  digitalWrite(enable_MD1, HIGH);
  digitalWrite(enable_MD2, HIGH);

  if (flag_activity == 1)
  {
    // The value in function below: test_cycle can be modified to change number of runs.
    // The function runs at every 5 mins interval
    // if for 1 hour recording choose the input value 12
    // if 8 hour recording choose the input value = 8*12 = 96
    test_cycle(96);
    flag_activity = 0;
  }
}