#ifndef ENCRYPT_H
#define ENCRYPT_H



INT8U DataSum(INT8U *pdat,INT8U len);//�ۼӺ�
#define Coding(tcp,Encrypt,len) Decode(tcp,Encrypt,len)//����
void Decode(INT8U *pdat,INT8U Encrypt,INT8U len);//����


#endif

