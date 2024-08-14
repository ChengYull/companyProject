//
// Created by Administrator on 24-8-5.
//

#ifndef STAFF_H
#define STAFF_H



class Staff {
public:
    int staffNum;
    char * name;
    int postNum;

    Staff();
    Staff(int staffNum,const char *name,int postNum);
    ~Staff();
    virtual void display() = 0;
};



#endif //STAFF_H
