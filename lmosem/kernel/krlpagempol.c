/***********************
 * krlpagempol.c 2016.02.26
 * ********************/
#include "lmosemtypes.h"
#include "lmosemmctrl.h"

adr_t kmempool_new(size_t msize)
{
    if(msize < KMEMPALCSZ_MIN || msize > KMEMPALCSZ_MIN)
	return NULL;

    return kmempool_onsize_new(msize);
}

bool_t kmempool_delete(adr_t fradr, size_t frsz)
{
    if(fradr == NULL || fradr < KMEMPALCSZ_MIN || fradr > KMEMPALCSZ_MAX)
	return NULL;

    return kmempool_onsize_delete(fradr, frsz);
}

adr_t kmempool_onsize_new(size_t msize)
{
    if(msize > OBJSORPAGE)
	return kmempool_pages_new(msize);

    return kmempool_objsz_new(msize);
}

bool_t kmempool_onsize_delete(adr_t fradr, size_t frsz)
{
    if(frsz > OBJSORPAGE)
	return kmempool_pages_delete(fradr, frsz);

    return kmempool_objsz_delete(fradr, frsz);
}

adr_t kmempool_pages_new(size_t msize)
{
    size_t sz = PAGE_ALIGN(msize);
    if(sz > KPMPORHALM)
	return kmempool_page_new_callhalmm(sz);

    return kmempool_pages_core_new(sz);
}

bool_t kmempool_pages_delete(adr_t fradr, size_t frsz)
{
    size_t sz = PAGE_ALIGN(frsz);
    if(sz > KPMPORHALM)
	return kmempool_page_delete_callhalmm(fradr, sz);

    return kmempool_pages_core_delete(fradr, sz);
}

adr_t kmempool_page_new_callhalmm(size_t msize)
{
    if(msize <= BLK128KB_SIZE)
	return hal_memallocblks(BLK128KB_SIZE);
    if(msize <= BLK256KB_SIZE)
	return hal_memallocblks(BLK256KB_SIZE);
    if(msize <= BLK512KB_SIZE)
	return hal_memallocblks(BLK512KB_SIZE);
    if(msize <= BLK1MB_SIZE)
	return hal_memallocblks(BLK1MB_SIZE);
    if(msize <= BLK2MB_SIZE)
	return hal_memallocblks(BLK2MB_SIZE);
    if(msize <= BLK4MB_SIZE)
	return hal_memallocblks(BLK4MB_SIZE);

    return NULL;
}

bool_t kmempool_page_delete_callhalmm(adr_t fradr, size_t frsz)
{
    if(frsz <= BLK128KB_SIZE)
	return hal_memfreeblks(fradr, BLK128KB_SIZE);
    if(frsz <= BLK256KB_SIZE)
	return hal_memfreeblks(fradr, BLK256KB_SIZE);
    if(frsz <= BLK512KB_SIZE)
	return hal_memfreeblks(fradr, BLK512KB_SIZE);
    if(frsz <= BLK1MB_SIZE)
	return hal_memfreeblks(fradr, BLK1MB_SIZE);
    if(frsz <= BLK2MB_SIZE)
	return hal_memfreeblks(fradr, BLK2MB_SIZE);
    if(frsz <= BLK4MB_SIZE)
	return hal_memfreeblks(fradr, BLK4MB_SIZE);

    return FALSE;
}
