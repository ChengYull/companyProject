//
// Created by Administrator on 24-8-5.
//

#ifndef STAFF_H
#define STAFF_H
#include <string>


class Staff {
public:
    int staffNum;
    std::string name;
    int postNum;

    Staff();
    Staff(int staffNum, const std::string &name,int postNum);
    virtual ~Staff();
    virtual void display() = 0;
};



#endif //STAFF_H
