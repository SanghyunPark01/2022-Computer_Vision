#include "pshCV.h"
#include <cstdlib>
#include <time.h>
#include <vector>
#include <fstream>
#include <math.h>


typedef std::vector<std::vector<EdgeInfo>*> EDGE_INFO;

EDGE_INFO Edges;

pshCV::pshCV()
{
    //class function
}
void pshCV::Thresholded(const KImageGray& inputimage, int value){
    int Thd = value;
    double _k_drow = inputimage.Row();
    double _k_dcol = inputimage.Col();

    for(int i=0; i< _k_drow; i++){
        for(int j=0; j < _k_dcol; j++){
            if(inputimage[i][j] < Thd){
                inputimage[i][j] = 0;
            }else{
                inputimage[i][j] = 255;
            }
        }
    }
}
void pshCV::OtsuThresholded(const KImageGray& inputimage){
    double dThd = 0;

    dThd = pshCV::_FindOtsuValue(inputimage);
    pshCV::Thresholded(inputimage, dThd);
}
int pshCV::_FindOtsuValue(KImageGray inputimage){
    int histo[256] = {0, };
    int iPixelNum = 0;

    for(int i=0; i < inputimage.Row(); i++){
        for(int j=0; j < inputimage.Col(); j++){
            iPixelNum++;
            histo[inputimage[i][j]]++;
        }
    }
    double P[256] = {0, };
    double Mu_g = 0;
    for(int i=0; i < 256; i++){
        P[i]=histo[i]/(double)iPixelNum;
        Mu_g += i*P[i];
    }

    double q1[256] = {0, };
    q1[0] = P[0];
    double q2[256] = {0, };
    double Mu1[256] = {0, };
    double Mu2[256] = {0, };
    double Variance_b[256] = {0, };
    for(int t=0; t <= 254; t++){
        q1[t+1] = q1[t] + P[t+1];
        q2[t+1] = 1 - q1[t+1];
        if(q1[t+1] == 0){
            Mu1[t+1] = 0;
            continue;
        }
        if(q2[t+1] == 0){
            Mu2[t+1] = 0;
            continue;
        }

        Mu1[t+1] = (q1[t]*Mu1[t] + (t+1)*P[t+1]) / q1[t+1];
        Mu2[t+1] = (Mu_g - q1[t+1]*Mu1[t]) / (1 - q1[t+1]);
        Variance_b[t+1] = q1[t+1]*q2[t+1]*pow((Mu1[t+1] - Mu2[t+1]),2);
    }
    double Max_var=Variance_b[0];
    int Thd = 0;
    for(int i=1; i <= 255; i++){
        if(Variance_b[i] > Max_var){
            Max_var = Variance_b[i];
            Thd = i;
        }
    }
    //std::cout<< Thd <<std::endl;;
    return Thd;
}
void pshCV::Dilated(const KImageGray& inputimage, int kernel_size){
    int nRow = inputimage.Row();
    int nCol = inputimage.Col();

    KImageGray igOut = inputimage;
    if(kernel_size == 3)
    {
        for(int i=1,ii=nRow-2; ii; i++,ii--)
            for(int j=1,jj=nCol-2; jj; j++,jj--)
            {
                if(inputimage[i][j] == 0)
                    if(inputimage[i-1][j-1] || inputimage[i-1][j] || inputimage[i-1][j+1] || inputimage[i][j-1]
                            || inputimage[i][j+1] || inputimage[i+1][j-1] || inputimage[i+1][j] || inputimage[i+1][j+1])
                        igOut[i][j] = 255;
            }
    }else if(kernel_size == 5){
        for(int i=2,ii=nRow-4; ii; i++,ii--)
            for(int j=2,jj=nCol-4; jj; j++,jj--)
            {
                if(inputimage[i][j] == 0)
                    if(inputimage[i-1][j-1] || inputimage[i-1][j] || inputimage[i-1][j+1] || inputimage[i][j-1]
                            || inputimage[i][j+1] || inputimage[i+1][j-1] || inputimage[i+1][j] || inputimage[i+1][j+1]
                            || inputimage[i-2][j-2] || inputimage[i-2][j-1] || inputimage[i-2][j] || inputimage[i-2][j+1]
                            || inputimage[i-2][j+2] || inputimage[i-1][j-2] || inputimage[i-1][j+2] || inputimage[i][j-2]
                            || inputimage[i][j+2] || inputimage[i+1][j-2] || inputimage[i+1][j+2] || inputimage[i+2][j-2]
                            || inputimage[i+2][j-2] || inputimage[i+2][j-1] || inputimage[i+2][j] || inputimage[i+2][j+1]
                            || inputimage[i+2][j+2])
                        igOut[i][j] = 255;
            }
    }else{
        return;
    }

    for(int i=0; i<nRow ; i++){
        for(int j=0; j<nCol;j++){
            inputimage[i][j] = igOut[i][j];
        }
    }

}
void pshCV::Eroded(const KImageGray& inputimage, int kernel_size){
    int nRow = inputimage.Row();
    int nCol = inputimage.Col();

    KImageGray igOut = inputimage;
    if(kernel_size == 3)
    {
        for(int i=1,ii=nRow-2; ii; i++,ii--)
            for(int j=1,jj=nCol-2; jj; j++,jj--)
            {
                if(inputimage[i][j] == 255)
                    if(inputimage[i-1][j-1]==0 || inputimage[i-1][j]==0 || inputimage[i-1][j+1]==0 || inputimage[i][j-1]==0
                            || inputimage[i][j+1]==0 || inputimage[i+1][j-1]==0 || inputimage[i+1][j]==0 || inputimage[i+1][j+1]==0)
                        igOut[i][j] = 0;
            }
    }else if(kernel_size == 5){
        for(int i=2,ii=nRow-4; ii; i++,ii--)
            for(int j=2,jj=nCol-4; jj; j++,jj--)
            {
                if(inputimage[i][j] == 255)
                    if(inputimage[i-1][j-1]==0 || inputimage[i-1][j]==0 || inputimage[i-1][j+1]==0 || inputimage[i][j-1]==0
                            || inputimage[i][j+1]==0 || inputimage[i+1][j-1]==0 || inputimage[i+1][j]==0 || inputimage[i+1][j+1]==0
                            || inputimage[i-2][j-2]==0 || inputimage[i-2][j-1]==0 || inputimage[i-2][j]==0 || inputimage[i-2][j+1]==0
                            || inputimage[i-2][j+2]==0 || inputimage[i-1][j-2]==0 || inputimage[i-1][j+2]==0 || inputimage[i][j-2]==0
                            || inputimage[i][j+2]==0 || inputimage[i+1][j-2]==0 || inputimage[i+1][j+2]==0 || inputimage[i+2][j-2]==0
                            || inputimage[i+2][j-2]==0 || inputimage[i+2][j-1]==0 || inputimage[i+2][j]==0 || inputimage[i+2][j+1]==0
                            || inputimage[i+2][j+2]==0)
                        igOut[i][j] = 0;
            }
    }else{
        return;
    }

    for(int i=0; i<nRow ; i++){
        for(int j=0; j<nCol;j++){
            inputimage[i][j] = igOut[i][j];
        }
    }
}
bool pshCV::CheckBinaryImage(KImageGray inputimage){
    int nRow = inputimage.Row();
    int nCol = inputimage.Col();

    bool check = true;
    for(int i=0; i<nRow ; i++){
        for(int j=0; j<nCol;j++){
            if(inputimage[i][j] != 255 && inputimage[i][j] != 0) check = false;
        }
    }
    return check;
}
bool pshCV::Labeling(const KImageColor& outputimage, KImageGray inputimage){
    int nRow = inputimage.Row();
    int nCol = inputimage.Col();

    int nForeground = 255;
    int nBackground = 0;

    srand((unsigned int)time(NULL));

    int nRandnum1 = rand() % 100;
    int nRandnum2 = rand() % 100;
    int nRandnum3 = rand() % 100;

    for(int i = 1; i < nRow-1 ;i++){
        for(int j = 1; j < nCol-1 ;j++){
            if(inputimage[i][j] == nForeground){
                if(inputimage[i-1][j-1] == nBackground && inputimage[i-1][j] == nBackground && inputimage[i][j-1] == nBackground){
                    outputimage[i][j].r = (i * nRandnum1 + j) % 256;
                    outputimage[i][j].g = (i * nRandnum2 + j) % 256;
                    outputimage[i][j].b = (i * nRandnum3 + j) % 256;
                    if(outputimage[i][j].r == 0 && outputimage[i][j].g == 0 && outputimage[i][j].b == 0){
                        outputimage[i][j].r = 140;
                    }
                }else if(inputimage[i-1][j-1] == nBackground && inputimage[i-1][j] == nForeground && inputimage[i][j-1] == nBackground){
                    if(outputimage[i-1][j].r == 0 && outputimage[i-1][j].g == 0 && outputimage[i-1][j].b == 0){
                        outputimage[i-1][j].r = (i * nRandnum1 + j) % 256;
                        outputimage[i-1][j].g = (i * nRandnum2 + j) % 256;
                        outputimage[i-1][j].b = (i * nRandnum3 + j) % 256;
                    }
                    outputimage[i][j].r = outputimage[i-1][j].r;
                    outputimage[i][j].g = outputimage[i-1][j].g;
                    outputimage[i][j].b = outputimage[i-1][j].b;
                }else if(inputimage[i-1][j-1] == nBackground && inputimage[i-1][j] == nBackground && inputimage[i][j-1] == nForeground){
                    if(outputimage[i][j-1].r == 0 && outputimage[i][j-1].g == 0 && outputimage[i][j-1].b == 0){
                        outputimage[i][j-1].r = (i * nRandnum1 + j) % 256;
                        outputimage[i][j-1].g = (i * nRandnum2 + j) % 256;
                        outputimage[i][j-1].b = (i * nRandnum3 + j) % 256;
                    }
                    outputimage[i][j].r = outputimage[i][j-1].r;
                    outputimage[i][j].g = outputimage[i][j-1].g;
                    outputimage[i][j].b = outputimage[i][j-1].b;
                }else if(inputimage[i-1][j-1] == nBackground && inputimage[i-1][j] == nForeground && inputimage[i][j-1] == nForeground){
                    if(outputimage[i-1][j].r == 0 && outputimage[i-1][j].g == 0 && outputimage[i-1][j].b == 0){
                        outputimage[i-1][j].r = (i * nRandnum1 + j) % 256;
                        outputimage[i-1][j].g = (i * nRandnum2 + j) % 256;
                        outputimage[i-1][j].b = (i * nRandnum3 + j) % 256;
                    }
                    outputimage[i][j-1].r = outputimage[i-1][j].r;
                    outputimage[i][j-1].g = outputimage[i-1][j].g;
                    outputimage[i][j-1].b = outputimage[i-1][j].b;
                    outputimage[i][j].r = outputimage[i-1][j].r;
                    outputimage[i][j].g = outputimage[i-1][j].g;
                    outputimage[i][j].b = outputimage[i-1][j].b;
                }else if(inputimage[i-1][j-1] == nForeground && inputimage[i-1][j] == nBackground && inputimage[i][j-1] == nBackground){
                    if(outputimage[i-1][j-1].r == 0 && outputimage[i-1][j-1].g == 0 && outputimage[i-1][j-1].b == 0)
                    {
                        outputimage[i-1][j-1].r = (i * nRandnum1 + j) % 256;
                        outputimage[i-1][j-1].g = (i * nRandnum2 + j) % 256;
                        outputimage[i-1][j-1].b = (i * nRandnum3 + j) % 256;
                    }
                    outputimage[i][j].r = outputimage[i-1][j-1].r;
                    outputimage[i][j].g = outputimage[i-1][j-1].g;
                    outputimage[i][j].b = outputimage[i-1][j-1].b;
                }else if(inputimage[i-1][j-1] == nForeground && inputimage[i-1][j] == nForeground && inputimage[i][j-1] == nForeground){
                    if(outputimage[i-1][j].r == 0 && outputimage[i-1][j].g == 0 && outputimage[i-1][j].b == 0)
                    {
                        outputimage[i-1][j].r = (i * nRandnum1 + j) % 256;
                        outputimage[i-1][j].g = (i * nRandnum2 + j) % 256;
                        outputimage[i-1][j].b = (i * nRandnum3 + j) % 256;
                    }
                    outputimage[i][j].r = outputimage[i-1][j].r;
                    outputimage[i][j].g = outputimage[i-1][j].g;
                    outputimage[i][j].b = outputimage[i-1][j].b;
                    outputimage[i-1][j-1].r = outputimage[i-1][j].r;
                    outputimage[i-1][j-1].g = outputimage[i-1][j].g;
                    outputimage[i-1][j-1].b = outputimage[i-1][j].b;
                    outputimage[i][j-1].r = outputimage[i-1][j].r;
                    outputimage[i][j-1].g = outputimage[i-1][j].g;
                    outputimage[i][j-1].b = outputimage[i-1][j].b;
                }else if(inputimage[i-1][j-1] == nForeground && inputimage[i-1][j] == nBackground && inputimage[i][j-1] == nForeground){
                    if(outputimage[i][j-1].r == 0 && outputimage[i][j-1].g == 0 && outputimage[i][j-1].b == 0)
                    {
                        outputimage[i][j-1].r = (i * nRandnum1 + j) % 256;
                        outputimage[i][j-1].g = (i * nRandnum2 + j) % 256;
                        outputimage[i][j-1].b = (i * nRandnum3 + j) % 256;
                    }
                    outputimage[i][j].r = outputimage[i][j-1].r;
                    outputimage[i][j].g = outputimage[i][j-1].g;
                    outputimage[i][j].b = outputimage[i][j-1].b;
                    outputimage[i-1][j].r = outputimage[i][j-1].r;
                    outputimage[i-1][j].g = outputimage[i][j-1].g;
                    outputimage[i-1][j].b = outputimage[i][j-1].b;
                    outputimage[i-1][j-1].r = outputimage[i][j-1].r;
                    outputimage[i-1][j-1].g = outputimage[i][j-1].g;
                    outputimage[i-1][j-1].b = outputimage[i][j-1].b;
                }else if(inputimage[i-1][j-1] == nForeground && inputimage[i-1][j] == nForeground && inputimage[i][j-1] == nBackground){
                    if(outputimage[i-1][j].r == 0 && outputimage[i-1][j].g == 0 && outputimage[i-1][j].b == 0)
                    {
                        outputimage[i-1][j].r = (i * nRandnum1 + j) % 256;
                        outputimage[i-1][j].g = (i * nRandnum2 + j) % 256;
                        outputimage[i-1][j].b = (i * nRandnum3 + j) % 256;
                    }
                    outputimage[i][j].r = outputimage[i-1][j].r;
                    outputimage[i][j].g = outputimage[i-1][j].g;
                    outputimage[i][j].b = outputimage[i-1][j].b;
                    outputimage[i][j-1].r = outputimage[i-1][j].r;
                    outputimage[i][j-1].g = outputimage[i-1][j].g;
                    outputimage[i][j-1].b = outputimage[i-1][j].b;
                }
            }
        }
    }
    for(int i = 1 ; i < nRow-1; i++){
        for(int j = nCol-2; j > 1 ;j--){
            if(inputimage[i][j] == nForeground){
                if(inputimage[i-1][j-1] == nBackground && inputimage[i-1][j] == nBackground && inputimage[i][j-1] == nForeground){
                    outputimage[i][j-1].r = outputimage[i][j].r;
                    outputimage[i][j-1].g = outputimage[i][j].g;
                    outputimage[i][j-1].b = outputimage[i][j].b;
                }else if(inputimage[i-1][j-1] == nForeground && inputimage[i-1][j] == nForeground && inputimage[i][j-1] == nBackground){
                    outputimage[i][j].r = outputimage[i-1][j].r;
                    outputimage[i][j].g = outputimage[i-1][j].g;
                    outputimage[i][j].b = outputimage[i-1][j].b;
                    outputimage[i][j-1].r = outputimage[i-1][j].r;
                    outputimage[i][j-1].g = outputimage[i-1][j].g;
                    outputimage[i][j-1].b = outputimage[i-1][j].b;
                }else if(inputimage[i-1][j-1] == nForeground && inputimage[i-1][j] == nForeground && inputimage[i][j-1] == nForeground){
                    outputimage[i][j].r = outputimage[i-1][j].r;
                    outputimage[i][j].g = outputimage[i-1][j].g;
                    outputimage[i][j].b = outputimage[i-1][j].b;
                    outputimage[i-1][j-1].r = outputimage[i-1][j].r;
                    outputimage[i-1][j-1].g = outputimage[i-1][j].g;
                    outputimage[i-1][j-1].b = outputimage[i-1][j].b;
                    outputimage[i][j-1].r = outputimage[i-1][j].r;
                    outputimage[i][j-1].g = outputimage[i-1][j].g;
                    outputimage[i][j-1].b = outputimage[i-1][j].b;
                }
            }
        }
    }

    for(int i = nRow-2 ; i > 1; i--){
        for(int j = nCol-2; j > 1 ;j--){
            if(inputimage[i][j] == nForeground){
                if(inputimage[i-1][j-1] == nBackground && inputimage[i-1][j] == nBackground && inputimage[i][j-1] == nForeground){
                    outputimage[i][j-1].r = outputimage[i][j].r;
                    outputimage[i][j-1].g = outputimage[i][j].g;
                    outputimage[i][j-1].b = outputimage[i][j].b;
                }else if(inputimage[i-1][j-1] == nBackground && inputimage[i-1][j] == nForeground && inputimage[i][j-1] == nBackground){
                    outputimage[i-1][j].r = outputimage[i][j].r;
                    outputimage[i-1][j].g = outputimage[i][j].g;
                    outputimage[i-1][j].b = outputimage[i][j].b;
                }else if(inputimage[i-1][j-1] == nForeground && inputimage[i-1][j] == nForeground && inputimage[i][j-1] == nForeground){
                    outputimage[i-1][j].r = outputimage[i][j].r;
                    outputimage[i-1][j].g = outputimage[i][j].g;
                    outputimage[i-1][j].b = outputimage[i][j].b;
                    outputimage[i-1][j-1].r = outputimage[i][j].r;
                    outputimage[i-1][j-1].g = outputimage[i][j].g;
                    outputimage[i-1][j-1].b = outputimage[i][j].b;
                    outputimage[i][j-1].r = outputimage[i][j].r;
                    outputimage[i][j-1].g = outputimage[i][j].g;
                    outputimage[i][j-1].b = outputimage[i][j].b;
                }
            }
        }
    }




}
void pshCV::HistoEQ(const KImageColor& inputimage){
    KImageGray R(inputimage.Row(),inputimage.Col());
    KImageGray G(inputimage.Row(),inputimage.Col());
    KImageGray B(inputimage.Row(),inputimage.Col());
    for (int i = 0; i < inputimage.Row(); i++) {
       for (int j = 0; j < inputimage.Col(); j++) {
           R[i][j] = inputimage[i][j].r;
           G[i][j] = inputimage[i][j].g;
           B[i][j] = inputimage[i][j].b;
       }
    }

    pshCV::_HistoValue(R);
    pshCV::_HistoValue(G);
    pshCV::_HistoValue(B);

    for(int i=0; i < inputimage.Row();i++){
        for(int j=0; j<inputimage.Col();j++){
            inputimage[i][j].r = R[i][j];
            inputimage[i][j].g = G[i][j];
            inputimage[i][j].b = B[i][j];
        }
    }

}
void pshCV::_Histo(KImageGray input,int histo[]){
    for (int i = 0; i < input.Row(); i++) {
        for (int j = 0; j < input.Col(); j++) {
            histo[input[i][j]] += 1;
        }
    }
}
void pshCV::_HistoValue(KImageGray& value){
    int nImgSize = value.Size();
    int histo[256] = {0, };
    pshCV::_Histo(value, histo);
    //sum - integral
    for(int i = 0;i<255;i++){
        histo[i+1] += histo[i];
    }

    //probability
    double dPHisto[256] = {0,};
    for(int i=0; i<256;i++){
        dPHisto[i] = (double)histo[i]/nImgSize;
    }

    //Equalization
    for(int i = 0; i< value.Row();i++){
        for(int j = 0; j< value.Col();j++){
            value[i][j] = (dPHisto[value[i][j]]*255);
        }
    }
}
void pshCV::HistoMatching(const KImageColor& SourceImage, KImageColor ReferImage){//target=reference
    int nSourceImg_Size = SourceImage.Size();
    int nRefImg_Size = ReferImage.Size();

    KImageGray R(SourceImage.Row(),SourceImage.Col());
    KImageGray G(SourceImage.Row(),SourceImage.Col());
    KImageGray B(SourceImage.Row(),SourceImage.Col());
    KImageGray r_R(ReferImage.Row(),ReferImage.Col());
    KImageGray r_G(ReferImage.Row(),ReferImage.Col());
    KImageGray r_B(ReferImage.Row(),ReferImage.Col());

    for(int i = 0; i<SourceImage.Row();i++){
        for(int j=0; j<SourceImage.Col();j++){
            R[i][j] = SourceImage[i][j].r;
            G[i][j] = SourceImage[i][j].g;
            B[i][j] = SourceImage[i][j].b;
        }
    }
    for(int i = 0; i<ReferImage.Row();i++){
        for(int j=0; j<ReferImage.Col();j++){
            r_R[i][j] = ReferImage[i][j].r;
            r_G[i][j] = ReferImage[i][j].g;
            r_B[i][j] = ReferImage[i][j].b;
        }
    }
    int Source_histo[3][256] = {{0, }, }; //rgb
    int Refer_histo[3][256] = {{0, }, }; //rgb
    double PSource_histo[3][256] = {{0, }, }; //rgb
    double PRefer_histo[3][256] = {{0, }, }; //rgb
    int transform[3][256] = {{0, } };
    pshCV::_Histo(R, Source_histo[0]);
    pshCV::_Histo(G, Source_histo[1]);
    pshCV::_Histo(B, Source_histo[2]);
    pshCV::_Histo(r_R, Refer_histo[0]);
    pshCV::_Histo(r_G, Refer_histo[1]);
    pshCV::_Histo(r_B, Refer_histo[2]);

    for(int k = 0; k<3;k++){//rgb
        for(int i = 0 ; i<255;i++){
            Source_histo[k][i+1] += Source_histo[k][i];
            Refer_histo[k][i+1] += Refer_histo[k][i];
        }
        for(int i=0;i<256;i++){
            PSource_histo[k][i] = (double)Source_histo[k][i]/nSourceImg_Size;
            PRefer_histo[k][i] = (double)Refer_histo[k][i]/nRefImg_Size;
        }
        for(int i=0;i<256;i++){
            for(int j=0;j<256;j++){
                if(PSource_histo[k][i]<PRefer_histo[k][j]){
                    if(j == 0){
                        transform[k][i]=j;
                    }else{
                        transform[k][i]=abs(PRefer_histo[k][j]-PSource_histo[k][i])<abs(PRefer_histo[k][j-1]-PSource_histo[k][i])?j:j-1;
                    }
                    break;
                }
                if(j==255){
                    transform[k][i] = j;
                }
            }
        }

    }
    for(int i = 0; i< SourceImage.Row();i++){
        for(int j = 0; j< SourceImage.Col();j++){
            SourceImage[i][j].r = transform[0][R[i][j]];
            SourceImage[i][j].g = transform[1][G[i][j]];
            SourceImage[i][j].b = transform[2][B[i][j]];
        }
    }
}
void pshCV::GaussianNoised(const KImageColor& icImg, double dSigma){
    KGaussian kGN;
    kGN.Create(0,dSigma*dSigma);
    kGN.OnRandom(icImg.Size());

    double dGNoise;
    double dGain = 8;

    for(unsigned int i = 0; i < icImg.Row();i++){
        for(unsigned int j = 0 ; j < icImg.Col() ; j++){
            dGNoise = kGN.Generate();

            //RGB
            if (icImg[i][j].r + dGNoise * dGain > 255){
                icImg[i][j].r = 255;
            }else if (icImg[i][j].r + dGNoise * dGain < 0){
                icImg[i][j].r = 0;
            }else
                icImg[i][j].r += dGNoise * dGain;

            if (icImg[i][j].g + dGNoise * dGain > 255){
                icImg[i][j].g = 255;
            }else if (icImg[i][j].g + dGNoise * dGain < 0){
                icImg[i][j].g = 0;
            }else
                icImg[i][j].g += dGNoise * dGain;

            if (icImg[i][j].b + dGNoise * dGain > 255){
                icImg[i][j].b = 255;
            }else if (icImg[i][j].b + dGNoise * dGain < 0){
                icImg[i][j].b = 0;
            }else
                icImg[i][j].b += dGNoise * dGain;
        }
    }
}
void pshCV::SaltAndPepperNoised(const KImageColor& icImg){
    srand((unsigned int)time(NULL));

        for (unsigned int i = 0; i < icImg.Row(); i++) {
            for (unsigned int j = 0; j < icImg.Col(); j++) {
                int t = rand() % 1000;
                if (t < 25) {
                    if (t > 12) {
                        //salt noise
                        icImg[i][j].r = 255;
                        icImg[i][j].g = 255;
                        icImg[i][j].b = 255;
                    }
                    else {
                        //pepper noise
                        icImg[i][j].r = 0;
                        icImg[i][j].g = 0;
                        icImg[i][j].b = 0;
                    }
                }
            }
        }
}

