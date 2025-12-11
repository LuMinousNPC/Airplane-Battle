#pragma once
#include "View.h"
#include "button.h"
#include "global.h"


class GameView : public View
{
public:
    GameView() = default;
    ~GameView() = default;

    // 视图生命周期函数（重写父类纯虚函数）
    void enter() override;     // 进入视图：初始化资源
    void update() override;    // 更新视图逻辑
    void draw() override;      // 绘制视图内容
    void handleInput(ExMessage& msg) override;  // 处理输入
    void quit() override;      // 退出视图：释放资源
	void drawGameUI();    // 绘制游戏界面UI

private:
    int Pause_x = (WINDOW_WIDTH - pause_img.getwidth()) / 2;                                //暂停菜单x坐标
    int Pause_y = (WINDOW_HEIGHT - pause_img.getheight()) / 2;                              //暂停菜单y坐标
    int button_x = Pause_x + (pause_img.getwidth() - return_game_img.getwidth()) / 2 - 10;  //按钮统一x坐标
    int return_game_y = Pause_y + 100;                                                      //回到游戏按钮y
    int go_set_y = Pause_y + 100 + 175;                                                     //进入设置按钮y
    int return_menu_y = Pause_y + 100 + 350;                                                //回到主菜单按钮y
    ImageButton pause_button{ Pause_x, Pause_y, 500, 700, "./Assert/images/pause.png" };
    ImageButton return_game_button{ button_x, return_game_y, 300, 100, "./Assert/images/buttonReturnGame.png" };
    ImageButton go_set_button{ button_x, go_set_y, 300, 100,  "./Assert/images/set.png" };
    ImageButton return_menu_button{ button_x, return_menu_y, 300, 100, "./Assert/images/buttonReturnMenu.png" };

};


