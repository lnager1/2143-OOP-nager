/*****************************************************************************
*                    
*  Author:           Lindsey
*  Email:            nager.lindsey@gmail.com
*  Label:            P03A
*  Title:            RPSLS
*  Course:           CMPS 2143-101
*  Semester:         Fall 2021
* 
*  Description:
*        This program allows for random generation of player hands to play against
*        each other in RPSLS
*  
*  Usage:
*        N/A
* 
*  Files:   
*       main.cpp    :   driver program
*****************************************************************************/

#include <iostream>
#include <functional> 
#include <map>
#include <random>
#include <string>
#include <ctime>

using namespace std;

#define ROCK u8"\U0000270A"
#define PAPER u8"\U0000270B"
#define SCISSORS u8"\U0001F44C"
#define LIZARD u8"\U0001F918"
#define SPOCK u8"\U0001F596"

#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"

struct Hands 
{
    const string rock = ROCK2;
    const string paper = PAPER2;
    const string scissors = SCISSORS2;
    const string lizard = LIZARD2;
    const string spock = SPOCK2;

    static map< string, string > Emojis;  // stl map
    //         name  , emoji

    static map< string, string > Names;  // stl map
    //         emoji  , name

    static string RandHand() 
    {
        auto it = Emojis.begin();  // iterator to front of map

        std::advance(it, rand() % Emojis.size());  // advance some random amnt
                                                   //   of steps

        string random_hand = it->second;  // grab emoji from map

        return random_hand;  // return rand emoji
    }

    static string Rock() 
    {
        return Emojis["rock"];
    }
    static string Paper() 
    {
        return Emojis["paper"];
    }
    static string Scissors() 
    {
        return Emojis["scissors"];
    }
    static string Lizard() 
    {
        return Emojis["lizard"];
    }
    static string Spock() 
    {
        return Emojis["spock"];
    }
};

// initialize static data member for
// hands struct (class)
map< string, string > Hands::Emojis = 
{
    {"rock", ROCK2},
    {"lizard", LIZARD2},
    {"spock", SPOCK2},
    {"scissors", SCISSORS2},
    {"paper", PAPER2}
};
// initialize static data member for
// hands struct (class)
map< string, string > Hands::Names = 
{
    {ROCK2, "rock"},
    {LIZARD2, "lizard"},
    {SPOCK2, "spock"},
    {SCISSORS2, "scissors"},
    {PAPER2, "paper"},
};

struct Player
{
    string weapon1;
    string weapon2;
    // other possible stuff

    /**
     * Constructor guarantees a player has two different "weapons"
     */
    Player()
    {
        weapon1 = Hands::RandHand();
        weapon2 = Hands::RandHand();

        while(weapon2==weapon1)
        {
            weapon2 = Hands::RandHand();
        }
    }
    /**
    * Public : operator/
    * 
    * Description:
    *      overloads the greater than operator to compare to player's hands
    * 
    * Params:
    *      Player other      :   player to be compared to original    
    *
    * Returns:
    *      bool       :   P1 wins return true, all other cases return false
    */
    bool operator> (Player other)
    {
        // True P1 wins
        // False P2 wins

        //convert emojis
        std::string p1weapon1 = Hands::Names[weapon1];
        std::string p1weapon2  = Hands::Names[weapon2];
        std::string p2weapon1  = Hands::Names[other.weapon1];
        std::string p2weapon2  = Hands::Names[other.weapon2];
        
        // Gets index of player 1's hand
        string hands[] = {"rock", "lizard", "spock", "scissors", "paper"};
		int index1 = -1;
        int index2 = -1;
		for(int i = 0; i < 5; i++)
        {
			if(hands[i] == p1weapon1)
            {
				index1 = i;
			}
            if(hands[i] == p1weapon2)
            {
				index2 = i;
			}
		}

        // True tie, both hands are equal
        if(p1weapon1 == p2weapon1 && p1weapon2 == p2weapon2)
        {
            return false;
        }
        // Hand 1 is tied, meaning test hand 2 for winner
        else if(p1weapon1 == p2weapon1)
        {
            // others weapon 2 = +1 on index OR others weapn1 = -2 on index
            if(p2weapon2 == hands[(index2+1) % 5] || p2weapon2 == hands[(index2+3) % 5])
            {
                //Return P1 wins
                return true;
            }
            else
            {
                // Return p2 wins
                return false;
            }
        }
        // test hand 1 for winner
        else 
        {
            // others weapon 1 = +1 on index OR others weapn1 = -2 on index
			if(p2weapon1 == hands[(index1+1) % 5] || p2weapon1 == hands[(index1+3) % 5])
            {
                //Return P1 wins
				return true;
			} 
            else
            {
                //Return P2 wins
				return false;
			}
		}
        
    }
};

