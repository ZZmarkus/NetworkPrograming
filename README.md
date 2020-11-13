# NetworkPrograming


## 함수 설명
```C
//초기 메인 인터페이스 작성
void display() {
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n");
	printf("\t\t1. 혼자 연습하기\n\n");
	printf("\t\t2. 상대와 대결하기\n\n\n\n");
	printf("\t\t※게임 규칙※\n\n");
	printf("\t    위로이동 : w + Enter\n\n");
	printf("\t    아래로 이동 : s + Enter\n\n");
	printf("\t    오른쪽 이동 : d + Enter\n\n");
	printf("\t    왼쪽 이동 : a + Enter\n\n");
	printf("\t    현재위치에 돌 놓기 : f + Enter\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
}

//클라이언트-서버간 오류 핸들러
void ErrorHandlling(char *msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

//오델로 게임 코드가 들어간 함수
int Odello()
```
