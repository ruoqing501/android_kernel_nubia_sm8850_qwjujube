KERNEL_SRC ?= /home/adrianojr59/Vídeos/NX809J_Android16_kernel/kernel_platform/common
M ?= $(shell pwd)

EXTRA_CFLAGS += -I$(KERNEL_SRC)/../msm-kernel/include

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) modules

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) clean
