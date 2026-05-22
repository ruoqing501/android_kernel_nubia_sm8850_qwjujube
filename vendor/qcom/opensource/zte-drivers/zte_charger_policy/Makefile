KERNEL_SRC ?= /home/adrianojr59/Vídeos/NX809J_Android16_kernel/kernel_platform/common

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(shell pwd) ARCH=arm64 \
		CROSS_COMPILE=aarch64-linux-gnu- LLVM=1 LLVM_IAS=1 \
		KBUILD_EXTRA_SYMBOLS="$(KERNEL_SRC)/../../vendor/qcom/opensource/zte-drivers/zte_power_supply/Module.symvers $(KERNEL_SRC)/../../vendor/qcom/opensource/zte-drivers/zte_misc/Module.symvers" \
		modules

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(shell pwd) clean
