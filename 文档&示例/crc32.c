#include <stdio.h>
#include <stdint.h>

// 多项式除数 0xEDB88320
#define POLY 0xEDB88320UL


// 计算 CRC32 校验和
uint32_t crc32(const void *data, size_t len)
{
    const uint8_t *bytes = data;
    uint32_t crc = 0xFFFFFFFFUL;

    // 循环处理每个字节
    for (size_t i = 0; i < len; i++)
    {
    	crc ^= bytes[i];        // 把当前字节与 crc 的低 8 位进行异或操作

        // 处理当前字节的 8 位，每次处理一位
        for (int j = 0; j < 8; j++)
        {
            if (crc & 1) 
			{      // 如果 crc 的最低位为 1，则右移并与多项式除数进行异或操作
              crc = (crc >> 1) ^ POLY;
            } 
			else 
			{            // 否则，只右移一个比特位
              crc >>= 1;
			}
        }
	}

return ~crc;                // 取反操作得到最终结果

}

int main()
{
    // 测试数据
    char data[] = "123456789";
    size_t len = sizeof(data) - 1;  // 注意，字符数组中包含了一个字符串末尾的 NULL 结束符

    // 计算 CRC32 校验和
    uint32_t crc = crc32(data, len);

    // 输出结果
    printf("CRC32: 0x%08X\n", crc);

	return 0;

}
