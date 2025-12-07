const int trigPin = 18;
const int echoPin = 19;
const int LED=25;
long duration;
int distance;
int level;
int percent;
const int TANK_HEIGHT = 72;  // cm
const int MIN_LEVEL = 2; 
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(LED,OUTPUT);
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  if(distance>0){
    distance=distance;
  }
  level=72-distance;
  percent = ((level - MIN_LEVEL) * 100) / (TANK_HEIGHT - MIN_LEVEL);
 
  Serial.print("Water level:");
  Serial.println(level);
  delay(500);
 

  Serial.print("Percentage of water:");
  Serial.println(percent);
  delay(500);


  if (percent>=100){
    Serial.println("Tank Full");
    delay(500);
  }
  if(percent<=30){
    digitalWrite(LED,HIGH);

  }
  else{
    digitalWrite(LED,LOW);
  }

  }



