import math

def func_one(x):
    return ((3*x*x) - (2*x*x*x))

def func_one_d(x):
    return ((6*x) - (6*x*x))

def main():
    res1 = func_one(0.5)
    res2 = func_one_d(0.5)
    print('smoothstep 3x^2-2x^3(0.5000) = ' + str(res1))
    print('smoothstep 3x^2-2x^3(0.5000) derivative = ' + str(res2))


if __name__=='__main__':
    main()
