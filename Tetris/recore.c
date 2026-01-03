#include "main.h"
#include <stdio.h>

//读出最佳成绩
Player read_best_score(void) 
{
	Player pla = {"", 0, 0, 0}; 
	FILE *fp = fopen("best_record.txt","r+");
	if ( fp ) {
		fscanf(fp,"%s", &pla.date.month);
		fscanf(fp,"%d", &pla.date.day);
		fscanf(fp,"%d", &pla.date.year);
		fscanf(fp,"%d", &pla.playscore);	
		fclose(fp);
	} 
	return pla;
}

//读入成绩
void recore_score( int score ) 
{	
	//读入成绩
	FILE *fp = fopen("recore.txt","a");
	if ( fp ) {
		fprintf(fp,"%s %d\n",__DATE__,score);
	}
	//更新最佳纪录
	Player bestpla = read_best_score();	
	int best_score = bestpla.playscore;
	if ( score <= best_score ) {
		printf("no enough\n");	
	} else {
		fp = fopen("best_record.txt","w");
		if ( fp ) {
			fprintf(fp,"%s %d",__DATE__,score);	
			fclose(fp);
		} 
	}
}

