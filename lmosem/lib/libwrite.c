/*****************************
 * libwrite.c 2016.6.15
 * **************************/
#include "libc.h"

sysstus_t write(hand_t fhand, buf_t buf, size_t len, uint_t flgs)
{
    sysstus_t rets = api_read(fhand, buf, len, flgs);
    return rets;
}
