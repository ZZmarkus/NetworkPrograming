#pragma warning(disable:4996)
#include <stdio.h>
#include <conio.h>             
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <process.h>

#define BUF_SIZE 100

unsigned WINAPI SendMsg(void *arg);

int Odello();
void ErrorHandlling(char *msg);

int place(int, int, int, int(*)[21]);
void display();

int arr[21][21] = { 0 };
int clntCnt = 0;
char ch[2];
int turn = 0;
int x = 8, y = 8;
int i, j;
int num;
int a = 1, b = 1, c = 0;
int b_n = 0;
int w_n = 0;

clock_t  start, mid, end;
HANDLE hMutex;

int main(int argc, char *argv[]) {
	arr[10][10] = { 1 };
	arr[11][11] = { 1 };
	arr[10][11] = { 2 };
	arr[11][10] = { 2 };
	WSADATA wsaData;
	SOCKET hSock;
	SOCKADDR_IN servAdr;
	HANDLE hSndThread, hRcvThread;


	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandlling("WSAStartup() error!");

	hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(argv[1]);
	servAdr.sin_port = htons(atoi(argv[2]));

	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandlling("connect() error");

	int select = 0;
	display();
	scanf("%d", &select);

	if (select == 1) {
		Odello();
	}
	else if (select == 2) {
		start = clock();
		while (1) {

			b_n = 0;
			w_n = 0;
			system("cls");

			for (i = 0; i < 21; i++) {
				for (j = 0; j < 21; j++) {
					switch (arr[i][j]) {
					case 0:
						printf(" ��");
						break;
					case 1:
						printf("��");
						b_n++;
						break;
					case 2:
						printf("��");
						w_n++;
						break;
					case 3:
						printf("��");
						b_n++;
						break;
					case 4:
						printf("��");
						w_n++;
						break;
					case 5:
						printf("��");
						b_n++;
						break;
					case 6:
						printf("��");
						w_n++;
						break;

					}
				}
				printf("\n");
			}

			printf("\t �鵹 vs �浹\n");
			mid = clock();

			printf("\t  %d vs  %d\t%d�� ���", b_n, w_n, (int)((mid - start) / 1000));

			if (turn % 2 == 0) {
				b_n--;
				printf("\t �鵹�� �Դϴ�. \n");
			}
			else {
				w_n--;
				printf("\t �浹�� �Դϴ�. \n");
			}


			if ((int)((mid - start) / 1000) > 10 * 20) { //�¸� ����1
				system("cls");
				printf("\t �浹 vs �鵹\n");
				printf("\t  %d vs  %d\n", b_n, w_n);
				if (b_n > w_n)
					printf("�浹 ��!\n");
				else
					printf("�鵹 ��!\n");
			}

			if (b_n > 40) {                                          // �¸� ����2
				system("cls");
				printf("�浹 �¸�!");
			}
			else if (w_n > 40) {
				system("cls");
				printf("�鵹 �¸�!");
			}


			hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSock, 0, NULL);
			recv(hSock, ch, 1, 0);


			if (turn % 2 == 0) {
				switch (ch[0]) {
				case 'a':
					if (x == 0)
						break;
					switch (arr[y][x - 1]) {
					case 0:
						arr[y][x - 1] = 1;
						break;
					case 1:
						arr[y][x - 1] = 3;
						break;
					case 2:
						arr[y][x - 1] = 4;
						break;
					}
					switch (arr[y][x]) {
					case 1:
						arr[y][x] = 0;
						break;
					case 2:
						arr[y][x] = 0;
						break;
					case 3:
						arr[y][x] = 1;
						break;
					case 4:
						arr[y][x] = 2;
						break;
					case 5:
						arr[y][x] = 1;
						break;
					case 6:
						arr[y][x] = 2;
						break;
					}
					x--;
					num = 1;
					break;
				case 'd':
					if (x == 20)
						break;

					switch (arr[y][x + 1]) {
					case 0:
						arr[y][x + 1] = 1;
						break;
					case 1:
						arr[y][x + 1] = 3;
						break;
					case 2:
						arr[y][x + 1] = 4;
						break;
					}
					switch (arr[y][x]) {
					case 1:
						arr[y][x] = 0;
						break;
					case 2:
						arr[y][x] = 0;
						break;
					case 3:
						arr[y][x] = 1;
						break;
					case 4:
						arr[y][x] = 2;
						break;
					case 5:
						arr[y][x] = 1;
						break;
					case 6:
						arr[y][x] = 2;
						break;
					}
					x++;
					num = 2;
					break;
				case 'w':
					if (y == 0)
						break;
					switch (arr[y - 1][x]) {
					case 0:
						arr[y - 1][x] = 1;
						break;
					case 1:
						arr[y - 1][x] = 3;
						break;
					case 2:
						arr[y - 1][x] = 4;
						break;
					}
					switch (arr[y][x]) {
					case 1:
						arr[y][x] = 0;
						break;
					case 2:
						arr[y][x] = 0;
						break;
					case 3:
						arr[y][x] = 1;
						break;
					case 4:
						arr[y][x] = 2;
						break;
					case 5:
						arr[y][x] = 1;
						break;
					case 6:
						arr[y][x] = 2;
						break;
					}
					num = 3;
					y--;
					break;
				case 's':
					if (y == 20)
						break;
					switch (arr[y + 1][x]) {
					case 0:
						arr[y + 1][x] = 1;
						break;
					case 1:
						arr[y + 1][x] = 3;
						break;
					case 2:
						arr[y + 1][x] = 4;
						break;
					}
					switch (arr[y][x]) {
					case 1:
						arr[y][x] = 0;
						break;
					case 2:
						arr[y][x] = 0;
						break;
					case 3:
						arr[y][x] = 1;
						break;
					case 4:
						arr[y][x] = 2;
						break;
					case 5:
						arr[y][x] = 1;
						break;
					case 6:
						arr[y][x] = 2;
						break;
					}
					num = 4;
					y++;
					break;
				case 'f': //������ ������� �� �� ���̿� ���̰Բ� ����� ��
					if (arr[y][x] == 1) {
						if (place(x, y, turn, arr)) {
							//-------------------------------------------------------------------------------------
							//����
							while (x - a >= 0) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
								if (arr[y][x - a] == 1) {
									break;
								}
								else if (arr[y][x - a] == 2) {
									a++;
								}
								else {
									a = 1;
									break;
								}
							}
							for (; a > 1; a--)
								arr[y][x - (a - 1)] = 1;
							a = 1;
							//-------------------------------------------------------------------------------------
							//������
							while (x + a <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
								if (arr[y][x + a] == 1) {
									break;
								}
								else if (arr[y][x + a] == 2) {
									a++;
								}
								else {
									a = 1;
									break;
								}
							}
							for (; a > 1; a--)
								arr[y][x + (a - 1)] = 1;
							a = 1;
							//-------------------------------------------------------------------------------------
							//�Ʒ�
							while (y + b <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
								if (arr[y + b][x] == 1) {
									break;
								}
								else if (arr[y + b][x] == 2) {
									b++;
								}
								else {
									b = 1;
									break;
								}
							}
							for (; b > 1; b--)
								arr[y + (b - 1)][x] = 1;
							b = 1;
							//-------------------------------------------------------------------------------------
							//��
							while (y - b >= 0) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
								if (arr[y - b][x] == 1) {
									break;
								}
								else if (arr[y - b][x] == 2) {
									b++;
								}
								else {
									b = 1;
									break;
								}
							}
							for (; b > 1; b--)
								arr[y - (b - 1)][x] = 1;
							b = 1;
							//-------------------------------------------------------------------------------------
							//1-7�� �밢��
							while (y + b <= 20) {
								if (arr[y + b][x - a] == 1) {
									break;
								}
								else if (arr[y + b][x - a] == 2) {
									a++;
									b++;
								}
								else {
									a = 1;
									b = 1;
									break;
								}
							}
							for (; b > 1; b--) {
								arr[y + (b - 1)][x - (a - 1)] = 1;
								a--;
							}
							a = 1;
							b = 1;
							//-------------------------------------------------------------------------------------
							//7-1�� �밢��
							while (y - b >= 0) {
								if (arr[y - b][x + a] == 1) {
									break;
								}
								else if (arr[y - b][x + a] == 2) {
									a++;
									b++;
								}
								else {
									a = 1;
									b = 1;
									break;
								}
							}
							for (; b > 1; b--) {
								arr[y - (b - 1)][x + (a - 1)] = 1;
								a--;
							}
							a = 1;
							b = 1;
							//-------------------------------------------------------------------------------------
							//11-5�� �밢��
							while (y + b <= 20) {
								if (arr[y + b][x + a] == 1) {
									break;
								}
								else if (arr[y + b][x + a] == 2) {
									a++;
									b++;
								}
								else {
									a = 1;
									b = 1;
									break;
								}
							}
							for (; b > 1; b--) {
								arr[y + (b - 1)][x + (a - 1)] = 1;
								a--;
							}
							a = 1;
							b = 1;
							//-------------------------------------------------------------------------------------
							//5-11�� �밢��
							while (y - b >= 0) {
								if (arr[y - b][x - a] == 1) {
									break;
								}
								else if (arr[y - b][x - a] == 2) {
									a++;
									b++;
								}
								else {
									a = 1;
									b = 1;
									break;
								}
							}
							for (; b > 1; b--) {
								arr[y - (b - 1)][x - (a - 1)] = 1;
								a--;
							}
							a = 1;
							b = 1;
							//-------------------------------------------------------------------------------------
							//turn++;
							arr[y][x] = 5;
							turn = 1;
						}
						break;
					}
				}
			}
			else {
				switch (ch[0]) {
				case 'a':
					if (x == 0)
						break;
					switch (arr[y][x - 1]) {
					case 0:
						arr[y][x - 1] = 2;
						break;
					case 1:
						arr[y][x - 1] = 3;
						break;
					case 2:
						arr[y][x - 1] = 4;
						break;
					}
					switch (arr[y][x]) {
					case 1:
						arr[y][x] = 0;
						break;
					case 2:
						arr[y][x] = 0;
						break;
					case 3:
						arr[y][x] = 1;
						break;
					case 4:
						arr[y][x] = 2;
						break;
					case 5:
						arr[y][x] = 1;
						break;
					case 6:
						arr[y][x] = 2;
						break;
					}
					x--;
					num = 1;
					break;
				case 'd':
					if (x == 20)
						break;

					switch (arr[y][x + 1]) {
					case 0:
						arr[y][x + 1] = 2;
						break;
					case 1:
						arr[y][x + 1] = 3;
						break;
					case 2:
						arr[y][x + 1] = 4;
						break;
					}
					switch (arr[y][x]) {
					case 1:
						arr[y][x] = 0;
						break;
					case 2:
						arr[y][x] = 0;
						break;
					case 3:
						arr[y][x] = 1;
						break;
					case 4:
						arr[y][x] = 2;
						break;
					case 5:
						arr[y][x] = 1;
						break;
					case 6:
						arr[y][x] = 2;
						break;
					}
					x++;
					num = 2;
					break;
				case 'w':
					if (y == 0)
						break;
					switch (arr[y - 1][x]) {
					case 0:
						arr[y - 1][x] = 2;
						break;
					case 1:
						arr[y - 1][x] = 3;
						break;
					case 2:
						arr[y - 1][x] = 4;
						break;
					}
					switch (arr[y][x]) {
					case 1:
						arr[y][x] = 0;
						break;
					case 2:
						arr[y][x] = 0;
						break;
					case 3:
						arr[y][x] = 1;
						break;
					case 4:
						arr[y][x] = 2;
						break;
					case 5:
						arr[y][x] = 1;
						break;
					case 6:
						arr[y][x] = 2;
						break;
					}
					num = 3;
					y--;
					break;
				case 's':
					if (y == 20)
						break;
					switch (arr[y + 1][x]) {
					case 0:
						arr[y + 1][x] = 2;
						break;
					case 1:
						arr[y + 1][x] = 3;
						break;
					case 2:
						arr[y + 1][x] = 4;
						break;
					}
					switch (arr[y][x]) {
					case 1:
						arr[y][x] = 0;
						break;
					case 2:
						arr[y][x] = 0;
						break;
					case 3:
						arr[y][x] = 1;
						break;
					case 4:
						arr[y][x] = 2;
						break;
					case 5:
						arr[y][x] = 1;
						break;
					case 6:
						arr[y][x] = 2;
						break;
					}
					num = 4;
					y++;
					break;
				case 'f':
					if (arr[y][x] == 2) {
						if (place(x, y, turn, arr)) {
							//-------------------------------------------------------------------------------------
							//����
							while (x - a >= 0) {                        //a�� 1���� �ϴϱ� a-1�� �ؾߵ�
								if (arr[y][x - a] == 2) {
									break;
								}
								else if (arr[y][x - a] == 1) {
									a++;
								}
								else {
									a = 1;
									break;
								}
							}
							for (; a > 1; a--)
								arr[y][x - (a - 1)] = 2;
							a = 1;
							//-------------------------------------------------------------------------------------
							//������
							while (x + a <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
								if (arr[y][x + a] == 2) {
									break;
								}
								else if (arr[y][x + a] == 1) {
									a++;
								}
								else {
									a = 1;
									break;
								}
							}
							for (; a > 1; a--)
								arr[y][x + (a - 1)] = 2;
							a = 1;
							//-------------------------------------------------------------------------------------
							//�Ʒ�
							while (y + b <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
								if (arr[y + b][x] == 2) {
									break;
								}
								else if (arr[y + b][x] == 1) {
									b++;
								}
								else {
									b = 1;
									break;
								}
							}
							for (; b > 1; b--)
								arr[y + (b - 1)][x] = 2;
							b = 1;
							//-------------------------------------------------------------------------------------
							//��
							while (y - b >= 0) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
								if (arr[y - b][x] == 2) {
									break;
								}
								else if (arr[y - b][x] == 1) {
									b++;
								}
								else {
									b = 1;
									break;
								}
							}
							for (; b > 1; b--)
								arr[y - (b - 1)][x] = 2;
							b = 1;
							//-------------------------------------------------------------------------------------
							//1-7�� �밢��
							while (y + b <= 20) {
								if (arr[y + b][x - a] == 2) {
									break;
								}
								else if (arr[y + b][x - a] == 1) {
									a++;
									b++;
								}
								else {
									b = 1;
									a = 1;
									break;
								}
							}
							for (; b > 1; b--) {
								arr[y + (b - 1)][x - (a - 1)] = 2;
								a--;
							}
							a = 1;
							b = 1;
							//-------------------------------------------------------------------------------------
							//7-1�� �밢��
							while (y - b >= 0) {
								if (arr[y - b][x + a] == 2) {
									break;
								}
								else if (arr[y - b][x + a] == 1) {
									a++;
									b++;
								}
								else {
									a = 1;
									b = 1;
									break;
								}
							}
							for (; b > 1; b--) {
								arr[y - (b - 1)][x + (a - 1)] = 2;
								a--;
							}
							a = 1;
							b = 1;
							//-------------------------------------------------------------------------------------
							//11-5�� �밢��
							while (y + b <= 20) {
								if (arr[y + b][x + a] == 2) {
									break;
								}
								else if (arr[y + b][x + a] == 1) {
									a++;
									b++;
								}
								else {
									a = 1;
									b = 1;
									break;
								}
							}
							for (; b > 1; b--) {
								arr[y + (b - 1)][x + (a - 1)] = 2;
								a--;
							}
							a = 1;
							b = 1;
							//-------------------------------------------------------------------------------------
							//5-11�� �밢��
							while (y - b >= 0) {
								if (arr[y - b][x - a] == 2) {
									break;
								}
								else if (arr[y - b][x - a] == 1) {
									a++;
									b++;
								}
								else {
									a = 1;
									b = 1;
									break;
								}
							}
							for (; b > 1; b--) {
								arr[y - (b - 1)][x - (a - 1)] = 2;
								a--;
							}
							a = 1;
							b = 1;
							//-------------------------------------------------------------------------------------
							//turn++;
							arr[y][x] = 6;
							turn = 0;
						}
					}
					break;
				}
			}
		}
		WaitForSingleObject(hSndThread, INFINITE);
		WaitForSingleObject(hRcvThread, INFINITE);
		closesocket(hSock);
		return 0;
	}
}


