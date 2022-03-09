#ifndef _ttp_h_
#define _ttp_h_

#include "common.h"
#include "ckt.h"

void ttp_run(char *lineInputBuffer);
int ttp_readLine(char *in);

void ttp_writeScreen();
void ttp_post( char* clli );
void ttp_post_number(int trunknum);
void ttp_bsy(int trunknum);
void ttp_rts(int trunknum);

void ttp_next( Circuit* circuit );
void ttp_first( Circuit* circuit );
void ttp_list_trunks();

#endif
