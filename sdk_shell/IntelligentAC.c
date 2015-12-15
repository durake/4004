/*
  * Copyright (c) 2013 Qualcomm Atheros, Inc..
  * All Rights Reserved.
  * Qualcomm Atheros Confidential and Proprietary.
  */

#include "qcom_common.h"
#include "threadx/tx_thread.h"
#include "threadx/tx_api.h"
#include "qcom_cli.h"
#include "threadxdmn_api.h"
#include "qcom_wps.h"
#include "qcom_uart.h"
#include "qcom_mem.h"


#define BYTE_POOL_SIZE_6K (6*1024 + 256 )
#define PSEUDO_HOST_STACK_SIZE_6K (6 * 1024 )

#define BYTE_POOL_SIZE_10K (10*1024 + 256 )
#define PSEUDO_HOST_STACK_SIZE_10K (10 * 1024 )

TX_BYTE_POOL pool0;
TX_THREAD host_thread;
TX_BYTE_POOL pool1;
TX_THREAD StateTimeTid;
TX_BYTE_POOL pool2;
TX_THREAD UartComTid;
TX_THREAD mainTid;
TX_BYTE_POOL pool4;
TX_THREAD reportStatusTid;
TX_BYTE_POOL pool5;
TX_THREAD xmppTid;
int devtype = 0x501;
TX_MUTEX localSendLock;
#define TSK_LocalSend_INIT tx_mutex_create(&localSendLock, "localSendLock tsk", TX_NO_INHERIT)

extern void user_pre_init(void);
extern void UartComThread(unsigned long which_thread);
extern void StateTimeThread(unsigned long which_thread);
extern void localReportThread(unsigned long which_thread);
extern void XmppThread(unsigned long which_thread);
extern int RegisterAIIPFrameFunc(void);

void shell_host_entry(ULONG which_thread)
{
//    extern void user_pre_init(void);
//    user_pre_init();
    
    qcom_enable_print(1);
    
    extern console_cmd_t cust_cmds[];
    extern int cust_cmds_num;
    extern void task_execute_cli_cmd();

    console_setup();
    console_reg_cmds(cust_cmds, cust_cmds_num);

    A_PRINTF("cli started ---------------\n");
    task_execute_cli_cmd();
    // Never returns 
}
void user_main(void)
{  
    TSK_LocalSend_INIT;

    tx_byte_pool_create(&pool1, "time pool", TX_POOL_CREATE_DYNAMIC, BYTE_POOL_SIZE_6K);
    {
        CHAR *pointer;
        tx_byte_allocate(&pool1, (VOID **) & pointer, PSEUDO_HOST_STACK_SIZE_6K, TX_NO_WAIT);
        tx_thread_create(&StateTimeTid, "time thread", StateTimeThread,
                         0, pointer, PSEUDO_HOST_STACK_SIZE_6K, 16, 16, 4, TX_AUTO_START);
    }
    
    tx_byte_pool_create(&pool2, "uart pool", TX_POOL_CREATE_DYNAMIC, BYTE_POOL_SIZE_10K);
    {
        CHAR *pointer;
        tx_byte_allocate(&pool2, (VOID **) & pointer, PSEUDO_HOST_STACK_SIZE_10K, TX_NO_WAIT);
        tx_thread_create(&UartComTid, "uart thread", UartComThread,
                         0, pointer, PSEUDO_HOST_STACK_SIZE_10K, 16, 16, 4, TX_AUTO_START);
    }
    

#if defined(AR6002_REV74)
    cdr_threadx_thread_init();
#endif
}

