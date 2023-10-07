# RT-Thread 学习笔记

RT-Thread 采用内核对象管理系统来访问 / 管理所有内核对象，内核对象包含了内核中绝大部分设施，这些内核对象可以是静态分配的静态对象，也可以是从系统内存堆中分配的动态对象。

通过这种内核对象的设计方式，RT-Thread 做到了不依赖于具体的内存分配方式，系统的灵活性得到极大的提高。



### RT-Thread 常用的文件有哪些？

| 文件名     | 介绍                                                         |
| ---------- | :----------------------------------------------------------- |
| rtconfig.h | rtconfig.h 是 RT-Thread 功能的配置头文件，里面定义了很多宏，通过这些宏定义，我们可以裁剪 RT-Thread 的功能。 |
| board.c    | board.c 是直接从 RT-Thread/3.0.3/bsp 文件夹下面拷贝过来的，里面存放的是与硬件相关的初始化函数 |
| rthw.h     | rthw.h 是处理器相关                                          |
|            |                                                              |
|            |                                                              |

### RT-Thread官方文件夹包含的内容

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

容器是一个全部变量的数组，数据类型为 ==struct  rt_object_information==，这是一个结构体类型，包含对象的三个信息，分别为对象类型、对象列表节点头和对象的大小。



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
    char        name[RT_NAME_MAX];    /* 对象的名字 */
    rt_uint8_t  type;                 /* 对象类型 */
    rt_uint8_t  flags;                /* 对象的状态 */
    rt_list_t   list;                 /* 对象的列表节点 */
    

	rt_list_t   tlist;                /* 线程链表节点 */
	
	void        *sp;	              /* 线程栈指针 */
	void        *entry;	              /* 线程入口地址 */
	void        *parameter;	          /* 线程形参 */	
	void        *stack_addr;          /* 线程起始地址 */
	rt_uint32_t stack_size;           /* 线程栈大小，单位为字节 */

    rt_ubase_t remaining_tick;       /* 用于实现阻塞延时 */
};
typedef struct rt_thread *rt_thread_t;
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

