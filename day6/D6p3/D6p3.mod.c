#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x4766f3ab, "module_layout" },
	{ 0xea3c74e, "tasklet_kill" },
	{ 0xadfb6ea0, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x2364c85a, "tasklet_init" },
	{ 0x31ace3dd, "cdev_add" },
	{ 0xa8881d43, "cdev_alloc" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x9d2ab8ac, "__tasklet_schedule" },
	{ 0x5f754e5a, "memset" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0xe914e41e, "strcpy" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C20D3A9BE9BF5C565D7CB9E");
