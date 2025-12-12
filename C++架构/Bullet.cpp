#include "Bullet.h"
#include "utils.h"
#include"SettingView.h"
// 子弹类实现
Bullet::Bullet(BulletType type, float x, float y, float speedY)
    : type(type), x(x), y(y), speedY(speedY), active(true) {

    // 加载子弹图片
    std::string imagePath;
    if (type == BulletType::PLAYER_BULLET) {
        imagePath = "./Assert/images/123.png";  // 玩家子弹
        width = 15;
        height = 30;
    }
    else {
        imagePath = "./Assert/images/34.png";   // 敌人子弹
        width = 20;
        height = 20;
    }

    loadimage(&image, imagePath.c_str(),width,height);
}

void Bullet::update(float deltaTime) {
    if (!active) return;

    // 更新位置（只沿Y轴移动）
    y += speedY * deltaTime;

    // 检查边界
    if (isOutOfBounds()) {
        active = false;
    }
}

void Bullet::draw() {
    if (!active) return;

    // 绘制子弹（透明贴图）
    putimage(static_cast<int>(x), static_cast<int>(y), &image);
}

bool Bullet::isOutOfBounds() const {
    return (y < -height || y > WINDOW_HEIGHT);
}

RECT Bullet::getRect() const {
    RECT rect;
    rect.left = static_cast<LONG>(x);
    rect.top = static_cast<LONG>(y);
    rect.right = static_cast<LONG>(x + width);
    rect.bottom = static_cast<LONG>(y + height);
    return rect;
}

// 子弹管理器实现

// 构造函数中初始化
BulletManager::BulletManager()
    : autoFireEnabled(false), autoFireInterval(0.5f), autoFireTimer(0.0f) {
}

// 设置自动射击
void BulletManager::setAutoFire(bool enable, float interval) {
    autoFireEnabled = enable;
    autoFireInterval = interval;
    if (!enable) {
        autoFireTimer = 0.0f;
    }
}

// 更新自动射击
void BulletManager::updateAutoFire(float deltaTime, float playerX, float playerY) {
    if (!autoFireEnabled) return;

    // 更新计时器
    autoFireTimer += deltaTime;

    // 达到射击间隔，发射子弹
    if (autoFireTimer >= autoFireInterval) {
        // 计算子弹发射位置（玩家飞机中心）
        float bulletX = playerX -8 ;  // 假设玩家飞机宽度50px，居中发射
        float bulletY = playerY - 23;      // 从飞机顶部发射

        // 发射子弹
        firePlayerBullet(bulletX, bulletY);

        // 重置计时器
        autoFireTimer = 0.0f;

        // 播放射击音效（如果有）
        if (ifSound) {
            playSound(2);  // 假设2是射击音效ID
        }
    }
}

BulletManager::~BulletManager() {
    // 清理所有子弹
    for (auto bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
}

void BulletManager::update(float deltaTime) {
    // 更新所有子弹
    for (auto bullet : bullets) {
        bullet->update(deltaTime);
    }

    // 清理无效子弹
    cleanupBullets();
}

void BulletManager::draw() {
    // 绘制所有活跃子弹
    for (auto bullet : bullets) {
        if (bullet->isActive()) {
            bullet->draw();
        }
    }
}

void BulletManager::firePlayerBullet(float x, float y) {
    // 创建新的玩家子弹（向上发射，速度-800像素/秒）
    Bullet* bullet = new Bullet(BulletType::PLAYER_BULLET, x, y, -800.0f);
    bullets.push_back(bullet);
}

void BulletManager::cleanupBullets() {
    // 移除无效的子弹
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        if (!(*it)->isActive()) {
            delete* it;
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}