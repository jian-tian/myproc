/*************************
 * krlobjnode_t.h 2016.03.11
 * **********************/
#ifndef _KRLOBJNODE_T_H
#define _KRLOBJNODE_T_H

#define OBJN_TY_DEV 1
#define OBJN_TY_FIL 2
#define OBJN_TY_NUL 0

typedef struct s_OBJNODE
{
    spinlock_t on_lock;
    list_h_t	on_list;
    sem_t	on_complesem;
    uint_t	on_flgs;
    uint_t	on_stus;
    sint_t	on_opercode;
    uint_t	on_objtype;
    void *	on_objadr;
    uint_t	on_acsflgs;
    uint_t	on_acsstus;
    uint_t	on_currops;
    uint_t	on_len;
    uint_t	on_ioctrd;
    buf_t	on_buf;
    uint_t	on_bufcurops;
    size_t	on_bufsz;
    uint_t	on_count;
    void *	on_safedsc;
}objnode_t;

#define OBJN_TY_DEV	1
#define ONJN_TY_FIL	2
#define OBJN_TY_NUL	0

#endif
