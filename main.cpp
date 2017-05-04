#include <iostream>
#include <cmath>

#define PI 3.14159265359f

class CDualNumber
{
public:
    CDualNumber (float real = 0.0f, float dual = 0.0f)
        : m_real(real), m_dual(dual)
    {
    }

    float Real() const { return m_real; }
    float Dual() const { return m_dual; }

private:
    float m_real;
    float m_dual;
};

inline CDualNumber operator + (const CDualNumber &a, const CDualNumber &b)
{
    return CDualNumber(a.Real() + b.Real(), a.Dual() + b.Dual());
}

inline CDualNumber operator - (const CDualNumber &a, const CDualNumber &b)
{
    return CDualNumber(a.Real() - b.Real(), a.Dual() - b.Dual());
}

inline CDualNumber operator * (const CDualNumber &a, const CDualNumber &b)
{
    return CDualNumber(
            a.Real() * b.Real(),
            a.Real() * b.Dual() + a.Dual() * b.Real()
            );
}

inline CDualNumber operator / (const CDualNumber &a, const CDualNumber &b)
{
    return CDualNumber(
            a.Real() / b.Real(),
            (a.Dual() * b.Real() - a.Real() * b.Dual()) / (b.Real() * b.Real())
            );
}


inline CDualNumber sqrt (const CDualNumber &a)
{
    float sqrtReal = ::sqrt(a.Real());
    return CDualNumber(
            sqrtReal, 0.5f* a.Dual() / sqrtReal
            );
}

inline CDualNumber pow (const CDualNumber &a, float y)
{
    return CDualNumber(
            ::pow(a.Real(), y),
            y * a.Dual() * ::pow(a.Real(), y - 1.0f)
            );
}

inline CDualNumber sin (const CDualNumber &a)
{
    return CDualNumber(
        ::sin(a.Real()),
        a.Dual() * ::cos(a.Real())
    );
}

inline CDualNumber cos (const CDualNumber &a)
{
    return CDualNumber(
            ::cos(a.Real()),
            -a.Dual() * ::sin(a.Real())
            );
}

inline CDualNumber tan (const CDualNumber &a)
{
    return CDualNumber(
        ::tan(a.Real()),
        a.Dual() / (::cos(a.Real()) * ::cos(a.Real()))
    );
}
 
inline CDualNumber atan (const CDualNumber &a)
{
    return CDualNumber(
        ::atan(a.Real()),
        a.Dual() / (1.0f + a.Real() * a.Real())
    );
}
 
inline CDualNumber SmoothStep (CDualNumber x)
{
    // f(x) = 3x^2 - 2x^3
    // f'(x) = 6x - 6x^2
    return x * x * (CDualNumber(3) - CDualNumber(2) * x);
}

//----------------------------------------------------------------------
// Test Functions
//----------------------------------------------------------------------

void TestSmoothStep (float x)
{
    CDualNumber y = SmoothStep(CDualNumber(x, 1.0f));
    printf("smoothstep 3x^2-2x^3(%0.4f) = %0.4f\n", x, y.Real());
    printf("smoothstep 3x^2-2x^3'(%0.4f) = %0.4f\n\n", x, y.Dual());
}
 
void TestTrig (float x)
{
    CDualNumber y = sin(CDualNumber(x, 1.0f));
    printf("sin(%0.4f) = %0.4f\n", x, y.Real());
    printf("sin'(%0.4f) = %0.4f\n\n", x, y.Dual());
 
    y = cos(CDualNumber(x, 1.0f));
    printf("cos(%0.4f) = %0.4f\n", x, y.Real());
    printf("cos'(%0.4f) = %0.4f\n\n", x, y.Dual());
 
    y = tan(CDualNumber(x, 1.0f));
    printf("tan(%0.4f) = %0.4f\n", x, y.Real());
    printf("tan'(%0.4f) = %0.4f\n\n", x, y.Dual());
 
    y = atan(CDualNumber(x, 1.0f));
    printf("atan(%0.4f) = %0.4f\n", x, y.Real());
    printf("atan'(%0.4f) = %0.4f\n\n", x, y.Dual());
}
 
void TestSimple (float x)
{
    CDualNumber y = CDualNumber(3.0f) / sqrt(CDualNumber(x, 1.0f));
    printf("3/sqrt(%0.4f) = %0.4f\n", x, y.Real());
    printf("3/sqrt(%0.4f)' = %0.4f\n\n", x, y.Dual());
 
    y = pow(CDualNumber(x, 1.0f) + CDualNumber(1.0f), 1.337f);
    printf("(%0.4f+1)^1.337 = %0.4f\n", x, y.Real());
    printf("(%0.4f+1)^1.337' = %0.4f\n\n", x, y.Dual());
}

int main (int argc, char **argv)
{
    TestSmoothStep(0.5f);
    TestSmoothStep(0.75f);
    TestTrig(PI * 0.25f);
    TestSimple(3.0f);
    return 0;
}   
