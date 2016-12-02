/*
 * A LED driver for the accton_as7512_32x_led
 *
 * Copyright (C) 2014 Accton Technology Corporation.
 * Brandon Chuang <brandon_chuang@accton.com.tw>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*#define DEBUG*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/leds.h>
#include <linux/slab.h>
#include <linux/dmi.h>


enum led_type {
	LED_TYPE_DIAG_GREEN,
	LED_TYPE_DIAG_RED,
	LED_TYPE_LOC_BLUE,
	LED_TYPE_FAN_GREEN,
	LED_TYPE_FAN_RED,
	LED_TYPE_PS1_GREEN,
	LED_TYPE_PS1_RED,    
	LED_TYPE_PS2_GREEN,
	LED_TYPE_PS2_RED,      
	LED_TYPE_FORCE,  
	LED_TYPE_MAX        
};

#define DRVNAME "as7512_32x_led"
#define NUM_OF_LED_REG              (LED_TYPE_MAX)
#define LED_CNTRLER_I2C_ADDRESS	    (0x60)
#define LED_BRIGHTNESS_ON_VALUE     (0x0)
#define LED_BRIGHTNESS_OFF_VALUE    (0x1)


enum led_light_mode {
	LED_MODE_OFF = 0,
	LED_MODE_GREEN,
	LED_MODE_AMBER,
	LED_MODE_RED,
	LED_MODE_BLUE,
	LED_MODE_GREEN_BLINK,
	LED_MODE_AMBER_BLINK,
	LED_MODE_RED_BLINK,
	LED_MODE_BLUE_BLINK,
	LED_MODE_AUTO,
	LED_MODE_UNKNOWN
};

struct accton_as7512_32x_led_data {
	struct platform_device  *pdev;
	struct mutex	        update_lock;
	char		            valid;		/* != 0 if registers are valid */
	unsigned long           last_updated; /* In jiffies */
	u8			            reg_val[NUM_OF_LED_REG];  /* 5 LED registers */
};
struct led_reg_type {
	enum led_type  types;
	u8   reg_addr;
	u8   bit;    
};

/* STATIC VARIABLE DECLARATIONS
 */
static struct accton_as7512_32x_led_data *ledctl = NULL;

static const struct led_reg_type led_reg[NUM_OF_LED_REG] =
{
	{LED_TYPE_DIAG_GREEN,   0x71,  2},
	{LED_TYPE_DIAG_RED,     0x71,  3},	   
	{LED_TYPE_LOC_BLUE,     0x71,  4},	   
	{LED_TYPE_FAN_GREEN,    0x71,  0},	   
	{LED_TYPE_FAN_RED,      0x71,  1},
	{LED_TYPE_PS1_GREEN,    0x70,  2},
    {LED_TYPE_PS1_RED,      0x70,  3},
    {LED_TYPE_PS2_GREEN,    0x70,  0},
    {LED_TYPE_PS2_RED,      0x70,  1},
	{LED_TYPE_FORCE,        0x70,  4},
};

/* EXPORTED SUBPROGRAM DECLARATIONS
 */
extern int accton_i2c_cpld_read (unsigned short cpld_addr, u8 reg);
extern int accton_i2c_cpld_write(unsigned short cpld_addr, u8 reg, u8 value);



static int accton_as7512_32x_led_read_value(u8 reg)
{
	return accton_i2c_cpld_read(LED_CNTRLER_I2C_ADDRESS, reg);
}

static int accton_as7512_32x_led_write_1bit(u8 reg, u8 value, u8 bit)
{
	int status = accton_as7512_32x_led_read_value(reg);

	if (status < 0) {
		dev_dbg(&ledctl->pdev->dev, "reg %d, err %d\n", reg, status);
		return -1;
	}
	status &= ~(1<<bit);
	status |= (value&0x1)<<bit;
	return accton_i2c_cpld_write(LED_CNTRLER_I2C_ADDRESS, reg, status);
}

static int _led_debug_mode(u8 on_off)
{
    return accton_as7512_32x_led_write_1bit(
        led_reg[LED_TYPE_FORCE].reg_addr, 
        on_off,  
        led_reg[LED_TYPE_FORCE].bit);
}



/*
static int accton_as7512_32x_led_write_value(u8 reg, u8 value, u8 mask)
{
	int status = accton_as7512_32x_led_read_value(reg);

	if (status < 0) {
		dev_dbg(&ledctl->pdev->dev, "reg %d, err %d\n", led_reg[i].reg_addr, status);
		return -1;
	}
	status &= mask;
	status |= value;
	return accton_i2c_cpld_write(LED_CNTRLER_I2C_ADDRESS, reg, status);
	
}
*/
static void accton_as7512_32x_led_update(void)
{
	mutex_lock(&ledctl->update_lock);

	if (time_after(jiffies, ledctl->last_updated + HZ + HZ / 2)
		|| !ledctl->valid) {
		int i;

		dev_dbg(&ledctl->pdev->dev, "Starting accton_as7512_32x_led update\n");
		ledctl->valid = 0;

		/* Update LED data
		 */
		for (i = 0; i < ARRAY_SIZE(ledctl->reg_val); i++) {
			int status = accton_as7512_32x_led_read_value(led_reg[i].reg_addr);

			if (status < 0) {
				dev_dbg(&ledctl->pdev->dev, "reg %d, err %d\n", led_reg[i].reg_addr, status);
				goto exit;
			}
			else {
				ledctl->reg_val[i] = status & (led_reg[i].bit <<1);
			}
		}

		ledctl->last_updated = jiffies;
		ledctl->valid = 1;
	}

exit:
	mutex_unlock(&ledctl->update_lock);
}


