#include "thirdparty/lite_crc/fast_crc.h"

namespace lite_crc {

// 8-bit table
static unsigned char local_crc8_table[256] = {
    0  , 7  , 14 , 9  , 28 , 27 , 18 , 21 ,
    56 , 63 , 54 , 49 , 36 , 35 , 42 , 45 ,
    112, 119, 126, 121, 108, 107, 98 , 101,
    72 , 79 , 70 , 65 , 84 , 83 , 90 , 93 ,
    224, 231, 238, 233, 252, 251, 242, 245,
    216, 223, 214, 209, 196, 195, 202, 205,
    144, 151, 158, 153, 140, 139, 130, 133,
    168, 175, 166, 161, 180, 179, 186, 189,
    199, 192, 201, 206, 219, 220, 213, 210,
    255, 248, 241, 246, 227, 228, 237, 234,
    183, 176, 185, 190, 171, 172, 165, 162,
    143, 136, 129, 134, 147, 148, 157, 154,
    39 , 32 , 41 , 46 , 59 , 60 , 53 , 50 ,
    31 , 24 , 17 , 22 , 3  , 4  , 13 , 10 ,
    87 , 80 , 89 , 94 , 75 , 76 , 69 , 66 ,
    111, 104, 97 , 102, 115, 116, 125, 122,
    137, 142, 135, 128, 149, 146, 155, 156,
    177, 182, 191, 184, 173, 170, 163, 164,
    249, 254, 247, 240, 229, 226, 235, 236,
    193, 198, 207, 200, 221, 218, 211, 212,
    105, 110, 103, 96 , 117, 114, 123, 124,
    81 , 86 , 95 , 88 , 77 , 74 , 67 , 68 ,
    25 , 30 , 23 , 16 , 5  , 2  , 11 , 12 ,
    33 , 38 , 47 , 40 , 61 , 58 , 51 , 52 ,
    78 , 73 , 64 , 71 , 82 , 85 , 92 , 91 ,
    118, 113, 120, 127, 106, 109, 100, 99 ,
    62 , 57 , 48 , 55 , 34 , 37 , 44 , 43 ,
    6  , 1  , 8  , 15 , 26 , 29 , 20 , 19 ,
    174, 169, 160, 167, 178, 181, 188, 187,
    150, 145, 152, 159, 138, 141, 132, 131,
    222, 217, 208, 215, 194, 197, 204, 203,
    230, 225, 232, 239, 250, 253, 244, 243
};

#define CRCSetPos(byte4,pos) byte4 = ((byte4) & 0xfc) | (pos)
#define CRCGetpos(byte4) ((byte4) & 0x03)

#define CRCSetVer(byte4,ver) byte4 = ((byte4) & 0xe3) | ((ver)<<2)
#define CRCGetVer(byte4) (((byte4) & 0x1c) >> 2)

#define CRCSetReserve(byte4,res) byte4 = ((byte4) & 0x1f) | ((res) << 5)
#define CRCGetReserve(byte4) (((byte4) & 0xe0) >> 5)

// CRC32_internal只能由FastCRC32调用，用户不可以调用
static uint32_t CRC_internal(uint32_t old_crc, const unsigned char* dat, uint32_t len) {
    if(len == 0)
        return old_crc;

    uint32_t crc = old_crc;
    unsigned char* p = (unsigned char*)&crc;

    uint32_t count = len / 3;
    const unsigned char* d = dat;
    for(uint32_t u = 0; u < count; ++u) {
        p[0] = local_crc8_table[p[0] ^ d[0]];
        p[1] = local_crc8_table[p[1] ^ d[1]];
        p[2] = local_crc8_table[p[2] ^ d[2]];

        d +=3;
    }

    uint32_t remainder = len % 3;
    for (uint32_t i = 0; remainder > 0 && i < remainder; ++i) {
        p[i] = local_crc8_table[p[i] ^ d[i]];
    }

    CRCSetPos(p[3],remainder);

    return crc;
}

uint32_t FastCRC(uint32_t old_crc, const unsigned char* dat, uint32_t len) {
    if (len == 0) {
        return old_crc;
    }

    uint32_t crc = old_crc;
    unsigned char* p = (unsigned char*)&crc;

    CRCSetReserve(p[3],0);
    CRCSetVer(p[3],0);
    unsigned char pos = CRCGetpos(p[3]) % 3;
    CRCSetPos(p[3],pos);

    // 先补齐，然后调用CRC32_internal函数启用MMX优化
    uint32_t u = 0;
    while(pos != 0 && len >0) {
        p[pos] = local_crc8_table[p[pos] ^ dat[u]];

        u++;
        len --;

        pos++;
        // 达到最大值
        if(pos == 3)
            pos = 0;
        CRCSetPos(p[3],pos);
    }

    if (pos != 0) {
        return crc;
    }

    dat += u;
    return CRC_internal(crc, dat, len);
}

} // namespace fast_crc
