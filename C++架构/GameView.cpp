#include "GameView.h"
#include "utils.h"
#include "global.h"
#include "viewManager.h"
#include <windows.h>


GameView::GameView()
    : deltaTime(0.0f), lastUpdateTime(0), currentScore(0){
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
    currentScore = 0;  // 重置当前分数
    

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
    // 检查子弹与敌人的碰撞
    handleBulletEnemyCollisions();
    
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
    drawScore();  // 绘制分数
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
        //  碰撞的敌机消失(checkPlayerCollision里实现)
        
        // 播放碰撞音效（如果有）
        if (ifSound) {
            playSound(1);
        }

        return true;
    }

    return false;
}
// 矩形碰撞检测实现
bool GameView::checkCollision(float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2) {
    return !(x1 + w1 < x2 ||
        x1 > x2 + w2 ||
        y1 + h1 < y2 ||
        y1 > y2 + h2);
}

// 处理子弹与敌人的碰撞
void GameView::handleBulletEnemyCollisions() {
    const auto& bullets = bulletManager.getBullets();
    const auto& enemies = enemyManager.getEnemies();

    // 遍历所有子弹
    for (auto bullet : bullets) {
        if (!bullet->isActive() || bullet->getType() != BulletType::PLAYER_BULLET) {
            continue;  // 只处理活跃的玩家子弹
        }

        // 获取子弹信息
        float bulletX = bullet->getX();
        float bulletY = bullet->getY();
        float bulletW = bullet->getWidth();
        float bulletH = bullet->getHeight();

        // 遍历所有敌人
        for (auto enemy : enemies) {
            if (!enemy->isActive()) {
                continue;  // 只处理活跃的敌人
            }

            // 获取敌人信息
            float enemyX = enemy->getX();
            float enemyY = enemy->getY();
            float enemyW = enemy->getWidth();
            float enemyH = enemy->getHeight();

            // 检查碰撞
            if (checkCollision(bulletX, bulletY, bulletW, bulletH,
                enemyX-0.5*enemyW, enemyY, enemyW, enemyH)) {
                onBulletHitEnemy(bullet, enemy);
                break;  // 一个子弹只能击中一个敌人
            }
        }
    }
}

// 子弹击中敌人的处理
void GameView::onBulletHitEnemy(Bullet* bullet, Enemy* enemy) {
    // 1. 子弹消失
    bullet->setActive(false);

    // 2. 敌人掉血（伤害值20）
    enemy->takeDamage(20);

    // 3. 检查敌人是否被击毁
    if (enemy->getHealth() <= 0) {
        enemy->setActive(false);
        
        //得分
        int enemyScore = 0;
        switch (enemy->getType()) {
        case EnemyType::NORMAL_PLANE: enemyScore = 100; break;  // 普通敌人
        case EnemyType::FAST_PLANE: enemyScore = 150; break;  // 快速敌人
        case EnemyType::ARMORED_PLANE: enemyScore = 200; break;  // 装甲敌人
        case EnemyType::BOSS_PLANE: enemyScore = 500; break;  // BOSS敌人
        default: enemyScore = 100; break;
        }

        currentScore += enemyScore;
    }
}
// 绘制分数
void GameView::drawScore() {
    // 设置文本样式
    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(20, 0, _T("微软雅黑"));

    // 绘制当前分数（左下角）
    TCHAR scoreText[50];
    _stprintf_s(scoreText, _T("分数: %d"), currentScore);
    outtextxy(20, WINDOW_HEIGHT - 40, scoreText);

}

// 绘制游戏结束界面
void GameView::drawGameOverScreen() {
    cleardevice();
    // 绘制背景
    putimage(0, 0, &setting_bk_image);
	
    // 绘制“游戏结束”文本
    settextcolor(RED);
    setbkmode(TRANSPARENT);
    settextstyle(50, 0, _T("微软雅黑"));
    outtextxy(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 100, _T("游戏结束"));
    // 绘制最终分数
    TCHAR scoreText[50];
    _stprintf_s(scoreText, _T("最终分数: %d"), currentScore);
    settextstyle(30, 0, _T("微软雅黑"));
    outtextxy(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2, scoreText);
    // 绘制提示文本
    settextstyle(20, 0, _T("微软雅黑"));
    outtextxy(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 + 50, _T("按任意键返回主菜单"));
    // 等待玩家按键
    ExMessage msg;
    while (true) {
        if (peekmessage(&msg, EM_KEY)) {
            break;  // 按键后退出循环
        }
    }
    // 返回主菜单
    view_manager.switch_to(ViewManager::ViewType::Menu);
}