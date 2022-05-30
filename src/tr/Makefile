CSRC_HOME := $(shell if [ "$$CSRC_HOME" != "" ]; then echo $$CSRC_HOME; else echo "$$PWD/.."; fi)
include $(CSRC_HOME)/config.mk

LIBS			=	
TR_SYNC			=	update_userinfo update_version update_configsnap
TR_SYNC_OBJS	=	update_userinfo.o update_version.o update_configsnap.o

LINK    =   -L$(ORACLE_HOME)/lib/ -lm -lz -lclntsh -lpthread -L$(LIB_PATH) -lSyncRedis -lhiredis -L$(SCLIB_PATH)/lib -lSC

all	:	$(LIBS) \
		$(TR_SYNC) \
		install \
		clean

test:	$(TSETPGM)

$(LIBS) :	$@
		$(CC) $(COMP) $@.c

$(TR_SYNC) :	$@
		$(PROC) $(PFLAGS) iname=$@
		$(CC) $(COMP) $(ORA_COMP) -c $@.c
		rm -f $@.c

install	:
		$(CC) -shared -o libSyncTR.so $(TR_SYNC_OBJS) $(LINK)
		mv libSyncTR.so ../../lib

clean   :
		rm -f *.o *.lis
