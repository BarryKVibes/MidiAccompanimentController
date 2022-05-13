/*******************************************************************************
  FootPedalSetupManager.cpp
  
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

#include "FootPedalSetupManager.h"
#include "../Utilities/Utilities.h"
#include "../SharedMacros.h"

// Global Variables
extern Button gFootPedalButtons[NumFootPedalButtons];

FootPedalSetupManager::FootPedalSetupManager() : SetupManagerBase()
{
}

// Initializes serial port for either sending MIDI or writing to the Serial Monitor.
void FootPedalSetupManager::Setup()
{
  // Setup LED pin early to allow it to enable flashing error code.
  pinMode(LedPin, OUTPUT);

#ifdef SEND_MIDI
  Serial.begin(BaudRateMidi);
#else
  // Write to Serial Monitor.
  Serial.begin(BaudRateSerialMonitor);
#endif

  int numButtons = GetNumButtons();
  for (char i = 0; i < numButtons; i++)
  {
    int pinNum = GetButtonAt(i).buttonState.pin;

    DBG_PRINT_LN("FootPedalSetupManager::Setup() - buttonIndex = "  + String((int)i) + "; pin = " + String(pinNum) + ".");
    pinMode(pinNum, INPUT_PULLUP);
  }

  // Indicated that RH Arduino is ready.
  blinkOnce();

  // if(!gIsSendMidi) { DbgPrintLn("RightHandSetup::Setup() - Setup done."); }
}

int FootPedalSetupManager::GetNumButtons()
{
  return COUNT_ENTRIES(gFootPedalButtons);
}

Button& FootPedalSetupManager::GetButtonAt(int index)
{
  return gFootPedalButtons[index];
}
