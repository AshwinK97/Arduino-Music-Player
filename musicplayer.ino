#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

// pin for sd card
#define SD_ChipSelectPin 4
TMRpcm music;

int song_number = 0;
boolean debounce1 = true;
boolean debounce2 = true;
boolean play_pause;

void setup() {
  // set pin for audio output
  music.speakerPin = 9;
  Serial.begin(9600); // allow serial output

  // set pin for sd card
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  } else {
    Serial.println("SD success");
  }

  // set pins for button input
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  
  // set player configuration
  music.setVolume(5);
  music.quality(1);
  //music.volume(0);
}

void loop() {
  
  // read for when next button is pressed
  if (digitalRead(2) == LOW  && debounce1 == true) {
    Serial.println("NEXT");
    song_number++; // incremement song
    if (song_number == 3) // loop back if last song is reached
      song_number = 1;
    debounce1 = false; // set debounce false so button cannot be registered again
    
    // play song based on song number
    if (song_number == 1)
      music.play("1.wav", 1);
    if (song_number == 2)
      music.play("2.wav", 1);
    
    // read for when pause button is pressed
    if (digitalRead(3) == LOW  && debounce2 == true) {
      Serial.println("PLAY / PAUSE");
      music.pause();
      debounce2 = false; // set debounce false so button cannot be registered again
    }
    
    // if switches are released, set debounce to true to allow for button press
    if (digitalRead(2) == HIGH)
      debounce1 = true;
    if (digitalRead(3) == HIGH)
      debounce2 = true;
  }
}
