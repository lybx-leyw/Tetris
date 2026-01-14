#ifndef __DRAW_H__
#define __DRAW_H__

void draw_block( float x, float y, Drawvalue* pdrawvalue );
void draw_blank( float x, float y, Drawvalue* pdrawvalue );
void draw_boarden( Drawvalue* pdrawvalue, NOfb* pnOfb, Viewvalue* pviewvalue );
void draw_some_clear(int nclear,Viewvalue* pviewvalue ,Drawvalue* pdrawvalue );
void draw_prompt( Viewvalue* pviewvalue ,Drawvalue* pdrawvalue ,PROMPT_Type );
void product_Bview(BLOCK_Type nexttype, NOfb* pnOfb, Drawvalue* pdrawvalue);
char* donextText(int nextype);
void draw_const_text ( NOfb* pnOfb, Viewvalue* pviewvalue ,Drawvalue* pdrawvalue ,
		Gamevalue* pgamevalue);
void draw_guide(void);

#endif