typedef struct letter{
   int x;
   int y;
   color col; 
   int HP;
}letter;


void safeDraw(int x, int y, color Col) {
  if (x > 31 || x < 0) {
    return;
  }
  if (y > 31 || y < 0) {
    return;
  }
  draw(0, x, y, 0, 0, Col);

}


//x and y are the top left position of a 5*5 square of a letter
void drawA(letter letter_) {
  int x=letter_.x;
  int y=letter_.y;
  int Col=letter_.col;
  safeDraw(x, y + 1, Col);
  delay(1);
  safeDraw(x, y + 2, Col);
  delay(1);
  safeDraw(x, y + 3, Col);
  delay(1);
  safeDraw(x, y + 4, Col);
  delay(1);
  safeDraw(x + 1, y, Col);
  delay(1);
  safeDraw(x + 1, y + 2, Col);
  delay(1);
  safeDraw(x + 2, y, Col);
  delay(1);
  safeDraw(x + 2, y + 2, Col);
  delay(1);
  safeDraw(x + 3, y, Col);
  delay(1);
  safeDraw(x + 3, y + 2, Col);
  delay(1);
  safeDraw(x + 4, y + 1, Col);
  delay(1);
  safeDraw(x + 4, y + 2, Col);
  delay(1);
  safeDraw(x + 4, y + 3, Col);
  delay(1);
  safeDraw(x + 4, y + 4, Col);
  delay(1);
  //total delay 14

}

void drawG(letter letter_) {
  int x=letter_.x;
  int y=letter_.y;
  int Col=letter_.col;
  safeDraw(x, y + 1, Col);
  delay(1);
  safeDraw(x, y + 2, Col);
  delay(1);
  safeDraw(x, y + 3, Col);
  delay(1);
  safeDraw(x, y + 4, Col);
  delay(1);
  safeDraw(x + 1, y, Col);
  delay(1);
  safeDraw(x + 1, y + 4, Col);
  delay(1);
  safeDraw(x + 2, y, Col);
  delay(1);
  safeDraw(x + 2, y + 4, Col);
  delay(1);
  safeDraw(x + 3, y, Col);
  delay(1);
  safeDraw(x + 3, y + 2, Col);
  delay(1);
  safeDraw(x + 3, y + 4, Col);
  delay(1);
  safeDraw(x + 4, y + 2, Col);
  delay(1);
  safeDraw(x + 4, y + 3, Col);
  delay(1);
  safeDraw(x + 4, y + 4, Col);
  delay(1);

}

void drawI(letter letter_) {
  int x=letter_.x;
  int y=letter_.y;
  int Col=letter_.col;
  safeDraw(x + 1, y, Col);
  delay(1);
  safeDraw(x + 1, y + 4, Col);
  delay(1);
  safeDraw(x + 2, y, Col);
  delay(1);
  safeDraw(x + 2, y + 1, Col);
  delay(1);
  safeDraw(x + 2, y + 2, Col);
  delay(1);
  safeDraw(x + 2, y + 3, Col);
  delay(1);
  safeDraw(x + 2, y + 4, Col);
  delay(1);
  safeDraw(x + 3, y, Col);
  delay(1);
  safeDraw(x + 3, y + 4, Col);
  delay(1);
  delay(5);

}

void drawN(letter letter_) {
  int x=letter_.x;
  int y=letter_.y;
  int Col=letter_.col;
  safeDraw(x, y, Col);
  delay(1);
  safeDraw(x, y + 1, Col);
  delay(1);
  safeDraw(x, y + 2, Col);
  delay(1);
  safeDraw(x, y + 3, Col);
  delay(1);
  safeDraw(x, y + 4, Col);
  delay(1);
  safeDraw(x + 1, y + 1, Col);
  delay(1);
  safeDraw(x + 2, y + 2, Col);
  delay(1);
  safeDraw(x + 3, y + 3, Col);
  delay(1);
  safeDraw(x + 4, y, Col);
  delay(1);
  safeDraw(x + 4, y + 1, Col);
  delay(1);
  safeDraw(x + 4, y + 2, Col);
  delay(1);
  safeDraw(x + 4, y + 3, Col);
  delay(1);
  safeDraw(x + 4, y + 4, Col);
  delay(1);
  delay(1);
}

void perform_player2_movement(player* player2){
 
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
  
}

