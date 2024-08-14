//
// Created by Administrator on 24-8-5.
//

#ifndef BOSS_H
#define BOSS_H
#include <string>

#include "Staff.h"


class Boss:public Staff{
    const char duty[30] = "管理公司所有事务";
public:
    Boss();
    Boss(int staffNum, char *name, int post);
    void display() override;
    std::string getPost();
};



#endif //BOSS_H
