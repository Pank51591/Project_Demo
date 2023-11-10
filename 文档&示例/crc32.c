#include <stdio.h>
#include <stdint.h>

// ����ʽ���� 0xEDB88320
#define POLY 0xEDB88320UL


// ���� CRC32 У���
uint32_t crc32(const void *data, size_t len)
{
    const uint8_t *bytes = data;
    uint32_t crc = 0xFFFFFFFFUL;

    // ѭ������ÿ���ֽ�
    for (size_t i = 0; i < len; i++)
    {
    	crc ^= bytes[i];        // �ѵ�ǰ�ֽ��� crc �ĵ� 8 λ����������

        // ����ǰ�ֽڵ� 8 λ��ÿ�δ���һλ
        for (int j = 0; j < 8; j++)
        {
            if (crc & 1) 
			{      // ��� crc �����λΪ 1�������Ʋ������ʽ��������������
              crc = (crc >> 1) ^ POLY;
            } 
			else 
			{            // ����ֻ����һ������λ
              crc >>= 1;
			}
        }
	}

return ~crc;                // ȡ�������õ����ս��

}

int main()
{
    // ��������
    char data[] = "123456789";
    size_t len = sizeof(data) - 1;  // ע�⣬�ַ������а�����һ���ַ���ĩβ�� NULL ������

    // ���� CRC32 У���
    uint32_t crc = crc32(data, len);

    // ������
    printf("CRC32: 0x%08X\n", crc);

	return 0;

}
