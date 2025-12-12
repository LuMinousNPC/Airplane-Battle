#ifndef ENEMY_H
#define ENEMY_H

#include <graphics.h>
#include <string>
#include "global.h"
#include "utils.h"

// 敌人类型枚举
enum class EnemyType {
    NORMAL_PLANE,       // 普通飞机
    FAST_PLANE,         // 快速飞机
    ARMORED_PLANE,      // 装甲飞机
    BOSS_PLANE,         // BOSS飞机
    SMALL_METEOR,       // 小陨石
    LARGE_METEOR        // 大陨石
};

// 敌人配置结构体
struct EnemyConfig {
    std::string imagePath;  // 图片路径
    int width;              // 宽度
    int height;             // 高度
    int health;             // 生命值
    float speed;            // 移动速度
    int scoreValue;         // 得分值
    int spawnWeight;        // 生成权重
};

// 敌人基类
class Enemy {
public:
    // 构造函数
    Enemy(EnemyType type, const EnemyConfig& config, float x, float y);

    // 析构函数
    virtual ~Enemy();

    // 更新敌人状态
    virtual void update(float deltaTime);

    // 绘制敌人
    virtual void draw();

    // 检查边界
    virtual bool checkBoundary();

    // 受伤处理
    virtual void takeDamage(int damage);

    // 重置敌人
    virtual void reset(float x, float y);

    // Getter方法
    EnemyType getType() const { return type; }
    float getX() const { return x; }
    float getY() const { return y; }
    int getWidth() const { return config.width; }
    int getHeight() const { return config.height; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return config.health; }
    int getScoreValue() const { return config.scoreValue; }
    bool isActive() const { return isActiveFlag; }

    // Setter方法
    void setActive(bool active) { isActiveFlag = active; }

protected:
    // 敌人类型
    EnemyType type;

    // 敌人配置
    EnemyConfig config;

    // 位置
    float x;
    float y;

    // 移动速度
    float speedX;
    float speedY;

    // 生命值
    int health;

    // 活跃状态
    bool isActiveFlag;

    // 图片资源
    IMAGE enemyImage;

    // 初始化图片
    void initImage();

    // 更新移动
    virtual void updateMovement(float deltaTime);

    // 更新AI行为
    virtual void updateAI(float deltaTime);

    // 绘制生命值条
    void drawHealthBar();
};

#endif // ENEMY_H