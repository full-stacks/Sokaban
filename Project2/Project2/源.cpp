
#include <graphics.h> //ͼ�ν���� ��imagesize() ͼ��洢��С������putimage() ���ͼ����
#include <conio.h>//����_getch()����ͷ�ļ� 
#include <stdio.h>
#include<Windows.h>
#pragma comment(lib,"winmm.lib")//���ֲ�����Ҫ��ͷ�ļ�
using namespace std;

/*��������*/
void LoadResource();//������Դ��������ӣ��յأ�Ŀ�ĵص�ͼƬ)  239
void DrawMap();      //��ͼģ�飬���Ƶ�ͼ      80
void keyDown();     //�����ƶ�  117
int GameOver();    ////�жϹؿ��Ƿ���� 250
void start1();    //��ʼ����Ϸҳ���ͼ 210
void start2();   //��һ�ء��ڶ��ء������ص�ͼ���ı��� 219
void start3();  //��һ�أ�ѡ��ؿ����˳���Ϸ��ͼ 231
void GameOverLayout();//ͨ��֮��չʾͼƬ���رճ��� 268
void select();       //ѡ���һ��,�ڶ��أ������ء� 298
void cycMouse();    //���ѭ�� 336
void cyclMap();   //ѭ����ͼ  282
void Game();     //��Ϸ���� 476

//ͼƬ���г�ʼ�����յأ�ǽ��Ŀ�ĵأ����ӣ�������ӵ���Ŀ�ĵ�,�˵�Ŀ�ĵص�ͼƬ)
int imgIndex[6] = { 0,1,3,4,5,7 }; 
IMAGE img[6];

//��ʼ���ؿ�
int cos = 0;

//��ͼ����ά���� map[cos][i][j]
/*0�յأ�1ǽ��3Ŀ�ĵأ�4���ӣ�5��*/
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

//mian����
int main()
{
	void DrawMap();
	LoadResource();  //������Դ
	Game();
}

/*��������*/
//��ͼģ�飬���Ƶ�ͼ
void DrawMap()  //��ͼģ�飬���Ƶ�ͼ
{               //���������е�ֵ,����Ӧ����ŵ�ͼ
	int x, y;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//����ƽ��ͼ����Ҫ��x��y����
			x = 50 * j;    
			y = 50 * i;   
			switch (map[cos][i][j])
			{
			case 0:     //�յ�
				putimage(x, y, img + 0);//���յ�ͼƬ
				break;
			case 1:     //ǽ��
				putimage(x, y, img + 1);
				break;
			case 3:     //Ŀ�ĵ�
				putimage(x, y, img + 2);
				break;
			case 4:		//����
				putimage(x, y, img + 3); 
				break;
			case 5:     //��
				putimage(x, y, img + 4);
				break;
			case 7:     //4+3   ���ӵ���Ŀ�ĵ�
				putimage(x, y, img + 5);
				break;
			case 8:     //5+3  ����Ŀ�ĵ��غ�
				putimage(x, y, img + 4);
				break;
			}
		}
	}
}

