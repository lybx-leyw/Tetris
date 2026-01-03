/**
Tetris游戏实现：
1.生成mymap
2.设计viewmap和方块	
3.实现随机生成方块
4.实现mymap和viewmap的链接
5.游戏时间设定
6.方块移动读取
7.方块旋转读取
8.方块堆叠机制	
9.消除与下落机制	
10.顶格失败	  
11.重来机制   
12.积分制（消除累分）
13.显示下一个
14.储存历史记录并展示最佳
/**/

#include "acllib.h"
#include "main.h"
#include "draw.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "map.h"
#include "recore.h"

//设置游戏常量
#define _nOfx 10
#define _nOfy 11
static NOfb nOfb;
static Drawvalue drawvalue;
static Viewvalue viewvalue;
static Gamevalue gamevalue;
static int mymap[_nOfy][_nOfx];
static Blockstate blockstate;
static Bewhat bewhat = {0};
static clock_t lastFallTime = 0;

int Setup(void)
{
	//设定常量
		//设置其他游戏常量
	nOfb = ( NOfb ){ _nOfx, _nOfy };//x,y
	drawvalue = ( Drawvalue ){ 80, 3, 10 ,400};
		//方块大小（需要是游戏界面中宽、高的公因数），中间墙宽，上下墙宽，左栏宽
	viewvalue = ( Viewvalue ){ nOfb.nOfx*drawvalue.size_of_block+
									drawvalue.size_of_leftland+
									drawvalue.width_of_midwall, 
				nOfb.nOfy*drawvalue.size_of_block+2*drawvalue.width_of_upwall, 
			  	nOfb.nOfx*drawvalue.size_of_block,
				nOfb.nOfy*drawvalue.size_of_block };
		//屏幕的宽，高，游戏界面的宽，高
	Guidevalue guidevalue = { 1100, 500 };//x,y
	gamevalue = ( Gamevalue ){ 0,1000,1000,1,1,{0,0},1,0 };
		//score,velocity,velocity0,clearChance;Player;nextype;breaktime; 
		//gamevalue	其他参数：
	gamevalue.bestpla = read_best_score();
	gamevalue.nexttype = rand()%nOfType;
	//改为UTF-8编码
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	
	//游戏准备
	srand(time(0));
	initConsole();
		//Guide
	initWindow("Guide",DEFAULT,DEFAULT,guidevalue.width,guidevalue.height);
	registerTimerEvent(readTimer);

		//键盘交互
	registerKeyboardEvent(onKeyboard);
		//地图初始化
	reset_mymap(&nOfb, mymap);
	
	//游戏开始
	startTimer(0,gamevalue.breaktime);
	return 0;
}

//状态管理
//1.阅读Guide时
void readTimer( int id )
{
	if( !bewhat.is_begin ) {
		draw_guide(); 
		return;
	}
	//开始游戏后关闭Guide，打开游戏对应的计时器
	CloseWindow(g_hWnd);
	cancelTimer(0);
	initWindow("Tetris",
			DEFAULT,DEFAULT,viewvalue.width_of_viewmap,
			viewvalue.height_of_viewmap);
	registerTimerEvent(onTimer);
	startTimer(0,gamevalue.breaktime);
}

