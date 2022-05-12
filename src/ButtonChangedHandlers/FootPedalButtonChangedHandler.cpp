/*******************************************************************************
  FootPedalButtonChangedHandler.cpp
  
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

#include "../lib/ArduMidi/ardumidi.h"

#include "FootPedalButtonChangedHandler.h"

#include "../FootPedalSwitchChangeManager.h"
#include "../SharedMacros.h"
#include "../SharedConstants.h"

extern FootPedalSwitchChangeManager gFootPedalSwitchChangeManager; // TODO: Inject dependency.

// This class handles Right Hand Arduino Increment/Decrement Program button changes. 
// It sends corresponding MIDI Program Change message.
FootPedalButtonChangedHandler::FootPedalButtonChangedHandler()
{
}

void FootPedalButtonChangedHandler::HandleButtonChange(Button* buttons, byte buttonIndex)
{
  bool isActive = buttons[buttonIndex].buttonState.active;

  // DBG_PRINT_LN("FootPedalButtonChangedHandler::HandleButtonChange() - buttons["+String(buttonIndex)+"] @ Pin "+String(buttons[buttonIndex].buttonState.pin)+"= "+String(buttons[buttonIndex].buttonState.active)+".");
  gFootPedalSwitchChangeManager.HandleButtonChange(buttonIndex, isActive);
}