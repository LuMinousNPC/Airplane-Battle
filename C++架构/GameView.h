#pragma once
#include "View.h"
#include "button.h"
#include "global.h"
#include "EnemyManager.h"
#include "Bullet.h" 

class GameView : public View
{
public:
    GameView();
    ~GameView();

    // 视图生命周期函数（重写父类纯虚函数）
    void enter() override;     // 进入视图：初始化资源
    void update() override;    // 更新视图逻辑
    void draw() override;      // 绘制视图内容
    void handleInput(ExMessage& msg) override;  // 处理输入
    void quit() override;      // 退出视图：释放资源
	
	void resetGame();    // 重置游戏状态
	bool checkCollisions(); // 检查碰撞
    void drawGameUI(); // 绘制游戏 UI

private:
    
    EnemyManager enemyManager; // 敌人管理器​

    BulletManager bulletManager; // 添加子弹管理器
 

    float deltaTime;            // 时间增量​
    DWORD lastUpdateTime;       // 上次更新时间
    // 背景图片
    IMAGE background_img1;
    IMAGE background_img2;

};

