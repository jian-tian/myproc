########################
#	Main control auto compile Makefile
########################

MAKEFLAGS = -sR

MKDIR = mkdir
RMDIR = rmdir

CP = cp
CD = cd
DD = dd
RM = rm
VM = qemu-system-arm -M mini2440 -kernel lmosemkrnl.uimg -serial stdio -mtdblock ndflash -show-cursor -usb -usbdevice keyboard -usbdevice mouse -net nic,vlan=0 -net tap,vlan=0,ifname=tap1,script=qemu-ifup,downscript=qemu-ifdown -monitor telnet::5555,server,nowait #-nographic
MAKE = make
MKIMAGE = mkimage
SUPERUSER = sudo
DKAPP = ./dnw2
DKAPFLAGS = lmosemkrnl.bin
PREMENTMFLGS = -C $(BUILD_PATH) -f pretreatment.mk
ARMHALYMFLGS = -C $(BUILD_PATH) -f lmosemhal.mk
ARMKRNLMFLGS = -C $(BUILD_PATH) -f lmosemkrl.mk 
ARMDRIVMFLGS = -C $(BUILD_PATH) -f lmosemdrv.mk
ARMLIBSMFLGS = -C $(BUILD_PATH) -f lmosemlib.mk
ARMTASKMFLGS = -C $(BUILD_PATH) -f lmosemtask.mk
ARMLINKMFLGS = -C $(BUILD_PATH) -f lmosemlink.mk
CPFLAGES =
VMFLAGES = 
MGFLAGES = -A arm -T kernel -C none -a 30007eb0 -e 30008000 -d lmosemkrnl.bin lmosemkrnl.uimg
DSTPATH = ../exckrnl
RELEDSTPATH = ../release
SRCFILE = lmosemkrnl.bin lmosemkrnl.elf
BUILD_PATH = ./build
EXKNL_PATH = ./exckrnl
BOOTEXCIMG = lmosem.bin
DSKIMG = flash.img
.PHONY : build print clean all cpkrnl knlexc writekrl downkrnl

build : clean print all

all:
	$(MAKE) $(PREMENTMFLGS)
	$(MAKE) $(ARMHALYMFLGS)
	$(MAKE) $(ARMKRNLMFLGS)
	$(MAKE) $(ARMDRIVMFLGS)
	$(MAKE) $(ARMLIBSMFLGS)
	$(MAKE) $(ARMTASKMFLGS)
	$(MAKE) $(ARMLINKMFLGS)
	@echo '恭喜，编译完成！'

clean :
	$(CD) $(BUILD_PATH); $(RM) -f *.mkh  *.lds *.o *.i *.krnl *.s *.map *.btoj *.vdi *vmdk
	$(CD) $(EXKNL_PATH); $(RM) -f *.mkh  *.lds *.o *.i *.krnl *.s *.map *.btoj *.vdi *vmdk
	@echo 'clean finished... ^_^'

print :
	@echo '.....正在编译构建系统.....'

knlexc : cpkrnl downkrnl #writekrl cpkrnlUIMAGE
	#$(CD) $(EXKNL_PATH) && $(VM) $(VMFLAGES)

cpkrnl :
	$(CD) $(BUILD_PATH) && $(CP) $(CPFLAGES) $(SRCFILE) $(DSTPATH)

writekrl :
	$(CD) $(EXKNL_PATH) && $(DD) bs=512 if=$(BOOTEXCIMG) of=$(DSKIMG) conv\=notrunc

UIMAGE:
	$(CD) $(EXKNL_PATH) && $(MKIMAGE) $(MGFLAGES)

downkrnl :
	$(CD) $(EXKNL_PATH) && $(SUPERUSER) $(DKAPP) $(DKAPFLAGS)
