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

// This file supports two pedal boards; one with 5 switches, and one with 8 switches (two rows of four pedals).
// The Arduino pins are specified in main.cpp.

#include "lib/ArduMidi/ardumidi.h"

#include "MidiAccompanimentController.h"
#include "MIDIEventFlasher.h"
#include "FootPedalSwitchChangeManager.h"
#include "SharedMacros.h"
#include "SharedConstants.h"
#include "StatusManager.h"
#include "Utilities/Utilities.h"

extern StatusManager gStatusManager;

FootPedalSwitchChangeManager::FootPedalSwitchChangeManager()
{
}

void FootPedalSwitchChangeManager::HandleButtonChange(int buttonIndex, bool isActive)
{
  if (buttonIndex >=0 && buttonIndex <= 4)
  {
    HandleFivePedalBoardSwitchChange(buttonIndex, isActive);
  }
  else if(buttonIndex >=5 && buttonIndex <= 13)
  {
    HandleEightPedalBoardSwitchChange(buttonIndex, isActive);
  }
}

// This method handles the 5-pedal board. The first four pedals select the current style's variation, and the 5th pedal sends Ending 1.
void FootPedalSwitchChangeManager::HandleFivePedalBoardSwitchChange(int buttonIndex, bool isActive)
{
  // TODO: Precondition buttonIndex within pedal range (e.g., 0..4).

  #ifdef SEND_MIDI
    // Index -> Switch
    const StyleSectionControlSwitchNum switchNum[NumFootPedalButtons] = {StyleSectionControlSwitchNum::MainA, StyleSectionControlSwitchNum::MainB, StyleSectionControlSwitchNum::MainC, StyleSectionControlSwitchNum::MainD, StyleSectionControlSwitchNum::Ending1};

    SendStyleSectionControlSysEx(switchNum[buttonIndex], isActive);
  #else
    DBG_PRINT_LN("FootPedalSwitchChangeManager::HandleFivePedalBoardSwitchChange() - buttonIndex = " + String(buttonIndex) + "; isActive = " + String(isActive) + ".");
  #endif
}

void FootPedalSwitchChangeManager::SendStyleSectionControlSysEx(StyleSectionControlSwitchNum switchNum, bool isSwitchOn)
{
  // Send Yamaha SX-700/900 Section Control SysEx based on which switch is pressed.
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

    const unsigned char SwitchOn = 0x7F; // Indicates front-panel switch is pressed.
    const unsigned char SwitchOff = 0x00; // Indicates front-panel switch is released.
    unsigned char switchOnOffByte =  isSwitchOn ? SwitchOn : SwitchOff;
    Serial.write(switchNum); // Switch No.
    Serial.write(switchOnOffByte); // Switch On/Off.
    Serial.write(0xF7); // End of Exclusive
}

// The 8-pedal board has two rows of four pedals. The left 6 pedals choose 6 different styles. The two right pedals increment, decrement the tempos.
void FootPedalSwitchChangeManager::HandleEightPedalBoardSwitchChange(int buttonIndex, bool isActive)
{
  // Send style change only if changed to active.
  if (!isActive)
  {
    return;
  }

  // Precondition buttonIndex within pedal range (e.g., 5..12).
  if (buttonIndex < 5 || buttonIndex > 12)
  {
    return;
  }

  // Button Index Layout.
  // 05 06 07 08
  // 09 10 12 11 

  int pedalIndex = buttonIndex - 5;
  // Pedal Index Layout - Zero-based.
  // 00 01 02 03
  // 04 05 06 07

  // TODO: Implement tempo change on pedal index 3 and 7.
  if (pedalIndex == 3)
  {    
    SendStyleNumSysEx(pedalIndex); // PLACEHOLDER TODO: Increment tempo
    return;
  }
  else if (pedalIndex == 7)
  {    
    SendStyleNumSysEx(pedalIndex); // PLACEHOLDER TODO: Decrement tempo
    return;
  }

  // Set style based on pedal index.
  uint16_t styleNum[] = { StyleNum::BigBandSwing, StyleNum::CoolBossa, StyleNum::VocalWaltz, StyleNum::Default,
                          StyleNum::BigBandBallad, StyleNum::AcousticJazz, StyleNum::BigBandJazz, StyleNum::Default };

  SendStyleNumSysEx(styleNum[pedalIndex]);

  #ifdef SEND_MIDI
  #else
    DBG_PRINT_LN("FootPedalSwitchChangeManager::HandleRegistrationButtonChange() - buttonIndex = "  + String(buttonIndex) + "; isActive = " + String(isActive) + ".");
  #endif
}

void FootPedalSwitchChangeManager::SendStyleNumSysEx(uint16_t styleNum)
{
  // F0 43 73 01 51 05 00 03 04 00 00 dd dd F7
  // where dd dd is the MSB/LSB of the style number.
  uint8_t styleNumMsb = (uint8_t)((styleNum & 0xFF00) >> 8);
  uint8_t styleNumLsb = (uint8_t)(styleNum & 0x00FF);
  uint8_t sysExBytes[] = {0xF0, 0x43, 0x73, 0x01, 0x51, 0x05, 0x00, 0x03, 0x04, 0x00, 0x00, 0xdd, 0xdd, 0xF7};

  sysExBytes[11] = styleNumMsb;
  sysExBytes[12] = styleNumLsb;

  #ifdef SEND_MIDI

  for (unsigned int i = 0; i < sizeof(sysExBytes); i++)
  {
    Serial.write(sysExBytes[i]);
  }

  #else
    DBG_PRINT_LN("FootPedalSwitchChangeManager::SetStyle() - MSB = 0x" + String(sysExBytes[11], HEX) + "; LSB = 0x" + String(sysExBytes[12], HEX) + ".");
  #endif
}
