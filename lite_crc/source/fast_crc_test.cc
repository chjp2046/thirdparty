////////////////////////////////////////////////////////////////////////
// fast_crc_test.cc
// @brief:    Test fast crc
// @author:   fatliu@tencent
// @time:     2010-10-20
// @version:  1.0
////////////////////////////////////////////////////////////////////////
#ifndef WIN32
#include <sys/time.h>
#else
#include <time.h>
#define NOGDI
#include <windows.h>
#endif

#include "thirdparty/glog/logging.h"
#include "thirdparty/gtest/gtest.h"
#include "thirdparty/lite_crc/fast_crc.h"

using namespace google;
using namespace lite_crc;

namespace {

// 8-bit table
static unsigned char crc8_table[256] = {
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

int32_t lite_gettimeofday(struct timeval* tv, void* zone) {
#ifndef WIN32
    return gettimeofday(tv, static_cast<struct timezone*>(zone));
#else
    tv->tv_sec = static_cast<long>(time(NULL));
    return 0;
#endif
}

// #define GP  0x107   // x^8 + x^2 + x + 1
// #define DI  0x07
// static int made_table=0;
//
// static void init_crc8()
// // Should be called before any other crc function.
// {
//    int i,j;
//    unsigned char crc;
//
//    if (!made_table) {
//        for (i=0; i<256; i++) {
//            crc = i;
//            for (j=0; j<8; j++)
//                crc = (crc << 1) ^ ((crc & 0x80) ? DI : 0);
//            crc8_table[i] = crc & 0xFF;
//            printf("%-3d, ", crc8_table[i]);
//            if((i + 1) % 8 == 0)
//                printf("\r\n");
//        }
//        made_table=1;
//    }
// }


// For a byte array whose accumulated crc value is stored in *crc, computes
// resultant crc obtained by appending m to the byte array
inline void CRC8(unsigned char *crc, unsigned char m) {
    *crc = crc8_table[(*crc) ^ m];
    //*crc &= 0xFF;
}

uint32_t FastCRC1(uint32_t old_crc, unsigned char* dat, uint32_t len) {
    uint64_t crc = 0;
    unsigned char* p = (unsigned char*)&crc;
    unsigned char* c0 = &p[0];
    unsigned char* c1 = &p[1];
    unsigned char* c2 = &p[2];
#if 0
    unsigned char* c3 = &p[3];
    unsigned char* c4 = &p[4];
    unsigned char* c5 = &p[5];
    unsigned char* c6 = &p[6];
    unsigned char* c7 = &p[7];
#endif
    // 假设是长度是3的倍数
    uint32_t count = len / 3;
    unsigned char* d = dat;
    for (uint32_t u = 0; u < count; ++u) {
        //d = dat + u * 3;

        *c0 = crc8_table[(*c0) ^ d[0]];
        *c1 = crc8_table[(*c1) ^ d[1]];
        *c2 = crc8_table[(*c2) ^ d[2]];

        d +=3;
    }

    return (int32_t)crc;
}

uint32_t CRC32_use_crc8(unsigned char* dat, uint32_t len) {
    uint32_t crc = 0;
    uint8_t crc_val  =0 ;
    for (uint32_t u = 0; u < len; u++)
        CRC8(&crc_val, dat[u]);

    crc = crc_val;
    return crc;
}

uint32_t GetCRC32(uint32_t old_crc,
                         const unsigned char* data,
                         uint32_t len) {
    //
    // CRC32算法
    // 描述:
    //       PKZip、WinZip 和 Ethernet 中的CRC算法, 做了累进改进, 改进见代码
    // 备注:
    //       适用于进行不定长累加的场合
    //
    static const uint32_t  crc32_table[256] = {
        0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
        0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
        0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
        0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
        0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
        0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
        0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
        0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
        0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
        0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
        0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
        0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
        0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
        0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
        0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
        0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
        0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
        0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
        0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
        0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
        0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
        0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
        0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
        0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
        0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
        0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
        0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
        0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
        0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
        0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
        0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
        0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
        0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
        0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
        0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
        0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
        0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
        0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
        0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
        0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
        0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
        0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
        0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
        0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
        0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
        0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
        0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
        0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
        0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
        0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
        0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
        0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
        0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
        0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
        0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
        0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
        0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
        0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
        0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
        0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
        0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
        0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
        0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
        0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
    };

    uint32_t  crc = old_crc;    //  初始化为这个值0xffffffff
    const unsigned char* buffer = data;

    // init table
    // 改变polynomial的值的时候才需要重新生成crc32 table
    // Gen_CRC32_Table<void>();

    for (uint32_t u = 0; u < len; ++u)
        crc = (crc >> 8) ^ crc32_table[(crc & 0xFF) ^ *buffer++];
    return crc;                  //  需要继续累加
    // return crc^0xffffffff;    //  结束累加的算法
}

void test_crc8_speed() {
    uint32_t buff_len = 900*1024*1024;
    unsigned char* buff = new unsigned char[buff_len];
    memset(buff, 0xfa, buff_len);

    struct timeval t0 = {0};
    struct timeval t1 = {0};
    lite_gettimeofday(&t0, NULL);

    LOG(INFO) << "calc crc8 start";

    uint32_t hash = CRC32_use_crc8(buff, buff_len);

    LOG(INFO) << "calc crc8 finished.";

    lite_gettimeofday(&t1, NULL);

    uint32_t cost = (t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec - t0.tv_usec;
    float f_cost = float(cost) / float(1000000);
    float speed = float(buff_len) / float(1024*1024) / f_cost;

    LOG(INFO) << "crc8 speed is " << speed <<" MB/s, cost:" << f_cost
        <<" seconds, cost:" << cost << " microseconds.\r\n";

    LOG(INFO) << "hash result, hash = " << hash;

    delete []buff;
    buff = NULL;
}

void test_fast_crc8_speed() {
    uint32_t buff_len = 900*1024*1024;
    unsigned char* buff = new unsigned char[buff_len];
    memset(buff, 0xfa, buff_len);

    struct timeval t0 = {0};
    struct timeval t1 = {0};
    lite_gettimeofday(&t0, NULL);

    LOG(INFO) << "calc fast crc8 start";

    uint32_t hash = FastCRC1(0, buff, buff_len);

    LOG(INFO) << "calc fast crc8 finished.";

    lite_gettimeofday(&t1, NULL);

    uint32_t cost = (t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec - t0.tv_usec;
    float f_cost = float(cost) / float(1000000);
    float speed = float(buff_len)/float(1024*1024) / f_cost;

    LOG(INFO) << "fast crc8 speed is "<< speed << " MB/s, cost:" << f_cost
        <<" seconds, cost:" << cost << " microseconds.";

    LOG(INFO) << "hash result, hash = " << hash;

    delete []buff;
    buff = NULL;
}

void test_crc32_speed() {
    uint32_t buff_len = 900*1024*1024;
    unsigned char* buff = new unsigned char[buff_len];
    memset(buff, 0xfa, buff_len);

    struct timeval t0 = {0};
    struct timeval t1 = {0};
    lite_gettimeofday(&t0, NULL);

    LOG(INFO) << "calc crc32 start";

    uint32_t hash = FastCRC(0xffffffff, buff, buff_len);

    LOG(INFO) << "calc crc32 finished.";

    lite_gettimeofday(&t1, NULL);

    uint32_t cost = (t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec - t0.tv_usec;
    float f_cost = float(cost) / float(1000000);
    float speed = float(buff_len)/float(1024*1024) / f_cost;

    LOG(INFO) << "fast crc speed is " << speed << " MB/s, cost:" << f_cost
        <<" seconds, cost:" << cost << " microseconds.";
    LOG(INFO) << "hash result, hash = " << hash;

    delete []buff;
    buff = NULL;
}

void test_hash_speed() {
    uint32_t buff_len = 800*1024*1024;
    unsigned char* buff = new unsigned char[buff_len];
    memset(buff, 0xfa, buff_len);

    struct timeval t0 = {0};
    struct timeval t1 = {0};
    lite_gettimeofday(&t0, NULL);

    LOG(INFO) << "calc hash start";

    uint32_t hash = GetCRC32(0xffffffff, buff, buff_len);

    LOG(INFO) << "calc hash finished.";

    lite_gettimeofday(&t1, NULL);

    uint32_t cost = (t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec - t0.tv_usec;
    float f_cost = float(cost) / float(1000000);
    float speed = float(buff_len)/float(1024*1024) / f_cost;

    LOG(INFO) << "crc32 speed is " << speed << " MB/s, cost:" << f_cost
        <<" seconds, cost:" << cost << " microseconds.";
    LOG(INFO) << "hash result, hash = " << hash;

    delete []buff;
    buff = NULL;
}

} // namespace

int32_t main(int32_t argc, char** argv)
{
    google::AllowCommandLineReparsing();
    google::ParseCommandLineFlags(&argc, &argv, true);

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

// @brief:     test fast CRC
TEST(TestFastCRC, FastCRC) {

    test_crc32_speed();

    test_crc8_speed();

    test_fast_crc8_speed();

    test_hash_speed();

    // prepare data
    printf("prepare data...\r\n");
    uint32_t max_buff = 1024*1024;
    max_buff *= (2*1024);
    unsigned char* dat = new unsigned char[max_buff];
    for(uint32_t u = 0; u < max_buff; ++u)
        dat[u] = static_cast<unsigned char>(u % 256);

    struct timeval t1 = {0};
    struct timeval t2 = {0};
    printf("begin test...\r\n");
    lite_gettimeofday(&t1, NULL);
    uint32_t hash = FastCRC(0xffffffff, dat, max_buff);
    lite_gettimeofday(&t2, NULL);

    uint32_t cost_usecs = (t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec - t1.tv_usec;
    float cost = float(cost_usecs) / float(1000000);

    float speed = (float(max_buff) / float(1024*1024)) / cost;
    printf("cost time:%5.2f seconds, for FastCRC data length:%5.2f M Bytes\r\n", cost,
                                                  float(max_buff) / float(1024*1024));
    printf("crc speed %5.2f M Bytes/s, hash result is:%u\r\n", speed, hash);

    delete[] dat;
}

