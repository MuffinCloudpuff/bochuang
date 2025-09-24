/*
***************************************************************************
*    ģ�飺Queue 
*    ������Queue ѭ������
*    ���ߣ�Huo
*    ʱ�䣺2017.09.06
*    �汾��UP-Magic-Version 1.0.0
***************************************************************************
*/
#include "Queue.h"

/* ѭ������ȫ�ֱ������� */
Queue_Mem_Struct Queue_Recv ;

/*
***************************************************************************
*	�� �� ��: QueueMemDataInsert
*	����˵��: ѭ������ �������ݺ���
*	��    ��: data ���������
*	�� �� ֵ: �������ݳɹ����
***************************************************************************
*/
boolean QueueMemDataInsert(uint8_t data)
{
    if (MAX_QUEUE_LEN == Queue_Recv.MemLength)
    {
        return FULL_ERROR;
    }
    else
    {
		Queue_Recv.MemDataBuf[Queue_Recv.MemRearRecvIndex] = data ;
/*
		if(++Queue_Recv.MemRearRecvIndex >= MAX_QUEUE_LEN)
			{Queue_Recv.MemRearRecvIndex = 0;}
*/
		Queue_Recv.MemRearRecvIndex = 
		           (Queue_Recv.MemRearRecvIndex + 1) % MAX_QUEUE_LEN;
		Queue_Recv.MemLength ++ ;
		return RW_OK;
    }
}

/*
***************************************************************************
*	�� �� ��: QueueMemDataDel
*	����˵��: ѭ������ �������ݺ���
*	��    ��: *data �������ݴ�ŵ�ַ
*	�� �� ֵ: �������ݳɹ����
***************************************************************************
*/
boolean QueueMemDataDel(uint8_t *data)
{
    if (0 == Queue_Recv.MemLength)
    {
        return EMPTY_ERROR;
    }
    else
    {
        *data = Queue_Recv.MemDataBuf[Queue_Recv.MemFrontSendIndex];
        Queue_Recv.MemFrontSendIndex = 
		           (Queue_Recv.MemFrontSendIndex + 1) % MAX_QUEUE_LEN;
        Queue_Recv.MemLength -- ;
        return RW_OK;
    }
}


