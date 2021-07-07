#pragma once 
class Player
{
private:
    float hit;
public:
    enum Players {
        PlayerX, PlayerY
    };
    const char* setPlayerName(Players player);
    
    void setHit(float hit);
    float getHit();
};

