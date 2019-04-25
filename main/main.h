
#define ColW 65535 //white
#define ColR 63488 //red
#define ColG 2016 //green
#define ColB 31 //blue
#define ColD 0 //dark
#define ColY 38020 //yellow



#include <stdlib.h>
#include <time.h>





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//define color
typedef uint16_t color;

//define player
typedef struct{
    int x;       //x position
    int y;       //y position
    int moveX;   //x movement
    int moveY;   //y movement
    int UP;      //UP bottom
    int LEFT;    //LEFT bottom
    int RIGHT;   //RIGHT bottom
    int DOWN;    //DOWN bottom
    int HP;      
    int HP_LOSE;     
    color mycolor;  
    int BE_UP;      //bottom UP enable  
    int BE_RIGHT;    //bottom RIGHT enable
    int BE_LEFT;     //bottom LEFT enable
    int heavy_usage;
    int light_usage;
    int thunder_counter;
    int r;                  //thunder position
    int next_free_light;
}player;

//define bomb
typedef struct{
  int x;
  int y;
  int active;
}heavyBomb1;

typedef struct{
  int x;
  int y;
  int active;  
}heavyBomb2;

typedef struct{
  int x;
  int y;
  int active;
}lightBomb1;

typedef struct{
  int x;
  int y;
  int active;  
}lightBomb2;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//pixel 0
//circle 1
//rec   2
//line 3
//screen 4

void draw (uint8_t T, uint8_t X, uint8_t Y, uint8_t SizeX, uint8_t SizeY, uint16_t Col){
    int delaytime = 1;   //Total Time = delay*8
  
    Serial.write(254);
    delay(delaytime);
    Serial.write(X);
    delay(delaytime);
    Serial.write(Y);
    delay(delaytime);
    Serial.write(SizeX);
    delay(delaytime);
    Serial.write(SizeY);
    delay(delaytime);
    Serial.write(Col/256);
    delay(delaytime);
    Serial.write(Col%256);
    delay(delaytime);
    Serial.write(T);
    delay(delaytime);
/*

    Serial.print(254);
    Serial.print(" X ");
    Serial.print(X);
    Serial.print(" Y ");
    Serial.print(Y);
    Serial.print(" SizeX ");
    Serial.print(SizeX);
    Serial.print(" SizeY ");
    Serial.print(SizeY);
    Serial.print(" Col ");
    Serial.print(Col);
    Serial.print(" Type ");
    Serial.println(T);
  */ 
}





int if_player1_shot_heavy (player player1, heavyBomb2 heavyBomb){
   if(abs(player1.x-heavyBomb.x)<=2){
      if(abs(player1.y-heavyBomb.y)<=1){return 1;}
   }
   else{return 0;}

}

int if_player2_shot_heavy (player player2, heavyBomb1 heavyBomb){
   if(abs(player2.x-heavyBomb.x)<=2){
      if(abs(player2.y-heavyBomb.y)<=1){return 1;}
   }
   else{return 0;}
}


int if_player1_shot_light (player player1, lightBomb2 lightBomb){
   if(abs(player1.x-lightBomb.x)<=1){
      if(abs(player1.y-lightBomb.y)<=1){return 1;}
   }
   else{return 0;}
}


int if_player2_shot_light (player player2, lightBomb1 lightBomb){
   if(abs(player2.x-lightBomb.x)<=1){
      if(abs(player2.y-lightBomb.y)<=1){return 1;}
   }
   else{return 0;}
}

int if_player1_thunder(player player1, player player2){
   if(abs(player1.x-player2.r)<=2){
      return 1; 
  }
  return 0;
}

int if_player2_thunder(player player1, player player2){
  if(abs(player2.x-player1.r)<=2){
     return 1;  
  }
  return 0;
}

//generate a int between 1 and 31
int randomGenerator(){
  
  int r = 1+rand()%30;      
  return r;
  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Ram Uesage
#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else // __ARM__
extern char *__brkval;
#endif // __arm__

int freeMemory() {
char top;
#ifdef __arm__
return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
return &top - __brkval;
#else // __arm__
return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif // __arm__
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//some rubbish and junks

             