void perform_player2_bottom_actions(player* player2, heavyBomb2* heavyBombList2){
 if (player2->UP == 1 && (!player2->BE_UP)
      && player2->heavy_usage < HEAVY_BOMB_NUM)
  {
    for(int i=0; i<HEAVY_BOMB_NUM;i++){
        if(heavyBombList2[i].active==0){
              heavyBombList2[i] = {player2->x, player2->y - 3, 1,0};
              player2->BE_UP = BE_UP_MAX;
              player2->heavy_usage++; 
              break;
        }    
    }
  }

}

void perform_player2_bomb_movement(player* player2,heavyBomb2* heavyBombList2, letter* A, letter* G, letter* A2, letter* I,letter* N){
  //heavy bomb movement//
  for (int i = 0; i < HEAVY_BOMB_NUM; i++){
      if (heavyBombList2[i].active == 1) {
          if(heavyBombList2[i].counter==0){
            //update bomb location
            heavyBombList2[i].y--;
            //bomb disappear if touch edge
            if (heavyBombList2[i].y <=7) {
              heavyBombList2[i].active = 0;
              player2->heavy_usage--;
            }
            //draw bomb
            else {
              draw(0, heavyBombList2[i].x, heavyBombList2[i].y, 0, 0, ColG);
              draw(3, heavyBombList2[i].x - 1, heavyBombList2[i].y + 1, heavyBombList2[i].x + 1, heavyBombList2[i].y + 1, ColG);
            }
            //clear bomb trace
            draw(0, heavyBombList2[i].x, heavyBombList2[i].y + 1, 0, 0, ColD);
            draw(3, heavyBombList2[i].x - 1, heavyBombList2[i].y + 2, heavyBombList2[i].x + 1, heavyBombList2[i].y + 2, ColD);

    
            if(heavyBombList2[i].y <=7 && heavyBombList2[i].x >=1 && heavyBombList2[i].x <=5){
                A->col-=2000;
                A->HP--;
                drawA(*A);
            }
            
           if(heavyBombList2[i].y <=7 && heavyBombList2[i].x >=6 && heavyBombList2[i].x <=12){
                G->col-=2000;
                drawG(*G);
            }


            if(heavyBombList2[i].y <=7 && heavyBombList2[i].x >=13 && heavyBombList2[i].x <=18){
                A2->col-=2000;
                drawA(*A2);
            }
            
            if(heavyBombList2[i].y <=7 && heavyBombList2[i].x >=19 && heavyBombList2[i].x <=24){
                I->col-=2000;
                drawI(*I);
            }

            if(heavyBombList2[i].y <=7 && heavyBombList2[i].x >=25 && heavyBombList2[i].x <=30){
                N->col-=2000;
                drawN(*N);
            }
            
            heavyBombList2[i].counter=HEAVY_BOMB_COUNTER;
          }
          else{heavyBombList2[i].counter--;}

      }
  }
}



int retry(player* player1, player* player2, heavyBomb2* heavyBombList2) {
  player1->x=33;
  player1->y=33;
  reset();
  
  for (int i = 0; i < HEAVY_BOMB_NUM; i++) {
    heavyBombList2[i] = { -1, -1, 0};
  }
  
  letter A, G, A2, I, N;
  A={1,2,10000,3};
  G={7,2,20000,3};
  A2={13,2,30000,3};
  I={19,2,40000,3};
  N={25,2,50000,3};
  drawA(A);
  drawG(G);
  drawA(A2);
  drawI(I);
  drawN(N);
  *player2 = {15, 30, 0, 0, 0, 0, 0, 0, 3, 0, ColB, 0, 0, 0, 0, -99};
  draw(1,player2->x,player2->y,1,0,player2->mycolor);
  int flag;
  while(1){
      delay(5);
      counter_update(player1, player2);
      joysticksIO(player1, player2);  
      perform_player2_movement(player2);
      perform_player2_bottom_actions(player2, heavyBombList2);
      perform_player2_bomb_movement(player1,heavyBombList2, &A, &G, &A2, &I, &N);
      if(A.HP==0){flag=0; break;}
  }
   
  if(flag==0){
     draw(5,0,0,6,32,ColD);
     A.col=ColD;
     drawA(A);
     int speed=100;
     while(1){
        draw(1,player2->x,player2->y,1,0,ColD);
        player2->y--;
        if(player2->y<=0){break;}  
        draw(1,player2->x,player2->y,1,0,player2->mycolor);
        delay(speed);
        speed-=3;
        
     }
  }



  
  return flag;
  
}
