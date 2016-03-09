#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fft.h"
//��Сֵ
double minimum(double data[],int length){
    if(data == NULL || length == 0) return 0.0;
    double MIN = data[0];
    int i;
    for(i = 1; i < length; i++){
        MIN = data[i]<MIN?data[i]:MIN;
    }
    return MIN;
}
//���ֵ
double maximum(double data[],int length){
    if(data == NULL || length == 0) return 0.0;
    double Max = data[0];
    int i;
    for(i = 1; i<length; i++)
        Max = data[i]<Max ? Max : data[i];
    return Max;
}
//����
double variance(double data[], int length){
    if(data == NULL || length == 0) return 0.0;
    double average = 0, s = 0, sum = 0;
    int i;
    for(i = 0; i<length; i++)
    {
        sum = sum + data[i];
    }
    average = sum / length;
    for(i = 0; i<length; i++)
    {
        s = s + pow(data[i] - average, 2);
    }
    s = s / length;
    return s;
}
//����ֵ��
double meanCrossingsRate(double data[], int length){
    if(data == NULL || length == 0) return 0.0;
    double Sum = 0;
    double num = 0;
    int i;
    for(i = 0; i < length; i++){
        Sum +=data[i];
    }
    double avg = Sum/length;
    for(i = 0; i < length - 1; i++){
        if ((data[i]-avg) * (data[i + 1]-avg) < 0){
            num++;
        }
    }
    return num / length;
}

//��׼��
double standardDeviation(double data[], int length){
    if(data == NULL || length == 0) return 0.0;
    double s = variance(data,length);
    s = sqrt(s);
    return s;
}
//���ֵ���ڵ�λ��=�׷�λ��
double spp(double data[],int length){
    if(data == NULL || length == 0) return 0;
    int r = 0;
    double max = data[0];
    int i;
    for(i = 0; i < length; i++) {
        if (data[i] > max ) {
            r = i;
            max = data[i];
        }
    }
    return r;
}
//Ƶ�� ����
double energy(double data[],int length){
    if(data == NULL || length == 0) return 0.0;
    double sum = 0;
    int i;
    for(i=0;i<length;i++){
        sum+=pow(data[i],2);
    }
    return sum/length;
}

//����ѧ����  ��
double entropy(double data[],int length){
    if(data == NULL || length == 0) return 0.0;
    double temp;
    double sum = 0;
    int i;
    for(i=0;i<length;i++){
        temp = data[i];
        if(temp > 0){
            sum+=log(temp)*temp;
        }
    }
    return sum*-1;
}

//ƽ��ֵ
double mean(double data[], int length){
    if(data == NULL || length == 0) return 0.0;

    double Sum = 0;
    int i;
    for(i = 0; i < length; i++)
        Sum = Sum + data[i];
    return Sum / length;
}

// ���� centroid : SUM(i*f(i)*f(i))/SUM(f(i)*f(i))��Intelligent Sleep Stage Mining Service with Smartphones
double centroid(double data[],int length){
    if(data == NULL || length == 0) return 0.0;
    double sum1 = 0;
    double sum2 = 0;
    double temp;
    double tempPow;
    int i;
    for(i=0;i<length;i++){
        temp = data[i];
        tempPow = temp*temp;
        sum1+=tempPow;
        sum2+=tempPow*i;
    }
    return sum2/sum1;
}


//������ֵ
double signalVectorMagnitude(double data[], int length){

    double MaxMagnitude = 0;
    int i;
    for(i = 0; i < length; i++){
        if (data[i] < 0)
            MaxMagnitude = (-data[i])<MaxMagnitude ? MaxMagnitude : (-data[i]);
        else
            MaxMagnitude = data[i]<MaxMagnitude ? MaxMagnitude : data[i];
    }
    return MaxMagnitude;
}
//�ķ�λ����Quartile�� 1/4
double firstQuartile(double data[], int length){

    if(data == NULL || length == 0) return 0.0;
    double* copydata;
    copydata = (double *)malloc(length*sizeof(double));
    int i,j;
    for(i = 0; i < length; i++){
        copydata[i] = data[i];
    }
    for(i = 0; i<length; i++){
        for (j = i + 1; j<length; j++)
        {
            if (copydata[j]<copydata[i])
            {
                double t;
                t = copydata[i];
                copydata[i] = copydata[j];
                copydata[j] = t;
            }
        }
    }
    double q = 1 + (length - 1) *0.25;
    int b = (int)q;
    double d = q - b;
    double quartile1 = copydata[b-1] + (copydata[b] - copydata[b-1])*d;
    return quartile1;
}
//�ķ�λ����Quartile�� 3/4**/
double thirdQuartile(double data[], int length){

    double* copydata;
    copydata = (double*)malloc(length*sizeof(double));
    int i,j;
    for(i = 0; i < length; i++)
    {
        copydata[i] = data[i];
    }
    for(i = 0; i<length; i++)
    {
        for (j = i + 1; j<length; j++)
        {
            if (copydata[j]<copydata[i])
            {
                double t;
                t = copydata[i];
                copydata[i] = copydata[j];
                copydata[j] = t;
            }
        }
    }
    double q = 1 + (length - 1) *0.75;
    int b = (int)q;
    double d = q - b;
    double quartile3 = copydata[b-1] + (copydata[b] - copydata[b-1])*d;
    return quartile3;
}

