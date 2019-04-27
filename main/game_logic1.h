//define heavy and light bomb capacity
#define HEAVY_BOMB_NUM 2
#define LIGHT_BOMB_NUM 5

//define heavy and light bomb speed
#define HEAVY_BOMB_COUNTER 7
#define LIGHT_BOMB_COUNTER 4

//player1 movement counter
#define PLAYER1_COUNTER_MAX 5;

//define bottom enable counter upper bound: leaving time for actions
//bottom enable: 0 means active
#define BE_UP_MAX 20
#define BE_RIGHT_MAX 5
#define BE_LEFT_MAX 100

//INVINCIBLE_FRAME time after shot
#define INVINCIBLE_FRAME 40

//thunder counter
#define thunder_counter_max 50;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//bomblist initialization
void bombList_init(heavyBomb1* heavyBombList1, heavyBomb2* heavyBombList2, lightBomb1* lightBombList1, lightBomb2* lightBombList2){
  for (int i = 0; i < HEAVY_BOMB_NUM; i++) {
    heavyBombList1[i] = {32, 32, 0};
    heavyBombList2[i] = { -1, -1, 0};
  }
  for (int i = 0; i < LIGHT_BOMB_NUM; i++) {
    lightBombList1[i] = {32, 32, 0};
    lightBombList2[i] = { -1, -1, 0};
  } 
}

//update counter (maybe trigger thunder hurt)
void counter_update(player* player1, player* player2){
  //All Counter Process
  if (player1->BE_UP != 0) {
    player1->BE_UP--;
  }
  if (player2->BE_UP != 0) {
    player2->BE_UP--;
  }
  if (player1->BE_RIGHT != 0) {
    player1->BE_RIGHT--;
  }
  if (player2->BE_RIGHT != 0) {
    player2->BE_RIGHT--;
  }
  if (player1->BE_LEFT != 0) {
    player1->BE_LEFT--;
  }
  
  if (player1->HP_LOSE != 0) {
    player1->HP_LOSE--;
    draw(1,player1->x,player1->y,1,0,ColD);
    draw(1,player1->x,player1->y,1,0,player1->mycolor);
  }
  if (player2->HP_LOSE != 0) {
    player2->HP_LOSE--;
    draw(1,player2->x,player2->y,1,0,ColD);
    draw(1,player2->x,player2->y,1,0,player2->mycolor);
  }
  if(player1->thunder_counter!=0){
    player1->thunder_counter--;
    if(player1->thunder_counter==0) {
       draw(3,player1->r-1, 31, player1->r+1,16,ColY);
       draw(3,player1->r-1, 31, player1->r+1,16,ColD);
       draw(3,player1->r-1,31,player1->r+1,31,ColD);
       //thunder: HP decrement
        if(if_player2_thunder(*player1, *player2)){
          draw(0, 31, 31, 0, 0, ColG);
          player2->HP_LOSE = INVINCIBLE_FRAME;
          player2->HP--;
          digitalWrite(12,HIGH);
        }
    }
  }
  if(player2->thunder_counter!=0){
    player2->thunder_counter--;
    if(player2->thunder_counter==0) {
       draw(3,player2->r-1, 0, player2->r+1,15,ColG);
       draw(3,player2->r-1, 0, player2->r+1,15,ColD);
       draw(3,player2->r-1,0,player2->r+1,15,ColD);
       //thunder: HP decrement
        if( if_player1_thunder(*player1, *player2)){
          draw(0, 31, 0, 0, 0, ColG);
          player1->HP_LOSE = INVINCIBLE_FRAME;
          player1->HP--;
          digitalWrite(11,HIGH);
        }
    }   
  }
}
