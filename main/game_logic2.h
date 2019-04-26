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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void perform_bottom_actions(player* player1, player* player2, heavyBomb1* heavyBombList1, heavyBomb2* heavyBombList2, lightBomb1* lightBombList1, lightBomb2* lightBombList2){
  //player 1 bottom
  //UP
  if (player1->UP==1 && (!player1->BE_UP)
      && player1->heavy_usage < HEAVY_BOMB_NUM)
  {
    heavyBombList1[0] = {player1->x, player1->y + 3, 1};
    player1->BE_UP = BE_UP_MAX;
    player1->heavy_usage++;

  }

  //RIGHT
  if (player1->RIGHT==1 && (!player1->BE_RIGHT)
      && player1->light_usage < LIGHT_BOMB_NUM)
  {
    if(player1->next_free_light>=LIGHT_BOMB_NUM*2){player1->next_free_light=0;}
    lightBombList1[player1->next_free_light] = {player1->x, player1->y + 2, 1};
    player1->next_free_light++;    
    player1->BE_RIGHT = BE_RIGHT_MAX;
    player1->light_usage++;
  }

  //LEFT
  if (player1->LEFT==1 && (!player1->BE_LEFT))
  {
     player1->r=randomGenerator();
     player1->BE_LEFT=BE_LEFT_MAX;
     player1->thunder_counter=thunder_counter_max;   
  }



  //player 2 bottom
  //UP
  if (player2->UP == 1 && (!player2->BE_UP)
      && player2->heavy_usage < HEAVY_BOMB_NUM)
  {
    heavyBombList2[0] = {player2->x, player2->y - 3, 1};   
    player2->BE_UP = BE_UP_MAX;
    player2->heavy_usage++;
  }

  //RIGHT
  if (player2->RIGHT == 1 && (!player2->BE_RIGHT)
      && player2->light_usage < LIGHT_BOMB_NUM)
  {
    if(player2->next_free_light>=LIGHT_BOMB_NUM*2){player2->next_free_light=0;}
    lightBombList2[player2->next_free_light] = {player2->x, player2->y - 2, 1};
    player2->next_free_light++;
    player2->BE_RIGHT = BE_RIGHT_MAX;
    player2->light_usage++;
  }

  //LEFT
  if (player2->LEFT == 1) {
     player2->r=randomGenerator();
     player2->BE_LEFT=BE_LEFT_MAX;
     player2->thunder_counter=thunder_counter_max; 
  }
  
}

void perform_player_movement(player* player1, player* player2){
  //player 1 movemetn
  if ((player1->moveX == -1) && (player1->x < 30)) {
    draw(1, player1->x, player1->y, 1, 0, ColD);
    player1->x++;
    draw(1, player1->x, player1->y, 1, 0, player1->mycolor);
  }
  if ((player1->moveX == 1) && (player1->x > 1)) {
    draw(1, player1->x, player1->y, 1, 0, ColD);
    player1->x--;
    draw(1, player1->x, player1->y, 1, 0, player1->mycolor);
  }
  if ((player1->moveY == 1) && (player1->y < 14)) {
    draw(1, player1->x, player1->y, 1, 0, ColD);
    player1->y++;
    draw(1, player1->x, player1->y, 1, 0, player1->mycolor);
  }
  if ((player1->moveY == -1) && (player1->y > 1)) {
    draw(1, player1->x, player1->y, 1, 0, ColD);
    player1->y--;
    draw(1, player1->x, player1->y, 1, 0, player1->mycolor);
  }

  //player 2 movement
  if ((player2->moveX == 1) && (player2->x < 30)) {
    draw(1, player2->x, player2->y, 1, 0, ColD);
    player2->x++;
    draw(1, player2->x, player2->y, 1, 0, player2->mycolor);
  }
  if ((player2->moveX == -1) && (player2->x > 1)) {
    draw(1, player2->x, player2->y, 1, 0, ColD);
    player2->x--;
    draw(1, player2->x, player2->y, 1, 0, player2->mycolor);
  }
  if ((player2->moveY == -1) && (player2->y < 30)) {
    draw(1, player2->x, player2->y, 1, 0, ColD);
    player2->y++;
    draw(1, player2->x, player2->y, 1, 0, player2->mycolor);
  }
  if ((player2->moveY == 1) && (player2->y > 17)) {
    draw(1, player2->x, player2->y, 1, 0, ColD);
    player2->y--;
    draw(1, player2->x, player2->y, 1, 0, player2->mycolor);
  }
  
}


