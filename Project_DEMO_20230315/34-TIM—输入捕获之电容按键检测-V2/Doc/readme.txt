/*********************************************************************************************/

【*】 程序简介 
-工程名称：TIM—输入捕获（电容按键）
-实验平台: 野火STM32 霸道 开发板
-MDK版本：5.16
-ST固件库版本：3.5.0

【 ！】功能简介：
使用定时器实现 电容按键 功能

学习目的：学会定时器输入捕获功能，了解电容按键的原理

【 ！！】注意事项：
使用电容按键需要把电容按键上方的J78跳线帽连接起来。(出厂默认已连接)
 
【 ！】实验操作：
下载程序到开发板，复位，触摸电容按键蜂鸣器会响。

/*********************************************************************************************/

【*】 引脚分配

电容按键：
电容按键的 金属板引出与定时器的通道相连。
	金属板<--->TPAD1
	

/*********************************************************************************************/
【*】 联系我们

-野火官网  :https://embedfire.com
-野火论坛  :http://www.firebbs.cn
-野火商城  :https://yehuosm.tmall.com/
-野火资料下载中心：http://doc.embedfire.com/products/link

/*********************************************************************************************/