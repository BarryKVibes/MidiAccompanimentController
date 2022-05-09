/*******************************************************************************
  ButtonsManager.h
  
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

#ifndef ButtonsManager_H
#define ButtonsManager_H

#include "MidiAccompanimentController.h"

#include "Button.h"
#include "ButtonChangedHandlers/ButtonChangedHandlerBase.h"

class ButtonsManager {

private:
  Button* mFootPedalButtons;
  uint16_t mCurFootPedalButtonFlags = 0;

public:
  ButtonsManager(Button* footPedalButtons);

  void ReadButtons(Button* buttons, int startButtonIndex, int endButtonIndex, ButtonChangedHandlerBase& buttonChangedHandler);

protected:
  // The default constructor is protected to prevent its usage.
  ButtonsManager();

  // The following methods are only used by the RH Arduino.
  void UpdateNewButtonFlags(uint8_t receivedByte, int index);

private:
  bool IsButtonDebounced(const Button& button);

private:
  uint16_t mNewFootSwitchesButtonFlags = 0;
};

#endif
