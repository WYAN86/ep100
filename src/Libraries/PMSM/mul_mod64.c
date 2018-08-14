
#include "mul_mod64.h"

add64(add_sub64 *v) 
{ 
     
        //   进行长乘法(结果为64位) 

        u32   y1; 
        y1 = abs(y);
        
        if( (v->xs == 1) && (y>=0) )
        {
               v->zl = v->xl + y;
               if(v->zl < v->xl)
               {
                    v->zh = v->xh + 1;
               }
               else
               {
                    v->zh = v->xh;               
               }
               v->zs = 1;   
        }
        else if( (v->xs == 1) && (y<0) )
        {
               if(v->xl >= y1)
               {
                    v->zh = v->xh;
                    v->zl = v->xl - y1;
                    v->zs = 0;
               }
               else
               {
                    if(v->xh >= 1)
                    {
                         v->zl = v->xl - y1;
                         v->zh = v->xh - 1;
                         v->zs = 1; 
                    }
                    else
                    {
                         v->zl =  y1 - v->xl ;
                         v->zh = 1;
                         v->zs = 0;
                    }         
               }
        }
        else if( (v->xs == 0) && (y>=0) )
        {
               if(v->xl >= y)
               {
                    v->zh = v->xh;
                    v->zl = v->xl - y;
                    v->zs = 0;
               }
               else
               {
                    if(v->xh >= 1)
                    {
                         v->zl = v->xl - y;
                         v->zh = v->xh - 1;
                         v->zs = 0; 
                    }
                    else
                    {
                         v->zl =  y - v->xl ;
                         v->zh = 0;
                         v->zs = 1;
                    }         
               }
        }
        else if( (v->xs == 0) && (y<0) )
        {
               v->zl = v->xl + y1;
               if(v->zl < v->xl)
               {
                    v->zh = v->xh + 1;
               }
               else
               {
                    v->zh = v->xh;               
               }
               v->zs = 0;   
        }
        
}

sub64(add_sub64 *v) 
{ 
     
        //   进行长乘法(结果为64位) 

        u32   y1; 
        y1 = abs(y);
        
        if( (v->xs == 1) && (y>=0) )
        {
               v->zl = v->xl + y;
               if(v->zl < v->xl)
               {
                    v->zh = v->xh + 1;
               }
               else
               {
                    v->zh = v->xh;               
               }
               v->zs = 1;   
        }
        else if( (v->xs == 1) && (y<0) )
        {
               if(v->xl >= y1)
               {
                    v->zh = v->xh;
                    v->zl = v->xl - y1;
                    v->zs = 0;
               }
               else
               {
                    if(v->xh >= 1)
                    {
                         v->zl = v->xl - y1;
                         v->zh = v->xh - 1;
                         v->zs = 1; 
                    }
                    else
                    {
                         v->zl =  y1 - v->xl ;
                         v->zh = 1;
                         v->zs = 0;
                    }         
               }
        }
        else if( (v->xs == 0) && (y>=0) )
        {
               if(v->xl >= y)
               {
                    v->zh = v->xh;
                    v->zl = v->xl - y;
                    v->zs = 0;
               }
               else
               {
                    if(v->xh >= 1)
                    {
                         v->zl = v->xl - y;
                         v->zh = v->xh - 1;
                         v->zs = 0; 
                    }
                    else
                    {
                         v->zl =  y - v->xl ;
                         v->zh = 0;
                         v->zs = 1;
                    }         
               }
        }
        else if( (v->xs == 0) && (y<0) )
        {
               v->zl = v->xl + y1;
               if(v->zl < v->xl)
               {
                    v->zh = v->xh + 1;
               }
               else
               {
                    v->zh = v->xh;               
               }
               v->zs = 0;   
        }
        
}

mul64(mul_mod64 *v) 
{ 
     
        //   进行长乘法(结果为64位) 

        u32   u0,   v0,   w0; 
        u32   u1,   v1,   w1,   w2,   t; 
  
        u0   =   v->xl   &   0xFFFF;     u1   =   v->xl   > >   16; 
        v0   =   v->y   &   0xFFFF;     v1   =   0; 
        w0   =   u0*v0; 
        t     =   u1*v0   +   (w0   > >   16); 
        w1   =   t   &   0xFFFF; 
        w2   =   t   > >   16; 
        //w1   =   u0*v1   +   w1; 

        //   x为高32位,   y为低32位 

        //v->zh   =   u1*v1   +   w2   +   (w1   > >   16) +  v->xh*v->y; 
        v->zh   = w2   +   (w1   > >   16) +  v->xh*v->y; 
        v->zl   =   u*v; 
        
        
        v->zs   =   v->xs; 
}

mod64(mul_mod64 *v) 
{ 
     
        //   进行长乘法(结果为64位) 

        u32   u0,   v0,   w0; 
        u32   u1,   v1,   w1,   u2; 

        v->zh = v->xh/v->y;
        
        u0 = v->xh%y;
        
        v0 = ( v->xl>>10 ) & 0x3fffff;
        
        w0 = (u0<<22) + v0;
        
        u1 = w0/v->y;
        
        v1 = w0%v->y;
        
        w1 =  v1<<10 + v->xl & 0x3ff  ;
        
        u2 = w1/v->y;
        
        v->zl = u1<<22 + u2;
        
        v->zs   =   v->xs; 
}



/*
//   计算(u*v)%m 

unsigned   mul_mod(unsigned   u,   unsigned   v,   unsigned   z) 
{ 
        //   如果u*v没有溢出,   则直接计算 

        if((u*v)/u   ==   v)   return   (u*v)%z; 

        //   进行长乘法(结果为64位) 

        unsigned   u0,   v0,   w0; 
        unsigned   u1,   v1,   w1,   w2,   t; 
  
        u0   =   u   &   0xFFFF;     u1   =   u   > >   16; 
        v0   =   v   &   0xFFFF;     v1   =   v   > >   16; 
        w0   =   u0*v0; 
        t     =   u1*v0   +   (w0   > >   16); 
        w1   =   t   &   0xFFFF; 
        w2   =   t   > >   16; 
        w1   =   u0*v1   +   w1; 

        //   x为高32位,   y为低32位 

        unsigned   x   =   u1*v1   +   w2   +   (w1   > >   16); 
        unsigned   y   =   u*v; */

