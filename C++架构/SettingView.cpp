#include "SettingView.h"
#include "viewManager.h"

int choice = 1;
int a = 100;
int b = 100;


int BGM_COUNT = sizeof(MusicPath) / sizeof(MusicPath[0]); // BGM总数

/*
    功能: playMusic: 播放指定音频
    参数:
        AudioPath[][2][128]:音乐组名/音效组名
        choose: 选择的音频
        isRepeat: 是否循环播放
            1 循环播放
            0 单次播放
    返回值: void
*/
void playAudio(const char AudioPath[][2][128], int choose, int isRepeat)
{
    char cmd[MAX_PATH] = " ";
    sprintf_s(cmd, "open Assert/musics/%s.mp3 alias %s type mpegvideo", AudioPath[choose][1], AudioPath[choose][0]);
    mciSendString(cmd, NULL, NULL, NULL);
    sprintf_s(cmd, isRepeat ? "play %s repeat from 0" : "play %s from 0", AudioPath[choose][0]);
    mciSendString(cmd, NULL, NULL, NULL);
};

//音效播放（异步）
void playSound(int choose) {


    char command[256];

    // 关闭可能存在的旧实例
    sprintf_s(command, sizeof(command), "close %s", SoundPath[choose][0]);
    mciSendString(command, NULL, 0, NULL);

    // 打开并异步播放
    sprintf_s(command, sizeof(command), "open \"Assert/sound/%s.wav\" alias %s",
        SoundPath[choose][1], SoundPath[choose][0]);
    mciSendString(command, NULL, 0, NULL);

    sprintf_s(command, sizeof(command), "play %s", SoundPath[choose][0]);
    mciSendString(command, NULL, 0, NULL);
}

/*
    功能: pauseMusic: 暂停播放指定音频
    参数:
        AudioPath[][2][128]:音乐组名/音效组名
        choose: 选择的音频
    返回值: void
*/
void pauseAudio(const char AudioPath[][2][128], int choose)
{
    char cmd[MAX_PATH] = " ";
    wsprintf(cmd, "pause %s", AudioPath[choose][0]);
    mciSendString(cmd, NULL, 0, NULL);
}

/*
    功能: resumeMusic: 继续指定音频
    参数:
        AudioPath[][2][128]:音乐组名/音效组名
        choose: 选择的音频
        isRepeat: 是否循环播放
            1 循环播放
            0 单次播放
    返回值: void
*/
void resumeAudio(const char AudioPath[][2][128], int choose, int isRepeat) {
    char cmd[MAX_PATH] = " ";
    wsprintf(cmd, isRepeat ? "play %s repeat" : "play %s", AudioPath[choose][0]);
    mciSendString(cmd, NULL, 0, NULL);
};

/*
    功能: stopMusic: 停止播放指定音频
    参数:
        AudioPath[][2][128]:音乐组名/音效组名
        choose: 选择的音频
    返回值: void
*/
void stopAudio(const char AudioPath[][2][128], int choose) {
    char cmd[MAX_PATH] = " ";
    wsprintf(cmd, "close %s", AudioPath[choose][0]);
    mciSendString(cmd, NULL, 0, NULL);
}

/*
    功能: setVolume: 设置指定音频的音量
    参数:
        AudioPath[][2][128]:音乐组名/音效组名
        choose: 选择的音频
        volume: 音量大小(0~1000)
    返回值: void
*/
void setAudioVolume(const char AudioPath[][2][128], int choose, int volume) {
    char cmd[MAX_PATH] = " ";
    wsprintf(cmd, "setaudio %s volume to %d", AudioPath[choose][0], volume);
    mciSendString(cmd, NULL, 0, NULL);
}


/* 进入视图时调用，初始化视图资源 */
void SettingView::enter() {

}

/* 更新视图逻辑 */
void SettingView::update() {

}

