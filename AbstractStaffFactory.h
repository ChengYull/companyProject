//
// Created by Administrator on 24-8-16.
//

#ifndef ABSTRACTSTAFFFACTORY_H
#define ABSTRACTSTAFFFACTORY_H
#include "Staff.h"

class AbstractStaffFactory {
public:
    virtual Staff * CreateCommenStaff() = 0;
    virtual Staff * CreateBoss() = 0;
    virtual Staff * CreateManager() = 0;
    virtual Staff * CreateStaffByPostNum(int postNum) = 0;
    virtual ~AbstractStaffFactory(){}
};

#endif //ABSTRACTSTAFFFACTORY_H
