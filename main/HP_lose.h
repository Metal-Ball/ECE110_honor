


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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


int if_player1_shot_light (player* player1, lightBomb2 lightBomb){
    if(abs(player1->x-lightBomb.x)<=1){
        if(abs(lightBomb.y-player1->y)==1){
            player1->HP_LOSE = INVINCIBLE_FRAME;
            player1->HP--;
            return 1;
        }
    }
    else{return 0;}
}


int if_player2_shot_light (player* player2, lightBomb1 lightBomb){
    if(abs(player2->x-lightBomb.x)<=1){
        if(abs(player2->y-lightBomb.y)==1){
            player2->HP_LOSE = INVINCIBLE_FRAME;
            player2->HP--;
            return 1;
        }
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
