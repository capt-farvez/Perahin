#include<stdio.h>

float marks_to_gpa(float marks)
{
    if(marks >= 80){
        return 4.00;
    }
    else if(marks >= 75){
        return 3.75;
    }
    else if(marks >= 70){
        return 3.50;
    }
    else if(marks >= 65){
        return 3.25;
    }
    else if(marks >= 60){
        return 3.00;
    }
    else if(marks >= 55){
        return 2.75;
    }
    else if(marks >= 50){
        return 2.50;
    }
    else if(marks >= 45){
        return 2.25;
    }
    else if(marks >= 40){
        return 2.00;
    }
    else if(marks < 40){
        return 0;
    }
}


float cgpa_count(float CSE103, float CSE104, float CSE105, float EEE121, float EEE122, float MTH103, float CHEM111, float CHEM112)
{
    float final_cgpa, total_credit=19.5, gpa_multi_credit ;
    float(CSE103_g);
    CSE103_g = marks_to_gpa(CSE103) * 3.0;
    float(CSE104_g);
    CSE104_g = marks_to_gpa(CSE104) * 1.5;
    float(CSE105_g);
    CSE105_g = marks_to_gpa(CSE105) * 3.0;
    float(EEE121_g);
    EEE121_g = marks_to_gpa(EEE121) * 3.0;
    float(EEE122_g);
    EEE122_g = marks_to_gpa(EEE122) * 1.5;
    float(MTH103_g);
    MTH103_g = marks_to_gpa(MTH103) * 3.0;
    float(CHEM111_g);
    CHEM111_g = marks_to_gpa(CHEM111) * 3.0;
    float(CHEM112_g);
    CHEM112_g = marks_to_gpa(CHEM112) * 1.5;

    gpa_multi_credit= (CSE103_g + CSE104_g + CSE105_g + EEE121_g + EEE122_g + MTH103_g+ CHEM111_g + CHEM112_g);
    final_cgpa = (gpa_multi_credit / total_credit);

    return final_cgpa ;
}

