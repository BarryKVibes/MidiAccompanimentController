/*******************************************************************************
  FootPedalSwitchChangeManager.h
  
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

#ifndef FootPedalSwitchChangeManager_H
#define FootPedalSwitchChangeManager_H

class FootPedalSwitchChangeManager  {

private:

// The SwitchNum enum contains valid values for the Yamaha SX-700/900  Style button SysEx ss = Switch Number byte.
// F0 43 7E 00 ss dd F7
// 
enum StyleSwitchNum
{
    Intro1 = 0x00,
    Intro2 = 0x01,
    Intro3 = 0x02,
    Intro4 = 0x03,
    MainA = 0x08,
    MainB = 0x09,
    MainC = 0x0A,
    MainD = 0x0B,
    FillInAA = 0x10,
    FillInBB = 0x11,
    FillInCC = 0x12,
    FillInDD = 0x13,
    BreakFill = 0x18,
    Ending1 = 0x20,
    Ending2 = 0x21,
    Ending3 = 0x22,
    Ending4 = 0x23
};

public:

  // This method is the default constructor.
  FootPedalSwitchChangeManager();
  void HandleButtonChange(int buttonIndex, bool isActive);

private:
  void HandleFivePedalBoardSwitchChange(int buttonIndex, bool isActive);
  void HandleEightPedalBoardSwitchChange(int buttonIndex, bool isActive);

  void SendStyleButtonSysEx(StyleSwitchNum styleSwitchNum, bool isSwitchOn);
};

#endif
