/*
characters - character.h
Created on: Jan 30, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 < https://www.openrpg.io/about/license/ >
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "ability-scores.h"
#include "skills.h"
#include "character-traits.h"
#include "races.h"

namespace ORPG {
	namespace Characters {
		void print_version_flag();
		void print_help_flag();
		void print_basic_version();
		void print_basic_help();
	}

	/* Generates an array of stats > 1 && < 20 */
	std::vector<int> ability_score_vector();

	// TODO take an in depth look at what should and should not be public here
	class Character {
	private:
		Race* race;							// The race of our character
		struct Vision vision;               // information about the characters vision
		size_t age;                         // the age of the character
		Alignment alignment;                // the character alignment
		Size size;                          // the size type
		std::string firstName;              // the characters first name
		std::string lastName;               // the characters first name
		AbilityScores abils;                // struct of ability scores
		Skills skills;                      // struct of skill checks
		int curr_hp;                        // current hit points
		int temp_hp;                        // temporary hit points
		int max_hp;                         // maximum hit points
		int prof;                           // proficiency bonus
		int level;                          // character level total
		int cur_exp;                        // current experience
		int max_exp;                        // experience needed for next level
		std::vector<Language> languages;    // the array of known languages
		Gender gender;                      // the characters gender
	
		void Initialize();

	public:
		/*
			* TODO(incomingstick): reduce the number of constructors here via defaults
			*/
		Character();
		Character(const int raceID);
		Character(AbilityScores ab);
		Character(AbilityScores ab, const int raceID);
		Character(AbilityScores ab, std::string name);
		Character(std::string name);
		Character(std::string name, const int raceID);
		Character(AbilityScores ab, std::string name, const int raceID);
		~Character();
	
		std::string format_mod(int mod, int spaces);
	
		void update_skills();

		// an integer that represents the Character class
		static const int ID = 0x0000;    

		// Returns a copy of our Ability abils struct
		AbilityScores get_ability_copy() { return abils; };

		// Returns a copy of our Skills skills struct
		// NOTE(var_username): Commented out because I broke it
		// Skills get_skills_copy() { return skills; };
	
		/* accessor functions for ability score modifiers */
		int STR() { return abils.getScore(EnumAbilityScore::STR); };
		int DEX() { return abils.getScore(EnumAbilityScore::DEX); };
		int CON() { return abils.getScore(EnumAbilityScore::CON); };
		int INT() { return abils.getScore(EnumAbilityScore::INT); };
		int WIS() { return abils.getScore(EnumAbilityScore::WIS); };
		int CHA() { return abils.getScore(EnumAbilityScore::CHA); };
	
		/* accessor functions for ability score modifiers */
		int STR_MOD() { return abils.getMod(EnumAbilityScore::STR); };
		int DEX_MOD() { return abils.getMod(EnumAbilityScore::DEX); };
		int CON_MOD() { return abils.getMod(EnumAbilityScore::CON); };
		int INT_MOD() { return abils.getMod(EnumAbilityScore::INT); };
		int WIS_MOD() { return abils.getMod(EnumAbilityScore::WIS); };
		int CHA_MOD() { return abils.getMod(EnumAbilityScore::CHA); };

		/* accessor functions for ability score saves */
		int STR_SAVE() { return modifier(abils.getSave(EnumAbilityScore::STR)); };
		int DEX_SAVE() { return modifier(abils.getSave(EnumAbilityScore::DEX)); };
		int CON_SAVE() { return modifier(abils.getSave(EnumAbilityScore::CON)); };
		int INT_SAVE() { return modifier(abils.getSave(EnumAbilityScore::INT)); };
		int WIS_SAVE() { return modifier(abils.getSave(EnumAbilityScore::WIS)); };
		int CHA_SAVE() { return modifier(abils.getSave(EnumAbilityScore::CHA)); };
	
		// allows quick conversion of a skill for its passive check
		int passive_stat(int stat) { return 8 + prof + stat; };
	
		std::string to_string();
		std::string to_sheet();
	};

	/*  */
	class CharacterFactory {
    private:
        struct race_node {
            int raceID;
            bool required;
            
            race_node* parent;
            std::vector<race_node* > children;
        };

        race_node* head;
        race_node* current;
        race_node* allocate_node(int raceID,
                                bool required,
                                race_node* parent);
    public:
        CharacterFactory();
        ~CharacterFactory();

        Character* NewCharacter(AbilityScores ab = AbilityScores());
        Character* NewCharacter(int identifier);
        Character* NewCharacter(int identifier, AbilityScores ab);
        Character* NewCharacter(AbilityScores ab,std::string name);

        void reset() { current = head; };
        std::vector<std::string> current_options();
        bool has_options();
        void select_option(int index);
        int current_id();
    };
}

#endif /* CHARACTER_H_ */
