#include<reg51.h>
#define dataport P2
#define adc_input P0
sbit rs = P3^0;
sbit rw = P3^1;
sbit e = P3^2;
sbit wr= P3^3;
sbit rd= P3^4;
sbit intr= P3^5;
void delay(unsigned int);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_data_string(unsigned char*);
void lcd_init();
void adc_conv();
void adc_read();
void lcd_data_adc(unsigned int);
int num[10];
void main()
{
while(1)
{
dataport=0x00;
adc_input=0xff;
P3=0x00;
lcd_init();
lcd_data_string("TEMPERATURE=");
adc_conv();
adc_read();
lcd_data('C');
delay(50);
 }
}
void lcd_init()
{
lcd_cmd(0x01);
delay(1);
lcd_cmd(0x06);
delay(1);
lcd_cmd(0x0e);
delay(1);
lcd_cmd(0x38);
delay(1);
lcd_cmd(0x80);
delay(1);
}
void delay(unsigned int sec )
{
int i ,j ;
for(i=0;i<sec;i++)
  for(j=0; j<1275; j++);
}
void lcd_cmd(unsigned char item)
{
dataport=item;
rs= 0;
rw=0;
e=1;
delay(1);
e=0;
return;
}
void lcd_data(unsigned char item) 
{
dataport = item;
rs= 1;
rw=0;
e=1;
delay(1);
e=0;
}
void adc_conv()
{                      
wr = 0;
delay(2);                     
wr = 1;                     
while(intr);
delay(2);
intr=1; 
}
void adc_read()
{
unsigned int value;                  
rd = 0;
delay(2);
value=adc_input;
delay(1);
rd=1; 
lcd_data_adc(value);                                          
}
void lcd_data_adc(unsigned int i)
{
int p;
int k=0;
while(i>0)
{
  num[k]=i%10;
  i=i/10;
  k++;
}
k--;
for (p=k;p>=0;p--)
{
dataport=num[p]+48;
rw = 0;
rs = 1;
e = 1;
delay(1);
e = 0;
}
}
void lcd_data_string(char *x)
{
    while(*x!='\0')
    {
        lcd_data(*x);
        delay(2);
        x++;
    }
}