#include <Windows.h>
#include <graphics.h>
#include <string>
#include <conio.h>
#include <iostream>
#include "Player.h"
#include "global.h"
#include "utils.h"
#include "view.h"
#include "ViewManager.h"
#include "MenuView.h"
#include"SettingView.h"
using namespace std;

// 全局对象实例
ViewManager view_manager;
Player player;

//音乐
//音乐开关
int ifMusic = 1;
//音效开关
int ifSound = 1;
//音乐音量
int MusicVolume = 300;
//音效音量
int SoundVolume = 300;
//音乐选择
int MusicNum = 0;


int main() {
    // 初始化图形窗口
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

    // 加载所有游戏资源
    loadAllResources();

    // 设置字体样式
    settextstyle(20, 0, "微软雅黑");

    // 直接通过ViewManager切换到菜单视图
    view_manager.switch_to(ViewManager::ViewType::Menu);

    //加载音乐
    if (ifMusic)
    {
        playAudio(MusicPath, MusicNum, 1);
        setAudioVolume(MusicPath, MusicNum, 300);
    }
    

    // 游戏主循环
    ExMessage msg;
    while (true) {
        //音乐
        if (ifMusic)
        {
            setAudioVolume(MusicPath, MusicNum, MusicVolume);
        }
        
        

        BeginBatchDraw();

        DWORD start_time = GetTickCount();

        // 处理鼠标/键盘输入消息
        while (peekmessage(&msg)) {
            view_manager.handleInput(msg);
        }
    
        // 更新游戏状态
        view_manager.update();

        // 绘制游戏画面
        //cleardevice();    //清空画布会导致闪烁，注释掉后直接通过draw覆盖绘制
        view_manager.draw();
        FlushBatchDraw();

        // 控制帧率
        DWORD end_time = GetTickCount();
        DWORD delta_time = end_time - start_time;
        if (delta_time < 1000 / 60) {  // 60 FPS
            Sleep(1000 / 60 - delta_time);
        }
    }

    EndBatchDraw();
    closegraph();
    return 0;
}