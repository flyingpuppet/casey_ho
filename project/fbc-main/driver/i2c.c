#include <i2c.h>
#include <serial.h>
#include <c_arc_pointer_reg.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <command.h>
#include <common.h>

#define MAX_WRITE_DATA_SIZE		0x40

#define min_t(type, x, y) ({			\
	type __min1 = (x);			\
	type __min2 = (y);			\
	__min1 < __min2 ? __min1 : __min2; })

#define max_t(type, x, y) ({			\
	type __max1 = (x);			\
	type __max2 = (y);			\
	__max1 > __max2 ? __max1 : __max2; })

void fbc_i2c_stop(struct fbc_i2c *i2c);
void i2c_xfer_prepare(struct fbc_i2c *i2c);
int i2c_do_address(struct fbc_i2c *i2c, unsigned int addr);
int aml_i2c_write(struct fbc_i2c *i2c, unsigned char *buf, unsigned len);
int aml_i2c_read(struct fbc_i2c *i2c, unsigned char *buf, unsigned len);

static struct i2c_master_regs i2c_master_regs_a = {
	.i2c_ctrl = P_I2C_M_0_CONTROL_REG,
	.i2c_slave_addr = P_I2C_M_0_SLAVE_ADDR,
	.i2c_token_list_0 = P_I2C_M_0_TOKEN_LIST0,
	.i2c_token_list_1 = P_I2C_M_0_TOKEN_LIST1,
	.i2c_token_wdata_0 = P_I2C_M_0_WDATA_REG0,
	.i2c_token_wdata_1 = P_I2C_M_0_WDATA_REG1,
	.i2c_token_rdata_0 = P_I2C_M_0_RDATA_REG0,
	.i2c_token_rdata_1 = P_I2C_M_0_RDATA_REG1

};

static struct i2c_master_regs i2c_master_regs_b = {
	.i2c_ctrl = P_I2C_M_1_CONTROL_REG,
	.i2c_slave_addr = P_I2C_M_1_SLAVE_ADDR,
	.i2c_token_list_0 = P_I2C_M_1_TOKEN_LIST0,
	.i2c_token_list_1 = P_I2C_M_1_TOKEN_LIST1,
	.i2c_token_wdata_0 = P_I2C_M_1_WDATA_REG0,
	.i2c_token_wdata_1 = P_I2C_M_1_WDATA_REG1,
	.i2c_token_rdata_0 = P_I2C_M_1_RDATA_REG0,
	.i2c_token_rdata_1 = P_I2C_M_1_RDATA_REG1

};

static struct i2c_ops gI2C_OPS = {	
		.xfer_prepare = i2c_xfer_prepare,
		.do_address = i2c_do_address,
		.read = aml_i2c_read,
		.write = aml_i2c_write,
		.stop = fbc_i2c_stop,
};

static struct fbc_i2c fbc_i2c_master_a = {
	.master_no = I2C_MASTER_MODULE_A,
	.wait_count = 10,
	.wait_ack_interval = 1,
	.wait_read_interval = 5,
 	.wait_xfer_interval = 5,
 	.speed = I2C_MASTER_SPEED_300K,
	.master_regs = &i2c_master_regs_a
};

static struct fbc_i2c fbc_i2c_master_b = {
	.master_no = I2C_MASTER_MODULE_B,
	.wait_count = 10,
	.wait_ack_interval = 1,
	.wait_read_interval = 5,
 	.wait_xfer_interval = 5,
 	.speed = I2C_MASTER_SPEED_300K,
	.master_regs = &i2c_master_regs_b,
	.ops = &gI2C_OPS,
};

//udelay --- system clock 200M.
static void udelay(int us)
{
	 register int n= (us)*105;
	 while(n--);
}

