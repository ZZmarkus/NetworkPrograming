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
				if (swap == 0) {	//swap의 초기값 = 0 --> 먼저 들어온 클라이언트가 선공임

					recv(clnt_sock[0], msg, 1, 0);

					for (int i = 0; i < clntCnt; i++) {	//클라이언트 1번으로부터 받은 msg를 모든 클라이언트에게 전송한다.
						send(clnt_sock[i], msg, 1, 0);
					}
					if (msg[0] == 'f')	//클라이언트 1번이 돌을 놓을때 f를 누르게 되는데 f를 누를경우 swap변수값이 바뀌어 턴이 바뀐다.
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
			printf("상대방을 기다리는중.......");
		}

	}


}


void ErrorHandlling(char *msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
