#######################
#	krnlbuidrule自动化编译配置文件Makefile
#######################

CCSTR		= 'CC -[M] 正在构建... ' $<
PRINTCSTR	= @echo $(CCSTR)

%.krnl : $(CCBUILDPATH)%.c
	$(CC) $(CFLAGS) -o $@ $<
	$(PRINTCSTR)
%.krnl : $(CCBUILDPATH)%.S
	$(CC) $(CFLAGS) -o $@ $<
	$(PRINTCSTR)
%.o : $(CCBUILDPATH)%.c
	$(CC) $(CFLAGS) -o $@ $<
	$(PRINTCSTR)
%.o : $(CCBUILDPATH)%.S
#	@echo $@ $<
	$(CC) $(CFLAGS) -o $@ $<
	$(PRINTCSTR)

%.lds : $(CCBUILDPATH)%.S
	$(CC) $(CPPFLAGSLDS) -o $@ $<
	$(PRINTCSTR)
%.mkh : $(CCBUILDPATH)%.S
	$(CC) $(CPPFLAGSLDS) -o $@ $<
	$(PRINTCSTR)
