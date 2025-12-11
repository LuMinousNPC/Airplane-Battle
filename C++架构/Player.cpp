
#include "utils.h"

#include "global.h"

#include <iostream>

#include"SettingView.h"

#include"Player.h"

//初始化玩家参数
Player::Player() : x(0), y(0), width(50), height(50), health(100),speed(3), isAlive(true) {
}

void Player::init() {
    loadimage(&playerImg, "./Assert/images/player_plan.png",width,height);

    width = playerImg.getwidth();    
    height = playerImg.getheight();  

    

    x = WINDOW_WIDTH / 2;
    y = WINDOW_HEIGHT - 150;

    health = 100;
    isAlive = true;
}

void Player::handleKey(ExMessage& msg) {
    if (MouseHit()) {
        
        // 直接跟随鼠标
        x = msg.x;
        y = msg.y;

    }

    //防止溢出
    if (x < width / 2) x = width / 2;
    if (x > WINDOW_WIDTH - width / 2) x = WINDOW_WIDTH - width / 2;
    if (y < height / 2) y = height / 2;
    if (y > WINDOW_HEIGHT - height / 2) y = WINDOW_HEIGHT - height / 2;
}

void Player::update() {
    


}


// 绘制玩家
void Player::draw() {
    if (!isAlive) return;

    
    int drawX = x - width / 2;
    int drawY = y - height / 2;

    putimage_new(drawX, drawY, &playerImg);

    // 绘制生命值条
    drawHealthBar();
}

// 绘制生命值条
void Player::drawHealthBar() {
    int barWidth = 50;
    int barHeight = 6;
    int barX = x - barWidth / 2;
    int barY = y - height / 2 - 15;

    // 背景（红色）
    setfillcolor(RGB(255, 0, 0));
    fillrectangle(barX, barY, barX + barWidth, barY + barHeight);

    // 当前生命值（绿色）
    int currentWidth = barWidth * health / 100;
    setfillcolor(RGB(0, 255, 0));
    fillrectangle(barX, barY, barX + currentWidth, barY + barHeight);

    // 边框
    setlinecolor(WHITE);
    rectangle(barX, barY, barX + barWidth, barY + barHeight);
}

//射击
void Player::shoot() {
    float bulletX = x;
    float bulletY = y - height / 2;
    //写好子弹管理了以后解除注释
    //bulletManager.createPlayerBullet(bulletX, bulletY, bulletLevel);
}
// 玩家受伤
void Player::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        isAlive = false;
        // 可以在这里触发死亡动画或效果
    }
}
