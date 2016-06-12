/**************************
 * krlsveread.h 2016.6.11
 * ***********************/
#ifndef KRLSVEREAD_H
#define KRLSVEREAD_H

sysstus_t krlsvetabl_read(uint_t swinr, stkparame_t * stkparv);
sysstus_t krlsve_read(hand_t fhand, buf_t buf, size_t len, uint_t flgs);
sysstus_t krlsve_core_read(hand_t fhand, buf_t buf, size_t len, uint_t flgs);
sysstus_t krlsve_read_device(objnode_t * ondep);

#endif
