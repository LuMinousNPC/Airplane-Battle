#ifndef MENUVIEW_H
#define MENUVIEW_H 

#include "View.h"
#include "button.h"
#include "global.h"
#include <chrono>



class MenuView : public View {
public:
	// enter()、exit()、handleInput()、update()、draw()
	MenuView() = default;
	~MenuView() = default;

	/* 进入视图时调用，初始化视图资源 */
	void enter() override;
	/* 更新视图逻辑 */
	void update() override;
	/* 绘制视图 */
	void draw()override;
	/* 处理输入消息 */
	void handleInput(ExMessage& msg) override;
	/* 退出视图时调用，释放资源 */
	void quit() override;

private:



private:
	//下面为按钮布局的计算逻辑，106为1280 / 8 * 2 / 3【为保证间距相同】
	// 开始游戏按钮
	ImageButton start_button{ 220, 400, 280, 75, "./Assert/images/buttonStart.png" };
	// 设置按钮
	ImageButton setting_button{ 220, 500, 280, 75, "./Assert/images/set.png" };
	// 退出按钮
	ImageButton exit_button{ 220, 600, 280, 75, "./Assert/images/buttonExit.png" };
};





#endif

