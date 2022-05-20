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
: mCurTempo(0)
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
  // Precondition buttonIndex within pedal range (e.g., 0..4).
  if (buttonIndex < 0 || buttonIndex > 4)
  {
    return;
  }

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
  // mCurTempo = 0;
  if (pedalIndex == 3)
  {
    if (mCurTempo == 0)
    {
      mCurTempo = DefaultTempo;
    }
    else
    {
      if (mCurTempo < MaxTempo)
      {
        mCurTempo++;
      }
    }

    SendTempoSysEx(mCurTempo);

    return;
  }
  else if (pedalIndex == 7)
  {    
    if (mCurTempo == 0)
    {
      mCurTempo = DefaultTempo;
    }
    else
    {
      if (mCurTempo > MinTempo)
      {
        mCurTempo--;
      }
    }
    
    SendTempoSysEx(mCurTempo);

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

// Sends the encoded four bytes for the Yamaha tempo change SysEx message.
// Based on https://www.psrtutorial.com/forum/index.php?topic=48303.0
void FootPedalSwitchChangeManager::SendTempoSysEx(uint16_t tempo)
{
  // F0 43 7E 01 t4 t3 t2 t1 F7
  // 11110000 F0 = Exclusive status 
  // 01000011 43 = YAMAHA ID 
  // 01111110 7E = Style
  // 00000001 01 = 
  // 0ttttttt t4 = tempo4
  // 0ttttttt t3 = tempo3
  // 0ttttttt t2 = tempo2
  // 0ttttttt t1 = tempo1
  // 11110111 F7 = End of Exclusive

  uint16_t t1, t2, t3, t4;
  uint32_t totalTempo;
  totalTempo = (uint32_t)(60000000 / tempo);
  // FootPedalSwitchChangeManager::SendTempoSysEx(120) - t4 = 0x0 t3 = 0x1e t2 = 0x42 t1 = 0x20.
  // FootPedalSwitchChangeManager::SendTempoSysEx(119) - t4 = 0x0 t3 = 0x1e t2 = 0x63 t1 = 0x9.
  // FootPedalSwitchChangeManager::SendTempoSysEx(121) - t4 = 0x0 t3 = 0x1e t2 = 0x21 t1 = 0x7b.

  // t4 = (uint32_t)(totalTempo / 0x00200000) & 0x7F; // 21 bit shift
  // t3 = (uint32_t)(totalTempo / 0x00004000) & 0x7F; // 14 bit shift
  // t2 = (uint32_t)(totalTempo / 0x00000080) & 0x7F; // 7 bit shift
  t4 = (uint32_t)(totalTempo >> 21) & 0x7F; // 21 bit shift
  t3 = (uint32_t)(totalTempo >> 14) & 0x7F; // 14 bit shift
  t2 = (uint32_t)(totalTempo >> 7) & 0x7F; // 7 bit shift
  t1 = totalTempo & 0x7F;
  //---------- tempo sysEx
  //return [hex(0xF0), hex(0x43), hex(0x7E), hex(0x1), hex(t4), hex(t3), hex(t2), hex(t1), hex(0xF7)].join(" ");

#ifdef SEND_MIDI
  Serial.write(0xF0); // Exclusive status
  Serial.write(0x43); // YAMAHA ID
  Serial.write(0x7E); // Style
  Serial.write(0x01);
  Serial.write(t4);
  Serial.write(t3);
  Serial.write(t2);
  Serial.write(t1);
  Serial.write(0xF7);
#else
  DBG_PRINT("FootPedalSwitchChangeManager::SendTempoSysEx(" + String(tempo) + " = 0x" + String(tempo, HEX) + ") - totalTempo = " + String(totalTempo));
  DBG_PRINT(" = B" + PrependZeros(String(totalTempo, BIN), 32));
  DBG_PRINT_LN(" - t4 = B"  + PrependZeros(String(t4, BIN), 7) 
  + " t3 = B"  + PrependZeros(String(t3, BIN), 7) 
  + " t2 = B"  + PrependZeros(String(t2, BIN), 7) 
  + " t1 = B"  + PrependZeros(String(t1, BIN), 7) 
  + ".");
#endif
}

// Prepend string with zeros up to numCharsWide long.
String FootPedalSwitchChangeManager::PrependZeros(String originalString, uint8_t numCharsWide)
{
  String paddedString, temp;
  paddedString = "";
  unsigned int originalStringLen = originalString.length();
  if (originalStringLen > numCharsWide)
  {
    return String(originalString);
  }

  // Make string of 0s to prepend.
  unsigned int numZerosNeeded = numCharsWide - originalStringLen;
  String stringOfZeros;

  for (unsigned int i = 0; i < numZerosNeeded; i++)
  {
    stringOfZeros = '0' + stringOfZeros;
  }

  paddedString = stringOfZeros + String(originalString);
  
  //DBG_PRINT_LN("FootPedalSwitchChangeManager::PrependZeros() paddedString = " + paddedString + ".");

  return paddedString;
}