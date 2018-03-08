#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>

static unsigned int gpioLED = 111;

static int __init red_module_init(void)
{
	printk(KERN_INFO "RED LED module loaded\n");

	if (!gpio_is_valid(gpioLED)){
		printk(KERN_INFO "GPIO_TEST: invalid LED GPIO\n");
		return -ENODEV;
	}

	gpio_request(gpioLED, "LED");
	gpio_direction_output(gpioLED, 1);

	return 0;
}

static void __exit red_module_exit(void)
{
	gpio_direction_output(gpioLED, 0);
	gpio_free(gpioLED);

	printk(KERN_INFO "RED LED module unloaded\n");
}

module_init(red_module_init);
module_exit(red_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Q. Coder");
MODULE_DESCRIPTION("RED LED module");
