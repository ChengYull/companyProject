//
// Created by Administrator on 24-8-5.
//

#ifndef COMMENSTAFF_H
#define COMMENSTAFF_H
#include <string>

#include "Staff.h"


class CommenStaff:public Staff {
    const char duty[30] = "完成经理交给的任务";
public:
    CommenStaff();
    CommenStaff(int staffNum,char * name,int post);
    void display() override;

    std::string getPost();
};



#endif //COMMENSTAFF_H
