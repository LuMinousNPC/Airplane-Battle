#ifndef PLAYER_H
#define PLAYER_H 

#include <string>
#include <vector>
#include <utility>
#include <graphics.h> 

using namespace std;


class Player {
public:
    // 构造函数
    Player();

    // 初始化玩家
    void init();

    // 更新玩家位置（跟随鼠标）
    void update();

    // 处理人物按键（鼠标输入）
    void handleKey(ExMessage& msg);

    // 绘制玩家（使用你的putimage_new函数）
    void draw();
    void drawHealthBar();
    // 获取玩家位置和状态信息
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getHealth() const { return health; }
    bool getIsAlive() const { return isAlive; }

    // 设置生命值
    void setHealth(int hp) { health = hp; if (health <= 0) isAlive = false; }

    // 受伤
    void takeDamage(int damage);
    
    //射击
    void shoot();

    
    
    bool isAlive;               // 是否存活
private:
    int x, y;                   // 玩家中心坐标
    int width, height;          // 玩家图片尺寸
    IMAGE playerImg;            // 玩家飞机图片
    int health;                 // 玩家生命值
    int speed;                  // 玩家速度
    
};

#endif