#include<stdio.h>
#include<easyx.h>
#include<list>
#pragma comment(lib,"winmm.lib")

using namespace std;

#define WIDTH 512
#define HEIGHT 768

void InitGame();

void DrawGame();

void UpdateGame();

struct Pos {

	int x, y;
	 
};


//定义背景图片
IMAGE BackgroundImg;
//定义位置
int BackgroundImg0Y, BackgroundImg1Y;

//定义飞机图片
IMAGE MyplaneImg0, MyplaneImg1;
//定义飞机坐标
Pos MyplanePos;

//定义子弹图片
IMAGE MyBulletImg0, MybulletImg1;

//定义子弹链表
std::list<Pos> MyBulletList;

//list<链表中每个节点存储的数据类型>变量名

int main() {
	
	initgraph(WIDTH, HEIGHT);

	InitGame();

	//播放音乐
	mciSendString("open gamemusic.mp3", NULL, 0, NULL);
	mciSendString("play gamemusic.mp3", NULL, 0, NULL);


	while (1)
	{
		DrawGame();
		UpdateGame();

		Sleep(10);
	}

	return 0;
}

//初始化游戏
void InitGame() {
	//加载背景图
	loadimage(&BackgroundImg, "back.jpg");

	//加载飞机图片 
	loadimage(&MyplaneImg0, "plane1.jpg");
	loadimage(&MyplaneImg1, "plane2.jpg");

	//加载子弹图片
	loadimage(&MyBulletImg0, "bullet1.jpg");
	loadimage(&MybulletImg1, "bullet2.jpg");

	//初始化游戏数据 
	//初始化背景图片位置
	BackgroundImg0Y = 0;
	BackgroundImg1Y = -HEIGHT;
	//初始化飞机的位置
	MyplanePos.x = (WIDTH-117) * 0.5;
	MyplanePos.y = (HEIGHT - 120) * 0.5 + 200;
	//初始化子单链表
	MyBulletList.clear();

}

void DrawGame() {
	 
	//双缓冲贴图
	BeginBatchDraw();
	//输出背景图片
	putimage(0, BackgroundImg0Y, &BackgroundImg);
	putimage(0, BackgroundImg1Y, &BackgroundImg);

	//输出飞机图片
	putimage(MyplanePos.x,MyplanePos.y , &MyplaneImg0,SRCPAINT);
	putimage(MyplanePos.x,MyplanePos.y , &MyplaneImg1,SRCAND);

	//输出子弹图片
	for (Pos pos : MyBulletList) //遍历链表
	{
		putimage(pos.x, pos.y, &MyBulletImg0, SRCPAINT);
		putimage(pos.x, pos.y, &MybulletImg1, SRCAND);
	}

	EndBatchDraw();
}

void UpdateGame() {
	//修改背景位置
	BackgroundImg0Y++;
	if (BackgroundImg0Y >= HEIGHT)
		BackgroundImg0Y = -HEIGHT;
	BackgroundImg1Y++;
	if (BackgroundImg0Y >= HEIGHT)
		BackgroundImg0Y = -HEIGHT; 

	if (GetAsyncKeyState('W')|| GetAsyncKeyState(VK_UP)) {
		if(MyplanePos.y > 0)
			MyplanePos.y-=5;
	}
	if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN)) {
		if(MyplanePos.y < HEIGHT - 120)
		MyplanePos.y+=5;
	}
	if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)) {
		if (MyplanePos.x > 0)
		MyplanePos.x-=5;
	}
	if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)) {
		if (MyplanePos.x < WIDTH - 117)

		MyplanePos.x+=5;
	}
	
	if (GetAsyncKeyState(VK_SPACE)) {
		Pos pos; 
		pos.x = MyplanePos.x + (117 - 19) * 0.5 - 6;
		pos.y = MyplanePos.y - 20;

		MyBulletList.push_back(pos);
	}

	//子弹移动
	for (Pos &pos : MyBulletList) //遍历链表
	{
		pos.y -= 5;
	}

}