unsigned WINAPI SendMsg(void *arg) {
	SOCKET hSock = *((SOCKET*)arg);
	scanf("%s", ch);

	WaitForSingleObject(hMutex, INFINITE);
	send(hSock, ch, 1, 0);
	ReleaseMutex(hMutex);
	return 0;
}

void display() {
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n");
	printf("\t\t1. ȥ�� �����ϱ�\n\n");
	printf("\t\t2. ���� ����ϱ�\n\n\n\n");
	printf("\t\t�ذ��� ��Ģ��\n\n");
	printf("\t    �����̵� : w + Enter\n\n");
	printf("\t    �Ʒ��� �̵� : s + Enter\n\n");
	printf("\t    ������ �̵� : d + Enter\n\n");
	printf("\t    ���� �̵� : a + Enter\n\n");
	printf("\t    ������ġ�� �� ���� : f + Enter\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
}

void ErrorHandlling(char *msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

int Odello() {
	char ch;
	arr[10][10] = 1;
	arr[11][11] = 1;
	arr[10][11] = 2;
	arr[11][10] = 2;
	start = clock();
	while (1) {
		b_n = 0;
		w_n = 0;
		system("cls");
		for (i = 0; i < 21; i++) {
			for (j = 0; j < 21; j++) {
				switch (arr[i][j]) {
				case 0:
					printf(" ��");
					break;
				case 1:
					printf("��");
					b_n++;
					break;
				case 2:
					printf("��");
					w_n++;
					break;
				case 3:
					printf("��");
					b_n++;
					break;
				case 4:
					printf("��");
					w_n++;
					break;
				case 5:
					printf("��");
					b_n++;
					break;
				case 6:
					printf("��");
					w_n++;
					break;

				}
			}
			printf("\n");
		}
		printf("\t �鵹 vs �浹\n");
		mid = clock();

		printf("\t  %d vs  %d\t%d�� ���", b_n, w_n, (int)((mid - start) / 1000));

		if (turn % 2 == 0)
			b_n--;
		else
			w_n--;

		if ((int)((mid - start) / 1000) > 10 * 30) { //�¸� ����1
			system("cls");
			printf("\t �浹 vs �鵹\n");
			printf("\t  %d vs  %d\n", b_n, w_n);
			if (b_n > w_n)
				printf("�浹 ��!\n");
			else
				printf("�鵹 ��!\n");
		}
		if (b_n > 70) {                                          // �¸� ����2
			system("cls");
			printf("�浹 �¸�!");
		}
		else if (w_n > 70) {
			system("cls");
			printf("�鵹 �¸�!");
		}


		ch = getch();

		if (turn % 2 == 0) {
			switch (ch) {
			case 'a':
				if (x == 0)
					break;
				switch (arr[y][x - 1]) {
				case 0:
					arr[y][x - 1] = 1;
					break;
				case 1:
					arr[y][x - 1] = 3;
					break;
				case 2:
					arr[y][x - 1] = 4;
					break;
				}
				switch (arr[y][x]) {
				case 1:
					arr[y][x] = 0;
					break;
				case 2:
					arr[y][x] = 0;
					break;
				case 3:
					arr[y][x] = 1;
					break;
				case 4:
					arr[y][x] = 2;
					break;
				case 5:
					arr[y][x] = 1;
					break;
				case 6:
					arr[y][x] = 2;
					break;
				}
				x--;
				num = 1;
				break;
			case 'd':
				if (x == 20)
					break;

				switch (arr[y][x + 1]) {
				case 0:
					arr[y][x + 1] = 1;
					break;
				case 1:
					arr[y][x + 1] = 3;
					break;
				case 2:
					arr[y][x + 1] = 4;
					break;
				}
				switch (arr[y][x]) {
				case 1:
					arr[y][x] = 0;
					break;
				case 2:
					arr[y][x] = 0;
					break;
				case 3:
					arr[y][x] = 1;
					break;
				case 4:
					arr[y][x] = 2;
					break;
				case 5:
					arr[y][x] = 1;
					break;
				case 6:
					arr[y][x] = 2;
					break;
				}
				x++;
				num = 2;
				break;
			case 'w':
				if (y == 0)
					break;
				switch (arr[y - 1][x]) {
				case 0:
					arr[y - 1][x] = 1;
					break;
				case 1:
					arr[y - 1][x] = 3;
					break;
				case 2:
					arr[y - 1][x] = 4;
					break;
				}
				switch (arr[y][x]) {
				case 1:
					arr[y][x] = 0;
					break;
				case 2:
					arr[y][x] = 0;
					break;
				case 3:
					arr[y][x] = 1;
					break;
				case 4:
					arr[y][x] = 2;
					break;
				case 5:
					arr[y][x] = 1;
					break;
				case 6:
					arr[y][x] = 2;
					break;
				}
				num = 3;
				y--;
				break;
			case 's':
				if (y == 20)
					break;
				switch (arr[y + 1][x]) {
				case 0:
					arr[y + 1][x] = 1;
					break;
				case 1:
					arr[y + 1][x] = 3;
					break;
				case 2:
					arr[y + 1][x] = 4;
					break;
				}
				switch (arr[y][x]) {
				case 1:
					arr[y][x] = 0;
					break;
				case 2:
					arr[y][x] = 0;
					break;
				case 3:
					arr[y][x] = 1;
					break;
				case 4:
					arr[y][x] = 2;
					break;
				case 5:
					arr[y][x] = 1;
					break;
				case 6:
					arr[y][x] = 2;
					break;
				}
				num = 4;
				y++;
				break;
			case 'f': //������ ������� �� �� ���̿� ���̰Բ� ����� ��
				if (arr[y][x] == 1) {
					if (place(x, y, turn, arr)) {
						//-------------------------------------------------------------------------------------
						//����
						while (x - a >= 0) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
							if (arr[y][x - a] == 1) {
								break;
							}
							else if (arr[y][x - a] == 2) {
								a++;
							}
							else {
								a = 1;
								break;
							}
						}
						for (; a > 1; a--)
							arr[y][x - (a - 1)] = 1;
						a = 1;
						//-------------------------------------------------------------------------------------
						//������
						while (x + a <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
							if (arr[y][x + a] == 1) {
								break;
							}
							else if (arr[y][x + a] == 2) {
								a++;
							}
							else {
								a = 1;
								break;
							}
						}
						for (; a > 1; a--)
							arr[y][x + (a - 1)] = 1;
						a = 1;
						//-------------------------------------------------------------------------------------
						//�Ʒ�
						while (y + b <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
							if (arr[y + b][x] == 1) {
								break;
							}
							else if (arr[y + b][x] == 2) {
								b++;
							}
							else {
								b = 1;
								break;
							}
						}
						for (; b > 1; b--)
							arr[y + (b - 1)][x] = 1;
						b = 1;
						//-------------------------------------------------------------------------------------
						//��
						while (y - b >= 0) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
							if (arr[y - b][x] == 1) {
								break;
							}
							else if (arr[y - b][x] == 2) {
								b++;
							}
							else {
								b = 1;
								break;
							}
						}
						for (; b > 1; b--)
							arr[y - (b - 1)][x] = 1;
						b = 1;
						//-------------------------------------------------------------------------------------
						//1-7�� �밢��
						while (y + b <= 20) {
							if (arr[y + b][x - a] == 1) {
								break;
							}
							else if (arr[y + b][x - a] == 2) {
								a++;
								b++;
							}
							else {
								a = 1;
								b = 1;
								break;
							}
						}
						for (; b > 1; b--) {
							arr[y + (b - 1)][x - (a - 1)] = 1;
							a--;
						}
						a = 1;
						b = 1;
						//-------------------------------------------------------------------------------------
						//7-1�� �밢��
						while (y - b >= 0) {
							if (arr[y - b][x + a] == 1) {
								break;
							}
							else if (arr[y - b][x + a] == 2) {
								a++;
								b++;
							}
							else {
								a = 1;
								b = 1;
								break;
							}
						}
						for (; b > 1; b--) {
							arr[y - (b - 1)][x + (a - 1)] = 1;
							a--;
						}
						a = 1;
						b = 1;
						//-------------------------------------------------------------------------------------
						//11-5�� �밢��
						while (y + b <= 20) {
							if (arr[y + b][x + a] == 1) {
								break;
							}
							else if (arr[y + b][x + a] == 2) {
								a++;
								b++;
							}
							else {
								a = 1;
								b = 1;
								break;
							}
						}
						for (; b > 1; b--) {
							arr[y + (b - 1)][x + (a - 1)] = 1;
							a--;
						}
						a = 1;
						b = 1;
						//-------------------------------------------------------------------------------------
						//5-11�� �밢��
						while (y - b >= 0) {
							if (arr[y - b][x - a] == 1) {
								break;
							}
							else if (arr[y - b][x - a] == 2) {
								a++;
								b++;
							}
							else {
								a = 1;
								b = 1;
								break;
							}
						}
						for (; b > 1; b--) {
							arr[y - (b - 1)][x - (a - 1)] = 1;
							a--;
						}
						a = 1;
						b = 1;
						//-------------------------------------------------------------------------------------
						//turn++;
						arr[y][x] = 5;
						turn = 1;
					}
					break;
				}
			}
		}
		else {
			switch (ch) {
			case 'a':
				if (x == 0)
					break;
				switch (arr[y][x - 1]) {
				case 0:
					arr[y][x - 1] = 2;
					break;
				case 1:
					arr[y][x - 1] = 3;
					break;
				case 2:
					arr[y][x - 1] = 4;
					break;
				}
				switch (arr[y][x]) {
				case 1:
					arr[y][x] = 0;
					break;
				case 2:
					arr[y][x] = 0;
					break;
				case 3:
					arr[y][x] = 1;
					break;
				case 4:
					arr[y][x] = 2;
					break;
				case 5:
					arr[y][x] = 1;
					break;
				case 6:
					arr[y][x] = 2;
					break;
				}
				x--;
				num = 1;
				break;
			case 'd':
				if (x == 20)
					break;

				switch (arr[y][x + 1]) {
				case 0:
					arr[y][x + 1] = 2;
					break;
				case 1:
					arr[y][x + 1] = 3;
					break;
				case 2:
					arr[y][x + 1] = 4;
					break;
				}
				switch (arr[y][x]) {
				case 1:
					arr[y][x] = 0;
					break;
				case 2:
					arr[y][x] = 0;
					break;
				case 3:
					arr[y][x] = 1;
					break;
				case 4:
					arr[y][x] = 2;
					break;
				case 5:
					arr[y][x] = 1;
					break;
				case 6:
					arr[y][x] = 2;
					break;
				}
				x++;
				num = 2;
				break;
			case 'w':
				if (y == 0)
					break;
				switch (arr[y - 1][x]) {
				case 0:
					arr[y - 1][x] = 2;
					break;
				case 1:
					arr[y - 1][x] = 3;
					break;
				case 2:
					arr[y - 1][x] = 4;
					break;
				}
				switch (arr[y][x]) {
				case 1:
					arr[y][x] = 0;
					break;
				case 2:
					arr[y][x] = 0;
					break;
				case 3:
					arr[y][x] = 1;
					break;
				case 4:
					arr[y][x] = 2;
					break;
				case 5:
					arr[y][x] = 1;
					break;
				case 6:
					arr[y][x] = 2;
					break;
				}
				num = 3;
				y--;
				break;
			case 's':
				if (y == 20)
					break;
				switch (arr[y + 1][x]) {
				case 0:
					arr[y + 1][x] = 2;
					break;
				case 1:
					arr[y + 1][x] = 3;
					break;
				case 2:
					arr[y + 1][x] = 4;
					break;
				}
				switch (arr[y][x]) {
				case 1:
					arr[y][x] = 0;
					break;
				case 2:
					arr[y][x] = 0;
					break;
				case 3:
					arr[y][x] = 1;
					break;
				case 4:
					arr[y][x] = 2;
					break;
				case 5:
					arr[y][x] = 1;
					break;
				case 6:
					arr[y][x] = 2;
					break;
				}
				num = 4;
				y++;
				break;
			case 'f':
				if (arr[y][x] == 2) {
					if (place(x, y, turn, arr)) {
						//-------------------------------------------------------------------------------------
						//����
						while (x - a >= 0) {                        //a�� 1���� �ϴϱ� a-1�� �ؾߵ�
							if (arr[y][x - a] == 2) {
								break;
							}
							else if (arr[y][x - a] == 1) {
								a++;
							}
							else {
								a = 1;
								break;
							}
						}
						for (; a > 1; a--)
							arr[y][x - (a - 1)] = 2;
						a = 1;
						//-------------------------------------------------------------------------------------
						//������
						while (x + a <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
							if (arr[y][x + a] == 2) {
								break;
							}
							else if (arr[y][x + a] == 1) {
								a++;
							}
							else {
								a = 1;
								break;
							}
						}
						for (; a > 1; a--)
							arr[y][x + (a - 1)] = 2;
						a = 1;
						//-------------------------------------------------------------------------------------
						//�Ʒ�
						while (y + b <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
							if (arr[y + b][x] == 2) {
								break;
							}
							else if (arr[y + b][x] == 1) {
								b++;
							}
							else {
								b = 1;
								break;
							}
						}
						for (; b > 1; b--)
							arr[y + (b - 1)][x] = 2;
						b = 1;
						//-------------------------------------------------------------------------------------
						//��
						while (y - b >= 0) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
							if (arr[y - b][x] == 2) {
								break;
							}
							else if (arr[y - b][x] == 1) {
								b++;
							}
							else {
								b = 1;
								break;
							}
						}
						for (; b > 1; b--)
							arr[y - (b - 1)][x] = 2;
						b = 1;
						//-------------------------------------------------------------------------------------
						//1-7�� �밢��
						while (y + b <= 20) {
							if (arr[y + b][x - a] == 2) {
								break;
							}
							else if (arr[y + b][x - a] == 1) {
								a++;
								b++;
							}
							else {
								b = 1;
								a = 1;
								break;
							}
						}
						for (; b > 1; b--) {
							arr[y + (b - 1)][x - (a - 1)] = 2;
							a--;
						}
						a = 1;
						b = 1;
						//-------------------------------------------------------------------------------------
						//7-1�� �밢��
						while (y - b >= 0) {
							if (arr[y - b][x + a] == 2) {
								break;
							}
							else if (arr[y - b][x + a] == 1) {
								a++;
								b++;
							}
							else {
								a = 1;
								b = 1;
								break;
							}
						}
						for (; b > 1; b--) {
							arr[y - (b - 1)][x + (a - 1)] = 2;
							a--;
						}
						a = 1;
						b = 1;
						//-------------------------------------------------------------------------------------
						//11-5�� �밢��
						while (y + b <= 20) {
							if (arr[y + b][x + a] == 2) {
								break;
							}
							else if (arr[y + b][x + a] == 1) {
								a++;
								b++;
							}
							else {
								a = 1;
								b = 1;
								break;
							}
						}
						for (; b > 1; b--) {
							arr[y + (b - 1)][x + (a - 1)] = 2;
							a--;
						}
						a = 1;
						b = 1;
						//-------------------------------------------------------------------------------------
						//5-11�� �밢��
						while (y - b >= 0) {
							if (arr[y - b][x - a] == 2) {
								break;
							}
							else if (arr[y - b][x - a] == 1) {
								a++;
								b++;
							}
							else {
								a = 1;
								b = 1;
								break;
							}
						}
						for (; b > 1; b--) {
							arr[y - (b - 1)][x - (a - 1)] = 2;
							a--;
						}
						a = 1;
						b = 1;
						//-------------------------------------------------------------------------------------
						//turn++;
						arr[y][x] = 6;
						turn = 0;
					}
				}
				break;
			}
		}
	}
}