//�����ƶ�
void keyDown()
{
	int i, j; //��������λ��
	for (i = 0; i < 10; i++)//iΪ��ֵ 
	{
		for (j = 0; j < 10; j++)//jΪ��ֵ 
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
	case 'W':/*����*/
	case 'w':
	case 72:
		if (map[cos][i - 1][j] == 0 || map[cos][i - 1][j] == 3)//�����Ϸ��ǿյ�(0)����Ŀ�ĵ� (3)
		{
			map[cos][i - 1][j] += 5;//����������һ������ֵΪ5(����) 
			map[cos][i][j] -= 5;//����ԭ����ֵΪ0(�յ�) 
		}
		else if (map[cos][i - 1][j] == 4 || map[cos][i - 1][j] == 7)//�����Ϸ������ӣ������ڿո��ϻ���������Ŀ�ĵش� 
		{
			if (map[cos][i - 2][j] == 0 || map[cos][i - 2][j] == 3)//�����Ϸ��ǿո����ǰ����Ŀ�ĵ�
			{
				map[cos][i - 2][j] += 4;//���������ƶ�����һ��0(�յ�)�ͱ�Ϊ 4(����)
				map[cos][i - 1][j] += 1;//4(ԭ����)+1��Ϊ 5(����)
				map[cos][i][j] -= 5;//5(ԭ����)-5��Ϊ0(�յ�) 
			}
		}
		break;
	case 'S':/*����*/
	case 's':
	case 80:
		if (map[cos][i + 1][j] == 0 || map[cos][i + 1][j] == 3)//���·��ǿյػ�Ŀ�ĵ� 
		{
			map[cos][i + 1][j] += 5;
			map[cos][i][j] -= 5;
		}
		else if (map[cos][i + 1][j] == 4 || map[cos][i + 1][j] == 7)//���·������� �������ڿյػ���Ŀ�ĵ��� 
		{
			if (map[cos][i + 2][j] == 0 || map[cos][i + 2][j] == 3)//�����·��ǿյغ�Ŀ�ĵ�
			{
				map[cos][i + 2][j] += 4;//���������ƶ�����һ��0(�յ�)�ͱ�Ϊ 4(����)
				map[cos][i + 1][j] += 1;//4(ԭ����)+1��Ϊ 5(����)
				map[cos][i][j] -= 5;//5(ԭ����)-5��Ϊ0(�յ�) 
			}
		}
		break;
	case 'A':
	case 'a':
	case 75:
		if (map[cos][i][j - 1] == 0 || map[cos][i][j - 1] == 3)//�����ǿյػ�Ŀ�ĵ� 
		{
			map[cos][i][j - 1] += 5;
			map[cos][i][j] -= 5;
		}
		else if (map[cos][i][j - 1] == 4 || map[cos][i][j - 1] == 7)//���������� �������ڿյػ���Ŀ�ĵ���
		{
			if (map[cos][i][j - 2] == 0 || map[cos][i][j - 2] == 3)//�������ǿյغ�Ŀ�ĵ�
			{
				map[cos][i][j - 2] += 4;//���������ƶ�����һ��0(�յ�)�ͱ�Ϊ 4(����)
				map[cos][i][j - 1] += 1;//4(ԭ����)+1��Ϊ 5(����)
				map[cos][i][j] -= 5;//5(ԭ����)-5��Ϊ0(�յ�) 
			}
		}
		break;
	case 'D':
	case 'd':
	case 77:
		if (map[cos][i][j + 1] == 0 || map[cos][i][j + 1] == 3)//���ҷ��ǿյػ�Ŀ�ĵ� 
		{
			map[cos][i][j + 1] += 5;
			map[cos][i][j] -= 5;
		}
		else if (map[cos][i][j + 1] == 4 || map[cos][i][j + 1] == 7)//���ҷ������� �������ڿյػ���Ŀ�ĵ���
		{
			if (map[cos][i][j + 2] == 0 || map[cos][i][j + 2] == 3)//�����ҷ��ǿյغ�Ŀ�ĵ�
			{
				map[cos][i][j + 2] += 4;//���������ƶ�����һ��0(�յ�)�ͱ�Ϊ 4(����)
				map[cos][i][j + 1] += 1;//4(ԭ����)+1��Ϊ 5(����)
				map[cos][i][j] -= 5;//5(ԭ����)-5��Ϊ0(�յ�) 
			}
		}
		break;
	}
}




//��ʼ��Ϸҳ���ͼ
void start1()//��ʼҳ���ͼ
{
	initgraph(50 * 10, 50 * 10);//չ������
	IMAGE st;
	loadimage(&st, "11.jpg", 500, 500);
	putimage(0, 0, &st);
}

//��һ�ء��ڶ��ء������ص�ͼ���ı���
void start2()//��һ�أ��ڶ��أ������ص�ͼ��12��
{
	initgraph(50 * 10, 50 * 10);//չ������
	settextcolor(RED);//�ı��������ú�ɫ
	outtextxy(160, 250, "��Ϸ������...");
	//���س����趨ʱ��
	Sleep(1000);
	IMAGE st;
	loadimage(&st, "12.jpg", 500, 500);
	putimage(0, 0, &st);
}

