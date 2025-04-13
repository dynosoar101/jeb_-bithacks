/*this program will use a DFMiniPlayer to incorporate sheep noises into our finished product. these noises will play using internal logic. the noises are ambient sheep noises and will be played  using a random timer. A grass eating noise will be played when the sheep comes into contact with the wheat*/

//library inclusions
#include <SoftwareSerial.h> //allows the use of GPIO pins for tx rx communication
#include <DFRobotDFPlayerMini.h> //library for miniplayer
#include <AlmostRandom.h>

// Define the communication pins for the DFPlayer Mini
/*uses digital pins 2 and 3 on the arduino. tx on arduino corresponds to rx
on mini player and vice versa. refer to pinout of DFMiniPlayer for wiring
*/
static const uint8_t TXPin = 2;
static const uint8_t RXPin = 3;

// Create a SoftwareSerial object for communication
SoftwareSerial softwareSerial(RXPin, TXPin);
// Create a DFRobotDFPlayerMini object
DFRobotDFPlayerMini MP3player;
// create an actual random object
AlmostRandom randomLib;

void setup() {
  // Initialize the serial monitor for debugging
  Serial.begin(9600);
  // Initialize the SoftwareSerial for communication
  softwareSerial.begin(9600);

  // Begin communication with the DFPlayer Mini
  if (MP3player.begin(softwareSerial)) {
    Serial.println("DFPlayer Mini ready");
  } else {
    Serial.println("DFPlayer Mini NOT READY");
  }
  
  // Set the volume (0-30)
  MP3player.volume(30);
  // int value = 3;
  // MP3player.play(value);
  // delay(2000);
  // value = 2;
  // MP3player.play(value);
}


void loop(){
  //random chance variable to determine if a noise should be played
  unsigned int randomChance = randomLib.getRandomInt();
  //randomChance%5;
  delay(3000);
  //the ultimate way to make it random
  if(randomChance%2 == 0){
    Serial.println("this is happening");
    playNoiseAmbient();
    //MP3player.play(2);
  }

}

/*sheep noises*/
//plays ambient noises, sheep BAAAAA's
void playNoiseAmbient(){
 int randomSoundFile = random(1,4);
 Serial.println(randomSoundFile);
 MP3player.play(randomSoundFile);
 //value = 1;
  // if(MP3player.readCurrentFileNumber() == -1){
  //   MP3player.play(randomSoundFile);
  // }

  
}
