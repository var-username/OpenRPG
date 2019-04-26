
/*
character-generator - race.h
Created on: Apr 29, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_RACE_H_
#define SRC_RACE_H_

#include "character.h"

namespace ORPG {
    class Human : public Character {
    private:
        typedef Character super;

    protected:
        void Initialize();

    public:
        Human(Ability ab = ability_struct(), std::string name = "");

        static const int ID = 0x0001;
        static const std::string race;
    };

    class Dwarf : public Character {
    private:
        typedef Character super;
        
    protected:
        void Initialize();

    public:
        Dwarf(Ability ab = ability_struct(), string name = "");

        static const int ID = 0x0010;
        static const std::string race;
    };

    class HillDwarf : public Dwarf {
    private:
        typedef Dwarf super;
    public:
        HillDwarf(Ability ab = ability_struct(), string name = "");

        static const int ID = 0x0011;
    };

    class Elf : public Character {
    protected:
        void Initialize();

    public:
        Elf(Ability ab = ability_struct(), string name = "");

        static const int ID = 0x0020;
        static const std::string race;
    };

    class HighElf : public Elf {
    public:
        HighElf(Ability ab = ability_struct(), string name = "");

        static const int ID = 0x0021;
    };

    class HalfLing : public Character {
    protected:
        void Initialize();

    public:
        HalfLing(Ability ab = ability_struct(), string name = "");

        static const int ID = 0x0030;
        static const std::string race;    
    };

    class Lightfoot : public HalfLing {
    public: 
        Lightfoot(Ability ab = ability_struct(), string name = "");
        
        static const int ID = 0x0031;
    };

    class Dragonborn : public Character {
    protected:
        void Initialize();
    
    public:
        Dragonborn(Ability ab = ability_struct(), string name = "");

        static const int ID = 0x0040;
        static const std::string race;
    };

    class Gnome : public Character {
    protected:
        void Initialize();
    
    public:
        Gnome(Ability ab = ability_struct(), string name = "");
        
        static const int ID = 0x0050;
        static const std::string race;
    };

    class RockGnome : public Gnome {
    public:
        RockGnome(Ability ab = ability_struct(), string name = "");

        static const int ID = 0x0051;
    };

    class HalfElf : public Character {
    protected:
        void Initialize();
    
    public:
        HalfElf(Ability ab = ability_struct(), string name = "");

        static const int ID = 0x0060;
        static const std::string race;
    };

    class HalfOrc : public Character {
    protected:
        void Initialize();
    
    public:
        HalfOrc(Ability ab = ability_struct(), string name = "");

        static const int ID = 0x0070;
        static const std::string race;
    };

    class Tiefling : public Character {
    protected:
        void Initialize();
    
    public:
        Tiefling(Ability ab = ability_struct(), string name = "");

        static const int ID = 0x0080;
        static const std::string race;
    };

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

        Character* NewCharacter(Ability ab = ability_struct(), std::string name = "", int identifier = -1);

        void reset() { current = head; };
        std::vector<std::string> current_options();
        bool has_options();
        void select_option(int index);
        int current_id();
    };
}

#endif /* SRC_RACE_H_ */
