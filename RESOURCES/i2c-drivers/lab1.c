#include <linux/module.h>
#include <linux/i2c.h>


static int foo_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	pr_info("foo_probe called\n");
	return 0;
}

static int foo_remove(struct i2c_client *client)
{
	pr_info("foo_remove called\n");
	return 0;
}

static struct i2c_device_id foo_idtable[] = {
	{ "foo", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, foo_idtable);

static struct i2c_driver foo_driver = {
	.driver = {
		.name   = "foo",
	},
	.id_table       = foo_idtable,
	.probe          = foo_probe,
	.remove         = foo_remove,
};

module_i2c_driver(foo_driver);

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>");
MODULE_DESCRIPTION("Driver for Barf Inc. Foo I2C devices");
MODULE_LICENSE("GPL");
