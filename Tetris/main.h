#ifndef __MAIN_H__
#define __MAIN_H__

//界面大小参数
typedef struct _basic_value_of_viewmap {
	int width_of_viewmap;
	int height_of_viewmap;
	int width_of_gameviewmap;
	int height_of_gameviewmap;
} Viewvalue;

//界面框架参数
typedef struct _draw_value {
	int size_of_block;
	int width_of_midwall;
	int width_of_upwall;
	int size_of_leftland;
} Drawvalue;

//方块数量
typedef struct _number_of_blocks {
	int nOfx;
	int nOfy;
} NOfb;

//方块类型
typedef enum  {
	I,Z,S,J,L,O,T,nOfType,
} BLOCK_Type;

//方块状态
typedef struct _block_state {
	BLOCK_Type btype;
	int block_placex;
	int block_placey;
	//方块所在空间内（2，2）处的坐标值
} Blockstate;

//方块变换类型
typedef enum  {
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_INVOLVE
} CHANGE_Type;

//公开方块形状
extern const int blocks[nOfType][4][4];

//提示文字类型
typedef enum {
	GAME_OVER,
	ALL_CLEAR,
	PART_TIME,
	WRONG_MOVE
} PROMPT_Type;

//日期
typedef struct _date {
	char month[100];
	int day;
	int year;
} Date;

//玩家数据存储
typedef struct _player{
	Date date;
	int playscore;
} Player;

//游戏基本状态
typedef struct {
	int score;
	int velocity;int velocity0;//初始速度
	//速度单位是秒每格
	int clearChance;int clearChance0;
	Player bestpla;
	int nexttype;
	int breaktime; 
} Gamevalue;

//游戏特殊状态
typedef struct _be_what {
	int is_scored;
	int is_begin;
	int is_over;
	int is_wrong;
	int is_clear;
	int is_timeP;
	int is_drawC;
	int is_producted;
	int is_steady;
} Bewhat;

//状态管理
void readTimer(int id);
void onTimer(int id);
void onKeyboard(int key, int event);

//Guide的参数
typedef struct {
	int width;
	int height;
} Guidevalue ;


#endif