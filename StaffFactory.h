//
// Created by Administrator on 24-8-16.
//

#ifndef STAFFFACTORY_H
#define STAFFFACTORY_H
#include "AbstractStaffFactory.h"


class StaffFactory : public AbstractStaffFactory {
    Staff * CreateCommenStaff() override;
    Staff * CreateBoss() override;
    Staff * CreateManager() override;
    Staff * CreateStaffByPostNum(int postNum) override;
};



#endif //STAFFFACTORY_H