/**
 * This class is used to test the random number generators by creating an
 * array with the same sides as some die. Then counting the values generated
 * between 1 and die size. There should be an equal number in every slot, which
 * for a 20 sided die is about .05 or 5 percent in each.
 * 
 */
class Tester 
{
    int* arr;
    int  size;

    public:
        Tester() : size{20} 
        {
            arr = new int[size + 1];
            initArr();
        }

        Tester(int size) : size{size} 
        {
            arr = new int[size + 1];
            initArr();
        }

        void initArr() 
        {
            for (int i = 0; i < size + 1; i++) 
            {
                arr[i] = 0;
            }
        }

        // add random value to distribution table
        void load(int i) 
        {
            arr[i]++;
        }

        // generate  the distribution table
        void distro(double res[], double total) 
        {
            for (int i = 0; i < size + 1; i++) 
            {
                res[i] = (double)arr[i] / total;
            }
        }
};

/**
 * DieRoll
 * @description: A class to implement roll playing dice rolls.
 * @methods:
 * private:
 *      int Random(Max) : returns a value between 0 and max.
 *      int Random(Min , Max) : returns a value between min and max
 *      void init(int , int)  : initialize class
 * public:
 *      DieRoll()
 *      DieRoll(int)
 *      DieRoll(int,int)
 *      void setDie(int)    : set sides
 *      int Roll(int,int)   :  NEEDS FIXING!!!!!!
 */
class DieRoll 
{
    int sides;

    int Random(int max)
    {
        return 1 + (rand() % max);
    }

    // min = 40 max = 100
    int Random(int min, int max) 
    {
        return 1 + min + (rand() % (max - min));
    }
    void init(int _seed, int _sides) 
    {
        sides = _sides;
        srand(_seed);
    }
public:
    DieRoll() 
    {
        //cout << "default base" << endl;
        init(time(0), 6);
    }
    DieRoll(int _seed) 
    {
        //cout << "overloaded const" << endl;
        init(_seed, 6);
    }
    DieRoll(int _seed, int _sides) 
    {
        //cout << "overloaded const" << endl;
        init(_seed, _sides);
    }

    void setDie(int _sides) 
    {
        sides = _sides;
    }

    // NEEDS FIXING!!!
    int Roll(int sides, int times) 
    {
        int sum = 0;
        while (times--) 
        {
            sum += Random(sides);
        }
        return sum;
    }
};

/**
 * RandRoll
 * @description: A random die roller using a "better" random
 *      number generator. Docs: https://www.cplusplus.com/reference/random/
 * 
 * @methods:
 *     int Roll(int)    : give the "sides" will return an 
 *     int between 1 and sides inclusive.
 * 
 */
class RandRoll 
{
    default_random_engine           generator;
    uniform_int_distribution< int > dieMap[21];

    public:
        /**
         * Constructor
         * 
         * @description: Create an stl array that has the common dice values
         *              loaded as uniform distribution types.
         * 
         *  Wasteful, as not every array location has a uniform distribution 
         *  associated with it. Could you make it less wasteful?
         */
        RandRoll()
        {
            dieMap[4] = uniform_int_distribution< int >(1, 4);
            dieMap[6] = uniform_int_distribution< int >(1, 6);
            dieMap[8] = uniform_int_distribution< int >(1, 8);
            dieMap[10] = uniform_int_distribution< int >(1, 10);
            dieMap[12] = uniform_int_distribution< int >(1, 12);
            dieMap[20] = uniform_int_distribution< int >(1, 20);
        }

        /**
         * Generate a random number depending on the "sides" of the dice.
         */
        int Roll(int sides) 
        {
            int diceRoll = dieMap[sides](generator);
            return diceRoll;
        };
};

/**
 * Rock Paper Scissors Lizard Spock
 * 
 * @description: A class to run the rock papers scissors game
 * 
 * Scissors cuts Paper
 * Paper covers Rock
 * Rock crushes Lizard
 * Lizard poisons Spock
 * Spock smashes Scissors
 * Scissors decapitates Lizard
 * Lizard eats Paper
 * Paper disproves Spock
 * Spock vaporizes Rock
 * Rock crushes Scissors
 */
class RPSLS : public DieRoll, public Hands 
{
    public:
        RPSLS(): DieRoll(time(0))
        {
            string h = RandHand();
            cout<<Names[h]<<": " <<h<<endl;
        };
        RPSLS(int seed) : DieRoll(seed) 
        {
            cout << "Rock: " << Rock() << endl;
        }
};