static void set_i2c_master_pin_mux(unsigned char i2c_m_module)
{
	if(I2C_MASTER_MODULE_A == i2c_m_module)
	{
		(*P_PERIPHS_PIN_MUX_0) &= (~(1 << 20)); 
		(*P_PERIPHS_PIN_MUX_0) &= (~(1 << 21));
		(*P_PERIPHS_PIN_MUX_0) |= ((1 << 9) | (1 << 8));
	}
	else
	{
		(*P_PERIPHS_PIN_MUX_4) |= ((1 << 1) | (1 << 0));
	}
	
	return;
}

static void clear_i2c_token_list(struct fbc_i2c *i2c)
{
	*(i2c->master_regs->i2c_token_list_0) = 0;
	*(i2c->master_regs->i2c_token_list_1) = 0;
	memset(i2c->token_tag, TOKEN_END, FBC_I2C_MAX_TOKENS);
	return;
}

static void set_i2c_token_list(struct fbc_i2c *i2c)
{
	int i;
	unsigned long token_reg = 0;

	for(i=0; i<FBC_I2C_MAX_TOKENS; i++)
	{
		token_reg |= i2c->token_tag[i] << (i*4);
	}
	*(i2c->master_regs->i2c_token_list_0) = token_reg;
	
	return;
}

static void start_i2c_token_xfer(struct fbc_i2c *i2c)
{
	*(i2c->master_regs->i2c_ctrl) &= ~1;	// clear
	*(i2c->master_regs->i2c_ctrl) |= 1;	// set
//	udelay(i2c->wait_xfer_interval);

	return;
}

static void fbc_i2c_stop(struct fbc_i2c *i2c)
{
	if(!i2c) return;
	
	clear_i2c_token_list(i2c);
	i2c->token_tag[0] = TOKEN_STOP;
	set_i2c_token_list(i2c);
	start_i2c_token_xfer(i2c);

	return;
}

static void i2c_xfer_prepare(struct fbc_i2c *i2c)
{
	if(!i2c) return;
	
	set_i2c_master_pin_mux(i2c->master_no);
	set_i2c_master_speed(i2c);
	
	return;
}

static int i2c_do_address(struct fbc_i2c *i2c, unsigned int addr)
{   
    i2c->cur_slave_addr = addr;

#ifdef	I2C_DEBUG
	printf("i2c->cur_slave_addr: 0x%x, addr: 0x%x\n", i2c->cur_slave_addr, addr);
#endif	
    *(i2c->master_regs->i2c_slave_addr) &= (~I2C_SLAVE_ADDR_MASK);
	
    *(i2c->master_regs->i2c_slave_addr) |= i2c->cur_slave_addr;
	
    return 0;
}

static void fbc_i2c_fill_data(struct fbc_i2c *i2c, unsigned char *buf, unsigned len)
{
	int i;
	unsigned long wdata0 = 0;
	unsigned long wdata1 = 0;

	for(i=0; i< min_t(unsigned, len, FBC_I2C_MAX_TOKENS>>1); i++)
		wdata0 |= (*buf++) << (i*8);

	for(; i< min_t(unsigned, len, FBC_I2C_MAX_TOKENS); i++)
		wdata1 |= (*buf++) << ((i - (FBC_I2C_MAX_TOKENS>>1))*8);

	*(i2c->master_regs->i2c_token_wdata_0) = wdata0;
	*(i2c->master_regs->i2c_token_wdata_1) = wdata1;
	return;
}

static int fbc_i2c_wait_ack(struct fbc_i2c *i2c)
{
	int i = 0;
	int btime = 1000000 * 9 / i2c->speed + 10;
	
	for(i=0; i <= i2c->wait_count*btime*100; i++)
	{
		if(!(*(i2c->master_regs->i2c_ctrl) & (1<<I2C_M_STATUS)))
		{
#ifdef	I2C_DEBUG
			printf("btime: %d, i: %d\n", btime, i);
#endif

			return I2C_S_OK;
		}
		
		udelay(i2c->wait_ack_interval);
		
	}
	
#ifdef	I2C_DEBUG
	printf("status: 0x%x\n", *(i2c->master_regs->i2c_ctrl));
#endif

	return I2C_S_TIMEOUT;

}