int place(int x, int y, int tern, int(*arr)[21]) {

	int a = 1;
	int b = 1;
	if (tern % 2 == 0) {
		//-------------------------------------------------------------------------------------
		//����
		while (x - a >= 0) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
			if (arr[y][x - a] == 1) {
				if (a == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y][x - a] == 2) {
				a++;
			}
			else {
				break;
			}
		}
		a = 1;
		//-------------------------------------------------------------------------------------
		//������
		while (x + a <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
			if (arr[y][x + a] == 1) {
				if (a == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y][x + a] == 2) {
				a++;
			}
			else {
				break;
			}
		}
		a = 1;
		//-------------------------------------------------------------------------------------
		//�Ʒ�
		while (y + b <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
			if (arr[y + b][x] == 1) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y + b][x] == 2) {
				b++;
			}
			else {
				break;
			}
		}
		b = 1;
		//-------------------------------------------------------------------------------------
		//��
		while (y - b >= 0) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
			if (arr[y - b][x] == 1) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y - b][x] == 2) {
				b++;
			}
			else {
				break;
			}
		}
		b = 1;
		//-------------------------------------------------------------------------------------
		//1-7�� �밢��
		while (y + b <= 20) {
			if (arr[y + b][x - a] == 1) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y + b][x - a] == 2) {
				a++;
				b++;
			}
			else { //0�̸�
				break;
			}
		}
		a = 1;
		b = 1;
		//-------------------------------------------------------------------------------------
		//7-1�� �밢��
		while (y - b >= 0) {
			if (arr[y - b][x + a] == 1) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y - b][x + a] == 2) {
				a++;
				b++;
			}
			else {
				break;
			}
		}
		a = 1;
		b = 1;
		//-------------------------------------------------------------------------------------
		//11-5�� �밢��
		while (y + b <= 20) {
			if (arr[y + b][x + a] == 1) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y + b][x + a] == 2) {
				a++;
				b++;
			}
			else {
				break;
			}
		}
		a = 1;
		b = 1;
		//-------------------------------------------------------------------------------------
		//5-11�� �밢��
		while (y - b >= 0) {
			if (arr[y - b][x - a] == 1) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y - b][x - a] == 2) {
				a++;
				b++;
			}
			else {
				break;
			}
		}
		a = 1;
		b = 1;
		//-------------------------------------------------------------------------------------
	}
	else {
		//-------------------------------------------------------------------------------------
		//����
		while (x - a >= 0) {                        //a�� 1���� �ϴϱ� a-1�� �ؾߵ�
			if (arr[y][x - a] == 2) {
				if (a == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y][x - a] == 1) {
				a++;
			}
			else {
				break;
			}
		}
		a = 1;
		//-------------------------------------------------------------------------------------
		//������
		while (x + a <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
			if (arr[y][x + a] == 2) {
				if (a == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y][x + a] == 1) {
				a++;
			}
			else {
				break;
			}
		}
		a = 1;
		//-------------------------------------------------------------------------------------
		//�Ʒ�
		while (y + b <= 20) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
			if (arr[y + b][x] == 2) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y + b][x] == 1) {
				b++;
			}
			else {
				break;
			}
		}
		b = 1;
		//-------------------------------------------------------------------------------------
		//��
		while (y - b >= 0) {                        // ����//a�� 1���� �ϴϱ� a-1�� �ؾߵ�
			if (arr[y - b][x] == 2) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y - b][x] == 1) {
				b++;
			}
			else {
				break;
			}
		}
		b = 1;
		//-------------------------------------------------------------------------------------
		//1-7�� �밢��
		while (y + b <= 20) {
			if (arr[y + b][x - a] == 2) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y + b][x - a] == 1) {
				a++;
				b++;
			}
			else {
				break;
			}
		}
		a = 1;
		b = 1;
		//-------------------------------------------------------------------------------------
		//7-1�� �밢��
		while (y - b >= 0) {
			if (arr[y - b][x + a] == 2) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y - b][x + a] == 1) {
				a++;
				b++;
			}
			else {
				break;
			}
		}

		a = 1;
		b = 1;
		//-------------------------------------------------------------------------------------
		//11-5�� �밢��
		while (y + b <= 20) {
			if (arr[y + b][x + a] == 2) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y + b][x + a] == 1) {
				a++;
				b++;
			}
			else {
				break;
			}
		}
		a = 1;
		b = 1;
		//-------------------------------------------------------------------------------------
		//5-11�� �밢��
		while (y - b >= 0) {
			if (arr[y - b][x - a] == 2) {
				if (b == 1) {
					break;
				}
				else {
					return 1;
				}
			}
			else if (arr[y - b][x - a] == 1) {
				a++;
				b++;
			}
			else {
				break;
			}
		}
		a = 1;
		b = 1;
		//-------------------------------------------------------------------------------------

	}
	return 0;
}
