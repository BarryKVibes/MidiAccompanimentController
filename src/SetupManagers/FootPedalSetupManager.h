/*******************************************************************************
  FootPedalSetupManager.h
  
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

#ifndef FootPedalSetupManager_H
#define FootPedalSetupManager_H

#include "SetupManagerBase.h"
#include "../SharedConstants.h"

class FootPedalSetupManager : public SetupManagerBase
{
public:
  FootPedalSetupManager();

  void Setup();
  int GetNumButtons();
  Button& GetButtonAt(int index);
};

#endif