/**
* Public : winner
* 
* Description:
*      determines the winner between two players
* 
* Params:
*      Player p1    :   first player
*      Player p2    :   second player
*
* Returns:
*      no return type
*/
void winner(Player p1, Player p2)
{
    if(p1 > p2)
    {
        if(p1.weapon1 != p2.weapon1)
        {
            cout << "Player one's " << p1.weapon1 
            << " beat player two's " << p2.weapon1 << "\n\n";
        }
        else
        {
            cout << "Player one's " << p1.weapon2 
            << " beat player two's " << p2.weapon2 << "\n\n";
        }
    } 
    else if (p2 > p1)
    {
        if(p1.weapon1 != p2.weapon1)
        {
            cout << "Player two's " << p2.weapon1 
            << " beat player one's " << p1.weapon1 << "\n\n";
        }
        else
        {
            cout << "Player two's " << p2.weapon2 
            << " beat player one's " << p1.weapon2 << "\n\n";
        }
    } 
    else 
    {
        cout << "There was a tie \n\n";
    }
}

int main() 
{
    cout << "Testing my default emojis for Rock Paper Scissors Lizard Spock" << endl;
    cout << "==============================================================" << endl;
    cout << "Rock: " << ROCK2 << endl;
    cout << "Paper: " << PAPER2 << endl;
    cout << "Scissors: " << SCISSORS2 << endl;
    cout << "Lizard: " << LIZARD2 << endl;
    cout << "Spock: " << SPOCK2 << endl;

    cout << "\n\nTesting Random Number Generators" << endl;
    cout << "==============================================================" << endl;

    cout << "\nUsing Rand() builtin" << endl;
    cout << "====================" << endl;
    int     arr[21] = {0};
    double  res[21] = {0.0};
    int     total = 1000;
    DieRoll dr;
    Tester  Tdr;

    for (int i = 1; i <= total; i++) 
    {
        Tdr.load(dr.Roll(20, 1));
    }

    Tdr.distro(res, total);

    for (int i = 1; i < 21; i++) 
    {
        cout << res[i] << " ";
    }
    cout << endl;

    cout << "\nUsing <random> header" << endl;
    cout << "====================" << endl;
    int      arr2[21] = {0};
    double   res2[21] = {0.0};
    RandRoll r;
    Tester   Tdr2;

    for (int i = 1; i <= total; i++) 
    {
        Tdr2.load(r.Roll(20));
    }

    Tdr2.distro(res2, total);

    for (int i = 1; i < 21; i++) 
    {
        cout << res2[i] << " ";
    }
    cout << endl;

    cout << "\n\nTesting Hand Static class RandHand" << endl;
    cout << "==============================================================" << endl;
    static map< string, int > HandCount;
    string                    tempHand;
    for (int i = 1; i <= 100; i++) 
    {
        tempHand = Hands::RandHand();

        if (HandCount.find(tempHand) == HandCount.end()) 
        {
            HandCount[tempHand] = 0;
        }
        HandCount[tempHand]++;

        cout << tempHand << " ";

        if (i % 10 == 0) 
        {
            cout << endl;
        }
    }
    for (auto const& x : HandCount) 
    {
        std::cout << x.first  // string (key)
                  << " : "
                  << (double)x.second / 100.0  // string's value
        << std::endl;
    }

    cout << "\n\nHand Static class methods for emojis, and reverse lookup" << endl;
    cout << "====================================" << endl;
    cout << Hands::Rock() << endl;
    cout << Hands::Paper() << endl;
    cout << Hands::Scissors() << endl;
    cout << Hands::Lizard() << endl;
    cout << Hands::Spock() << endl;

    cout << Hands::Names[Hands::Rock()] << endl;
    cout << Hands::Names[Hands::Paper()] << endl;
    cout << Hands::Names[Hands::Scissors()] << endl;
    cout << Hands::Names[Hands::Lizard()] << endl;
    cout << Hands::Names[Hands::Spock()] << endl;

    cout << "\n\nRock Paper Scissors Lizard Spock Class" << endl;
    cout << "====================================" << endl;

    RPSLS rps1(36353);
    RPSLS rps2;

    cout << "\n\nGenerate Two Unique Pairs. " << endl;
    cout << "====================================" << endl;

    string h1 = Hands::RandHand();
    string h2 = Hands::RandHand();

    while(h2==h1)
    {
      h2 = Hands::RandHand();
    }

    string h3 = Hands::RandHand();
    string h4 = Hands::RandHand();

    while(h4==h3)
    {
      h4 = Hands::RandHand();
    }

    cout<<h1<<"+"<<h2<<" vs "
        <<h3<<"+"<<h4<<endl;

    std::cout << "\n\nTest Cases\n";

    // Loops through and creates two new player instances
    for(int i = 0; i < 25; i++)
    {
        Player useP1;
        Player useP2;

        // Prints random values generated
        std::cout << useP1.weapon1 << "+" << useP1.weapon2 << " v.s " 
            << useP2.weapon1 << "+" << useP2.weapon2 << '\t';

        // Determines winner
        winner(useP1, useP2);
    }
    return 0;
}