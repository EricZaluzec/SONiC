#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x2ab9dba5, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xf67d08f8, __VMLINUX_SYMBOL_STR(platform_device_unregister) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9ad37ed, __VMLINUX_SYMBOL_STR(platform_device_register_full) },
	{ 0x23beab60, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xc71c735c, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x20705009, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x8733c9e1, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x2cc2a51d, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x29a3fd3b, __VMLINUX_SYMBOL_STR(platform_accton_as7712_32x) },
	{ 0x4780b264, __VMLINUX_SYMBOL_STR(accton_i2c_cpld_write) },
	{ 0x33ec10cf, __VMLINUX_SYMBOL_STR(led_classdev_register) },
	{ 0x6417e47a, __VMLINUX_SYMBOL_STR(led_classdev_unregister) },
	{ 0x88b2cdf7, __VMLINUX_SYMBOL_STR(led_classdev_suspend) },
	{ 0xfbf6264d, __VMLINUX_SYMBOL_STR(__dynamic_dev_dbg) },
	{ 0x1e12b70c, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x78f78725, __VMLINUX_SYMBOL_STR(accton_i2c_cpld_read) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x77f4cc43, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2cdb2ba7, __VMLINUX_SYMBOL_STR(led_classdev_resume) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=accton_i2c_cpld";

