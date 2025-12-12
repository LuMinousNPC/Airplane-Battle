#include "Enemy.h"
#include <cstdlib>
#include <ctime>

// 静态变量初始化
static bool randomInitialized = false;

Enemy::Enemy(EnemyType type, const EnemyConfig& config, float x, float y)
    : type(type), config(config), x(x), y(y),
    speedX(0.0f), speedY(config.speed),
    health(config.health), isActiveFlag(true) {
    if (!randomInitialized) {
        srand((unsigned int)time(NULL));
        randomInitialized = true;
    }
    initImage();
}

Enemy::~Enemy() {
    // 图片资源由系统管理，不需要手动释放
}

void Enemy::initImage() {
    // 加载图片（参照Player类的加载方式）
    loadimage(&enemyImage, config.imagePath.c_str(), config.width, config.height);

    // 更新实际的宽高（如果图片加载后尺寸不同）
    config.width = enemyImage.getwidth();
    config.height = enemyImage.getheight();
}

void Enemy::update(float deltaTime) {
    if (!isActiveFlag) return;

    updateMovement(deltaTime);
    updateAI(deltaTime);
}

void Enemy::updateMovement(float deltaTime) {
    // 基本的向下移动
    y += speedY * deltaTime * 60;  // 转换为像素/秒

    // 左右移动（如果有）
    x += speedX * deltaTime * 60;
}

void Enemy::updateAI(float deltaTime) {
    // 基类空实现，由子类重写
}

void Enemy::draw() {
    if (!isActiveFlag) return;

    // 计算绘制位置（中心坐标转左上角坐标）
    int drawX = static_cast<int>(x - config.width / 2);
    int drawY = static_cast<int>(y - config.height / 2);

    // 使用putimage_new绘制（支持透明）
    putimage_new(drawX, drawY, &enemyImage);

    // 绘制生命值条（除了陨石）
    if (type != EnemyType::SMALL_METEOR && type != EnemyType::LARGE_METEOR && health < config.health) {
        drawHealthBar();
    }
}

void Enemy::drawHealthBar() {
    int barWidth = config.width;
    int barHeight = 4;
    int barX = static_cast<int>(x - barWidth / 2);
    int barY = static_cast<int>(y - config.height / 2 - 10);

    // 背景（红色）
    setfillcolor(RGB(255, 0, 0));
    solidrectangle(barX, barY, barX + barWidth, barY + barHeight);

    // 当前生命值（绿色）
    float healthRatio = static_cast<float>(health) / config.health;
    int currentWidth = static_cast<int>(barWidth * healthRatio);
    setfillcolor(RGB(0, 255, 0));
    solidrectangle(barX, barY, barX + currentWidth, barY + barHeight);

    // 边框
    setlinecolor(WHITE);
    rectangle(barX, barY, barX + barWidth, barY + barHeight);
}

bool Enemy::checkBoundary() {
    // 检查是否超出屏幕底部
    if (y > WINDOW_HEIGHT + config.height) {
        return true;
    }

    // 检查是否超出屏幕左右边界
    if (x < -config.width || x > WINDOW_WIDTH + config.width) {
        return true;
    }

    return false;
}

void Enemy::takeDamage(int damage) {
    if (!isActiveFlag) return;

    health -= damage;

    if (health <= 0) {
        health = 0;
        isActiveFlag = false;
    }
}

void Enemy::reset(float x, float y) {
    this->x = x;
    this->y = y;
    health = config.health;
    isActiveFlag = true;
    speedX = 0.0f;
    speedY = config.speed;
}