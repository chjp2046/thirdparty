#ifndef THIRDPARTY_LITE_CRC_FASTCRC_H_
#define THIRDPARTY_LITE_CRC_FASTCRC_H_

#include "common/base/stdint.h"

namespace lite_crc {

// FastCRC32���Զ��ַ��������ۼӼ���crc���ڱ�������Ը��ļ�����o2�Ż�
// old_crc�ֽ�Ϊ4��byte
// |---byte0----|---byte1----|---byte2----|---byte3----|
// byte0��¼�ַ����ĵ�0��3��6,......3n���ַ���crc8�ۼӽ��
// byte1��¼�ַ����ĵ�1��4��7,......3n+1���ַ�crc8�ۼӽ��
// byte2�����ַ����ĵ�2��5��8,......3n+2���ַ�crc8�ۼӽ��
// byte3�ĸ�ʽΪ|--bit0--|--bit1--|--bit2--|--bit3--|--bit4--|--bit5--|--bit6--|--bit7--|
// bit0-bit1������¼�´�Ҫ�ۼӵ���ʼλ��
// bit2-bit4������¼��ǰCRC32�İ汾��
//  ĳЩӦ�ÿ�����Ҫһ����������Чhashֵ����ȵ�����ֵ����������Ĭ��ʹ�õİ汾����000��
//  �ͰѰ汾��111����Ϊ������;�������Ѱ汾���ֶ�����Ϊ111���Ͳ������Ч��hashֵ��ͻ��
// bit5-bit7����
uint32_t FastCRC(uint32_t old_crc, const unsigned char* dat, uint32_t len);

} // namespace fast_crc

#endif // THIRDPARTY_LITE_CRC_FASTCRC_H_

