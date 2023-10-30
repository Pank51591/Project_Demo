# RT-Thread 学习笔记

RT-Thread 采用内核对象管理系统来访问 / 管理所有内核对象，内核对象包含了内核中绝大部分设施，这些内核对象可以是静态分配的静态对象，也可以是从系统内存堆中分配的动态对象。

通过这种内核对象的设计方式，RT-Thread 做到了不依赖于具体的内存分配方式，系统的灵活性得到极大的提高。



### RT-Thread 常用的文件有哪些？

| 文件名     | 介绍                                                         |
| ---------- | :----------------------------------------------------------- |
| rtconfig.h | rtconfig.h 是 RT-Thread 功能的配置头文件，里面定义了很多宏，通过这些宏定义，我们可以裁剪 RT-Thread 的功能。 |
| board.c    | board.c 是直接从 RT-Thread/3.0.3/bsp 文件夹下面拷贝过来的，里面存放的是与硬件相关的初始化函数 |
| rthw.h     | rthw.h 是处理器相关                                          |
| clock.c    | clock.c 第一次使用需要自行在文件夹 rtthread\3.0.3\src 中新建并添加到工程的 rtt/source 组中，里面存放着与系统时钟相关的函数。 |
| timer.c    | 与系统定时器相关的函数。                                     |



### 官方文件夹包含的内容

| 名称          | 描述                                                    |
| ------------- | ------------------------------------------------------- |
| BSP           | Board Support Package（板级支持包）基于各种开发板的移植 |
| components    | RT-Thread 的各个组件代码，例如 finsh，gui 等。          |
| documentation | 相关文档，如编码规范等                                  |
| examples      | 相关示例代码                                            |
| include       | RT-Thread 内核的头文件。                                |
| libcpu        | 各类芯片的移植代码。                                    |
| src           | RT-Thread 内核的源文件。                                |
| tools         | RT-Thread 命令构建工具的脚本文件。                      |

### 什么是容器？

容器是一个全部变量的数组，数据类型为 ==struct  rt_object_information==，这是一个结构体类型，包含对象的三个信息，分别为 <u>对象类型、对象列表节点头和对象的大小</u>。



### 什么是IPC对象？

