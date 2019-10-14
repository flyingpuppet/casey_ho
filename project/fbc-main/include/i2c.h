#ifndef __FBC_I2C_H__
#define __FBC_I2C_H__

//#define I2C_DEBUG				0x1

#define I2C_MASTER_MODULE_A		0x0

#define I2C_MASTER_MODULE_B		0x1

#define I2C_MASTER_SPEED_100K	100000

#define I2C_MASTER_SPEED_300K	300000

#define I2C_MASTER_SPEED_400K	400000

#define I2C_MASTER_IDLE_STATUS	0x0

#define I2C_MASTER_ERROR_STATUS	0x3

#define I2C_MASTER_RUNNING_STATUS	0x1

#define FBC_I2C_MAX_TOKENS	0x8

#define TAS5707_I2C_ADDR	0x36

#define AT24C64_I2C_ADDR	0xA0

#define I2C_SUSPEND_SPEED    6                  // speed = 8KHz / I2C_SUSPEND_SPEED

#define I2C_CTRL_CLK_DELAY_MASK			0x3ff
#define I2C_SLAVE_ADDR_MASK				0xff
#define I2C_SLAVE_ADDR_MASK_7BIT		0x7F

#define I2C_STATUS		(1<<2)
#define I2C_IDLE		0
#define I2C_RUNNING		1

#define I2C_M_TEN		       	0x0010	/* this is a ten bit chip address */
#define I2C_M_RD		       	0x0001	/* read data, from slave to master */
#define I2C_M_NOSTART		   	0x4000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_REV_DIR_ADDR		0x2000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK	 	0x1000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NO_RD_ACK		 	0x0800	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_RECV_LEN		 	0x0400	/* length will be first received byte */

enum fbc_i2c_token {
	TOKEN_END,
	TOKEN_START,
	TOKEN_SLAVE_ADDR_WRITE,
	TOKEN_SLAVE_ADDR_READ,
	TOKEN_DATA,
	TOKEN_DATA_LAST,
	TOKEN_STOP
};



enum {
	EINVAL = -3,
	I2C_S_BUSY = -2,
	I2C_S_TIMEOUT = -1,
	I2C_S_OK = 0,
};

struct i2c_msg {
	unsigned short addr;	// slave address
	unsigned short flags;
	unsigned short len;		// msg length
	unsigned char *buf;		// pointer to msg data
};

struct i2c_master_regs {
	volatile unsigned long *i2c_ctrl;
	volatile unsigned long *i2c_slave_addr;
	volatile unsigned long *i2c_token_list_0;
	volatile unsigned long *i2c_token_list_1;
	volatile unsigned long *i2c_token_wdata_0;
	volatile unsigned long *i2c_token_wdata_1;
	volatile unsigned long *i2c_token_rdata_0;
	volatile unsigned long *i2c_token_rdata_1;
};

struct fbc_i2c {
	unsigned short master_no;
	unsigned char token_tag[FBC_I2C_MAX_TOKENS];
	int wait_count;
	int wait_ack_interval;
	int wait_read_interval;
	int wait_xfer_interval;
	int cur_token;
	int speed;
	int msg_flags;
	unsigned cur_slave_addr;
	struct i2c_master_regs *master_regs;
	struct i2c_ops *ops;
};

struct i2c_ops {
     void (*xfer_prepare)(struct fbc_i2c *i2c);
	 int  (*do_address)(struct fbc_i2c *i2c, unsigned int addr);
	 int  (*read)(struct fbc_i2c *i2c, unsigned char *buf, unsigned int len);
	 int  (*write)(struct fbc_i2c *i2c, unsigned char *buf, unsigned int len);
	 void (*stop)(struct fbc_i2c *i2c);
};

int i2c_transfer(struct fbc_i2c *i2c, struct i2c_msg *msgs, int num);

int codec_read_byte(unsigned addr, unsigned char reg_addr, unsigned char *data);
int codec_write_byte(unsigned addr, unsigned char reg_addr, unsigned char data);

int codec_write(unsigned addr, unsigned char r_addr, unsigned char *buf, unsigned len);
int codec_read(unsigned addr, unsigned char r_addr, unsigned char *buf, unsigned len);

#endif //__FBC_I2C_H__