void perform_bomb_movement(player* player1, player* player2, heavyBomb1* heavyBombList1, heavyBomb2* heavyBombList2, lightBomb1* lightBombList1, lightBomb2* lightBombList2){
  
  //heavy bomb movement & HP decrement//
    if (heavyBombList1[0].active == 1) {
      //update bomb location
      heavyBombList1[0].y++;
      //bomb disappear if touch edge
      if (heavyBombList1[0].y > 32) {
        heavyBombList1[0].active = 0;
        player1->heavy_usage--;
      }
      //draw bomb
      else {
        draw(0, heavyBombList1[0].x, heavyBombList1[0].y, 0, 0, ColY);
        draw(3, heavyBombList1[0].x - 1, heavyBombList1[0].y - 1, heavyBombList1[0].x + 1, heavyBombList1[0].y - 1, ColY);
      }
      //clear bomb trace
      draw(0, heavyBombList1[0].x, heavyBombList1[0].y - 1, 0, 0, ColD);
      draw(3, heavyBombList1[0].x - 1, heavyBombList1[0].y - 2, heavyBombList1[0].x + 1, heavyBombList1[0].y - 2, ColD);
      if (!player2->HP_LOSE && if_player2_shot_heavy(*player2, heavyBombList1[0])) {
        draw(0, 0, 0, 0, 0, 65535);
        player2->HP_LOSE = INVINCIBLE_FRAME;
        player2->HP--;
        digitalWrite(12,HIGH);
      }

    }

    if (heavyBombList2[0].active == 1) {
      //update bomb location
      heavyBombList2[0].y--;
      //bomb disappear if touch edge
      if (heavyBombList2[0].y < 0) {
        heavyBombList2[0].active = 0;
        player2->heavy_usage--;
      }
      //draw bomb
      else {
        draw(0, heavyBombList2[0].x, heavyBombList2[0].y, 0, 0, ColG);
        draw(3, heavyBombList2[0].x - 1, heavyBombList2[0].y + 1, heavyBombList2[0].x + 1, heavyBombList2[0].y + 1, ColG);
      }
      //clear bomb trace
      draw(0, heavyBombList2[0].x, heavyBombList2[0].y + 1, 0, 0, ColD);
      draw(3, heavyBombList2[0].x - 1, heavyBombList2[0].y + 2, heavyBombList2[0].x + 1, heavyBombList2[0].y + 2, ColD);


      if (!player1->HP_LOSE && if_player1_shot_heavy(*player1, heavyBombList2[0])) {
        draw(0, 31, 0, 0, 0, 65535);
        player1->HP_LOSE = INVINCIBLE_FRAME;
        player1->HP--;
        digitalWrite(11,HIGH);
        
      }


    }
  


  //light bomb movement & HP decrement//
  for (int i = 0; i < LIGHT_BOMB_NUM; i++)
  {
    if (lightBombList1[i].active == 1) {
      //update bomb location
      lightBombList1[i].y++;
      //bomb disappear if touch edge
      if (lightBombList1[i].y > 32) {
        lightBombList1[i].active = 0;
        player1->light_usage--;
      }
      //draw bomb
      else {
        draw(0, lightBombList1[i].x, lightBombList1[i].y, 0, 0, ColY);
      }
      //clear bomb trace
      draw(0, lightBombList1[i].x, lightBombList1[i].y - 1, 0, 0, ColD);


      if (!player2->HP_LOSE && if_player2_shot_light(*player2, lightBombList1[i])) {
        draw(0, 31, 0, 0, 0, 65535);
        player2->HP_LOSE = INVINCIBLE_FRAME;
        player2->HP--;
        digitalWrite(12,HIGH);
      }


    }
    if (lightBombList2[i].active == 1) {
      //update bomb location
      lightBombList2[i].y--;
      //bomb disappear if touch edge
      if (lightBombList2[i].y < 0) {
        lightBombList2[i].active = 0;
        player2->light_usage--;
      }
      //draw bomb
      else {
        draw(0, lightBombList2[i].x, lightBombList2[i].y, 0, 0, ColG);
      }
      //clear bomb trace
      draw(0, lightBombList2[i].x, lightBombList2[i].y + 1, 0, 0, ColD);

      if (!player1->HP_LOSE && if_player1_shot_light(*player1, lightBombList2[i])) {
        draw(0, 31, 31, 0, 0, 65535);
        player1->HP_LOSE = INVINCIBLE_FRAME;
        player1->HP--;
        digitalWrite(11,HIGH);
      }

    }

  }
    
}
