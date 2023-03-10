#ifndef PSHCV_H
#define PSHCV_H
/*
My Computer Vision class
Park, Sanghyun from KR
E-mail : pash0302@naver.com
GitHub : SanghyunPark01
*/

#include "kfc.h"
#include "imageform.h"
struct EdgeInfo {
    double u;
    double v;
    int Dir;
    double Mag;
    double Ang;
};

class pshCV
{
private:
    static int _FindOtsuValue(KImageGray imputimage);
    static void _Histo(KImageGray input,int []);
    static void _HistoValue(KImageGray& value);

public:
    pshCV();
    static void Thresholded(const KImageGray& inputimage, int value);
    static void OtsuThresholded(const KImageGray& inputimage);
    static void Dilated(const KImageGray& inputimage, int kernel_size);
    static void Eroded(const KImageGray& inputimage, int kernel_size);
    static bool CheckBinaryImage(const KImageGray);
    static bool Labeling(const KImageColor& outputimage, KImageGray inputimage);
    static void HistoEQ(const KImageColor& inputimage);
    static void HistoMatching(const KImageColor& SourceImage, KImageColor ReferImage);//target : reference
    static void GaussianNoised(const KImageColor& icImg, double dSigma);
    static void SaltAndPepperNoised(const KImageColor& icImg);
    static void BoxFiltering(const KImageColor& icImg, int KernelSize);
    static void GaussianFiltering(const KImageColor& icImg, double dSigma);
    static void MedianFiltering(const KImageColor& icImg, int KernelSize);
    static void CannyEdged(KImageGray& igImg, double dSigma, int nHighThld, int nLowThld);
    static KImageColor CircleHoughTransform(KImageGray igImg, int nRadius);
    static KImageColor GeneralizedHoughTransform(KImageGray igImg);
    static void OpticalFlow(KImageGray &igMain_0, KImageGray &igMain_1, KImageColor &output, int size);
    static void Window_weight(KImageDouble &Window, int size, double sigma = 1.0);
    static void ImageSub_double(KImageGray &igMain, KImageGray &igSub, KImageDouble &output);
    static void diff_double(KImageGray &igMain, KImageDouble &d_dx, KImageDouble &d_dy);
    static void crop_double(KImageDouble &idMain, KImageDouble &output, int pX, int pY, int width, int height);
    static void MakeMat_2Col(KImageDouble &id0, KImageDouble &id1, KImageDouble &output, int size);
    static void MakeMat_1Col(KImageDouble &idMain, KImageDouble &output, int size);
    static void TranMat(KImageDouble &idMain, KImageDouble &output);
    static void MultiMat(KImageDouble &id0, KImageDouble &id1, KImageDouble &output);
    static void InvMat22(KImageDouble &idMain, KImageDouble &output);
    static void DrawLine(KImageColor &igMain, int pX, int pY, double u, double v);
    ~pshCV();
};

#endif // PSHCV_H
