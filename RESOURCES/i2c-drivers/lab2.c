#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/of_device.h>

static int foo_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret;

	pr_info("foo_probe called\n");

	if (client->dev.of_node) {
		pr_info("device tree instantiated probe. data = %x\n",
			(unsigned int)of_device_get_match_data(&client->dev));
	}

	ret = i2c_smbus_read_byte_data(client, 0x0d);
	pr_info("i2c read byte = %x\n", ret);
	if (ret < 0)
		return ret;

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

static const struct of_device_id foo_dt_ids[] = {
        { .compatible = "foo,bar", .data = (void *) 0xDEADBEEF },
        { }
};
MODULE_DEVICE_TABLE(of, foo_dt_ids);

static struct i2c_driver foo_driver = {
	.driver = {
		.name   = "foobar",
		.of_match_table = of_match_ptr(foo_dt_ids)
	},
	.id_table       = foo_idtable,
	.probe          = foo_probe,
	.remove         = foo_remove,
};

module_i2c_driver(foo_driver);

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>");
MODULE_DESCRIPTION("Driver for Barf Inc. Foo I2C devices");
MODULE_LICENSE("GPL");
