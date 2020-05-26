
#include <graphics.h> //图形界面库 ，imagesize() 图像存储大小函数，putimage() 输出图像函数
#include <conio.h>//函数_getch()所需头文件 
#include <stdio.h>
#include<Windows.h>
#pragma comment(lib,"winmm.lib")//音乐播放需要的头文件
using namespace std;

/*函数声明*/
void LoadResource();//加载资源（人物，箱子，空地，目的地等图片)  239
void DrawMap();      //画图模块，绘制地图      80
void keyDown();     //人物移动  117
int GameOver();    ////判断关卡是否结束 250
void start1();    //初始的游戏页面的图 210
void start2();   //第一关、第二关、第三关的图及文本。 219
void start3();  //下一关，选择关卡，退出游戏的图 231
void GameOverLayout();//通关之后展示图片，关闭程序 268
void select();       //选择第一关,第二关，第三关。 298
void cycMouse();    //鼠标循环 336
void cyclMap();   //循环地图  282
void Game();     //游戏主体 476

//图片进行初始化（空地，墙，目的地，箱子，人物，箱子到达目的地,人到目的地的图片)
int imgIndex[6] = { 0,1,3,4,5,7 }; 
IMAGE img[6];

//初始化关卡
int cos = 0;

//地图，三维数组 map[cos][i][j]
/*0空地，1墙，3目的地，4箱子，5人*/
int map[3][10][10] =
{
	{
	0,0,1,1,1,0,0,0,0,0,
	0,0,1,3,1,0,0,0,0,0,
	0,0,1,0,1,1,1,1,0,0,
	1,1,1,0,0,4,3,1,0,0,
	1,3,4,4,0,1,1,1,0,0,
	1,1,1,5,4,1,0,0,0,0,
	0,0,0,1,3,1,0,0,0,0,
	0,0,0,1,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,},

	{
	1,1,1,1,1,0,0,0,0,0,
	1,5,0,0,1,0,0,0,0,0,
	1,0,4,4,1,0,1,1,1,0,
	1,0,4,0,1,0,1,3,1,0,
	1,1,1,0,1,1,1,3,1,0,
	0,1,1,0,0,0,0,3,1,0,
	0,1,0,0,0,1,0,0,1,0,
	0,1,0,0,0,1,1,1,1,0,
	0,1,1,1,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,},
	{
	0,0,0,1,1,1,1,1,1,1 ,
	0,0,1,1,0,0,1,0,5,1 ,
	0,0,1,0,0,0,1,0,0,1 ,
	0,0,1,4,0,4,0,4,0,1 ,
	0,0,1,0,4,1,1,0,0,1 ,
	1,1,1,0,4,0,1,0,1,1 ,
	1,3,3,3,3,3,0,0,1,0 ,
	1,1,1,1,1,1,1,1,1,0 ,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,}
};

//mian函数
int main()
{
	void DrawMap();
	LoadResource();  //加载资源
	Game();
}

/*函数定义*/
//画图模块，绘制地图
void DrawMap()  //画图模块，绘制地图
{               //根据数组中的值,贴相应的序号的图
	int x, y;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//贴出平面图所需要的x，y坐标
			x = 50 * j;    
			y = 50 * i;   
			switch (map[cos][i][j])
			{
			case 0:     //空地
				putimage(x, y, img + 0);//贴空地图片
				break;
			case 1:     //墙体
				putimage(x, y, img + 1);
				break;
			case 3:     //目的地
				putimage(x, y, img + 2);
				break;
			case 4:		//箱子
				putimage(x, y, img + 3); 
				break;
			case 5:     //人
				putimage(x, y, img + 4);
				break;
			case 7:     //4+3   箱子到达目的地
				putimage(x, y, img + 5);
				break;
			case 8:     //5+3  人与目的地重合
				putimage(x, y, img + 4);
				break;
			}
		}
	}
}

