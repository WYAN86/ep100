#include "nvic_conf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/   
/* Private function prototypes -----------------------------------------------*/

void nvic_conf(void)
{

     NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x00000000);

     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
     
 
}