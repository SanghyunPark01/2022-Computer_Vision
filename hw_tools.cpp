#include "hw_tools.h"
#include "cmath"
double find_max(double a, double b, double c)
{
    return (a>b)&&(a>c)?a:(b>c)?b:c;
}
double find_min(double a, double b, double c)
{
    return (a<b)&&(a<c)?a:(b<c)?b:c;
}

double find_X(double C, int H_prime)
{
    return C*(1-abs((fmod(H_prime,2))-1));
}
