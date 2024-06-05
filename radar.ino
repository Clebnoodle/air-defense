#include <Servo.h>
#define SERVO_PIN 9
#define SERVO_DELAY 20
#define SERVO_LONG_DELAY 1000

#define SERVO2_PIN 8
#define SERVO2_DELAY 20
#define SERVO2_LONG_DELAY 1000

#define TRIG_PIN 11
#define ECHO_PIN 12

#define TRIG2_PIN 6
#define ECHO2_PIN 7

Servo myservo;
Servo myservo2;
int angle1 = 0;
int direction1 = 1;
int angle2 = 0;
int direction2 = 1;



void setup() {
  // put your setup code here, to run once:
  myservo.attach(SERVO_PIN);
  myservo2.attach(SERVO2_PIN);

  // Start the serial communication
  Serial.begin(9600);
  
  // Define the trigPin as an OUTPUT
  pinMode(TRIG_PIN, OUTPUT);
  
  // Define the echoPin as an INPUT
  pinMode(ECHO_PIN, INPUT);

  // Define the trigPin as an OUTPUT
  pinMode(TRIG2_PIN, OUTPUT);
  
  // Define the echoPin as an INPUT
  pinMode(ECHO2_PIN, INPUT);
}

long getDistance(int trigPin, int echoPin)
{
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, which returns the duration of the pulse in microseconds
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  // Speed of sound wave divided by 2 (there and back)
  // Sound speed in air (34300 cm/s)
  long distanceCm = duration * 0.034 / 2;

  return distanceCm;
}

void runServo(Servo servoIn, int & angle, int & direction, int angleChange)
{
    while (withinRange()) {}
    // put your main code here, to run repeatedly:
    servoIn.write(angle);
    angle += direction * angleChange;

    if (angle > 180)
    {
      direction = -1;
    }
    else if (angle < 0)
    {
      direction = 1;
    }
}

void goMax(Servo servoIn, int & angle, int & direction)
{
  while (angle < 180)
  {
    runServo(servoIn, angle, direction, 20);
  }

}

void goMin(Servo servoIn, int & angle, int & direction)
{
    while (angle > 0)
  {
    runServo(servoIn, angle, direction, 20);
  }
}

bool withinRange()
{
  return getDistance(TRIG_PIN, ECHO_PIN) < 20.0;
}

void loop() {

  long dis1 = getDistance(TRIG_PIN, ECHO_PIN);
  delay(100);
  // long dis2 = getDistance(TRIG2_PIN, ECHO2_PIN);

  // Print the distance to the Serial Monitor
  Serial.print("Distance 1: ");
  Serial.print(dis1);
  Serial.println(" cm");

  // Serial.print("Distance 2: ");
  // Serial.print(dis2);
  // Serial.println(" cm");
  
  

    
  runServo(myservo, angle1, direction1, 20);
  if (direction2 > 0)
  {
    goMax(myservo2, angle2, direction2);
    direction2 *= -1;
  }
  else
  {
    goMin(myservo2, angle2, direction2);
    direction2 *= -1;
  }

  
  delay(SERVO_DELAY);

}
