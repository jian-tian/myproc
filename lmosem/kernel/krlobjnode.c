/***************************
 * krlobjnode.c 2016.03.14
 * ************************/
#include "lmosemstype.h"
#include "lmosemmctrl.h"

void objnode_t_init(objnode_t * initp)
{
    hal_spinlock_init(&initp->on_lock);
    list_init(&initp->on_list);
    krlsem_t_init(&initp->on_complesem);
    initp->on_flgs = 0;
    initp->on_stus = 0;
    initp->on_opercode = -1;
    initp->on_objtype = 0;
    initp->on_objadr = NULL;
    initp->on_acsflgs = 0;
    initp->on_currops = 0;
    initp->on_len = 0;
    initp->on_ioctrd = 0;
    initp->on_buf = NULL;
    initp->on_bufcurops = 0;
    initp->on_bufsz = 0;
    initp->on_count = 0;
    initp->on_safedsc = NULL;
    initp->on_fname = NULL;
    initp->on_finode = NULL;
    initp->on_extp = NULL;

    return;
}

objnode_t * krlnew_objnode()
{
    objnode_t * ondp = (objnode_t *)krlnew((size_t)sizeof(objnode_t));
    if(!ondp)
	return NULL;
    objnode_t_init(ondp);
    return ondp; 
}

bool_t krldel_objnode(objnode_t * ondp)
{
    if(FALSE == krldelete((adr_t)(ondp), (size_t)sizeof(objnode_t)))
    {
	hal_sysdie("krldel objnode err");
	return FALSE;
    }
    return TRUE;
}
