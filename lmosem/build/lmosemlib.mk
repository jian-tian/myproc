###############################
#	lib自动化编译配置文件Makefile
###############################

MAKEFLAGS = -s
KERNELCE_PATH = ../lib/
HEADFILE_PATH = -I ../include -I ../include/bastypeinc -I ../include/halinc -I ../include/knlinc -I ../include/libinc -I ../include/drvinc
CCBUILDPATH = $(KERNELCE_PATH)
include krnlbuidcmd.mh
include krnlobjs.mkh

.PHONY : all everything build_kernel

all : build_kernel

build_kernel : everything

everything : $(BUILD_MK_LIBS_OBJS)
include krnlbuidcmd.mh