//人物移动
void keyDown()
{
	int i, j; //保存人物位置
	for (i = 0; i < 10; i++)//i为行值 
	{
		for (j = 0; j < 10; j++)//j为列值 
		{
			if (map[cos][i][j] == 5 || map[cos][i][j] == 8)
				break;
		}
		if (map[cos][i][j] == 5 || map[cos][i][j] == 8)
			break;
	}
	char userkey = _getch();
	switch (userkey)
	{
	case 'W':/*上移*/
	case 'w':
	case 72:
		if (map[cos][i - 1][j] == 0 || map[cos][i - 1][j] == 3)//人物上方是空地(0)或者目的地 (3)
		{
			map[cos][i - 1][j] += 5;//人物坐标上一个坐标值为5(人物) 
			map[cos][i][j] -= 5;//人物原坐标值为0(空地) 
		}
		else if (map[cos][i - 1][j] == 4 || map[cos][i - 1][j] == 7)//人物上方是箱子，箱子在空格上或者箱子在目的地处 
		{
			if (map[cos][i - 2][j] == 0 || map[cos][i - 2][j] == 3)//箱子上方是空格或者前面是目的地
			{
				map[cos][i - 2][j] += 4;//箱子向上移动，上一个0(空地)就变为 4(箱子)
				map[cos][i - 1][j] += 1;//4(原箱子)+1变为 5(人物)
				map[cos][i][j] -= 5;//5(原人物)-5变为0(空地) 
			}
		}
		break;
	case 'S':/*下移*/
	case 's':
	case 80:
		if (map[cos][i + 1][j] == 0 || map[cos][i + 1][j] == 3)//人下方是空地或目的地 
		{
			map[cos][i + 1][j] += 5;
			map[cos][i][j] -= 5;
		}
		else if (map[cos][i + 1][j] == 4 || map[cos][i + 1][j] == 7)//人下方是箱子 ，箱子在空地或者目的地上 
		{
			if (map[cos][i + 2][j] == 0 || map[cos][i + 2][j] == 3)//箱子下方是空地和目的地
			{
				map[cos][i + 2][j] += 4;//箱子向下移动，下一个0(空地)就变为 4(箱子)
				map[cos][i + 1][j] += 1;//4(原箱子)+1变为 5(人物)
				map[cos][i][j] -= 5;//5(原人物)-5变为0(空地) 
			}
		}
		break;
	case 'A':
	case 'a':
	case 75:
		if (map[cos][i][j - 1] == 0 || map[cos][i][j - 1] == 3)//人左方是空地或目的地 
		{
			map[cos][i][j - 1] += 5;
			map[cos][i][j] -= 5;
		}
		else if (map[cos][i][j - 1] == 4 || map[cos][i][j - 1] == 7)//人左方是箱子 ，箱子在空地或者目的地上
		{
			if (map[cos][i][j - 2] == 0 || map[cos][i][j - 2] == 3)//箱子左方是空地和目的地
			{
				map[cos][i][j - 2] += 4;//箱子向下移动，下一个0(空地)就变为 4(箱子)
				map[cos][i][j - 1] += 1;//4(原箱子)+1变为 5(人物)
				map[cos][i][j] -= 5;//5(原人物)-5变为0(空地) 
			}
		}
		break;
	case 'D':
	case 'd':
	case 77:
		if (map[cos][i][j + 1] == 0 || map[cos][i][j + 1] == 3)//人右方是空地或目的地 
		{
			map[cos][i][j + 1] += 5;
			map[cos][i][j] -= 5;
		}
		else if (map[cos][i][j + 1] == 4 || map[cos][i][j + 1] == 7)//人右方是箱子 ，箱子在空地或者目的地上
		{
			if (map[cos][i][j + 2] == 0 || map[cos][i][j + 2] == 3)//箱子右方是空地和目的地
			{
				map[cos][i][j + 2] += 4;//箱子向下移动，下一个0(空地)就变为 4(箱子)
				map[cos][i][j + 1] += 1;//4(原箱子)+1变为 5(人物)
				map[cos][i][j] -= 5;//5(原人物)-5变为0(空地) 
			}
		}
		break;
	}
}




//初始游戏页面的图
void start1()//初始页面的图
{
	initgraph(50 * 10, 50 * 10);//展开画布
	IMAGE st;
	loadimage(&st, "11.jpg", 500, 500);
	putimage(0, 0, &st);
}

//第一关、第二关、第三关的图及文本。
void start2()//第一关，第二关，第三关的图（12）
{
	initgraph(50 * 10, 50 * 10);//展开画布
	settextcolor(RED);//文本背景设置红色
	outtextxy(160, 250, "游戏加载中...");
	//加载程序设定时间
	Sleep(1000);
	IMAGE st;
	loadimage(&st, "12.jpg", 500, 500);
	putimage(0, 0, &st);
}

//下一关，选择关卡，退出游戏的图
void start3()//下一关，选择关卡，退出游戏的图(13)
{
	IMAGE st;
	loadimage(&st, "13.jpg", 500, 500);
	putimage(0, 0, &st);
}

