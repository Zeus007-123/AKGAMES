/****************************************************************************************************************

Player Special Abilities:

Critical Hit   : unlocks after level 2 : Deals one more damage of same amount, total 2x damage
Blocker        : unlocks after level 3 : 0 damage on enemy hit
Life Steal     : unlocks after level 4 : after dealing damage, recovers a HP of same as that of that damage variable.
Ranged Attack  : unlocks after level 5 : Deals additional damage of 0.5x damage and takes 0 damage on next enemy hit.

Player Stats
Level 1 : HP = 100, meleeDamage = 25, rangedDamage = 45, minHeal = 30, maxHeal = 45, minDef = 05, maxDef = 15
Level 2 : HP = 200, meleeDamage = 30, rangedDamage = 50, minHeal = 32, maxHeal = 50, minDef = 08, maxDef = 20
Level 3 : HP = 300, meleeDamage = 35, rangedDamage = 55, minHeal = 34, maxHeal = 55, minDef = 11, maxDef = 25
Level 4 : HP = 400, meleeDamage = 40, rangedDamage = 60, minHeal = 36, maxHeal = 60, minDef = 14, maxDef = 30
Level 5 : HP = 500, meleeDamage = 45, rangedDamage = 65, minHeal = 38, maxHeal = 65, minDef = 17, maxDef = 35
Level 6 : HP = 600, meleeDamage = 50, rangedDamage = 70, minHeal = 40, maxHeal = 70, minDef = 20, maxDef = 40

i.e HP+=100, minDamage+=5, maxDamage+=5, minHeal += 2, maxHeal+=5, minDef=3, maxDef+=5

Goblin    : HP = 200 , 20-35 , 6-24
Troll     : HP = 500 , 35-50 , 15-35
Murlocs   : HP = 1000, 40-70 , 15-40

Special Abilities of Murlocs:

Summon minion  : summons a Minion of 150 HP. We have to destroy him to be able to touch Murlocs.
Healing Elixir : Heals 100 HP.
Hypnotize      : Player hits himself with same damage that the player used

******************************************************************************************************************/

#include <iostream>
#include <ctime>
#include <string.h>
#include <iomanip>
using namespace std;

enum PlayerState{  // some player states 
dead,
alive,
hypnotising=1000,
healthdrain=2000
};

class Player 
{

  private:
  int health;
  int fullhealth;
  int meleeDamage;
  int rangedDamage;
  int minHeal; // Healing split into minimum healing and maximum healing
  int maxHeal;
  int minDef; // Defence split into minimum defence and maximum defence
  int maxDef;
  int level;
  string name;

// Special Abilities of Player split into following
  bool criticalHit = false;
  bool blocker = false;
  bool lifeSteal = false;
  bool rangedAttack = false;

  bool block = false;
  bool hypnotise = false;

  public:
  Player(int _level, int _health, int full_health, int melee_Damage, int ranged_Damage, int min_Heal, int max_Heal, int min_Def, int max_Def, string _name) 
  { 
    level = _level;
    health = _health;
    fullhealth = full_health;
    meleeDamage = melee_Damage;
    rangedDamage = ranged_Damage;
    minHeal = min_Heal;
    maxHeal = max_Heal;
    minDef = min_Def;
    maxDef = max_Def;
    name = _name;
  }
  void Item(string item)  // called from levelUP() function 
  {
    cout<<"\n$"<<setfill('=')<<setw(28)<<"$"<<endl;
    cout<<"$"<<string(3,' ')<<"Item obtained: "<<item<<string(3,' ')<<"$"<<endl;
    cout<<"$"<<setfill('=')<<setw(28)<<"$"<<endl;
  }

