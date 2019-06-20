#ifndef DATE_TYPE_H
#define DATE_TYPE_H

class date_type
{
private:
    int x,y;
    char a,b;
    float xx,yy;
public:
    date_type();
   void input();
   void show(char aa,char bb);
   void show(int xx1,int yy1);
   void show(float xx1,float yy1);
};

#endif // DATE_TYPE_H
