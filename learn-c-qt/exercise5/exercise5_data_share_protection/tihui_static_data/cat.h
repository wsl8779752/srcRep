#ifndef CAT_H
#define CAT_H

class Cat1
{
private:
    int age, gender;
    static int num_of_cat;
public:
    Cat1(int x,int y);
    static int get_num_of_cat();
};

#endif // CAT_H
