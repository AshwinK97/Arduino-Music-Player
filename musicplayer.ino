#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

#define SD_ChipSelectPin 4
TMRpcm music;

int song_number = 0;
boolean debounce1 = true;
boolean debounce2 = true;
boolean play_pause;

void setup() {
  music.speakerPin = 9;
  Serial.begin(9600);

  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  } else {
    Serial.println("SD success");
  }

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  
  music.setVolume(5);
  music.quality(1);
  //music.volume(0);
}

void loop() {
  if (digitalRead(2) == LOW  && debounce1 == true) {
    Serial.println("NEXT");
    song_number++;
    if (song_number == 3)
      song_number = 1;
    debounce1 = false;
    
    if (song_number == 1)
      music.play("1.wav", 1);
    if (song_number == 2)
      music.play("2.wav", 1);
    
    if (digitalRead(3) == LOW  && debounce2 == true) {
      Serial.println("PLAY / PAUSE");
      music.pause();
      debounce2 = false;
    }
    
    if (digitalRead(2) == HIGH)
      debounce1 = true;
    if (digitalRead(3) == HIGH)
      debounce2 = true;
  }
}
