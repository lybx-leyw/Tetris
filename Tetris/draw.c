#include "acllib.h"
#include "main.h"
#include <stdio.h>

//方块制作
void draw_block( float x, float y, Drawvalue* pdrawvalue )
{	
	beginPaint();
	x = 0+x*pdrawvalue->size_of_block;
	y = pdrawvalue->width_of_upwall+y*pdrawvalue->size_of_block;
	
	//1.底色
	setPenColor(WHITE);
	setBrushColor(RGB(97,29,16));
	rectangle(x,y,x+pdrawvalue->size_of_block,
				y+pdrawvalue->size_of_block);
	
	//2.内容1
	setPenColor(RGB(255,230,98));
	setBrushColor(RGB(255,230,98));
	rectangle(x+pdrawvalue->size_of_block/10,
		y+pdrawvalue->size_of_block/10,
		x+pdrawvalue->size_of_block-pdrawvalue->size_of_block/10,
		y+pdrawvalue->size_of_block-pdrawvalue->size_of_block/10);
	
	//3.内容2
	setPenColor(RGB(220,55,13));
	setBrushColor(RGB(220,55,13));
	rectangle(x+2*pdrawvalue->size_of_block/10,
		y+2*pdrawvalue->size_of_block/10,
		x+pdrawvalue->size_of_block-pdrawvalue->size_of_block/10,
		y+pdrawvalue->size_of_block-pdrawvalue->size_of_block/10);
		
	endPaint();
}

//方块清除
void draw_blank( float x, float y, Drawvalue* pdrawvalue )
{	
	beginPaint();
	x = 0+x*pdrawvalue->size_of_block;
	y = pdrawvalue->width_of_upwall+y*pdrawvalue->size_of_block;
	
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(x,y,x+pdrawvalue->size_of_block,
				y+pdrawvalue->size_of_block);
	
	endPaint();
}

//边框绘画
void draw_boarden( Drawvalue* pdrawvalue, NOfb* pnOfb, Viewvalue* pviewvalue )
{
	beginPaint();
	
	//1.游戏中间墙绘制
	setPenColor(GREEN);
	setPenWidth(1);
	setBrushColor(GREEN);
	setBrushStyle(BRUSH_STYLE_SOLID);
	rectangle( pdrawvalue->size_of_block*pnOfb->nOfx,0,
			pdrawvalue->size_of_block*pnOfb->nOfx+pdrawvalue->width_of_midwall,
			pviewvalue->height_of_viewmap );	
	
	//2.绘制上下墙
	setPenColor(BLUE);
	setBrushColor(BLUE);
	rectangle(0,0,pdrawvalue->size_of_block*pnOfb->nOfx,pdrawvalue->width_of_upwall);
	rectangle(0,pviewvalue->height_of_viewmap-pdrawvalue->width_of_upwall,
		pdrawvalue->size_of_block*pnOfb->nOfx,pviewvalue->height_of_viewmap);
	
	//3.辅助分界线
	setPenColor(BLACK);
	setPenWidth(1); 
	for(int i=1; i<pnOfb->nOfx; i++) {
		line(i*pdrawvalue->size_of_block,
			pdrawvalue->width_of_upwall,
			i*pdrawvalue->size_of_block,
			pviewvalue->height_of_viewmap-pdrawvalue->width_of_upwall);
	}
	
	endPaint();
}

//消除的提示文字绘制
void draw_some_clear(int nclear,Viewvalue* pviewvalue ,Drawvalue* pdrawvalue )
{
	beginPaint();
	setTextSize((int)(36/1300.0*pviewvalue->width_of_viewmap));
	setTextBkColor(WHITE);
	setTextFont("Malgun Gothic");
	
	char text[100];
	switch(nclear) 
	{
		case 1:
			setTextColor(BLACK); memcpy(text,"Good!",sizeof(text)); break;
		case 2:
			setTextColor(BLUE); memcpy(text,"Great!",sizeof(text)); break;
		case 3:
			setTextColor(GREEN); memcpy(text,"Wonderful!",sizeof(text)); break;
		case 4:
			setTextColor(RED); memcpy(text,"Fantastic!",sizeof(text)); break;
	}
	paintText(pviewvalue->width_of_gameviewmap+0.2*pdrawvalue->size_of_leftland,
			10*pdrawvalue->size_of_block,
			text);
	endPaint();
}

//绘制展示图片
void product_Bview(BLOCK_Type nexttype, NOfb* pnOfb, Drawvalue* pdrawvalue)
{
	for (int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if (blocks[nexttype][i][j] == 1) {
				draw_block( pnOfb->nOfx+0.5+j, 2.5+i, pdrawvalue );
			} else {
				draw_blank( pnOfb->nOfx+0.5+j, 2.5+i, pdrawvalue );
			}
		}		
	} 
}