void pshCV::BoxFiltering(const KImageColor& icImg, int KSize){
    int row = icImg.Row();
    int col = icImg.Col();
    KImageColor pFImg = icImg;

    int m = KSize / 2;

    for (int i = m; i < row - m; i++) {
        for (int j = m; j < col - m; j++) {
            // R
            int temp_r = 0;
            for (int ii = -m; ii <= m; ii++) {
                for (int jj = -m; jj <= m; jj++) {
                    temp_r += icImg[i + ii][j + jj].r;
                }
            }
            pFImg[i][j].r = temp_r / (KSize * KSize);

            // G
            int temp_g = 0;
            for (int ii = -m; ii <= m; ii++) {
                for (int jj = -m; jj <= m; jj++) {
                    temp_g += icImg[i + ii][j + jj].g;
                }
            }
            pFImg[i][j].g = temp_g / (KSize * KSize);

            // B
            int temp_b = 0;
            for (int ii = -m; ii <= m; ii++) {
                for (int jj = -m; jj <= m; jj++) {
                    temp_b += icImg[i + ii][j + jj].b;
                }
            }
            pFImg[i][j].b = temp_b / (KSize * KSize);
        }
    }

    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            icImg[i][j].r = pFImg[i][j].r;
            icImg[i][j].g = pFImg[i][j].g;
            icImg[i][j].b = pFImg[i][j].b;
        }
    }

}
void pshCV::GaussianFiltering(const KImageColor& icImg ,double dSigma){
    int i,j,r,c;

    int row = icImg.Row();
    int col = icImg.Col();
    KImageColor pFImg = icImg;

    int nHalf = (int)(3.0 * dSigma + 0.3);
    KMatrix mMask(nHalf * 2 +1,nHalf*2+1);

    double dScale = 0.0, dSigma2 = 2.0*_SQR(dSigma);
    double dConst = 1.0 / _2PI/_SQR(dSigma);

    for(r = -nHalf,i=0 ; r <= nHalf ; r++,i++){
        for(c = -nHalf,j=0 ; c <= nHalf ; c++,j++){
            mMask[i][j] = dConst*exp(-(r*r+c*c)/dSigma2);
            dScale += mMask[i][j];
        }
    }
    mMask /= dScale;

    double dR,dG,dB;
    for (int i = nHalf; i < row - nHalf; i++) {
        for (int j = nHalf; j < col - nHalf; j++) {
            dR = dG = dB = 0;
            for (int ii = -nHalf, r = 0; ii <= nHalf; ii++, r++) {
                for (int jj = -nHalf, c = 0; jj <= nHalf; jj++, c++) {
                    dR += icImg[i + ii][j + jj].r * mMask[r][c];
                    dG += icImg[i + ii][j + jj].g * mMask[r][c];
                    dB += icImg[i + ii][j + jj].b * mMask[r][c];
                }
            }
            pFImg[i][j].r = (unsigned char)dR;
            pFImg[i][j].g = (unsigned char)dG;
            pFImg[i][j].b = (unsigned char)dB;
           }
    }
    for(int i = 0; i <row; i++){
        for(int j = 0; j<col;j++){
            icImg[i][j].r = pFImg[i][j].r;
            icImg[i][j].g = pFImg[i][j].g;
            icImg[i][j].b = pFImg[i][j].b;
        }
    }
}
void pshCV::MedianFiltering(const KImageColor& icImg, int KSize){
    int row = icImg.Row();
    int col = icImg.Col();
    KImageColor pFImg = icImg;

    int nHalf = KSize / 2;
    KMatrix mMaskArr(3,KSize*KSize); //3 means r,g,b / k*k means sorted array
    int index;
    for (int i = nHalf; i < row - nHalf; i++) {
        for (int j = nHalf; j < col - nHalf; j++) {
            index = 0;
            for (int ii = -nHalf; ii <= nHalf; ii++) {
                for (int jj = -nHalf; jj <= nHalf; jj++, index++) {
                    mMaskArr[0][index] = icImg[i + ii][j + jj].r; //r
                    mMaskArr[1][index] = icImg[i + ii][j + jj].g; //g
                    mMaskArr[2][index] = icImg[i + ii][j + jj].b; //b
                }
            }

            // Sort
            for (int k = 0; k < index; k++) {
                for (int l = k + 1; l < index; l++) {
                    // r
                    if (mMaskArr[0][k] > mMaskArr[0][l]) {
                        int buff = mMaskArr[0][k];
                        mMaskArr[0][k] = mMaskArr[0][l];
                        mMaskArr[0][l] = buff;
                    }

                    // g
                    if (mMaskArr[1][k] > mMaskArr[1][l]) {
                        int buff = mMaskArr[1][k];
                        mMaskArr[1][k] = mMaskArr[1][l];
                        mMaskArr[1][l] = buff;
                    }

                    // b
                    if (mMaskArr[2][k] > mMaskArr[2][l]) {
                        int buff = mMaskArr[2][k];
                        mMaskArr[2][k] = mMaskArr[2][l];
                        mMaskArr[2][l] = buff;
                    }
                }
            }

            pFImg[i][j].r = mMaskArr[0][index / 2];
            pFImg[i][j].g = mMaskArr[1][index / 2];
            pFImg[i][j].b = mMaskArr[2][index / 2];
        }
    }
    for(int i = 0; i <row; i++){
        for(int j = 0; j<col;j++){
            icImg[i][j].r = pFImg[i][j].r;
            icImg[i][j].g = pFImg[i][j].g;
            icImg[i][j].b = pFImg[i][j].b;
        }
    }

}
void pshCV::CannyEdged(KImageGray& igImg, double dSigma, int nHighThld, int nLowThld){
    int nRow = igImg.Row();
    int nCol = igImg.Col();
    KMatrix mEdgeDir(nRow, nCol);
    KImageGray igFDG(nRow, nCol);
    KImageGray igMaxima(nRow, nCol);
    KImageGray igCannyEdge(nRow, nCol);
    Edges.clear();
    std::vector<EdgeInfo>* vEdgeCol;
    for (int i = 0; i < nRow; i++) {
        vEdgeCol = new std::vector<EdgeInfo>(nCol);
        Edges.push_back(vEdgeCol);
    }

    // DOG
    int nH = (int)(3 * dSigma + 0.3);
    double dScale = 0;
    KMatrix mDOG_X(nH * 2 + 1, nH * 2 + 1);
    KMatrix mDOG_Y(nH * 2 + 1, nH * 2 + 1);
    double dDOG_constant = 1 / (2 * 3.14 * pow(dSigma, 4));
    double dDOG_temp;

    for (int i = 0, r = -nH; r <= nH; i++, r++) {
        dDOG_temp = -r * exp(-(r * r) / (2 * dSigma * dSigma));
        for (int j = 0, c = -nH; c <= nH; j++, c++) {
            mDOG_X[i][j] = dDOG_constant * dDOG_temp * exp(-(c * c) / (2 * dSigma * dSigma));
            mDOG_Y[j][i] = mDOG_X[i][j];

            // Half scailing
            if (r < 0) {
                dScale += mDOG_X[i][j];
            }
        }
    }
    mDOG_X /= -dScale;
    mDOG_Y /= -dScale;

    // Convolution
    double dTempX = 0, dTempY = 0;
    for (int i = nH; i < nRow - nH; i++) {
        for (int j = nH; j < nCol - nH; j++) {
            dTempX = dTempY = 0;
            for (int ii = -nH, r = 0; ii <= nH; ii++, r++) {
                for (int jj = -nH, c = 0; jj <= nH; jj++, c++) {
                    dTempX += igImg[i + ii][j + jj] * mDOG_X[r][c];
                    dTempY += igImg[i + ii][j + jj] * mDOG_Y[r][c];
                }
            }
            // Magnitude
            igFDG[i][j] = fabs(dTempX) + fabs(dTempY);

            // Orientation
            // Store the edge pixel
            mEdgeDir[i][j] = (unsigned char)((((int)(atan2(dTempY, dTempX) * (180.0 / 3.14) / 22.5) + 1) >> 1) & 0x00000003);

            Edges[i]->at(j).u = dTempX / sqrt(dTempX * dTempX + dTempY * dTempY);
            Edges[i]->at(j).v = dTempY / sqrt(dTempX * dTempX + dTempY * dTempY);
            Edges[i]->at(j).Dir = mEdgeDir[i][j];
            Edges[i]->at(j).Mag = fabs(dTempX) + fabs(dTempY);
            Edges[i]->at(j).Ang = (180.0 / 3.14) * atan2(dTempY, dTempX) + 0.5; // 0 ~ 360 degree

        }
    }

    // Non-Maxima Suppression
    igMaxima = igFDG;
    int dx[4] = {1, 1, 0, -1};
    int dy[4] = {0, 1, 1, 1};
    int dir = 0;
    for (int i = 1; i < nRow - 1; i++) {
        for (int j = 1; j < nCol - 1; j++) {
            dir = mEdgeDir[i][j];

            if (igFDG[i][j] > igFDG[i + dy[dir]][j + dx[dir]] && igFDG[i][j] > igFDG[i - dy[dir]][j - dx[dir]]) {
                if (igFDG[i][j] >= nHighThld) {
                    igMaxima[i][j] = 255;
                }
                else if (igFDG[i][j] < nLowThld) {
                    igMaxima[i][j] = 0;
                }
            }
            else {
                igMaxima[i][j] = 0;
            }
        }
    }

    // Hysteresis Thresholding
    igCannyEdge = igMaxima;
    for (int i = 1; i < nRow - 1; i++) {
        for (int j = 1; j < nCol - 1; j++) {
            if (igCannyEdge[i][j] != 0 && igCannyEdge[i][j] < 255) {
                if (igCannyEdge[i - 1][j - 1] == 255 || igCannyEdge[i - 1][j] == 255 || igCannyEdge[i - 1][j + 1] == 255 ||
                    igCannyEdge[i][j - 1] == 255 || igCannyEdge[i][j + 1] == 255 ||igCannyEdge[i + 1][j - 1] == 255 ||
                    igCannyEdge[i + 1][j] == 255 || igCannyEdge[i + 1][j + 1] == 255) {
                    igCannyEdge[i][j] = 255;
                }
                else {
                    igCannyEdge[i][j] = 0;
                }
            }
        }
    }
    // Result
    for(int i = 0; i < nRow; i++){
        for(int j = 0; j < nCol; j++ ){
            igImg[i][j] = igCannyEdge[i][j];
        }
    }
}
KImageColor pshCV::CircleHoughTransform(KImageGray igImg, int nRadius){
    int nRow = igImg.Row();
    int nCol = igImg.Col();

    KImageGray icEdgeImg(igImg);
    pshCV::CannyEdged(icEdgeImg, 0.7, 80, 15);

    KImageDouble idResult(nRow, nCol);

    // Voting
    double dVoting[11][11];
    for(int i = -5; i < 6; i++){
        for(int j = -5; j < 6; j++){
            dVoting[i + 5][j + 5] = 1.0 / (3.14*2 * pow(0.7, 2)) * exp(-0.5 * (pow(i, 2) + pow(j, 2) / pow(0.7, 2)));//gaussian weight
        }
    }
    nRadius /= 2;
    int nTempCol, nTempRow;

    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            if (icEdgeImg[i][j] == 255) {
                // Voting
                nTempCol = j + Edges[i]->at(j).v * nRadius;
                nTempRow = i + Edges[i]->at(j).u * nRadius;
                if (nTempCol < 0 || nTempRow < 0 || nTempCol >= nCol || nTempRow >= nRow) {
                    continue;
                }

                for (int ii = -5; ii < 6; ii++) {
                    for (int jj = -5; jj < 6; jj++) {
                        if (nTempCol + jj < 0 || nTempRow + ii < 0 || nTempCol + jj >= nCol || nTempRow + ii >= nRow) {
                            continue;
                        }
                        idResult[nTempRow + ii][nTempCol + jj] += 40 * dVoting[ii + 5][jj + 5];
                    }
                }

                // voting
                nTempCol = j - Edges[i]->at(j).v * nRadius;
                nTempRow = i - Edges[i]->at(j).u * nRadius;
                if (nTempCol < 0 || nTempRow < 0 || nTempCol >= nCol || nTempRow >= nRow) {
                    continue;
                }

                for (int ii = -5; ii < 6; ii++) {
                    for (int jj = -5; jj < 6; jj++) {
                        if (nTempCol + jj < 0 || nTempRow + ii < 0 || nTempCol + jj >= nCol || nTempRow + ii >= nRow) {
                            continue;
                        }
                        idResult[nTempRow + ii][nTempCol + jj] += 40 * dVoting[ii + 5][jj + 5];
                    }
                }
            }
        }
    }

    KImageGray igVoting = idResult.ToGray();
    KImageColor icOutput = igVoting.GrayToRGB();
    int nMax = 0;
    int nPx, nPy;
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            if (igVoting[i][j] > nMax) {
                nPx = j;
                nPy = i;
                nMax = igVoting[i][j];
            }

        }
    }

    icOutput[nPy][nPx].r = 0;
    icOutput[nPy][nPx].g = 255;
    icOutput[nPy][nPx].b = 0;

    int nDegree = 0;
    int nRad;
    double dDx;
    double dDy;
    double dU;
    double dV;
    std::vector<std::pair<double,double>> vPoints;

    for (nDegree = 0; nDegree < 2000; nDegree++) {
        nRad = nDegree / 3.14;
        dDx = (double)nPy + nRadius * cos(nRad);
        dDy = (double)nPx + nRadius * sin(nRad);
        if (dDx < 0 || dDy < 0) {
            continue;
        }
        else {
            std::pair<double, double> vPoint = std::make_pair(dDx, dDy);
            vPoints.push_back(vPoint);
        }
    }

    //display
    while (!vPoints.empty()) {
        dU = vPoints.back().first;
        dV = vPoints.back().second;
        vPoints.pop_back();

        icOutput[(int)dU][(int)dV].r = 255;
        icOutput[(int)dU][(int)dV].g = 255;
        icOutput[(int)dU][(int)dV].b = 0;
    }

    return icOutput;
}
KImageColor pshCV::GeneralizedHoughTransform(KImageGray igImg){
    int nRow = igImg.Row();
    int nCol = igImg.Col();
    std::vector<std::pair<int, int>> vPoints;
    std::vector<std::pair<double, double>> vTables[4];
    KImageDouble idResult(nRow, nCol);

    KImageColor icError(nRow,nCol);

    // Read File
    //std::string directory = "C:\\Users\\SanghyunPark\\Desktop\\computer vision\\01_Homeworks_-_students\\data\\plug.txt";
    std::string sDirectory = ".\\data\\plug.txt";
    std::ifstream file(sDirectory);

    if(!file){
        std::cout<<"Unable to open file"<<std::endl;
        return icError;
    }

    int nX, nY;
    double dCx = 0, dCy = 0;

    int nn;
    file >> nn;
    while (!file.eof()) {
        file >> nX >> nY;
        vPoints.push_back(std::make_pair(nX, nY));
    }
    if (file.is_open()) {
        file.close();
    }

    for (unsigned int i = 0; i < vPoints.size(); i++) {
        dCx += vPoints[i].first;
        dCy += vPoints[i].second;
    }
    dCx /= vPoints.size();
    dCy /= vPoints.size();

    // Table
    int nDir;
    double dDist, dAngle;
    double dGradX, dGradY;
    for (int i = 1, ii = vPoints.size() - 2; ii; i++, ii--) {
        dGradX = (double)(vPoints[i + 1].first - vPoints[i - 1].first) + 1e-8;
        dGradY = (double)(vPoints[i + 1].second - vPoints[i - 1].second) + 1e-8;

        // setting Edge Direction
        double dTemp = (180 / 3.14) * (atan2(dGradY, dGradX));
        dTemp += 90.0;
        nDir = ((((int)(dTemp / 22.5) + 1) >> 1) & 0x00000003);

        // distance, angle
        dDist = sqrt((dCx - vPoints[i].first) * (dCx - vPoints[i].first) + (dCy - vPoints[i].second) * (dCy - vPoints[i].second));
        dAngle = (180.0 / 3.14) * atan2((double)(dCy - vPoints[i].second), (double)(dCx - vPoints[i].first));

        // add info to table
        vTables[nDir].push_back(std::make_pair(dDist, dAngle));
    }

    // Voting
    double dVoting[11][11];
    for(int i = -5; i < 6; i++){
        for(int j = -5; j < 6; j++){
            dVoting[i + 5][j + 5] = 1.0 / (3.14*2 * pow(0.7, 2)) * exp(-0.5 * (pow(i, 2) + pow(j, 2) / pow(0.7, 2)));     //gaussian weight
        }
    }

    int n_X, n_Y;
    double d_Angle;

    KImageGray igEdge(igImg);
    pshCV::CannyEdged(igEdge, 0.7, 80, 15);

    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            if (igEdge[i][j] == 255) {
                // Rotation
                for (int theta = 0; theta < 4; theta++) {
                    d_Angle = 90.0 * theta;
                    double dTemp = Edges[i]->at(j).Ang;
                    int nEdgeDir = ((((int)((d_Angle - dTemp + 90.0) / 22.5) + 1) >> 1) & 0x00000003);

                    for (unsigned long long k = 0; k < vTables[nEdgeDir].size(); k++) {
                        for (double dScale = 0.9; dScale <= 0.9; dScale += 0.05) {
                            // Voting
                            n_X = j + dScale * vTables[nEdgeDir][k].first * cos(_RADIAN(vTables[nEdgeDir][k].second + 90 * theta));
                            n_Y = i + dScale * vTables[nEdgeDir][k].first * sin(_RADIAN(vTables[nEdgeDir][k].second + 90 * theta));
                            if (n_X < 0 || n_Y < 0 || n_X >= nCol || n_Y >= nRow) {
                                continue;
                            }

                            for (int y = -5; y < 6; y++) {
                                for (int x = -5; x < 6; x++) {
                                    if (n_X + x < 0 || n_Y + y < 0 || n_X + x >= nCol || n_Y + y >= nRow) {
                                        continue;
                                    }
                                    idResult[n_Y + y][n_X + x] += 5 * dVoting[y + 5][x + 5];
                                }
                            }

                            // voting
                            n_X = j - dScale * vTables[nEdgeDir][k].first * cos(_RADIAN(vTables[nEdgeDir][k].second + 90 * theta));
                            n_Y = i - dScale * vTables[nEdgeDir][k].first * sin(_RADIAN(vTables[nEdgeDir][k].second + 90 * theta));
                            if (n_X < 0 || n_Y < 0 || n_X >= nCol || n_Y >= nRow) {
                                continue;
                            }

                            for (int y = -5; y < 6; y++) {
                                for (int x = -5; x < 6; x++) {
                                    if (n_X + x < 0 || n_Y + y < 0 || n_X + x >= nCol || n_Y + y >= nRow) {
                                        continue;
                                    }
                                    idResult[n_Y + y][n_X + x] += 5 * dVoting[y + 5][x + 5];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    KImageGray igVoting = idResult.ToGray();
    KImageColor icOutput = igVoting.GrayToRGB();
    int nMax = 0;
    int nPx, nPy;
    for (int i = 1; i < nRow - 1; i++) {
        for (int j = 1; j < nCol - 1; j++) {
            if (igVoting[i][j] > nMax) {
                nPx = j;
                nPy = i;
                nMax = igVoting[i][j];
            }

        }
    }
    icOutput[nPy][nPx].r = 0;
    icOutput[nPy][nPx].g = 255;
    icOutput[nPy][nPx].b = 0;
    // display
    for (nDir = 0; nDir < 4; nDir++) {
        for (unsigned long long i = 0; i < vTables[nDir].size(); i++) {
            int temp_x = nPx + vTables[nDir][i].first * cos(-3.14 / 2.0 + _RADIAN(vTables[nDir][i].second));
            int temp_y = nPy + vTables[nDir][i].first * sin(-3.14 / 2.0 + _RADIAN(vTables[nDir][i].second));
            if (temp_x < 0 || temp_y < 0 || temp_x >= nCol || temp_y >= nRow) {
                continue;
            }

            icOutput[temp_y][temp_x].r = 255;
            icOutput[temp_y][temp_x].g = 255;
        }
    }
    return icOutput;
}
void pshCV::OpticalFlow(KImageGray &igMain_0, KImageGray &igMain_1, KImageColor &output, int size){
    KImageDouble Window, subContain, d_dx, d_dy;

    subContain.Create(igMain_0.Row(),igMain_1.Col());
    int half = (int)(size/2);

    //qDebug() << "window";
    pshCV::Window_weight(Window,size,1);
    //qDebug() << "Sub";
    pshCV::ImageSub_double(igMain_0,igMain_1,subContain);
    //qDebug() << "diff";
    pshCV::diff_double(igMain_0,d_dx,d_dy);

    KImageDouble Ix, Iy, It;
    KImageDouble A, At, d, b, AtW,AtWb,AtWA, AtWAi;
    output.Create(igMain_0.Row(),igMain_0.Col());
    output = igMain_0.GrayToRGB();
    double u, v;
    for(int i = half; i < (int)igMain_0.Row()-half; i = i + 5){
        //qDebug() << i;
        for(int j = half; j < (int)igMain_0.Col()-half; j = j + 5){
            pshCV::crop_double(d_dx, Ix, j-half, i-half, size, size);
            pshCV::crop_double(d_dy,Iy,j-half,i-half,size,size);
            pshCV::crop_double(subContain,It,j-half,i-half,size,size);

            pshCV::MakeMat_2Col(Ix,Iy,A,size);
            pshCV::MakeMat_1Col(It,b,size);
            //qDebug() << "tran";
            pshCV::TranMat(A,At);

            //qDebug() << "multi";
            pshCV::MultiMat(At,Window,AtW);
            pshCV::MultiMat(AtW,b,AtWb);
            pshCV::MultiMat(AtW,A,AtWA);
            //qDebug() << "inv";
            pshCV::InvMat22(AtWA,AtWAi);
            //qDebug() << "d";
            pshCV::MultiMat(AtWAi,AtWb,d);
            u = d[0][0];
            v = d[1][0];
            //qDebug() << "draw";
            pshCV::DrawLine(output,j,i,u,v);
        }
    }


    qDebug() << "End";
}
void pshCV::Window_weight(KImageDouble &Window, int size, double sigma){
    KMatrix kernel = KGaussianMulti::Kernel_2D(sigma, size);
    Window.Create(size*size, size*size);

    int j = -1;
    for(int i = 0; i < size*size; i++){
        if( (i % size) == 0) j++;
        Window[i][i] = kernel[j][i%size];

        //qDebug() << Window[i][i];
    }


}

void pshCV::ImageSub_double(KImageGray &igMain, KImageGray &igSub, KImageDouble &output){
    output.Create(igMain.Row(),igMain.Col());

    if(igMain.Row() != igSub.Row() || igMain.Col() != igSub.Col()) return;

    for(int i = 0; i < (int)igMain.Row(); i++){
        for(int j = 0; j < (int)igMain.Col(); j++){
            output[i][j] = igMain[i][j] - igSub[i][j];
        }
    }
}
void pshCV::crop_double(KImageDouble &idMain, KImageDouble &output, int pX, int pY, int width, int height){
    //qDebug() << "crop start";
    output.Create(height,width);
    for(int i = pY, ii= 0; i < pY+height; i++,ii++){
        for(int j = pX,jj = 0; j < pX+width;j++,jj++){
            output[ii][jj] = idMain[i][j];
        }
    }

    //qDebug() << "crop End";
}

void pshCV::diff_double(KImageGray &igMain, KImageDouble &d_dx, KImageDouble &d_dy){
    d_dx.Create(igMain.Row(),igMain.Col());
    d_dy.Create(igMain.Row(),igMain.Col());

    for(int i = 1; i < (int)igMain.Row()-1; i++){
        for(int j = 1; j < (int)igMain.Col()-1; j++){
            d_dx[i][j] = igMain[i][j+1] - igMain[i][j-1];
            d_dy[i][j] = igMain[i+1][j] - igMain[i-1][j];
        }
    }
}

void pshCV::MakeMat_2Col(KImageDouble &id0, KImageDouble &id1, KImageDouble &output, int size){
    output.Create(size*size, 2);
    //qDebug() << "MakeMat";
    for(int i = 0; i < size*size; i++){
        //qDebug() << "1" << i;
        output[i][0] = id0[(int)(i/size)][i%size];
        output[i][1] = id1[(int)(i/size)][i%size];
        //qDebug() << output[i][0] << output[i][1];
    }
    //qDebug() << "MakeMat End";
}

void pshCV::MakeMat_1Col(KImageDouble &idMain, KImageDouble &output, int size){
    output.Create(size*size, 1);

    for(int i = 0; i < size*size; i++){
        //qDebug() << "1col" << i;
        output[i][0] = idMain[(int)(i/size)][i%size];
        //qDebug() << output[i][0];
    }
}
void pshCV::TranMat(KImageDouble &idMain, KImageDouble &output){
    output.Create(idMain.Col(),idMain.Row());

    for(int i =0; i < (int)idMain.Row();i++ ){
        for(int j = 0; j < (int)idMain.Col(); j++){
            output[j][i] = idMain[i][j];
        }
    }
}
void pshCV::MultiMat(KImageDouble &id0, KImageDouble &id1, KImageDouble &output){
    if(id0.Col() != id1.Row()) return; // multiply condition consider

    output.Create(id0.Row(),id1.Col());
    //qDebug() << "multi start";
    for(int i = 0; i < (int)id0.Row(); i++){
        for(int j =0; j < (int)id1.Col(); j++){
           for(int k = 0; k < (int)id1.Row(); k++){
                output[i][j] += id0[i][k] * id1[k][j];
           }
        }
    }
    //qDebug() << "multi End";
}

void pshCV::InvMat22(KImageDouble &idMain, KImageDouble &output){
    if(idMain.Row() != idMain.Col() || idMain.Row() != 2) return; //Inverse condition condider
    double det = idMain[0][0] * idMain[1][1] - idMain[0][1]*idMain[1][0];
    //qDebug() << "id " << idMain[0][0] << idMain[1][1] << idMain[0][1] << idMain[1][0];
    //qDebug() << "det" << det;

    output.Create(2,2);

    if(det == 0){
        output[0][0] = 0;
        output[0][1] = 0;
        output[1][0] = 0;
        output[1][1] = 0;
        //qDebug() << "det 0 ";
        return; //Inverse condition consider
    }



    output[0][0] = idMain[1][1] * (1 / det);
    output[0][1] = -idMain[1][0] * (1 / det);
    output[1][0] = -idMain[0][1] * (1 / det);
    output[1][1] = idMain[0][0] * (1 / det);



}

void pshCV::DrawLine(KImageColor &igMain, int pX, int pY, double u, double v){
    int magWeight = 2;
    double mag = (std::abs(u) + std::abs(v));
    //qDebug() << "mag" <<mag;
    //qDebug() << "u" << u << "v" << v;

    igMain._ppA[pY][pX] = {250, 0, 0};
    int i,y,x;
    for( i = 0; i<(int)mag*magWeight; i++){
        y = (int)((double)pY+v*(double)i/mag);
        x = (int)((double)pX+u*(double)i/mag);

        if(y > (int)igMain.Row()-1 || y < 0|| x > (int)igMain.Col()-1 || x < 0) return;

        igMain[y][x] = {250, 0, 0};
    }
}
