
unsigned int channel_voltage[8];
unsigned char channel_conv;
unsigned char channel_display = 0;
unsigned int channel_limit[] = {0,0,0,0,0,0,0,0};
unsigned char channel_limit_flags[] = {0,0,0,0,0,0,0,0};

void auto_dsp();
void man_dsp();
void incr_channel();
void decr_channel();
void null_fcn();
void incr_10();
void decr_10();
void incr_1();
void decr_1();

void DG528_driver(unsigned char channel);
unsigned int ADC161_conv(void);
