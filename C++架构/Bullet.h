#pragma once
#pragma once
#include <graphics.h>
#include <string>

enum class BulletType {
    PLAYER_NORMAL,    // 玩家普通子弹
    PLAYER_LASER,     // 玩家激光
    PLAYER_MISSILE,   // 玩家导弹
    ENEMY_NORMAL,     // 敌人普通子弹
    ENEMY_BOSS        // BOSS子弹
};

class AdvancedBullet {
private:
    float x, y;               // 子弹中心坐标
    float speedX, speedY;     // 子弹速度
    int damage;              // 伤害值
    bool isActive;           // 是否活跃
    BulletType type;         // 子弹类型
    IMAGE* bulletImg;        // 子弹图片
    int width, height;       // 子弹尺寸

    // 特殊效果
    int homingTargetId;      // 追踪目标ID（用于追踪导弹）
    float rotation;          // 旋转角度

public:
    AdvancedBullet(float startX, float startY, float speedX, float speedY,
        BulletType type, int damage = 10, IMAGE* img = nullptr);

    void update();
    void draw();
    bool checkBoundary(int screenWidth, int screenHeight);
    void homingUpdate(float targetX, float targetY); // 追踪逻辑

    // Getter & Setter
    float getX() const { return x; }
    float getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getDamage() const { return damage; }
    bool getIsActive() const { return isActive; }
    BulletType getType() const { return type; }

    void setActive(bool active) { isActive = active; }
    void setHomingTarget(int targetId) { homingTargetId = targetId; }
};
