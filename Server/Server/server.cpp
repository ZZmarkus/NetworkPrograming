#pragma warning(disable:4996)
#include <stdio.h>
#include <conio.h>             
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <process.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

void ErrorHandlling(char *msg);

int clntCnt = 0;
SOCKET clnt_sock[MAX_CLNT];
HANDLE hMutex;



int main(int argc, char *argv[]) {
	WSADATA wsaData;
	SOCKET hServerSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz;
	int swap = 0;
	char msg[BUF_SIZE];
	char* wait[6];
	wait[0] = ".";
	wait[1] = "..";
	wait[2] = "...";
	wait[3] = "....";
	wait[4] = ".....";
	wait[5] = "......";

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandlling("WSAStartup() error!");

	hServerSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hServerSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandlling("bind() error");

	if (listen(hServerSock, 5) == SOCKET_ERROR)
		ErrorHandlling("listen() error");

	while (1) {
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServerSock, (SOCKADDR*)&clntAdr, &clntAdrSz);

		clnt_sock[clntCnt++] = hClntSock;

		printf("accept : %d\n", clntCnt);

		if (clntCnt % 2 == 0) {
			while (1) {
				if (swap == 0) {	//swap�� �ʱⰪ = 0 --> ���� ���� Ŭ���̾�Ʈ�� ������

					recv(clnt_sock[0], msg, 1, 0);

					for (int i = 0; i < clntCnt; i++) {	//Ŭ���̾�Ʈ 1�����κ��� ���� msg�� ��� Ŭ���̾�Ʈ���� �����Ѵ�.
						send(clnt_sock[i], msg, 1, 0);
					}
					if (msg[0] == 'f')	//Ŭ���̾�Ʈ 1���� ���� ������ f�� ������ �Ǵµ� f�� ������� swap�������� �ٲ�� ���� �ٲ��.
						swap = 1;
				}
				else {
					recv(clnt_sock[1], msg, 1, 0);
					for (int i = 0; i < clntCnt; i++) {
						send(clnt_sock[i], msg, 1, 0);
					}
					if (msg[0] == 'f')
						swap = 0;
				}

			}
		}
		else {
			printf("������ ��ٸ�����.......");
		}

	}


}


void ErrorHandlling(char *msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
