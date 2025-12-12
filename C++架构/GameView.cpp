#include "GameView.h"
#include "utils.h"
#include "global.h"
#include "viewManager.h"
#include <windows.h>


GameView::GameView()
    : deltaTime(0.0f), lastUpdateTime(0) {
    // 构造函数初始化
}

GameView::~GameView() {
    // 析构函数
}

void GameView::enter() {
    loadimage(&background_img1, "./Assert/images/Game_Panel1.jpg");
    loadimage(&background_img2, "./Assert/images/Game_Panel2.jpg");
    enemyManager.init();
    player.init();
    bulletManager.setAutoFire(true, 0.5f);

    resetGame();
}

void GameView::update() {
    player.update();
    // 更新自动射击
    bulletManager.updateAutoFire (deltaTime, player.getX (), player.getY ());
    bulletManager.update(deltaTime);
    // 计算deltaTime
    DWORD currentTime = GetTickCount();
    deltaTime = static_cast<float>(currentTime - lastUpdateTime) / 1000.0f;
    lastUpdateTime = currentTime;

    // 更新敌人系统
    enemyManager.update(deltaTime);

    // 检查碰撞
    checkCollisions();
}

void GameView::draw() {
    cleardevice();

    // 两张图片滚动粘贴
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
    bulletManager.draw();
    enemyManager.draw();
    player.draw();
    drawGameUI();
}

void GameView::handleInput(ExMessage& msg) {
    gameState = GameState::PLAYING;
    if (player.isAlive && msg.message != NULL) {
        player.handleKey(msg);
    }
}

void GameView::quit() {
    enemyManager.clearEnemies();
}

// 绘制游戏UI
void GameView::drawGameUI() {
    

}

// 重置游戏
void GameView::resetGame() {
    // 重置玩家
    player.init();

    // 清除所有敌人
    enemyManager.clearEnemies();

    // 重置时间
    lastUpdateTime = GetTickCount();
}

// 检查碰撞
bool GameView::checkCollisions() {
    if (!player.isAlive) return false;

    // 检查玩家与敌人的碰撞
    bool collision = enemyManager.checkPlayerCollision(
        player.getX(), player.getY(),
        player.getWidth(), player.getHeight());

    if (collision) {
        // 玩家受伤处理
        player.takeDamage(20);  // 示例伤害值

        // 播放碰撞音效（如果有）
        if (ifSound) {
            playSound(1);
        }

        return true;
    }

    return false;
}