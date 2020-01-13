#include <includes.h>

/**************************************************************
*                       ����������ƿ�
**************************************************************/
static  OS_TCB   AppTaskStartTCB;


/**************************************************************
*                      ��������ջ
**************************************************************/
static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];


/*************************************************************
*                    ��������
*************************************************************/
static  void  AppTaskStart  (void *p_arg);


int  main (void)
{
    OS_ERR  err;

    /* ��ʼ��ϵͳ*/
    OSInit(&err);                                               

    /* �������� */
    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                
                 (CPU_CHAR   *)"App Task Start",
                 (OS_TASK_PTR ) AppTaskStart,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_START_PRIO,
                 (CPU_STK    *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
                 
    /* ��������*/
    OSStart(&err);                                              
		
		
}


/***********************************************************************
  * @ ������  �� AppTaskStart
  * @ ����˵���� Ϊ�˷���������е����񴴽����������������������
  * @ ����    �� ��  
  * @ ����ֵ  �� ��
  **********************************************************************/

static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    OS_ERR      err;


   (void)p_arg;
    /* ������Ӳ����ʼ�� */
    BSP_Init();          
  
    CPU_Init();

    cpu_clk_freq = BSP_CPU_ClkFreq();                           
    cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        
    OS_CPU_SysTickInit(cnts);                                   
     
    /* �ڴ��ʼ��*/
    Mem_Init();                                                
#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               
#endif

    CPU_IntDisMeasMaxCurReset();

    /* ��ѭ�� */
    while (DEF_TRUE) 
    {                                          
			macLED1_TOGGLE ();
			OSTimeDly ( 5000, OS_OPT_TIME_DLY, & err );
    }
		
		
}