  void levelUP()   // All stuff that changes after a level
  {
    level += 1;
    fullhealth += 100;
    health = fullhealth;
    switch(level){
      case 3: 
        cout<<"\nSpecial Ability : Critical Hit unlocked !!!\n";
        criticalHit = true;
        Item(" Sword");
        break;
      case 4:
        cout<<"\nSpecial Ability : Blocker unlocked !!!\n";
        blocker = true;
        Item("Shield");
        break;
      case 5:
        cout<<"\nSpecial Ability : LifeSteal unlocked !!!\n";
        lifeSteal = true;
        Item("Armour");
        break;
      case 6:
        cout<<"\nSpecial Ability : Ranged Attack unlocked !!!\n";
        rangedAttack = true;
        Item("   Bow");
        break;
    }
    meleeDamage += 5;
    rangedDamage += 5;
    minHeal += 2;
    maxHeal += 5;
    minDef += 3; 
    maxDef += 5;
  }
  int getHealth()
  {
    return health;
  }
  int getFullHealth()
  {
    return fullhealth;
  }
  int getLevel()
  {
    return level;
  }
  string getName()
  {
    return name;
  }
  int GiveDamage()
  {
    srand(time(0));
    int Damage = (rand() % (rangedDamage + 1 - meleeDamage) + meleeDamage);     //Random Damage
    
    if(hypnotise)
    {
      hypnotise = false;
      cout<<name<<" is hypnotised.\n";
      cout<<name<<" attacked himself with "<<Damage<<" points\n";
      health -= Damage;
      cout<<name<<"'s health after getting attacked is "<<health<<'\n';
      return 0;
    }
    srand(time(0));
    int specialAbility = (rand() % 11);         //Special Abilities having 10% probability.
    
    if (specialAbility == 1 && criticalHit == true)
    {
      cout<<name<<" used special ability : Critical Hit !\n";
      cout<<"Damage will be now 2 x "<<Damage<<'\n';
      Damage = Damage*2;
    }
    else if (specialAbility == 2 && blocker == true)
    {  
      cout<<name<<" used special ability : Blocker !\n";
      block = true;
      return 0; 
    }
    else if (specialAbility == 3 && lifeSteal == true) 
    {
      cout<<name<<" used special ability : Life Steal !\n";
      health += Damage;
      if (health>fullhealth) {health = fullhealth;}
      cout<<name<<" health recovered by "<<Damage<<" HP points\n";
      cout<<name<<" drained "<<Damage<<" HP from enemy"<<'\n';
      return Damage + healthdrain;        // Adding "healthdrain" denotes health drain state in which enemy cannot block
    }
    else if (specialAbility == 4 && rangedAttack == true) 
    {  
      cout<<name<<" used special ability : Ranged Attack !\n";
      cout<<"Damage will be now 1.5 x "<<Damage<<'\n';
      block = true;
      Damage = Damage*1.5;
    }
    
    cout<<name<<" attacked wth "<<Damage<<" points"<<'\n';
    return Damage;
  }

  void TakeDamage(int dmg)
  {  
    if (block)
    {
      block = false;
      cout<<name<<" blocked Enemy's attack completely. No Damage inflicted on "<<name<<"\n";
      return;
    }
    if (dmg > hypnotising)       //Player State "hypnotising" to detect Hypnotise being applied by Murlocs
    {
      dmg-=hypnotising;
      hypnotise = true;
    }
    srand(time(0));        //from here onwards, normal takedamage
    int def = (rand() % (maxDef + 1 - minDef) + minDef);
    cout<<name<<" defended "<<def<<" points"<<'\n';
    dmg -= def;
    if (dmg >=0)
      health -= dmg;
    if (health <= 0 )
    {
      cout<<name<<" died !!!"<<endl;
      health = 0;
      return;
    }
    cout<<name<<"'s health after getting attacked is "<<health<<'\n';
  } 
  void Healing()
  {
    if (health == fullhealth)
      cout<<"Healing is not applied."<<name<<"'s health is already full("<<health<<")\n";

    srand(time(0));
    int heal = (rand() % (maxHeal + 1 - minHeal) + minHeal);
    cout<<name<<" used healing of "<<heal<<" points"<<'\n';
    health += heal;
    if (health>=fullhealth) {health = fullhealth;}
    cout<<name<<"'s health after healing is "<<health<<'\n';
  }
};

class Enemy 
{
  protected:
  int health;
  int fullhealth;
  int minDamage;
  int maxDamage;
  int minDef;
  int maxDef;
  string name;

