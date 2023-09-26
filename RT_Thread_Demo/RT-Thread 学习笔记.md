

RT-Thread 采用内核对象管理系统来访问 / 管理所有内核对象，内核对象包含了内核中绝大部分设施，这些内核对象可以是静态分配的静态对象，也可以是从系统内存堆中分配的动态对象。

通过这种内核对象的设计方式，RT-Thread 做到了不依赖于具体的内存分配方式，系统的灵活性得到极大的提高。



### 什么是容器

容器是一个全部变量的数组，数据类型为 struct  rt_object_information，这是一个结构体类型，包含对象的三个信息，分别为对象类型、对象列表节点头和对象的大小。



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


};
typedef struct rt_thread *rt_thread_t;
```


