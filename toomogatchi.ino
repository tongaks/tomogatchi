#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "images.h"

#define OLED_RESET 4
int feed_button = 2;
int pet_button = 3;
bool isHungry = false;
int weight = 50;
int hunger_bar = 2;
int interval = 4000; //every 1 sec
int previous = 0;
int state = 0;
bool isBlink = false;

Adafruit_SSD1306 display(OLED_RESET);

// void Idle() {
//   unsigned long currentmilli = millis();

//   display.clearDisplay();
//   display.drawBitmap(0, 0, idle1, 132, 32, WHITE);
//   display.display();

//   if (currentmilli - previous >= interval) {
//     previous = currentmilli;
//     display.clearDisplay();
//     display.drawBitmap(0, 0, idle2, 132, 32, WHITE);
//     display.display();
//   }
// }

// void Idle() {
//   display.clearDisplay();
//   display.drawBitmap(0, 0, idle1, 132, 32, WHITE);
//   display.display();
//   delay(1000);
//   display.clearDisplay();
//   display.drawBitmap(0, 0, idle2, 132, 32, WHITE);
//   display.display();
//   delay(1000);
// }

void ScratchScreen(){}

void WalkAround() {
  display.clearDisplay();
  display.drawBitmap(0, 0, walk1, 132, 32, WHITE);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.drawBitmap(0, 0, walk2, 132, 32, WHITE);
  display.display();
  delay(1000);  
  display.clearDisplay();
  display.drawBitmap(0, 0, walk3, 132, 32, WHITE);
  display.display();
  delay(1000);
}

// void Idle() {
//   display.clearDisplay();
//   display.drawBitmap(0, 0, idle1, 132, 32, WHITE);
//   display.display();
//   delay(2000);
//   display.clearDisplay();
//   display.drawBitmap(0, 0, idle2, 132, 32, WHITE);
//   display.display();
//   delay(800);
// }

void Hungry() {
  if (hunger_bar < 2) {
    weight + 20;    
    isHungry = true;
    display.clearDisplay();
    display.drawBitmap(0, 0, hungry1, 132, 32, WHITE);
    display.display();
    delay(1300);
  } else {
    isHungry = false;
  }
}

void Idle() {
  unsigned long currentmilli = millis();
  switch (hunger_bar) {
    case 3:
      isHungry = false;
      display.clearDisplay();
      display.drawBitmap(0, 0, idle_3bar, 132, 32, WHITE);
      display.display();
      if (isBlink == true && currentmilli - previous >= interval){
        display.clearDisplay();
        display.drawBitmap(0, 0, idle2_3bar, 132, 32, WHITE);
        display.display();
        isBlink = false;
        previous = currentmilli;
      }
      break;
    case 2:
      display.clearDisplay();
      display.drawBitmap(0, 0, idle_2bar, 132, 32, WHITE);
      display.display();
      if (isBlink == true && currentmilli - previous >= interval){
        display.clearDisplay();
        display.drawBitmap(0, 0, idle2_2bar, 132, 32, WHITE);
        display.display();
        isBlink = false;
        previous = currentmilli;
      }
      break;
    case 1:
      display.clearDisplay();
      display.drawBitmap(0, 0, idle_1bar, 132, 32, WHITE);
      display.display();
      if (isBlink == true && currentmilli - previous >= interval){
        display.clearDisplay();
        display.drawBitmap(0, 0, idle2_1bar, 132, 32, WHITE);
        display.display();
        isBlink = false;
        previous = currentmilli;
      }
      break;
    default:
      display.clearDisplay();
      display.drawBitmap(0, 0, idle_empty, 132, 32, WHITE);
      display.display();
      if (isBlink == true && currentmilli - previous >= interval){
        display.clearDisplay();
        display.drawBitmap(0, 0, idle2_3bar, 132, 32, WHITE);
        display.display();
        isBlink = false;
        previous = currentmilli;
      }
      break;
  }
}

// void Idle() {
//   unsigned long currentmilli = millis();
//   switch (hunger_bar) {
//     case 3:
//       isHungry = false;
//       display.clearDisplay();
//       display.drawBitmap(0, 0, idle_3bar, 132, 32, WHITE);
//       display.display();
//       delay(2000);
//       display.clearDisplay();
//       display.drawBitmap(0, 0, idle2_3bar, 132, 32, WHITE);
//       display.display();
//       break;
//     case 2:
//       display.clearDisplay();
//       display.drawBitmap(0, 0, idle_2bar, 132, 32, WHITE);
//       display.display();
//       delay(2000);
//       display.clearDisplay();
//       display.drawBitmap(0, 0, idle2_2bar, 132, 32, WHITE);
//       display.display();
//       break;
//     case 1:
//       display.clearDisplay();
//       display.drawBitmap(0, 0, idle_1bar, 132, 32, WHITE);
//       display.display();
//       delay(2000);
//       display.clearDisplay();
//       display.drawBitmap(0, 0, idle2_1bar, 132, 32, WHITE);
//       display.display();
//       break;
//     default:
//       display.clearDisplay();
//       display.drawBitmap(0, 0, idle_empty, 132, 32, WHITE);
//       display.display();
//       delay(2000);
//       display.clearDisplay();
//       display.drawBitmap(0, 0, idle2_empty, 132, 32, WHITE);
//       display.display();
//       break;
//   }
// }

void Feed() {
  int feed_button_state = digitalRead(feed_button);
  if (feed_button_state == LOW) {
    hunger_bar ++;
    Serial.println(hunger_bar);
  } else if (hunger_bar > 3) {
    hunger_bar = 3;
  }

}

void Tomodatchi() {
  int hunger_chance = random(1, 8);
  int choice = random(1, weight);
  if (choice == 1) {
    isHungry = true;
    hunger_bar - 1;
  } else if (choice == 3) {
    isBlink = true;    
  }
  
  if (isHungry && choice == 1) {
    Hungry();
    if (hunger_chance == 1) {
      hunger_bar -= 1;
      isHungry = true;
    }
  } else if (choice == 2) {
    WalkAround();
  } else {
    Idle();
    Feed();    
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(feed_button, INPUT_PULLUP);
  pinMode(pet_button, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);

}

void loop() {
    Tomodatchi();
}
