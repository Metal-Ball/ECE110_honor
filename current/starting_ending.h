//define bottom enable counter upper bound: leaving time for actions
//bottom enable: 0 means active
#define BE_UP_MAX 20
#define BE_RIGHT_MAX 5
#define BE_LEFT_MAX 100
////////////////////////////////////////////////////////////////////////////////////////////////////
//pixel 0
//circle 1
//rec   2
//line 3
//screen 4

void reset(){
    draw(4, 0,0,0,0,ColD);
    
}
void print_welcome_message(){
    reset();
    
    draw(2,0,0,31,15,ColY);
    draw(0,1,25,0,0,ColY);
    draw(0,5,25,0,0,ColY);
    draw(0,1,29,0,0,ColY);
    draw(0,5,29,0,0,ColY);
    
    draw(0,26,25,0,0,ColY);
    draw(0,30,25,0,0,ColY);
    draw(0,26,29,0,0,ColY);
    draw(0,30,29,0,0,ColY);
    
    return;
}


void game_ready(player* player1, player* player2){
    print_welcome_message();
    delay(50);
    int player1_is_ready=0;
    int player2_is_ready=0;
    while(1){
      joysticksIO(player1,player2);
      if(!player1_is_ready){
         if(player1->UP==1){
            player1_is_ready=1;
            draw(0,31,31,0,0,ColR);
         }
      }
      if(!player2_is_ready){
         if(player2->UP==1){
            player2_is_ready=1;
            draw(0,0,0,0,0,ColB);
         }
      }
      
      if(player1_is_ready && player2_is_ready){break;}
    }
}



void game_start(player player1, player player2){
    //TODO: INSERT YOUR CODE HERE
    
    delay(1000);
    reset();
    delay(100);
    draw(1,player1.x,player1.y,1,0,player1.mycolor);
    draw(1,player2.x,player2.y,1,0,player2.mycolor);
    delay(1000);
    
    
}



void game_player1_wins(player player1, player player2){
    //TODO: INSERT YOUR CODE HERE
    
    int a,b,c,d,e,f,g,h,i,j,k,l,m,n;
    for(a=23;a<=31;a++)
    {
        draw(0,31,a,0,0,ColR);
    }
    draw(0,30,31,0,0,ColR);
    draw(0,29,30,0,0,ColR);
    draw(0,28,29,0,0,ColR);
    draw(0,29,28,0,0,ColR);
    draw(0,30,27,0,0,ColR);
    draw(0,27,30,0,0,ColR);
    draw(0,26,31,0,0,ColR);
    draw(0,25,31,0,0,ColR);
    for(b=25;b<=31;b++)
    {
        draw(0,25,b,0,0,ColR);
    }
    for(b=25;b<=31;b++)
    {
        draw(0,25,b,0,0,ColR);
    }
    for(c=27;c<=23;c++)
    {
        draw(0,c,25,0,0,ColR);
    }
    for(d=29;d<=31;d++)
    {
        draw(0,21,d,0,0,ColR);
    }
    draw(0,20,28,0,0,ColR);
    draw(0,20,27,0,0,ColR);
    draw(0,19,26,0,0,ColR);
    draw(0,19,25,0,0,ColR);
    for(e=26;e<=28;e++)
    {
        draw(0,18,d,0,0,ColR);
    }
    for(f=26;f<=28;f++)
    {
        draw(0,17,f,0,0,ColR);
    }
    draw(0,16,26,0,0,ColR);
    draw(0,16,25,0,0,ColR);
    draw(0,15,27,0,0,ColR);
    draw(0,15,28,0,0,ColR);
    for(g=29;g<=31;g++)
    {
        draw(0,13,g,0,0,ColR);
    }
    for(h=8;h<=12;h++)
    {
        draw(0,h,31,0,0,ColR);
    }
    for(i=25;i<=31;i++)
    {
        draw(0,10,i,0,0,ColR);
    }
    for(h=8;h<=12;h++)
    {
        draw(0,h,25,0,0,ColR);
    }
    for(j=25;j<=31;j++)
    {
        draw(0,6,j,0,0,ColR);
    }
    for(k=25;k<=31;k++)
    {
        draw(0,2,k,0,0,ColR);
    }
    draw(0,5,30,0,0,ColR);
    draw(0,4,29,0,0,ColR);
    draw(0,4,28,0,0,ColR);
    draw(0,4,27,0,0,ColR);
    draw(0,3,26,0,0,ColR);
    
}

void game_player2_wins(player player1, player player2){
    //TODO: INSERT YOUR CODE HERE
    int a,b,c,d,e,f,g,h,i,j,k,l,m,n;
    for(a=0;a<=6;a++)
    {
        draw(0,0,a,0,0,ColB);
    }
    draw(0,1,0,0,0,ColB);
    draw(0,2,1,0,0,ColB);
    draw(0,3,2,0,0,ColB);
    draw(0,2,3,0,0,ColB);
    draw(0,1,4,0,0,ColB);
    draw(0,4,1,0,0,ColB);
    draw(0,5,0,0,0,ColB);
    draw(0,6,0,0,0,ColB);
    draw(0,7,0,0,0,ColB);
    draw(0,8,1,0,0,ColB);
    draw(0,8,2,0,0,ColB);
    draw(0,7,3,0,0,ColB);
    draw(0,6,4,0,0,ColB);
    draw(0,5,4,0,0,ColB);
    draw(0,4,5,0,0,ColB);
    draw(0,4,6,0,0,ColB);
    for(b=5;b<=8;b++)
    {
        draw(0,b,6,0,0,ColB);
    }
    draw(0,10,0,0,0,ColB);
    draw(0,10,1,0,0,ColB);
    draw(0,10,2,0,0,ColB);
    draw(0,11,3,0,0,ColB);
    draw(0,11,4,0,0,ColB);
    draw(0,12,5,0,0,ColB);
    draw(0,12,6,0,0,ColB);
    for(c=3;c<=5;c++)
    {
        draw(0,13,c,0,0,ColB);
    }
    for(d=3;d<=5;d++)
    {
        draw(0,14,d,0,0,ColB);
    }
    draw(0,15,5,0,0,ColB);
    draw(0,15,6,0,0,ColB);
    draw(0,16,3,0,0,ColB);
    draw(0,16,4,0,0,ColB);
    for(e=0;e<=2;e++)
    {
        draw(0,17,e,0,0,ColB);
    }
    for(f=19;f<=23;f++)
    {
        draw(0,f,0,0,0,ColB);
    }
    for(g=0;g<=6;f++)
    {
        draw(0,21,g,0,0,ColB);
    }
    for(h=19;h<=24;h++)
    {
        draw(0,h,6,0,0,ColB);
    }
    for(i=0;i<=6;f++)
    {
        draw(0,25,i,0,0,ColB);
    }
    for(j=0;j<=6;j++)
    {
        draw(0,29,0,0,0,ColB);
    }
    draw(0,26,1,0,0,ColB);
    draw(0,27,2,0,0,ColB);
    draw(0,27,3,0,0,ColB);
    draw(0,27,4,0,0,ColB);
    draw(0,28,5,0,0,ColB);
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////
