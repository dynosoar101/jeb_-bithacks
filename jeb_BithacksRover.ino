/*program uses two L293D motor drivers to program 4 motors. 2 motors correspond to each driver, with one controller rear and one front wheels*/

//variable declarations
const int baudRate = 9600; // 115200 baud rate for esp

//refer to L293d pinout for pin number naming
//motor 1 input pin declarations
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
// const int motor1Pin3;
// const int motor1Pin4;
// //motor 2 input pin declarations
// const int motor2Pin1;
// const int motor2Pin2;
// const int motor2Pin3;
// const int motor2Pin4;

void setup() {
  Serial.begin(9600);

  //set all motor pins to output
  pinMode(motor1Pin1,OUTPUT);
  pinMode(motor1Pin2,OUTPUT);
  // pinMode(motor1Pin3,OUTPUT);
  // pinMode(motor1Pin4,OUTPUT);
  // pinMode(motor2Pin1,OUTPUT);
  // pinMode(motor2Pin2,OUTPUT);
  // pinMode(motor2Pin3,OUTPUT);
  // pinMode(motor2Pin4,OUTPUT);



}

void loop() {
  //Serial.println("more balls");
  digitalWrite(motor1Pin1,HIGH);
  digitalWrite(motor1Pin2,LOW);
}