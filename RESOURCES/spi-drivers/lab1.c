#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/of_device.h>

static const struct of_device_id myspi_of_match[] = {
	{
		.compatible = "mycompany,myspi",
		.data = (void *) "some useful data",
	},
	{ },
};
MODULE_DEVICE_TABLE(of, myspi_of_match);

static int myspi_probe(struct spi_device *spi)
{
	const struct of_device_id *match;

	pr_info("myspi_probe called\n");

	match = of_match_device(of_match_ptr(myspi_of_match), &spi->dev);
	if (match) {
		/* parse device tree options */
		pr_info("devicetree match\n");
	}

	/* get memory for driver's per-chip state */
//	chip = devm_kzalloc(&spi->dev, sizeof *chip, GFP_KERNEL);
//	if (!chip)
//		return -ENOMEM;

//	spi_set_drvdata(spi, chip);

	return 0;
}

static const struct spi_device_id myspi_id_table[] = {
	{ "myspi", 0 },
	{ },
};
MODULE_DEVICE_TABLE(spi, myspi_id_table);

static struct spi_driver myspi_driver = {
        .driver = {
                .name = "myspi_spi",
                .of_match_table = of_match_ptr(myspi_of_match),
        },
        .probe = myspi_probe,
        .id_table = myspi_id_table,
};
module_spi_driver(myspi_driver);

MODULE_AUTHOR("Codie McCoderson");
MODULE_DESCRIPTION("Driver for simple SPI device");
MODULE_LICENSE("GPL");
