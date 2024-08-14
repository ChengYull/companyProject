//
// Created by Administrator on 24-8-5.
//

#ifndef MANGER_H
#define MANGER_H
#include <string>

#include "Staff.h"


class Manger:public Staff {
    const char duty[30] = "下发任务给员工";
public:
    Manger();
    Manger(int staffNum, char *name, int post);
    void display() override;
    std::string getPost();
};



#endif //MANGER_H
