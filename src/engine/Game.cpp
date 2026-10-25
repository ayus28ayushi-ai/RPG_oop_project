#include "Game.h"
#include <cstdlib>
#include <ctime>

int calcNormalDamage(int atk, int def) {
    int dmg=atk-def;
    return (dmg<1)?1:dmg;
}

int calcCritDamage(int atk, int def) {
    int dmg=(atk-def)*2;
    return (dmg<1)?1:dmg;
}

using DamageFunc = int(*)(int, int);

Game::Game()
    : dungeon_(6),
      currentRoom_(0),
      previousRoom_(0),
      turnCount_(0)
{
    dungeon_.buildDefault();
}

void Game::run(){

    std::cout<<"So you have accepted my challenge...";
    std::string hero_name;
    std::cout<<"Enter your name to continue: ";
    std::cin>> hero_name;
    hero_ = Hero(hero_name);
    std::cout<<"Welcome "<<hero_name<<" to the Dungeon!"<<std::endl;
    std::cout<<"You stand in the entrance hall\nCurrent room: "<<dungeon_[currentRoom_];
    srand(time(nullptr)); // fixed: seed random for crit/flee

    bool isRunning_=true;
    while(isRunning_){

        std::cout<< "\n========================================\n"
                 <<"Options:\n"
                 <<"1. Look around\n"
                 <<"2. Move\n"
                 <<"3. Fight\n"
                 <<"4. Inventory\n"
                 <<"5. Equip weapon\n"
                 <<"6. Use potion\n"
                 <<"7. Pick up loot\n"
                 <<"8. Hero status\n"
                 <<"9. Quit\n"
                 << "\n========================================\n";
        
        int choice;
        std::cout<<"Enter your choice: ";
        std::cin>>choice;
        if(std::cin.fail()||choice<1||choice>9){ // fixed: safe input (letters/bad numbers)
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            std::cout<<"Invalid entry"<<std::endl;
            continue;
        }
        else{
            ++turnCount_; // fixed: count every valid action
            std::cout<<"\n\n"<<std::endl;
            switch(choice){

                case 1:{
                    std::cout<<dungeon_[currentRoom_]<<std::endl;
                    break;
                }
                
                case 2:{
                    std::cout<<"\nTo move\n"
                            <<"North - enter 0\n"
                            <<"East - enter 1\n"
                            <<"South - enter 2\n"
                            <<"West - enter 3\n";
                    int dir;
                    bool chk=false;
                    while(!chk){
                        std::cout<<"Enter your choice: ";
                        std::cin>>dir;
                        if(std::cin.fail()||dir<0||dir>3){ // fixed: safe input
                            std::cin.clear();
                            std::cin.ignore(10000,'\n');
                            std::cout<<"Invalid input, out of bounds.\n";
                            continue;
                        }
                        else{
                            int nextRoom_ = dungeon_[currentRoom_].exit(dir);
                            if(nextRoom_ == -1){
                                std::cout<<"There is no exit in that direction.\nPlease choose a different direction.\n";
                                continue;
                            }
                            else{
                                chk=true;
                                previousRoom_=currentRoom_;
                                currentRoom_=nextRoom_;
                                std::cout << "\nYou moved to a new room!\n";
                                std::cout << dungeon_[currentRoom_] << std::endl;
                            }
                        }
                    }
                    break;
                }
                
                case 3:{
                    if(!dungeon_[currentRoom_].hasLiveMonster()) std::cout<<"No monster in the room."<<std::endl;
                    else{
                        bool inCombat_=true;
                        std::cout<<"-Fight Started-"<<std::endl;
                        Monster& mon = const_cast<Monster&>(dungeon_[currentRoom_].monster()); // fixed: monster() returns const
                        while(hero_.isAlive()&&mon.isAlive()&&inCombat_){
                            int action;
                            std::cout<<"Actions:\n"
                                     <<"0 - Attack\n"
                                     <<"1 - Heal\n"
                                     <<"2 - Flee\n"
                                     <<"Enter your action: ";
                            std::cin>>action;
                            if(std::cin.fail()||action<0||action>2){ // fixed: safe input
                                std::cin.clear();
                                std::cin.ignore(10000,'\n');
                                std::cout<<"Input out of bounds."<<std::endl;
                            }
                            else{
                                switch(action){
                                    case 0:{

                                        DamageFunc damageFn = calcNormalDamage;
                                        if ((rand()%100) < 20) {
                                            damageFn = calcCritDamage;
                                            std::cout<<"CRITICAL HIT!"<<std::endl;
                                        }
                                        int heroDmg = damageFn(hero_.attackPower(), mon.stats().defense());
                                        mon.takeDamage(heroDmg);
                                        std::cout<<"You hit "<<mon.name()<<" for "<<heroDmg<<" damage."<<std::endl;

                                        if (!mon.isAlive()) {
                                            std::cout << "You defeated " << mon.name() << "!\n";
                                            mon.markDefeated();
                                            hero_.gainXp(mon.xpReward());
                                            hero_.pickUp(mon.loot());

                                            if (currentRoom_ == 5) {
                                                std::cout << "\n=========================================\n"
                                                          << "  VICTORY! You defeated the Dragon!\n"
                                                          << "  Turns taken: " << turnCount_ << "\n" // fixed: show turns
                                                          << "  Monsters defeated: " << Monster::defeated() << "\n" // fixed: show defeated
                                                          << "========================================="<<std::endl;
                                                inCombat_ = false;
                                                isRunning_ = false;
                                            }
                                            break;
                                        }

                                        int monsterDmg = calcNormalDamage(mon.stats().attack(), hero_.stats().defense());
                                        hero_.takeDamage(monsterDmg);
                                        std::cout<<mon.name()<<" struck back for "<<monsterDmg<<" damage.";

                                        if (!hero_.isAlive()) {
                                            std::cout<<"\n=========================================\n"
                                                    <<"  GAME OVER! You perished in battle...\n" // fixed: typo
                                                    <<"========================================="<<std::endl;
                                            inCombat_ = false;
                                            isRunning_ = false;
                                            break;
                                        }
                                        break;
                                    }
                                    case 1:{
                                        if(hero_.usePotion()){ // fixed: respect return value
                                            std::cout<<"Potion used. Current HP: "<<hero_.stats().hp()<<"/"<<hero_.stats().maxHp()<<std::endl;
                                        }else{
                                            std::cout<<"No potions available."<<std::endl;
                                        }

                                        int monsterDmg = calcNormalDamage(mon.stats().attack(), hero_.stats().defense());
                                        hero_.takeDamage(monsterDmg);
                                        std::cout<<mon.name()<<" attacked you for "<<monsterDmg<<" damage while you drank!"<<std::endl;

                                        if (!hero_.isAlive()) {
                                            std::cout << "\n=========================================\n";
                                            std::cout << "  GAME OVER! You perished in battle...\n"; // fixed: typo
                                            std::cout << "=========================================\n";
                                            isRunning_ = false;
                                            inCombat_ = false;
                                            break;
                                        }
                                        break;
                                    }
                                    case 2:{
                                        if ((rand() % 100) < 50) {
                                            std::cout<<"You successfully fled back to the previous room!"<<std::endl;
                                            currentRoom_ = previousRoom_;
                                            inCombat_= false;
                                            break;
                                        } 

                                        std::cout<<"Escape failed! "<<mon.name()<<" blocked your exit!"<<std::endl;

                                        int monsterDmg = calcNormalDamage(mon.stats().attack(), hero_.stats().defense());
                                        hero_.takeDamage(monsterDmg);
                                        std::cout<<mon.name()<<" hit you for "<<monsterDmg<<" damage!"<<std::endl;

                                        if (!hero_.isAlive()) {
                                            std::cout << "\n=========================================\n";
                                            std::cout << "  GAME OVER! You perished in battle...\n"; // fixed: typo
                                            std::cout << "=========================================\n";
                                            isRunning_ = false;
                                            inCombat_= false;
                                            break;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    break;
                }

                
                case 4:{
                    std::cout<<"--------Hero Inventory---------"<<std::endl;
                    std::cout<<hero_.bag()<<std::endl;
                    break;
                }
                

                case 5:{

                    std::cout<<"--------Hero Inventory---------"<<std::endl;
                    std::cout<<hero_.bag()<<std::endl;

                    Inventory tempBag = hero_.bag(); // fixed: copy BEFORE equip so name stays valid
                    int wep;
                    std::cout<<"Enter slot number: ";
                    std::cin>>wep;
                    if(std::cin.fail()){ // fixed: safe input
                        std::cin.clear();
                        std::cin.ignore(10000,'\n');
                        std::cout<<"Invalid entry"<<std::endl;
                        break;
                    }

                    if(hero_.equip(wep)){
                        std::cout << "Weapon wielded: " << tempBag[wep].name() << std::endl;
                    }
                    else std::cout<<"Slot out of bounds or item not a weapon."<<std::endl;
                    break;
                }

                case 6:{
                    if(hero_.usePotion()){
                        std::cout<<"Potion used. Hero healed."<<std::endl;
                        std::cout<<"Updated HP: "<<hero_.stats().hp()<<"/"<<hero_.stats().maxHp()<<std::endl;
                    }
                    else{
                        std::cout<<"No potions available."<<std::endl;
                    }
                    break;
                }
               
                case 7:{
                    if(dungeon_[currentRoom_].hasLoot()){
                        if(hero_.bag().isFull()){
                            std::cout<<"Inventory is full. Cannot pick up more items."<<std::endl;
                        }
                        else{
                            Item lootItem = dungeon_[currentRoom_].takeLoot();
                            hero_.pickUp(lootItem);
                            std::cout << "You picked up: " << lootItem.name() << "."<<std::endl;
                        }

                    }
                    else std::cout<<"There is nothing to pick up."<<std::endl;
                    break;
                }


                case 8:{
                    std::cout<<"---------Hero Status---------"<<std::endl;
                    std::cout<<hero_<<std::endl;
                    break;
                }

                case 9:
                std::cout<<"You have quit"<<std::endl;
                isRunning_=false;
                break;

            }
        }
    }
}