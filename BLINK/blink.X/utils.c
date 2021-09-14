#include "utils.h"

/*F**************************************************************************
* NAME: MSdelay
*----------------------------------------------------------------------------
* PARAMS:
* val: delay in milliseconds
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Set a delay in milliseconds
*----------------------------------------------------------------------------
* NOTE:
* 9
*****************************************************************************/
void MSdelay(unsigned int val)
{
 unsigned int i,j;
 for(i=0;i<val;i++)
     for(j=0;j<165;j++);  /*This count Provide delay of 1 ms for 8MHz Frequency */
} 

