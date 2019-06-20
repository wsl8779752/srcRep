#include "ads1115.h" 
/*悦得机器人的ads1115配置如下：*/
/*总共有3个ads1115 设备，地址位分别接的是GND，VCC和SCL，故地址是ADDRESS_0 1 3*/
/*每个器件的4个通道分别接的是输入与GND，所以多路输入为MUX_4 5 6 7*/
/*器件工作模式为单次转换，禁止比较器，最大量程（FSR）为6.144V，速率为128 SPS*/
/*由以上的设定，可以设置配置寄存器的高8位可以配置 OS_1+ MUX_4（or5 6 7）+ PGA0 +MODE_1 = 0XC1*/
/*低8位配置为DR_7(860sps)+ COMP_MODE_0 + COMOP_POL_0 + COMP_LAT_0 + COM_QUE_3 = 0xe3*/
void yuedeAds1115PortInit(){
    SCL_DDR_OUT;                                                                
    SDA_DDR_OUT; 
    SDA_H;
}
void ads1115ConfigRegister(unsigned char addr,unsigned char port){
    static unsigned char chnel,writeaddr;
    switch (addr) { 
        case 0: { writeaddr = ADDRESS_0; }//对应接地的ads1115 
                break; 
        case 1: { writeaddr = ADDRESS_1;} //对应接vcc的器件  
                break; 
        case 2: { writeaddr = ADDRESS_2; }//对应接SDA的器件,实际上悦得的板子用不到  
                break; 
        default: { writeaddr = ADDRESS_3;} //对应接SCL的器件  
                 break; 
    } 
    switch (port)
    {
        case 0: chnel=0xC1; break;//启动一次转换，AIN0与GND，量程6.144V，单次模式
        case 1: chnel=0xD1; break;//通道设置为AIN1与GND，其他同上
        case 2: chnel=0xE1; break;//通道设置为AIN2与GND，其他同上
        case 3: chnel=0xF1; break;//通道设置为AIN3与GND，其他同上
        default:;break; 
    }
    Writebuff[0] = writeaddr;
    Writebuff[1] = Pointer_1;
    Writebuff[2] = chnel;
    Writebuff[3] = 0xe3 ;  //860sps,禁用比较器,转换需要大约1.2ms
    WriteWord();
}
static void PointRegister (unsigned char addr)
{
    static unsigned char writeaddr;
    switch (addr) { 
        case 0: { writeaddr = ADDRESS_0; }//对应接地的ads1115 
                break; 
        case 1: { writeaddr = ADDRESS_1;} //对应接vcc的器件  
                break; 
        case 2: { writeaddr = ADDRESS_2; }//对应接SDA的器件,实际上悦得的板子用不到  
                break; 
        default: { writeaddr = ADDRESS_3;} //对应接SDA的器件  
                 break; 
    } 
    Writebuff[0] = writeaddr; //90
    Writebuff[1] = Pointer_0; //00
    WriteWord();  
}