static void fbc_i2c_get_read_data(struct fbc_i2c *i2c, unsigned char *buf, unsigned len)
{
	int i;
	unsigned long rdata0 = *(i2c->master_regs->i2c_token_rdata_0);
	unsigned long rdata1 = *(i2c->master_regs->i2c_token_rdata_1);
	
#ifdef	I2C_DEBUG
	printf("rdata0: 0x%x, rdata1: 0x%x\n", rdata0, rdata1);
#endif

	for(i=0; i< min_t(unsigned, len, FBC_I2C_MAX_TOKENS >> 1); i++)
	{
		*buf++ = (rdata0 >> (i*8)) & 0xff;
	}

	for(; i< min_t(unsigned, len, FBC_I2C_MAX_TOKENS); i++)
	{
		*buf++ = (rdata1 >> ((i - (FBC_I2C_MAX_TOKENS >>1 )) * 8)) & 0xff;
	}

	return;

}

struct fbc_i2c *get_i2c_master(unsigned char i2c_m_module)
{
	if(I2C_MASTER_MODULE_A == i2c_m_module)
	{
		return &fbc_i2c_master_a;
	}
	else
	{
		return &fbc_i2c_master_b;
	}
}

int set_i2c_master_speed(struct fbc_i2c *i2c)
{
	unsigned sys_clk = clk_get_rate(0x1);
	unsigned i2c_clock_set = sys_clk / i2c->speed;
	
	if(!i2c) return EINVAL;

	i2c_clock_set >>= 1;

	if (i2c_clock_set > 0xfff) i2c_clock_set = 0xfff;
	
	*(i2c->master_regs->i2c_ctrl) &= (~((0x3 << 28) | (0x3ff << I2C_M_DELAY_LSB)));
	*(i2c->master_regs->i2c_ctrl) |= ((i2c_clock_set & 0x3ff) << I2C_M_DELAY_LSB);
	*(i2c->master_regs->i2c_ctrl) |= ((i2c_clock_set >> 10) << 28);
	
	*(i2c->master_regs->i2c_slave_addr) &= (~(0xfff << 16));
	*(i2c->master_regs->i2c_slave_addr) |= ((i2c_clock_set >> 1) << 16);
	*(i2c->master_regs->i2c_slave_addr) |= 1 << 28;
	
	return 0;
}

static int aml_i2c_read(struct fbc_i2c *i2c, unsigned char *buf, unsigned len)
{
	int i;
	int ret;
	unsigned rd_len;
	int tagnum = 0;

	if(!buf || !len) return EINVAL;
	
	clear_i2c_token_list(i2c);

	if(!(i2c->msg_flags & I2C_M_NOSTART))
	{
	
#ifdef	I2C_DEBUG
		printf("aml_i2c_read rlen: %d\n", len);
#endif

		i2c->token_tag[tagnum++] = TOKEN_START;
		i2c->token_tag[tagnum++] = TOKEN_SLAVE_ADDR_READ;

		set_i2c_token_list(i2c);
		
		start_i2c_token_xfer(i2c);

		ret = fbc_i2c_wait_ack(i2c);
		if(ret<0)
			return ret;
		
		clear_i2c_token_list(i2c);
	}

	while(len)
	{
		tagnum = 0;
		rd_len = min_t(unsigned, len, FBC_I2C_MAX_TOKENS);
		if(rd_len == 1)
		{
			i2c->token_tag[tagnum++] = TOKEN_DATA_LAST;
		}
		else
		{
			for(i=0; i<rd_len-1; i++)
				i2c->token_tag[tagnum++] = TOKEN_DATA;
			
			if(len > rd_len)
				i2c->token_tag[tagnum++] = TOKEN_DATA;
			else
				i2c->token_tag[tagnum++] = TOKEN_DATA_LAST;
		}

		set_i2c_token_list(i2c);
		start_i2c_token_xfer(i2c);

		ret = fbc_i2c_wait_ack(i2c);
		
#ifdef	I2C_DEBUG
		printf("ret: %d\n", ret);
#endif

		if(ret<0)
			return ret;
		
		fbc_i2c_get_read_data(i2c, buf, rd_len);
		
		len -= rd_len;
		buf += rd_len;

		clear_i2c_token_list(i2c);
	}
	
	return 0;
}


