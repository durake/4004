# Copyright (c) 2015 Qualcomm Atheros, Inc.
# All Rights Reserved.
# Qualcomm Atheros Confidential and Proprietary.
# $ATH_LICENSE_TARGET_MK$
#
# 
# 
default: all
DIR_ADAPTER = ./ipp_adapter
DIR_IPP_API = ./ipp_api
DIR_IPP_UTIL = ./ipp_util
DIR_IPP_DEVCLOUD = ./IPPDeviceCloudManager
DIR_IPP_CLOUDMSG = ./IPPThinCloudManager
DIR_IPP_SELFSERV = ./SelfService
DIR_IPP_TGSSDK = ./ThreeGenerationSystemSDK
IMAGEDIR := $(SRC_IOE)/image
DEMO_OUT = $(IMAGEDIR)/iot_demo.out
DEMO_LIB = $(LIBDIR)/libiot_demo.a

COPTS := -g3 -Os -Wall -Wpointer-arith -Wundef -Wl,-EL -fno-inline-functions -nostdlib -mlongcalls -ffunction-sections
DEFINES := \
	-DAR6K \
	-DAR6002 \
	-TARG:unaligned_loads=1 \
	-DAR6002_REV74 \
	-DIOT_BUILD_FLAG \
	-DAR6002_REV7 \
	-include $(INTERNALDIR)/include/fwconfig_AR6006.h \
	-Wno-return-type \
	-DATHOS \
	-DATH_TARGET \
        -DSWAT_WMICONFIG_MISC_EXT \
        -DSWAT_SSL \
        -DSWAT_I2C \
        -DSWAT_I2S \
        -DSWAT_WMICONFIG_SNTP \
        -DSWAT_OTA \
        -DENABLE_HTTP_CLIENT  \
        -DENABLE_HTTP_SERVER  \
        -DSWAT_DNS_ENABLED \
        -DHTTP_ENABLED \
        -DDNS_ENABLED \
        -DBRIDGE_ENABLED \
        -DCONFIG_HOSTLESS \
        -DSSL_ENABLED \
        -DSWAT_BENCH_RAW


INCLUDES := \
	-I$(FW)/include/AR6002/hw/include \
	-I. \
	-I$(FW)/include/qcom \
	-I$(FW)/include \
	-I$(FW)/include/AR6002/ \
	-I$(FW)/include/AR6K/ \
	-I$(THREADXDIR)/include/ \
	-I$(INTERNALDIR)/include \
	-I$(INTERNALDIR)/include/os \
	-I$(INTERNALDIR)/include/whal\
	-I./IPPDeviceCloudManager\
	-I./ipp_sdk_header \
        -I./ipp_util \
        -I./IPPThinCloudManager\
	-I./SelfService\
	-I./ipp_adapter\
	-I./ThreeGenerationSystemSDK



CFLAGS = $(COPTS) $(DEFINES) $(INCLUDES)

CC = xt-xcc
AR = xt-ar
RM = rm -f


CSRCS=$(wildcard *.c ${DIR_IPP_TGSSDK}/*.c ${DIR_ADAPTER}/*.c ${DIR_IPP_API}/*.c ${DIR_IPP_UTIL}/*.c ${DIR_IPP_DEVCLOUD}/*.c ${DIR_IPP_CLOUDMSG}/*.c ${DIR_IPP_SELFSERV}/*.c)
OBJS=$(CSRCS:%.c=%.o)
DEPS := $(CSRCS:%.c=%.d)
LIBS := $(LIBDIR)/libiot_demo.a \
	$(LIBDIR)/libramcust.a \
	$(LIBDIR)/libota.a \
	$(LIBDIR)/libp2p_fw.a \
	$(LIBDIR)/libserport.a \
	$(LIBDIR)/libuartserp.a \
	$(LIBDIR)/libconsole.a\
	$(LIBDIR)/libpatches_iot.a\
	$(LIBDIR)/libpatches.a \
        $(LIBDIR)/libpatches_ssl_iot.a \
	$(LIBDIR)/libhost_dset_api.a \
        $(LIBDIR)/libota.a \
        $(LIBDIR)/libautoip4.a \
        $(LIBDIR)/libwow_stub.a \
        $(LIBDIR)/libhttppatches.a \
        $(LIBDIR)/libsntppatches.a \
        $(LIBDIR)/libdnspatches.a \
        $(LIBDIR)/libotapatches.a \
        $(LIBDIR)/libstrrclpatches.a \
        $(LIBDIR)/libipv6patches.a \
        $(LIBDIR)/libippatches.a \
        $(LIBDIR)/libsslpatches.a \
        $(LIBDIR)/libwhalpatches.a\
	$(LIBDIR)/ceacota.a \
		$(LIBDIR)/libcustpatches.a \
		$(LIBDIR)/libsdk_apps.a

LDFLAGS = -g -nostdlib -Wl,-EL -Wl,--gc-sections \
	-L$(IMAGEDIR)  \
	-L.\
	-Tsdk_shell.ld \
	-u app_start \
	-Wl,-static \
	-Wl,--start-group \
	$(LIBS)	\
	-Wl,--end-group\
	$(IMAGEDIR)/rom.addrs.ld \
	-lgcc 


ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),mkdbg)
ifdef DEPS
sinclude $(DEPS)
endif
endif
endif

$(DEMO_LIB): $(OBJS)
	@mkdir -p $(LIBDIR)
	$(AR) ru $@ $^

$(DEMO_OUT): $(LIBS) $(LDS)
	@mkdir -p $(IMAGEDIR)
	$(CC) $(LDFLAGS) -o $@ 

all: $(OBJS) $(DEMO_LIB) $(DEMO_OUT) 

clean:
	$(foreach d, $(SUBDIRS), make -C $(d) clean;)
	$(RM) *.o ${DIR_IPP_TGSSDK}/*.o ${DIR_IPP_DEVCLOUD}/*.o ${DIR_IPP_CLOUDMSG}/*.o ${DIR_IPP_SELFSERV}/*.o ${DIR_ADAPTER}/*.o ${DIR_IPP_API}/*.o ${DIR_IPP_UTIL}/*.o
	$(RM) $(DEMO_LIB)
	$(RM) $(DEMO_OUT)


mkdbg:
	@echo pwd=`pwd`
	@echo TARGET = $(TARGET)
	@echo AR6002_REV = $(AR6002_REV)
	@echo ROMDIR = $(ROMDIR)
	@echo DEMO_OUT = $(DEMO_OUT)
	@echo DEMO_LIB = $(DEMO_LIB)
	@echo SUBDIRS = $(SUBDIRS)
	@echo CSRCS = $(CSRCS)
	@echo OBJS = $(OBJS)
	@echo DEPS = $(DEPS)
	@echo LIBS = $(LIBS)
	@echo CC = $(CC) at `which $(CC)`
	@echo CFLAGS = $(CFLAGS)
	@echo LDFLAGS = $(LDFLAGS)
