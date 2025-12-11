#include <random>
#include "RandomUtils.h"

static std::random_device rd;   // 初始化引擎（硬件种子）
static std::mt19937 gen(rd());  // 种子启动引擎

//下面是根据分布器将引擎输出映射到目标范围
// -生成随机整数
int randomInt(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);  // 整数均匀分布
	return dist(gen); // 通过引擎返回结果
}

// -生成随机浮点数
float randomFloat(float min, float max) {
	std::uniform_real_distribution<float> dist(min, max);  // 浮点数均匀分布
	return dist(gen); // 通过引擎返回结果
}

// -按概率返回布尔值
bool randomBool(double probability) {
	if (probability < 0.0 || probability > 1.0) {
		throw std::invalid_argument("概率必须在0.0到1.0之间");
	}
	std::bernoulli_distribution dist(probability);    // 伯努利分布：专门生成bool值，参数为true的概率
	return dist(gen);
}

/*
* 生成正态分布随机数
* 均值（mean）默认0.0（标准正态分布）
* 标准差（stddev）默认1.0（标准正态分布）
* 符合N(mean, pow(stddev, 2))的随机数
* 根据正态分布生成敌人类型符合难度设计
*/
// -随机敌人类型
EnemyType randomEnemyType(double mean, double stddev) {
	std::normal_distribution<double> dist(mean, stddev);   // 正态分布函数
	if (dist(gen) > -1 && dist(gen) < 1) {
		return EnemyType::NORMAL;             // 常规敌人    最高概率
	}
	else if(dist(gen) > -2 && dist(gen) < -1){
		return EnemyType::FAST;               // 高速低血    次高概率
	}
	else if (dist(gen) > 1 && dist(gen) < 2) {
		return EnemyType::TANK;               // 高血低速    次高概率
	}
	else {
		return EnemyType::METEOR;             // 高伤        最低概率
	}
}

// -随机生成X坐标
float randomSpawnX() {
	std::uniform_real_distribution<float> dist(0.0, 760.0);  // 浮点数均匀分布
	return dist(gen); // 通过引擎返回结果
}