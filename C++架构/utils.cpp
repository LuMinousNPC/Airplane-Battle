#include "global.h"
#include "utils.h"
#include <iostream>

extern Player player;

//是否正在进行游戏
GameState gameState = GameState::MENU;

// 背景图资源
IMAGE menu_bk_image;      // 菜单背景图
IMAGE setting_bk_image;   // 设置面板背景图


//人物暂停界面
IMAGE pause_img;
IMAGE return_game_img;
IMAGE return_menu_img;
IMAGE go_set_img;




// 加载所有游戏资源（图片、图集、动画等）
void loadAllResources() {
    

    //加载背景图资源
    loadimage(&menu_bk_image, "./Assert/images/startUI1.jpg", WINDOW_WIDTH,WINDOW_HEIGHT);
    loadimage(&setting_bk_image, "./Assert/images/Settings_Panel.jpg", WINDOW_WIDTH, WINDOW_HEIGHT);
    

    //加载子弹图片



}

/* 图像处理半透明渲染
*  功能：支持Alpha通道的图像覆盖，实现透明/半透明效果，弥补EasyX默认putimage不支持透明度的缺陷
*  参数：
*    x, y - 目标图像在窗口中的左上角坐标
*    img - 指向IMAGE对象的指针，存储待覆盖的图像，包含Alpha通道信息（PNG格式）
*/
void putimage_new(int x, int y, const IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC((IMAGE*)img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

// 半透明渲染图像到设备上下文: 实现透明通道渲染，调用系统底层绘图API实现
inline void putimage_alpha(int x, int y, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

// 水平翻转图片
inline void flip_image(IMAGE* src, IMAGE* dst) {
    int w = src->getwidth();
    int h = src->getheight();
    Resize(dst, w, h);	// 设置目标图片尺寸（与源图一致）
    DWORD* src_buffer = GetImageBuffer(src);
    DWORD* dst_buffer = GetImageBuffer(dst);
    // 逐像素水平翻转（每行从右到左复制像素）
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int idx_src = y * w + x;
            int idx_dst = y * w + (w - x - 1);
            dst_buffer[idx_dst] = src_buffer[idx_src];
        }
    }
}

// 水平翻转图集（批量翻转图集中的所有图片）
void flip_atlas(Atlas& src, Atlas& dst) {
    dst.clear(); // 清空目标图集
    // 遍历源图集中的所有图片，逐一翻转后添加到目标图集
    for (int i = 0; i < src.get_size(); i++) {
        IMAGE img_filpped;
        flip_image(src.get_image(i), &img_filpped);
        dst.add_image(img_filpped);
    }
}

/*
    功能：判断目标点是否在指定矩形区域内（左闭右开、上闭下开，避免边界重叠）
    参数：
        x, y: 目标点的坐标
        l: 矩形区域的左边界x坐标
        t: 矩形区域的上边界y坐标
        r: 矩形区域的右边界x坐标
        b: 矩形区域的下边界y坐标
    返回值：在区域内返回true，否则返回false
*/
bool inArea(int x, int y, int l, int t, int r, int b) {
    // 判定条件：x在左边界和右边界之间，y在上边界和下边界之间（排除边界，避免重叠判定）
    return (x > l && x < r && y > t && y < b);
}

/*
    功能：实现滑动条控件（用于音量调节等场景）
    参数：
        x1, x2: 滑动条的左右端点x坐标（水平方向）
        y: 滑动条的垂直中心y坐标
        w, h: 滑块的宽度和高度
        num: 绑定的数值（输出参数，随滑块移动更新）
        max: 数值的最大值（最小值固定为0）
        inSlider: 标记是否处于拖动滑块状态（输入输出参数）
        msg: 鼠标消息（用于检测点击、拖动）
    返回值：数值是否发生变化（true=变化，false=未变化）
*/
bool Slider(int x1, int x2, int y, int w, int h, int& num, int max, bool& inSlider, ExMessage& msg) {
    int x;      // 滑块对应的x坐标（根据num计算）

    // 绘制滑动条背景（深色圆角矩形，注释保留原逻辑，若需要显示可取消注释）
    // setfillcolor(DARKGRAY);                        // 设置滑动条背景颜色
    // fillroundrect(x1, y - 5, x2, y + 5, 5, 5);     // 绘制滑动条背景（圆角矩形，适配滑块高度）

    // 检测鼠标按下：判断是否点击滑块区域
    if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x1 - w / 2, y - h / 2, x2 + w / 2, y + h / 2)) {
        inSlider = true; // 标记进入拖动状态
    }
    // 检测鼠标松开：退出拖动状态
    else if (inSlider && msg.message == WM_LBUTTONUP) {
        inSlider = false;
    }

    if (inSlider == false) {  // 未按住滑块：绘制默认状态滑块，数值不变
        // 根据当前数值计算滑块位置
        x = x1 + (x2 - x1) * (num) / max;
        setfillcolor(RGB(16, 43, 133));   // 滑块默认颜色
        // 绘制默认滑块（圆角矩形，居中于(x,y)）
        fillroundrect(x - w / 2, y - h / 2, x + w / 2, y + h / 2, 5, 5);
        return false; // 数值未变化
    }
    else {                // 按住滑块：跟随鼠标移动，更新数值
        // 根据鼠标x坐标计算当前数值
        num = (msg.x - x1) * max / (x2 - x1);
        if (msg.x < x1) {         // 鼠标超出左边界：数值设为最小值0
            num = 0;
        }
        else if (msg.x > x2) {    // 鼠标超出右边界：数值设为最大值max
            num = max;
        }
        // 根据更新后的数值计算滑块位置
        x = x1 + (x2 - x1) * (num) / max;
        setfillcolor(RGB(135, 234, 253));   // 滑块选中颜色
        // 绘制选中状态滑块（放大一圈，增强视觉反馈）
        fillroundrect(x - w / 2 - 3, y - h / 2 - 3, x + w / 2 + 3, y + h / 2 + 3, 5, 5);
        return true; // 数值已变化
    }
    return false;
}
