#include<reg51.h>
sbit rs=P1^0; 
sbit rw=P1^1; 
sbit e=P1^2; 
sbit quarter_tank=P3^0; //pin connected to quarter level of tank
sbit half_tank=P3^1; //pin connected to half level of tank
sbit three_fourth=P3^2; //pin connected to three-fourth level of tank
sbit full_tank=P3^3; //pin connected to full level of tank
sbit spkr_on=P3^4;  
sbit spkr_off=P3^5; 

void delay(int k)
{
int i,j;
for(i=0;i<k;i++)
  for(j=0;j<1275;j++);
}

void write(int j)
{
rs=1;  
rw=0;  
P2=j;  
e=1;  
delay(1);
e=0;
return;
}

void cmd(int j)
{
P2=j; 
rs=0; 
rw=0; 
e=1;  
delay(1);
e=0;
return;
}

void puts(char *a) 
{
unsigned int p=0;
for(;a[p]!=0;p++)
write(a[p]);
}

void lcd_init(void) 
{
cmd(0x38);
delay(1);
cmd(0x0e);
delay(1); 
cmd(0x01);
cmd(0x80);
}

void main()
{
quarter_tank=half_tank=three_fourth=full_tank=spkr_off=1; 
quarter_tank=half_tank=three_fourth=full_tank=spkr_off=0; 
spkr_on=1;  //negative logic speaker
while(1)
{
  while(quarter_tank==0&&half_tank==0&&three_fourth==0&&full_tank==0&&spkr_off==0)  
  {
   lcd_init();        
   puts("vacant");    
  }
  while(quarter_tank==1&&half_tank==0&&three_fourth==0&&full_tank==0&&spkr_off==0)	
  {
   lcd_init();
   puts("Quarter");   
  }
  while(quarter_tank==1&&half_tank==1&&three_fourth==0&&full_tank==0&&spkr_off==0)	
  {
   lcd_init();     
   puts("HALF"); 
  }
  while(quarter_tank==1&&half_tank==1&&three_fourth==1&&full_tank==0&&spkr_off==0)
  {
   lcd_init();
   puts("3/4 FULL");     
  }
  while(quarter_tank==1&&half_tank==1&&three_fourth==1&&full_tank==1&&spkr_off==0)	
  {
   lcd_init();
   puts("FULL");    
   spkr_on=0;
  }
}
}