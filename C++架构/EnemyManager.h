#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <vector>
#include "Enemy.h"

// 前置声明
class Enemy;

// 敌人管理器类
class EnemyManager {
public:
    // 构造函数
    EnemyManager();

    // 析构函数
    ~EnemyManager();

    // 初始化
    void init();

    // 更新所有敌人
    void update(float deltaTime);

    // 绘制所有敌人
    void draw();

    // 生成敌人
    void spawnEnemy(EnemyType type, float x, float y);

    // 随机生成敌人
    void spawnRandomEnemy();

    // 清除所有敌人
    void clearEnemies();

    // 获取敌人列表
    const std::vector<Enemy*>& getEnemies() const;

    // 检查敌人与玩家的碰撞
    bool checkPlayerCollision(float playerX, float playerY, float playerWidth, float playerHeight);

    // 获取当前敌人数目
    int getEnemyCount() const;

private:
    // 敌人列表
    std::vector<Enemy*> enemies;

    // 敌人配置表
    std::vector<EnemyConfig> enemyConfigs;

    // 生成计时器
    float spawnTimer;

    // 基础生成间隔
    float baseSpawnInterval;

    // 生成间隔递减因子
    float spawnIntervalDecrement;

    // 最小生成间隔
    float minSpawnInterval;

    // 初始化敌人配置
    void initEnemyConfigs();

    // 清理无效敌人
    void cleanupEnemies();

    // 创建敌人实例
    Enemy* createEnemy(EnemyType type, const EnemyConfig& config, float x, float y);
};

#endif // ENEMY_MANAGER_H