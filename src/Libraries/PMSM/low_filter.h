#ifndef __LOW_FILTER_H
#define __LOW_FILTER_H

//#include "stm32f10x.h"
#include "IQmathLib.h"


typedef struct
{
     _iq  Input;
     _iq  Output[2];
     _iq  FilterTf;
     _iq  FilterTs;
     _iq  Kr;
     _iq  Ky;
} low_filter;

#define low_filter_default {0, {0,0}, 0, 0, 0, 0}

//ÂË²¨
extern low_filter speed_ref_filter;
extern low_filter speed_fdb_filter;

extern low_filter iq_ref_filter;
extern low_filter iq_fdb_filter;

extern low_filter id_ref_filter;
extern low_filter id_fdb_filter;

extern low_filter vdc_filter;

//extern low_filter pos_ref_filter;
//extern low_filter pos_forward_filter;

extern low_filter as_filter;

void low_filter_init(low_filter *v);
void low_filter_calc(low_filter *v);

#endif
