// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2016 Istituto Italiano di Tecnologia
 * Authors: Stefan Bethge
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include "yarp/dev/ControlBoardInterfacesImpl.h"
#include <yarp/dev/ControlBoardHelper.h>
#include <yarp/dev/IVelocityPositionControlImpl.h>

using namespace yarp::dev;

ImplementVelocityPositionControl::ImplementVelocityPositionControl(IVelocityPositionControlRaw *tq):
    iVelocityPositionControlRaw(tq),
    helper(NULL),
    temp_int(NULL),
    temp_double(NULL),
    temp_double2(NULL),
    tempPids()
{
}

ImplementVelocityPositionControl::~ImplementVelocityPositionControl()
{
    uninitialize();
}


bool ImplementVelocityPositionControl::initialize(int size, const int *axis_map, const double *enc, const double *zeros)
{
    if (helper != NULL)
        return false;

    helper=(void *)(new ControlBoardHelper(size, axis_map, enc, zeros,0));
    yAssert (helper != NULL);
    temp_double = new double [size];
    yAssert (temp_double != NULL);
    temp_double2 = new double [size];
    yAssert (temp_double2 != NULL);
    temp_int = new int [size];
    yAssert (temp_int != NULL);
    tempPids = new Pid [size];
    yAssert (tempPids != NULL);

    return true;
}

bool ImplementVelocityPositionControl::uninitialize ()
{
    if(helper != NULL)
    {
        delete castToMapper(helper);
        helper = NULL;
    }
    checkAndDestroy(temp_double);
    checkAndDestroy(temp_double2);
    checkAndDestroy(temp_int);
    checkAndDestroy(tempPids);

    return true;
}

bool ImplementVelocityPositionControl::getAxes(int *axes)
{
    return iVelocityPositionControlRaw->getAxes(axes);
}

bool ImplementVelocityPositionControl::setVelocityPositionMode()
{
    return iVelocityPositionControlRaw->setVelocityPositionModeRaw();
}

bool ImplementVelocityPositionControl::velocityPositionMove(int j, double sp, double pos) {
    int k;
    double enc, enc2;
    castToMapper(helper)->velA2E(sp, j, enc, k);
    castToMapper(helper)->posA2E(pos, j, enc2, k);
    return iVelocityPositionControlRaw->velocityPositionMoveRaw(k, enc, enc2);
}

bool ImplementVelocityPositionControl::velocityPositionMove(const double *sp, const double *pos) {
    castToMapper(helper)->velA2E(sp, temp_double);
    castToMapper(helper)->velA2E(pos, temp_double2);
    return iVelocityPositionControlRaw->velocityPositionMoveRaw(temp_double, temp_double2);
}

bool ImplementVelocityPositionControl::stop(int j)
{
    int k;
    k=castToMapper(helper)->toHw(j);
    return iVelocityPositionControlRaw->stopRaw(k);
}

bool ImplementVelocityPositionControl::stop()
{
    return iVelocityPositionControlRaw->stopRaw();
}

bool ImplementVelocityPositionControl::setVelocityPid(int j, const Pid &pid)
{
    int k=castToMapper(helper)->toHw(j);
    return iVelocityPositionControlRaw->setVelocityPidRaw(k,pid);
}

bool ImplementVelocityPositionControl::setVelocityPids(const Pid *pids)
{
    int tmp=0;
    int nj=castToMapper(helper)->axes();

    for(int j=0;j<nj;j++)
    {
        tmp=castToMapper(helper)->toHw(j);
        tempPids[tmp]=pids[j];     // here the conversion consists into reordering the Pids array
    }

    return iVelocityPositionControlRaw->setVelocityPidsRaw(tempPids);
}

bool ImplementVelocityPositionControl::getVelocityPid(int j, Pid *pid)
{
    int k;
    k=castToMapper(helper)->toHw(j);

    return iVelocityPositionControlRaw->getVelocityPidRaw(k, pid);
}


bool ImplementVelocityPositionControl::getVelocityPids(Pid *pids)
{
    bool ret=iVelocityPositionControlRaw->getVelocityPidsRaw(tempPids);
    int nj=castToMapper(helper)->axes();

    for(int j=0;j<nj;j++)
        pids[castToMapper(helper)->toUser(j)]=tempPids[j];

    return ret;
}
