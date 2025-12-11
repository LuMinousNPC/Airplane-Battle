#include "Bullet.h"


#include"utils.h"
#include <cmath>

// 外部声明你的putimage_new函数
extern void putimage_new(int x, int y, const IMAGE* img);

AdvancedBullet::AdvancedBullet(float startX, float startY, float speedX, float speedY,
    BulletType bulletType, int dmg, IMAGE* img)
    : x(startX), y(startY), speedX(speedX), speedY(speedY), damage(dmg),
    isActive(true), type(bulletType), bulletImg(img), homingTargetId(-1), rotation(0) {

    if (bulletImg) {
        width = bulletImg->getwidth();
        height = bulletImg->getheight();
    }
    else {
        // 默认尺寸
        width = 8;
        height = 16;
    }
}

void AdvancedBullet::update() {
    if (!isActive) return;

    x += speedX;
    y += speedY;

    // 根据子弹类型添加特殊行为
    switch (type) {
    case BulletType::PLAYER_MISSILE:
        // 导弹可能有尾焰效果等
        break;
    case BulletType::PLAYER_LASER:
        // 激光可能持续存在
        break;
    default:
        break;
    }
}

void AdvancedBullet::draw() {
    if (!isActive) return;

    if (bulletImg) {
        // 使用你的putimage_new函数绘制带透明度的子弹
        int drawX = (int)(x - width / 2);
        int drawY = (int)(y - height / 2);
        putimage_new(drawX, drawY, bulletImg);
    }
    else {
        // 备用：简单图形绘制
        COLORREF bulletColor;
        switch (type) {
        case BulletType::PLAYER_NORMAL:
            bulletColor = RGB(0, 255, 255); // 青色
            break;
        case BulletType::PLAYER_LASER:
            bulletColor = RGB(255, 0, 0);   // 红色
            break;
        case BulletType::ENEMY_NORMAL:
            bulletColor = RGB(255, 255, 0); // 黄色
            break;
        default:
            bulletColor = RGB(255, 255, 255); // 白色
        }

        setfillcolor(bulletColor);
        solidcircle((int)x, (int)y, width / 2);
    }
}

bool AdvancedBullet::checkBoundary(int screenWidth, int screenHeight) {
    if (x < -width || x > screenWidth + width ||
        y < -height || y > screenHeight + height) {
        isActive = false;
        return true;
    }
    return false;
}

void AdvancedBullet::homingUpdate(float targetX, float targetY) {
    if (homingTargetId == -1) return;

    // 简单的追踪逻辑
    float dx = targetX - x;
    float dy = targetY - y;
    float distance = sqrtf(dx * dx + dy * dy);

    if (distance > 0) {
        // 标准化方向
        dx /= distance;
        dy /= distance;

        // 调整速度方向（可以添加追踪强度参数）
        float homingStrength = 0.1f;
        speedX = speedX * (1 - homingStrength) + dx * 5.0f * homingStrength;
        speedY = speedY * (1 - homingStrength) + dy * 5.0f * homingStrength;

        // 更新旋转角度（用于导弹等）
        rotation = atan2f(dy, dx) * 180 / 3.14159f;
    }
}