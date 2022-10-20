#pragma once

class CCoeffs{
public:
    double a;
    double b;
    double c;
    CCoeffs(){
        a=0;b=0;c=0;
    };
    void ask_for_input();
    void print();
};
