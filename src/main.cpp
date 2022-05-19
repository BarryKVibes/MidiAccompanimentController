/*******************************************************************************
  MidiAccompanimentController.ino
  
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

// This file is the main Arduino file which includes the setup() and loop() functions.
// It also includes objects used by other files, including Button and Sensor definitions.

#include <Arduino.h>

#include "MidiAccompanimentController.h" // MidiAccompanimentController.h contains compiler directives.

#include "SetupManagers/FootPedalSetupManager.h"
#include "ButtonChangedHandlers/FootPedalButtonChangedHandler.h"

#include "FootPedalSwitchChangeManager.h"
#include "MIDIEventFlasher.h"
#include "StatusManager.h"


#include "ButtonsManager.h"
#include "Utilities/Utilities.h"
#include "SharedConstants.h"
#include "SharedMacros.h"

#ifndef SEND_MIDI
  #include "Utilities/Diagnostics.h"
#endif

// Foot Switches Button configuration.
Button gFootPedalButtons[NumFootPedalButtons] = {
  // Button {ButtonState buttonState, unsigned long lastToggleTimeMs} where
  // ButtonState {active, pin, unused0, unused1, unused2}

  // The Five-Pedal Board Buttons (Indexes 0..4)
  {{false, 2, 0, 0, 0}, 0}, {{false, 3, 0, 0, 0}, 0}, {{false, 4, 0, 0, 0}, 0}, {{false, 5, 0, 0, 0}, 0},
  {{false, 6, 0, 0, 0}, 0},

  // The Eight-Pedal Board Buttons (Indexes 5..12)
  {{false, 8, 0, 0, 0}, 0}, {{false, 9, 0, 0, 0}, 0}, {{false, 10, 0, 0, 0}, 0}, {{false, 11, 0, 0, 0}, 0},
  {{false, 12, 0, 0, 0}, 0}, {{false, A0, 0, 0, 0}, 0}, {{false, A1, 0, 0, 0}, 0}, {{false, A2, 0, 0, 0}, 0}
  };

ButtonsManager* pButtonsManager = new ButtonsManager(gFootPedalButtons);

FootPedalSetupManager setupManager;
FootPedalButtonChangedHandler footPedalButtonChangedHandler;
MIDIEventFlasher gMIDIEventFlasher;
StatusManager gStatusManager;


#ifndef SEND_MIDI
Diagnostics diagnostics;
#endif

// This function is called once, upon startup.
void setup()
{
  // Setup serial port and pin states.
  setupManager.Setup();

  DBG_PRINT_LN("Setup() - Setup done.");
}

// This function is called repeatedly.
void loop()
{
  pButtonsManager->ReadButtons(gFootPedalButtons, 0, NumFootPedalButtons - 1, footPedalButtonChangedHandler);

  gStatusManager.UpdateStatusIndicator();
}

