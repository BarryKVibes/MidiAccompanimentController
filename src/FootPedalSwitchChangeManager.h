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
enum StyleSectionControlSwitchNum
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

enum StyleNum
{
  // The following style numbers aresGenos values from https://www.psrtutorial.com/forum/index.php/topic,48497.msg380267.html#msg380267
  // Not all Genos style numbers are in PSR-SX900 and vice versa, hence the Unknown enum is used values from 
  // https://www.psrtutorial.com/forum/index.php/topic,48497.msg380267.html#msg380267
  // Not all Genos style numbers are in PSR-SX900 and vice versa, hence the Unknown enum is used, 
  // and set to Default, which is set to BigBandSwing = 0x1E52.
  Default  = 0x1E52, // BigBandSwing
  Unknown  = Default,

  SkyPop = 0x4232, 
  KissDancePop = 0x5201, 
  DancehallPop = 0x5149, 
  BoyBandPop = 0x401F, 
  ReggaetonPop = 0x514D, 
  CanadianRock = 0x2E52, 
  UKSoftRock = 0x514A, 
  _16BeatRock = 0x322C, 
  StadiumRock = 0x2C58, 
  GrungeRock = 0x4F21, 
  SongwriterBallad = 0x2E5C, 
  UnpluggedBallad = 0x2E5F, 
  _6_8GuitarBallad = 0x3C2E, 
  _12_8PopBallad = 0x2B63, 
  SoulfulBallad = 0x2E5B, 
  CountryFolk8Beat = 0x2E18, 
  CountryFolkUpbeat = 0x0A06, 
  CountrySongwriter = 0x2E19, 
  NashvillePop = 0x2E1A, 
  NashvilleRock = 0x404B, 
  USElectroPop = 0x5249, 
  USFolkPop = 0x4C20, 
  USSingerPop = 0x4E69, 
  CanadianTeenPop = 0x4131, 
  _90sAussiePop = 0x4945, 
  _70sHardRock = 0x2C40, 
  _70sShuffleRock = 0x3C41, 
  _70sStraightRock = 0x2C59, 
  _80sClassicRock = 0x322F, 
  _80sPowerRock = 0x2C3F, 
  IrishPopBallad = 0x2C36, 
  SmoothPopBallad = 0x4023, 
  _16BeatBallad = 0x4021, 
  PianoBallad = 0x2C20, 
  _90s8BeatBallad = 0x2C3A, 
  USCountryPop = 0x4050, 
  CountryPopDuo = 0x5021, 
  CalifornianCountry = 0x2E12, 
  CountryPop = 0x2E03, 
  CountryHits = 0x2E04, 
  UKFolkPop = 0x416A, 
  BritPopSwing = 0x3400, 
  _90sGuitarPop = 0x4002, 
  CrazyPop = 0x4012, 
  ReggaetonSlowJam = 0x514B, 
  _80sEdgyRock = 0x2C53, 
  _80sRockDiva = 0x3238, 
  _90sRockBallad = 0x4049, 
  OrchRockBallad1 = 0x2E48, 
  OrchRockBallad2 = 0x4045, 
  UnpluggedPop = 0x2C0A, 
  LoveSong = 0x2C21, 
  _6_8ChartBallad = 0x3C07, 
  BoyBandBallad = 0x2E2D, 
  ModernPopBallad = 0x402F, 
  _90sUSChartBallad = 0x5205, 
  CountryFolkBallad = 0x4E60, 
  CountryBallad1 = 0x2E05, 
  CountryBallad2 = 0x2E06, 
  CountryBallad3 = 0x4204, 
  Live8Beat = 0x2C46, 
  PopEvergreen = 0x2E4A, 
  _00sBoyBand = 0x2C5E, 
  IrishPopRock = 0x4E6B, 
  WestCoastPop = 0x4004, 
  _6_8Rock = 0x3C42, 
  RockShuffleFast = 0x3C43, 
  _80sRockBeat = 0x2C54, 
  _80sSynthRock = 0x4502, 
  PowerRock = 0x2C43, 
  PowerBallad = 0x2C25, 
  VocalPopBallad = 0x2E4C, 
  Acoustic8BtBallad = 0x2E4E, 
  PopRockShuffle = 0x4809, 
  _90sPopShuffle = 0x4968, 
  Country8Beat1 = 0x2E1D, 
  Country8Beat2 = 0x2E00, 
  Country8Beat3 = 0x2E02, 
  CountryBeat = 0x2E32, 
  CountryShuffle = 0x0A01, 
  _90sDancePop = 0x524B, 
  FunkPopRock = 0x4043, 
  ChartPianoShuffle = 0x4808, 
  ContempGtrPop = 0x2E54, 
  CountryRock = 0x2E01, 
  ElectroRock = 0x404E, 
  BritRockPop = 0x2C52, 
  StandardRock = 0x2C47, 
  AcousticRock = 0x4044, 
  _6_8BalladRock = 0x3C2C, 
  ModernPickin = 0x2E10, 
  CountryStrummin = 0x2E0E, 
  CountryStraits = 0x2E13, 
  TopChartCountry = 0x0207, 
  Country2_4 = 0x0200, 
  CountrySingalong = 0x0A03, 
          
