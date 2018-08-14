#include "rampgen.h"



rampgen rampgen_parameter = rampgen_default;

void rampgen_calc(rampgen *v)
{

     v->Angle += _IQmpy(v->StepAngleMax,v->Freq);
     

     if (v->Angle > _IQ(1.0))
          v->Angle -= _IQ(1.0);
     else if (v->Angle < _IQ(-1.0))
          v->Angle += _IQ(1.0);
     

     v->Out = _IQmpy(v->Angle,v->Gain) + v->Offset;
     

     if (v->Out > _IQ(1.0))
          v->Out -= _IQ(1.0);
     else if (v->Out < _IQ(-1.0))
          v->Out += _IQ(1.0);
}

