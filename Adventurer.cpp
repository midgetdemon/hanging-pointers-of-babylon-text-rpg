#include <iostream>
#include <string>
#include "Adventurer.hpp" 

Adventurer::Adventurer(std::string name, std::string description, int maxHealth, int physAtk, int physDef, int magAtk, int magDef, int speed) 
    : Entity(name, description, maxHealth, physAtk, physDef, magAtk, magDef, speed){ 
        level = 1;
        experience = 0;
    }

void Adventurer::levelUp(){
	setLevel(getLevel()+1); 	
}

void Adventurer::setLevel(int l){
	level = l; 
}
	
int Adventurer::getLevel() const {
	return level;
}

/**addItem: adds an item to the player's inventory.
 * args: the item to be added
 * outputs: none
 * */
void Adventurer::addItem(Item* item){
    inventory.push_back(item);
}

/**turn: This method is called when this adventurer takes a turn in combat.
 * args: enemies (vector of valid enemy targets)
 * outputs: none
 * */
void Adventurer::turn(std::vector<Enemy*> enemies){
    InputReader reader;
    std::cout << "It's your turn. Available options:\n"
              << "1:\tAttack\n"
              << "2:\tInspect\n"
              << "3:\tUse Item\n"
              << "4:\tFlee\n";

    int inputChoices[]{1, 2, 3, 4};
    int selection = 0;

    //turn only proceeds when the player chooses to attack or flee. Successfully using an item sets the selection flag to 1 as well
    while (selection != 1 && selection != 4){ 
        selection = reader.readInput(inputChoices, 4);
        
        switch(selection){
            /*************************** ATTACK ***************************/
            case 1:{ 
                // prompt the user for target selection
                std::cout << "Choose a target.\n";

                int enemyChoices[enemies.size()];
                int targetIndex = 1;
                int enemySelection = 0;
                for (auto e : enemies){
                    std::cout << targetIndex << ":\t" << e->getName() <<"\n";
                    enemyChoices[targetIndex - 1] = targetIndex;
                    targetIndex++;
                }
                enemySelection = reader.readInput(enemyChoices, enemies.size());

                // execute the action
                attack(enemies[enemySelection - 1]);
            } break;
            /*************************** INSPECT ***************************/
            case 2:{ //inspect
                // prompt the user for target selection
                std::cout << "Choose a target.\n";

                int enemyChoices[enemies.size()];
                int targetIndex = 1;
                int enemySelection = 0;
                for (auto e : enemies){
                    std::cout << targetIndex << ":\t" << e->getName() <<"\n";
                    enemyChoices[targetIndex - 1] = targetIndex;
                    targetIndex++;
                }
                enemySelection = reader.readInput(enemyChoices, enemies.size());

                // execute the action
                enemies[enemySelection - 1]->inspect();
            } break;
            /*************************** ITEM ***************************/
            case 3:{ //use item
                std::cout << "item used\n";
            } break;
            /*************************** FLEE ***************************/
            case 4:{ //flee
                std::cout << "flee used\n";
            } break;
        }
    }
}

/**attack: Generic attack method. Only the player can use this.
 * Deals 100% physical attack in damage. Prints a short message.
 * args: the target of the attack
 * outputs: none
 * */
void Adventurer::attack(Enemy* target){
    std::cout << name << " strikes the " << target->getName() << " with their bare fists, dealing " << target->dealPDamage(physAtk) << " physical damage.\n";
}