/*
character-generator - race.cpp
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

/*
 * TODO(incomingstick): based on how much copy pasting I did, it is clear that
 * setting the name could get ugly quick if we don't turn as much of it into
 * functions.
 */

namespace ORPG {
    const string Human::race = "Human";

    Human::Human(Ability ab, string name) {
        abils.STR = ab.STR + 1;    // Strength
        abils.DEX = ab.DEX + 1;    // Dexterity
        abils.CON = ab.CON + 1;    // Constitution
        abils.INT = ab.INT + 1;    // Intelligence
        abils.WIS = ab.WIS + 1;    // Wisdom
        abils.CHA = ab.CHA + 1;    // Charisma

        // TODO parse and set the name here, generating any missing pieces

        firstName = name;

        Initialize();
    }

    void Human::Initialize() {
        NameGenerator ng(race);
        if (firstName.empty())
            firstName = ng.make_first();
        lastName = ng.make_last();


        // Standard character initialization
        curr_hp = 10;                   // TODO current hit points
        temp_hp = 0;                    // TODO temporary hit points
        max_hp = curr_hp;               // TODO maximum hit points
        prof = 2;                       // proficiency bonus
        level = 1;                      // character level total
        cur_exp = 0;                    // current experience
        max_exp = levels[level - 1];    // experience needed for next level

        // Race specific features
        // SRD V5.1 pg 5
        size = Medium;
        // speed = 30;
        languages.push_back(Common);

        Character::Initialize();
    }

    const string Dwarf::race = "Dwarf";

    Dwarf::Dwarf(Ability ab, string name) {
        abils.STR = ab.STR;     // Strength
        abils.DEX = ab.DEX;     // Dexterity
        abils.CON = ab.CON + 2; // Constitution
        abils.INT = ab.INT;     // Intelligence
        abils.WIS = ab.WIS;     // Wisdom
        abils.CHA = ab.CHA;     // Charisma

        Initialize();
    }

    void Dwarf::Initialize() {
        // TODO parse and set the name here, generating any missing pieces
        NameGenerator ng(race);

        if(firstName.empty())
            firstName = ng.make_first();
        lastName = ng.make_last();

        // Standard character initialization
        curr_hp = 10;                   // TODO current hit points
        temp_hp = 0;                    // TODO temporary hit points
        max_hp = curr_hp;               // TODO maximum hit points
        prof = 2;                       // proficiency bonus
        level = 1;                      // character level total
        cur_exp = 0;                    // current experience
        max_exp = levels[level - 1];    // experience needed for next level

        // Race specific features
        // SRD V5.1 pg 3
        vision.type = DarkVision;
        vision.radius = 60;
        size = Medium;
        //speed = 25;
        languages.push_back(Common);
        languages.push_back(Dwarvish);

        Character::Initialize();
    }

    // TODO Hill Dwarves get +1 hp max for each level (SRD V5.1 pg 4)
    HillDwarf::HillDwarf(Ability ab, string name) {
        abils.STR = ab.STR;     // Strength
        abils.DEX = ab.DEX;     // Dexterity
        abils.CON = ab.CON + 2; // Constitution
        abils.INT = ab.INT;     // Intelligence
        abils.WIS = ab.WIS + 1; // Wisdom
        abils.CHA = ab.CHA;     // Charisma

        firstName = name;

        Initialize();
    }

    const string Elf::race = "Elf";

    Elf::Elf(Ability ab, string name) {
        abils.STR = ab.STR;     // Strength
        abils.DEX = ab.DEX + 2; // Dexterity
        abils.CON = ab.CON;     // Constitution
        abils.INT = ab.INT;     // Intelligence
        abils.WIS = ab.WIS;     // Wisdom
        abils.CHA = ab.CHA;     // Charisma

        firstName = name;
        
        Initialize();
    }

    void Elf::Initialize() {
        NameGenerator ng(race);

        if(firstName.empty())
            firstName = ng.make_first();
        lastName = ng.make_last();
        
        // Standard character initialization
        curr_hp = 10;                   // TODO current hit points
        temp_hp = 0;                    // TODO temporary hit points
        max_hp = curr_hp;               // TODO maximum hit points
        prof = 2;                       // proficiency bonus
        level = 1;                      // character level total
        cur_exp = 0;                    // current experience
        max_exp = levels[level - 1];    // experience needed for next level

        // Race specific features
        // SRD V5.1 pg 4
        size = Medium;
        //speed = 30;
        vision.type = DarkVision;
        vision.radius = 60;
        skills.get(PRC)->setProfBonus(1);
        languages.push_back(Common);
        languages.push_back(Elvish);

        Character::Initialize();
    }

    HighElf::HighElf(Ability ab, string name) {
        abils.STR = ab.STR;     // Strength
        abils.DEX = ab.DEX + 2; // Dexterity
        abils.CON = ab.CON;     // Constitution
        abils.INT = ab.INT + 1; // Intelligence
        abils.WIS = ab.WIS;     // Wisdom
        abils.CHA = ab.CHA;     // Charisma

        firstName = name;

        Initialize();
    }

    // Halfling Race (SRD V5.1 pg 4)
    const string HalfLing::race = "Halfling";

    HalfLing::HalfLing(Ability ab, string name) {
        abils.STR = ab.STR;     // Strength
        abils.DEX = ab.DEX + 2; // Dexterity
        abils.CON = ab.CON;     // Constitution
        abils.INT = ab.INT;     // Intelligence
        abils.WIS = ab.WIS;     // Wisdom
        abils.CHA = ab.CHA;     // Charisma

        firstName = name;

        Initialize();
    }

