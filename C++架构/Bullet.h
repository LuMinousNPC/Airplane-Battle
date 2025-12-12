#ifndef BULLET_H
#define BULLET_H
#include <graphics.h>
#include <vector>
#include "global.h"
// 子弹类型
enum class BulletType {
	PLAYER_BULLET, // 玩家子弹
	ENEMY_BULLET // 敌人子弹
};
// 子弹类
class Bullet {
public:
	// 构造函数
	Bullet(BulletType type, float x, float y, float speedY);
	// 更新子弹
	void update(float deltaTime);
	// 绘制子弹
	void draw();
	// 检查是否超出边界
	bool isOutOfBounds() const;
	// 获取子弹矩形（用于碰撞检测）
	RECT getRect() const;
	// Getter 方法
	float getX() const { 
		return x; 
	}
	float getY() const { 
		return y;
	}
	int getWidth() const { 
		return width; 
	}
	int getHeight() const { 
		return height; 
	}
	BulletType getType() const {
		return type;
	}
	bool isActive() const { 
		return active; 
	}
	// Setter 方法
	void setActive(bool active) { this->active = active; }
private:BulletType type;    // 子弹类型
	float x, y;    // 位置
	float speedY;    // Y 轴速度
	int width, height;    // 尺寸
	bool active;     // 是否活跃
	IMAGE image; // 子弹图片
};


// 子弹管理器类
class BulletManager {
public:
	// 构造函数
	BulletManager();
	// 析构函数
	~BulletManager();
	// 更新所有子弹
	void update(float deltaTime);
	// 绘制所有子弹
	void draw();
	// 发射玩家子弹
	void firePlayerBullet(float x, float y);
	// 清理无效子弹
	void cleanupBullets();
	// 获取所有子弹
	const std::vector<Bullet*>& getBullets() const { 
		return bullets; 
	}
	// 设置自动射击参数
	void setAutoFire (bool enable, float interval = 0.5f);
	// 更新自动射击（在游戏主循环中调用）
	void updateAutoFire (float deltaTime, float playerX, float playerY);
private:
	std::vector<Bullet*> bullets; // 子弹列表
	bool autoFireEnabled; // 是否启用自动射击
	float autoFireInterval; // 自动射击间隔（秒）
	float autoFireTimer; // 自动射击计时器


};
#endif // BULLET_H