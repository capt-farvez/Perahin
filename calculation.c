#include<stdio.h>
#include "perahin.h"

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


float cgpa_count(Marks marks)
{
    float final_cgpa, total_credit=19.5, gpa_multi_credit ;
    float(CSE103_g);
    CSE103_g = marks_to_gpa(marks.cse103) * 3.0;
    float(CSE104_g);
    CSE104_g = marks_to_gpa(marks.cse104) * 1.5;
    float(CSE105_g);
    CSE105_g = marks_to_gpa(marks.cse105) * 3.0;
    float(EEE121_g);
    EEE121_g = marks_to_gpa(marks.eee121) * 3.0;
    float(EEE122_g);
    EEE122_g = marks_to_gpa(marks.eee122) * 1.5;
    float(MTH103_g);
    MTH103_g = marks_to_gpa(marks.mth103) * 3.0;
    float(CHEM111_g);
    CHEM111_g = marks_to_gpa(marks.chem111) * 3.0;
    float(CHEM112_g);
    CHEM112_g = marks_to_gpa(marks.chem112) * 1.5;

    gpa_multi_credit= (CSE103_g + CSE104_g + CSE105_g + EEE121_g + EEE122_g + MTH103_g+ CHEM111_g + CHEM112_g);
    final_cgpa = (gpa_multi_credit / total_credit);

    return final_cgpa ;
}

