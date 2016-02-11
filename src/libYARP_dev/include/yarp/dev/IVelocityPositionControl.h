// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright: 2016 Istituto Italiano di Tecnologia
 * Authors: Stefan Bethge <stefan.bethge@iit.it>
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef __YARPVELOCITYPOSITIONCONTROL__
#define __YARPVELOCITYPOSITIONCONTROL__

#include <yarp/os/Vocab.h>
#include <yarp/dev/ControlBoardPid.h>

namespace yarp {
    namespace dev {
        class IVelocityPositionControl;
        class IVelocityPositionControlRaw;
      }
}

/**
 * @ingroup dev_iface_motor
 *
 * Interface for control boards implementing velocity/position control.
 */
class YARP_dev_API yarp::dev::IVelocityPositionControl
{
public:
    /**
     * Destructor.
     */
    virtual ~IVelocityPositionControl() {}


    /**
     * Get the number of controlled axes. This command asks the number of controlled
     * axes for the current physical interface.
     * @return the number of controlled axes.
     * @return true/false on success/failure
     */
    virtual bool getAxes(int *ax) = 0;

    /**
     * Set velocity+position control mode. This command
     * is required by control boards implementing different
     * control methods (e.g. velocity/torque), in some cases
     * it can be left empty.
     * @return true/false on success failure
     */
    virtual bool setVelocityPositionMode()=0;

    /** Get current P value of the position part for a specific joint.
     * @param j joint number
     * @param pid pointer to storage for the return value.
     * @return true/false on success/failure
     */
    virtual bool getPositionP(int j, Pid *pid)=0;

    /** Get current P value of the position part for a specific joint.
     * @param pids vector that will store the values of the pids.
     * @return true/false on success/failure
     */
    virtual bool getPositionPs(Pid *pids)=0;

    /** Set new p value of the position part for a joint axis.
     * @param j joint number
     * @param pid new pid value
     * @return true/false on success/failure
    */
    virtual bool setPositionP(int j, const Pid &pid)=0;

    /** Set new p value of the position part on multiple axes.
     * @param pids pointer to a vector of pids
     * @return true/false upon success/failure
     */
    virtual bool setPositionPs(const Pid *pids)=0;

    /** Get current pid value of the velocity part for a specific joint.
     * @param j joint number
     * @param pid pointer to storage for the return value.
     * @return true/false on success/failure
     */
    virtual bool getVelocityPid(int j, Pid *pid)=0;

    /** Get current pid value of the velocity part for a specific joint.
     * @param pids vector that will store the values of the pids.
     * @return true/false on success/failure
     */
    virtual bool getVelocityPids(Pid *pids)=0;

    /** Set new pid value for a joint axis.
     * @param j joint number
     * @param pid new pid value
     * @return true/false on success/failure
    */
    virtual bool setVelocityPid(int j, const Pid &pid)=0;

    /** Set new pid value on multiple axes.
     * @param pids pointer to a vector of pids
     * @return true/false upon success/failure
     */
    virtual bool setVelocityPids(const Pid *pids)=0;

    /**
     * Start motion at a given speed for one joint.
     * @param j   which joints this command is referring to
     * @param sp  the new speed value
     * @param pos the new position value
     * @return true/false upon success/failure
     */
    virtual bool velocityPositionMove(int j, double sp, double pos)=0;

    /**
     * Start motion at a given speed, multiple joints.
     * @param sp pointer to the array containing the new speed values
     * @param pos pointer to the array containing the new position values
     * @return true/false upon success/failure
     */
    virtual bool velocityPositionMove(const double *sp, const double *pos)=0;

    /** Stop motion, single joint
     * @param j joint number
     * @return true/false on success or failure
     */
    virtual bool stop(int j)=0;

    /** Stop motion, multiple joints
     * @return true/false on success or failure
     */
    virtual bool stop()=0;
};

/**
 * @ingroup dev_iface_motor
 *
 * Interface for control boards implementing velocity/position control.
 */
class yarp::dev::IVelocityPositionControlRaw
{
public:
    /**
     * Destructor.
     */
    virtual ~IVelocityPositionControlRaw() {}

