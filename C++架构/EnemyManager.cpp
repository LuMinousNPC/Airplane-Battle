#include "EnemyManager.h"
#include <algorithm>
#include <cstdlib>



EnemyManager::EnemyManager()
    : spawnTimer(0.0f), baseSpawnInterval(2.0f),
    spawnIntervalDecrement(0.01f), minSpawnInterval(0.5f) {
}

EnemyManager::~EnemyManager() {
    clearEnemies();
}

void EnemyManager::init() {
    initEnemyConfigs();
    spawnTimer = 0.0f;
}

void EnemyManager::initEnemyConfigs() {
    // 清除现有配置
    enemyConfigs.clear();

    // 普通飞机配置
    enemyConfigs.push_back({
        "./Assert/images/plane_normal.png",  // 图片路径
        60, 40,         // 宽高
        30,             // 生命值
        2.0f,           // 速度
        100,            // 得分
        40              // 生成权重
        });

    // 快速飞机配置
    enemyConfigs.push_back({
        "./Assert/images/plane_fast.png",    // 图片路径
        50, 35,         // 宽高
        15,             // 生命值
        4.0f,           // 速度
        150,            // 得分
        25              // 生成权重
        });

    // 装甲飞机配置
    enemyConfigs.push_back({
        "./Assert/images/plane_armored.png", // 图片路径
        70, 50,         // 宽高
        60,             // 生命值
        1.5f,           // 速度
        200,            // 得分
        20              // 生成权重
        });

    // BOSS飞机配置
    enemyConfigs.push_back({
        "./Assert/images/plane_boss.png",    // 图片路径
        120, 80,        // 宽高
        200,            // 生命值
        1.0f,           // 速度
        500,            // 得分
        5               // 生成权重
        });

    // 小陨石配置
    enemyConfigs.push_back({
        "./Assert/images/meteor_small.png",  // 图片路径
        40, 40,         // 宽高
        1,              // 生命值
        3.0f,           // 速度
        50,             // 得分
        15              // 生成权重
        });

    // 大陨石配置
    enemyConfigs.push_back({
        "./Assert/images/meteor_large.png",  // 图片路径
        80, 80,         // 宽高
        200,              // 生命值
        2.0f,           // 速度
        100,            // 得分
        10              // 生成权重
        });
}

Enemy* EnemyManager::createEnemy(EnemyType type, const EnemyConfig& config, float x, float y) {
    // 根据类型创建不同的敌人实例
    // 这里可以扩展为具体的敌人子类
    return new Enemy(type, config, x, y);
}

void EnemyManager::update(float deltaTime) {
    // 更新生成计时器
    spawnTimer += deltaTime;

    // 计算当前生成间隔（随着游戏进行逐渐缩短）
    // 将复杂计算拆分为两行
    float calculatedInterval = baseSpawnInterval - (spawnIntervalDecrement * spawnTimer);
    float currentSpawnInterval = (std::max)(calculatedInterval, minSpawnInterval);

    // 检查是否需要生成敌人
    if (spawnTimer >= currentSpawnInterval) {
        spawnRandomEnemy();
        spawnTimer = 0.0f;
    }

    // 更新所有敌人
    for (auto& enemy : enemies) {
        if (enemy->isActive()) {
            enemy->update(deltaTime);

            // 检查边界
            if (enemy->checkBoundary()) {
                enemy->setActive(false);
            }
        }
    }

    // 清理无效敌人
    cleanupEnemies();
}

void EnemyManager::draw() {
    for (auto& enemy : enemies) {
        if (enemy->isActive()) {
            enemy->draw();
        }
    }
}

void EnemyManager::spawnEnemy(EnemyType type, float x, float y) {
    // 查找对应的配置
    if (static_cast<int>(type) >= enemyConfigs.size()) {
        return;
    }

    const EnemyConfig& config = enemyConfigs[static_cast<int>(type)];

    // 创建敌人
    Enemy* enemy = createEnemy(type, config, x, y);
    if (enemy != nullptr) {
        enemies.push_back(enemy);
    }
}

void EnemyManager::spawnRandomEnemy() {
    // 计算总权重
    int totalWeight = 0;
    for (const auto& config : enemyConfigs) {
        totalWeight += config.spawnWeight;
    }

    if (totalWeight <= 0) {
        return;
    }

    // 随机选择一个权重
    int randomWeight = rand() % totalWeight;
    int currentWeight = 0;
    int selectedIndex = 0;

    // 找到对应的敌人类型
    for (int i = 0; i < enemyConfigs.size(); i++) {
        currentWeight += enemyConfigs[i].spawnWeight;
        if (randomWeight < currentWeight) {
            selectedIndex = i;
            break;
        }
    }

    // 生成随机X坐标（确保敌人完全在屏幕内）
    const EnemyConfig& config = enemyConfigs[selectedIndex];
    float spawnX = static_cast<float>(rand() % (WINDOW_WIDTH - config.width)) +
        static_cast<float>(config.width) / 2.0f;
    float spawnY = -config.height / 2;  // 从屏幕顶部外开始

    // 生成敌人
    spawnEnemy(static_cast<EnemyType>(selectedIndex), spawnX, spawnY);
}

void EnemyManager::clearEnemies() {
    for (auto& enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}

const std::vector<Enemy*>& EnemyManager::getEnemies() const {
    return enemies;
}

bool EnemyManager::checkPlayerCollision(float playerX, float playerY, float playerWidth, float playerHeight) {
    for (auto& enemy : enemies) {
        if (enemy->isActive()) {
            // 简单的矩形碰撞检测
            float enemyLeft = enemy->getX() - enemy->getWidth() / 2;
            float enemyRight = enemy->getX() + enemy->getWidth() / 2;
            float enemyTop = enemy->getY() - enemy->getHeight() / 2;
            float enemyBottom = enemy->getY() + enemy->getHeight() / 2;

            float playerLeft = playerX - playerWidth / 2;
            float playerRight = playerX + playerWidth / 2;
            float playerTop = playerY - playerHeight / 2;
            float playerBottom = playerY + playerHeight / 2;

            if (!(enemyLeft > playerRight || enemyRight < playerLeft ||
                enemyTop > playerBottom || enemyBottom < playerTop)) {
                // 2. 碰撞的敌机消失
                enemy->setActive (false);
                return true;
            }
        }
    }
    return false;
}

int EnemyManager::getEnemyCount() const {
    int count = 0;
    for (const auto& enemy : enemies) {
        if (enemy->isActive()) {
            count++;
        }
    }
    return count;
}

void EnemyManager::cleanupEnemies() {
    // 使用erase-remove惯用法清理无效敌人
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](Enemy* enemy) {
            if (!enemy->isActive()) {
                delete enemy;
                return true;
            }
            return false;
        }), enemies.end());
}