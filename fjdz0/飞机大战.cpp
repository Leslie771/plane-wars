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


//���屳��ͼƬ
IMAGE BackgroundImg;
//����λ��
int BackgroundImg0Y, BackgroundImg1Y;

//����ɻ�ͼƬ
IMAGE MyplaneImg0, MyplaneImg1;
//����ɻ�����
Pos MyplanePos;

//�����ӵ�ͼƬ
IMAGE MyBulletImg0, MybulletImg1;

//�����ӵ�����
std::list<Pos> MyBulletList;

//list<������ÿ���ڵ�洢����������>������

int main() {
	
	initgraph(WIDTH, HEIGHT);

	InitGame();

	//��������
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

//��ʼ����Ϸ
void InitGame() {
	//���ر���ͼ
	loadimage(&BackgroundImg, "back.jpg");

	//���طɻ�ͼƬ 
	loadimage(&MyplaneImg0, "plane1.jpg");
	loadimage(&MyplaneImg1, "plane2.jpg");

	//�����ӵ�ͼƬ
	loadimage(&MyBulletImg0, "bullet1.jpg");
	loadimage(&MybulletImg1, "bullet2.jpg");

	//��ʼ����Ϸ���� 
	//��ʼ������ͼƬλ��
	BackgroundImg0Y = 0;
	BackgroundImg1Y = -HEIGHT;
	//��ʼ���ɻ���λ��
	MyplanePos.x = (WIDTH-117) * 0.5;
	MyplanePos.y = (HEIGHT - 120) * 0.5 + 200;
	//��ʼ���ӵ�����
	MyBulletList.clear();

}

void DrawGame() {
	 
	//˫������ͼ
	BeginBatchDraw();
	//�������ͼƬ
	putimage(0, BackgroundImg0Y, &BackgroundImg);
	putimage(0, BackgroundImg1Y, &BackgroundImg);

	//����ɻ�ͼƬ
	putimage(MyplanePos.x,MyplanePos.y , &MyplaneImg0,SRCPAINT);
	putimage(MyplanePos.x,MyplanePos.y , &MyplaneImg1,SRCAND);

	//����ӵ�ͼƬ
	for (Pos pos : MyBulletList) //��������
	{
		putimage(pos.x, pos.y, &MyBulletImg0, SRCPAINT);
		putimage(pos.x, pos.y, &MybulletImg1, SRCAND);
	}

	EndBatchDraw();
}

void UpdateGame() {
	//�޸ı���λ��
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

	//�ӵ��ƶ�
	for (Pos &pos : MyBulletList) //��������
	{
		pos.y -= 5;
	}

}