//��һ�أ�ѡ��ؿ����˳���Ϸ��ͼ
void start3()//��һ�أ�ѡ��ؿ����˳���Ϸ��ͼ(13)
{
	IMAGE st;
	loadimage(&st, "13.jpg", 500, 500);
	putimage(0, 0, &st);
}

//����������ӣ��յأ�Ŀ�ĵص�ͼƬ
void LoadResource()
{
	initgraph(50 * 10, 50 * 10);//չ������
	for (int i = 0; i < 6; i++)
	{
		char filename[20] = "";
		sprintf_s(filename, "%d.jpg", imgIndex[i]);//���ݸ�ʽ��������ַ�����Ҳ���Ǹ�ʽ�������ļ��ŵ��ַ�����
		loadimage(img + i, filename, 50, 50);//��ȡͼƬ�ļ�
	}
}

//�жϹؿ��Ƿ�������Ƿ�������δ��
int GameOver()
{
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[cos][i][j] == 4)//������û��4�����ӣ� ���������Ӷ���λ������1 
			{
				count = 0;
				return 0;
			}
		}
	}
	return 1;
}

//ͨ��֮��չʾͼƬ���رճ���
void GameOverLayout()
{
	Sleep(1000);
	outtextxy(160, 250, "��Ϸͨ��...");//�ı���ʾ�ڻ����ϣ���Ϸͨ��
	//ͨ��֮��չʾ���յ���Ƭ
	Sleep(1000);
	IMAGE g;
	loadimage(&g, "��ϲ��ͨ��.jpg", 500, 500);
	putimage(0, 0, &g);
	Sleep(2000);
	exit(0);
}

//��ͼѭ��
void cyclMap()
{
	settextcolor(YELLOW);
	outtextxy(160, 250, "�ؿ�������...");
	Sleep(1000);//�ӳ�1��
	while (1)//��ͼѭ��
	{
		DrawMap();
		keyDown();
		if (GameOver())

			break;////ͨ��֮��							
	}
}

//ѡ���һ��,�ڶ��أ������ء�
void select()
{

	while (1)
	{
		//����¼���Ϣѭ��
		MOUSEMSG msg = { 0 };
		msg = GetMouseMsg();//��ȡ�������
		switch (msg.uMsg)
		{
		case WM_LBUTTONDBLCLK://������˫��

			//��һ��
			if (msg.x > 30 && msg.x < 468 && msg.y>86 && msg.y < 163)
			{
				cos;
				cyclMap();
				GameOverLayout();
			}
			//�ڶ���
			else if (msg.x > 30 && msg.x < 468 && msg.y>250 && msg.y < 324)
			{
				cos++;//�ڶ���
				cyclMap();
				GameOverLayout();
			}
			//������
			else if (msg.x > 30 && msg.x < 468 && msg.y>415 && msg.y < 490)
			{
				cos = cos + 2;//������
				cyclMap();
				GameOverLayout();
			}
		}
	}
}

