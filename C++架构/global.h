#ifndef GLOBAL_H
#define GLOBAL_H

#include <graphics.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "Player.h"


using namespace std;


// 窗口尺寸全局常量
constexpr auto WINDOW_WIDTH = 720;                       //窗口宽度;
constexpr auto WINDOW_HEIGHT = 960;                      //窗口高度;
constexpr auto TARGET_FPS = 60;                        // 目标帧率;
constexpr auto BACKGROUND_SCROLL_SPEED = 2;            // 背景滚动速度（像素/帧）;

//玩家属性配置
constexpr auto PLAYER_MAX_HEALTH = 100;                // 玩家最大生命值;
constexpr auto PLAYER_START_LIVES = 1;                 // 玩家初始生命数（无尽模式）;
constexpr auto PLAYER_COLLISION_DAMAGE = 30;           // 与敌人碰撞的伤害值;
constexpr auto PLAYER_SPEED = 5;                       // 玩家移动速度;
constexpr auto PLAYER_SHOOT_COOLDOWN = 0.2;            // 射击冷却时间（秒）;
constexpr auto PLAYER_BULLET_DAMAGE = 20;              // 玩家子弹伤害;

//敌人属性配置
// 敌人生成
constexpr auto MAX_ENEMIES_ON_SCREEN = 15;             // 屏幕最大敌人数;
constexpr auto ENEMY_SPAWN_MIN_INTERVAL = 1.0;         // 最小生成间隔（秒）;
constexpr auto ENEMY_SPAWN_MAX_INTERVAL = 3.0;         // 最大生成间隔（秒）;
constexpr auto ENEMY_SPAWN_SAFE_MARGIN = 50;           // 生成边界安全距离;

// 普通敌机
constexpr auto NORMAL_ENEMY_HEALTH = 30;               // 生命值;
constexpr auto NORMAL_ENEMY_SPEED = 3.0;               // 移动速度（像素/帧）;
constexpr auto NORMAL_ENEMY_SCORE = 100;               // 击毁得分;
constexpr auto NORMAL_ENEMY_DAMAGE = 10;               // 碰撞伤害;

// 快速敌机
constexpr auto FAST_ENEMY_HEALTH = 15;                 // 生命值;
constexpr auto FAST_ENEMY_SPEED = 5.0;                 // 移动速度;
constexpr auto FAST_ENEMY_SCORE = 150;                 // 击毁得分;
constexpr auto FAST_ENEMY_DAMAGE = 15;                 // 碰撞伤害;

// 坦克敌机
constexpr auto TANK_ENEMY_HEALTH = 60;                 // 生命值;
constexpr auto TANK_ENEMY_SPEED = 1.5;                 // 移动速度;
constexpr auto TANK_ENEMY_SCORE = 200;                 // 击毁得分;
constexpr auto TANK_ENEMY_DAMAGE = 20;                 // 碰撞伤害;

// 陨石
constexpr auto METEOR_BASE_SPEED_Y = 2.5;              // 基础向下速度;
constexpr auto METEOR_SPEED_X_RANGE = 1.5;             // X轴速度随机范围（±值）;
constexpr auto METEOR_SCORE = 50;                      // 击毁得分;
constexpr auto METEOR_DAMAGE = 40;                     // 碰撞伤害（较高）;

// 子弹属性
constexpr auto PLAYER_BULLET_SPEED = 10.0;             // 玩家子弹速度（向上）
constexpr auto ENEMY_BULLET_SPEED = 5.0;               // 敌人子弹速度（向下）
constexpr auto BULLET_OUT_OF_BOUNDS_MARGIN = 50;       // 出界判定边距

// 游戏平衡配置
constexpr auto SCORE_MULTIPLIER = 1;                    // 分数倍率（可调整难度）
constexpr auto HEALTH_BAR_WIDTH = 50;                   // 生命条宽度
constexpr auto HEALTH_BAR_HEIGHT = 6;                   // 生命条高度


// 枚举类型
// 敌人枚举
enum class EnemyType {
    NORMAL,      // 普通敌机：中等速度，中等血量，100分
    FAST,        // 快速敌机：高速，低血量，150分
    TANK,        // 坦克敌机：低速，高血量，200分
    METEOR       // 高伤害
};
// 子弹类型枚举 (BulletType) - 已存在，补充说明(在bullet.h里面）

// 游戏状态枚举
enum class GameState {
    MENU,        // 主菜单状态
    PLAYING,     // 游戏进行中状态
    GAME_OVER    // 游戏结束状态
};

// 游戏状态
extern GameState gameState;


// 菜单背景图片
extern IMAGE menu_bk_image;
// 设置背景
extern IMAGE setting_bk_image;


extern IMAGE background_img;		// 背景图资源

extern Player player;



//游玩中暂停
extern IMAGE pause_img;
extern IMAGE return_game_img;
extern IMAGE return_menu_img;
extern IMAGE go_set_img;


//11.13(音乐更新)
//音乐别名和路径
const char MusicPath[][2][128] = {
    "M00","空",
    "M01","fall",
    "M02","spring",
    "M03","summer",
    "M04","winter",
    "M08","LavaChicken",
    "M10","空"
};

//音效别名和路径
const char SoundPath[][2][128] = {
    {"S00", "点击音效"},
    
    
};//音乐开关
extern int ifMusic;
//音效开关
extern int ifSound;
//音乐音量
extern int MusicVolume;
//音效音量
extern int SoundVolume;
//音乐选择
extern int MusicNum;

#endif