  public:
  Enemy()
  {   //nothing here 
  }
  int getHealth()
  {
    return health;
  }
  int getFullHealth()
  {
    return fullhealth;
  }
  string getName()
  {
    return name;
  }
  virtual int GiveDamage()
  {
    srand(time(0));
    int Damage = (rand() % (maxDamage + 1 - minDamage) + minDamage);
    cout<<name<<" attacked wth "<<Damage<<" points"<<"\n";
    return Damage;
  }
  virtual void TakeDamage(int dmg)
  {
    srand(time(0));
    int def = (rand() % (maxDef + 1 - minDef) + minDef);
    if (dmg > healthdrain){                      // "healthdrain" denotes health drain state in which enemy cannot block
      dmg -= healthdrain;
      goto skipDefence;
    }
    cout<<name<<" defended "<<def<<" points"<<'\n';
    dmg -= def;
    
    skipDefence:
    if (dmg >=0)
      health -= dmg;
    if (health <= 0 )
    {
      cout<<name<<" died !!!"<<endl;
      health = 0;
      return;
    }
    cout<<name<<"'s health after getting attacked is "<<health<<'\n';
  } 

  virtual int getMinionHealth() {return 0;}
  virtual bool minionEnabled() {return false;}
};

class Goblin: public Enemy
{
  public:
  Goblin(int _health, int full_health, int min_Damage, int max_Damage, int min_Def, int max_Def, string _name) 
  {
    health = _health;
    fullhealth = full_health;
    minDamage = min_Damage;
    maxDamage = max_Damage;
    minDef = min_Def;
    maxDef = max_Def;
    name = _name;
  }
};

class Troll: public Enemy
{
  public:
  Troll(int _health, int full_health, int min_Damage, int max_Damage, int min_Def, int max_Def, string _name) 
  {
    health = _health;
    fullhealth = full_health;
    minDamage = min_Damage;
    maxDamage = max_Damage;
    minDef = min_Def;
    maxDef = max_Def;
    name = _name;
  }
};

class Murlocs: public Enemy
{  
  int minionHealth;
  bool minion = false;

  public:
  Murlocs(int _health, int full_health, int min_Damage, int max_Damage, int min_Def, int max_Def, string _name, int minion_Health) 
  {
    health = _health;
    fullhealth = full_health;
    minDamage = min_Damage;
    maxDamage = max_Damage;
    minDef = min_Def;
    maxDef = max_Def;
    name = _name;
    minionHealth = minion_Health;
  }
   
  int getMinionHealth()       //Minions are creatures released by Murlocs's special ability
  {
    return minionHealth;
  }
  bool minionEnabled()
  {
    return minion;
  }
  int GiveDamage()
  {
    srand(time(0));
    int specialAbility = (rand() % 15);   /// 6.66% probability
    int Damage = (rand() % (maxDamage + 1 - minDamage) + minDamage);
    if (specialAbility == 1)
    {
      cout<<"Murlocs used special ability : Summon Minion !\n";
      minion = true;
      minionHealth = 150;
    }
    else if (specialAbility == 2)
    {
      cout<<"Murlocs used special ability : Healing Elixir !\n";
      if (health == fullhealth)
      {
        cout<<"No healing applied. Murlocs's health is full\n";
        cout<<"Murlocs attacked wth "<<Damage<<" points"<<"\n";
        return Damage;
      }
      health += 100;
      cout<<"Murlocs healed by 100 HP\n";
      if (health > fullhealth){
        health = fullhealth;
      }
    }
    else if (specialAbility == 3)
    {
      cout<<"Murlocs used special ability : Hypnotize !\n";
      cout<<"Murlocs attacked wth "<<Damage<<" points"<<"\n";
      return Damage + hypnotising;             // Player State Hypnotising to indicate Hypnotised condition
    }
    if(minion)
    {
      srand(time(0));
      int dmg = (rand() % (11) + 5);
      cout<<"Murlocs attacked wth "<<Damage<<" points and Minion attacked with "<<dmg<<" points"<<"\n";
      return Damage + dmg;
    }
    cout<<"Murlocs attacked wth "<<Damage<<" points"<<"\n";
    return Damage;
  }
  void TakeDamage(int dmg)
  {
    if (dmg == 0){
      return;
    }
    if(minion)   // When minion is there, Murloc's doesn't take damage.
    {
      minionHealth -= dmg;
      if (minionHealth <= 0)
      {
        minionHealth = 0;
        minion = false;
        cout<<"Minion died !!!\n";
      }
      cout<<"Minion's health after getting attacked is "<<minionHealth<<" out of 150\n";
      return;
    }
    srand(time(0));
    int def = (rand() % (maxDef + 1 - minDef) + minDef);
    if (dmg > healthdrain){                          // "healthdrain" denotes health drain state in which enemy cannot block
      dmg -= healthdrain;
      goto skipDefence;
    }
    cout<<"Murlocs defended "<<def<<" points"<<'\n';
    dmg -= def;

    skipDefence:
    if (dmg >=0)
      health -= dmg;
    if (health <= 0 )
    {
      cout<<"Murlocs died !!!"<<endl;
      health = 0;
      return;
    }
    cout<<"Murlocs's health after getting attacked is "<<health<<'\n';
  } 
};

