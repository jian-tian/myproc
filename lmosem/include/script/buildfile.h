#ifndef _BUILD_FILE_H
#define _BUILD_FILE_H

#define BUILD_BOOT_OBJS
#define BUILD_HALY_OBJS init.o lmosemhal_start.o interrupt.o intabtdistr.o halglobal.o halinit.o vector.o platform.o printfk.o div0.o _udivsi3.o _umodsi3.o _modsi3.o _divsi3.o cpuctrl.o halmach.o halmmu.o halmm.o haluart.o halintrupt.o

#define BUILD_KRNL_OBJS krlinit.o krlpagempol.o krlglobal.o krlmm.o krlintupt.o krlobjnode.o krldevice.o krlsem.o krltime.o krlsched.o krlthread.o krlcpuidle.o krlwaitlist.o krlsvemm.o krlservice.o krlsveopen.o krlsvethread.o krlsveclose.o krlsveread.o krlsvewrite.o krlsveioctrl.o krlsvelseek.o task.o

#define BUILD_MEMY_OBJS

#define BUILD_FSYS_OBJS
#define BUILD_DRIV_OBJS drvtick.o drvrtc.o drvfs.o drvuart.o

#define BUILD_LIBS_OBJS lapitime.o lapithread.o lapimm.o lapiopen.o \
			lapiclose.o lapiread.o lapiwrite.o lapiioctrl.o lapilseek.o \
			libmm.o libthread.o libopen.o libclose.o libread.o \
			libwrite.o libioctrl.o liblseek.o libtime.o printf.o
#define BUILD_TASK_OBJS utask.o
#define BUILD_LINK_OBJS BUILD_BOOT_OBJS BUILD_HALY_OBJS \
			BUILD_KRNL_OBJS BUILD_MEMY_OBJS \
			BUILD_FSYS_OBJS BUILD_DRIV_OBJS \
			BUILD_LIBS_OBJS BUILD_TASK_OBJS
#define LINKR_IPUT_FILE BUILD_LINK_OBJS
#define LINKR_OPUT_FILE lmosemkrnl.elf
#define KERNL_ELFF_FILE LINKR_OPUT_FILE
#define KERNL_BINF_FILE lmosemkrnl.bin
                          
#endif // BUILDFILE_H
