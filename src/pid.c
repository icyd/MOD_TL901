#include "pid.h"

int main(void) {
    uint16_t output;
    pidStruct pid = {FIXK_MAKE(2.474), FIXI_MAKE(0.00124), FIXD_MAKE(1237)};
    output = pidUpdate(80, 100, &pid);
}

uint8_t pidUpdate(inUnit input, inUnit setPoint, pidStruct *pidPnt) {
    static errUnit lastError = 0;
    static errUnit xShort = 0;
    static calcUnit xIntegral = 0;
    calcUnit xDerivate;
    calcUnit xProp;
    errUnit error;
    errUnit xIdeal;
    outUnit out;

    error = setPoint - input;
    xProp = ((calcUnit)pidPnt->Kp * (calcUnit)error) >> K_DIF;
    xIntegral += (calcUnit)pidPnt->Ki * (error - xShort);
    error = ewma(error);
    xDerivate = ((calcUnit)pidPnt->Kd * (error - lastError)) >> D_DIF;
    lastError = error;
    xIdeal = (errUnit)((xProp + xDerivate + (xIntegral >> I_DIF)) >> MINDIV);
    if (xIdeal > OUT_MAX)
        out = OUT_MAX;
    else if (xIdeal < OUT_MIN)
        out = OUT_MIN;
    else
        out = (outUnit)xIdeal;
    xShort = xIdeal - (errUnit)out;

    return out;
}
