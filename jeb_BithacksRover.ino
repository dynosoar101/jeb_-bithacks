/*program uses two L293D motor drivers to program 4 motors. 2 motors correspond to each driver, with one controller rear and one front wheels

Pin1 and Pin2 correspond to the left side of the motor driver, Pin3 and Pin4 -> right
*/

//function definitions
void clearMoves();
void moveForward();
void turnLeft(int turnAmount);
void turnRight(int turnAmount);


//variable declarations

//refer to L293d pinout for pin number naming
//motor 1 input pin declarations - motor 1 is rear wheels
const int motor1Pin1 = 2; //drives top left ouput pin - should be red motor wire
const int motor1Pin2 = 3; //drives bottom left output pin - should be blk motor wire
const int motor1Pin3 = 4; //drives bottom right output pin - should be blK motor wire
const int motor1Pin4 = 5; //drives top right output pin should be red motor wire
// //motor 2 input pin declarations - motor 2 is front wheels
const int motor2Pin1 = 7;
const int motor2Pin2 = 8;
const int motor2Pin3 = 9;
const int motor2Pin4 = 10;

void setup() {
  Serial.begin(9600);

  //set all motor pins to output
  //motor 1
  pinMode(motor1Pin1,OUTPUT);
  pinMode(motor1Pin2,OUTPUT);
  pinMode(motor1Pin3,OUTPUT);
  pinMode(motor1Pin4,OUTPUT);
  //motor 2
  pinMode(motor2Pin1,OUTPUT);
  pinMode(motor2Pin2,OUTPUT);
  pinMode(motor2Pin3,OUTPUT);
  pinMode(motor2Pin4,OUTPUT);



}

void loop() {
  //Serial.println("more balls");
  moveForward();
}


/*subroutine definitions for moving forward, left, and right*/
//clears all movement
void clearMoves(){
  //motor 1 clears
  digitalWrite(motor1Pin1,LOW);
  digitalWrite(motor1Pin2,LOW);
  digitalWrite(motor1Pin3,LOW);
  digitalWrite(motor1Pin4,LOW);
  //motor 2 clears
  digitalWrite(motor2Pin1,LOW);
  digitalWrite(motor2Pin2,LOW);
  digitalWrite(motor2Pin3,LOW);
  digitalWrite(motor2Pin4,LOW);
}

//forward
void moveForward(){
  //moves motor 1
  digitalWrite(motor1Pin1,HIGH);
  digitalWrite(motor1Pin2,LOW);
  digitalWrite(motor1Pin4,HIGH);
  digitalWrite(motor1Pin3,LOW);

  //moves motor2
  digitalWrite(motor2Pin1,HIGH);
  digitalWrite(motor2Pin2,LOW);
  digitalWrite(motor2Pin4,HIGH);
  digitalWrite(motor2Pin3,LOW);
}
//turns left by making rear right wheel move and left wheel stop 
//turnAmount argument specifies how much left to go by
void turnLeft(int turnAmount){
  clearMoves();
  digitalWrite(motor1Pin1, HIGH);
  delay(turnAmount);
  clearMoves();
}

//turns left by making rear left wheel move and right wheel stop 
//turnAmount argument specifies how much left to go by
void turnRight(int turnAmount){
  clearMoves();
  digitalWrite(motor1Pin1, HIGH);
  delay(turnAmount);
  clearMoves();
}