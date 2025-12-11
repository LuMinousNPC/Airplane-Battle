#pragma once

#include "view.h"
#include "button.h"
#include "utils.h"
// 团队介绍视图：展示团队信息，支持返回菜单
class SettingView : public View {
public:
	SettingView() = default;
	~SettingView() = default;

	// 视图生命周期函数（重写父类纯虚函数）
	void enter() override;     // 进入视图：初始化资源
	void update() override;    // 更新视图逻辑
	void draw() override;      // 绘制视图内容
	void handleInput(ExMessage& msg) override;  // 处理输入
	void quit() override;      // 退出视图：释放资源

private:
	//返回按钮
	ImageButton setting_button_return{ 220, 870,250, 80,"./Assert/images/Return_Button.png" };


	//画面按钮
	ImageButton setting_button_view{ 285, 140,180, 80,"Assert/images/Screen button.png" };

	//难度按钮
	ImageButton setting_button_difficulty{ 475, 140,180, 80,"Assert/images/Difficulty Button.png" };

	//音乐按钮
	ImageButton setting_button_music{ 95, 140,180, 80,"Assert/images/Music button.png" };


	//音乐音量条
	ImageButton Music_volume_bar{ 620-365, 270,380, 15,"Assert/images/track.png" };

	//音效音量条
	ImageButton Sound_Volume_Slider{ 620 - 365, 340,380, 15,"Assert/images/track.png" };

	//切换音乐左箭头按钮(上一首)
	ImageButton setting_button_Previous_music{ 620 - 365, 400,40, 40,"Assert/images/Switch music button (Previous).png" };

	//切换音乐右箭头按钮（下一首）
	ImageButton setting_button_next_music{ 960 - 365, 400,40, 40,"Assert/images/Switch music button (Next).png" };

	//音乐开关（两个）
	ImageButton setting_button_music_switch_on{ 620 - 365, 470,150, 45,"Assert/images/Switch (On).png" };
	ImageButton setting_button_music_switch_off{ 620 - 365, 470,150, 45,"Assert/images/Switch (Off).png" };

	//音效开关（两个）
	ImageButton setting_button_sound_switch_on{ 620 - 365, 540,150, 45,"Assert/images/Switch (On).png" };
	ImageButton setting_button_sound_switch_off{ 620 - 365, 540,150, 45,"Assert/images/Switch (Off).png" };

	ExMessage currentMsg;
	// 新增：滑块状态变量
	bool inSlider1 = false;
	bool inSlider2 = false;
	// 新增：音量值（假设需要保存这两个值）
	//int musicVolume = 500;   // 音乐音量（0-1000）
	//int soundVolume = 500;   // 音效音量（0-1000）

};

void playAudio(const char AudioPath[][2][128], int choose, int isRepeat);
void pauseAudio(const char AudioPath[][2][128], int choose);
void resumeAudio(const char AudioPath[][2][128], int choose, int isRepeat);
void stopAudio(const char AudioPath[][2][128], int choose);
void setAudioVolume(const char AudioPath[][2][128], int choose, int volume);
//11.15音效播放
void playSound(int choose);
