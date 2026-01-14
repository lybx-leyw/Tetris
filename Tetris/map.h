#ifndef __MAP_H__
#define __MAP_H__

void reset_mymap ( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx] );
void printf_mymap( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx] );
void check_map ( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx], 
		Drawvalue* pdrawvalue, Viewvalue* pviewvalue );
Blockstate rand_productb( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx], BLOCK_Type nexttype );
void line_change (int* x, int* y, int line[2][3]);
int block_change (NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx], 
	Blockstate* pblockstate, CHANGE_Type change, int* score);
int clearmove( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx], int* score );
int gameOver( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx] );
void stead_map( NOfb* pnOfb, int mymap[pnOfb->nOfy][pnOfb->nOfx] );

#endif