static int aml_i2c_write(struct fbc_i2c *i2c, unsigned char *buf, unsigned len)
{
    int i;
    int ret;
    unsigned wr_len;
	int tagnum = 0;
	
	if(!buf || !len) return EINVAL;
	
	clear_i2c_token_list(i2c);
	
	if(!(i2c->msg_flags & I2C_M_NOSTART))
	{
#ifdef	I2C_DEBUG
		printf("aml_i2c_write wlen: %d\n", len);
#endif

		i2c->token_tag[tagnum++] = TOKEN_START;
		i2c->token_tag[tagnum++] = TOKEN_SLAVE_ADDR_WRITE;
	}
	
	while(len)
	{
		wr_len = min_t(unsigned, len, FBC_I2C_MAX_TOKENS - tagnum);
		
		for(i=0; i<wr_len; i++)
			i2c->token_tag[tagnum++] = TOKEN_DATA;

		set_i2c_token_list(i2c);

		fbc_i2c_fill_data(i2c, buf, wr_len);

		start_i2c_token_xfer(i2c);

		len -= wr_len;
		buf += wr_len;
		tagnum = 0;

		ret = fbc_i2c_wait_ack(i2c);
		if(ret<0)
			return ret;

		clear_i2c_token_list(i2c);

	}
	
	return 0;
}

//General i2c master transfer
int i2c_transfer(struct fbc_i2c *i2c, struct i2c_msg *msgs, int num)
{
	struct i2c_msg *p = 0;
	unsigned int i;
	unsigned int ret = 0;	
	
	i2c->ops->xfer_prepare(i2c);

	for(i = 0; !ret && i < num; i++)
	{
		p = &msgs[i];
		i2c->msg_flags = p->flags;
		
		ret = i2c->ops->do_address(i2c, p->addr);
		if (ret || !p->len)
		{
			continue;
		}
		
		if (p->flags & I2C_M_RD)
		{
			ret = i2c->ops->read(i2c, p->buf, p->len);
		}
		else
		{
			ret = i2c->ops->write(i2c, p->buf, p->len);
		}
	}
	
	i2c->ops->stop(i2c);

	//Return the number of messages processed, or the error code
//	if (ret == 0)
//		return num;
//	else
	return ret;
	
}

int codec_write(unsigned addr, unsigned char r_addr, unsigned char *buf, unsigned len)
{
	int ret;
	struct fbc_i2c *i2c;
	unsigned char *buff;
	
	if(!buf || !len) return EINVAL;

	buff = (unsigned char *)malloc(len + 1);

	memset(buff, 0, len+1);
	buff[0] = r_addr;
	memcpy(buff + 1, buf, len);
	
	i2c = get_i2c_master(I2C_MASTER_MODULE_B);

	struct i2c_msg msg[] = {
    	{
        	.addr = addr,
        	.flags = 0,
        	.len = len + 1,
        	.buf = buff,
    	},
    	
	};

	ret = i2c_transfer(i2c, msg, 1);

	free(buff);
	
	return ret;
}

int codec_write_byte(unsigned dev_addr, unsigned char r_addr, unsigned char data)
{
	return codec_write(dev_addr, r_addr, &data, 1);
}

