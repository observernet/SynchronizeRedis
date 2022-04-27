CSRC_HOME := $(shell if [ "$$CSRC_HOME" != "" ]; then echo $$CSRC_HOME; else echo "$$PWD/.."; fi)
include $(CSRC_HOME)/config.mk

LIBS	=	
PCPGM	=	SyncRedisFromOracle 
CPGM	=	SyncRedisCli

LINK    =   -L$(ORACLE_HOME)/lib/ -lm -lz -lclntsh -lpthread -ldl -L$(LIB_PATH) -lSyncRedis -lhiredis -L$(SCLIB_PATH)/lib -lSC

all	:	$(PCPGM) \
		$(CPGM) \
		clean

test:	$(TSETPGM)

$(LIBS) :	$@
		$(CC) $(COMP) $@.c

$(PCPGM) :	$@
		$(PROC) $(PFLAGS) iname=$@
		$(CC) $(COMP) $(ORA_COMP) $@.c
		$(CC) -o $(INSTALL_PATH)/$@ $@.o $(LIB) $(LINK)
		rm -f $@.c

$(CPGM) :	$@
		$(CC) $(COMP) $@.c
		$(CC) -o $(INSTALL_PATH)/$@ $@.o $(LIB) $(LINK)

clean   :
		rm -f *.o *.lis
