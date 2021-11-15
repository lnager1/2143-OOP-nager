/*

1) Dice (Rolls multiple die, need diffrent modes for final result)
-> modes: Standard, Average, Bestof, addition, subtraction

2) Weapon class (generated using a config file)
- attackValue
Fists & Feet (1.d.4 OR 1.d.6)
Sword (1.d.12 OR 2.d.6 OR 3.d.4)
Bow (1.d.8 OR 2.d.4 OR 1.d.10)
Magic Spell (1.d.20 OR 2.d.10 OR 3.d.6 OR 5.d.4)
Magic Weapon (Add 1.d.4 OR 1.d.6 to primary weapon)
Fire Weapon (Add 1.d.6 OR 1.d.8 to primary weapon)

3) Attacker(s) are bad guys (how many and what kind are generated from a file)
Attackers are their own class having
-hitPoints (How many points until expiration)
-attackStrength (Points damage against who they are fighting)
-recoveryStrength (regains x number of hit points per round)

4) Defender(s) are good guys (made dependng on how many attackers there are)
BaseFighter is our parents of both:
-Name : string
-HP : Health points (random from 3 - 8)
-RR : Regeneration Rate (random from .15 - .75)
-PW : Primary Weapon = Fists and Feet
Subclasses of BaseFighter:
Warrior (uses sword)
Wizard (uses magic)
Archer (uses bow)
Elf: (uses magic + sword)
DragonBorn: (uses bow + fire)

5) Main logic rules:
Attacking force (bad guys) is any size
Defending force (good guys) 1 of each character type for every 100 attackers
Attacking force heals only in battle
Defending Force can heal any time
Characters die at 0 hp duh
Defending force can swap out characters in the middle of battle when it is their turn to attack. This will be used in place of an attack.
Game ends when one of the two queues (attackers or defenders) is empty

6) Need to print running commentary to std::out describing what is happening
Example: 
Wizard Attacks Dragonborn for 13 damage (dragon has 0 hp remaining)
DragonBorn Born has perished.
Defenders send out Wizard

Output notes:
Enemies are controled by a bad guy named "Captain Base"
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <queue>
#include <stdlib.h>
#include <cmath>

class Die 
{
	int sides;
public:
	//Both allows for passing in and default construction
	Die(int sidesIn = 6)
    {
		sides = sidesIn;
	}
	int roll(int rolls = 1) 
    {
			int sum = 0;
			while(rolls--)
            {
				sum += (std::rand() % sides) + 1;
			}
			return sum;
	};

	friend std::ostream& operator<<(std::ostream &os, const Die& d)
    {
			return os << "[" << d.sides << "]";
	}
};

/*Specified that it needed to be able to Standard, Average, Bestof, addition, subtraction on a single set type of dice
Options are:
Letter at the start denoting
-> Average (a)
-> Best of (b)
-> Standard ()

and number, d then number for number of dice then number of faces
XdX

lastly plus followed by a number
+X

Example string = "b12d6+16"

So Mode-Dice-Addition
*/
class Dice
{
	public:
    std::string setString;

	Dice(std::string diceString = "1d6")
    {
		setString = diceString;
	}
	int roll()
    {
		int index = 0;
		char mode = 's';
		//check if non-standard mode
		if(setString[0] == 'a' || setString[0] == 'b')
        {
			mode = setString[0];
			index = 1;
		}
		//grab dice
		std::string count = "0", sides = "0", base = "0";
		while(setString[index] != 'd' && index < setString.size())
        {
			count += setString[index];
			index++;
		}
		index++;
		while(setString[index] != '+' && index < setString.size())
        {
			sides += setString[index];
			index++;
		}
		index++;
		while(index < setString.size())
        {
			base += setString[index];
			index++;
		}
		if(mode == 'a')
        {
			return average(std::stoi(count), std::stoi(sides), std::stoi(base));
		} 
        else if(mode == 'b')
        {
			return bestOf(std::stoi(count), std::stoi(sides), std::stoi(base));
		} 
        else 
        {
			return standard(std::stoi(count), std::stoi(sides), std::stoi(base));
		}
	}

	int standard(int count,int sides,int base)
    {
		int result = 0;
		for(int i = 0; i < count; i++)
        {
			result += (std::rand() % sides) + 1;
		}
		return result + base;
	}
	int average(int count,int sides,int base)
    {
		int result = 0;
		for(int i = 0; i < count; i++)
        {
			result += (std::rand() % sides) + 1;
		}
		return (result / count) + base;
	}
	int bestOf(int count,int sides,int base)
    {
		int result = 0;
		for(int i = 0; i < count; i++)
        {
			int dieRoll = (std::rand() % sides) + 1;
			if(result < dieRoll)
            { 
				result = dieRoll;
			}
		}
		return result + base;
	}
    // Adds two dice together
    const Dice operator+(Dice rhs)
    {
        std::string newDiceString;
        Dice returnVal;
        std::string constant;

        // If already has a plus constant
        if(setString.find('+') != std::string::npos)
        {
            int constant = stoi(setString.substr(setString.find('+'), std::string::npos));
            std::string sWithouta = setString.substr(0, setString.find('+'));
            returnVal = Dice(sWithouta + "+" + std::to_string(rhs.roll() + constant));
            return returnVal;
        }
        // If doesn't have a plus constant 
        else
        {
            newDiceString = setString + "+" + std::to_string(rhs.roll());

            returnVal = Dice(newDiceString);
            return returnVal;
        }
    }
};

