#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H
#include "view.h"
#include "menuView.h"

#include "GameView.h"
#include "SettingView.h"


class ViewManager
{
public:
    // 视图类型枚举
    enum class ViewType {
        
        Menu,       // 菜单
        Setting,    // 设置
        Game,       // 游戏
        End         // 结束
    };

public:

    ViewManager() = default;
    ~ViewManager() {
        // 释放所有视图资源
        if (current_view) {
            delete current_view;
        }
    }
    //设置当前状态
    void set_current_view(View* view) {
        current_view = view;
        current_view->enter();
    }



    // 切换视图：根据类型创建对应视图
    void switch_to(ViewType type) {
        // 释放旧视图
        if (current_view) {
            current_view->quit();
            delete current_view;
            current_view = nullptr;
        }

        switch (type) {
        case ViewType::Menu:
            current_view = new MenuView();
            break;
        case ViewType::Game:
            current_view = new GameView();
            break;
        case ViewType::Setting:
            current_view = new SettingView();
            break;
        default:
            break;
        }

        // 进入新视图
        if (current_view) {
            current_view->enter();
        }
    }


    // 委托给当前视图的方法
    void update() {
        if (current_view) current_view->update();
    }
    void draw() {
        if (current_view) current_view->draw();
    }
    void handleInput(ExMessage& msg) {
        if (current_view) current_view->handleInput(msg);
    }



private:
    View* current_view = nullptr; // 当前活动视图
};

// 全局视图管理器
extern ViewManager view_manager;



#endif