//2.游戏计时器（游戏开始）
void onTimer(int id) 
{
	clock_t currentTime = clock();
	//链接
	check_map( &nOfb, mymap, &drawvalue, &viewvalue );
	//判断游戏是否已经结束
	bewhat.is_over = gameOver( &nOfb, mymap );
	//判断是否在暂停
	if ( bewhat.is_timeP ) {
		lastFallTime += CLOCKS_PER_SEC/1000*gamevalue.breaktime;
		draw_prompt( &viewvalue, &drawvalue, PART_TIME ); 
	} else {
		//判断是否有消除
		if ( !bewhat.is_clear ) {  
			bewhat.is_clear = clearmove(&nOfb, mymap, &gamevalue.score);
		}
		//判断界面有无方块
		bewhat.is_producted = 0;
		for (int i=0; i<nOfb.nOfy; i++) {
			for (int j=0; j<nOfb.nOfx; j++) {
				if ( mymap[i][j] == 1 || bewhat.is_over) {
					bewhat.is_producted=1;
					break;	
				}
			} if (bewhat.is_producted) break;			
		}
		if ( !bewhat.is_producted ) {
			blockstate = rand_productb( &nOfb, mymap, gamevalue.nexttype ); 	
			gamevalue.nexttype = rand()%nOfType;
			bewhat.is_producted = 1;
		}
		//定时下落，延时展示某些提示文字
		if (
			(currentTime - lastFallTime)*1000/CLOCKS_PER_SEC >= gamevalue.velocity &&
			!bewhat.is_over)
		{
			//下落
			block_change(&nOfb, mymap, &blockstate, MOVE_DOWN, &gamevalue.score);
			printf_mymap( &nOfb, mymap );
			//定时清空重绘
			beginPaint();
			clearDevice();
			endPaint();
			check_map( &nOfb, mymap, &drawvalue, &viewvalue );
			//错误提示
			if ( bewhat.is_wrong ) { 
				draw_prompt( &viewvalue, &drawvalue, WRONG_MOVE); 
				bewhat.is_wrong = 0;
			}
			//清空提示
			if ( bewhat.is_drawC ) {
				draw_prompt( &viewvalue, &drawvalue, ALL_CLEAR ); 
				bewhat.is_drawC = 0;
			}
			//消除提示
			if ( bewhat.is_clear ) {
				draw_some_clear(bewhat.is_clear,&viewvalue,&drawvalue);
				bewhat.is_clear = 0;
			}	
			//无论如何，无法下移就固定
				//2.若无法下移：
			if( bewhat.is_steady ) {
				stead_map( &nOfb, mymap );
				bewhat.is_steady = 0; 
			}
				//1.判断是否无法下移
			for (int i=0; i<nOfb.nOfy; i++) {
				for (int j=0; j<nOfb.nOfx; j++) {
					if ( mymap[i][j]==1 && ( i==nOfb.nOfy-1 || mymap[i+1][j] == 2 )){
							bewhat.is_steady = 1;
							break;
					} 
				} if( bewhat.is_steady ) break;
			} 
			check_map( &nOfb, mymap, &drawvalue, &viewvalue );
			lastFallTime = currentTime;
		}
		//一直要显示的量
			//1.下一方块视图展示
		product_Bview( gamevalue.nexttype, &nOfb , &drawvalue );
			//2.文字
		draw_const_text(&nOfb, &viewvalue, &drawvalue, &gamevalue);
		check_map( &nOfb, mymap, &drawvalue, &viewvalue );
		//游戏结束判断
		if (bewhat.is_over) {
			draw_prompt( &viewvalue, &drawvalue, GAME_OVER );
			recore_score(gamevalue.score);
		}
	} 
}

//键盘事件
void onKeyboard(int key, int event)
{
	if (event != KEY_DOWN) return;
	if (bewhat.is_over && key != 'R' && key != 'r') return;
	switch(key) {
		//左右下移
		case VK_LEFT:
			block_change(&nOfb,mymap,&blockstate,MOVE_LEFT,&gamevalue.score);
			break;
		case VK_RIGHT:
			block_change(&nOfb,mymap,&blockstate,MOVE_RIGHT,&gamevalue.score);
			break;
		case VK_DOWN:
			block_change(&nOfb,mymap,&blockstate,MOVE_DOWN,&gamevalue.score);
			break;
		//暂停
		case 'P':
		case 'p':
			bewhat.is_timeP = ( bewhat.is_timeP==0 )?1:0;
			break;
		//重来
		case 'R':
		case 'r':
			reset_mymap(&nOfb, mymap);
			gamevalue.clearChance = gamevalue.clearChance0;
			gamevalue.score = 0;
			bewhat.is_timeP = 0;
			gamevalue.velocity = gamevalue.velocity0;
			bewhat.is_scored = 0;
			break;
		//旋转
		case VK_UP:
			bewhat.is_wrong = block_change(&nOfb,mymap,&blockstate,MOVE_INVOLVE,&gamevalue.score);
			break;
		//速降
		case VK_SPACE:
			for(int i=0; i<nOfb.nOfy; i++) {
				block_change(&nOfb,mymap,&blockstate,MOVE_DOWN,&gamevalue.score); 
			}
			stead_map( &nOfb, mymap );
			bewhat.is_steady = 0;
			break;
		//调速
		case 'S':
		case 's':
			gamevalue.velocity *= 2;
			break;
		case 'Q':
		case 'q':
			gamevalue.velocity /= 2;
			break;
		//清空
		case 'C':
		case 'c':
			if( !gamevalue.clearChance ) break;
			reset_mymap(&nOfb, mymap);
			check_map(&nOfb,mymap,&drawvalue,&viewvalue);
			gamevalue.clearChance--;
			bewhat.is_drawC = 1;
			break;
		//开始
		case 'B':
		case 'b':
			bewhat.is_begin = 1;
			break;
	}
}
