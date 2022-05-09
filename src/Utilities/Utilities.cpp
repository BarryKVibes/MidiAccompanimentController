/*******************************************************************************
  Utilities.cpp
  
  MIDI Accompaniment Controller
  https://github.com/BarryKVibes/MidiAccompanimentController
  Copyright 2022, Barry K Vibes
  
 *******************************************************************************
  
  This file is part of MidiAccompanimentController.
  
  MidiAccompanimentController is free software: you can redistribute it and/or 
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  MidiAccompanimentController is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License along 
  with MidiAccompanimentController. If not, see <https://www.gnu.org/licenses/>.
  
 ******************************************************************************/

#include <Arduino.h>

#include "Utilities.h"
#include "../SharedMacros.h"
#include "../SharedConstants.h"

void blinkOnce()
{
  digitalWrite(LedPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(LedPin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}

// Blink LED at Pin 13 at specified rate.
void blinkOnceAt(int rateMs)
{
  digitalWrite(LedPin, HIGH);
  delay(rateMs/2);
  digitalWrite(LedPin, LOW);
  delay(rateMs/2);
}

// Blink fast for the specified number of times.
void blinkFastNTimes(int numTimes)
{
    for (int i = 0; i < numTimes; i++)
    {
      blinkOnceAt(300);
    }
}

void fatalError()
{
  // Blink indefinitely with SOS code.
  while (true)
  {
    // 3 Fast
    for (int i = 0; i < 3; i++)
    {
      blinkOnceAt(300);
    }

    delay(500);
    
    // 3 Slow
    for (int i = 0; i < 3; i++)
    {
      blinkOnceAt(600);
    }
 
    delay(500);
  }
}

String GetButtonInfo(Button* buttons, int buttonIndex)
{
  String buttonInfo = String("Button[" + String(buttonIndex) + "] @ Pin " + String(buttons[buttonIndex].buttonState.pin) + " = " + String(buttons[buttonIndex].buttonState.active)); 

  return buttonInfo;
}

void PrintAllButtonInfo(Button* buttons, int numButtons)
{
  for (int buttonIndex = 0; buttonIndex < numButtons; buttonIndex++)
  {
    DBG_PRINT_LN("PrintAllButtonInfo() - " + GetButtonInfo(buttons, buttonIndex));
  }
}