// Creates Base class for weapon and generates base value "fists and feet"
class Weapon
{
    public:
        Weapon()
        {
            // Random dice values
            int useRand = rand()%2;

            if(useRand)
            {
                attackValue = Dice("1d6");
            }
            else
            {
                attackValue = Dice("1d4");
            }
        }
    
    Dice attackValue;
};

// Creates weapon type that inheirits virtually from weapon
class Sword : virtual public Weapon
{
    public:
        Sword()
        {
            int useRand = rand()%3;
            
            if(useRand == 2)
            {
                attackValue = Dice("3d4");
            }
            else if(useRand == 1)
            {
                attackValue = Dice("2d6");
            }
            else
            {
                attackValue = Dice("1d12");
            }
        }
    
};

// Creates weapon type that inheirits virtually from weapon
class Bow : virtual public Weapon
{
    public:
        Bow()
        {
            int useRand = rand()%3;
            
            if(useRand == 2)
            {
                attackValue = Dice("1d8");
            }
            else if(useRand == 1)
            {
                attackValue = Dice("2d4");
            }
            else
            {
                attackValue = Dice("1d10");
            }
        }
    
};

// Creates weapon type that inheirits virtually from weapon
class MagicSpell : virtual public Weapon
{
    public:
        MagicSpell()
        {
            int useRand = rand()%4;
            
            if(useRand == 3)
            {
                attackValue = Dice("1d20");
            }
            else if(useRand == 2)
            {
                attackValue = Dice("2d10");
            }
            else if(useRand == 1)
            {
                attackValue = Dice("3d6");
            }
            else
            {
                attackValue = Dice("5d4");
            }
        }
};

// Creates weapon type that inheirits virtually from weapon
class MagicWeapon : virtual public Weapon
{
    public:
        MagicWeapon()
        {
            int useRand = rand()%2;

            if(useRand)
            {
                attackValue = Dice("1d6");
            }
            else
            {
                attackValue = Dice("1d4");
            }
        }
};

// Creates weapon type that inheirits virtually from weapon
class FireWeapon : virtual public Weapon 
{
    public:
        FireWeapon()
        {
            int useRand = rand()%2;

            if(useRand)
            {
                attackValue = Dice("1d6");
            }
            else
            {
                attackValue = Dice("1d8");
            }
        }
};

// Creates weapon type that inheirits virtually from weapon and weapon type
class MagicSword : virtual public Sword, virtual public MagicWeapon
{
     public:
        MagicSword()
        {
            // Diamond inheritance is ugly
            Weapon::attackValue = Sword::attackValue + MagicWeapon::attackValue;
        }
};

// Creates weapon type that inheirits virtually from weapon and weapon type
class FireSword : virtual public Sword, virtual public FireWeapon
{
     public:
        FireSword()
        {
            // Diamond inheritance is ugly
            Weapon::attackValue = Sword::attackValue + FireWeapon::attackValue;
        }
};

// Creates weapon type that inheirits virtually from weapon and weapon type
class MagicBow : virtual public Bow, virtual public MagicWeapon
{
     public:
        MagicBow()
        {
            // Diamond inheritance is ugly
            Weapon::attackValue = Bow::attackValue + MagicWeapon::attackValue;
        }
};

// Creates weapon type that inheirits virtually from weapon and weapon type
class FireBow : virtual public Bow, virtual public FireWeapon
{ 
     public:
        FireBow()
        {
            // Diamond inheritance is ugly
            Weapon::attackValue = Bow::attackValue + FireWeapon::attackValue;
        }
};

// Creates base character type
class Character
{
    public:
        Character()
        {
            // Base stats on every character
            health = rand()%5 + 3;
            regenRate = (rand()%60 + 15)/100;
        }

        double health;
        double regenRate;

        Weapon useWeapon;

        std::string name;
};

// Assigns name and weapon to specified character type
class Warrior : public Character
{
    public:
        Warrior()
        {
            useWeapon = Sword();
            name = "Warrior";
        }
};

// Assigns name and weapon to specified character type
class Wizard : public Character
{
    public:
        Wizard()
        {
            useWeapon = MagicSpell();
            name = "Wizard";
        }
};

// Assigns name and weapon to specified character type
class Archer : public Character
{
    public:
        Archer()
        {
            useWeapon = Bow();
            name = "Archer";
        }
};