    void HalfLing::Initialize() {
        NameGenerator ng(race);

        if(firstName.empty())
            firstName = ng.make_first();
        lastName = ng.make_last();
        
        // Standard character initialization
        curr_hp = 10;                   // TODO current hit points
        temp_hp = 0;                    // TODO temporary hit points
        max_hp = curr_hp;               // TODO maximum hit points
        prof = 2;                       // proficiency bonus
        level = 1;                      // character level total
        cur_exp = 0;                    // current experience
        max_exp = levels[level - 1];    // experience needed for next level

        // Race specific features
        // SRD V5.1 pg 4
        size = Small;
        //speed = 25;
        languages.push_back(Common);
        languages.push_back(Language::Halfling);

        Character::Initialize();
    }

    // Lightfoot Subrace (SRD V5.1 pg 5)
    Lightfoot::Lightfoot(Ability ab, string name) {
        abils.STR = ab.STR;     // Strength
        abils.DEX = ab.DEX + 2; // Dexterity
        abils.CON = ab.CON;     // Constitution
        abils.INT = ab.INT;     // Intelligence
        abils.WIS = ab.WIS;     // Wisdom
        abils.CHA = ab.CHA + 1;     // Charisma

        firstName = name;

        Initialize();
    }

    // TODO Dragonborn Race (SRD V5.1 pg 5)
    // TODO Gnome Race (SRD V5.1 pg 6)
    // TODO Rock Gnome Subrace (SRD V5.1 pg 6)
    // TODO Half-Elf Race (SRD V5.1 pg 6)
    // TODO Half-Orc Race (SRD V5.1 pg 7)
    // TODO Tiefling Race (SRD V5.1 pg 7)

    // TODO Find cleaner way to do this factory, things get entered in too many places!!!
    CharacterFactory::CharacterFactory() {
        // TODO populate race tree here and remove the above race vector
        head = allocate_node(Character::ID, false, NULL);
        
        race_node* human = allocate_node(Human::ID, true, head);
        
        race_node* dwarf = allocate_node(Dwarf::ID, true, head);
        race_node* hillDwarf = allocate_node(HillDwarf::ID, true, dwarf);
        
        race_node* elf = allocate_node(Elf::ID, true, head);
        race_node* highElf = allocate_node(HighElf::ID, true, elf);
        
        race_node* halfling = allocate_node(HalfLing::ID, true, head);
        race_node* lightfoot = allocate_node(Lightfoot::ID, true, halfling);

        dwarf->children = {
            hillDwarf
        };

        elf->children = {
            highElf
        };
        
        halfling->children = {
            lightfoot
        };

        head->children = {
            human,
            dwarf,
            elf,
            halfling
        };

        current = head;
    }

    CharacterFactory::~CharacterFactory() {
        //TODO clean up here
    }

    CharacterFactory::race_node* CharacterFactory::allocate_node(int raceID,
                                                                bool required,
                                                                race_node* parent) {
        race_node* node = new race_node;
            
        if(node == NULL) {
            printf("out of memory");
            exit(EXIT_FAILURE);
        }
        
        node->raceID = raceID;
        node->required = required;
        node->parent = parent;

        return node;
    }

    // TODO Combine these three functions??

    Character* CharacterFactory::NewCharacter(Ability ab, string name, int identifier) {
        if (identifier == -1)
            identifier = current->raceID;

        switch(identifier) {
        case Human::ID : {
            return new Human(ab, name);
        } break;
            
        case Dwarf::ID : {
            return new Dwarf(ab, name);
        } break;
    
        case HillDwarf::ID : {
            return new HillDwarf(ab, name);
        } break;
            
        case Elf::ID : {
            return new Elf(ab, name);
        } break;
            
        case HighElf::ID : {
            return new HighElf(ab, name);
        } break;

        case HalfLing::ID : {
            return new HalfLing(ab, name);
        } break;

        case Lightfoot::ID : {
            return new Lightfoot(ab, name);
        } break;

        default: {
            return NULL;
        }
        }
    }

    vector<string> CharacterFactory::current_options() {
        vector<string> ret;
        
        // TODO Maybe we can make this more automatic?
        // We already have race names in strings, could we use those?
        for(race_node* node : current->children) {
            switch(node->raceID) {
            case Human::ID : {
                ret.push_back("Human");
            } break;

            case Dwarf::ID : {
                ret.push_back("Dwarf");
            } break;
    
            case HillDwarf::ID : {
                ret.push_back("Hill Dwarf");
            } break;
        
            case Elf::ID : {
                ret.push_back("Elf");  
            } break;
        
            case HighElf::ID : {
                ret.push_back("High Elf");
            } break;

            case HalfLing::ID : {
                ret.push_back("Halfling");
            } break;

            case Lightfoot::ID : {
                ret.push_back("Lightfoot");
            } break;
            }
        }
        
        return ret;
    }

    bool CharacterFactory::has_options() {
        if(!current->children.empty())
            return true;
        else return false;
    }

    void CharacterFactory::select_option(int index) {
        if(current == NULL) return;

        if(index < 0 || (size_t)index > current->children.size())
            return;
        
        if(current->children[index] != NULL)
            current = current->children[index];
    }

    int CharacterFactory::current_id() {
        if(current != NULL) return current->raceID;
        return -1;
    }
}