  PartyAnthem = 0x4238, 
  ClubReggaeton = 0x5142, 
  Dubstep = 0x4236, 
  DanceFloor = 0x2E3C, 
  DangerDance = 0x423A, 
  _80sMonsterHit = 0x4545, 
  _80sTeenDisco = 0x2D52, 
  _80sEuroPop = 0x322E, 
  _80sSynthPop = 0x412D, 
  _80sClassic6_8 = 0x3C44, 
  ElectroPop = 0x2D55, 
  EDMAnthem = 0x423C, 
  SlowNSwingin = 0x2D39, 
  ChartEDM = 0x2E3D, 
  ElectroHouse1 = 0x4239, 
  ClassicalPop = 0x524A, 
  RetroSoul = 0x3222, 
  _90sPopBallad = 0x5206, 
  Cool8Beat = 0x2C03, 
  Wonder8Beat = 0x2C02, 
  ClubMixDJ = 0x4220, 
  FrenchDJ = 0x2D4E, 
  ReggaetonDJ = 0x415F, 
  MinimalElectro = 0x2D4D, 
  NatureHipHop = 0x4166, 
  _80sRetroDisco = 0x2D54, 
  _80sBritishPop = 0x401E, 
  _80sSynthDuo = 0x2D36, 
  _80sFunkIcon = 0x412F, 
  _80sPopBallad = 0x2E5D, 
  StreetBeatbox = 0x496C, 
  BigRoom = 0x4221, 
  USClubDance = 0x4222, 
  ClubDance1 = 0x4156, 
  ClubDance2 = 0x2D40, 
  Up_Tempo8Beat = 0x2E20, 
  Swedish8BeatPop = 0x2C1D, 
  SwedishPopShuffle = 0x3462, 
  SynthPop = 0x4031, 
  _80sBoyBand = 0x402C, 
  EuroTrance = 0x2D43, 
  RetroDance = 0x2D45, 
  ClubHouse1 = 0x4942, 
  DreamDance = 0x4144, 
  GlobalDJs = 0x4147, 
  _70sDisco1 = 0x4122, 
  _70sDisco2 = 0x2D20, 
  DiscoSurvival = 0x4368, 
  _70sSpanishDisco = 0x4132, 
  _70sDiscoFunk = 0x4123, 
  TrancePop = 0x4151, 
  Electronica = 0x4155, 
  ModernHipHop = 0x2E24, 
  FunkyHouse = 0x2D2A, 
  DirtyPop = 0x415A, 
  _80sDivaBallad = 0x3C20, 
  _80sGuitarPop = 0x2C51, 
  _80s8Beat = 0x2E26, 
  _80sPianoBallad = 0x2C39, 
  _80sAnalogBallad = 0x4037, 
  ClubHouse2 = 0x4226, 
  MiamiHouse = 0x4227, 
  ElectroHouse2 = 0x4228, 
  GangstaHouse = 0x4229, 
  GrindHouse = 0x422A, 
  PianoHouse = 0x422B, 
  ElectroStep = 0x422C, 
  Eurodance1 = 0x422D, 
  Eurodance2 = 0x422E, 
  TropicalHouse = 0x422F, 
  FrenchClub = 0x415B, 
  Ibiza2010 = 0x2D42, 
  ChilloutCafe = 0x4032, 
  Chillout1 = 0x407, 
  Chillout2 = 0x408, 
  _70sGlamPiano = 0x2E40, 
  _70s8BeatBallad = 0x2C24, 
  DiscoChocolate = 0x4520, 
  PhillyDisco = 0x4120, 
  FunkDisco = 0x41A, 
  ChillPerformer = 0x1829, 
  CloudyBay = 0x182A, 
  NightWalk = 0x182B, 
  Play4Sofa = 0x182C, 
  AngelSun = 0x182D, 
  _80sDiscoBeat = 0x4540, 
  _6_8ClassicSynth = 0x3D40, 
  PopWaltz = 0x3820, 
  _90sDisco = 0x2D24, 
  HipHop = 0x4160, 
  TurkishEuro = 0x4014, 
  MrSoul = 0x410, 
  SoulShuffle = 0x1C74, 
  SoulSupreme = 0x2D02, 
  DetroitPop = 0x1C66, 
  MotorCity = 0x2D01, 
  _60sBlueEyedSoul = 0x2E3B, 
  _60sShadowedPop = 0x2C05, 
  _60sVintageRumba = 0x2F30, 
  _60sOrganBallad = 0x2C28, 
  _60sChartSwing = 0x1C01, 
  LovelyShuffle = 0x3C02, 
  FranklySoul = 0x4105, 
  _6_8SoulBallad = 0x3D00, 
  UKSoul = 0x4F20, 
  DetroitBeat = 0x2D07, 
  _60sRisingPop = 0x3C28, 
  _60sUnderground = 0x2C5A, 
  _60sPianoPop = 0x2E23, 
  _60s8Beat = 0x2C6, 
  _60sVintagePop = 0x2F2B, 
  SlowBlues = 0x3D2, 
  BluesRock = 0x2D0, 
  BluesShuffle = 0x1C65, 
  CountryBlues = 0x2E11, 
  FunkyShuffle = 0x48E, 
  RockAndRoll = 0x2C64, 
  _50sRockAndRoll = 0x1C6F, 
  _60sRockAndRoll = 0x2C62, 
  RockAndRollJive = 0x1C67, 
  RockAndRollShuffle = 0x3461, 
  JustRnB = 0x2D3E, 
  RAndBShuffle = 0x1C6E, 
  KoolShuffle = 0x4805, 
  FusionShuffle = 0x4802, 
  _70sCoolBallad = 0x4563, 
  OldiesRockAndRoll = 0x3463, 
  Twist = 0x2C60, 
  Skiffle = 0x2C65, 
  PianoBoogie = 0x1C61, 
  BlueberryBlues = 0x3C60, 
  _80sSmoothBallad = 0x4034, 
  _90sSmoothBallad = 0x4033, 
  RAndBSoulBallad = 0x4109, 
  CoolRAndB = 0x4016, 
  RAndBSlowBallad = 0x2E51, 
  _60sSuperGroup = 0x3223, 
  _60sBigHit = 0x4019, 
  _60sVintageRock = 0x2C44, 
  _60sPopRock = 0x2C45, 
  VintageGuitarPop = 0x2C01, 
  AmazingGospel = 0x2B62, 
  HollywoodGospel = 0x480A, 
  GospelSwing = 0x0800, 
  GospelBallad = 0x2E4B, 
  SouthernGospel = 0x3D04, 
  SurfRock = 0x2E2C, 
  BeachRock = 0x2C67, 
  Classic8Beat = 0x2E21, 
  _6_8SlowRock = 0x3C23, 
  BubblegumPop = 0x2C7, 
  Worship6_8 = 0x3F64, 
  WorshipSlow = 0x2C2E, 
  GospelBrothers = 0x411, 
  GospelSisters = 0x1460, 
  SoulBallad = 0x4030, 
  JazzFunk = 0x414, 
  JazzFusion = 0x483, 
  _70sScatLegend = 0x48B, 
  _70sChartSoul = 0x417, 
  LiveSoulBand = 0x4042, 
  FunkPop = 0x4969, 
  BigBandSwing = 0x1E52, 
  BigBandJazz = 0x1E51, 
  ClassicBigBand = 0x1E44, 
  ModernBigBand = 0x1E2E, 
  BigBandBallad = 0xA49, 
  OrchestralSwing1 = 0xA46, 
  OrchestralSwing2 = 0x1E4A, 
  Orchestral6_8 = 0x3C21, 
  PartyAGogo = 0xA3B, 
  HappyBeat = 0x2E1E, 
  AcousticJazz = 0x1E20, 
  CoolPianoJazz = 0x1E34, 
  InstrumentalJazz = 0x1E2F, 
  CoolSwing = 0x1E37, 
  CoolJazzBallad = 0x0A2D, 
  DreamyBallad = 0x0A4A, 
  EasyBallad = 0x2C26, 
  EpicBallad = 0x2C2A, 
  Orchestral12_8 = 0x3C24, 
  Tijuana = 0x0B00, 
  JazzOrganGroove = 0x2C0C, 
  JazzOrganCombo = 0x1E30, 
  JazzGuitarClub = 0x1E26, 
  OrchBigBand1 = 0x1E42, 
  OrchBigBand2 = 0x1E43, 
  _70sPopDuo1 = 0x2C23, 
  _70sPopDuo2 = 0x2E4D, 
  _70sEasyPop = 0x2E0F, 
  _70sChartBallad = 0x2C3E, 
  EasySwing = 0x0A28, 
  TradPianoJazz = 0x1E31, 
  TradPianoBallad = 0x1E32, 
  ManhattanSwing = 0x1E35, 
  FastJazz = 0x1E3A, 
  CoolJazzWaltz = 0x1629, 
  EasyPop = 0x2E22, 
  EasyListening = 0x0A40, 
  MidnightSwing = 0x0A41, 
  _40sSwingBallad = 0x0A4C, 
  EuroPopOrgan = 0x2C1B, 
  SlowJazzWaltz = 0x1622, 
  MediumJazzWaltz = 0x1621, 
  FrenchJazz = 0x0A29, 
  AfroCuban = 0x7B01, 
  FiveFour = 0x2400, 
  OrganSwing = 0x0A26, 
  OrganBossa = 0x2F0E, 
  RomanticWaltz = 0x0F79, 
  _8BeatAdria = 0x2C08, 
  Easy8Beat = 0x2E31, 
  BigBandFast1 = 0x1E46, 
  BigBandFast2 = 0x0A43, 
  BigBandMedium = 0x1E40, 
  SwinginBigBand = 0x1E45, 
  BigBandShuffle = 0x1E4F, 
  CountrySwing = 0x0A00, 
  Hawaiian = 0x0B62, 
  Dixieland = 0x0A2B, 
  Ragtime = 0x0221, 
  JumpJive = 0x1C60, 
  Reggaeton1 = 0x5344, 
  Reggaeton2 = 0x514E, 
  PopCha_Cha = 0x2F12, 
  RockCha_Cha = 0x2F2F, 
  FastCha_Cha = 0x2F1C, 
  CoolBossa = 0x0273, 
  BossaBrazil = 0x026C, 
  LoungeBossa = 0x026B, 
  SlowBossa = 0x0262, 
  BossaNova = 0x0264, 
  CubanCha_Cha = 0x2F11, 
  Bachata = 0x2F28, 
  PopBachata = 0x2F33, 
  PopCumbia = 0x5144, 
  Axe = 0x412B, 
  SambaRio = 0x0275, 
  SambaReggae = 0x2F2C, 
  SalsaGranCiclon = 0x4313, 
  RumbaFlamenco = 0x4325, 
  TangoFlamencos = 0x4328, 
  LatinPartyPop = 0x4035, 
  _80sBrazilianPop = 0x514C, 
  EuroPopMambo = 0x0A54, 
  LiveMerengue = 0x431D, 
  BrazilianBossa = 0x0272, 
  Parranda = 0x4311, 
  Forro = 0x0372, 
  Joropo = 0x0F78, 
  CubanSon = 0x4310, 
  Guajira = 0x2F0F, 
  Guaguanco = 0x430F, 
  Salsa = 0x430E, 
  BoleroLento = 0x2F02, 
  GuitarRumba = 0x2F20, 
  JazzSamba = 0x4268, 
  PopLatin = 0x2F25, 
  PopBossa = 0x0261, 
  PopLatinBallad = 0x2F2A, 
  SheriffReggae = 0x4720, 
  HappyReggae = 0x0B20, 
  FinalWaltz = 0x1623, 
  VocalWaltz = 0x1628, 
  EnglishWaltz = 0x0C00, 
  SlowWaltz = 0x0C3, 
  Jive = 0x1C00, 
  Quickstep1 = 0x0A3C, 
  Quickstep2 = 0x0A23, 
  SlowFoxtrot1 = 0x0A52, 
  SlowFoxtrot2 = 0x0A22, 
  VocalFoxtrot = 0x0A4D, 
  Cha_Cha = 0x2F03, 
  Samba = 0x4263, 
  Rumba = 0x2F00, 
  Beguine = 0x2F01, 
  Tango = 0x1B00, 
  Pasodoble = 0x1B60, 
  Foxtrot = 0x0A20, 
  SwingFox = 0x0A21, 
  Charleston = 0x0A2A, 
  OrganQuickstep = 0x0A24, 
  OrganCha_Cha = 0x2F04, 
  OrganSamba = 0x4261, 
  OrganRumba = 0x2F29, 
  Gunslinger = 0x4E65, 
  WildWest = 0x2F66, 
  SecretService = 0x2C2C, 
  Sci_FiMarch = 0x036C, 
  MovieSoundtrack = 0x1001, 
  OnBroadway = 0x1827, 
  MovieHorns = 0x1830, 
  EtherealMovie = 0x1822, 
  EtherealVoices = 0x1826, 
  MovieClassic = 0x2E49, 
  AnimationFantasy = 0x1B41, 
  AnimationBallad = 0x2E41, 
  IcyBallad = 0x4E68, 
  MoviePanther = 0x1E49, 
  BlockbusterBallad = 0x404F, 
  VienneseWaltz = 0x1000, 
  OrchPopClassics = 0x2CD, 
  StringAdagio = 0x2F70, 
  Moonlight6_8 = 0x3C22, 
  OrchestralPolka = 0x0362, 
  MovieDisco = 0x2D25, 
  SaturdayNight = 0x4124, 
  _70sTVTheme = 0x4005, 
  _80sMovieBallad = 0x4010, 
  MovieBallad = 0x1820, 
  _6_8March = 0x0B40, 
  USMarch = 0x0340, 
  OrchestralMarch = 0x0341, 
  BaroqueAir = 0x2F68, 
  GreenFantasia = 0x3F69, 
  _80sChristmas = 0x2D35, 
  ChristmasBallad = 0x0B66, 
  ChristmasSwing = 0x0B60, 
  ChristmasWaltz = 0x0F62, 
  OrganHymn = 0x182F, 
  MovieSwing1 = 0x0A48, 
  MovieSwing2 = 0x0A44, 
  PopMusical = 0x4946, 
  ItsShowtime = 0x1B40, 
  TapDanceSwing = 0x0A27, 
  OrchMovieBallad = 0x4E6A, 
  BroadwayBallad = 0x2C2D, 
  GuitarSerenade = 0x0F63, 
  DreamSchlager = 0x4233, 
  FantasyFox = 0x4237, 
  ApresSkiParty = 0x2D38, 
  PopRumba = 0x2F17, 
  SchlagerRock = 0x2C57, 
  AlpenSchlager = 0x2E39, 
  VolksDance = 0x377, 
  OktoberRockHit = 0x020E, 
  VolksSchlager = 0x3232, 
  SchlagerFox = 0x2E25, 
  YoungFox = 0x2D31, 
  YoungBallad = 0x2E30, 
  HelloShuffle = 0x3F6A, 
  ModernSchlager = 0x3224, 
  SchlagerPop = 0x1800, 
  SchlagerBeat = 0x2C0E, 
  SchlagerAlp = 0x2C0F, 
  SchlagerRumba = 0x2F24, 
  Schlager6_8 = 0x3C25, 
  SchlagerFever = 0x2C5C, 
  AlpenBallad1 = 0x3F62, 
  AlpenBallad2 = 0x3F63, 
  PartyPolka = 0x0000, 
  SchlagerPolka = 0x0365, 
  SchlagerPalace = 0x2E2B, 
  PolkaPop = 0x0361, 
  SchlagerShuffle = 0x3C00, 
  SchlagerSamba = 0x4360, 
  DiscoFox = 0x2D2B, 
  DiscoFoxRock = 0x2C5B, 
  GermanRock = 0x2C55, 
  SchlagerWaltz = 0x2B60, 
  MallorcaParty = 0x2D2C, 
  MallorcaDisco = 0x4159, 
  PartyArena = 0x2D2D, 
  SoftSchlager = 0x2E2A, 
  ApresSkiHit = 0x2D2E, 
  SynthPopDuo = 0x2D2F, 
  RumbaIsland = 0x0300, 
  _70sFrenchHit = 0x2F69, 
  SingalongDanceBand = 0x0A3D, 
  SingalongPiano = 0x0373, 
  PubPiano = 0x0360, 
  Hoedown = 0x0201, 
  Bluegrass = 0x020A, 
          