int codec_read(unsigned addr, unsigned char r_addr, unsigned char *buf, unsigned len)
{
	int ret;
	struct fbc_i2c *i2c;
	
	if(!buf || !len) return EINVAL;
	
	i2c = get_i2c_master(I2C_MASTER_MODULE_B);

	struct i2c_msg msg[] = {
    	{
        	.addr = addr,
        	.flags = 0,
        	.len = 1,
        	.buf = &r_addr,
    	},
    	{
        	.addr = addr,
        	.flags = 1,
        	.len = len,
        	.buf = buf,
    	},
    	
	};

	ret = i2c_transfer(i2c, msg, 2);
	
	return ret;
}

int codec_read_byte(unsigned addr, unsigned char r_addr, unsigned char *data)
{
	return codec_read(addr, r_addr, data, 1);
	
}

int do_i2c_test(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned char addr;
	unsigned char reg;
	unsigned char buf[64] = {0};
	unsigned len, i;

	if(argc < 2) return cmd_usage(cmdtp);

	struct fbc_i2c *i2c = get_i2c_master(I2C_MASTER_MODULE_B);
	

	if(!strcmp(argv[1], "-r"))
	{
		printf("i2c read.\n");
		
		if(argc < 5) return cmd_usage(cmdtp);

		addr = strtoul(argv[2], NULL, 16);
		reg = strtoul(argv[3], NULL, 16);
		len = strtoul(argv[4], NULL, 16);
		buf[0] = reg;
		
		printf("addr: 0x%x, reg: 0x%x, len: %d\n", addr, reg, len);
		
		struct i2c_msg msg[] = {
        	{
            	.addr = addr,
            	.flags = 0,
            	.len = 1,             //I2C data address length.
            	.buf = buf,
        	},
        	{
            	.addr = addr,
            	.flags = 1,
            	.len = len,                //read 1 byte from I2C data address.
            	.buf = buf,
        	}
    	};

		i2c_transfer(i2c, msg, 2);
		
		for(i=0; i<len; i++)
		{
			printf("reg[%x]: 0x%x\n", reg+i, buf[i]);
		}
		
	}
	else if(!strcmp(argv[1], "-w"))
	{
		printf("i2c write.\n");
		
		if(argc < 4) return cmd_usage(cmdtp);
		
		addr = strtoul(argv[2], NULL, 16);
		len = 0;
		
		for(i=3; i<argc; i++)
		{
			buf[i-3] = strtoul(argv[i], NULL, 16);
			len++;
		}
		
		struct i2c_msg msg[] = {
        	{
            	.addr = addr,
            	.flags = 0,
            	.len = len,
            	.buf = buf,
        	},
        	
    	};
		printf("addr: 0x%x, reg: 0x%x, len: %d\n", addr, buf[0], len);
		
		i2c_transfer(i2c, msg, 1);
		
	}else if(!strcmp(argv[1], "-wcodec"))
	{
		printf("i2c write codec.\n");
		
		if(argc < 5) return cmd_usage(cmdtp);

		addr = strtoul(argv[2], NULL, 16);
		reg = strtoul(argv[3], NULL, 16);
		
		len = 0;
		
		for(i=4; i<argc; i++)
		{
			buf[i-4] = strtoul(argv[i], NULL, 16);
			len++;
		}

		if(len == 1)
		{
			printf("codec_write_byte.\n");
			codec_write_byte(addr, reg, buf[0]);
		}
		else
		{
			printf("codec_write.\n");
			codec_write(addr, reg, buf, len);
		}
		
	}
	else if(!strcmp(argv[1], "-rcodec"))
	{
		printf("i2c write codec.\n");
		
		if(argc < 5) return cmd_usage(cmdtp);

		addr = strtoul(argv[2], NULL, 16);
		reg = strtoul(argv[3], NULL, 16);
		len = strtoul(argv[4], NULL, 16);
		
		if(len == 1)
		{
			printf("codec_read_byte.\n");
			codec_read_byte(addr, reg, buf);
		}
		else
		{
			printf("codec_read.\n");
			codec_read(addr, reg, buf, len);
		}

		for(i=0; i<len; i++)
		{
			printf("reg[%x]: 0x%x\n", reg+i, buf[i]);
		}
		
	}
	
	return 0;
}

