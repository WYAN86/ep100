#include "low_filter.h"


low_filter speed_ref_filter;
low_filter speed_fdb_filter;

low_filter iq_ref_filter;
low_filter iq_fdb_filter;

low_filter id_ref_filter;
low_filter id_fdb_filter;

low_filter as_filter;



void low_filter_init(low_filter *v)
{
     v->Kr = _IQdiv(v->FilterTs , (v->FilterTs+ v->FilterTf));
     v->Ky = _IQdiv(v->FilterTf , (v->FilterTs +v->FilterTf));
}


void low_filter_calc(low_filter *v)
{
     v->Output[0] = _IQmpy(v->Kr,v->Input) + _IQmpy(v->Ky,v->Output[1]);
     v->Output[1] = v->Output[0];
}