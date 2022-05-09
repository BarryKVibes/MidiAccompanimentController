/*******************************************************************************
  ButtonsManager.cpp
  
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

#include "MidiAccompanimentController.h"

#include "ButtonsManager.h"
#include "SharedMacros.h"
#include "SharedConstants.h"
#include "Utilities/Utilities.h"

extern Button gFootPedalButtons[NumFootPedalButtons];

// Used only by RH Arduino to keep track of both LH Arduino and RH Arduino buttons and sensors.
// It contains utilty functions to update LH buttons given corresponding button flags.
ButtonsManager::ButtonsManager(Button* footPedalButtons) :
  mFootPedalButtons(footPedalButtons)
{
}

// This method reads the digital input pin corresponding the the buttons passed in, after the debounce time has elapsed.
// It is used by both the RH and LH Arduinos.
void ButtonsManager::ReadButtons(Button* buttons, int startButtonIndex, int endButtonIndex, ButtonChangedHandlerBase& buttonChangedHandler)
{
  // DBG_PRINT_LN("ButtonsManager::ReadButtons() - Started.");
  bool newButtonState = false;
  for (byte i = startButtonIndex; i <= endButtonIndex; i++)
  {
     if (!IsButtonDebounced(buttons[i]))
    {
      continue;
    }

    // Button has been debounced; OK to read the corresponding pin value.
    //int inputVal = digitalRead(buttons[i].buttonState.pin);
    int inputVal = digitalRead(buttons[i].buttonState.pin);
    // DBG_PRINT_LN("ButtonsManager::ReadButtons() - ["+String(i)+"] @ Pin "+String(buttons[i].buttonState.pin)+"= "+String(inputVal)+".");

    // Note: Input pin is pulled high; therefore logic is inverted.
    newButtonState = inputVal == 0 ? true : false;

    if (buttons[i].buttonState.active == newButtonState) {

      // Button state did not change; check next button.
      // DBG_PRINT_LN("Button at pin " + String(i) + " is active");
      continue;
    }

    // Button state changed. Save its state.
    buttons[i].buttonState.active = newButtonState;
    buttons[i].lastToggleTimeMs = millis();

    // DBG_PRINT_LN("ButtonsManager::ReadButtons() - " + GetButtonInfo(buttons, i) + " State changed to = " + String(buttons[i].buttonState.active)+".");

    buttonChangedHandler.HandleButtonChange(buttons, i);
  }

}

// TODO: bjk 220111 Move debounce into button class, per https://roboticsbackend.com/arduino-object-oriented-programming-oop/
// Returns true if it is OK to handle button state toggle.
// This function returns true if the time between the current time and
// the last button state toggle time is greater than the debounce time.
bool ButtonsManager::IsButtonDebounced(const Button& button)
{
  unsigned long curTimeMs = millis();

  // Ignore current state until past the button settling time.
  unsigned long elapsedTimeMs = curTimeMs - button.lastToggleTimeMs;

  if (elapsedTimeMs < DebounceDelayMs) {
    // Last button toggle time is too recent. Prevent changing its state.
//    if (button.buttonState.active) {
//      DBG_PRINT_LN("Button " + String(button.buttonState.pin) + " elapsedTimeMs = " + String(elapsedTimeMs));
//    }

    return false;
  }
  else {
//    if (button.buttonState.active) {
//      DBG_PRINT_LN("Debounce Button " + String(button.buttonState.pin) + " completed." + " elapsedTimeMs = " + String(elapsedTimeMs));
//    }

    return true;
  }
}
