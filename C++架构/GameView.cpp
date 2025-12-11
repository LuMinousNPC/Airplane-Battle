#include "GameView.h"
#include "utils.h"
#include "global.h"
#include "viewManager.h"

IMAGE background_img1;       // 背景图
IMAGE background_img2;



void GameView::enter() {
	loadimage(&background_img1, "./Assert/images/Gane_Panel1.jpg");
    loadimage(&background_img2, "./Assert/images/Gane_Panel2.jpg");

    player.init();

}


void GameView::update() {
    
    player.update();

}


void GameView::draw() {
	cleardevice();

    //两张图片滚动粘贴

	static int y1 = -960;        
	static int y2 = -2880;
    int backgroundSpeed = 2;    // 背景滚动速度

    
    putimage(0, y1, &background_img1);
    putimage(0, y2, &background_img2);

   
    y1 += backgroundSpeed;
    y2 += backgroundSpeed;

    
    if (y1 >= 960) {
        y1 = -2880;
    }
    if (y2 >= 960) {
        y2 = -2880; 
    }


    player.draw();
}

void GameView::handleInput(ExMessage& msg) {
    gameState = GameState::PLAYING;
    if (player.isAlive==true&& msg.message != NULL) player.handleKey(msg);
	
}


void GameView::quit() {

}


void drawGameUI() {
    // 绘制玩家生命条
    player.drawHealthBar();
}