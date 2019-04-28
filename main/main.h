

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
    int BE_DOWN;     //bottom DOWN enable
    int heavy_usage;
    int light_usage;
    double thunder_counter;
    int r;                  //thunder position
}player;

//define bomb
typedef struct{
  int x;
  int y;
  int active;
  int counter;
}heavyBomb1;

typedef struct{
  int x;
  int y;
  int active; 
  int counter; 
}heavyBomb2;

typedef struct{
  int x;
  int y;
  int active;
  int counter;
}lightBomb1;

typedef struct{
  int x;
  int y;
  int active;  
  int counter;
}lightBomb2;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//pixel 0
//circle 1
//rec   2
//line 3
//screen 4

void draw (uint8_t T, uint8_t X, uint8_t Y, uint8_t SizeX, uint8_t SizeY, uint16_t Col){
    int delaytime = 0;   //Total Time = delay*8
  
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

}

void drawRec0(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint16_t Col){
  for(int xx=X1;xx<=X2;xx++){
      draw(0,xx,Y1,0,0,Col);  
  }
  for(int yy=Y1+1;yy<=Y2;yy++){
      draw(0,X2,yy,0,0,Col);
  }
  for(int xx=X2-1;xx>=X1;xx--){
      draw(0,xx,Y2,0,0,Col);  
  }
  for(int yy=Y2-1;yy>Y1;yy--){
      draw(0,X1,yy,0,0,Col);
  }
}

void drawRec1(uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint16_t Col){
  if(X1>X2 || Y1>Y2){return;}
  else{
     drawRec0(X1,Y1,X2,Y2,Col);
     drawRec1(X1+1,Y1+1,X2-1,Y2-1,Col);
  }
  
}

void drawArrow(int x, int y,color Col){
   draw(3,x,y+1,x,y-1,Col);
   draw(0,x+1,y,0,0,Col);  
  
}

void reset(){
    draw(4, 0,0,0,0,ColD);
    
}


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

             
