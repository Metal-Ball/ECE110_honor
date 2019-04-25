
#include "main.h"
#include "joystick_IO.h"
#include "starting_ending.h"
#include "game_logic1.h"
#include "game_logic2.h"


///////////////////////////constant and global variables//////////////////////////////////////////////////////////////////////
//game starting signal
int start=0;

//define heavy and light bomb capacity
#define HEAVY_BOMB_NUM 1
#define LIGHT_BOMB_NUM 3

//define bottom enable counter upper bound: leaving time for actions
//bottom enable: 0 means active
#define BE_UP_MAX 20
#define BE_RIGHT_MAX 5
#define BE_LEFT_MAX 100

//INVINCIBLE_FRAME period after shot
#define INVINCIBLE_FRAME 40

//thunder counter
#define thunder_counter_max 50;

//construct 2 players in the order of
//x, y, moveX, moveY, UP, LEFT, RIGHT, DOWN, HP, HP_LOSE, name, color,
//BE_UP, BE_RIGHT, heavy_usage, light_usage, thunder_counter
static player player1 = {15, 1, 0, 0, 0, 0, 0, 0, 3, 0,  ColR, 0, 0, 0, 0, -99,0};
static player player2 = {15, 30, 0, 0, 0, 0, 0, 0, 3, 0, ColB, 0, 0, 0, 0, -99,0};

//initialize bomb lists
heavyBomb1 heavyBombList1[HEAVY_BOMB_NUM];
heavyBomb2 heavyBombList2[HEAVY_BOMB_NUM];
lightBomb1 lightBombList1[LIGHT_BOMB_NUM*2];
lightBomb2 lightBombList2[LIGHT_BOMB_NUM*2];

/////////////////////////game set up///////////////////////////////////////////////////////////////////////////////////////////
void setup() {

  Serial.begin(74880);

  pinMode (2, INPUT); // BottomUp 1
  pinMode (3, INPUT); // BottomRight 1
  pinMode (4, INPUT); // BottomDown 1
  pinMode (5, INPUT); // BottomLeft 1
  pinMode (6, INPUT); // BottomStart 1
  pinMode (7, INPUT); // BottomEnd 1

  //player2
  pinMode(12,OUTPUT);
  //player1
  pinMode(11,OUTPUT);
  //clock
  pinMode(10,OUTPUT);
  //reset
  pinMode(8,OUTPUT);
  
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

  //pin 12 is used as player 2 get shot signal
  digitalWrite(12,LOW);
  //pin 11 is used as player 1 get shot signal
  digitalWrite(11,LOW);
  //pin 10 is used as clock signal
  analogWrite(10,127);
  //pin 8 is used as reset signal
  digitalWrite(8,LOW);
  
  //feed random num generator
  srand(time(NULL));
  
  //bombList initializations
  bombList_init(heavyBombList1, heavyBombList2, lightBombList1, lightBombList2);

}


void loop() {
  
  //////////////////////////starting////////////////////////////////////////////////////////////////////////////
  if(!start){
     game_ready(&player1, &player2);
     game_start(player1, player2);
     start=1;
  }
  if(start){
  //////////////////////////gaming//////////////////////////////////////////////////////////////////////////////
  if(player1.HP>0 && player2.HP>0){  
      
  //global delay 
  delay(5);

  //initialize output pins
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  
  //all counters update
  counter_update(&player1, &player2);
  
  //read joysticks inputs
  joysticksIO(&player1,&player2);
   
  //perform bottom actions
  perform_bottom_actions(&player1, &player2, heavyBombList1, heavyBombList2, lightBombList1, lightBombList2);
 
  //perform player movement
  perform_player_movement(&player1, &player2);
  
  //perform bomb movement
  perform_bomb_movement(&player1, &player2, heavyBombList1, heavyBombList2, lightBombList1, lightBombList2);

  }
  //////////////////////////ending//////////////////////////////////////////////////////////////////////////////
  if (player1.HP == 0) {
    reset();
    draw(1,player2.x,player2.y,1,0,player2.mycolor);
    game_player2_wins(player1,player2);
    player1.HP--;
    digitalWrite(8,HIGH);
  }
  if (player2.HP == 0 ) {
    reset();
    draw(1,player1.x,player1.y,1,0,player1.mycolor);
    game_player1_wins(player1,player2);
    player2.HP--;
    digitalWrite(8,HIGH);
  }
  }
}
