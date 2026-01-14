#include "main.h"
#include <stdio.h>
#include "draw.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

//初始化mymap
void reset_mymap ( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx] )
{
	for (int i=0; i<pnOfb->nOfy; i++) {
		for (int j=0; j<pnOfb->nOfx; j++) {
			mymap[i][j] = 0;
		}
	}
}

//辅助，printmymap
void printf_mymap( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx] )
{
	for (int i=0; i<pnOfb->nOfy; i++) {
		for (int j=0; j<pnOfb->nOfx; j++) {
			printf( "%d ", mymap[i][j] );
		}
		printf("\n");
	}
}

//将mymap和viewmap链接
void check_map ( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx], 
		Drawvalue* pdrawvalue, Viewvalue* pviewvalue ) 
{
	draw_boarden( pdrawvalue, pnOfb, pviewvalue );
	for (int i=0; i<pnOfb->nOfy; i++) {
		for (int j=0; j<pnOfb->nOfx; j++) {
			draw_blank( j, i, pdrawvalue );
			if ( mymap[i][j] == 1 || mymap[i][j] == 2 ) {
				draw_block( j, i, pdrawvalue );
			}
		}
	}	
	draw_boarden( pdrawvalue, pnOfb, pviewvalue );
}

//方块整体形状制作
const int blocks[nOfType][4][4] = {
	//中心点为（2，2）	
	// I型方块
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}},
	// Z型方块
    {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    // S型方块
    {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
    // J型方块
    {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    // L型方块
    {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    // O型方块
    {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
    // T型方块
 	{{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
};


//mymap随机生成方块
Blockstate rand_productb( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx], BLOCK_Type nexttype )
{	
	Blockstate blockstate;
	blockstate.btype = nexttype;
	
	int x,y;
	int size = ( nexttype==I )?4:3;

	while( 1 ){
		//随机生成初始中心坐标		
		int is_wrong = 0;
		x = ( nexttype == I )?( rand()%2 ):1;
		y = ( nexttype == I )?
			( rand()%(pnOfb->nOfx-3)+1 ): ( rand()%(pnOfb->nOfx-2)+1 );
	
		//检验该坐标是否合理
		for (int i=(x==0)?1:0; i<size; i++) {
			for (int j=0; j<size; j++) {
				if ( blocks[nexttype][i][j] == 1 && mymap[x-1+i][y-1+j] != 0 ) {
					is_wrong = 1;
					break;
				}
			} if( is_wrong ) break;
		}
		if( is_wrong ) { continue; } 
		//若合理：
		else {
			for (int i=(x==0)?1:0; i<size; i++) {
				for (int j=0; j<size; j++) {
					if (  mymap[x-1+i][y-1+j] == 0 && blocks[nexttype][i][j] == 1 ) {
						mymap[x-1+i][y-1+j] = blocks[nexttype][i][j];
					}
				}
			}
			break;
		}	
	} 	
	printf("%d %d\n" ,x ,y);
	blockstate.block_placex = x;
	blockstate.block_placey = y;
	
	return blockstate;
}

//变换辅助函数，矩阵运算（线性变换）
void line_change (int* x, int* y, int line[2][3])
{
	int a = *x;
	int b = *y;
	*x = line[0][0]*a+line[0][1]*b+line[0][2];
	*y = line[1][0]*a+line[1][1]*b+line[1][2];
}

//方块变换
int block_change (NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx], 
	Blockstate* pblockstate, CHANGE_Type change, int* score) 
{
	int is_wrong = 0;

	//得到矩阵
	int line[2][3];
	if (change == MOVE_DOWN) {
    	int midline[2][3] = {{1,0,1}, {0,1,0}};
    	memcpy(line, midline, sizeof(line));
	} else if (change == MOVE_RIGHT) {
    	int midline[2][3] = {{1,0,0}, {0,1,1}};
    	memcpy(line, midline, sizeof(line));
	} else if (change == MOVE_LEFT) {
   		int midline[2][3] = {{1,0,0}, {0,1,-1}};
    	memcpy(line, midline, sizeof(line));
	} else {
    	int midline[2][3] = 
			{{0,-1,pblockstate->block_placex+pblockstate->block_placey},
			 {1,0,pblockstate->block_placey-pblockstate->block_placex}};
    	memcpy(line, midline, sizeof(line));
	}
	
	//检验能否变换
	for (int i=0; i<pnOfb->nOfy; i++) {
		for (int j=0; j<pnOfb->nOfx; j++) {
			if ( mymap[i][j]==1 ) {
				int a = i;
				int b = j;
				line_change( &a, &b, line );
				if (!( a<pnOfb->nOfy && a>=0 && b<pnOfb->nOfx && b>=0 ) ||
					mymap[a][b] == 2 ) {
					is_wrong = 1;
					printf("wrong move!\n");
					break;
				} 	
			}
		} if(is_wrong) break;
	} 
	
	//能变换：
	if(is_wrong) {} else {
		//记录需要变换的坐标，清除原本方块
		int changePlace [4][2] = {0};
		int m = 0;
		for (int i=0; i<pnOfb->nOfy; i++) {
			for (int j=0; j<pnOfb->nOfx; j++) {
				if ( mymap[i][j] == 1 ) {
					mymap[i][j] = 0;
					int a = i;
					int b = j;
					line_change( &a, &b, line );
					changePlace [m][0] = a;
					changePlace [m][1] = b;
					m++;
				}
			} 
		}
		//变换
		for (int i=0; i<4; i++) {
			mymap[changePlace[i][0]][changePlace[i][1]] = 1;
		}
		//更改方块中心点
		line_change(&pblockstate->block_placex,&pblockstate->block_placey,line);
		printf("%d,%d\n", pblockstate->block_placex,pblockstate->block_placey);
		//如果是向下移动，加分
		if ( change == MOVE_DOWN ){
			*score += 10;
		}
	}
	
	return is_wrong;
}

//消除功能
int clearmove( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx], int* score )
{
	int cnt;
	int nclear = 0;
	for (int i=0; i<pnOfb->nOfy; i++) {
		cnt = 0;
		for (int j=0; j<pnOfb->nOfx; j++) {
			if ( mymap[i][j] == 2 ) {
				cnt++;
			}
		}
		if ( cnt == pnOfb->nOfx ) {
			for (int j=0; j<pnOfb->nOfx; j++) {
				mymap[i][j] = 0;
				for (int k = i; k>0; k--) {
					if ( mymap[k][j] == 2 ) {
						mymap[k][j] = 0;
						mymap[k+1][j] = 2;
					}
				}
			}
			nclear++;
		}
	}
	*score += 200*(nclear)*(nclear);
	return nclear;
}

//游戏结束判断
int gameOver( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx] )
{
	int ret = 0;
	for (int i=0; i<2; i++) {
		for (int j=0; j<pnOfb->nOfx; j++) {
			if ( mymap[i][j] == 2 ) {
				ret = 1;
				printf("game over!\n");
				break;
			}
		}
		if (ret) break;
	}
	return ret;
}

//方块固定
void stead_map( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx] )
{
	for (int i=0; i<pnOfb->nOfy; i++) {
		for (int j=0; j<pnOfb->nOfx; j++) {
			if ( mymap[i][j]==1 ){
				mymap[i][j] = 2;
			} 
		} 
	}
}
	