//其他提示文字绘制
void draw_prompt( Viewvalue* pviewvalue ,Drawvalue* pdrawvalue ,PROMPT_Type type )
{
	beginPaint();
	switch ( type ) {
		//GAME_OVER
		case GAME_OVER:
			setTextColor(BLACK);
			setTextFont("Malgun Gothic");
			setTextSize((int)(72/1300.0*pviewvalue->width_of_viewmap));
			setTextBkColor(WHITE);
			paintText( pviewvalue->width_of_viewmap/2-2*pdrawvalue->size_of_block,
					pviewvalue->height_of_viewmap/2-pdrawvalue->size_of_block,
					"Game Over" );
			break;
		//WRONG_MOVE
		case WRONG_MOVE:
			setTextColor(GREEN);
			setTextFont("Malgun Gothic");
			setTextSize((int)(36/1300.0*pviewvalue->width_of_viewmap));
			setTextBkColor(WHITE);
			paintText(pviewvalue->width_of_gameviewmap+pdrawvalue->size_of_block,
					10*pdrawvalue->size_of_block,
					"Wrong Move");
			break;
		//PART_TIME
		case PART_TIME:
			setTextColor(BLUE);
			setTextFont("Malgun Gothic");
			setTextSize((int)(36/1300.0*pviewvalue->width_of_viewmap));
			setTextBkColor(WHITE);
			paintText(pviewvalue->width_of_gameviewmap+pdrawvalue->size_of_block,
					10*pdrawvalue->size_of_block,
					"Part Time");
			break;
		//ALL_CLEAR
		case ALL_CLEAR:
			setTextColor(GREEN);
			setTextFont("Malgun Gothic");
			setTextSize((int)(36/1300.0*pviewvalue->width_of_viewmap));
			setTextBkColor(WHITE);
			paintText(pviewvalue->width_of_gameviewmap+pdrawvalue->size_of_block,
					10*pdrawvalue->size_of_block,
					"Clear!!!!");
			break;
	}
	endPaint();
}

//游戏状态栏的文字绘制
	//把方块类型转化为文本
char* donextText(int nextype)
{
	switch ( nextype ) {
		case I:return "I";
		case Z:return "Z";
		case S:return "S";
		case J:return "J";
		case L:return "L";
		case O:return "O";
		case T:return "T";
	}
}
	//绘制
void draw_const_text ( NOfb* pnOfb, Viewvalue* pviewvalue ,Drawvalue* pdrawvalue ,
		Gamevalue* pgamevalue)
{
	beginPaint();
	
	char text[100];
	//得分：
	setTextColor(BLUE);
	setTextFont("Malgun Gothic");
	setTextSize((int)(25/1300.0*pviewvalue->width_of_viewmap));
	setTextBkColor(WHITE);
	sprintf(text,"Score: %d",pgamevalue->score);
	paintText(pviewvalue->width_of_gameviewmap+pdrawvalue->size_of_block,
					7*pdrawvalue->size_of_block,
					text);
	//当前速度
	setTextColor(RED);
	setTextFont("Malgun Gothic");
	setTextSize((int)(25/1300.0*pviewvalue->width_of_viewmap));
	setTextBkColor(WHITE);
	sprintf(text,"Velocity: *%.1f",pgamevalue->velocity0*1.0/pgamevalue->velocity);
	paintText(pviewvalue->width_of_gameviewmap+pdrawvalue->size_of_block,
					8*pdrawvalue->size_of_block,
					text);
	//清空次数
	setTextColor(RED);
	setTextFont("Malgun Gothic");
	setTextSize((int)(25/1300.0*pviewvalue->width_of_viewmap));
	setTextBkColor(WHITE);
	sprintf(text,"Clear Chance: %d ", pgamevalue->clearChance);
	paintText(pviewvalue->width_of_gameviewmap+pdrawvalue->size_of_block,
					9*pdrawvalue->size_of_block,
					text);
	//历史最高得分
	setTextColor(BLACK);
	setTextFont("Malgun Gothic");
	setTextSize((int)(24/1300.0*pviewvalue->width_of_viewmap));
	setTextBkColor(WHITE);
	sprintf(text,"Best-\nDate: %s %d %d \nScore: %d",pgamevalue->bestpla.date.month,
			pgamevalue->bestpla.date.day,pgamevalue->bestpla.date.year,
			pgamevalue->bestpla.playscore);
	paintText(pviewvalue->width_of_gameviewmap+pdrawvalue->size_of_block,
					1*pdrawvalue->size_of_block,text);
	//下一个方块
	setTextColor(BLACK);
	setTextFont("Malgun Gothic");
	setTextSize((int)(24/1300.0*pviewvalue->width_of_viewmap));
	setTextBkColor(WHITE);
	sprintf(text,"Next:%s",donextText(pgamevalue->nexttype));
	paintText(pviewvalue->width_of_gameviewmap+pdrawvalue->size_of_block,
					2*pdrawvalue->size_of_block,text);
	
	endPaint();
}
	
//Guide绘制
void draw_guide(void) 
{
	beginPaint();
	clearDevice();
	
	setTextColor(BLACK);
	setTextSize(22);
	setTextFont("Malgun Gothic");
	setTextBkColor(WHITE);
	paintText(30,100,
"Welcome to Tetris,"
"which is a game to move the blocks and try your best to clear them."
"When there is a line filled with blocks,which will"
);
	paintText(0,150,
"be cleared soon,you will get points.The more line you once clear,"
"the more points you will get(points for clearing n lines once= 200*n*n);"
);
	paintText(30,200,"The following keys might help you:	");
	paintText(30,400,"Enjoy your journey!");
	setTextFont("Noto Sans SC Black");
	paintText(0,250,
"<-- / --> : left / right_._._._._._._._VK_DOWN : Soft-drop (faster fall)"
"_._._._._._._._VK_UP : Change the blocks_._._._._._._._Space : Hard-drop");
	paintText(0,300,
"P : Pause 	R : Restart_._._._._._._._S : Increase falling speed (*2)_._._._._._._._._._"
"Q : Decrease falling speed (/2).");
	paintText(0,350,
"C : Use a \"clear chance\" (once per game) to clear the entire blocks_._._._._._._._"
"B:Begin your game.");
	setTextSize(25);
	paintText(400,25,"Tetris - Gameplay Guide");
	
	endPaint();
}
	
