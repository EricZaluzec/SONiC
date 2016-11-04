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
	{ 0x3940d6dc, __VMLINUX_SYMBOL_STR(hwmon_device_register) },
	{ 0xc1ed9a06, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x6adf1c95, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x23beab60, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x20705009, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x8733c9e1, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd27feae7, __VMLINUX_SYMBOL_STR(i2c_smbus_write_word_data) },
	{ 0x1b17e06c, __VMLINUX_SYMBOL_STR(kstrtoll) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x69539c9c, __VMLINUX_SYMBOL_STR(i2c_smbus_read_word_data) },
	{ 0x1e12b70c, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x9166fada, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0xfbf6264d, __VMLINUX_SYMBOL_STR(__dynamic_dev_dbg) },
	{ 0x807c9567, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x77f4cc43, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x96da5039, __VMLINUX_SYMBOL_STR(i2c_smbus_read_i2c_block_data) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x63e08021, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0xff1b5b65, __VMLINUX_SYMBOL_STR(hwmon_device_unregister) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=i2c-core";

MODULE_ALIAS("i2c:ym2651");
