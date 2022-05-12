/*******************************************************************************
  FootPedalSwitchChangeManager.cpp
  
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

#include "lib/ArduMidi/ardumidi.h"

#include "MidiAccompanimentController.h"
#include "MIDIEventFlasher.h"
#include "FootPedalSwitchChangeManager.h"
#include "SharedMacros.h"
#include "SharedConstants.h"
#include "StatusManager.h"
#include "Utilities/Utilities.h"

const uint8_t MaxProgramNumber = 0x7F;

extern StatusManager gStatusManager;

FootPedalSwitchChangeManager::FootPedalSwitchChangeManager()
{
}

void FootPedalSwitchChangeManager::HandleButtonChange(int buttonIndex, bool isActive)
{
  if (buttonIndex >=0 && buttonIndex <= 4)
  {
    HandleStyleButtonChange(buttonIndex, isActive);
  }
  else if(buttonIndex >=5 && buttonIndex <= 13)
  {
    HandleRegistrationButtonChange(buttonIndex, isActive);
  }
}


void FootPedalSwitchChangeManager::HandleStyleButtonChange(int buttonIndex, bool isActive)
{
  // TODO: Precondition buttonIndex within pedal range (e.g., 0..4).

  // Send Yamaha SX-700/900 SysEx based on which switch is pressed.
  #ifdef SEND_MIDI
    // Send SysEx
    //  F0 43 7E 00 ss dd F7
    // ss = Switch Number
    // 00H INTRO 1
    // 01H INTRO 2
    // 02H INTRO 3
    // 03H INTRO 4
    // 08H MAIN A
    // 09H MAIN B
    // 0AH MAIN C
    // 0BH MAIN D
    // 10H FILL IN AA
    // 11H FILL IN BB
    // 12H FILL IN CC
    // 13H FILL IN DD
    // 18H BREAK FILL
    // 20H ENDING 1
    // 21H ENDING 2
    // 22H ENDING 3
    // 23H ENDING 4

    // 0ddddddd dd = Switch On/Off
    // 00H (Off)
    // 7FH (On)

    // F7 = End of Exclusive

    Serial.write(0xF0); // Exclusive status
    Serial.write(0x43); // YAMAHA ID
    Serial.write(0x7E); // Style
    Serial.write(0x00);

    // Index -> Switch
    // 0 -> Intro/Ending
    // 1 -> Style Variation
    // 2 -> Fill In 1
    // 3 -> Fill in 2
    // 4 -> Start/Stop TBD: May be different SysEx; using 0x20 for now.
    const unsigned char switchNum[NumFootPedalButtons] = {0x00, 0x08, 0x10, 0x11, 0x20};
    const unsigned char SwitchOn = 0x7F; // TBD: What is Switch On/Off?
    const unsigned char SwitchOff = 0x00; // TBD: What is Switch On/Off?
    unsigned char switchOnOffByte =  isActive ? SwitchOn : SwitchOff;
    Serial.write(switchNum[buttonIndex]); // Switch No.
    Serial.write(switchOnOffByte); // Switch On/Off.
    Serial.write(0xF7); // End of Exclusive
  #else
    DBG_PRINT_LN("FootPedalSwitchChangeManager::HandleStyleButtonChange() - buttonIndex = " + String(buttonIndex) + "; isActive = " + String(isActive) + ".");
  #endif
}

void FootPedalSwitchChangeManager::HandleRegistrationButtonChange(int buttonIndex, bool isActive)
{
  #ifdef SEND_MIDI
  // TBD
  #else
    DBG_PRINT_LN("FootPedalSwitchChangeManager::HandleRegistrationButtonChange() - buttonIndex = "  + String(buttonIndex) + "; isActive = " + String(isActive) + ".");
  #endif
}
