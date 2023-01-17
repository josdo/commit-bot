/*  --------------- 
    sharedData 
    --------------- */
static const float SUPPLY_VOLTAGE = 3.3;

/*  --------------- 
    phaseControl 
    --------------- */
#include "sharedData.h"

/*  Control three parts of stepping: 
    * where is magnetic pull
    * how strong is the pull
    * how quickly does the pull move around the circumference
*/

/*  rotPerSec = dThetaPerStep * stepsPerSec
*/

/* Create a phase and phase voltage using these safe constructors. */
typedef float phaseV_t;
typedef uint32_t phase_t;
typedef uint32_t channel_t;

// Phase 1 owns the first row of channels. Phase 2 owns the second row.
static channel_t const channelOrder[2][2] = [
    [channel(1), channel(2)],
    [channel(3), channel(4)]
];

void initPhaseControl()
{
    // Configure pins
    // Setup PWM
}

/*  Return phase voltage. */
phaseV_t phaseV(float v)
{
    // Check abs <= SUPPLY_VOLTAGE
    // return v
}

/*  Return phase. */
phase_t phase(uint32_t p)
{
    // Check phase is 1 or 2
    // return p
}

channel_t channel(uint32_t c)
{
    // Check within [1,4]
    // return c
}

/*  Gets the pair of channels corresponding to a phase. */
channel_t * getChannels(phase_t p)
{
    // return &( (phase(1) == p) ? channelOrder[0] : channelOrder[1] );
}

/*  Return 1 out of the 2 channels of a phase that will be
    high voltage. */
channel_t activeChannel(phase_t p, bool isForward)
{
    channel_t *chs = getChannels(p);
    // Return the active channel
    return (isForward) ? chs[0] : chs[1];
}

/*  Return 1 out of the 2 channels of a phase that will be
    held low (0 V). */
channel_t passiveChannel(phase_t p, bool isForward)
{
    channel_t *chs = getChannels(p);
    // Return the passive channel
    return (isForward) ? chs[1] : chs[0];
}

/*  Set stator's effective north pole.
    Args
        theta: orientation of stator's north pole in radians */
void setStatorNorth(float theta)
{
    setPhaseVoltage(phase(1), sin(theta));
    setPhaseVoltage(phase(2), cos(theta));
}

/*  Set phase voltage using PWM. */
void setPhaseVoltage(phase_t p, phaseV_t v)
{
    bool phaseDisabled = (phaseV(0) == v);
    // if phaseDisabled
        // Clear latch of the enable pin
        // Zero out duty cycle for both phase channels
    // else
        // Set latch of the enable pin
        // Set the duty cycle of the active channel
        // Zero out the duty cycle of the passive channel

        // bool isForward = (phaseV(0) > v);
        // activeChannel(p, isForward);
        // passiveChannel(p, isForward);
}

/*  --------------- 
    motorStepService 
    --------------- */
#include "sharedData.h"

typdef enum
{
    TWO_PHASE_ON,
    ONE_PHASE_ON,
    HALF_STEP,
    QTR_STEP
} stepMode_t;

static float currTheta = 0;
static float dTheta = 0;
static uint32_t sps = 0;
static stepMode_t stepMode;

/*  Set desired stator north and commands it. */
void setCurrTheta(float theta)
{
    // Constrain to [0, 2pi)
    // update currTheta
    // setStatorNorth(currTheta)
}

/*  Set step size with error checks.
    Args
        rads: radial step in stator's north pole, in radians. 
            Can be positive or negative. */
void setStepSize(float rads)
{
    // Check between -pi/2 and pi/2
    // set dTheta
}

/*  Set step rate. 
    Args
        numStepsPerSec: steps per second */
void setStepRate(uint32_t numStepsPerSec)
{
    // set sps
}

void init()
{
    // Initialize step sequence based on step mode
    if (TWO_PHASE_ON == stepMode)
    {
        // setCurrTheta(pi/4);
        // setStepSize(pi/2);
        // setMaxStepRate from empirical testing
    }
    else if (ONE_PHASE_ON == stepMode)
    {
        // setCurrTheta(0);
        // setStepSize(pi/2);
        // setMaxStepRate from empirical testing
    }
    else if (HALF_STEP == stepMode)
    {
        // setCurrTheta(0);
        // setStepSize(pi/4);
        // setMaxStepRate from empirical testing
    }
    else if (QTR_STEP == stepMode)
    {
        // setCurrTheta(0);
        // setStepSize(pi/8);
        // setMaxStepRate from empirical testing
    }

    // setStepRate(10);
    // Initialize step timer to (1000 / sps) ms
    // Start step timer
}

void run()
{
    // if ES_TIMEOUT
        // setStepRate(getStepRateFromDial())
        // perform a step using setStatorNorth
        // start the step timer
    // if ES_NEW_SPEED
        // setStepRate(event.param);
}

/*  --------------- 
    speedDialService 
    --------------- */

#include "SharedData.h"

static const uint32_t MAX_ANALOG_READING; // TODO
static const uint32_t MS_PER_READ = 20;
static uint32_t currStepRate = 0;
static uint32_t maxStepRate = 0;

// analog pin

void init()
{
    // Set up AD read library
    // Set maximums based on empirical testing with 2 phase on drive
    // Create and start pot read timer of MS_PER_READ
}

void run()
{
    // if ES_TIMEOUT
        // read analog pin
        // updaet currStepRate to reading / MAX_ANALOG_READING * MAX_STEP_RATE
        // restart timer
}

void setMaxStepRate(uint32_t r)
{
    // check >= 0
    // maxStepRate = r;
}

uint32_t getStepRateFromDial()
{
    return currStepRate;
}