    /**
     * Get the number of controlled axes. This command asks the number of controlled
     * axes for the current physical interface.
     * @return the number of controlled axes.
     * @return true/false on success/failure
     */
    virtual bool getAxes(int *ax) = 0;

    /**
     * Set velocity+position control mode. This command
     * is required by control boards implementing different
     * control methods (e.g. velocity/torque), in some cases
     * it can be left empty.
     * @return true/false on success failure
     */
    virtual bool setVelocityPositionModeRaw()=0;

    /** Set the reference value of the velocity for a given joint.
     * @param j joint number
     * @param t new value
     * @return true/false on success/failure
     */
    virtual bool setRefVelocityRaw(int j, double vel)=0;

    /** Set the reference value of the velocity for all joints.
     * @param t pointer to the array of torque values
     * @return true/false on success/failure
     */
    virtual bool setRefVelocitiesRaw(const double *vels)=0;

    /** Get the reference value of the velocity for a given joint.
     * @param j joint number
     * @param t new value
     * @return true/false on success/failure
     */
    virtual bool getRefVelocityRaw(int j, double *vel)=0;

    /** Get the reference value of the velocity for all joints.
     * @param t pointer to the array of torque values
     * @return true/false on success/failure
     */
    virtual bool getRefVelocitiesRaw(double *vels)=0;

    /** Get current P value of the position part for a specific joint.
     * @param j joint number
     * @param pid pointer to storage for the return value.
     * @return true/false on success/failure
     */
    virtual bool getPositionPRaw(int j, Pid *pid)=0;

    /** Get current P value of the position part for a specific joint.
     * @param pids vector that will store the values of the pids.
     * @return true/false on success/failure
     */
    virtual bool getPositionPsRaw(Pid *pids)=0;

    /** Set new p value of the position part for a joint axis.
     * @param j joint number
     * @param pid new pid value
     * @return true/false on success/failure
    */
    virtual bool setPositionPRaw(int j, const Pid &pid)=0;

    /** Set new p value of the position part on multiple axes.
     * @param pids pointer to a vector of pids
     * @return true/false upon success/failure
     */
    virtual bool setPositionPsRaw(const Pid *pids)=0;

    /** Get current pid value of the velocity part for a specific joint.
     * @param j joint number
     * @param pid pointer to storage for the return value.
     * @return true/false on success/failure
     */
    virtual bool getVelocityPidRaw(int j, Pid *pid)=0;

    /** Get current pid value of the velocity part for a specific joint.
     * @param pids vector that will store the values of the pids.
     * @return true/false on success/failure
     */
    virtual bool getVelocityPidsRaw(Pid *pids)=0;

    /** Set new pid value for a joint axis.
     * @param j joint number
     * @param pid new pid value
     * @return true/false on success/failure
    */
    virtual bool setVelocityPidRaw(int j, const Pid &pid)=0;

    /** Set new pid value on multiple axes.
     * @param pids pointer to a vector of pids
     * @return true/false upon success/failure
     */
    virtual bool setVelocityPidsRaw(const Pid *pids)=0;

    /**
     * Start motion at a given speed for one joint.
     * @param j   which joints this command is referring to
     * @param sp  the new speed value
     * @param pos the new position value
     * @return true/false upon success/failure
     */
    virtual bool velocityPositionMoveRaw(int j, double sp, double pos)=0;

    /**
     * Start motion at a given speed, multiple joints.
     * @param sp pointer to the array containing the new speed values
     * @param pos pointer to the array containing the new position values
     * @return true/false upon success/failure
     */
    virtual bool velocityPositionMoveRaw(const double *sp, const double *pos)=0;

    /** Stop motion, single joint
     * @param j joint number
     * @return true/false on success or failure
     */
    virtual bool stopRaw(int j)=0;

    /** Stop motion, multiple joints
     * @return true/false on success or failure
     */
    virtual bool stopRaw()=0;
};

#endif  /* __YARPVELOCITYPOSITIONCONTROL__ */
