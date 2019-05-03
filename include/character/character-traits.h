/*
characters - character-traits.h
Created on: Apr 29, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_CHARACTER_TRAITS_H_
#define SRC_CHARACTER_TRAITS_H_

namespace ORPG {
    /* NOTE: These are just the 5E character requirements */

	/* an arrray that holds the EXP needed for each level */
	const int levels[] = {
		300,          // Level 2
		900,          // Level 3
		2700,         // Level 4
		6500,         // Level 5
		14000,        // Level 6
		23000,        // Level 7
		34000,        // Level 8
		48000,        // Level 9
		64000,        // Level 10
		85000,        // Level 11
		100000,       // Level 12
		120000,       // Level 13
		140000,       // Level 14
		165000,       // Level 15
		195000,       // Level 16
		225000,       // Level 17
		265000,       // Level 18
		305000,       // Level 19
		355000        // Level 20
	};

	/* An enum containing the traditional alignment grid */
	enum Alignment {
		LawfulGood, 	NeutralGood, 	ChaoticGood,
		LawfulNeutral, 	TrueNeutral, 	ChaoticNeutral,
		LawfulEvil, 	NeutralEvil, 	ChaoticEvil
	};

	/* An enum containing the list of D&D 5E languages */
	enum Language {
		Common,    Dwarvish,   Elvish,
		Giant,     Gnomish,    Goblin,
		Halfling,  Orc,        Abyssal,
		Celestial, Draconic,   DeepSpeech,
		Infernal,  Primordial, Silvian,
		Undercommon
	};

	/*
	 * An enum containing genders
	 * 
	 * NOTE(incomingstick): How far do we want to take this? We could
	 * put ourselves in  a tricky place if this is done wrong.
	 */
	enum Gender {
		Male,
		Female,
		Agender
	};

	enum Size {
		Tiny,        // 2½ by 2½ ft.          [under 2 feet tall]
		Small,       // 5 by 5 ft.            [2 to 4 feet tall]
		Medium,      // 5 by 5 ft.            [4 to 8 feet tall]
		Large,       // 10 by 10 ft.          [8 to 12 feet tall]
		Huge,        // 15 by 15 ft.          [12 to 16 feet tall]
		Gargantuan   // 20 by 20 ft or larger [taller than 16 feet]
	};

	enum VisionType {
		Normal,
		Blindsight,
		DarkVision,
		TrueSight
	};

	struct Vision {
		VisionType type;    // type of sight
		int radius;         // radius of vision in feet (-1 == infinite IF unobstructed)
	};

}

#endif