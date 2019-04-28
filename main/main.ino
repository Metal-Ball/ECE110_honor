#include "all_constants.h"
#include "main.h"
#include "HP_lose.h"
#include "joystick_IO.h"
#include "starting_ending.h"
#include "game_logic1.h"
#include "game_logic2.h"
#include "retry.h"

///////////////////////////constant and global variables//////////////////////////////////////////////////////////////////////
//game starting signal
int start=0;

static int player1_counter=PLAYER1_COUNTER_MAX;


static player player1;
static player player2;

//initialize bomb lists
heavyBomb1 heavyBombList1[HEAVY_BOMB_NUM];
heavyBomb2 heavyBombList2[HEAVY_BOMB_NUM];
lightBomb1 lightBombList1[LIGHT_BOMB_NUM];
lightBomb2 lightBombList2[LIGHT_BOMB_NUM];



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
  

}


void loop() {
  
  //////////////////////////starting////////////////////////////////////////////////////////////////////////////
  if(!start){
     reset();
     //prepare for game and initialize players
     game_ready(&player1, &player2);
     //bombList initializations
     bombList_init(heavyBombList1, heavyBombList2, lightBombList1, lightBombList2);
     //start game
     game_start(player1, player2);
     start=1;
    
  }
  if(start){
  //////////////////////////gaming//////////////////////////////////////////////////////////////////////////////
  if(player1.HP>0 && player2.HP>0){  
      
  //global delay 
  delay(5);
 
  //player1 speed 
  if(player1_counter!=0)
  {player1_counter--;}
  
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
  perform_player_movement(&player1, &player2,&player1_counter);
  
  //perform bomb movement
  perform_bomb_movement(&player1, &player2, heavyBombList1, heavyBombList2, lightBombList1, lightBombList2);

  }
  //////////////////////////ending//////////////////////////////////////////////////////////////////////////////
  if (player1.HP == 0) {
    reset();
    draw(1,player2.x,player2.y,1,0,player2.mycolor);
    game_player2_wins(player1,player2);
    reset();
    digitalWrite(8,HIGH);
    //start=retry();
    reset();
  }
  if (player2.HP == 0 ) {
    reset();
    draw(1,player1.x,player1.y,1,0,player1.mycolor);
    game_player1_wins(player1,player2);
    reset();
    digitalWrite(8,HIGH);
    //start=retry();
    reset();
  }
  }
}
