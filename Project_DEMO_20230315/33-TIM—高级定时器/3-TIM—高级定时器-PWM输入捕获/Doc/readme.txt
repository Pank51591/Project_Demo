/*********************************************************************************************/

【*】 程序简介 
-工程名称：TIM—高级控制定时器PWM输入捕获
-实验平台: 野火STM32 霸道 开发板
-MDK版本：5.16
-ST固件库版本：3.5.0

【 ！】功能简介：
使用STM32的高级控制定时器PWM输入捕获模式，测量PWM波形频率和周期。
学习目的：学会使用高级控制定时器输入捕获功能，以及通用定时器PWM输出功能。

【 ！】实验操作：
电脑端使用串口调试助手，选择电脑与STM32相连的COM口，设置为115200-N-8-1，
PWM输出引脚和高级控制定时器的输入捕获引脚。


/*********************************************************************************************/

【*】 引脚分配

串口(TTL-USB TO USART)：
CH340的收发引脚与STM32的发收引脚相连。
	RX<--->PA9
	TX<--->PA10

高级控制定时器捕获输入引脚：

    KEY1 <---> PA0
	


/*********************************************************************************************/
【*】 联系我们

-野火官网  :https://embedfire.com
-野火论坛  :http://www.firebbs.cn
-野火商城  :https://yehuosm.tmall.com/
-野火资料下载中心：http://doc.embedfire.com/products/link

/*********************************************************************************************/