//加载人物，箱子，空地，目的地等图片
void LoadResource()
{
	initgraph(50 * 10, 50 * 10);//展开画布
	for (int i = 0; i < 6; i++)
	{
		char filename[20] = "";
		sprintf_s(filename, "%d.jpg", imgIndex[i]);//数据格式化输出到字符串。也就是格式化，把文件放到字符串里
		loadimage(img + i, filename, 50, 50);//读取图片文件
	}
}

//判断关卡是否结束，是否有箱子未推
int GameOver()
{
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[cos][i][j] == 4)//当数组没有4（箱子） ，表明箱子都到位，返回1 
			{
				count = 0;
				return 0;
			}
		}
	}
	return 1;
}

//通关之后展示图片，关闭程序
void GameOverLayout()
{
	Sleep(1000);
	outtextxy(160, 250, "游戏通关...");//文本显示在画布上：游戏通关
	//通关之后，展示最终的照片
	Sleep(1000);
	IMAGE g;
	loadimage(&g, "恭喜你通关.jpg", 500, 500);
	putimage(0, 0, &g);
	Sleep(2000);
	exit(0);
}

//地图循环
void cyclMap()
{
	settextcolor(YELLOW);
	outtextxy(160, 250, "关卡加载中...");
	Sleep(1000);//延迟1秒
	while (1)//地图循环
	{
		DrawMap();
		keyDown();
		if (GameOver())

			break;////通关之后							
	}
}

//选择第一关,第二关，第三关。
void select()
{

	while (1)
	{
		//鼠标事件消息循环
		MOUSEMSG msg = { 0 };
		msg = GetMouseMsg();//获取鼠标坐标
		switch (msg.uMsg)
		{
		case WM_LBUTTONDBLCLK://鼠标左键双击

			//第一关
			if (msg.x > 30 && msg.x < 468 && msg.y>86 && msg.y < 163)
			{
				cos;
				cyclMap();
				GameOverLayout();
			}
			//第二关
			else if (msg.x > 30 && msg.x < 468 && msg.y>250 && msg.y < 324)
			{
				cos++;//第二关
				cyclMap();
				GameOverLayout();
			}
			//第三关
			else if (msg.x > 30 && msg.x < 468 && msg.y>415 && msg.y < 490)
			{
				cos = cos + 2;//第三关
				cyclMap();
				GameOverLayout();
			}
		}
	}
}

//鼠标循环
void cycMouse() 
{
	while (1)
	{
		//鼠标事件消息循环
		MOUSEMSG msg = { 0 };
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDBLCLK://鼠标左键双击

			if (msg.x > 30 && msg.x < 468 && msg.y>86 && msg.y < 163)//第一关（第二次第一关）
			{
				cyclMap();
				//通关之后
				//展开【下一关，选择关卡，退出游戏】图（13）
				start3();
				cycMouse();
				while (1)
				{
					//鼠标事件消息循环
					MOUSEMSG msg = { 0 };
					msg = GetMouseMsg();
					switch (msg.uMsg)
					{

					case WM_LBUTTONDBLCLK://鼠标左键双击

						if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//下一关,即第二关（第二次第二关）
						{
							cos++;//第二关
							cyclMap();

							/*通关之后
							展开【下一关，选择关卡，退出游戏】的图片（13）*/
							start3();
							cycMouse();

						}
						//重新选择关卡
						else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
						{
							//第三次显示
							start2();//显示【第一关，第二关，第三关】的图片（12）
							select();

						}

						//退出游戏
						else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
						{
							outtextxy(160, 250, "游戏退出中...");
							//关闭页面
							Sleep(2000);
							closegraph();//关闭图形界面
							exit(0);
						}

					}
				}
			}
			//第二关（第二次）
			else if (msg.x > 30 && msg.x < 468 && msg.y>250 && msg.y < 324)//第二关，通关之后在此循环图【下一关，选择关卡，退出游戏】的部分
			{
				cos++;//第二关
				cyclMap();
				//通关之后
				//展开【下一关，选择关卡，退出游戏】的图片（13）
				start3();

				while (1)//
				{
					//鼠标事件消息循环
					MOUSEMSG msg = { 0 };
					msg = GetMouseMsg();
					switch (msg.uMsg)
					{

					case WM_LBUTTONDBLCLK://鼠标左键双击
						//第二次显示的下一关
						if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//下一关,即第三关
						{
							cos = cos++;//第三关,2+1
							cyclMap();
							GameOverLayout();
						}
						//第二次显示关卡123
						else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//重新选择关卡
						{
							//第三次显示
							start2();//显示【第一关，第二关，第三关】的图片（12）
							select();

						}
						//退出游戏
						else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
						{
							outtextxy(160, 250, "游戏退出中...");
							//关闭页面
							Sleep(2000);
							closegraph();//关闭图形界面
							exit(0);
						}
					}
				}
			}
			//重新选择关卡
			else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
			{
				//第三次显示
				start2();//显示【第一关，第二关，第三关】的图片（12）
				select();


			}

			//退出游戏
			else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
			{
				outtextxy(160, 250, "游戏退出中...");
				//关闭页面
				Sleep(2000);
				closegraph();//关闭图形界面
				exit(0);
			}


			//第三关（第二次）
			else if (msg.x > 30 && msg.x < 468 && msg.y>415 && msg.y < 490)//第三关，则通关之后退出游戏
			{
				cos = cos + 2;//第三关
				cyclMap();
				GameOverLayout();
			}
		}
	}
	cycMouse();
}

