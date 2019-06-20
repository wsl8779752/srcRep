#ifndef CPU_H
#define CPU_H
enum cpu_word{
    word_32,
    word_42
};

enum cpu_core{
    single_core,
    double_core,
    quotra_core
};

class cpu
{

private:
    unsigned cpu_clock :32;
    cpu_word word :1 ;
    cpu_core core :2 ;
    unsigned flag_of_xiancheng : 1;
public:
    cpu();
};

#endif // CPU_H