class GameManager {

 public:

void gameTitle(){
  //GAME NAME printing
  system("clear");
  cout<<" \033[1m\033[47m\033[30m"<<'*'<<setfill('*')<<setw(101)<<'*'<< "\033[0m"<<endl;
  cout<<" \033[1m\033[47m\033[30m"<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<< "\033[0m"<<endl;
  cout<<" \033[1m\033[47m\033[30m"<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<< "\033[0m"<<endl;
  cout<<" \033[1m\033[47m\033[30m"<<'*'<<setfill(' ')<<std::string(40, ' ' )<<setw(60)<<left<<"NILFGAARD KINGDOM"<<'*'<< "\033[0m"<<endl;
  cout<<" \033[1m\033[47m\033[30m"<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<< "\033[0m"<<endl;
  cout<<" \033[1m\033[47m\033[30m"<<'*'<<setfill(' ')<<setw(101)<<right<<'*'<< "\033[0m"<<endl;
  cout<<" \033[1m\033[47m\033[30m"<<'*'<<setfill('*')<<setw(101)<<'*'<< "\033[0m"<<endl<<endl;
  //--------------------------------------------------------------------------------------------
  cout<<"Dare to enter the NILFGAARD KINGDOM ? \n";
  cout<<"MONSTER KING MURLOCS and his henchmen have spread terror across the land.\n";
  cout<<"Infiltrate the CASTLE in the KINGDOM and kill all the enemies...\n\n\n";
}

void healthStats(Player &player, Enemy *enemy)
{
  cout<<" \033[1m\033[47m\033[30m"<<'-'<<setfill('-')<<setw(32)<<'-'<< "\033[0m"<<endl;
  cout<<" \033[1m\033[47m\033[30m"<<'|'<<setfill(' ')<<std::string(3, ' ' )<<setw(12)<<left<<player.getName()<<'|'<< "\033[0m";
  cout<<"\033[1m\033[47m\033[30m"<<setfill(' ')<<std::string(4, ' ' )<<setw(11)<<left<<enemy->getName()<<'|'<< "\033[0m"<<endl;
  cout<<" \033[1m\033[47m\033[30m"<<'|'<<std::string(2, ' ' )<<setfill(' ')<<setw(5)<<right<<player.getHealth()<<"/"  
    <<setw(4)<<left<<player.getFullHealth()<<setw(4)<<right<<'|'<< "\033[0m";
  cout<<"\033[1m\033[47m\033[30m"<<std::string(3, ' ' )<<setfill(' ')<<setw(4)<<right<<enemy->getHealth()<<"/"
    <<setw(4)<<left<<enemy->getFullHealth()<<setw(4)<<right<<'|'<< "\033[0m"<<endl;
  cout<<" \033[1m\033[47m\033[30m"<<'-'<<setfill('-')<<setw(32)<<'-'<< "\033[0m"<<endl;

  if(enemy->minionEnabled())
  {
    cout<<" \033[1m\033[47m\033[30m"<<'-'<<setfill('-')<<setw(16)<<'-'<< "\033[0m"<<endl;
    cout<<"\033[1m\033[47m\033[30m"<<'|'<<setfill(' ')<<std::string(3, ' ' )<<setw(12)<<left<<" Minion"<<'|'<< "\033[0m"<<endl;
    cout<<"\033[1m\033[47m\033[30m"<<'|'<<std::string(3, ' ' )<<setfill(' ')<<setw(4)<<right<<enemy->getMinionHealth()<<"/"
    <<setw(4)<<left<<"150"<<setw(4)<<right<<'|'<< "\033[0m"<<endl;
    cout<<" \033[1m\033[47m\033[30m"<<'-'<<setfill('-')<<setw(16)<<'-'<< "\033[0m"<<endl;
  }
}

PlayerState battleloop(Player *player,Enemy *enemy)
{
  char move;
  do
  {
    healthStats(*player,enemy);
    Start:
    cout<<"\nPress A to attack or H to Heal\n";
    cin>>move;
    cout<<'\n';
    if (move == 'A' or move == 'a')
    {
      enemy->TakeDamage(player->GiveDamage());
    }
    else if (move == 'H' || move == 'h')
    {
      player->Healing();
      cout<<"Enemy health remaining is: "<<enemy->getHealth()<<'\n';
    }
    else 
    {
      cout<<"Invalid Input ! \n\n";
      goto Start;
    }
    //Enemy Death Condition Check
    if (enemy->getHealth()<=0) 
    {
      cout<<'-'<<setfill('-')<<setw(101)<<'-'<<endl;
      break;
    }
    //Enemy's turn
    cout<<'\n';
    player->TakeDamage(enemy->GiveDamage());
    cout<<'\n';
    cout<<'-'<<setfill('-')<<setw(101)<<'-'<<endl;
  }while(player->getHealth()>0 && enemy->getHealth()>0);
  
  //Return according to Player death condition
  if (player->getHealth() <=0)
    return dead;      //Player Dead
  else
    return alive;      //Player Alive
}
};

