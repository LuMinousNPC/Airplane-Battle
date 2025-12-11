#ifndef BUTTON_H
#define BUTTON_H

#include <graphics.h>
#include <string>
#include "utils.h"


class Button {
public:
	Button() = default;
	Button(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

	// 绘制按钮
	virtual void drawButton() = 0;

	// x，y是按钮的左上角坐标
	// w，h是按钮的宽高
	int x, y, w, h;
};


class ImageButton : public Button {
public:
	ImageButton() = default;
	ImageButton(int x, int y, int w, int h, const char* imagePath) : Button(x, y, w, h) {
		// 加载图片
		loadimage(&image, imagePath,w,h);
	}
	~ImageButton() = default;

	void drawButton() override {
		// 绘制按钮
		putimage_new(x,y,&image);
	}
	//带参版本
	void drawButton(int input_x, int input_y) {
		putimage_new(input_x, input_y, &image);
		x = input_x;
		y = input_y;
	}

private:
	// 按钮的图片
	IMAGE image;
};


class TextButton : public Button {
public:
	TextButton() = default;
	~TextButton() = default;
	TextButton(int x, int y, int w, int h, const char* text) : Button(x, y, w, h), text(text) {}
	TextButton(int x, int y, int w, int h, const std::string& text) : Button(x, y, w, h), text(text) {}

	void drawButton() override {
		// 绘制按钮
		setcolor(BLACK);
		setfillcolor(YELLOW);
		// fillrectangle参数是左上角(x,y)和右下角(x+w, y+h)
		fillrectangle(x, y, x + w, y + h);
		// 文字居中：计算文字宽度，调整x偏移（outtextxy默认左上角对齐）
		settextcolor(BLUE);
		int textWidth = textwidth(text.c_str());
		int textHeight = textheight(text.c_str());
		outtextxy(x + (w - textWidth) / 2, y + (h - textHeight) / 2, text.c_str());
	}
private:
	// 按钮上的文字
	std::string text;

};








#endif

