/********************************
 * krlobjnode.h 2016.03.14
 * *****************************/
#ifndef _KRLOBJNODE_H
#define _KRLOBJNODE_H

void objnode_t_init(objnode_t * initp);
objnode_t * krlnew_objnode();
bool_t krldel_objnode(objnode_t * ondp);

#endif
