#include "crc32.h"
#define	COMPUTE(var, ch)	(var) = (var) << 8 ^ crc32_tab[(var) >> 24 ^ (ch)]
UInt32 crc32( const void *buf, size_t size)
{
    UInt32 crc = 0x00000000;
	const UInt8 *p;
    int nr;
    crc = crc ^ 0xffffffffUL;
	p = reinterpret_cast<const UInt8 *>(buf);
    while (size >= 8) {
        DO8;
        size -= 8;
    }
    if (size) do {
        DO1;
    } while (--size);
    return crc ^ 0xffffffffUL;
}
