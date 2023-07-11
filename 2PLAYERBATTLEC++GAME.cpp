/****************************************************************************************************

BATTLE CLASH PVP is a 2P Battle Game

Players with Parameter Types :

ShaolinMaster     : High Health, Low Damage, Low Healing
Samurai           : Avg Health, Avg Damage, Avg Healing
Ninja             : Low Health, High Damage, Avg Healing

Parameter         : High,Average,Low

Health            : 500, 350, 250
Base Damage       : 70, 55, 45
Additional Damage : 20-35, 15-30 ,10-25
Healing           : NA,  55-75, 35-55

Special Ability   - Special Abilities Loaded on every fifth move but will be used only if player chooses to Attack.

ShaolinMaster     : One Inch Punch - A deadly damage of 150 damage points.
Samurai           : Stun - enemy gets stunned/moves into a dazed or semi-conscious state and will end up wasting their 3 moves.
Ninja             : Shadow Clone - creates a shadow clone of 150 hp. Ninja will get attacked only after shadow clone is dead.

****************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <random>
#include <stdlib.h>

using namespace std;

enum PlayerState {
  STUN,
  ALIVE,
  DEAD
};

class Player{

  protected:

  int Health;
  int Full_Health;
  int Base_Damage;
  int Ad_Damage;
  int Max_Damage,Min_Damage,Max_Heal,Min_Heal;
  int Move_Count;
  char Name,Opp;

  public:
  
  Player(){
    
  }
  virtual int giveDamage(){
    return 0;
  }
  virtual int takeDamage(int dmg){
    return 0;
  }
  virtual void Heal(){
  }
  int getHealth(){
    return Health;
  }
};

class ShaolinMaster : public Player {

  int stun = 0, stun_Count = 0;
  public:

  ShaolinMaster(char _name, int _health, int _fullhealth, int _basedamage, int _maxdamage, int _mindamage, int _maxheal, int _minheal, int _movecount){
    Health = _health;
    Full_Health = _fullhealth;
    Base_Damage = _basedamage;
    Max_Damage = _maxdamage;
    Min_Damage = _mindamage;
    Max_Heal = _maxheal;
    Min_Heal = _minheal;
    Name = _name;
    Move_Count = _movecount;
    Opp = (Name == '1')? '2' : '1';

    cout<<"\033[38;5;208m"<<"\n Player "<< Name <<" is ShaolinMaster of Health "<< Full_Health <<" and Special Ability One Inch Punch !!\n"<<"\033[0m";
    cout<<endl;
  }

  int giveDamage(){
    int Damage;

    //Check whether player got stunned. If yes, skip attacking
    if (stun == 1 && stun_Count < 3){
      cout<<"\033[38;5;208m"<<" Player "<< Name <<" is stunned. Won't be able to attack...\n"<<"\033[0m";
      cout<<endl;
      stun_Count++;
      return 0;
    }
    //Special Ability
    if (Move_Count >= 4) {
      Move_Count = 0;
      cout<<"\033[38;5;208m"<<" Player "<< Name <<" used ShaolinMaster special ability : One Inch Punch !!!\n"<<"\033[0m";
      cout<<"\033[38;5;208m"<<" Player "<< Name <<" gave a deadly blow of 150 damage\n"<<"\033[0m";
      cout<<endl;
      cout<<endl;
      return 150;
    }
    //Normal Attack
    Move_Count++;
    srand(time(0));
    Damage = Base_Damage + (rand() % (Max_Damage + 1 - Min_Damage) + Min_Damage);
    cout<<"\033[38;5;208m"<<" Player "<< Name <<" attacked with "<< Damage <<" damage\n"<<"\033[0m";
    cout<<endl;
    return Damage;
  }

  int takeDamage(int dmg){
    //Skip the damage 999 which denotes stun.
    if (dmg == STUN){
      stun = 1;
      stun_Count = 0;
      return 200;
    }
    //skipping 0 condition.
    if (dmg == 0){return 200;}
    
    Health -= dmg;
    if (Health <= 0){
      cout<<"\033[38;5;208m"<<" Oh no ... Player "<< Name <<" died"<<'\n'<<"\033[0m";
      cout<<"\033[38;5;208m"<<" Player "<< Opp <<" Won the game\n"<<"\033[0m";
      cout<<endl;
      cout<<endl;
      return 2;
      }
    else{
      cout<<"\033[38;5;208m"<<" Player "<< Name <<" health after getting attacked is: "<< Health <<'\n'<<"\033[0m";
      cout<<endl;
    }
    return 200;
  }

  void Heal(){
    Move_Count++;
    srand(time(0));
    int random_Heal = (rand() % (Max_Heal + 1 - Min_Heal) + Min_Heal);
    if (Health == Full_Health){
      cout<<"\033[38;5;208m"<<" Player "<< Name <<" Health is already full. Heal is not applied.\n"<<"\033[0m";
      cout<<endl;
      return;
    }
    Health += random_Heal; // Healing
    if (Health >= Full_Health) {Health = Full_Health;}
    cout<<"\033[38;5;208m"<<" Player "<< Name <<" healed with "<< random_Heal <<" hp points\n"<<"\033[0m";
    cout<<"\033[38;5;208m"<<" Player "<< Name <<" health after healing is "<< Health <<'\n'<<"\033[0m";
    cout<<endl;
    cout<<endl;
  }
};

class Samurai : public Player {
  int stun = 0, stun_Count = 0;
  public:

  Samurai(char _name, int _health, int _fullhealth, int _basedamage, int _maxdamage, int _mindamage, int _maxheal, int _minheal, int _movecount){
    Health = _health;
    Full_Health = _fullhealth;
    Base_Damage = _basedamage;
    Max_Damage = _maxdamage;
    Min_Damage = _mindamage;
    Max_Heal = _maxheal;
    Min_Heal = _minheal;
    Name = _name;
    Move_Count = _movecount;
    Opp = (Name == '1')? '2' : '1';

    cout<<"\033[33m"<<"\n Player "<< Name <<" is Samurai of Health "<< Full_Health <<" and Special Ability Stun !!\n"<<"\033[0m";
    cout<<endl;
  }

  int giveDamage(){
    //Check whether player got stunned. If yes, skip attacking
    if (stun == 1 && stun_Count <= 3){
      cout<<"\033[33m"<<" Player "<< Name <<" is stunned. Won't be able to attack...\n"<<"\033[0m";
      cout<<endl;
      stun_Count++;
      return 0;
    }
    
    int Damage;
    //Special Ability
    if (Move_Count >= 4) {
      Move_Count = 0;
      cout<<"\033[33m"<<" Player "<< Name <<" used Samurai special ability : Stun !!!\n"<<"\033[0m";
      cout<<"\033[33m"<<" Player "<< Opp <<" got Stunned!\n"<<"\033[0m";
      cout<<endl;
      cout<<endl;
      return 0; //code number to identify stun attack
    }
    //Normal Attack
    Move_Count++;
    srand(time(0));
    Damage = Base_Damage + (rand() % (Max_Damage + 1 - Min_Damage) + Min_Damage);
    cout<<"\033[33m"<<" Player "<< Name <<" attacked with "<< Damage <<" damage\n"<<"\033[0m";
    cout<<endl;
    return Damage;
  }

  int takeDamage(int dmg){
    
    //Skip the damage 999 which denotes stun.
    if (dmg == STUN){
      stun = 1;
      stun_Count = 0;
      return 200;
    }
    
    //skipping 0 condition.
    if (dmg == 0){return 200;}
    
    Health -= dmg;
    if (Health <= 0){
      cout<<"\033[33m"<<" Oh no ... Player "<< Name <<" died"<<'\n'<<"\033[0m";
      cout<<"\033[33m"<<" Player "<< Opp <<" Won the game\n"<<"\033[0m";
      cout<<endl;
      cout<<endl;
      return 2;
      }
    else{
      cout<<"\033[33m"<<" Player "<< Name <<" health after getting attacked is: "<< Health <<'\n'<<"\033[0m";
      cout<<endl;
    }
    return 200;
  }

  void Heal(){
    Move_Count++;
    srand(time(0));
    int random_Heal = (rand() % (Max_Heal + 1 - Min_Heal) + Min_Heal);
    if (Health == Full_Health){
      cout<<"\033[33m"<<" Player "<< Name <<" Health is already full. Heal is not applied.\n"<<"\033[0m";
      cout<<endl;
      return;
    }
    Health += random_Heal; // Healing
    if (Health >= Full_Health) {Health = Full_Health;}
    cout<<"\033[33m"<<" Player "<< Name <<" healed with "<< random_Heal <<" hp points\n"<<"\033[0m";
    cout<<"\033[33m"<<" Player "<< Name <<" health after healing is "<< Health <<'\n'<<"\033[0m";
    cout<<endl;
    cout<<endl;
  }
};

class Ninja : public Player{
  int stun = 0, stun_Count = 0;
  int Shadow_Clone = 0;
  public:

  Ninja(char _name, int _health, int _fullhealth, int _basedamage, int _maxdamage, int _mindamage, int _maxheal, int _minheal, int _movecount){
    Health = _health;
    Full_Health = _fullhealth;
    Base_Damage = _basedamage;
    Max_Damage = _maxdamage;
    Min_Damage = _mindamage;
    Max_Heal = _maxheal;
    Min_Heal = _minheal;
    Name = _name;
    Move_Count = _movecount;
    Opp = (Name == '1')? '2' : '1'; 

    cout<<"\033[38;5;250m"<<"\n Player "<< Name <<" is Ninja of Health "<< Full_Health <<" and Special Ability Shadow Clone !!\n"<<"\033[0m";
    cout<<endl;
  }

  int giveDamage(){
    //Check whether player got stunned. If yes, skip attacking
    if (stun == 1 && stun_Count <= 3){
      cout<<"\033[38;5;250m"<<" Player "<< Name <<" is stunned. Won't be able to attack...\n"<<"\033[0m";
      cout<<endl;
      stun_Count++;
      return 0;
    }
    
    int Damage;
    //Special Ability
    if (Move_Count >= 4) {
      Move_Count = 0;
      cout<<"\033[38;5;250m"<<" Player "<< Name <<" used Ninja special ability : Shadow Clone !!!\n"<<"\033[0m";
      cout<<"\033[38;5;250m"<<" Player "<< Name <<" Summoned a shadow clone of 150 HP\n"<<"\033[0m";
      cout<<endl;
      cout<<endl;
      Shadow_Clone = 150;
      return 0;
    }
    //Normal Attack
    Move_Count++;
    srand(time(0));
    Damage = Base_Damage + (rand() % (Max_Damage + 1 - Min_Damage) + Min_Damage);
    cout<<"\033[38;5;250m"<<" Player "<< Name <<" attacked with "<< Damage <<" damage\n"<<"\033[0m";
    cout<<endl;
    return Damage;
  }

  int takeDamage(int dmg){
    
    //Skip the damage 999 which denotes stun.
    if (dmg == STUN){
      stun = 1;
      stun_Count = 0;
      return 200;
    }
    //skipping 0 condition.
    if (dmg == 0){return 200;}

    //killing shadowClone first
    if (Shadow_Clone > 0){
      Shadow_Clone -= dmg;
      if (Shadow_Clone <= 0){
        cout<<"\033[38;5;250m"<<" Shadow Clone of Player "<< Name<< " Died\n"<<"\033[0m";
        cout<<endl;
        Shadow_Clone = 0;
      }
      cout<<"\033[38;5;250m"<<" Shadow Clone's health after getting attacked is: "<< Shadow_Clone <<" out of 150\n"<<"\033[0m";
      cout<<endl;
      return 200;
    }
    //normal takeDamage
    Health -= dmg;
    if (Health <= 0){
      cout<<"\033[38;5;250m"<<" Oh no ... Player "<< Name <<" died"<<'\n'<<"\033[0m";
      cout<<"\033[38;5;250m"<<" Player "<< Opp <<" Won the game\n"<<"\033[0m";
      cout<<endl;
      cout<<endl;
      return 2;
      }
    else{
      cout<<"\033[38;5;250m"<<" Player "<< Name <<" health after getting attacked is: "<< Health <<'\n'<<"\033[0m";
      cout<<endl;
    }
    return 200;
  }

  void Heal(){
    Move_Count++;
    srand(time(0));
    int random_Heal = (rand() % (Max_Heal + 1 - Min_Heal) + Min_Heal);
    if (Health == Full_Health){
      cout<<"\033[38;5;250m"<<" Player "<< Name <<" Health is already full. Heal is not applied.\n"<<"\033[0m";
      cout<<endl;
      return;
    }
    Health += random_Heal; // Healing
    if (Health >= Full_Health) {Health = Full_Health;}
    cout<<"\033[38;5;250m"<<" Player "<< Name <<" healed with "<< random_Heal <<" hp points\n"<<"\033[0m";
    cout<<"\033[38;5;250m"<<" Player "<< Name <<" health after healing is "<< Health <<'\n'<<"\033[0m";
    cout<<endl;
    cout<<endl;
  }
};

class GameManager : public Player{

 public:

 void GameTitle(){
  //GAME NAME printing
  system("clear");
  cout<<" \033[1m\033[47m\033[30m" << '*' << setfill('*') << setw(101) << '*' << "\033[0m" <<endl;
  cout<<" \033[1m\033[47m\033[30m" << '*' << setfill(' ') << setw(101) << right << '*' << "\033[0m" <<endl;
  cout<<" \033[1m\033[47m\033[30m" << '*' <<setfill(' ') << setw(101) << right << '*' << "\033[0m" <<endl;
  cout<<" \033[1m\033[47m\033[30m" << '*' << setfill(' ') << std::string(40, ' ' ) << setw(60) << left << " BATTLE CLASH PVP " << '*' << "\033[0m" <<endl;
  cout<<" \033[1m\033[47m\033[30m" << '*' << setfill(' ') << setw(101) << right << '*' << "\033[0m" <<endl;
  cout<<" \033[1m\033[47m\033[30m" << '*' << setfill(' ') << setw(101) << right << '*' << "\033[0m" <<endl;
  cout<<" \033[1m\033[47m\033[30m" << '*' << setfill('*') << setw(101) << '*' << "\033[0m" <<endl;
  //--------------------------------------------------------------------------------------------
 }

void Instructions(){

  cout<<" \n\n This is a 2 Player vs Player Battle Game \n\n ";
  cout<<" Players in the game can Attack or Heal \n\n ";
  cout<<" Special ability gets loaded for every fifth move and gets released automatically when player chooses to attack. \n\n ";
  cout<<" Characters in the game\n\n";
  cout<<" ShaolinMaster : A powerful human with high health.\n Uses a special ability One Inch Punch that deals 150 damage to the enemy. \n\n ";
  cout<<"Samurai : A discliplined and focussed warrior.\n Uses a special ability Stun to stun his opponents for duration of 3 moves \n\n";
  cout<<" Ninja : A trained assassin with fast and high damage ability.\n Uses a special ability Shadow Clone that summons a Shadow Clone of 150 HP.\n Enemy must kill the clone first to attack the player. \n\n";
  cout<<"\n         ShaolinMaster Player  text in  -> '\033[38;5;208mOrange\033[0m'";
  cout<<"\n         Samurai Player text in  -> '\033[33mYellow\033[0m'";
  cout<<"\n         Ninja Player text in  -> '\033[38;5;250mSilver\033[0m'";
  cout<<endl;
  cout<<endl;
  
}

void playerselection(){
  
char UserInput;
  do {
    cout<<endl<< " Press S to start the game or any other key to exit... "<<endl;
    cin>>UserInput;
    if ((UserInput == 'S')||(UserInput == 's'))
    {
      cout<< '+' << setfill('+') << setw(101) << '+' <<endl;
      
      //Player Selection Happens Here ------------------
      char PlayerA,PlayerB;
      Player *A , *B;
      p1: //Player 1 selection location
      cout<<endl;
      cout<< " \n Player 1 : Select your character \n";
      cout<<endl;
      cout<< "\033[38;5;208m 1: ShaolinMaster \033[0m\n" << "\033[33m 2: Samurai \033[0m\n" << "\033[38;5;250m 3: Ninja \033[0m\n";
      cout<<endl;
      cin>>PlayerA;
      switch(PlayerA)
        {
          case '1': A = new ShaolinMaster('1',500,500,45,25,10,55,35,0);
                    break;
          case '2': A = new Samurai('1',350,350,55,30,15,75,55,0);
                    break;
          case '3': A = new Ninja('1',250,250,70,35,20,75,55,0);
                    break;
          default: cout<< " Invalid Input \n";
                    cout<<endl;
                    goto p1;
        }
      p2: //Player 2 selection location
      cout<<endl;
      cout<< " \n Player 2 : Select your character \n";
      cout<<endl;
      cout<< "\033[38;5;208m 1: ShaolinMaster \033[0m\n" << "\033[33m 2: Samurai \033[0m\n" << "\033[38;5;250m 3: Ninja \033[0m\n";
      cout<<endl;
      cin>>PlayerB;
      switch(PlayerB)
        {
          case '1': B = new ShaolinMaster('2',500,500,45,25,10,55,35,0);
                    break;
          case '2': B = new Samurai('2',350,350,55,30,15,75,55,0);
                    break;
          case '3': B = new Ninja('2',250,250,70,35,20,75,55,0);
                    break;
          default: cout<< " Invalid Input \n";
                    cout<<endl;
                    goto p2;
        }
      cout<< '+' << setfill('+') << setw(101) << '+' <<endl;
    
      //BATTLE Loop Starts Here -----------------
      gameLoop(A,B);
      delete A;
      delete B;
}
      else
    {
      cout<<endl;
      cout<<"\033[34m"<< " GAME OVER !!! " << "\033[0m" <<endl;
      cout<<endl;
    }
  }while((UserInput == 'S')||(UserInput == 's'));
      
}

int PlayerMove(Player *X,Player *Y){
  char Move;
  int Death;
  int Heal;
  cout<<endl;
  Start:
  cout<< " Press A to Attack OR Press H to Heal : \n";
  cin>>Move;
  cout<<endl;
  if(Move == 'A' || Move == 'a'){
    Death = Y->takeDamage(X->giveDamage());
    return Death;
  } 
  else if(Move == 'H' || Move == 'h'){
    X->Heal();
    return 0;
  }
  else{
    cout<<endl;
    cout<< " Invalid Input .. \n\n";
    cout<<endl;
    goto Start;
  } 
}

void gameLoop(Player *A, Player *B){
  
  do{
  int Move;
  //Player 1 make his move
    cout<<endl;
  cout<< " \n Player 1 make your move ! " <<'\n';
    cout<<endl;
  Move = PlayerMove(A,B);
  if (Move == DEAD){break;} //Death Break
    
  //Player 2 make his move
    cout<<endl;
  cout<< " \n Player 2 make your move ! " <<'\n';
    cout<<endl;
  Move = PlayerMove(B,A);
  if (Move == ALIVE){break;} // Death Break
    
  cout<< '-' << setfill('-') << setw(101) << '-' <<endl;
  }while(A->getHealth()>0 && B->getHealth()>0);

}
};

int main(){

  GameManager game;
 
  game.GameTitle();
  game.Instructions();
  game.playerselection();
 
  return 0;
}