// Assigns name and weapon to specified character type
class Elf : public Character
{
    public:
        Elf()
        {
            useWeapon = MagicSword();
            name = "Elf";
        }
};

// Assigns name and weapon to specified character type
class DragonBorn : public Character
{
    public:
        DragonBorn()
        {
            useWeapon = FireBow();
            name = "Dragon Born";
        }
};

// Class that does game structure
class Game
{
    public:
    // Attackers in queue
    std::queue<Character> attackers;

    // Defenders in vector because you are constantly searching and not pulling from front
    std::vector<Character> defenders;

    //Fills containers and runs game
    Game(std::string fileName)
    {
        fillAttackers(fileName);
        fillDefenders();
        runGame();
    }
    //Fills containers from file
    void fillAttackers(std::string fileName)
    {
        std::ifstream fin;
        fin.open(fileName);

        while(!fin.eof())
        {
            std::string characterType;
            fin >> characterType;

            if(characterType == "warrior")
            {
                attackers.push(Warrior());
            }
            else if(characterType == "wizard")
            {
                attackers.push(Wizard());
            }
            else if(characterType == "archer")
            {
                attackers.push(Archer());
            }
            else if(characterType == "elf")
            {
                attackers.push(Elf());
            }
            else
            {
                attackers.push(DragonBorn());
            }
        }
    }
    // Fills defenders with appropriate number based on attackers
    void fillDefenders()
    {
        for(int i = 0; i < std::ceil(attackers.size()/100.0); i++)
        {
            defenders.push_back(Warrior());
            defenders.push_back(Wizard());
            defenders.push_back(Archer());
            defenders.push_back(Elf());
            defenders.push_back(DragonBorn());
        }
    }

    //  Finds defender that matches attacker name
    int findDefender(std::string nameToFind, int start = 0)
    {
        for(int i = start; i < defenders.size(); i++)
        {
            if(defenders[i].name == nameToFind)
            {
                return i;
            }
        }
        if(defenders.size())
        {
            return defenders.size()-1;
        }
        else
        {
            return 0;
        }
    }

    // Runs game
    void runGame()
    {
        Character* attacker;
        Character* defender;

        int defendersLost = 0;
        int attatckersLost = 0;
        int totalAttacks = 0;
        int numRounds = 0;
        int numDef = defenders.size();
        int numAtc = attackers.size();
        
        //this needs to be outside the loop so that it persists between runs
        attacker = &(attackers.front());

        int index = findDefender((*attacker).name);
        defender = &(defenders[index]);
        
        while(!attackers.empty() && !defenders.empty())
        {
            int damageDealtDef;
            int damageDealtAtc;

            // Damage dealt to defenders
            damageDealtDef = (*attacker).useWeapon.attackValue.roll();
            

            // Attackers attack first
            (*defender).health -= damageDealtDef;
            std::cout << "Attacking " << (*attacker).name << " attacks defending " << (*defender).name << " for " << damageDealtDef << ".\n";
            
            if((*defender).health <= 0)
            {
                std::cout << "Defending " << (*defender).name << " has died.\n";
                defenders.erase(defenders.begin() + index);
                defendersLost++;

                index = findDefender((*attacker).name);
                if(defenders.size()){
                    defender = &(defenders[index]);
                }
            }

            // Swap at 5 or less health else attack
            if(defenders.size() && (*defender).health <= 4)
            {
                std::cout << "Defending " << (*defender).name << " swaps out\n";
                index = findDefender((*attacker).name, index + 1);
                defender = &(defenders[index]);
            }
            else if (defenders.size())
            {
                damageDealtAtc = (*defender).useWeapon.attackValue.roll();
                (*attacker).health -= damageDealtAtc;
                std::cout << "Defending " << (*defender).name << " attacks " << (*attacker).name << " for " << damageDealtAtc << ".\n";
            }

            // Check for death
            if((*attacker).health <= 0)
            {
                std::cout << "Attacker " << (*attacker).name << " has died.\n";
                attackers.pop();
                attatckersLost++;
            }

            // Regen
            if(attackers.size()){
                (*attacker).health += (*attacker).regenRate;
            }

            for(int j = 0; j < defenders.size(); j++)
            {
                defenders[j].health += defenders[j].regenRate;
            }
            numRounds++;
        }

        // Prints stats
        if(attackers.empty())
        {
            std::cout << "\n\nDefenders Win\n";
        }
        else
        {
            std::cout << "\n\nAttackers win\n";
        }

        std::cout << "Number of Attackers: " << numAtc << std::endl;
        std::cout << "Number of Defenders: " << numDef << std::endl;
        std::cout << "Number of Rounds: " << numRounds << std::endl;
        std::cout << "Pecentage won by Attackers: " <<  (double)defendersLost/numRounds*100 << "%\n";
        std::cout << "Percentage won by Defenders: " << (double)attatckersLost/numRounds*100 << "%\n";
    } 
};

int main()
{
	std::srand (time(NULL));
	Game("input.dat");

    return 0;
}