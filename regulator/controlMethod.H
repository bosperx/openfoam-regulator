/*---------------------------------------------------------------------------*\
Class
    Foam::ControlMethod

Description
    ControlMethod is a base class for implementing a control algotirhm
    used by Regulator. The control algorithm is selected by specifying
    a "mode" in regulator dict and setting "parameters" dict accordingly
    to control algorithm implementation.

\*---------------------------------------------------------------------------*/
#ifndef ControlMethod_H
#define ControlMethod_H

#include "fvCFD.H"

class ControlMethod
{
public:
    virtual ~ControlMethod() = default;
    ControlMethod() = default;
    ControlMethod(const dictionary &);

    //- ControlMethod factory
    static std::shared_ptr<ControlMethod> create(const dictionary &);

    enum controlType
    {
        twoStep, // on/off control
        PID,
    };
    static const Enum<controlType> controlTypeNames;

    //- Returns a parameters sub-dictionary or empty dict
    static const dictionary parameters(const dictionary &);

    //- Calculate output signal from current process value, target value
    // and current time delta
    virtual scalar calculate(scalar current, scalar target, scalar deltaT) = 0;

    //- Write to runtime dict
    virtual void write(Ostream &) const;

protected:
    controlType type_;
};

class TwoStepControl : public ControlMethod
{
public:
    TwoStepControl() = default;
    TwoStepControl(const dictionary &);

    scalar calculate(scalar current, scalar target, scalar deltaT);
    void write(Ostream &) const override;

private:
    // Wartość histerezy
    //- Przy istnieniu histerezy wprowadzana jest zmienna zastępczna y'_z taka,
    //- że y'_z = y + 0.5h, dla sygnału wyjściowego 1 albo y - 0.5h dla sygnału 0
    scalar h_;

    // Preserve old output signal for histeresis correction
    scalar outputSignal_;

};

class PIDControl : public ControlMethod
{
public:
    PIDControl() = default;
    PIDControl(const dictionary &);

    scalar calculate(scalar current, scalar target, scalar deltaT);
    void write(Ostream &) const override;


private:
    scalar Kp_;                     // Proportional control term
    scalar Ti_;                     // Integral control term
    scalar Td_;                     // Differential control term
    scalar outputMax_;              // Max output signal (saturation)
    scalar outputMin_;              // Min output signal
    scalar errorMax_;               // Constains received absolute error value
    scalar integralErrorMax_;       // Constains built-up integral error
    scalar oldError_;               // Old error
    scalar errorIntegral_;          // Error integral w.r.t. time
};

#endif
