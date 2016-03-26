/************************************
 * krlmm.c 2016.03.03
 * *********************************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

void init_krlmm()
{
    init_krlpagempol();
    return;
}

adr_t krlnew(size_t mmsize)
{
    adr_t ret = NULL;
    if(mmsize == MALCSZ_MIN || mmsize > MALCSZ_MAX)
    {
	printfk("mmsize error\n\r");
	return NULL;
    }
 
    ret = kmempool_new(mmsize);
    if(!ret)
    {
	printfk("kmempool_new failed\n\r");
	return NULL;
    }
    return ret;
}

bool_t krldelete(adr_t fradr, size_t frsz)
{
    if(fradr == NULL || frsz == MALCSZ_MIN || frsz > MALCSZ_MAX)
	return NULL;
    return kmempool_delete(fradr, frsz);
}