//���ѭ��
void cycMouse() 
{
	while (1)
	{
		//����¼���Ϣѭ��
		MOUSEMSG msg = { 0 };
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDBLCLK://������˫��

			if (msg.x > 30 && msg.x < 468 && msg.y>86 && msg.y < 163)//��һ�أ��ڶ��ε�һ�أ�
			{
				cyclMap();
				//ͨ��֮��
				//չ������һ�أ�ѡ��ؿ����˳���Ϸ��ͼ��13��
				start3();
				cycMouse();
				while (1)
				{
					//����¼���Ϣѭ��
					MOUSEMSG msg = { 0 };
					msg = GetMouseMsg();
					switch (msg.uMsg)
					{

					case WM_LBUTTONDBLCLK://������˫��

						if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//��һ��,���ڶ��أ��ڶ��εڶ��أ�
						{
							cos++;//�ڶ���
							cyclMap();

							/*ͨ��֮��
							չ������һ�أ�ѡ��ؿ����˳���Ϸ����ͼƬ��13��*/
							start3();
							cycMouse();

						}
						//����ѡ��ؿ�
						else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
						{
							//��������ʾ
							start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12��
							select();

						}

						//�˳���Ϸ
						else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
						{
							outtextxy(160, 250, "��Ϸ�˳���...");
							//�ر�ҳ��
							Sleep(2000);
							closegraph();//�ر�ͼ�ν���
							exit(0);
						}

					}
				}
			}
			//�ڶ��أ��ڶ��Σ�
			else if (msg.x > 30 && msg.x < 468 && msg.y>250 && msg.y < 324)//�ڶ��أ�ͨ��֮���ڴ�ѭ��ͼ����һ�أ�ѡ��ؿ����˳���Ϸ���Ĳ���
			{
				cos++;//�ڶ���
				cyclMap();
				//ͨ��֮��
				//չ������һ�أ�ѡ��ؿ����˳���Ϸ����ͼƬ��13��
				start3();

				while (1)//
				{
					//����¼���Ϣѭ��
					MOUSEMSG msg = { 0 };
					msg = GetMouseMsg();
					switch (msg.uMsg)
					{

					case WM_LBUTTONDBLCLK://������˫��
						//�ڶ�����ʾ����һ��
						if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//��һ��,��������
						{
							cos = cos++;//������,2+1
							cyclMap();
							GameOverLayout();
						}
						//�ڶ�����ʾ�ؿ�123
						else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//����ѡ��ؿ�
						{
							//��������ʾ
							start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12��
							select();

						}
						//�˳���Ϸ
						else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
						{
							outtextxy(160, 250, "��Ϸ�˳���...");
							//�ر�ҳ��
							Sleep(2000);
							closegraph();//�ر�ͼ�ν���
							exit(0);
						}
					}
				}
			}
			//����ѡ��ؿ�
			else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
			{
				//��������ʾ
				start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12��
				select();


			}

			//�˳���Ϸ
			else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
			{
				outtextxy(160, 250, "��Ϸ�˳���...");
				//�ر�ҳ��
				Sleep(2000);
				closegraph();//�ر�ͼ�ν���
				exit(0);
			}


			//�����أ��ڶ��Σ�
			else if (msg.x > 30 && msg.x < 468 && msg.y>415 && msg.y < 490)//�����أ���ͨ��֮���˳���Ϸ
			{
				cos = cos + 2;//������
				cyclMap();
				GameOverLayout();
			}
		}
	}
	cycMouse();
}

