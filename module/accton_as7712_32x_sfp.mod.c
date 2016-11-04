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
	{ 0xcee3a49d, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x5a42d065, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x29a3fd3b, __VMLINUX_SYMBOL_STR(platform_accton_as7712_32x) },
	{ 0x6adf1c95, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x4d018d7d, __VMLINUX_SYMBOL_STR(sysfs_create_bin_file) },
	{ 0xc1ed9a06, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x23beab60, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x20705009, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x8733c9e1, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x1b17e06c, __VMLINUX_SYMBOL_STR(kstrtoll) },
	{ 0xc9ba90bd, __VMLINUX_SYMBOL_STR(i2c_smbus_write_i2c_block_data) },
	{ 0xfbf6264d, __VMLINUX_SYMBOL_STR(__dynamic_dev_dbg) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x63e08021, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0x9878bee7, __VMLINUX_SYMBOL_STR(sysfs_remove_bin_file) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x96da5039, __VMLINUX_SYMBOL_STR(i2c_smbus_read_i2c_block_data) },
	{ 0x1e12b70c, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x78f78725, __VMLINUX_SYMBOL_STR(accton_i2c_cpld_read) },
	{ 0x77f4cc43, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=i2c-core,accton_i2c_cpld";

MODULE_ALIAS("i2c:sfp1");
MODULE_ALIAS("i2c:sfp2");
MODULE_ALIAS("i2c:sfp3");
MODULE_ALIAS("i2c:sfp4");
MODULE_ALIAS("i2c:sfp5");
MODULE_ALIAS("i2c:sfp6");
MODULE_ALIAS("i2c:sfp7");
MODULE_ALIAS("i2c:sfp8");
MODULE_ALIAS("i2c:sfp9");
MODULE_ALIAS("i2c:sfp10");
MODULE_ALIAS("i2c:sfp11");
MODULE_ALIAS("i2c:sfp12");
MODULE_ALIAS("i2c:sfp13");
MODULE_ALIAS("i2c:sfp14");
MODULE_ALIAS("i2c:sfp15");
MODULE_ALIAS("i2c:sfp16");
MODULE_ALIAS("i2c:sfp17");
MODULE_ALIAS("i2c:sfp18");
MODULE_ALIAS("i2c:sfp19");
MODULE_ALIAS("i2c:sfp20");
MODULE_ALIAS("i2c:sfp21");
MODULE_ALIAS("i2c:sfp22");
MODULE_ALIAS("i2c:sfp23");
MODULE_ALIAS("i2c:sfp24");
MODULE_ALIAS("i2c:sfp25");
MODULE_ALIAS("i2c:sfp26");
MODULE_ALIAS("i2c:sfp27");
MODULE_ALIAS("i2c:sfp28");
MODULE_ALIAS("i2c:sfp29");
MODULE_ALIAS("i2c:sfp30");
MODULE_ALIAS("i2c:sfp31");
MODULE_ALIAS("i2c:sfp32");