/* 绘制视图 */
void SettingView::draw() {
    
    //当前音乐名字位置
    RECT rect = { 620-365, 400, 980-365, 440 };  

    // 绘制背景图片
    putimage(0, 0, &setting_bk_image);
    if (choice == 1) {
        setting_button_music.drawButton();
        setting_button_view.drawButton();
        setting_button_difficulty.drawButton();
        setting_button_return.drawButton();

        Music_volume_bar.drawButton();
        Sound_Volume_Slider.drawButton();
        setting_button_Previous_music.drawButton();
        setting_button_next_music.drawButton();



        //绘制音乐开关
        if (ifMusic)
        {
            setting_button_music_switch_on.drawButton();
        }
        else
        {
            setting_button_music_switch_off.drawButton();
        }

        //绘制音效开关
        if (ifSound) {
            setting_button_sound_switch_on.drawButton();
        }
        else {
            setting_button_sound_switch_off.drawButton();
        }

        //音乐名称显示
        settextstyle(40, 0, "Noto Serif SC Black");    //设置字体样式 当前音乐名字
        settextcolor(RGB(27, 66, 185));			    //设置文字颜色
        drawtext(MusicPath[MusicNum][1], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//绘制当前音乐名字





        //文字显示
        setbkmode(TRANSPARENT); // 设置文字背景为透明
        settextcolor(BLACK); // 设置文字颜色
        settextstyle(55, 0, TEXT("Noto Serif SC Black")); // 设置文字样式
        outtextxy(95, 250, TEXT("音乐音量")); // 输出文字
        outtextxy(95, 320, TEXT("音效音量"));
        outtextxy(95, 390, TEXT("当前音乐"));
        outtextxy(95, 460, TEXT("音乐"));
        outtextxy(95, 530, TEXT("音效"));


        Slider(620-365, 620-365 + 380, 277, 20, 40, MusicVolume, 1000, inSlider1, currentMsg);

        Slider(620-365, 620-365 + 380, 347, 20, 40, SoundVolume, 1000, inSlider2, currentMsg);

    }
    if (choice == 2) {
        setting_button_music.drawButton();
        setting_button_view.drawButton();
        setting_button_difficulty.drawButton();
        setting_button_return.drawButton();
        setbkmode(TRANSPARENT); // 设置文字背景为透明
        settextcolor(BLACK); // 设置文字颜色
        settextstyle(55, 0, TEXT("Noto Serif SC Black")); // 设置文字样式
        outtextxy(95, 250, TEXT("待开发...")); // 输出文字
    }
    if (choice == 3) {
        setting_button_music.drawButton();
        setting_button_view.drawButton();
        setting_button_difficulty.drawButton();
        setting_button_return.drawButton();
        setbkmode(TRANSPARENT); // 设置文字背景为透明
        settextcolor(BLACK); // 设置文字颜色
        settextstyle(55, 0, TEXT("Noto Serif SC Black")); // 设置文字样式
        outtextxy(95, 250, TEXT("待开发...")); // 输出文字
    }
}

/* 处理输入消息 */
void SettingView::handleInput(ExMessage& msg) {
    currentMsg = msg;
    if (msg.message == WM_LBUTTONDOWN) {
        // 判断是否点击返回按钮
        if (inArea(msg.x, msg.y,
            setting_button_return.x, setting_button_return.y,
            setting_button_return.x + setting_button_return.w, setting_button_return.y + setting_button_return.h)) {
            std::cout << "返回菜单按钮被点击" << std::endl;
            //播放音效
            if (ifSound)
            {
                playSound(0);
            }
            // 切换回菜单视图（调用ViewManager的视图切换功能）
            if (gameState != GameState::PLAYING)view_manager.switch_to(ViewManager::ViewType::Menu);
            else view_manager.switch_to(ViewManager::ViewType::Game);
        }

        // 判断是否点击音乐按钮
        if (inArea(msg.x, msg.y,
            setting_button_music.x, setting_button_music.y,
            setting_button_music.x + setting_button_music.w, setting_button_music.y + setting_button_music.h)) {
            std::cout << "音乐按钮被点击" << std::endl;
            //播放音效
            if (ifSound)
            {
                playSound(0);
            }
            // 切换音乐菜单
            choice = 1;
        }

        // 判断是否点击难度按钮
        if (inArea(msg.x, msg.y,
            setting_button_difficulty.x, setting_button_difficulty.y,
            setting_button_difficulty.x + setting_button_difficulty.w, setting_button_difficulty.y + setting_button_difficulty.h)) {
            std::cout << "难度按钮被点击" << std::endl;
            //播放音效
            if (ifSound)
            {
                playSound(0);
            }
            // 切换难度菜单（不用做实现，显示“更新中....”）
            choice = 3;
        }

        // 判断是否点击画面按钮
        if (inArea(msg.x, msg.y,
            setting_button_view.x, setting_button_view.y,
            setting_button_view.x + setting_button_view.w, setting_button_view.y + setting_button_view.h)) {
            std::cout << "画面按钮被点击" << std::endl;
            //播放音效
            if (ifSound)
            {
                playSound(0);
            }
            // 切换画面菜单（不用做实现，显示“更新中....”）
            choice = 2;
        }

        // 判断是否点击切换上一首音乐按钮
        if (inArea(msg.x, msg.y,
            setting_button_Previous_music.x, setting_button_Previous_music.y,
            setting_button_Previous_music.x + setting_button_Previous_music.w, setting_button_Previous_music.y + setting_button_Previous_music.h)) {
            std::cout << "切换上一首音乐" << std::endl;
            
            //播放音效
            if (ifSound)
            {
                playSound(0);
            }
            
            // 切换上一首音乐
            if (ifMusic)
                stopAudio(MusicPath, MusicNum);
            MusicNum--;
            MusicNum = (MusicNum + BGM_COUNT) % BGM_COUNT;
            if (ifMusic)
            {
                playAudio(MusicPath, MusicNum, 1);
                setAudioVolume(MusicPath, MusicNum, MusicVolume);
            }
        }
        // 判断是否点击切换下一首音乐按钮
        if (inArea(msg.x, msg.y,
            setting_button_next_music.x, setting_button_next_music.y,
            setting_button_next_music.x + setting_button_next_music.w, setting_button_next_music.y + setting_button_next_music.h)) {
            std::cout << "切换下一首音乐" << std::endl;
            
            //播放音效
            if (ifSound)
            {
                playSound(0);
            }
            
            // 切换下一首音乐
            if (ifMusic)
                stopAudio(MusicPath, MusicNum);
            MusicNum++;
            MusicNum = (MusicNum + BGM_COUNT) % BGM_COUNT;
            if (ifMusic)
            {
                playAudio(MusicPath, MusicNum, 1);
                setAudioVolume(MusicPath, MusicNum, MusicVolume);
            }
        }
        // 判断是否点击音乐开关按钮

        if (ifMusic)
        {
            if (inArea(msg.x, msg.y,
                setting_button_music_switch_on.x, setting_button_music_switch_on.y,
                setting_button_music_switch_on.x + setting_button_music_switch_on.w, setting_button_music_switch_on.y + setting_button_music_switch_on.h)) {
                std::cout << "音乐开关被点击" << std::endl;
                //播放音效
                if (ifSound)
                {
                    playSound(0);
                }
                // 音乐开/音乐关
                ifMusic = (ifMusic + 1) % 2;
                stopAudio(MusicPath, MusicNum);
            }
        }
        else
        {
            if (inArea(msg.x, msg.y,
                setting_button_music_switch_on.x, setting_button_music_switch_on.y,
                setting_button_music_switch_on.x + setting_button_music_switch_on.w, setting_button_music_switch_on.y + setting_button_music_switch_on.h)) {
                std::cout << "音乐开关被点击" << std::endl;
                //播放音效
                if (ifSound)
                {
                    playSound(0);
                }
                // 音乐开/音乐关
                ifMusic = (ifMusic + 1) % 2;
                playAudio(MusicPath, MusicNum, 0);
                setAudioVolume(MusicPath, MusicNum, MusicVolume);
            }


        }


        // 判断是否点击音效开关按钮
        if (inArea(msg.x, msg.y,
            setting_button_sound_switch_on.x, setting_button_sound_switch_on.y,
            setting_button_sound_switch_on.x + setting_button_sound_switch_on.w, setting_button_sound_switch_on.y + setting_button_sound_switch_on.h)) {
            std::cout << "画面按钮被点击" << std::endl;           
            // 音效开/音效关
            ifSound = (ifSound + 1) % 2;
            //播放音效
            if (ifSound)
            {
                playSound(0);
            }
        }



    }
}

/* 退出视图时调用，释放资源 */
void SettingView::quit() {

}