//��Ϸ����
void Game()
{
	
	setbkmode(TRANSPARENT);  //���ñ���͸��
	settextcolor(RED);//�ı���������
	//��������
	settextstyle(40, 0, "��������");
	//��ȡ�����Ϣ���ڿ�ʼ
	while (1)
	{
		//����¼���Ϣѭ��
		MOUSEMSG msg = { 0 };
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{

		case WM_LBUTTONDBLCLK://������˫��
			//��ʼ��Ϸ
			if (msg.x > 1 && msg.x < 123 && msg.y>251 && msg.y < 318)//��ʼ��Ϸ
			{
				start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12)
									
				while (1)
				{
					//����¼���Ϣѭ��
					MOUSEMSG msg = { 0 };
					msg = GetMouseMsg();
					switch (msg.uMsg)
					{
					case WM_LBUTTONDBLCLK://������˫��
						//��һ�ε�һ��
						if (msg.x > 30 && msg.x < 468 && msg.y>86 && msg.y < 163)
						{
							
							cyclMap();
							
							//����һ�أ�ѡ��ؿ����˳���Ϸ����13��
							start3();							
							while (1)
							{
								//����¼���Ϣѭ��
								MOUSEMSG msg = { 0 };
								msg = GetMouseMsg();
								switch (msg.uMsg)
								{

								case WM_LBUTTONDBLCLK://������˫��


									if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//��һ��,���ڶ���
									{
										cos++;//�ڶ���
										cyclMap();
										//ͨ��֮��
										//չ������һ�أ�ѡ��ؿ����˳���Ϸ����ͼƬ��13��
										start3();
										while (1)//
										{
											//����¼���Ϣѭ��
											MOUSEMSG msg = { 0 };
											msg = GetMouseMsg();
											switch (msg.uMsg)
											{

											case WM_LBUTTONDBLCLK://������˫��
												//�ڶ�����ʾ����һ��
												if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//��һ��,��������
												{

												

													cos = cos++;//������,2+1
													cyclMap();
													GameOverLayout();//��Ϸ�����˳�
													
												}
												//�ڶ�����ʾ�ؿ�123
												else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//����ѡ��ؿ�
												{
													//�ڶ�����ʾ
													start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼ			  
													while (1)
													{
														//����¼���Ϣѭ��
														MOUSEMSG msg = { 0 };
														msg = GetMouseMsg();
														switch (msg.uMsg)
														{
														case WM_LBUTTONDBLCLK://������˫��

															if (msg.x > 30 && msg.x < 468 && msg.y>86 && msg.y < 163)//��һ�أ��ڶ��ε�һ�أ�
															{
																cyclMap();
																//ͨ��֮��
																//չ������һ�أ�ѡ��ؿ����˳���Ϸ��ͼ��13��
																start3();
																cycMouse();
																while (1)
																{
																	//����¼���Ϣѭ��
																	MOUSEMSG msg = { 0 };
																	msg = GetMouseMsg();
																	switch (msg.uMsg)
																	{

																	case WM_LBUTTONDBLCLK://������˫��
																		
																		if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//��һ��,���ڶ��أ��ڶ��εڶ��أ�
																		{
																			cos++;//�ڶ���
																			cyclMap();
																			
																			/*ͨ��֮��
																			չ������һ�أ�ѡ��ؿ����˳���Ϸ����ͼƬ��13��*/
																			start3();
																			cycMouse();
																			
																		}
																		//����ѡ��ؿ�
																		else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
																		{
																			//��������ʾ
																			start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12��
																			select();
																			
																		}
																		
																		//�˳���Ϸ
																		else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
																		{
																		outtextxy(160, 250, "��Ϸ�˳���...");
																		//�ر�ҳ��
																		Sleep(2000);
																		closegraph();//�ر�ͼ�ν���
																		exit(0);
																		}

																	}
																}
															}
															//�ڶ��أ��ڶ��Σ�
															else if (msg.x > 30 && msg.x < 468 && msg.y>250 && msg.y < 324)//�ڶ��أ�ͨ��֮���ڴ�ѭ��ͼ����һ�أ�ѡ��ؿ����˳���Ϸ���Ĳ���
															{
																cos++;//�ڶ���
																cyclMap();
															//ͨ��֮��
															//չ������һ�أ�ѡ��ؿ����˳���Ϸ����ͼƬ��13��
																start3();

															while (1)//
															{
																//����¼���Ϣѭ��
																MOUSEMSG msg = { 0 };
																msg = GetMouseMsg();
																switch (msg.uMsg)
																{

																case WM_LBUTTONDBLCLK://������˫��
																	//�ڶ�����ʾ����һ��
																	if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//��һ��,��������
																	{
																		cos = cos++;//������,2+1
																		cyclMap();
																		GameOverLayout();
																	}
																	//�ڶ�����ʾ�ؿ�123
																	else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//����ѡ��ؿ�
																	{
																		//��������ʾ
																		start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12��
																		select();
																		
																	}
																	//�˳���Ϸ
																	else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
																	{
																		outtextxy(160, 250, "��Ϸ�˳���...");
																		//�ر�ҳ��
																		Sleep(2000);
																		closegraph();//�ر�ͼ�ν���
																		exit(0);
																	}
																}
															}
														}
																		//����ѡ��ؿ�
															else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
															{
																//��������ʾ
																start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12��
																select();
																
																
															}

																		//�˳���Ϸ
															else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
																		{
																		outtextxy(160, 250, "��Ϸ�˳���...");
																		//�ر�ҳ��
																		Sleep(2000);
																		closegraph();//�ر�ͼ�ν���
																		exit(0);
																		}

																
															//�����أ��ڶ��Σ�
															else if (msg.x > 30 && msg.x < 468 && msg.y>415 && msg.y < 490)//�����أ���ͨ��֮���˳���Ϸ
															{
																cos = cos + 2;//������
																cyclMap();
																GameOverLayout();
															}
														}
													}
												}
												//�˳���Ϸ
												else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)//�˳���Ϸ
												{
												outtextxy(160, 250, "��Ϸ�˳���...");
												//�ر�ҳ��
												Sleep(2000);
												closegraph();//�ر�ͼ�ν���
												exit(0);
												}
											}
										}
									}
									//����ѡ��ؿ����ڶ��ؽ�����
									else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//����ѡ��ؿ�
										{
											//��һ����ʾ
											start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12)
										
															
										while (1)
										{
											//����¼���Ϣѭ��
											MOUSEMSG msg = { 0 };
											msg = GetMouseMsg();
											switch (msg.uMsg)
											{
											case WM_LBUTTONDBLCLK://������˫��

												if (msg.x > 30 && msg.x < 468 && msg.y>86 && msg.y < 163)//��һ�أ��ڶ��ε�һ�أ�
												{
													cyclMap();

													//ͨ��֮��
													//չ������һ�أ�ѡ��ؿ����˳���Ϸ��ͼ��13��
													start3();
													while (1)
													{
														//����¼���Ϣѭ��
														MOUSEMSG msg = { 0 };
														msg = GetMouseMsg();
														switch (msg.uMsg)
														{

														case WM_LBUTTONDBLCLK://������˫��
															
															if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//��һ��,���ڶ��أ��ڶ��εڶ��أ�
															{
																cos++;//�ڶ���
																cyclMap();
																//ͨ��֮��
																//չ������һ�أ�ѡ��ؿ����˳���Ϸ����ͼƬ��13��
																start3();
																while (1)//
																{
																	//����¼���Ϣѭ��
																	MOUSEMSG msg = { 0 };
																	msg = GetMouseMsg();
																	switch (msg.uMsg)
																	{

																	case WM_LBUTTONDBLCLK://������˫��
																		//�ڶ�����ʾ����һ��
																		if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//��һ��,��������
																		{
																			cos = cos++;//������,2+1
																			cyclMap();
																			GameOverLayout();
																		}
																		//�ڶ�����ʾ�ؿ�123
																		else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//����ѡ��ؿ�
																		{
																			//��������ʾ
																			start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12��
																			select();
																			
																			
																		}
																		//�˳���Ϸ
																		else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
																		{
																			outtextxy(160, 250, "��Ϸ�˳���...");
																			//�ر�ҳ��
																			Sleep(2000);
																			closegraph();//�ر�ͼ�ν���
																			exit(0);
																		}
																	}
																}
															}
															//����ѡ��ؿ�
															else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
															{
																//��������ʾ
																start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12��
																select();
																
															}

															//�˳���Ϸ
															else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
															{
																outtextxy(160, 250, "��Ϸ�˳���...");
																//�ر�ҳ��
																Sleep(2000);
																closegraph();//�ر�ͼ�ν���
																exit(0);
															}

														}
													}
												}
												//�ڶ��أ��ڶ��Σ�
												else if (msg.x > 30 && msg.x < 468 && msg.y>250 && msg.y < 324)//�ڶ��أ�ͨ��֮���ڴ�ѭ��ͼ����һ�أ�ѡ��ؿ����˳���Ϸ���Ĳ���
												{
													cos++;//�ڶ���
													cyclMap();
													//ͨ��֮��
													//չ������һ�أ�ѡ��ؿ����˳���Ϸ����ͼƬ��13��
													start3();

													while (1)//
													{
														//����¼���Ϣѭ��
														MOUSEMSG msg = { 0 };
														msg = GetMouseMsg();
														switch (msg.uMsg)
														{

														case WM_LBUTTONDBLCLK://������˫��
															//�ڶ�����ʾ����һ��
															if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//��һ��,��������
															{
																cos = cos++;//������,2+1
																cyclMap();
																GameOverLayout();
															}
															//�ڶ�����ʾ�ؿ�123
															else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//����ѡ��ؿ�
															{
																//��������ʾ
																start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12��
																select();
																
															}
															//�˳���Ϸ
															else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
															{
																outtextxy(160, 250, "��Ϸ�˳���...");
																//�ر�ҳ��
																Sleep(2000);
																closegraph();//�ر�ͼ�ν���
																exit(0);
															}
														}
													}
												}
												//����ѡ��ؿ�
												else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)
												{
													//��������ʾ
													start2();//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12��
													select();
													
												}

												//�˳���Ϸ
												else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)
												{
													outtextxy(160, 250, "��Ϸ�˳���...");
													//�ر�ҳ��
													Sleep(2000);
													closegraph();//�ر�ͼ�ν���
													exit(0);
												}


												//�����أ��ڶ��Σ�
												else if (msg.x > 30 && msg.x < 468 && msg.y>415 && msg.y < 490)//�����أ���ͨ��֮���˳���Ϸ
												{
													cos = cos + 2;//������
													cyclMap();
													GameOverLayout();
												}
											}
										}
									}
									
									//�˳���Ϸ
									else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)//�˳���Ϸ
									{
									outtextxy(160, 250, "��Ϸ�˳���...");
									//�ر�ҳ��
									Sleep(2000);
									closegraph();//�ر�ͼ�ν���
									exit(0);
									}
								}

							}
						}
						//��һ�εڶ���
						else if (msg.x > 30 && msg.x < 468 && msg.y>250 && msg.y < 324)//�ڶ���
						{	
						
							cos++;//�ڶ���
							cyclMap();
							start3();
							
						while (1)//
						{
							//����¼���Ϣѭ��
							MOUSEMSG msg = { 0 };
							msg = GetMouseMsg();
							switch (msg.uMsg)
							{

							case WM_LBUTTONDBLCLK://������˫��
								//��һ��,��������
								if (msg.x > 143 && msg.x < 328 && msg.y>39 && msg.y < 137)//��һ��,��������
								{
									cos = cos++;//������,2+1
									cyclMap();
									GameOverLayout();


								}
								//����ѡ��ؿ����ڶ��ؽ�����
								else if (msg.x > 153 && msg.x < 335 && msg.y>187 && msg.y < 384)//����ѡ��ؿ�
								{
									//��ʾ����һ�أ��ڶ��أ������ء���ͼƬ��12)
									start2();
									
									//
									//
									//BUG
									select();
								}
								//�˳���Ϸ
								else if (msg.x > 166 && msg.x < 335 && msg.y>333 && msg.y < 413)//�˳���Ϸ
								{
									outtextxy(160, 250, "��Ϸ�˳���...");
									//�ر�ҳ��
									Sleep(2000);
									closegraph();//�ر�ͼ�ν���
									exit(0);
								}
							}
						}
						}

						//��һ�ε�����
						else if (msg.x > 30 && msg.x < 468 && msg.y>415 && msg.y < 490)//������
						{
							cos = cos + 2;//������
							cyclMap(); 
							GameOverLayout();
						}
					}
				}
			}
			//�˳�ʼ��Ϸ
			else if (msg.x > 1 && msg.x < 113 && msg.y>360 && msg.y < 430)//�˳�ʼ��Ϸ
			{
				outtextxy(160, 250, "��Ϸ�˳���...");
				Sleep(2000);
				closegraph();//�ر�ͼ�ν���
				exit(0);
			}
			//���ֿ�
			else if (msg.x > 385 && msg.x < 495 && msg.y>243 && msg.y < 325)//���ֿ�
			{
				mciSendString(TEXT("open fun.MP3 alias mysong"), NULL, 0, NULL);//open-������ʽ��alias-- �����˸������ļ��ı���Ϊfun
				mciSendString(TEXT("play mysong "), NULL, 0, NULL);
			}
			//���ֹ�
			else if (msg.x > 385 && msg.x < 495 && msg.y>360 && msg.y < 438)//���ֿ�
			{
			    mciSendString(TEXT("close mysong "), NULL, 0, NULL);
			}
		}
	}
}																																				