class LevelManager : public GameManager{
  int level;
  int gCount;
  int vCount;
  Enemy *enemy;
  Player *player = new Player(1,100,100,25,45,30,45,5,15,"Witcher");
  PlayerState death = alive;
  
  public:
  PlayerState Level()
  {
    level = player->getLevel();
    gCount = (level<=3) ? level : 3;
    vCount = (level>3) ? (level-3) : 0;
    
    //output message
    cout<<'\n'<<'+'<<setfill('+')<<setw(101)<<'+'<<endl;
    switch(level)
      {
        case 1:  cout << "\n Villagers : Thank you for fighting  for us, Witcher. We "
              "wish you the best for your journey.\n";
                 cout << "\n Witcher has entered the enemy area... \n\nYou will "
              "gain a weapon/ skill after each level, which will make you "
              "stronger. During the levels, you might need to look at your / "
              "enemy's current stats. Do not worry. We will keep track of the "
              "same and show it to you after every turn. \n\nLet's go !! THE "
              "FIRST LEVEL IS COMING ......\n\nAs per our calculations, there "
              "is only ONE ENEMY in the level.\n\n";
                cout<<"\n Level 1 : Defeat the Goblin !!!\n";
          break;
        case 2: cout << "\n--------------------*--------------------**-----------------"
              "---*--------------------\n\n";
                cout << "\n Witcher has defeated the First Level ... \n";
                cout << "\n Witcher : Piece of Cake. Bring it on, MURLOCS :) \n\n";
                cout << " Villagers : We have found a Map which will help you learn "
              "about MURLOCS' territory a bit more. Hope it helps.\n"
              "Villagers handover the map to reach Monster Murlocs\n";
                cout << " It looks like MURLOCS has found out about you. He is sending "
              "the SECOND LEVEL with 2 enemies now !! ... \n\n";
                cout << " Witcher : BRING IT ON !! "
              "\n\n--------------------*--------------------**---------------"
              "-----*--------------------\n\n";
                cout<<"\n Level 2 : Defeat two Goblins !!!\n";
          break;
        case 3: cout << "\n---------------------*--------------------**----------------"
              "----*--------------------\n\n";
                cout << "\n Witcher making it look easy ....\n";
                cout << "\n Witcher : Took some time. But was not a problem. I "
              "need to start attacking with more power !! \n";
                cout << "\n 3 enemies are on your way... "
              "\n\n\n--------------------*--------------------**-------------"
              "-------*--------------------\n\n";
                cout<<"\n Level 3 : Defeat three Goblins !!!\n";
          break;
        case 4: cout << "\n--------------------*--------------------**-----------------"
              "---*--------------------\n\n";
                cout << "\n Witcher successful once AGAIN ....\n";
                cout << "\n Witcher : Things are getting more challenging now. I "
              "need to use my defending skills !! \n";
                cout << "\n The 4th level is here !! 4 enemies have arrived... "
              "\n\n\n--------------------*--------------------**-------------"
              "-------*--------------------\n\n";
                cout<<"\n Level 4 : Defeat three Goblins and a Troll !!!\n";
          break;
        case 5: cout << "\n--------------------*--------------------**-----------------"
              "---*--------------------\n\n";
                cout << "\n Witcher is still standing !! ....\n";
                cout << "\n Witcher : My attacks and defence are getting weaker. "
              "But I can control them for now. \n";
                cout << "\n Seems like this is the last level that MURLOCS has. 5 of his "
              "fellow monsters have appeared ... \n\n\n";
                cout << "--------------------*--------------------**-------------------"
              "-*--------------------\n\n";
                cout<<"\n Level 5 : Defeat three Goblins and two Trolls !!!\n";
          break;
        case 6: cout << "\n--------------------*--------------------**-----------------"
              "---*--------------------\n\n";
                cout << "\n Witcher pulls through !! ..... \n";
                cout << "\n Witcher : I need to decapitate the enemy so that I "
              "have so breathing room. MURLOCS is next.\n";
                cout << "\n Villagers : Wait !! MURLOCS is not an ordinary Enemy ! He "
              "has Special Abilities !!\n";
                cout << "\n MURLOCS has arrived !!! He looks "
              "angry as you have killed his army of monsters. ALL. THE. BEST !! "
              ".... \n\n\n";
                cout << "--------------------*--------------------**-------------------"
              "-*--------------------\n\n";
                cout<<"\n Level 6 : Defeat Murlocs the MONSTER KING !!!\n";
      }
    cout<<'\n'<<'+'<<setfill('+')<<setw(101)<<'+'<<endl;

    if (level == 6)
    {
      enemy = new Murlocs(1000,1000,40,70,15,40,"Murlocs",150);
      death = battleloop(player, enemy);
      delete enemy;
    }
    else
    {
      for(int g=1; g<=gCount; g++)
        {
          enemy = new Goblin(200,200,20,35,6,24,"Goblin");
          cout<<"\nGoblin "<<g<<" appeared !\n";
          cout<<endl;
          death = battleloop(player, enemy);
          delete enemy;
        }
      for(int v=1; v<=vCount && v>0; v++)
        {
          enemy = new Troll(500,500,35,50,15,35,"Troll");
          cout<<"\nTroll "<<v<<" appeared !\n";
          cout<<endl;
          death = battleloop(player, enemy);
          delete enemy;
        }
    }
    player->levelUP();
    return death;
  }

void playerselection(){
  char userInput;
  gameTitle();
  do{
    cout<<"Press S to start the Game or any other key to exit\n";
    cin>>userInput;
    cout<<"\n\n";
    if (userInput != 'S' && userInput != 's')
    {return ;}
    PlayerState n;
    for (int i = 1; i<=6; i++)
      {
        n = Level();
        if (n==dead)
        {
          cout<<"\nGAME OVER !!!\n";
          cout<<endl;
          break;
        }  
      }
    if (n == alive)
    {
      cout << "\n--------------------*--------------------**-----------------"
              "---*--------------------\n\n";
      cout << "\n Witcher kills MURLOCS with one final strike !! .... "
              "IT'S OVER !!! \n";
      cout << "\n Witcher : I did it. I finally did it !! \n\n\n";
      cout << "--------------------*--------------------**-------------------"
              "-*--------------------\n\n";
      cout<<"Congrats !!! You defeated Murlocs and cleared the troops in CASTLE of KINGDOM NILFGAARD. Glory awaits you strong warrior !!\n\n"; 
    }
  }while(userInput == 'S' || userInput == 's');
}
};

int main() 
{
  GameManager game;
  LevelManager level;
 
  game.gameTitle();
  level.playerselection();
  
  return 0;
}
