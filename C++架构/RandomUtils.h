#pragma once
#include "global.h"

int randomInt(int min, int max);                 // -生成随机整数

float randomFloat(float min, float max);         // -生成随机浮点数

bool randomBool(double probability = 0.5);                // -按概率返回布尔值

EnemyType randomEnemyType(double mean = 0.0, double stddev = 1.0);                     // -随机敌人类型

float randomSpawnX();                            // -随机生成X坐标