//������
double zeroCrossingRate(double data[], int length){

    double num = 0;
    int i;
    for(i = 0; i < length - 1; i++)
    {
        if (data[i] * data[i + 1]< 0){
            num++;
        }
    }
    return num / length;
}

//��λ����Median��
double median(double data[], int length){

    double* copydata = (double*)malloc(length*sizeof(double));
    int i,j;
    for(i = 0; i < length; i++){
        copydata[i] = data[i];
    }
    double medium;
    for(i = 0; i<length; i++) {
        for (j = i + 1; j<length; j++) {
            if (copydata[j]<copydata[i])
            {
                double t;
                t = copydata[i];
                copydata[i] = copydata[j];
                copydata[j] = t;
            }
        }
    }

    if (length % 2 == 1)
        medium = copydata[length / 2];
    else
        medium = (copydata[length / 2 - 1] + copydata[length / 2]) / 2;
    return medium;
}

/*��ĳ������ֵ���й�һ��
 * @param lower ��һ���ķ�Χ���ֵ
 * @param upper ��һ���ķ�Χ���ֵ
 * @param value Ҫ��һ��������
 * @param min ������������Сֵ
 * @param max �������������ֵ
 * @return
 */
double zeroOneLibSvm(double lower,double upper,double value,double min,double max){
    return lower + (upper-lower) * (value-min)/(max-min);
}
//ֻ�ܽ��ճ���Ϊ128������
//������128��ȫΪ0
double* fftMe(double list[],int length) {
    complex theList[128];
    int i;
    for (i = 0; i < length; i++) {
        complex co;
        co.real=list[i];
        co.imag=0;
        theList[i] = co;
    }
    for (i = length; i < 128; i++) {
        complex co;
        co.imag=0;
        co.real=0;
        theList[i] = co;
    }

    // fft
    fft(length,theList);

    double alpha=1.0/(double)length;
    for (i = 0; i < length; i++) {
        complex co;
        co.real = alpha*theList[i].real;
        co.imag = alpha*theList[i].imag;
        theList[i] = co;
    }
    float fftSeries[length];
    double out[length/2];
    c_abs(theList,fftSeries,length);
    for(i=0;i<length/2;i++){
       out[i] = fftSeries[i+1]*2;
       //printf("%.10f\n",out[i]);
    }
    return out;
}

//������ƽ��ֵ
double rms(double list[],int length){
    double rms=0;
    double sum = 0;
    int i;
    for(i=0;i<length;i++){
        sum+=pow(list[i],2);
    }
    rms = sqrt(sum/length);
    return rms;
}

//������ֵ��� ����ɢֵ����ۼ�����Ȼ������ܳ��ȡ�ʵ����ƽ��ÿʱ�̵������
double sma(double data[],int length,double interval){
    double sum=0;
    double lot=length * interval;
    int i;
    for(i=0;i<length;i++){
        sum +=data[i]*interval;
    }
    return sum/lot;
}

//�ķ�λ��
double iqr(double list[],int length){
    return thirdQuartile(list,length)-firstQuartile(list,length);
}
//����ƽ����
double mad(double data[],int length){
    if(data == NULL || length == 0) return 0.0;
    double meanD = mean(data,length);
    double sum = 0;
    int i;
    for(i=0;i<length;i++){
        sum+=fabs(data[i]-meanD);
    }
    return sum/length;
}
//ʱ�� ����
double tenergy(double data[],int length){
    if(data == NULL || length == 0) return 0.0;
    return energy(data,length);
}
//Ƶ�� ��׼����
double fdev(double data[],int length){
    return standardDeviation(data,length);
}
//Ƶ��ƽ��ֵ
double fmean(double data[],int length){
    return mean(data,length);
}

//Ƶ�� ƫ��
double skew(double data[],int length){
    if(data == NULL || length == 0) return 0.0;
    double meanD = mean(data,length);
    double dev = standardDeviation(data,length);
    double sum=0;
    int i;
    for(i=0;i<length;i++){
        sum+=pow((data[i]-meanD)/dev,3);
    }
    return sum/length;
}

//Ƶ�� ���
double kurt(double data[],int length){
    if(data == NULL || length == 0) return 0.0;
    double meanD = mean(data,length);
    double dev = standardDeviation(data,length);
    double sum=0;
    int i;
    for(i=0;i<length;i++){
        sum+=pow((data[i]-meanD)/dev,4)-3;
    }
    return sum/length;
}
