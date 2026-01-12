#include "main.h"
#include <stdio.h>
#include <stdlib.h> 

//读出最佳成绩
Player read_best_score(void) 
{
	Player pla = {"", 0, 0, 0}; 
	FILE *fp = fopen("best_record.txt","r");
	fflush(fp);
	if ( fp ) {
		fscanf(fp,"%s", &pla.date.month);
		fscanf(fp,"%d", &pla.date.day);
		fscanf(fp,"%d", &pla.date.year);
		fscanf(fp,"%d", &pla.playscore);	
		fclose(fp);
	} else {
		exit(0); 
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
	} else {
		exit(0); 
	}
	//更新最佳纪录
	Player bestpla = read_best_score();	
	int best_score = bestpla.playscore;
	fclose(fp);
	
	if ( score <= best_score ) {
		printf("no enough\n");	
	} else {
		fp = fopen("best_record.txt","w");
		if ( fp ) {
			fprintf(fp,"%s %d",__DATE__,score);	
			fclose(fp);
		} else {
			exit(0); 
		}
	}
}