​		[IPC](https://so.csdn.net/so/search?q=IPC&spm=1001.2101.3001.7020)对象是==活动在内核级别的一种 进程间通信 的工具==。 存在的IPC对象通过它的标识符来引用和访问，这个标识符是一个非负整数，它唯一的标识了一个IPC对象，这个IPC对象可以是 **消息队列** 或 **信号量** 或 **共享存储器**中的任意一种类型。



### 容器的接口实现

容器接口相关的函数均在 object.c 中实现。

从容器中获取指定类型的对象的信息由函数 rt_object_get_information()实现



### 对象类型枚举

```c
    1 enum rt_object_class_type

    2 {

    3 RT_Object_Class_Thread = 0, /* 对象是线程 */

    4 RT_Object_Class_Semaphore, /* 对象是信号量 */

    5 RT_Object_Class_Mutex, /* 对象是互斥量 */

    6 RT_Object_Class_Event, /* 对象是事件 */

    7 RT_Object_Class_MailBox, /* 对象是邮箱 */

    8 RT_Object_Class_MessageQueue, /* 对象是消息队列 */

    9 RT_Object_Class_MemHeap, /* 对象是内存堆 */

    10 RT_Object_Class_MemPool, /* 对象是内存池 */

    11 RT_Object_Class_Device, /* 对象是设备 */

    12 RT_Object_Class_Timer, /* 对象是定时器 */

    13 RT_Object_Class_Module, /* 对象是模块 */

    14 RT_Object_Class_Unknown, /* 对象未知 */

    15 RT_Object_Class_Static = 0x80 /* 对象是静态对象 */

    16 };
```



### 线程结构体

```c
struct rt_thread
{
/* rt 对象 */
char name[RT_NAME_MAX]; /* 对象的名字 */
rt_uint8_t type; /* 对象类型 */
rt_uint8_t flags; /* 对象的状态 */
rt_list_t list; /* 对象的列表节点 */

rt_list_t tlist; /* 线程链表节点 */

void *sp; /* 线程栈指针 */
void *entry; /* 线程入口地址 */
void *parameter; /* 线程形参 */
void *stack_addr; /* 线程起始地址 */
rt_uint32_t stack_size; /* 线程栈大小，单位为字节 */

rt_ubase_t init_tick; /* 初始时间片 */ 
rt_ubase_t remaining_tick; /* 剩余时间片 */ 

rt_uint8_t current_priority; /* 当前优先级 */
rt_uint8_t init_priority; /* 初始优先级 */
rt_uint32_t number_mask; /* 当前优先级掩码 */

rt_err_t error; /* 错误码 */
rt_uint8_t stat; /* 线程的状态 */

struct rt_timer thread_timer; /* 内置的线程定时器 */
};
```



### 什么是临界段？

​		代码的临界段也称为临界区，指处理时不可分割的代码区域，**一旦这部分代码开始执行，则不允许任何中断打断。**为确保临界段代码的执行不被中断，在进入临界段之前须关中断，而临界段代码执行完毕后，要立即打开中断。

```c
    ; 开关中断函数的实现 
    ;/*
    ; * void rt_hw_interrupt_disable();
    ; */
    rt_hw_interrupt_disable PROC
    EXPORT rt_hw_interrupt_disable
    CPSID I (1)
    BX LR
    ENDP

    ;/*
    ; * void rt_hw_interrupt_enable(void);
    ; */
    rt_hw_interrupt_enable PROC
    EXPORT rt_hw_interrupt_enable
    CPSIE I (2)
    BX LR
    ENDP 
        
    PRIMASK = 0; /* PRIMASK 初始值为 0,表示没有关中断 */ (3) 
    /* 临界段代码保护 */
    {
        /* 临界段开始 */
        rt_hw_interrupt_disable(); /* 关中断,PRIMASK = 1 */ (4)
        {
            /* 执行临界段代码，不可中断 */ (5)
        }
        /* 临界段结束 */
        rt_hw_interrupt_enable(); /* 开中断,PRIMASK = 0 */ (6)
     }
```

### 线程对象的创建

```c
/**
 * This function will create a thread object and allocate thread object memory
 * and stack.
 *
 * @param name the name of thread, which shall be unique
 * @param entry the entry function of thread
 * @param parameter the parameter of thread enter function
 * @param stack_size the size of thread stack
 * @param priority the priority of thread
 * @param tick the time slice if there are same priority thread
 *
 * @return the created thread object
 */
rt_thread_t rt_thread_create(const char *name,         //线程的名称
                             void (*entry)(void *parameter),       //入口函数
                             void       *parameter,       //线程的入口函数的参数
                             rt_uint32_t stack_size,      //线程栈的大小
                             rt_uint8_t  priority,        //优先级
                             rt_uint32_t tick)            //时间片
{
    struct rt_thread *thread;
    void *stack_start;

    thread = (struct rt_thread *)rt_object_allocate(RT_Object_Class_Thread,
                                                    name);
    if (thread == RT_NULL)
        return RT_NULL;

    stack_start = (void *)RT_KERNEL_MALLOC(stack_size);
    if (stack_start == RT_NULL)
    {
        /* allocate stack failure */
        rt_object_delete((rt_object_t)thread);

        return RT_NULL;
    }

    _rt_thread_init(thread,
                    name,
                    entry,
                    parameter,
                    stack_start,
                    stack_size,
                    priority,
                    tick);

    return thread;
}
```

### 线程是如何切换的？

创建线程，并将线程按顺序放到就绪列表中。

```c
/* 初始化线程 */
rt_thread_init( &rt_flag1_thread,  /* 线程控制块 */
				flag1_thread_entry,  /* 线程入口地址 */
				RT_NULL,  /* 线程形参 */
				&rt_flag1_thread_stack[0],  /* 线程栈起始地址 */
				sizeof(rt_flag1_thread_stack) );  /* 线程栈大小，单位为字节 */

/* 将线程插入到就绪列表 */ 
rt_list_insert_before( &(rt_thread_priority_table[0]),&(rt_flag1_thread.tlist) ); 
 
/* 初始化线程 */
rt_thread_init( &rt_flag2_thread, /* 线程控制块 */
				flag2_thread_entry, /* 线程入口地址 */
                RT_NULL, /* 线程形参 */
                &rt_flag2_thread_stack[0], /* 线程栈起始地址 */
                sizeof(rt_flag2_thread_stack) ); /* 线程栈大小，单位为字节 */

/* 将线程插入到就绪列表 */ 
rt_list_insert_before( &(rt_thread_priority_table[1]),&(rt_flag2_thread.tlist) );
```

==就绪列表==的下标对应的是线程的优先级，但是目前我们的线程还不支持优先级，有关支持多优先级的知识点我们后面会讲到，所以 flag1 和 flag2 线程在插入到就绪列表的时候可以随便选择插入的位置。



==调度器==是操作系统的核心，其主要功能就是**实现线程的切换**，即从就绪列表里面找到优先级最高的线程，然后去执行该线程。从代码上来看，调度器无非也就是由几个全局变量和一些可以实现线程切换的函数组成，全部都在 scheduler.c 文件中实现。

**初始化系统调度器**

```c
/***********初始化系统调度器**********/
/**
 * @ingroup SystemInit
 * This function will initialize the system scheduler
 */
void rt_system_scheduler_init(void)
{
    register rt_base_t offset;

    rt_scheduler_lock_nest = 0;

    RT_DEBUG_LOG(RT_DEBUG_SCHEDULER, ("start scheduler: max priority 0x%02x\n",
                                      RT_THREAD_PRIORITY_MAX));
    
    /*线程就绪列表初始化*/
    for (offset = 0; offset < RT_THREAD_PRIORITY_MAX; offset ++)
    {
        rt_list_init(&rt_thread_priority_table[offset]);     ////线程优先级列表
    }

    rt_current_priority = RT_THREAD_PRIORITY_MAX - 1;
    rt_current_thread = RT_NULL;       //初始化当前线程栈

    /* initialize ready priority group */
    rt_thread_ready_priority_group = 0;

#if RT_THREAD_PRIORITY_MAX > 32
    /* initialize ready table */
    rt_memset(rt_thread_ready_table, 0, sizeof(rt_thread_ready_table));
#endif

    /* initialize thread defunct */
    rt_list_init(&rt_thread_defunct);     //
}
```

**启动系统调度器**

```c
/************启动系统调度器**********/
/**
 * @ingroup SystemInit
 * This function will startup 启动 scheduler. It will select one thread
 * with the highest priority level, then switch to it.
 */
void rt_system_scheduler_start(void)
{
    register struct rt_thread *to_thread;
    register rt_ubase_t highest_ready_priority;

#if RT_THREAD_PRIORITY_MAX > 32
    register rt_ubase_t number;

    number = __rt_ffs(rt_thread_ready_priority_group) - 1;
    highest_ready_priority = (number << 3) + __rt_ffs(rt_thread_ready_table[number]) - 1;
#else
    highest_ready_priority = __rt_ffs(rt_thread_ready_priority_group) - 1;
#endif

    /* get switch to thread  手动指定第一个运行的线程*/
    to_thread = rt_list_entry(rt_thread_priority_table[highest_ready_priority].next,
                              struct rt_thread,
                              tlist);

    rt_current_thread = to_thread;

    /* switch to new thread   线程切换*/
    rt_hw_context_switch_to((rt_uint32_t)&to_thread->sp);

    /* never come back */
}
```



**系统调度函数**

```c
/**
 * This function will perform 执行 one schedule. It will select one thread
 * with the highest priority level, then switch to it.
 */
void rt_schedule(void)
{
    rt_base_t level;
    struct rt_thread *to_thread;
    struct rt_thread *from_thread;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* check the scheduler is enabled or not */
    if (rt_scheduler_lock_nest == 0)
    {
        register rt_ubase_t highest_ready_priority;

#if RT_THREAD_PRIORITY_MAX <= 32
        highest_ready_priority = __rt_ffs(rt_thread_ready_priority_group) - 1;
#else
        register rt_ubase_t number;

        number = __rt_ffs(rt_thread_ready_priority_group) - 1;
        highest_ready_priority = (number << 3) + __rt_ffs(rt_thread_ready_table[number]) - 1;
#endif

        /* get switch to thread 指定下一个运行的线程*/
        to_thread = rt_list_entry(rt_thread_priority_table[highest_ready_priority].next,
                                  struct rt_thread,
                                  tlist);

        /* if the destination thread is not the same as current thread 如果目标线程与当前线程不同 */
        if (to_thread != rt_current_thread)
        {
            rt_current_priority = (rt_uint8_t)highest_ready_priority;
            from_thread         = rt_current_thread;
            rt_current_thread   = to_thread;

            RT_OBJECT_HOOK_CALL(rt_scheduler_hook, (from_thread, to_thread));

            /* switch to new thread */
            RT_DEBUG_LOG(RT_DEBUG_SCHEDULER,
                         ("[%d]switch to priority#%d "
                          "thread:%.*s(sp:0x%p), "
                          "from thread:%.*s(sp: 0x%p)\n",
                          rt_interrupt_nest, highest_ready_priority,
                          RT_NAME_MAX, to_thread->name, to_thread->sp,
                          RT_NAME_MAX, from_thread->name, from_thread->sp));

#ifdef RT_USING_OVERFLOW_CHECK
            _rt_scheduler_stack_check(to_thread);
#endif

            if (rt_interrupt_nest == 0)
            {
                extern void rt_thread_handle_sig(rt_bool_t clean_state);

                rt_hw_context_switch((rt_uint32_t)&from_thread->sp,
                                     (rt_uint32_t)&to_thread->sp);

                /* enable interrupt */
                rt_hw_interrupt_enable(level);

#ifdef RT_USING_SIGNALS
                /* check signal status */
                rt_thread_handle_sig(RT_TRUE);
#endif
            }
            else
            {
                RT_DEBUG_LOG(RT_DEBUG_SCHEDULER, ("switch in interrupt\n"));

                rt_hw_context_switch_interrupt((rt_uint32_t)&from_thread->sp,
                                               (rt_uint32_t)&to_thread->sp);
                /* enable interrupt */
                rt_hw_interrupt_enable(level);
            }
        }
        else
        {
            /* enable interrupt */
            rt_hw_interrupt_enable(level);
        }
    }
    else
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(level);
    }
}

```



### 对消息队列的接收

```c
/*消息队列结构体*/
struct rt_messagequeue
{
    struct rt_ipc_object parent;              /**< inherit from ipc_object */

    void                *msg_pool;            /**< start address of message queue */

    rt_uint16_t          msg_size;            /**< message size of each message */
    rt_uint16_t          max_msgs;            /**< max number of messages */

    rt_uint16_t          entry;               /**< index of messages in the queue 队列中消息的索引*/
    void                *msg_queue_head;      /**< list head */
    void                *msg_queue_tail;      /**< list tail */
    void                *msg_queue_free;      /**< pointer indicated the free node of queue 指针指示队列的空闲节点*/
};
typedef struct rt_messagequeue *rt_mq_t;
```



```c
/**
 * This function will receive a message from message queue object, if there is
 * no message in message queue object, the thread shall wait for a specified
 * time.
 * 此函数将接收来自消息队列对象的消息，如果消息队列对象中没有消息，线程将等待指定的时间
 *
 * @param mq the message queue object
 * @param buffer the received message will be saved in
 * @param size the size of buffer
 * @param timeout the waiting time
 *
 * @return the error code
 */
rt_err_t rt_mq_recv(rt_mq_t    mq,      /* 读取（接收）队列的ID(句柄) */
                    void      *buffer,  /* 读取（接收）的数据保存位置 */
                    rt_size_t  size,
                    rt_int32_t timeout)
{
    struct rt_thread *thread;
    register rt_ubase_t temp;
    struct rt_mq_message *msg;
    rt_uint32_t tick_delta;

    RT_ASSERT(mq != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(size != 0);

    /* initialize delta tick 初始化增量刻度*/
    tick_delta = 0;
    
    /* get current thread */
    thread = rt_thread_self();
    RT_OBJECT_HOOK_CALL(rt_object_trytake_hook, (&(mq->parent.parent)));

    /* disable interrupt */
    temp = rt_hw_interrupt_disable();

    /* for non-blocking call */
    if (mq->entry == 0 && timeout == 0)
    {
        rt_hw_interrupt_enable(temp);

        return -RT_ETIMEOUT;
    }

    /* message queue is empty */
    while (mq->entry == 0)
    {
        RT_DEBUG_IN_THREAD_CONTEXT;

        /* reset error number in thread */
        thread->error = RT_EOK;

        /* no waiting, return timeout */
        if (timeout == 0)
        {
            /* enable interrupt */
            rt_hw_interrupt_enable(temp);

            thread->error = -RT_ETIMEOUT;

            return -RT_ETIMEOUT;
        }

        /* suspend current thread */
        rt_ipc_list_suspend(&(mq->parent.suspend_thread),
                            thread,
                            mq->parent.parent.flag);

        /* has waiting time, start thread timer */
        if (timeout > 0)
        {
            /* get the start tick of timer */
            tick_delta = rt_tick_get();

            RT_DEBUG_LOG(RT_DEBUG_IPC, ("set thread:%s to timer list\n",
                                        thread->name));

            /* reset the timeout of thread timer and start it */
            rt_timer_control(&(thread->thread_timer),
                             RT_TIMER_CTRL_SET_TIME,
                             &timeout);
            rt_timer_start(&(thread->thread_timer));
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(temp);

        /* re-schedule */
        rt_schedule();      //选择一个最高优先级的线程，执行

        /* recv message */
        if (thread->error != RT_EOK)
        {
            /* return error */
            return thread->error;
        }

        /* disable interrupt */
        temp = rt_hw_interrupt_disable();

        /* if it's not waiting forever and then re-calculate timeout tick */
        if (timeout > 0)
        {
            tick_delta = rt_tick_get() - tick_delta;
            timeout -= tick_delta;
            if (timeout < 0)
                timeout = 0;
        }
    }

    /* get message from queue */
    msg = (struct rt_mq_message *)mq->msg_queue_head;

    /* move message queue head */
    mq->msg_queue_head = msg->next;
    
    /* reach queue tail, set to NULL */
    if (mq->msg_queue_tail == msg)
        mq->msg_queue_tail = RT_NULL;

    /* decrease message entry */
    mq->entry --;

    /* enable interrupt */
    rt_hw_interrupt_enable(temp);

    /* copy message */
    rt_memcpy(buffer, msg + 1, size > mq->msg_size ? mq->msg_size : size);

    /* disable interrupt */
    temp = rt_hw_interrupt_disable();
    
    /* put message to free list */
    msg->next = (struct rt_mq_message *)mq->msg_queue_free;
    mq->msg_queue_free = msg;
    
    /* enable interrupt */
    rt_hw_interrupt_enable(temp);

    RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(mq->parent.parent)));

    return RT_EOK;
}
```

### 消息队列的发送

```c
/**
 * This function will send a message to message queue object, if there are
 * threads suspended on message queue object, it will be waked up.
 *
 * @param mq the message queue object
 * @param buffer the message
 * @param size the size of buffer
 *
 * @return the error code
 */
rt_err_t rt_mq_send(rt_mq_t mq, void *buffer, rt_size_t size)
{
    register rt_ubase_t temp;
    struct rt_mq_message *msg;

    RT_ASSERT(mq != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(size != 0);

    /* greater than one message size */
    if (size > mq->msg_size)
        return -RT_ERROR;

    RT_OBJECT_HOOK_CALL(rt_object_put_hook, (&(mq->parent.parent)));

    /* disable interrupt */
    temp = rt_hw_interrupt_disable();

    /* get a free list, there must be an empty item */
    msg = (struct rt_mq_message *)mq->msg_queue_free;
    /* message queue is full */
    if (msg == RT_NULL)
    {
        /* enable interrupt */
        rt_hw_interrupt_enable(temp);

        return -RT_EFULL;
    }
    /* move free list pointer */
    mq->msg_queue_free = msg->next;

    /* enable interrupt */
    rt_hw_interrupt_enable(temp);

    /* the msg is the new tailer of list, the next shall be NULL */
    msg->next = RT_NULL;
    /* copy buffer */
    rt_memcpy(msg + 1, buffer, size);

    /* disable interrupt */
    temp = rt_hw_interrupt_disable();
    /* link msg to message queue */
    if (mq->msg_queue_tail != RT_NULL)
    {
        /* if the tail exists, */
        ((struct rt_mq_message *)mq->msg_queue_tail)->next = msg;
    }

    /* set new tail */
    mq->msg_queue_tail = msg;
    /* if the head is empty, set head */
    if (mq->msg_queue_head == RT_NULL)
        mq->msg_queue_head = msg;

    /* increase message entry */
    mq->entry ++;

    /* resume suspended thread */
    if (!rt_list_isempty(&mq->parent.suspend_thread))
    {
        rt_ipc_list_resume(&(mq->parent.suspend_thread));

        /* enable interrupt */
        rt_hw_interrupt_enable(temp);

        rt_schedule();

        return RT_EOK;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(temp);

    return RT_EOK;
}
RTM_EXPORT(rt_mq_send);
```

### 创建一个消息队列

如何给一个消息队列的结构体元素赋值，然后得到一个新的消息队列结构体？

```c
/**
 * This function will create a message queue object from system resource
 *
 * @param name the name of message queue
 * @param msg_size the size of message
 * @param max_msgs the maximum number of message in queue
 * @param flag the flag of message queue
 *
 * @return the created message queue, RT_NULL on error happen
 */
rt_mq_t rt_mq_create(const char *name,
                     rt_size_t   msg_size,
                     rt_size_t   max_msgs,
                     rt_uint8_t  flag)
{
    struct rt_messagequeue *mq;
    struct rt_mq_message *head;
    register rt_base_t temp;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* allocate object */
    mq = (rt_mq_t)rt_object_allocate(RT_Object_Class_MessageQueue, name);
    if (mq == RT_NULL)
        return mq;

    /* set parent */
    mq->parent.parent.flag = flag;

    /* init ipc object */
    rt_ipc_object_init(&(mq->parent));

    /* init message queue */

    /* get correct message size */
    mq->msg_size = RT_ALIGN(msg_size, RT_ALIGN_SIZE);
    mq->max_msgs = max_msgs;

    /* allocate message pool */
    mq->msg_pool = RT_KERNEL_MALLOC((mq->msg_size + sizeof(struct rt_mq_message)) * mq->max_msgs);
    if (mq->msg_pool == RT_NULL)
    {
        rt_mq_delete(mq);

        return RT_NULL;
    }

    /* init message list */
    mq->msg_queue_head = RT_NULL;
    mq->msg_queue_tail = RT_NULL;

    /* init message empty list */
    mq->msg_queue_free = RT_NULL;
    for (temp = 0; temp < mq->max_msgs; temp ++)
    {
        head = (struct rt_mq_message *)((rt_uint8_t *)mq->msg_pool +
                                        temp * (mq->msg_size + sizeof(struct rt_mq_message)));
        head->next = mq->msg_queue_free;
        mq->msg_queue_free = head;
    }

    /* the initial entry is zero */
    mq->entry = 0;

    return mq;
}
RTM_EXPORT(rt_mq_create);
```

### RT-Thread对Printf的重映射

```c
/**
  * @brief：  重映射串口DEBUG_USARTx到rt_kprintf()函数
  *   Note：DEBUG_USARTx是在bsp_usart.h中定义的宏，默认使用串口1
  * @param str：要输出到串口的字符串
  * @retval ：无
  *
  * @attention
  * 
  */
void rt_hw_console_output(const char *str)
{	
	/* 进入临界段 （代码保护，不会进入中断）*/
    rt_enter_critical();

	/* 直到字符串结束 */
    while (*str!='\0')
	{
		/* 换行 */
        if (*str=='\n')
		{
			USART_SendData(DEBUG_USARTx, '\r');     //输入一个回车
			while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);
		}

		USART_SendData(DEBUG_USARTx, *str++); 				
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);	
	}	

	/* 退出临界段 */
    rt_exit_critical();
}
```

### 线程计时时间增长的函数

```c
/**
 * This function will notify kernel there is one tick passed. Normally,
 * this function is invoked by clock ISR.
 */
void rt_tick_increase(void)
{
    struct rt_thread *thread;

    /* increase the global tick */
    ++ rt_tick;

    /* check time slice 检查时间片*/
    thread = rt_thread_self();

    -- thread->remaining_tick;   //剩余时间
    if (thread->remaining_tick == 0)
    {
        /* change to initialized tick */
        thread->remaining_tick = thread->init_tick;

        /* yield 这个函数将出让当前线程产生处理器，调度程序将选择最高线程运行。在yield处理器之后，当前			线程仍然处于READY状态。*/
        rt_thread_yield();
    }

    /* check timer */
    rt_timer_check();
}
```



```c
/**
 * This function will let current thread yield processor, and scheduler will
 * choose a highest thread to run. After yield processor, the current thread
 * is still in READY state.
 *
 * @return RT_EOK
 */
rt_err_t rt_thread_yield(void)
{
    register rt_base_t level;
    struct rt_thread *thread;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    /* set to current thread */
    thread = rt_current_thread;

    /* if the thread stat is READY and on ready queue list */
    if ((thread->stat & RT_THREAD_STAT_MASK) == RT_THREAD_READY &&
        thread->tlist.next != thread->tlist.prev)
    {
        /* remove thread from thread list */
        rt_list_remove(&(thread->tlist));

        /* put thread to end of ready queue */
        rt_list_insert_before(&(rt_thread_priority_table[thread->current_priority]),
                              &(thread->tlist));

        /* enable interrupt */
        rt_hw_interrupt_enable(level);
        
        /*线程调度：切换到最高优先级的线程*/
        rt_schedule();

        return RT_EOK;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
RTM_EXPORT(rt_thread_yield);
```

### 定时器的实现

​		在 RT-Thread 中，每个线程都内置一个定时器，当线程需要延时的时候，则先将线程挂起，然后内置的定时器就会启动，并且将定时器插入到一个==全局的系统定时器列表rt_timer_list==，这个全局的系统定时器列表维护着一条双向链表，每个节点代表了正在延时的线程的定时器，节点按照延时时间大小做升序排列。当每次时基中断SysTick 中断）来临时，就扫描系统定时器列表的第一个定时器，看看延时时间是否到，如果到则让该定时器对应的线程就绪，如果延时时间不到，则退出扫描，因为定时器节点是按照延时时间升序排列的，第一个定时器延时时间不到期的话，那后面的定时器延时时间自然不到期。比起第一种方法，这种方法就大大缩短了寻找延时到期的线程的时间。

**定时器结构体**

```c
/**
 * timer structure
 */
struct rt_timer
{
    struct rt_object parent;                            /**< inherit from rt_object */

    rt_list_t        row[RT_TIMER_SKIP_LIST_LEVEL];     /*节点*/

    void (*timeout_func)(void *parameter);          /**< timeout function */
    void            *parameter;                     /**< timeout function's parameter */

    rt_tick_t        init_tick;                         /**< 定时器实际需要延时的时间 */
    rt_tick_t        timeout_tick;                      /**< 定时器实际超时时的系统节拍数 */
};
typedef struct rt_timer *rt_timer_t;
```

**定时器启动函数**

核心实现算法是将定时器<u>按照延时时间做升序排列插入到系统定时器列表 rt_timer_list 中</u>

```c
/**
 * This function will start the timer
 *
 * @param timer the timer to be started
 *
 * @return the operation status, RT_EOK on OK, -RT_ERROR on error
 */
rt_err_t rt_timer_start(rt_timer_t timer)
{
    unsigned int row_lvl;
    rt_list_t *timer_list;
    register rt_base_t level;
    rt_list_t *row_head[RT_TIMER_SKIP_LIST_LEVEL];
    unsigned int tst_nr;
    static unsigned int random_nr;

    /* timer check */
    RT_ASSERT(timer != RT_NULL);

    /* stop timer firstly */
    level = rt_hw_interrupt_disable();
    /* remove timer from list */
    _rt_timer_remove(timer);
    /* change status of timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
    rt_hw_interrupt_enable(level);

    RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(timer->parent)));

    /*
     * get timeout tick,
     * the max timeout tick shall not great than RT_TICK_MAX/2
     * 最大超时刻度不应大于 RT_tick_max/2
     */
    RT_ASSERT(timer->init_tick < RT_TICK_MAX / 2);
    timer->timeout_tick = rt_tick_get() + timer->init_tick;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

#ifdef RT_USING_TIMER_SOFT
    if (timer->parent.flag & RT_TIMER_FLAG_SOFT_TIMER)
    {
        /* insert timer to soft timer list */
        timer_list = rt_soft_timer_list;
    }
    else
#endif
    {
        /* insert timer to system timer list */
        timer_list = rt_timer_list;
    }

    row_head[0]  = &timer_list[0];
    for (row_lvl = 0; row_lvl < RT_TIMER_SKIP_LIST_LEVEL; row_lvl++)
    {
        for (; row_head[row_lvl] != timer_list[row_lvl].prev;
             row_head[row_lvl]  = row_head[row_lvl]->next)
        {
            struct rt_timer *t;
            rt_list_t *p = row_head[row_lvl]->next;

            /* fix up the entry pointer 修复入口指针*/
            t = rt_list_entry(p, struct rt_timer, row[row_lvl]);

            /* If we have two timers that timeout at the same time, it's
             * preferred that the timer inserted early get called early.
             * So insert the new timer to the end the the some-timeout timer
             * list.
             */
            //比较两个定时器的 timeout_tick 值, 两个定时器的超时时间相同，则继续在定时器列表中寻找下一个节点
            if ((t->timeout_tick - timer->timeout_tick) == 0)
            {
                continue;
            }
            else if ((t->timeout_tick - timer->timeout_tick) < RT_TICK_MAX / 2)
            {
                break;
            }
        }
        if (row_lvl != RT_TIMER_SKIP_LIST_LEVEL - 1)
            row_head[row_lvl + 1] = row_head[row_lvl] + 1;
    }

    /* Interestingly, this super simple timer insert counter works very very
     * well on distributing the list height uniformly. By means of "very very
     * well", I mean it beats the randomness of timer->timeout_tick very easily
     * (actually, the timeout_tick is not random and easy to be attacked). */
    random_nr++;
    tst_nr = random_nr;
    
    /*将定时器插入到系统定时器列表*/
    rt_list_insert_after(row_head[RT_TIMER_SKIP_LIST_LEVEL - 1],      //双向列表根节点地址
                         &(timer->row[RT_TIMER_SKIP_LIST_LEVEL - 1]));//要被插入的节点的地址
    for (row_lvl = 2; row_lvl <= RT_TIMER_SKIP_LIST_LEVEL; row_lvl++)
    {
        if (!(tst_nr & RT_TIMER_SKIP_LIST_MASK))
            rt_list_insert_after(row_head[RT_TIMER_SKIP_LIST_LEVEL - row_lvl],
                                 &(timer->row[RT_TIMER_SKIP_LIST_LEVEL - row_lvl]));
        else
            break;
        /* Shift over the bits we have tested. Works well with 1 bit and 2
         * bits. */
        tst_nr >>= (RT_TIMER_SKIP_LIST_MASK + 1) >> 1;
    }
    /*设置定时器标志位为激活态*/
    timer->parent.flag |= RT_TIMER_FLAG_ACTIVATED;

    /* enable interrupt */
    rt_hw_interrupt_enable(level);

#ifdef RT_USING_TIMER_SOFT
    if (timer->parent.flag & RT_TIMER_FLAG_SOFT_TIMER)
    {
        /* check whether timer thread is ready */
        if ((timer_thread.stat & RT_THREAD_STAT_MASK) != RT_THREAD_READY)
        {
            /* resume timer thread to check soft timer */
            rt_thread_resume(&timer_thread);
            rt_schedule();
        }
    }
#endif

    return -RT_EOK;
}
RTM_EXPORT(rt_timer_start);

```

**定时器扫描函数**

查询定时器的延时是否到期，如果到期则让对应的线程就绪。

```c
1 /**
2 * 该函数用于扫描系统定时器列表，当有超时事件发生时
3 * 就调用对应的超时函数
4 *
5 * @note 该函数在操作系统定时器中断中被调用
6 */
7 void rt_timer_check(void)
8 {
9 struct rt_timer *t;
10 rt_tick_t current_tick;
11 register rt_base_t level;
12 
13 /* 获取系统时基计数器 rt_tick 的值 */
14 current_tick = rt_tick_get(); (1)
15 
16 /* 关中断 */
17 level = rt_hw_interrupt_disable(); (2)
18 
19 /* 系统定时器列表不为空，则扫描定时器列表 */ (3)
20 while (!rt_list_isempty(&rt_timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1]))
21 {
22 /* 获取第一个节点定时器的地址 */ (4)
23 t = rt_list_entry(rt_timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1].next,
24 struct rt_timer,
25 row[RT_TIMER_SKIP_LIST_LEVEL - 1]);
26 
27 if ((current_tick - t->timeout_tick) < RT_TICK_MAX / 2) (5)
28 {
29 /* 先将定时器从系统定时器列表移除 */
30 _rt_timer_remove(t); (6)
31 
32 /* 调用超时函数（调用超时函数 rt_thread_timeout，将线程就绪）*/
33 t->timeout_func(t->parameter); (7)
34 
35 /* 重新获取 rt_tick */
36 current_tick = rt_tick_get(); (8)
37 
38 /* 周期定时器 */ (9)
39 if ((t->parent.flag & RT_TIMER_FLAG_PERIODIC) &&
40 (t->parent.flag & RT_TIMER_FLAG_ACTIVATED))
41 {
42 /* 启动定时器 */
43 t->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
44 rt_timer_start(t);
45 }
46 /* 单次定时器 */ (10)
47 else
48 {
49 /* 停止定时器 */
50 t->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
51 }
52 }
53 else
54 break; (11)
55 }
56 
57 /* 开中断 */
58 rt_hw_interrupt_enable(level); (12)
59 }
```

**线程超时函数**

```c
1 /**
2 * 线程超时函数
3 * 当线程延时到期或者等待的资源可用或者超时时，该函数会被调用
4 *
5 * @param parameter 超时函数的形参
6 */
7 void rt_thread_timeout(void *parameter)
8 {
9 struct rt_thread *thread;
10 
11 thread = (struct rt_thread *)parameter;
12 
13 /* 设置错误码为超时 */ 
14 thread->error = -RT_ETIMEOUT;
15 
16 /* 将线程从挂起列表中删除 */ 
17 rt_list_remove(&(thread->tlist));
18 
19 /* 将线程插入到就绪列表 */ 
20 rt_schedule_insert_thread(thread);
21 
22 /* 系统调度 */ 
23 rt_schedule();
24 }
```

### 初始化一个线程

在线程初始化函数中，需要将自身内置的定时器初始化好。即调用 rt_timer_init（）函数。

```c
1 rt_err_t rt_thread_init( struct rt_thread *thread,
2 const char *name,
3 void (*entry)(void *parameter),
4 void *parameter,
5 void *stack_start,
6 rt_uint32_t stack_size,
7 rt_uint8_t priority)
8 {
9  /* 线程对象初始化 */
10 /* 线程结构体开头部分的成员就是 rt_object_t 类型 */
11 rt_object_init((rt_object_t)thread, RT_Object_Class_Thread, name);
12 rt_list_init(&(thread->tlist));
13 
14 thread->entry = (void *)entry;
15 thread->parameter = parameter;
16 
17 thread->stack_addr = stack_start;
18 thread->stack_size = stack_size;
19 
20 /* 初始化线程栈，并返回线程栈指针 */
21 thread->sp = (void *)rt_hw_stack_init( thread->entry,
22 thread->parameter,
23 (void *)((char *)thread->stack_addr + thread->stack_size - 4) );
24 
25 thread->init_priority = priority;
26 thread->current_priority = priority;
27 thread->number_mask = 0;
28 
29 /* 错误码和状态 */
30 thread->error = RT_EOK;
31 thread->stat = RT_THREAD_INIT;
32 
    
33 /* 初始化线程定时器 （注意）*/ 
34 rt_timer_init(&(thread->thread_timer), /* 静态定时器对象 */ 
35 thread->name, /* 定时器的名字，直接使用的是线程的名字 */ 
36 rt_thread_timeout, /* 超时函数 */ 
37 thread, /* 超时函数形参 */ 
38 0, /* 延时时间 */ 
39 RT_TIMER_FLAG_ONE_SHOT); /* 定时器的标志 */ 
40 
41 return RT_EOK;
42 }
```



函数开头的“_rt”表示该函数是一个==内部函数==



### 消息队列

队列又称消息队列，是一种常用于<u>线程间通信的数据结构</u>，队列可以在线程与线程间、中断和线程间传送信息，实现了线程接收来自其他线程或中断的不固定长度的消息，并根据不同的接口选择传递消息是否存放在线程自己的空间。线程能够从队列里面读取消息，当队列中的消息是空时，挂起读取线程，用户还可以指定挂起的线程时间 timeout；当队列中有新消息时，挂起的读取线程被唤醒并处理新消息，消息队列是一种异步的通信方式。

RT-Thread 中使用队列数据结构实现线程异步通信工作，具有如下特性：

- 消息支持先进先出方式排队与优先级排队方式，支持异步读写工作方式。

- 读队列支持超时机制。

- 支持发送紧急消息，这里的紧急消息是往队列头发送消息。

- 可以允许不同长度（不超过队列节点最大值）的任意类型消息。

- 一个线程能够从任意一个消息队列接收和发送消息。

- 多个线程能够从同一个消息队列接收和发送消息。

- 当队列使用结束后，需要通过删除队列操作释放内存函数回收。

    

#### 什么是队列句柄？

​		说白了就是消息队列的对象实例。通过下面的消息队列控制块的类可以进行创建实例，可以得到对象句柄

#### 队列模式 (2种) 

​		使用 `RT_IPC_FLAG_PRIO` 优先级 flag 创建的 ==IPC 对象==，在多个线 程 等 待 消 息 队 列 资 源 时 ， 将 由 优 先 级 高 的 线 程 优 先 获 得 资 源 。 而 使 用`RT_IPC_FLAG_FIFO` 先进先出 flag 创建的 IPC 对象，在多个线程等待消息队列资源时，将按照先来先得的顺序获得资源。`RT_IPC_FLAG_PRIO` 与 `RT_IPC_FLAG_FIFO` 均在 rtdef.h中有定义

#### 消息队列的阻塞机制

​		阻塞机制：就是不干完不准回来。

​        非阻塞机制：就是你先干，我现在看看有其他的事没有，完了告诉我一声。

​		

**消息队列控制块**

```c
struct rt_messagequeue
{
    struct rt_ipc_object parent;                        /**< inherit from ipc_object */

    void                *msg_pool;                      /**< start address of message queue */

    rt_uint16_t          msg_size;                      /**< message size of each message */
    rt_uint16_t          max_msgs;                      /**< max number of messages */

    rt_uint16_t          entry;                         /**< index of messages in the queue */

    void                *msg_queue_head;                /**< list head */
    void                *msg_queue_tail;                /**< list tail */
    void                *msg_queue_free;                /**< pointer indicated the free node of queue */
};
typedef struct rt_messagequeue *rt_mq_t;
```

使用队列模块的典型流程如下：

- 创建消息队列 rt_mq_create。

- 写队列操作函数 rt_mq_send。

- 读队列操作函数 rt_mq_recv。

- 删除队列 rt_mq_delete。

    

#### **创建队列**

```c
/**
 * This function will create a message queue object from system resource
 *
 * @param name the name of message queue
 * @param msg_size the size of message
 * @param max_msgs the maximum number of message in queue
 * @param flag the flag of message queue
 *
 * @return the created message queue, RT_NULL on error happen
 */
rt_mq_t rt_mq_create(const char *name,
                     rt_size_t   msg_size,
                     rt_size_t   max_msgs,
                     rt_uint8_t  flag)
{
    struct rt_messagequeue *mq;
    struct rt_mq_message *head;
    register rt_base_t temp;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* allocate object 分配对象 */
    mq = (rt_mq_t)rt_object_allocate(RT_Object_Class_MessageQueue, name);
    if (mq == RT_NULL)
        return mq;

    /* set parent */
    mq->parent.parent.flag = flag;

    /* init ipc object 初始化消息队列内核对象 */
    rt_ipc_object_init(&(mq->parent));

    /* init message queue */

    /* get correct message size */
    mq->msg_size = RT_ALIGN(msg_size, RT_ALIGN_SIZE);
    mq->max_msgs = max_msgs;

    /* allocate message pool 分配消息内存池 */
    mq->msg_pool = RT_KERNEL_MALLOC((mq->msg_size + sizeof(struct rt_mq_message)) * mq->max_msgs);
    if (mq->msg_pool == RT_NULL)
    {
        rt_mq_delete(mq);      //消息队列删除函数
        return RT_NULL;
    }

    /* init message list 初始化消息队列头尾链表 */
    mq->msg_queue_head = RT_NULL;
    mq->msg_queue_tail = RT_NULL;

    /* init message empty list 初始化消息队列空闲链表 */
    mq->msg_queue_free = RT_NULL;
    for (temp = 0; temp < mq->max_msgs; temp ++)
    {
        head = (struct rt_mq_message *)((rt_uint8_t *)mq->msg_pool +
                                        temp * (mq->msg_size + sizeof(struct rt_mq_message)));
        head->next = mq->msg_queue_free;
        mq->msg_queue_free = head;
    }

    /* the initial entry is zero */
    mq->entry = 0;

    return mq;
}
RTM_EXPORT(rt_mq_create);
```

#### 消息队列发送消息函数

```c
1 rt_err_t rt_mq_send(rt_mq_t mq, void *buffer, rt_size_t size) (1)
2 {
3 register rt_ubase_t temp;
4 struct rt_mq_message *msg;
5 
6 RT_ASSERT(mq != RT_NULL); (2)
7 RT_ASSERT(buffer != RT_NULL);
8 RT_ASSERT(size != 0);
9 
10 /* 判断消息的大小*/
11 if (size > mq->msg_size) (3)
12 return -RT_ERROR;
13 
14 RT_OBJECT_HOOK_CALL(rt_object_put_hook, (&(mq->parent.parent)));
15 
16 /* 关中断 */
17 temp = rt_hw_interrupt_disable();
18 
19 /* 获取一个空闲链表，必须有一个空闲链表项*/
20 msg = (struct rt_mq_message *)mq->msg_queue_free; (4)
21 /* 消息队列满 */
22 if (msg == RT_NULL) {
23 /* 开中断 */
24 rt_hw_interrupt_enable(temp);
25 
26 return -RT_EFULL;
27 }
28 /* 移动空闲链表指针 */
29 mq->msg_queue_free = msg->next; (5)
30 
31 /* 开中断 */
32 rt_hw_interrupt_enable(temp);
33 
34 /* 这个消息是新的链表尾部，其下一个指针为 RT_NULL /
35 msg->next = RT_NULL;
36 /* 拷贝数据 */
37 rt_memcpy(msg + 1, buffer, size); (6)
38 
39 /* 关中断 */
40 temp = rt_hw_interrupt_disable();
41 /* 将消息挂载到消息队列尾部 */
42 if (mq->msg_queue_tail != RT_NULL) { (7)
43 /* 如果已经存在消息队列尾部链表 */
44 ((struct rt_mq_message *)mq->msg_queue_tail)->next = msg;
45 }
46 
47 /* 设置新的消息队列尾部链表指针 */
48 mq->msg_queue_tail = msg; (8)
49 /* 如果头部链表是空的，设置头部链表指针 */
50 if (mq->msg_queue_head == RT_NULL) (9)
51 mq->msg_queue_head = msg;
52 
53 /* 增加消息数量记录 */
54 mq->entry ++; (10)
55 
56 /* 恢复挂起线程 */
57 if (!rt_list_isempty(&mq->parent.suspend_thread)) { (11)
58 rt_ipc_list_resume(&(mq->parent.suspend_thread));
59 
60 /* 开中断 */
61 rt_hw_interrupt_enable(temp);
62 
63 rt_schedule(); (12)
64 
65 	return RT_EOK;
66 	}
67 
68 /* 开中断 */
69 rt_hw_interrupt_enable(temp);
70 
71 return RT_EOK;
72 }
73 RTM_EXPORT(rt_mq_send);
```



#### 消息队列接收消息函数

```c
1 rt_err_t rt_mq_recv(rt_mq_t mq, (1)
2 void *buffer, (2)
3 rt_size_t size, (3)
4 rt_int32_t timeout) (4)
5 {
6 struct rt_thread *thread;
7 register rt_ubase_t temp;
8 struct rt_mq_message *msg;
9 rt_uint32_t tick_delta;
10 
11 RT_ASSERT(mq != RT_NULL);
12 RT_ASSERT(buffer != RT_NULL);
13 RT_ASSERT(size != 0); (5)
14 
15 
16 tick_delta = 0;
17 /* 获取当前的线程 */
18 thread = rt_thread_self(); (6)
19 RT_OBJECT_HOOK_CALL(rt_object_trytake_hook, (&(mq->parent.parent)));
20 
21 /* 关中断 */
22 temp = rt_hw_interrupt_disable();
23 
24 /* 非阻塞情况 */
25 if (mq->entry == 0 && timeout == 0) { (7)
26 rt_hw_interrupt_enable(temp);
27 
28 return -RT_ETIMEOUT;
29 }
30 
31 /* 消息队列为空 */
32 while (mq->entry == 0) { (8)
33 RT_DEBUG_IN_THREAD_CONTEXT;
34 
35 /* 重置线程中的错误号 */
36 thread->error = RT_EOK; (9)
37 
38 /* 不等待 */
39 if (timeout == 0) {
40 /* 开中断 */
41 rt_hw_interrupt_enable(temp);
42 
43 thread->error = -RT_ETIMEOUT;
44 
45 return -RT_ETIMEOUT;
46 }
47 
48 /* 挂起当前线程 */
49 rt_ipc_list_suspend(&(mq->parent.suspend_thread), (10)
50 thread,
51 mq->parent.parent.flag);
52 
53 /* 有等待时间，启动线程计时器 */
54 if (timeout > 0) { (11)
55 /* 获取 systick 定时器时间 */
56 tick_delta = rt_tick_get();
57 
58 RT_DEBUG_LOG(RT_DEBUG_IPC, ("set thread:%s to timer list\n",
59 thread->name));
60 
61 /* 重置线程计时器的超时并启动它 */
62 rt_timer_control(&(thread->thread_timer), (12)
63 RT_TIMER_CTRL_SET_TIME,
64 &timeout);
65 rt_timer_start(&(thread->thread_timer));
66 }
67 
68 /* 开中断 */
69 rt_hw_interrupt_enable(temp);
70 
71 /* 发起线程调度 */
72 rt_schedule(); (13)
73 
74 
75 if (thread->error != RT_EOK) {
76 /* 返回错误 */
77 return thread->error;
78 }
79 
80 /* 关中断 */
81 temp = rt_hw_interrupt_disable();
82 
83 /* 如果它不是永远等待，然后重新计算超时滴答 */
84 if (timeout > 0) {
85 tick_delta = rt_tick_get() - tick_delta;
86 timeout -= tick_delta;
87 if (timeout < 0)
88 timeout = 0;
89 }
90 }
91 
92 /* 获取消息 */
93 msg = (struct rt_mq_message *)mq->msg_queue_head; (14)
94 
95 /* 移动消息队列头链表指针 */
96 mq->msg_queue_head = msg->next; (15)
97 /* 到达队列尾部，设置为 NULL */
98 if (mq->msg_queue_tail == msg) (16)
99 mq->msg_queue_tail = RT_NULL;
100 
101 /* 记录消息个数，自减一 */
102 mq->entry --; (17)
103 
104 /* 开中断 */
105 rt_hw_interrupt_enable(temp);
106 
107 /* 拷贝消息到指定存储地址 */
108 rt_memcpy(buffer, msg + 1, size > mq->msg_size ? mq->msg_size : size); (18)
109 
110 /* 关中断 */
111 temp = rt_hw_interrupt_disable();
112 /*移到空闲链表 */
113 msg->next = (struct rt_mq_message *)mq->msg_queue_free; (19)
114 mq->msg_queue_free = msg;
115 /* 开中断 */
116 rt_hw_interrupt_enable(temp);
117 
118 RT_OBJECT_HOOK_CALL(rt_object_take_hook, (&(mq->parent.parent)));
119 
120 return RT_EOK;
121 }
122 RTM_EXPORT(rt_mq_recv);
```



当且仅当空闲消息链表上有可用的空闲消息块时，发送者才能成功发送消息；当空闲消息链表上无可用消息块，说明消息队列已满，此时，发送消息的的线程或者中断程序会收到一个错误码（-RT_EFULL）

#### 消息队列使用注意事项

在使用 RT-Thread 提供的消息队列函数的时候，需要了解以下几点：

1. 使用 `rt_mq_recv()、rt_mq_send()、rt_mq_delete()`等这些函数之前应先创建消息队列，并根据队列句柄进行操作。

2. 队列读取采用的是先进先出（FIFO）模式，会首先读取出首先存储在队列中的数据。当然也有例外，RT-hread 给我们提供了另一个函数，可以发送紧急消息的，那么读取的时候就会读取到紧急消息的数据。

3. 必须要我们定义一个存储读取出来的数据的地方，并且把存储数据的起始地址传递给 rt_mq_recv()函数，否则，将发生地址非法的错误。

4. 接收消息队列中的消息是拷贝的方式，读取消息时候定义的地址必须保证能存放下即将读取消息的大小。



### 信号量（类似于一种标志）

​		信号量（Semaphore）是一种实现线程间通信的机制，==实现线程之间同步或临界资源的互斥访问==，常用于协助一组相互竞争的线程来访问临界资源。**在多线程系统中，各线程之间需要同步或互斥实现临界资源的保护**，信号量功能可以为用户提供这方面的支持。

#### 二值信号量的应用场景

​		某个线程需要等待一个标记，那么线程可以在轮询中查询这个标记有没有被置位，这样子做，就会很消耗 CPU 资源，其实根本不需要在轮询中查询这个标记，只需要使用二值信号量即可，当二值信号量没有的时候，线程进入阻塞态等待二值信号量到来即可，当得到了这个信号量（标记）之后，在进行线程的处理即可，这样子么就不会消耗太多资源了，而且实时响应也是最快的。

#### 计数型信号量的应用场景

​		计数型信号量与二值信号量其实都是差不多的，一样用于资源保护，**不过计数信号量则允许多个线程获取信号量访问共享资源**，但会限制线程的最大数目。访问的线程数达到信号量可支持的最大数目时，会阻塞其他试图获取该信号量的线程，直到有线程释放了信号量。



**信号量的结构体**

信号量属于内核对象，也会在自身结构体里面包含一个内核对象类型的成员，通过这个成员可以将信号量挂到系统对象容器里面。==rt_semaphore 对象从 rt_ipc_object 中派生，由 IPC 容器管理。==

```c
struct rt_semaphore
{
	struct rt_ipc_object parent;    /**< 继承自 ipc_object 类*/
	rt_uint16_t value;              /**< 信号量的值，最大为 65535 */
};
typedef struct rt_semaphore *rt_sem_t;
```

**创建信号量**

```c
/**
 * This function will create a semaphore from system resource
 *
 * @param name the name of semaphore
 * @param value the init value of semaphore
 * @param flag the flag of semaphore
 *
 * @return the created semaphore, RT_NULL on error happen
 *
 * @see rt_sem_init
 */
rt_sem_t rt_sem_create(const char *name, rt_uint32_t value, rt_uint8_t flag)
{
    rt_sem_t sem;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* allocate object 分配内核对象：信号量 */
    sem = (rt_sem_t)rt_object_allocate(RT_Object_Class_Semaphore, name);
    if (sem == RT_NULL)
        return sem;

    /* init ipc object 初始化信号量对象*/
    rt_ipc_object_init(&(sem->parent));

    /* set init value 设置可用信号量的值*/
    sem->value = value;

    /* set parent 设置信号量模式（和队列模式一样也有2种）*/
    sem->parent.parent.flag = flag;

    return sem;
}
RTM_EXPORT(rt_sem_create);
```



当线程完成资源的访问后，应尽快释放它持有的信号量，使得其他线程能获得该信号量。

​		线程通过获取信号量来获得信号量资源，**当信号量值大于零时，线程将获得信号量**，并且相应的信号量值都会减 1；**如果信号量的值等于零，那么说明当前信号量资源不可用**，==（例子里面，在释放的时候会将这个信号量的值加1）==获取该信号量的线程将根据 time 参数的情况选择直接返回、或挂起等待一段时间、或永久等待，直到其他线程或中断释放该信号量。



### 互斥量

​		任意时刻互斥量的状态只有两种，**开锁或闭锁**。当互斥量被线程持有时，该互斥量处于闭锁状态，这个线程获得互斥量的所有权。当该线程释放这个互斥量时，该互斥量处于开锁状态，线程失去该互斥量的所有权。当一个线程持有互斥量时，其他线程将不能再对该互斥量进行开锁或持有。

互斥量与二值信号量最大的不同是：互斥量具有优先级继承机制，而信号量没有。

#### 互斥量的优先级继承机制

 		在 RT-Thread 操作系统中为了降低优先级翻转问题利用了优先级继承算法。优先级继承算法是指，<u>暂时提高某个占有某种资源的低优先级线程的优先级，使之与在所有等待该资源的线程中优先级最高那个线程的优先级相等，而当这个低优先级线程执行完毕释放该资源时，优先级重新回到初始设定值</u>。因此，继承优先级的线程避免了系统资源被任何中间优先级的线程抢占。

#### 互斥量的作用机制

​		用互斥量处理不同线程对临界资源的同步访问时，==线程想要获得互斥量才能进行资源访问==，如果一旦有线程成功获得了互斥量，则互斥量立即变为闭锁状态，此时其他线程会因为获取不到互斥量而不能访问这个资源，线程会根据用户自定义的等待时间进行等待，直到互斥量被持有的线程释放后，其他线程才能获取互斥量从而得以访问该临界资源，此时互斥量再次上锁，如此一来就可以确保每个时刻只有一个线程正在访问这个临界资源，保证了临界资源操作的安全性。

![](E:\github\Project_Demo\RT_Thread_Demo\图片\互斥量运作机制.png)

   ==如果资源被占用的时候，无论是什么优先级的线程想要使用该资源都会被阻塞。==

#### 互斥量的释放

​		使用该函数接口时，只有已持有互斥量所有权的线程才能释放它，每释放一次该互斥量，它的持有计数就减 1。当该互斥量的持有计数为零时（即持有线程已经释放所有的持有操作），互斥量则变为开锁状态，等待在该互斥量上的线程将被唤醒。如果线程的优先级被互斥量的优先级翻转机制临时提升，那么当互斥量被释放后，线程的优先级将恢复为原本设定的优先级。

#### 互斥量使用的注意事项

1.  两个线程不能对同时持有同一个互斥量。如果某线程对已被持有的互斥量进行获取，则该线程会被挂起，直到持有该互斥量的线程将互斥量释放成功，其他线程才能申请这个互斥量。
2. 互斥量不能在中断服务程序中使用。
3. RT-Thread 作为实时操作系统需要保证线程调度的实时性，尽量避免线程的长时间阻塞，因此在获得互斥量之后，应该尽快释放互斥量。
4. 持有互斥量的过程中，不得再调用 rt_thread_control() 等函数接口更改持有互斥量线程的优先级。



### 事件

​		事件是一种实现线程间通信的机制，主要用于实现**线程间的同步**，但事件通信只能是事件类型的通信，无数据传输。<u>与信号量不同的是，它可以实现一对多，多对多的同步。</u>即一个线程可以等待多个事件的发生：可以是任意一个事件发生时唤醒线程进行事件处理；也可以是几个事件都发生后才唤醒线程进行事件处理。同样，事件也可以是多个线程同步多个事件。



事件可以理解成不同的==标志==



RT-Thread 提供的事件具有如下特点：

-  事件只与线程相关联，事件相互独立，一个 32 位的事件集合（set 变量），用于标识该线程发生的事件类型，其中每一位表示一种事件类型（0 表示该事件类型未发生、1 表示该事件类型已经发生），一共 32 种事件类型。
-  事件仅用于同步，不提供数据传输功能。
- 事件无排队性，即多次向线程发送同一事件(如果线程还未来得及读走)，等效于只发送一次。
- 允许多个线程对同一事件进行读写操作。
- 支持事件等待超时机制。	





### 软件定时器

​		软件定时器是由操作系统提供的一类系统接口，它构建在硬件定时器基础之上，使系统能够提供不受硬件定时器资源限制的定时器服务，它实现的功能与硬件定时器也是类似的。

#### 创建软件定时器

```c
/**
 * This function will create a timer
 *
 * @param name the name of timer
 * @param timeout the timeout function
 * @param parameter the parameter of timeout function
 * @param time the tick of timer
 * @param flag the flag of timer
 *
 * @return the created timer object
 */
rt_timer_t rt_timer_create(const char *name,
                           void (*timeout)(void *parameter),
                           void       *parameter,
                           rt_tick_t   time,
                           rt_uint8_t  flag)
{
    struct rt_timer *timer;

    /* allocate a object */
    timer = (struct rt_timer *)rt_object_allocate(RT_Object_Class_Timer, name);
    if (timer == RT_NULL)
    {
        return RT_NULL;
    }

    /*定时器初始化*/
    _rt_timer_init(timer, timeout, parameter, time, flag);

    return timer;
}
RTM_EXPORT(rt_timer_create);
```



### 邮箱

​		邮箱在操作系统中是一种常用的 IPC 通信方式，邮箱可以在线程与线程之间。中断与线程之间进行消息的传递，此外，邮箱相比于信号量与消息队列来说，其开销更低，效率更高，所以常用来做线程与线程、中断与线程间的通信。邮箱中的每一封邮件只能容纳固定的 4 字节内容（STM32 是 32 位处理系统，一个指针的大小即为 4 个字节，所以一封邮件恰好能够容纳一个指针），当需要在线程间传递比较大的消息时，可以把指向一个缓冲区的指针作为邮件发送到邮箱中。

​		线程能够从邮箱里面读取邮件消息，当邮箱中的邮件是空时，根据用户自定义的阻塞时间决定是否挂起读取线程；当邮箱中有新邮件时，挂起的读取线程被唤醒，邮箱也是一种异步的通信方式。



RT-Thread 中使用邮箱实现线程异步通信工作，具有如下特性：

- 邮件支持先进先出方式排队与优先级排队方式，支持异步读写工作方式。
- 发送与接收邮件均支持超时机制。
- 一个线程能够从任意一个消息队列接收和发送邮件。
- 多个线程能够向同一个邮箱发送邮件和从中接收邮件。
- 邮箱中的每一封邮件只能容纳固定的 4 字节内容（可以存放地址）。
- 当队列使用结束后，需要通过删除邮箱以释放内存。







### 内存管理



### 中断管理



### 双向链表