static void accton_as7512_32x_led_diag_set(struct led_classdev *led_cdev,
										   enum led_brightness led_light_mode)
{
#define NUM_DIAG_LED_CTRL   (2)

    u8 value[NUM_DIAG_LED_CTRL], i;
    struct led_reg_type led_ctrl[NUM_DIAG_LED_CTRL]= 
                {led_reg[LED_TYPE_DIAG_GREEN], led_reg[LED_TYPE_DIAG_RED]};


    switch ((enum led_light_mode)led_light_mode) {
    case LED_MODE_OFF:
            value[0]= value[1] = LED_BRIGHTNESS_OFF_VALUE;
            break;
    case LED_MODE_GREEN:
            value[0] = LED_BRIGHTNESS_ON_VALUE;
            value[1] = LED_BRIGHTNESS_OFF_VALUE;
            break;            
    case LED_MODE_RED:
            value[0] = LED_BRIGHTNESS_OFF_VALUE;
            value[1] = LED_BRIGHTNESS_ON_VALUE;
            break;  
    case LED_MODE_AMBER:
            value[0] = LED_BRIGHTNESS_ON_VALUE;
            value[1] = LED_BRIGHTNESS_ON_VALUE;
            break; 
    default:
            return;
    }
    
	for (i = 0; i < NUM_DIAG_LED_CTRL; i++) {
		accton_as7512_32x_led_write_1bit(
		    led_ctrl[i].reg_addr, value[i], led_ctrl[i].bit);
	}
	return;
	
}

static enum led_brightness accton_as7512_32x_led_diag_get(struct led_classdev *cdev)
{
	u8 is_green_reg_on, is_red_reg_on;

	accton_as7512_32x_led_update();

	is_green_reg_on = 
	    (ledctl->reg_val[LED_TYPE_DIAG_GREEN] == LED_BRIGHTNESS_OFF_VALUE)?0:1;
	is_red_reg_on = 
	    (ledctl->reg_val[LED_TYPE_DIAG_RED] == LED_BRIGHTNESS_OFF_VALUE) ?0:1;

	if (is_green_reg_on && is_red_reg_on) {
	    return LED_MODE_AMBER;
	}
	
	if (is_green_reg_on) {
		return LED_MODE_GREEN;
	}
	
	if (is_red_reg_on) {
		return LED_MODE_RED;
	}

	return LED_MODE_OFF;
}

static void accton_as7512_32x_led_loc_set(struct led_classdev *led_cdev,
										  enum led_brightness led_light_mode)
{
	if (LED_MODE_OFF == (enum led_light_mode)led_light_mode) {
		accton_as7512_32x_led_write_1bit(led_reg[LED_TYPE_LOC_BLUE].reg_addr, 
		                                 LED_BRIGHTNESS_OFF_VALUE,
		                                 led_reg[LED_TYPE_LOC_BLUE].bit);
		return;
	}
	
	if (LED_MODE_BLUE == (enum led_light_mode)led_light_mode) {
		accton_as7512_32x_led_write_1bit(led_reg[LED_TYPE_LOC_BLUE].reg_addr, 
		                                 LED_BRIGHTNESS_ON_VALUE,
		                                 led_reg[LED_TYPE_LOC_BLUE].bit);
		return;
	}	
}

static enum led_brightness accton_as7512_32x_led_loc_get(struct led_classdev *cdev)
{
	accton_as7512_32x_led_update();
	
	if (ledctl->reg_val[LED_TYPE_LOC_BLUE] == LED_BRIGHTNESS_OFF_VALUE) {
		return LED_MODE_OFF;
	}
	
	return LED_MODE_BLUE;
}

static void _accton_as7512_32x_led_set(struct led_classdev *led_cdev,
										   enum led_brightness led_light_mode)
{
    return;
}

static enum led_brightness accton_as7512_32x_led_auto_get(struct led_classdev *cdev)
{
	return LED_MODE_AUTO;
}

