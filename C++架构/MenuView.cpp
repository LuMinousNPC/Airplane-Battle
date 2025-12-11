#define _CRT_SECURE_NO_WARNINGS
#include "MenuView.h"
#include "utils.h"
#include "viewManager.h"
#include <cstdlib>
#include "global.h"
#include <sstream>
#include <iostream>

/* 进入视图时调用，初始化视图资源 */
void MenuView::enter() {

}

/* 更新视图逻辑 */
void MenuView::update() {

}

/* 绘制视图 */
void MenuView::draw() {
    cleardevice();

    // 绘制背景图片
    putimage(0, 0, &menu_bk_image);
    // 绘制开始游戏按钮
    start_button.drawButton();
    // 绘制退出按钮
    exit_button.drawButton();
    //  绘制设置按钮
    setting_button.drawButton();


}

/* 处理输入消息 */
void MenuView::handleInput(ExMessage& msg) {
    if (msg.message == WM_LBUTTONDOWN) {
        // 开始按钮点击判断：左=x，上=y，右=x+w，下=y+h
        if (inArea(msg.x, msg.y,
            start_button.x, start_button.y,
            start_button.x + start_button.w, start_button.y + start_button.h)) {
            std::cout << "开始按钮被点击" << std::endl;
            //播放音效
            if (ifSound)
            {
                playSound(0);
            }
            view_manager.switch_to(ViewManager::ViewType::Game);
        }
       
        
        // 退出按钮点击判断：左=x，上=y，右=x+w，下=y+h
        if (inArea(msg.x, msg.y,
            exit_button.x, exit_button.y,
            exit_button.x + exit_button.w, exit_button.y + exit_button.h)) {
            //播放音效
            if (ifSound)
            {
                playSound(0);
            }
            std::cout << "退出按钮被点击" << std::endl;
            
            closegraph();
            exit(0);
        }
        if (inArea(msg.x, msg.y,
            setting_button.x, setting_button.y,
            setting_button.x + setting_button.w, setting_button.y + setting_button.h)) {
            std::cout << "设置按钮被点击" << std::endl;
            //播放音效
            if (ifSound)
            {
                playSound(0);
            }
            view_manager.switch_to(ViewManager::ViewType::Setting);
        }
    }
}

/* 退出视图时调用，释放资源 */
void MenuView::quit() {

}

