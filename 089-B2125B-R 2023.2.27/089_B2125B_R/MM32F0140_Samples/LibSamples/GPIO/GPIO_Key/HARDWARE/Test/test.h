#ifndef __TEST_H__
#define __TEST_H__


extern volatile unsigned char  gcTest_state;
extern volatile unsigned char  gcTestRfXamsCnt;
extern volatile unsigned int Testled_horseCnt;	
extern volatile unsigned int Testled_BlinkCnt;	
extern volatile unsigned int giTestTimeSecCnt;  
extern volatile unsigned int giTestTimeMinCnt;  
extern volatile unsigned char gcTestTxRf_flag; 

extern void  Is_IntoTest(void);
extern void  Test_func(void);
extern void Testled_scan(void);
extern void Sleep_Process(void);

#endif




