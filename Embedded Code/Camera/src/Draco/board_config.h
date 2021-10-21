#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#define INPUT
#define OUTPUT


/***************** IO MUX ********************/
/* lcd panel */
#define LCD_CS_PIN_NUM			43

#define LCD_RST_PIN_NUM			41
#define LCD_RST_FUNC_GPIOHS_NUM		2

#define LCD_DCX_PIN_NUM			44
#define LCD_DCX_FUNC_GPIOHS_NUM		3

#define LCD_WR_PIN_NUM			45
#define LCD_RD_PIN_NUM			46

#ifdef LCD_TE_FMARK
#define LCD_FMARK_PIN_NUM		42
#define LCD_FMARK_FUNC_GPIOHS_NUM	4
#endif

/* cmos sensor dvp */
#define CMOS_PCLK_PIN_NUM		8
#define CMOS_XCLK_PIN_NUM		9
#define CMOS_HREF_PIN_NUM		10
#define CMOS_VSYNC_PIN_NUM		12

#define CMOS_RST_PIN_NUM		13
#define CMOS_RST_FUNC_GPIOHS_NUM	5
#define CMOS_PWDN_PIN_NUM           11
#define CMOS_PWDN_FUNC_GPIOHS_NUM   4

#define CMOS_I2C_SCLK_PIN_NUM	14
#define CMOS_I2C_SDA1_PIN_NUM	0
#define CMOS_I2C_SDA2_PIN_NUM	15

/* ir light control */
#define IR_LED_PIN_NUM			30
#define IR_LED_FUNC_GPIOHS_NUM		9

//backlight
#define LCD_BL_ENABLE
#ifdef LCD_BL_ENABLE
#define LCD_BL_PIN_NUM			47
#define LCD_BL_FUNC_GPIOHS_NUM		8
#endif

/*  Uart  */
#define UART_RX_PIN_NUM			4
#define UART_TX_PIN_NUM			5

#endif /* _BOARD_CONFIG_H_ */
