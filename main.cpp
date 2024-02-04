#include <iostream>
#include <cmath>
#include <vector>
#include <boost/math/distributions/students_t.hpp>


#include <QDir>
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

#define alpha1 0.05



void twoSampleTTest(const std::vector<double>& sample1, const std::vector<double>& sample2, double alpha) {
    // محاسبه میانگین نمونه ها
    double mean1 = 0, mean2 = 0;
    for (double value : sample1) {
        mean1 += value;
    }
    mean1 /= sample1.size();

    for (double value : sample2) {
        mean2 += value;
    }
    mean2 /= sample2.size();

   // محاسبه واریانس نمونه اول
    double variance1 = 0, variance2 = 0;
    for (double value : sample1) {
        variance1 += pow(value - mean1, 2);
    }
    variance1 /= (sample1.size() - 1);

     // محسببه واریانس نمونه دوم
    for (double value : sample2) {
        variance2 += pow(value - mean2, 2);
    }
    variance2 /= (sample2.size() - 1);

    // انحراف معیار استاندارد ( بخش بر تعداد منهای یک)
    double pooledStdDev = sqrt((variance1 / sample1.size()) + (variance2 / sample2.size()));

    // محاسبه آماره T
    double tScore = fabs((mean1 - mean2) / pooledStdDev);

    // درجه های آزادی
    int df = sample1.size() + sample2.size() - 2;

    // توزیع تی بر حسب ضریب اطمینان و درجه ازادی
    boost::math::students_t tDist(df);

    // ناحیه بحرانی
    double criticalValue = boost::math::quantile(tDist, 1.0 - alpha / 2);

    // نمایش مقادیر
    std::cout << "Sample 1 Mean: " << mean1 << std::endl;
    std::cout << "Sample 2 Mean: " << mean2 << std::endl;
    std::cout << "Sample 1 Variance: " << variance1 << std::endl;
    std::cout << "Sample 2 Variance: " << variance2 << std::endl;
    std::cout << "Pooled Standard Deviation: " << pooledStdDev << std::endl;
    std::cout << "t-Score: " << tScore << std::endl;
    std::cout << "Degrees of Freedom: " << df << std::endl;
    std::cout << "Critical Value: " << criticalValue << std::endl;

    // اعمال تست
    if (tScore > criticalValue) {
        std::cout << "Null hypothesis rejected. Means are different." << std::endl;
    } else {
        std::cout << "Null hypothesis not rejected. Means are not significantly different." << std::endl;
    }
}




int main() {




    Document ReadExcel("C://Users/"+qgetenv("USERNAME")+"/Desktop/tst.xlsx");


    std::vector<double> Soc1 ;
    std::vector<double> Soc2 ;


  for(int i=2;i<45;i++){
      
      Soc1.push_back(ReadExcel.cellAt(i,1)->readValue().toInt());
}

  for(int i=2;i<33;i++){

  Soc2.push_back(ReadExcel.cellAt(i,3)->readValue().toInt());

   }

    twoSampleTTest(Soc1, Soc2, alpha1);

    return 0;
}
