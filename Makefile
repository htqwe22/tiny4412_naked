AR := arm-linux-ar
CC := arm-linux-gcc
CXX := arm-linux-g++
AS := arm-linux-as
LD := arm-linux-ld
NM := arm-linux-nm

# 生成bin文件工具,或加入 -I elf32-littlearm
OBJCOPY := arm-linux-objcopy
# 反汇编工具
OBJDUMP := arm-linux-objdump
# .bin 文件不能反汇编，主要是不能提供反汇编的信息
# .o .elf文件是可以支持反汇编的
# 反汇编工具 OBJDUMP -S xxx > target.s

#CFLAGS := -fno-builtin -Wall -Wstrict-prototypes -fno-stack-protector -fno-common -nostdinc -static -fPIC
#CFLAGS +=  -marm -mabi=aapcs-linux -mno-thumb-interwork -march=armv5
#LDFLAGS :=  -Bstatic -T test.lds -v
# or 链接时使用 $(LD) -Ttext=0xc4000000 -nostdlib test.o -o test
#LDFLAGS := -Ttext=0xc4000000 -nostdlib 
LDFLAGS := -Tthis.lds -nostdlib 

S_OBJS := start.o 
#div.o
#_udivsi3.o _divsi3.o _modsi3.o _umodsi3.o _ashldi3.o _lshrdi3.o _ashrdi3.o
C_OBJS :=  main.o clock.o ddr3.o trustzone.o uart.o console.o mmu.o util_string.o
CXX_OBJS := 

BIN_NAME := main.bin


#########################################################################
# THE ORDER Bellow is very important. the first is the entrance
OBJS := $(S_OBJS) $(C_OBJS) $(CXX_OBJS) 

all: $(BIN_NAME) 
.PHONY: all clean

#$(SOURCE:%.c=%.o)
#$(patsubst %.c,%.o,$(dir))
SRC := $(C_OBJS:%.o=%.c)
SRS := $(S_OBJS:%.o=%.S)
SRCXX := $(CXX_OBJS:%.o=%.cpp)
ELFS := $(BIN_NAME:%.bin=%.elf)
MAP_NAME := $(BIN_NAME:%.bin=%.map)
DUMP_NAME := $(BIN_NAME:%.bin=%.dis)
LDFLAGS += -Map $(MAP_NAME) 
#-lgcc -L/home/ht/.bin/arm-linux-gcc4.5.1/lib/gcc/arm-none-linux-gnueabi/4.5.1/ 
$(warning SRS is $(SRS),SRC is $(SRC),ELFS is $(ELFS))

$(BIN_NAME):$(OBJS) this.lds
	$(LD) ${LDFLAGS} $(OBJS) -o $(ELFS)
#	$(NM) -n $(ELFS) > $(MAP_NAME)
	$(OBJCOPY) -S -O binary $(ELFS) $@
	$(OBJDUMP) -S $(ELFS) > $(DUMP_NAME)
#	cp $@ $(HOME)/armLearn/xmodem/
	
$(S_OBJS):%.o:%.S
	$(CC) ${CFLAGS} -c $^ -o $@
$(C_OBJS):%.o:%.c
	$(CC) ${CFLAGS} -c $^ -o $@
$(CXX_OBJS):%.o:%.cpp
	$(CXX) ${CFLAGS} -c $^ -o $@

clean:
	rm -f $(BIN_NAME) $(OBJS) $(ELFS) $(MAP_NAME) $(DUMP_NAME)
