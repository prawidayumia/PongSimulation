#include"Player.h" //include class player
#include"Score.h" //include class score
#include<chrono> //include lib chrono
#include<future> //include lib future
#include<iostream> //include lib iostream 

using namespace std;

Player getHit(Player* player) {
    int* temp = new int; // alokasi memory tipe data int
    srand((int)temp); //fungsi random
    delete temp;//realease alamat memory
    float result = rand() % 100 + 1; // random hit
    player->setHit(result); // set hit player
    return *player; // return player
}

int main() {
    
    // Instance Score
    Score score;
    score.setScorePlayerX(0);
    score.setScorePlayerY(0);
    
    //instance player
    Player playerX = Player();
    const char* playerXName = playerX.setPlayerName(playerX.PlayerX);
    //copy player
    Player playerY = playerX;
    const char* playerYName = playerY.setPlayerName(playerY.PlayerY);

    int scorePlayerX = 0, scorePlayerY = 0;
    float playerXHit, playerYHit;

    //game loop
    while (1) {
        //random untuk menentukan player x atau player y dulu yang main
        float first = rand() % 1;
    back:
        //jika player x yang main dulu
        if (first == 0) {
            // jalankan thread pada fungsi gethit yang mempunyai parameter player dan return object player
            auto future_playerX = async(getHit, &playerX); 
            //get data hit pada fungsi gethit
            playerXHit = future_playerX.get().getHit();

            // jalankan thread pada fungsi gethit yang mempunyai parameter player dan return object player
            auto future_playerY = async(getHit, &playerY);
            //get data hit pada fungsi gethit
            playerYHit = future_playerY.get().getHit();
        }
        //jika player y yang main dulu
        else if (first == 1) {
            // jalankan thread pada fungsi gethit yang mempunyai parameter player dan return object player
            auto future_playerY = async(getHit, &playerY);
            //get data hit pada fungsi gethit
            playerYHit = future_playerY.get().getHit();
            // jalankan thread pada fungsi gethit yang mempunyai parameter player dan return object player
            auto future_playerX = async(getHit, &playerX);
            //get data hit pada fungsi gethit
            playerXHit = future_playerX.get().getHit();
        }

        //jika hit kedua player lebih dati 50 maka kembali ke state back
        if (playerXHit > 50 && playerYHit > 50) {
            cout << "Back!" << endl;
            cout << "Player X Hit : " << playerXHit << endl;
            cout << "Player Y Hit : " << playerYHit << endl;
            goto back;
        }
        //jika hit kedua player kurang dati 50 maka kembali ke state back
        else if (playerXHit <= 50 && playerYHit <= 50) {
            cout << "Back!" << endl;
            cout << "Player X Hit : " << playerXHit << endl;
            cout << "Player Y Hit : " << playerYHit << endl;
            goto back;
        }
        else {
            if (playerXHit <= 50) { //jika hit player kurang dari 50 maka berikan score ke lawannya
                scorePlayerY++;
            }
            else {
                scorePlayerX++;
            }
        }

        cout << "Player X Hit : " << playerXHit << endl;
        cout << "Player Y Hit : " << playerYHit << endl;
        cout << "Score X : " << scorePlayerX << endl;
        cout << "Score Y : " << scorePlayerY << endl;

        std::this_thread::sleep_for(std::chrono::seconds(3)); // jeda 3 detik
        system("cls"); //clear window

        //jika score salah satu player mencapai 10 
        if (scorePlayerX == 10 || scorePlayerY == 10) {
            score.setScorePlayerX(scorePlayerX); // set score player x
            score.setScorePlayerY(scorePlayerY); // set score player y
            break; // keluar dari game loop
        }
    }
    
    if (score.getScorePlayerX() == 10) {
        cout << "Player X Win" << endl;
        cout << "Score X : " << score.getScorePlayerX() <<endl;
        cout << "Score Y : " << score.getScorePlayerY() <<endl;
    }
    else if (score.getScorePlayerY() == 10) {
        cout << "Player Y Win" << endl;
        cout << "Score X : " << score.getScorePlayerX() <<endl;
        cout << "Score Y : " << score.getScorePlayerY() <<endl;
    }

    system("pause");
    return 0;
}
