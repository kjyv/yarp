// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2016 Istituto Italiano di Tecnologia
 * Authors: Stefan Bethge
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef __YARPVELOCITYPOSITIONCONTROLIMPL__
#define __YARPVELOCITYPOSITIONCONTROLIMPL__

#include <yarp/dev/IVelocityPositionControl.h>
#include <yarp/dev/api.h>

namespace yarp {
    namespace dev {
        class ImplementVelocityPositionControl;
    }
}

class YARP_dev_API yarp::dev::ImplementVelocityPositionControl: public IVelocityPositionControl
{
protected:
    yarp::dev::IVelocityPositionControlRaw *iVelocityPositionControlRaw;
    void *helper;
    int     *temp_int;
    double  *temp_double;
    double  *temp_double2;
    Pid     *tempPids;

    /**
     * Initialize the internal data and alloc memory.
     * @param size is the number of controlled axes the driver deals with.
     * @param axis_map is a lookup table mapping axes onto physical drivers.
     * @param enc is an array containing the encoder to angles conversion factors.
     * @param zos is an array containing the zeros of the encoders.
     * @return true if initialized succeeded, false if it wasn't executed, or assert.
     */
    bool initialize (int size, const int *axis_map, const double *enc, const double *zeros);
          
    /**
     * Clean up internal data and memory.
     * @return true if uninitialization is executed, false otherwise.
     */
    bool uninitialize ();

public:
    /* Constructor.
     * @param y is the pointer to the class instance inheriting from this 
     *  implementation.
     */
    ImplementVelocityPositionControl(yarp::dev::IVelocityPositionControlRaw *y);
        
    /**
     * Destructor. Perform uninitialize if needed.
     */
    virtual ~ImplementVelocityPositionControl();

    virtual bool getAxes(int *ax) = 0;
    virtual bool setVelocityPositionMode()=0;
    virtual bool getPositionP(int j, Pid *pid)=0;
    virtual bool getPositionPs(Pid *pids)=0;
    virtual bool setPositionP(int j, const Pid &pid)=0;
    virtual bool setPositionPs(const Pid *pids)=0;
    virtual bool getVelocityPid(int j, Pid *pid)=0;
    virtual bool getVelocityPids(Pid *pids)=0;
    virtual bool setVelocityPid(int j, const Pid &pid)=0;
    virtual bool setVelocityPids(const Pid *pids)=0;
    virtual bool velocityPositionMove(int j, double sp, double pos);
    virtual bool velocityPositionMove(const double *sp, const double *pos);
    virtual bool stop(int j);
    virtual bool stop();
};

//TODO: add stub implementation

#endif   /* __YARPVELOCITYPOSITIONCONTROLIMPL__ */


