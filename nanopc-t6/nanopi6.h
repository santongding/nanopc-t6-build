/*
 * SPDX-License-Identifier:     GPL-2.0+
 *
 * Copyright (C) Guangzhou FriendlyELEC Computer Tech. Co., Ltd.
 * (http://www.friendlyelec.com)
 *
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd
 */

#ifndef __CONFIG_NANOPI6_H__
#define __CONFIG_NANOPI6_H__

#include <configs/rk3588_common.h>

/* Remove or override few declarations from rk3588-common.h */
#undef CONFIG_BOOTCOMMAND
#undef CONFIG_DISPLAY_BOARDINFO_LATE
#undef RKIMG_DET_BOOTDEV
#undef RKIMG_BOOTCOMMAND

#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_SYS_MMC_MAX_BLK_COUNT	32768

#define CONFIG_MISC_INIT_R
#define CONFIG_SERIAL_TAG

#ifndef CONFIG_SPL_BUILD

#define ROCKCHIP_DEVICE_SETTINGS \
	"stdout=serial,vidconsole\0" \
	"stderr=serial,vidconsole\0"

#define RKIMG_DET_BOOTDEV \
	"bootcmd=setenv ethaddr 00000000eb9fa2be; setenv eth1addr 00000000eb9fa2be; setenv bootdev unknown; setenv kernel_addr_gz 0xa2080000; setenv fdt_addr_r 0x08300000; setenv kernel /boot/Image.gz; setenv fdtfile rk3588-nanopi6-rev01.dtb; setenv overlayfile rk3588-nanopi6-optee.dtbo; for p in 5 6; do for d in 1 0; do test ${bootdev} = unknown && test $(part uuid mmc ${d}:${p}) = 17d61bff-8fdc-4089-b675-9be21b9f6ac7 && echo .. Looking for ${kernel} in mmc ${d}:${p} && test -e mmc ${d}:${p} ${kernel} && setenv bootdev ${d} && setenv bootpart ${p} && echo .. Found; done; done; if test ${bootdev} = unknown; then echo .. Kernel not found; else echo .. Loading kernel; ext2load mmc ${bootdev}:${bootpart} ${kernel_addr_gz} ${kernel}; unzip ${kernel_addr_gz} ${kernel_addr_r}; echo .. Loading DTB: mmc ${bootdev}:${bootpart} ${fdtfile}; ext2load mmc ${bootdev}:${bootpart} ${fdt_addr_r} /boot/${fdtfile}; echo .. Resizing DTB to 320K; fdt addr ${fdt_addr_r}; fdt resize 0x50000; echo .. Loading overlay: mmc ${bootdev}:${bootpart} ${overlayfile}; ext2load mmc ${bootdev}:${bootpart} 0x083C0000 /boot/${overlayfile}; echo .. Applying overlay; fdt apply 0x083C0000; echo .. Booting kernel; booti ${kernel_addr_r} - ${fdt_addr_r}; fi; \0"
#define RKIMG_BOOTCOMMAND \
	"run bootcmd;"

#define CONFIG_BOOTCOMMAND		RKIMG_BOOTCOMMAND

#endif

#endif /* __CONFIG_NANOPI6_H__ */