static struct led_classdev accton_as7512_32x_leds[] = {
	[0] = {
		.name			 = "accton_as7512_32x_led::diag",
		.default_trigger = "unused",
		.brightness_set	 = accton_as7512_32x_led_diag_set,
		.brightness_get	 = accton_as7512_32x_led_diag_get,
		.flags			 = LED_CORE_SUSPENDRESUME,
		.max_brightness	 = LED_MODE_AUTO,
	},
	[1] = {
		.name			 = "accton_as7512_32x_led::loc",
		.default_trigger = "unused",
		.brightness_set	 = accton_as7512_32x_led_loc_set,
		.brightness_get	 = accton_as7512_32x_led_loc_get,
		.flags			 = LED_CORE_SUSPENDRESUME,
		.max_brightness	 = LED_MODE_AUTO,
	},
	[2] = {
		.name			 = "accton_as7512_32x_led::fan",
		.default_trigger = "unused",
		.brightness_set	 = _accton_as7512_32x_led_set,
		.brightness_get  = accton_as7512_32x_led_auto_get,
		.flags			 = LED_CORE_SUSPENDRESUME,
		.max_brightness  = LED_MODE_AUTO,
	},
	[3] = {
		.name			 = "accton_as7512_32x_led::psu1",
		.default_trigger = "unused",
		.brightness_set	 = _accton_as7512_32x_led_set,
		.brightness_get  = accton_as7512_32x_led_auto_get,
		.flags			 = LED_CORE_SUSPENDRESUME,
		.max_brightness  = LED_MODE_AUTO,
	},
	[4] = {
		.name			 = "accton_as7512_32x_led::psu2",
		.default_trigger = "unused",
		.brightness_set	 = _accton_as7512_32x_led_set,
		.brightness_get  = accton_as7512_32x_led_auto_get,
		.flags			 = LED_CORE_SUSPENDRESUME,
		.max_brightness  = LED_MODE_AUTO,
	},
};

static int accton_as7512_32x_led_suspend(struct platform_device *dev,
		pm_message_t state)
{
	int i = 0;

	for (i = 0; i < ARRAY_SIZE(accton_as7512_32x_leds); i++) {
		led_classdev_suspend(&accton_as7512_32x_leds[i]);
	}

	return 0;
}

static int accton_as7512_32x_led_resume(struct platform_device *dev)
{
	int i = 0;

	for (i = 0; i < ARRAY_SIZE(accton_as7512_32x_leds); i++) {
		led_classdev_resume(&accton_as7512_32x_leds[i]);
	}

	return 0;
}

static int accton_as7512_32x_led_probe(struct platform_device *pdev)
{
	int ret, i;

	for (i = 0; i < ARRAY_SIZE(accton_as7512_32x_leds); i++) {
		ret = led_classdev_register(&pdev->dev, &accton_as7512_32x_leds[i]);

		if (ret < 0)
			break;
	}

	/* Check if all LEDs were successfully registered */
	if (i != ARRAY_SIZE(accton_as7512_32x_leds)){
		int j;

		/* only unregister the LEDs that were successfully registered */
		for (j = 0; j < i; j++) {
			led_classdev_unregister(&accton_as7512_32x_leds[i]);
		}
	}

	return ret;
}

static int accton_as7512_32x_led_remove(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(accton_as7512_32x_leds); i++) {
		led_classdev_unregister(&accton_as7512_32x_leds[i]);
	}

	return 0;
}

static struct platform_driver accton_as7512_32x_led_driver = {
	.probe	 = accton_as7512_32x_led_probe,
	.remove	 = accton_as7512_32x_led_remove,
	.suspend = accton_as7512_32x_led_suspend,
	.resume  = accton_as7512_32x_led_resume,
	.driver  = {
		.name	= DRVNAME,
		.owner	= THIS_MODULE,
	},
};

static int __init accton_as7512_32x_led_init(void)
{
	int ret;

	extern int platform_accton_as7512_32x(void);
	if (!platform_accton_as7512_32x()) {
		return -ENODEV;
	}	
	
	ret = platform_driver_register(&accton_as7512_32x_led_driver);
	if (ret < 0) {
		goto exit;
	}

	ledctl = kzalloc(sizeof(struct accton_as7512_32x_led_data), GFP_KERNEL);
	if (!ledctl) {
		ret = -ENOMEM;
		platform_driver_unregister(&accton_as7512_32x_led_driver);
		goto exit;
	}

	mutex_init(&ledctl->update_lock);

	ledctl->pdev = platform_device_register_simple(DRVNAME, -1, NULL, 0);
	if (IS_ERR(ledctl->pdev)) {
		ret = PTR_ERR(ledctl->pdev);
		platform_driver_unregister(&accton_as7512_32x_led_driver);
		kfree(ledctl);
		goto exit;
	}

exit:
	return ret;
}

static void __exit accton_as7512_32x_led_exit(void)
{
	platform_device_unregister(ledctl->pdev);
	platform_driver_unregister(&accton_as7512_32x_led_driver);
	kfree(ledctl);
}

module_init(accton_as7512_32x_led_init);
module_exit(accton_as7512_32x_led_exit);

MODULE_AUTHOR("Brandon Chuang <brandon_chuang@accton.com.tw>");
MODULE_DESCRIPTION("accton_as7512_32x_led driver");
MODULE_LICENSE("GPL");
