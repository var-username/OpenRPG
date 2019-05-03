/*
characters - race.cpp
Created on: Apr 29, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>
#include <vector>
#include <cstdlib>

#include "names.h"
#include "character.h"

using namespace std;
using namespace ORPG;

/**
 * Races currently assume 5e. What can we do to abstract outside of
 * that space?
 * 
 * TODO(incomingstick): based on how much copy pasting I did, it is clear that
 * setting the name could get ugly quick if we don't turn as much of it into
 * functions.
 */

namespace ORPG {

    Race::Race() {
        Initialize();
    }

    void Race::Initialize() {

    }

    /* The const string representation for a Human */
    const string Human::race = "Human";

    /**
     * @desc Constructor for a Human that is passed no arguments. A base Human
     * has +1 to all stats. Human::Initialize() is called at the end of the
     * constructor.
     */
    Human::Human() {
        abilBonus.setScore(STR, 1);    // Strength
        abilBonus.setScore(DEX, 1);    // Dexterity
        abilBonus.setScore(CON, 1);    // Constitution
        abilBonus.setScore(INT, 1);    // Intelligence
        abilBonus.setScore(WIS, 1);    // Wisdom
        abilBonus.setScore(CHA, 1);    // Charisma
    }

    /**
     * @desc Initialization for a Human that is passed no arguments. 
     * Currently there is no additonal intialization that is done.
     * 
     * NOTE(incomingstick): Here we should finish setting up our race,
     * by doing everything that ALL Races of type Human should do.
     */
    void Human::Initialize() {
        // TODO

        Super::Initialize();
    }

    /* The const string representation for a Dwarf */
    const string Dwarf::race = "Dwarf";

    /**
     * @desc Constructor for a Dwarf that is passed no arguments. A base Dwarf
     * has +2 to CON. Dwarf::Initialize() is called at the end of the
     * constructor.
     */
    Dwarf::Dwarf() {
        abilBonus.setScore(STR, 0);     // Strength
        abilBonus.setScore(DEX, 0);     // Dexterity
        abilBonus.setScore(CON, 2);     // Constitution
        abilBonus.setScore(INT, 0);     // Intelligence
        abilBonus.setScore(WIS, 0);     // Wisdom
        abilBonus.setScore(CHA, 0);     // Charisma

        Initialize();
    }

    /**
     * @desc Initialization for a Dwarf that is passed no arguments. 
     * Currently there is no additional initialization that is done.
     * 
     * NOTE(incomingstick): Here we should finish setting up our race,
     * by doing everything that ALL Races of type Dwarf should do.
     */
    void Dwarf::Initialize() {
        // TODO

        Super::Initialize();
    }

    /* The const string representation for a HillDwarf */
    const string HillDwarf::race = "Hill Dwarf";

    /**
     * @desc Constructor for a HillDwarf that is passed no arguments. A base
     * HillDwarf has +2 to CON and +1 to WIS. HillDwarf::Initialize() is
     * called at the end of the constructor.
     */
    HillDwarf::HillDwarf() {
        abilBonus.setScore(STR, 0);     // Strength
        abilBonus.setScore(DEX, 0);     // Dexterity
        abilBonus.setScore(CON, 2);     // Constitution
        abilBonus.setScore(INT, 0);     // Intelligence
        abilBonus.setScore(WIS, 1);     // Wisdom
        abilBonus.setScore(CHA, 0);     // Charisma

        Initialize();
    }

    // Elf Race (SRD V5.1 pg 4)
    
    /* The const string representation for an Elf */
    const string Elf::race = "Elf";

    /**
     * @desc Constructor for an Elf that is passed no arguments. A base Elf
     * has +2 to DEX. Elf::Initialize() is called at the end of the
     * constructor.
     */
    Elf::Elf() {
        abilBonus.setScore(STR, 0);      // Strength
        abilBonus.setScore(DEX, 2);      // Dexterity
        abilBonus.setScore(CON, 0);      // Constitution
        abilBonus.setScore(INT, 0);      // Intelligence
        abilBonus.setScore(WIS, 0);      // Wisdom
        abilBonus.setScore(CHA, 0);      // Charisma

        Initialize();
    }

    void Elf::Initialize() {
        // TODO
        //size = medium
        //60ft darkvision
        //perception proficiency
        //languages: common and elvish

        Super::Initialize();
    }

    const string HighElf::race = "High Elf";

    HighElf::HighElf() {
        abilBonus.setScore(STR, 0);      // Strength
        abilBonus.setScore(DEX, 2);      // Dexterity
        abilBonus.setScore(CON, 0);      // Constitution
        abilBonus.setScore(INT, 1);      // Intelligence
        abilBonus.setScore(WIS, 0);      // Wisdom
        abilBonus.setScore(CHA, 0);      // Charisma

        Initialize();
    }
}