  CountryWaltz = 0x1601, 
  ModCeltic4_4 = 0x2F71, 
  ModCeltic6_8 = 0x3C2B, 
  OberkrainerPolka1 = 0x0001, 
  OberkrainerPolka2 = 0x0363, 
  ZitherPolka = 0x0371, 
  OberkrainerWaltz1 = 0x0F7D, 
  OberkrainerWaltz2 = 0x0F65, 
  SaeidyPop = 0x2D66, 
  Saeidy = 0x2D61, 
  WehdaSaghira = 0x2D63, 
  Laff = 0x2D64, 
  ArabicEuro = 0x2D65, 
  ModernDangdut1 = 0x3221, 
  ModernDangdut2 = 0x4366, 
  Keroncong = 0x2E4F, 
  Bhangra = 0x0A37, 
  Bhajan = 0x2D4B, 
  ScottishJig = 0x1F61, 
  ScottishReel = 0x0367, 
  ScottishStrathspey = 0x0370, 
  ScottishPolka = 0x0B65, 
  ScottishWaltz = 0x0F74, 
  BrassBand = 0x1828, 
  IrishHymn = 0x3F65, 
  CelticDance3_4 = 0x1462, 
  CelticDance = 0x2F6B, 
  IrishDance = 0x4362, 
  JingJuJieZou = 0x0209, 
  XiQingLuoGu = 0x2C56, 
  Duranguense = 0x0347, 
  Grupera = 0x4312, 
  MalfufFunk = 0x2D67, 
  ScandSlowRock = 0x3C03, 
  ScandCountry = 0x2E07, 
  ScandBugg = 0x1C64, 
  ScandShuffle = 0x3761, 
  ScandWaltz = 0x0F6B, 
  FrenchMusette = 0x0F67, 
  FrenchWaltz = 0x0F68, 
  Tarantella = 0x0B63, 
  Sirtaki = 0x0368, 
  MexicanDance = 0x036A, 
  BohemianWaltz = 0x2B61, 
  GermanWaltz = 0x0F76, 
  ItalianWaltz = 0x0F6A, 
  ItalianMazurka = 0x0F69, 
  MariachiWaltz = 0x0F6E, 
  Flamenco = 0x0F6D, 
  SpanishPaso = 0x1B61, 
  USMarchingBand = 0x0348, 
  GermanMarch1 = 0x0343, 
  GermanMarch2 = 0x0344, 
  AlpenLand = 0x2E2E, 
  FolkSongDuo = 0x2C09, 
  FolkPop = 0x2E0D
};

public:

  // This method is the default constructor.
  FootPedalSwitchChangeManager();
  void HandleButtonChange(int buttonIndex, bool isActive);

private:
  void HandleFivePedalBoardSwitchChange(int buttonIndex, bool isActive);
  void HandleEightPedalBoardSwitchChange(int buttonIndex, bool isActive);

  void SendStyleSectionControlSysEx(StyleSectionControlSwitchNum switchNum, bool isSwitchOn);
  void SendStyleNumSysEx(uint16_t styleNum);
  void SendTempoSysEx(uint16_t tempo);

  String PrependZeros(String plaintext, uint8_t numCharsWide);

private:
  const uint16_t DefaultTempo = 120;
  const uint16_t MaxTempo = 220;
  const uint16_t MinTempo = 30;
  
  uint16_t mCurTempo;
};

#endif
