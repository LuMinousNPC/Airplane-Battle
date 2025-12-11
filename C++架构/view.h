#pragma once
#include <graphics.h>
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "global.h"



class View
{
public:
    View() = default;
    virtual ~View() = default;

    // 视图生命周期函数
    virtual void enter() { /* 进入视图时调用，初始化视图资源 */ };
    virtual void update() { /* 更新视图逻辑 */ };
    virtual void draw() { /* 绘制视图 */ };
    virtual void handleInput(ExMessage& msg) { /* 处理输入消息 */ };
    virtual void quit() { /* 退出视图时调用，释放资源 */ };
};