//游戏主体
void Game()
{
	
	setbkmode(TRANSPARENT);  //设置背景透明
	settextcolor(RED);//文本背景设置
	//设置字体
	settextstyle(40, 0, "华文琥珀");
	//获取鼠标消息用于开始
	while (1)
	{
		//鼠标事件消息循环
		MOUSEMSG msg = { 0 };
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{

		case WM_LBUTTONDBLCLK://鼠标左键双击
			//开始游戏
			if (msg.x > 1 && msg.x < 123 && msg.y>251 && msg.y < 318)//开始游戏
			{
				start2();//显示【第一关，第二关，第三关】的图片（12)
									
				while (1)
				{
					//鼠标事件消息循环
					MOUSEMSG msg = { 0 };
					msg = GetMouseMsg();
					switch (msg.uMsg)
					{
					case WM_LBUTTONDBLCLK://鼠标左键双击
						//第一次第一关
						if (msg.x > 30 && msg.x < 468 && msg.y>86 && msg.y < 163)
						{
							
							cyclMap();
							
							//【下一关，选择关卡，退出游戏】（13）
							start3();							
							while (1)
							{
								//鼠标事件消息循环
								MOUSEMSG msg = { 0 };
								msg = GetMouseMsg();
								switch (msg.uMsg)
								{

								case WM_LBUTTONDBLCLK://鼠标左键双击


									if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//下一关,即第二关
									{
										cos++;//第二关
										cyclMap();
										//通关之后
										//展开【下一关，选择关卡，退出游戏】的图片（13）
										start3();
										while (1)//
										{
											//鼠标事件消息循环
											MOUSEMSG msg = { 0 };
											msg = GetMouseMsg();
											switch (msg.uMsg)
											{

											case WM_LBUTTONDBLCLK://鼠标左键双击
												//第二次显示的下一关
												if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//下一关,即第三关
												{

												

													cos = cos++;//第三关,2+1
													cyclMap();
													GameOverLayout();//游戏结束退出
													
												}
												//第二次显示关卡123
												else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//重新选择关卡
												{
													//第二次显示
													start2();//显示【第一关，第二关，第三关】的图			  
													while (1)
													{
														//鼠标事件消息循环
														MOUSEMSG msg = { 0 };
														msg = GetMouseMsg();
														switch (msg.uMsg)
														{
														case WM_LBUTTONDBLCLK://鼠标左键双击

															if (msg.x > 30 && msg.x < 468 && msg.y>86 && msg.y < 163)//第一关（第二次第一关）
															{
																cyclMap();
																//通关之后
																//展开【下一关，选择关卡，退出游戏】图（13）
																start3();
																cycMouse();
																while (1)
																{
																	//鼠标事件消息循环
																	MOUSEMSG msg = { 0 };
																	msg = GetMouseMsg();
																	switch (msg.uMsg)
																	{

																	case WM_LBUTTONDBLCLK://鼠标左键双击
																		
																		if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//下一关,即第二关（第二次第二关）
																		{
																			cos++;//第二关
																			cyclMap();
																			
																			/*通关之后
																			展开【下一关，选择关卡，退出游戏】的图片（13）*/
																			start3();
																			cycMouse();
																			
																		}
																		//重新选择关卡
																		else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
																		{
																			//第三次显示
																			start2();//显示【第一关，第二关，第三关】的图片（12）
																			select();
																			
																		}
																		
																		//退出游戏
																		else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
																		{
																		outtextxy(160, 250, "游戏退出中...");
																		//关闭页面
																		Sleep(2000);
																		closegraph();//关闭图形界面
																		exit(0);
																		}

																	}
																}
															}
															//第二关（第二次）
															else if (msg.x > 30 && msg.x < 468 && msg.y>250 && msg.y < 324)//第二关，通关之后在此循环图【下一关，选择关卡，退出游戏】的部分
															{
																cos++;//第二关
																cyclMap();
															//通关之后
															//展开【下一关，选择关卡，退出游戏】的图片（13）
																start3();

															while (1)//
															{
																//鼠标事件消息循环
																MOUSEMSG msg = { 0 };
																msg = GetMouseMsg();
																switch (msg.uMsg)
																{

																case WM_LBUTTONDBLCLK://鼠标左键双击
																	//第二次显示的下一关
																	if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//下一关,即第三关
																	{
																		cos = cos++;//第三关,2+1
																		cyclMap();
																		GameOverLayout();
																	}
																	//第二次显示关卡123
																	else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//重新选择关卡
																	{
																		//第三次显示
																		start2();//显示【第一关，第二关，第三关】的图片（12）
																		select();
																		
																	}
																	//退出游戏
																	else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
																	{
																		outtextxy(160, 250, "游戏退出中...");
																		//关闭页面
																		Sleep(2000);
																		closegraph();//关闭图形界面
																		exit(0);
																	}
																}
															}
														}
																		//重新选择关卡
															else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
															{
																//第三次显示
																start2();//显示【第一关，第二关，第三关】的图片（12）
																select();
																
																
															}

																		//退出游戏
															else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
																		{
																		outtextxy(160, 250, "游戏退出中...");
																		//关闭页面
																		Sleep(2000);
																		closegraph();//关闭图形界面
																		exit(0);
																		}

																
															//第三关（第二次）
															else if (msg.x > 30 && msg.x < 468 && msg.y>415 && msg.y < 490)//第三关，则通关之后退出游戏
															{
																cos = cos + 2;//第三关
																cyclMap();
																GameOverLayout();
															}
														}
													}
												}
												//退出游戏
												else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)//退出游戏
												{
												outtextxy(160, 250, "游戏退出中...");
												//关闭页面
												Sleep(2000);
												closegraph();//关闭图形界面
												exit(0);
												}
											}
										}
									}
									//重新选择关卡（第二关结束）
									else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//重新选择关卡
										{
											//第一次显示
											start2();//显示【第一关，第二关，第三关】的图片（12)
										
															
										while (1)
										{
											//鼠标事件消息循环
											MOUSEMSG msg = { 0 };
											msg = GetMouseMsg();
											switch (msg.uMsg)
											{
											case WM_LBUTTONDBLCLK://鼠标左键双击

												if (msg.x > 30 && msg.x < 468 && msg.y>86 && msg.y < 163)//第一关（第二次第一关）
												{
													cyclMap();

													//通关之后
													//展开【下一关，选择关卡，退出游戏】图（13）
													start3();
													while (1)
													{
														//鼠标事件消息循环
														MOUSEMSG msg = { 0 };
														msg = GetMouseMsg();
														switch (msg.uMsg)
														{

														case WM_LBUTTONDBLCLK://鼠标左键双击
															
															if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//下一关,即第二关（第二次第二关）
															{
																cos++;//第二关
																cyclMap();
																//通关之后
																//展开【下一关，选择关卡，退出游戏】的图片（13）
																start3();
																while (1)//
																{
																	//鼠标事件消息循环
																	MOUSEMSG msg = { 0 };
																	msg = GetMouseMsg();
																	switch (msg.uMsg)
																	{

																	case WM_LBUTTONDBLCLK://鼠标左键双击
																		//第二次显示的下一关
																		if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//下一关,即第三关
																		{
																			cos = cos++;//第三关,2+1
																			cyclMap();
																			GameOverLayout();
																		}
																		//第二次显示关卡123
																		else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//重新选择关卡
																		{
																			//第三次显示
																			start2();//显示【第一关，第二关，第三关】的图片（12）
																			select();
																			
																			
																		}
																		//退出游戏
																		else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
																		{
																			outtextxy(160, 250, "游戏退出中...");
																			//关闭页面
																			Sleep(2000);
																			closegraph();//关闭图形界面
																			exit(0);
																		}
																	}
																}
															}
															//重新选择关卡
															else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
															{
																//第三次显示
																start2();//显示【第一关，第二关，第三关】的图片（12）
																select();
																
															}

															//退出游戏
															else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
															{
																outtextxy(160, 250, "游戏退出中...");
																//关闭页面
																Sleep(2000);
																closegraph();//关闭图形界面
																exit(0);
															}

														}
													}
												}
												//第二关（第二次）
												else if (msg.x > 30 && msg.x < 468 && msg.y>250 && msg.y < 324)//第二关，通关之后在此循环图【下一关，选择关卡，退出游戏】的部分
												{
													cos++;//第二关
													cyclMap();
													//通关之后
													//展开【下一关，选择关卡，退出游戏】的图片（13）
													start3();

													while (1)//
													{
														//鼠标事件消息循环
														MOUSEMSG msg = { 0 };
														msg = GetMouseMsg();
														switch (msg.uMsg)
														{

														case WM_LBUTTONDBLCLK://鼠标左键双击
															//第二次显示的下一关
															if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//下一关,即第三关
															{
																cos = cos++;//第三关,2+1
																cyclMap();
																GameOverLayout();
															}
															//第二次显示关卡123
															else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//重新选择关卡
															{
																//第三次显示
																start2();//显示【第一关，第二关，第三关】的图片（12）
																select();
																
															}
															//退出游戏
															else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
															{
																outtextxy(160, 250, "游戏退出中...");
																//关闭页面
																Sleep(2000);
																closegraph();//关闭图形界面
																exit(0);
															}
														}
													}
												}
												//重新选择关卡
												else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
												{
													//第三次显示
													start2();//显示【第一关，第二关，第三关】的图片（12）
													select();
													
												}

												//退出游戏
												else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
												{
													outtextxy(160, 250, "游戏退出中...");
													//关闭页面
													Sleep(2000);
													closegraph();//关闭图形界面
													exit(0);
												}


												//第三关（第二次）
												else if (msg.x > 30 && msg.x < 468 && msg.y>415 && msg.y < 490)//第三关，则通关之后退出游戏
												{
													cos = cos + 2;//第三关
													cyclMap();
													GameOverLayout();
												}
											}
										}
									}
									
									//退出游戏
									else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)//退出游戏
									{
									outtextxy(160, 250, "游戏退出中...");
									//关闭页面
									Sleep(2000);
									closegraph();//关闭图形界面
									exit(0);
									}
								}

							}
						}
						//第一次第二关
						else if (msg.x > 30 && msg.x < 468 && msg.y>250 && msg.y < 324)//第二关
						{	
						
							cos++;//第二关
							cyclMap();
							start3();
							
						while (1)//
						{
							//鼠标事件消息循环
							MOUSEMSG msg = { 0 };
							msg = GetMouseMsg();
							switch (msg.uMsg)
							{

							case WM_LBUTTONDBLCLK://鼠标左键双击
								//下一关,即第三关
								if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//下一关,即第三关
								{
									cos = cos++;//第三关,2+1
									cyclMap();
									GameOverLayout();


								}
								//重新选择关卡（第二关结束）
								else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//重新选择关卡
								{
									//显示【第一关，第二关，第三关】的图片（12)
									start2();
									
									//
									//
									//BUG
									select();
								}
								//退出游戏
								else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)//退出游戏
								{
									outtextxy(160, 250, "游戏退出中...");
									//关闭页面
									Sleep(2000);
									closegraph();//关闭图形界面
									exit(0);
								}
							}
						}
						}

						//第一次第三关
						else if (msg.x > 30 && msg.x < 468 && msg.y>415 && msg.y < 490)//第三关
						{
							cos = cos + 2;//第三关
							cyclMap(); 
							GameOverLayout();
						}
					}
				}
			}
			//退出始游戏
			else if (msg.x > 1 && msg.x < 113 && msg.y>360 && msg.y < 430)//退出始游戏
			{
				outtextxy(160, 250, "游戏退出中...");
				Sleep(2000);
				closegraph();//关闭图形界面
				exit(0);
			}
			//音乐开
			else if (msg.x > 385 && msg.x < 495 && msg.y>243 && msg.y < 325)//音乐开
			{
				mciSendString(TEXT("open fun.MP3 alias mysong"), NULL, 0, NULL);//open-操作方式，alias-- 定义了该音乐文件的别名为fun
				mciSendString(TEXT("play mysong "), NULL, 0, NULL);
			}
			//音乐关
			else if (msg.x > 385 && msg.x < 495 && msg.y>360 && msg.y < 438)//音乐开
			{
			    mciSendString(TEXT("close mysong "), NULL, 0, NULL);
			}
		}
	}
}																																				
