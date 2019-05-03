/*
characters - character-traits.cpp
Created on: Apr 29, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/

#include "character/skills.h"
#include "character/ability-scores.h"
#include "roll.h"

namespace ORPG {

    /* Generates a stat > 1 && < 20 */
	int gen_stat() {
        /* TODO accept different types of stat generation */

        Die d6(6);

        return d6.roll() + d6.roll() + 6;
    }

    Skill::Skill(int8 modifier, uint8 proficiencyBonus) {
        this->mod = modifier;
        this->profBonus = proficiencyBonus;
    }
    
    void Skill::set(int8 modifier, uint8 proficiencyBonus) {
        this->mod = modifier;
        this->profBonus = proficiencyBonus;
    }

    void Skill::setMod(int8 modifier) {
        this->mod = modifier;
    }

    void Skill::setProfBonus(uint8 modifier) {
        this->profBonus = modifier;
    }

    int8 Skill::getMod() {
        return this->mod;
    }

    uint8 Skill::getProfBonus() {
        return this->profBonus;
    }

    Skills::Skills() {
        this->skillsMap = {
            { ACR, new Skill(0, 0) },    // Acrobatics       (DEX)
            { ANM, new Skill(0, 0) },    // Animal Handling  (WIS)
            { ARC, new Skill(0, 0) },    // Arcana           (INT)
            { ATH, new Skill(0, 0) },    // Athletics        (STR)
            { DEC, new Skill(0, 0) },    // Deception        (CHA)
            { HIS, new Skill(0, 0) },    // History          (INT)
            { INS, new Skill(0, 0) },    // Insight          (WIS)
            { ITM, new Skill(0, 0) },    // Intimidation     (CHA)
            { INV, new Skill(0, 0) },    // Investigation    (INT)
            { MED, new Skill(0, 0) },    // Medicine         (WIS)
            { NAT, new Skill(0, 0) },    // Nature           (INT)
            { PRC, new Skill(0, 0) },    // Perception       (WIS)
            { PRF, new Skill(0, 0) },    // Performance      (CHA)
            { PRS, new Skill(0, 0) },    // Persuasion       (CHA)
            { REL, new Skill(0, 0) },    // Religion         (INT)
            { SLE, new Skill(0, 0) },    // Sleight of Hand  (DEX)
            { STL, new Skill(0, 0) },    // Stealth          (DEX)
            { SUR, new Skill(0, 0) }     // Survival         (WIS)
        };
    }

    Skills::~Skills() {
        delete[] &skillsMap;
    }

    Skill* Skills::get(EnumSkill skill) {
        return skillsMap[skill];
    }

    /**
     * @desc Constructor for AbilityScore that is passed no arguments.
     * It sets score equal to a randomly generated number between 8 and 18,
     * and sets isProf to false.
     *
    AbilityScore::AbilityScore() {
        this->score = gen_stat();
        this->prof = false;
    }
    */
    
    /**
     * @desc Constructor for AbilityScore that is passed two arguments.
     * It sets this->score equal to score and sets this->isProf to isProf.
     * 
     * @param uint8 score - the unsigned 8-bit integer score value to set. 
     * @param bool isProf - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    AbilityScore::AbilityScore(uint8 score, bool isProf) {
        this->score = score;
        this->prof = isProf;
    }

    /**
     * @desc Deconstructor for AbilityScore that is passed no arguments.
     * Currently does nothing, and the compiler handles deconstruction.
     */
    AbilityScore::~AbilityScore() {
        // TODO
    }

    /**
     * @desc Setter method for score and isProf. isProf is a boolean
     * representation of whether or not a proficiency bonus should be added to
     * the save of the given AbilityScore.
     * 
     * @param uint8 score - the unsigned 8-bit integer score value to set. 
     * @param bool isProf - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScore::set(uint8 newScore, bool isProf) {
        this->score = newScore;
        this->prof = isProf;
    }

    /**
     * @desc Setter method for an AbilityScore's score.
     * 
     * @param uint8 score - the unsigned 8-bit integer score value to set. 
     */
    void AbilityScore::setScore(uint8 score) {
        this->score = score;
    }

    /**
     * @desc Setter method for the isProf property. isProf is a boolean
     * representation of whether or not a proficiency bonus should be
     * added for the save of the given AbilityScore.
     * 
     * @param bool isProf - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScore::setIsProf(bool isProf) {
        this->prof = isProf;
    }

    /**
     * @desc Accessor method for an AbilityScore's score.
     * 
     * @return uint8 - an unsigned 8-bit integer of the AbilityScore's score
     */
    uint8 AbilityScore::getScore() {
        return this->score;
    }

    /**
     * @desc Accessor method for the AbilityScore's modifier.
     * A modifier is defined as:
     * 
     * Mod = floor((Score - 10) / 2);
     * 
     * @return int8 - an 8-bit integer of the AbilityScore's modifier
     */
    int8 AbilityScore::getMod() {
        return modifier(this->score);
    }

    /**
     * @desc Accessor method for the isProf property. The current Proficiency
     * bonus should be added to any AbilityScore's modifier that has isProf
     * set to true, otherwise it is just the AbilityScore's modifier. It is
     * up to the implementer to handle that addition.
     * 
     * @return bool - a boolean value denoting whether or not a proficiency
     * bonus should be added to the save of this AbilityScore
     */
    bool AbilityScore::isProf() {
        return this->prof;
    }

    /**
     * @desc Constructor for AbilityScores that is passed no arguments.
     * It sets all ability scores equal to 10 and isProf to false.
     */
    AbilityScores::AbilityScores() {
        this->scoresMap = {
            { STR, new AbilityScore(10, false) },
            { DEX, new AbilityScore(10, false) },
            { CON, new AbilityScore(10, false) },
            { INT, new AbilityScore(10, false) },
            { WIS, new AbilityScore(10, false) },
            { CHA, new AbilityScore(10, false) }
        };
    }

    /**
     * @desc Deconstructor for AbilityScores that is passed no arguments.
     * Currently does nothing, and the compiler handles deconstruction.
     */
    AbilityScores::~AbilityScores() {
        // TODO
    }

    /**
     * @desc Setter method for an AbilityScore's score and isProf, denoted
     * by EnumAbilityScore ability. isProf is a boolean representation of
     * whether or not a proficiency bonus should be added to the save of the
     * given AbilityScore.
     * 
     * @param EnumAbilityScore ability - the AbilityScore score to query
     * @param uint8 score - the unsigned 8-bit integer score value to set. 
     * @param bool isProf - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScores::set(EnumAbilityScore ability, uint8 newScore, bool isProf) {
        scoresMap[ability]->set(newScore, isProf);
    }

    /**
     * @desc Accessor method for an AbilityScore, denoted by
     * EnumAbilityScore ability. This returns the pointer of the queried
     * AbilityScore.
     * 
     * @param EnumAbilityScore ability - the AbilityScore score to query
     * 
     * @return AbilityScore* - an pointer to the AbilityScore's denoted by
     * EnumAbilityScore ability
     */
    AbilityScore* AbilityScores::get(EnumAbilityScore ability) {
        return scoresMap[ability];
    }

    /**
     * @desc Setter method for an AbilityScore's score, denoted
     * by EnumAbilityScore ability. A modifier is defined as:
     * 
     * Mod = floor((Score - 10) / 2);
     * 
     * @param EnumAbilityScore ability - the AbilityScore score to query
     * @param uint8 score - the unsigned 8-bit integer score value to set. 
     */
    void AbilityScores::setScore(EnumAbilityScore ability, uint8 score) {
        scoresMap[ability]->setScore(score);
    }

    /**
     * @desc Setter method for the isProf property AbilityScore, denoted by
     * EnumAbilityScore ability. isProf is a boolean representation of whether
     * or not a proficiency bonus should be added to the save of the given
     * AbilityScore.
     * 
     * @param EnumAbilityScore ability - the AbilityScore score to query
     * @param bool isProf - a boolean value denoting whether or not a
     * proficiency bonus should be added to the save of the given AbilityScore
     */
    void AbilityScores::setIsProf(EnumAbilityScore ability, bool isProf) {
        scoresMap[ability]->setIsProf(isProf);
    }

    /**
     * @desc Setter method for curProf, the current Proficiency Bonus
     * that is added to any AbilityScore that has isProf set to true.
     * 
     * @param uint8 - a unsigned 8-bit integer containing the current
     * Proficiency bonus that is added to any AbilityScore that has isProf
     * set to true.
     */
    void AbilityScores::setCurrentProf(uint8 newProf) {
        curProf = newProf;
    }
}