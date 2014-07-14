#include<stdio.h>
#include<stdlib.h>


void display(int bord[][8]);
void invert(int bord[][8], int a, int b, int player);
void turn(int bord[][8], int init, int player);

/*メイン関数*/
int main(void)
{

	/*
		0 = 入力なし
		1 = 白
		2 = 黒
	*/

	int bord[8][8];
	int i, j, k;


	/*ボードの初期化*/
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			bord[i][j] = 0;
		}
	}
	bord[3][4] = bord[4][3] = 2;
	bord[3][3] = bord[4][4] = 1;
	/*ボードの初期化終了*/
	
	turn(bord, 0, 2);

	return 0;

}


void display(int bord[][8]){
	int i, j;
	printf("   ");
	for(j = 0; j < 8; j++){
		printf("[%c] ", 97 + j);
	}
	printf("\n");
	for(i = 0; i < 8; i++){
		printf("[%d]", i);
		for(j = 0; j < 8; j++){
			switch(bord[i][j]){
				case 0:
				printf("   |");
				break;

				case 1:
				printf(" Q |");
				break;

				case 2:
				printf(" @ |");
				break;

				default:
				exit(1);
				break;
			}
		}
		printf("\n   ");
		for(j = 0; j < 32; j++){
			printf("-");
		}
		printf("\n");
	}
}

void invert(int bord[][8], int a, int b, int player)
{

	int i, j;
	int count = 0;

	printf("a:%d, b:%d\n", a, b);

	/*エラー検出*/
	for(i = -1; i < 2; i++){
		for(j = -1; j < 2; j++){
			if( (-1 < (a + i) || (a + i) < 9) && ((-1 < ((b - 97) + j)) || (((b - 97) + j) < 9)) ){
				if((bord[a + i][(b - 97) + j] == 1) || (bord[a + i][(b - 97) + j] == 2)){
					count ++;
					printf("OK!(%3d,%3d), value : %3d\n", i, j, bord[a + i][(b - 97) + j]);
				}else{
					printf("NO!(%3d,%3d), value : %3d\n", i, j, bord[a + i][(b - 97) + j]);
				}
			}
		}
	}

	/*周囲1マス内に他の石がなかったらエラー*/
	if(count == 0){
		puts("<WARNING> : ENTER CORRECT NUMBER");
		if(player == 2){
			turn(bord, 1, 2);
		}else{
			turn(bord, 1, 1);
		}
	}

	if(player == 2){
		bord[a][b - 97] = 2;
	}else{
		bord[a][b - 97] = 1;
	}

	display(bord);	

}

void turn(int bord[][8], int init, int player)
{

	/*
		1 = 白
		2 = 黒
		初期状態では黒
	*/
	int a;		//入力_行
	char b;		//入力_列
	int static p;
	int p2;
	

	if(init != 0){
		p = player;
	}

	if(player == 2){
		p2 = player;
		puts("BLACK(@) TURN. ENTER POSITION. ex(num char)");
		printf(">");
		scanf("%d %c", &a, &b);
		p = 1;	//黒->白
		if((a < 0 || 8 < a) && ((int)b) < 97 || 104 < (int)b){
			puts("<WARNING> : ENTER CORRECT NUMBER");
			turn(bord, 1, 2);	//再帰
		}
	}else if(player ==1){
		p2 = player;
		puts("WHITE(Q) TURN. ENTER POSITION. ex(num char)");
		printf(">");
		scanf("%d %c", &a, &b);
		p = 2;	//白->黒
		if((a < 0 || 8 < a) && ((int)b) < 97 || 104 < (int)b){
			puts("<WARNING> : ENTER CORRECT NUMBER");
			turn(bord, 1, 1);	//再帰
		}
	}

	invert(bord, a, (int)b, p2);

	turn(bord, 1, p);

}
