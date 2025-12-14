#ifndef UTILS_H
#define UTILS_H
#include <graphics.h>
#include <windows.h> 

#pragma comment(lib, "Msimg32.lib")


// 加载所有游戏资源（图片、图集、动画等）
void loadAllResources();

/* 图像处理半透明渲染
*  功能：支持Alpha通道的图像覆盖，实现透明/半透明效果，弥补EasyX默认putimage不支持透明度的缺陷
*  参数：
*    x, y - 目标图像在窗口中的左上角坐标
*    img - 指向IMAGE对象的指针，存储待覆盖的图像，包含Alpha通道信息（PNG格式）
*/
void putimage_new(int x, int y, const IMAGE* img);




/*
    功能：判断目标点是否在指定矩形区域内（左闭右开、上闭下开，避免边界重叠判定）
    参数：
        x, y: 目标点的坐标
        l: 矩形区域的左边界x坐标
        t: 矩形区域的上边界y坐标
        r: 矩形区域的右边界x坐标
        b: 矩形区域的下边界y坐标
    返回值：目标点在区域内返回true，否则返回false
*/
bool inArea(int x, int y, int l, int t, int r, int b);

/*
    功能：滑动条控件（用于音量调节、参数设置等场景）
    参数：
        x1, x2: 滑动条水平方向的左右端点x坐标
        y: 滑动条的垂直中心y坐标
        w, h: 滑块的宽度和高度
        num: 绑定的数值（输出参数，随滑块移动更新，范围0~max）
        max: 绑定数值的最大值
        inSlider: 标记是否处于滑块拖动状态（输入输出参数）
        msg: 鼠标消息（用于检测点击、拖动操作）
    返回值：数值是否发生变化（true=变化，false=未变化）
*/
bool Slider(int x1, int x2, int y, int w, int h, int& num, int max, bool& inSlider, ExMessage& msg);

#endif