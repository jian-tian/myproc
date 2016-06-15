/******************************
 * libclose.c 2016.6.15
 * ***************************/
#include "libc.h"

sysstus_t close(hand_t fhand)
{
    sysstus_t rets = api_close(fhand);
    return rets;
}
