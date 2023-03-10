#include <QFileDialog>
#include <QPainter>

#include <string>
#include <iostream>
#include "mainframe.h"
#include "ui_mainframe.h"
#include "imageform.h"
#include "hw_tools.h"
#include "pshCV.h"

MainFrame::MainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    _plpImageForm       = new KPtrList<ImageForm*>(10,false,false);
    _q_pFormFocused     = 0;

    //객체 맴버의 초기화


    //get a current directory
    char st[100];
    GetCurrentDirectoryA(100,st);

    //리스트 출력창을 안보이게
    ui->listWidget->setVisible(false);
    this->adjustSize();

    //UI 활성화 갱신
    UpdateUI();
}

MainFrame::~MainFrame()
{ 
    delete ui;         
    delete _plpImageForm;   
}

void MainFrame::Detach(ImageForm *pForm)
{    
    //ImageForm 포인터 삭제
    _plpImageForm->Remove(pForm);

    //활성화 ImageForm 초기화
    _q_pFormFocused     = 0;

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::UpdateUI()
{
    if(ui->tabWidget->currentIndex() == 0) // hw 01-02
    {
        //ui->buttonSepiaTone->setEnabled( _q_pFormFocused &&  _q_pFormFocused->ID() == "OPEN" );

    }

}

void MainFrame::OnMousePos(const int &nX, const int &nY, ImageForm* q_pForm)
{
    UpdateUI();
}

void MainFrame::closeEvent(QCloseEvent* event)
{
    //생성된 ImageForm을 닫는다.
    for(int i=_plpImageForm->Count()-1; i>=0; i--)
        _plpImageForm->Item(i)->close();
}


void MainFrame::on_buttonOpen_clicked()
{
    //이미지 파일 선택
    QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
    QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a Image File"),  "./data", "Image Files(*.bmp *.ppm *.pgm *.png)",0, q_Options);

    if(q_stFile.length() == 0)
        return;

    //이미지 출력을 위한 ImageForm 생성    
    ImageForm*              q_pForm   = new ImageForm(q_stFile, "OPEN", this);

    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_buttonDeleteContents_clicked()
{
    //생성된 ImageForm을 닫는다.
    for(int i=_plpImageForm->Count()-1; i>=0; i--)
        _plpImageForm->Item(i)->close();

    //리스트에서 삭제한다.
    _plpImageForm->RemoveAll();
}

void MainFrame::on_buttonShowList_clicked()
{
    static int nWidthOld = ui->tabWidget->width();

    if(ui->listWidget->isVisible())
    {
        nWidthOld = ui->listWidget->width();
        ui->listWidget->hide();
        this->adjustSize();
    }
    else
    {        
        ui->listWidget->show();
        QRect q_rcWin = this->geometry();

        this->setGeometry(q_rcWin.left(), q_rcWin.top(), q_rcWin.width()+nWidthOld, q_rcWin.height());
    }
}

void MainFrame::on_buttonSepiaTone_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    //Hue값 Sat값 받기
    double  dHue = ui->spinHue->value();
    double  dSat = ui->spinSaturation->value();
    if(dHue==360)dHue=0;
    //출력 영상
    KImageColor icSepia(icMain.Row(), icMain.Col());
    KImageGray igHue(icMain.Row(),icMain.Col());//(unsigned char)(hue/360.0)*255.0
    KImageGray igSat(icMain.Row(),icMain.Col());
    KImageGray igVal(icMain.Row(),icMain.Col());

    //Get HSV from RGB
    double _mig_Hue;
    double _mig_Sat;
    std::vector<double> _v_dValue;
    //Convert HSV to RGB
    double H_prime = dHue/60;
    double dValue,dChroma,dX;
    double dR_prime,dG_prime,dB_prime;
    double dR,dG,dB,dm;

    //
    int k=0;

    for(int i=0;i<icMain.Row();i++){
        for(int j=0;j<icMain.Col();j++){
            dValue = find_max(icMain[i][j].r,icMain[i][j].g,icMain[i][j].b)/255;
            _v_dValue.push_back(dValue);
            dChroma=dValue*dSat;
            dX=find_X(dChroma,H_prime);
            if(H_prime>=5 && H_prime <6){
                dR_prime=dChroma;
                dG_prime=0;
                dB_prime=dX;
            }else if(H_prime>=4){
                dR_prime=dX;
                dG_prime=0;
                dB_prime=dChroma;
            }else if(H_prime>=3){
                dR_prime=0;
                dG_prime=dX;
                dB_prime=dChroma;
            }else if(H_prime>=2){
                dR_prime=0;
                dG_prime=dChroma;
                dB_prime=dX;
            }else if(H_prime>=1){
                dR_prime=dX;
                dG_prime=dChroma;
                dB_prime=0;
            }else if(H_prime>=0){
                dR_prime=dChroma;
                dG_prime=dX;
                dB_prime=0;
            }else{
                std::cout<<"Convert Error";
            }
            dm=dValue-dChroma;
            dR=(dR_prime+dm)*255;
            dG=(dG_prime+dm)*255;
            dB=(dB_prime+dm)*255;
            icSepia[i][j].r=dR;
            icSepia[i][j].g=dG;
            icSepia[i][j].b=dB;
        }
    }

    for(int i=0;i<icMain.Row();i++){
        for(int j=0;j<icMain.Col();j++){

            double max_rgb = find_max(icMain[i][j].r,icMain[i][j].b,icMain[i][j].b);
            double min_rgb = find_min(icMain[i][j].r,icMain[i][j].b,icMain[i][j].b);
            double Hue_temp=0;
            if(max_rgb==icMain[i][j].r){
                Hue_temp=60*((icMain[i][j].g-icMain[i][j].b)/(max_rgb-min_rgb));
            }else if(max_rgb==icMain[i][j].g){
                Hue_temp=60*((icMain[i][j].b-icMain[i][j].r)/(max_rgb-min_rgb))+120;
            }else if(max_rgb==icMain[i][j].b){
                Hue_temp=60*((icMain[i][j].r-icMain[i][j].g)/(max_rgb-min_rgb))+240;
            }else {
                std::cout<<"Extract Error";
            }
            if(Hue_temp<0)Hue_temp+=360;
            _mig_Hue = Hue_temp;
            _mig_Sat = (max_rgb-min_rgb)/max_rgb;
            _mig_Hue=(_mig_Hue/360)*255;
            _mig_Sat =_mig_Sat*255;
            igHue[i][j] = _mig_Hue;
            igSat[i][j] = _mig_Sat;
            igVal[i][j] = _v_dValue[k]*255;
            k++;
        }
    }
    //

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(icSepia, "Sepia Tone", this);
    ImageForm*  q_pFormHue = new ImageForm(igHue, "Hue", this);
    ImageForm*  q_pFormSat = new ImageForm(igSat, "Saturation", this);
    ImageForm*  q_pFormVal = new ImageForm(igVal, "Value", this);

    _plpImageForm->Add(q_pForm);
    _plpImageForm->Add(q_pFormHue);
    _plpImageForm->Add(q_pFormSat);
    _plpImageForm->Add(q_pFormVal);

    q_pForm->show();
    q_pFormHue->show();
    q_pFormSat->show();
    q_pFormVal->show();

    //UI 활성화 갱신
    UpdateUI();
}


void MainFrame::on_buttonCustomThd_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageGray   igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;

    double  dThd = ui->spinThd->value();
    KImageGray igCustomThd = igMain;
    pshCV::Thresholded(igCustomThd,dThd);

    std::string msg = std::to_string(dThd);
    QString _q_msg = "Thd Value : ";
    QString _q_value = QString::number(dThd);
    _q_msg = _q_msg.append(_q_value);

    ImageForm*  q_pForm = new ImageForm(igCustomThd, _q_msg, this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}


void MainFrame::on_buttonOstu_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageGray   igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;

    KImageGray igOtsuThd = igMain;
    pshCV::OtsuThresholded(igOtsuThd);

    ImageForm*  q_pForm = new ImageForm(igOtsuThd,"Otsu", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}


void MainFrame::on_buttonDilation_clicked()
{
    KImageGray   igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address()) //&&  _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;
    if(!pshCV::CheckBinaryImage(igMain))return;

    KImageGray igDilation = igMain;

    int iKIndex = ui->Kernelsize->currentIndex();
    int dKernel;
    if(iKIndex == 0)dKernel = 3;
    else if(iKIndex == 1)dKernel = 5;
    else return;

    //std::cout<<iKIndex<<std::endl;
    pshCV::Dilated(igDilation,dKernel);

    ImageForm*  q_pForm = new ImageForm(igDilation,"Dilation", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}


void MainFrame::on_buttonErosion_clicked()
{
    KImageGray   igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address()) //&&  _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;
    if(!pshCV::CheckBinaryImage(igMain))return;

    KImageGray igErosion = igMain;

    int iKIndex = ui->Kernelsize->currentIndex();
    int dKernel;
    if(iKIndex == 0)dKernel = 3;
    else if(iKIndex == 1)dKernel = 5;
    else return;

    //std::cout<<iKIndex<<std::endl;
    pshCV::Eroded(igErosion,dKernel);

    ImageForm*  q_pForm = new ImageForm(igErosion,"Erosion", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();

}


void MainFrame::on_buttonLabeling_clicked()
{
    KImageGray   igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address()) //&&  _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;
    if(!pshCV::CheckBinaryImage(igMain))return;

    KImageColor icLabeling(igMain.Row(), igMain.Col());

    pshCV::Labeling(icLabeling,igMain);

    ImageForm*  q_pForm = new ImageForm(icLabeling,"Labeling", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();

}


void MainFrame::on_buttonHistoEq_clicked()
{
    KImageColor icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    pshCV::HistoEQ(icMain);

    ImageForm*  q_pForm = new ImageForm(icMain,"Histogram Equalization", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();

}


void MainFrame::on_buttonHistoMatchRef_clicked()
{
    KImageColor icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    ImageForm*  q_pForm = new ImageForm(icMain,"Histogram Matching Reference Image", this);
    _plpImageForm->Add(q_pForm);
    //q_pForm->show();
    UpdateUI();

}

void MainFrame::on_buttonHistoMatching_clicked()
{
    KImageColor icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    bool refImg_flag = false;
    KImageColor ref_img;
    if(!_plpImageForm->IsEmpty()){
        for(int i =0 ;i <_plpImageForm->Count();i++){
            if((*_plpImageForm)[i]->ID() == "Histogram Matching Reference Image"){
                ImageForm* q_pForm = (*_plpImageForm)[i];
                ref_img = q_pForm->ImageColor();
                refImg_flag = true;
                (*_plpImageForm)[i]->ID() = "trash";
                break;
            }
        }
    }else{
        return;
    }

    if(!refImg_flag)return;

    pshCV::HistoMatching(icMain, ref_img);

    ImageForm*  q_pForm = new ImageForm(icMain,"Histogram Matching", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}


void MainFrame::on_buttonGaussianNoise_clicked()
{
    KImageColor icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    double  dNSigma = ui->spinNSigma->value();
    pshCV::GaussianNoised(icMain, dNSigma);

    ImageForm*  q_pForm = new ImageForm(icMain,"Gaussian Noised Image", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}


void MainFrame::on_buttonSnPNoise_clicked()
{
    KImageColor icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    pshCV::SaltAndPepperNoised(icMain);

    ImageForm*  q_pForm = new ImageForm(icMain,"SnP Noised Image", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}


void MainFrame::on_pushButton_3_clicked() //BoxFiltering
{
    KImageColor icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address())
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    int iKIndex = ui->BFkernelsize->currentIndex();
    int nKernel;
    if(iKIndex == 0)nKernel = 3;
    else if(iKIndex == 1)nKernel = 5;
    else return;

    pshCV::BoxFiltering(icMain, nKernel);

    ImageForm*  q_pForm = new ImageForm(icMain,"Box Filtering", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}


void MainFrame::on_buttonGaussianFiltering_clicked()
{
    KImageColor icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address())
        icMain = _q_pFormFocused->ImageColor();
    else
        return;
    double  dFSigma = ui->spinFSigma->value();

    pshCV::GaussianFiltering(icMain, dFSigma);

    ImageForm*  q_pForm = new ImageForm(icMain,"Gaussian Filtering", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}


void MainFrame::on_buttonMedianFiltering_clicked()
{
    KImageColor icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address())
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    int iKIndex = ui->MFkernelsize->currentIndex();
    int dKernel;
    if(iKIndex == 0)dKernel = 3;
    else if(iKIndex == 1)dKernel = 5;
    else return;

    pshCV::MedianFiltering(icMain,dKernel);

    ImageForm*  q_pForm = new ImageForm(icMain,"Median Filtering", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}


void MainFrame::on_buttonCannyEdge_clicked()
{
    KImageGray igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address())
        igMain = _q_pFormFocused->ImageGray();
    else
        return;

    int nLowThld = ui->spinLowThreshold->value();
    int nHighThld = ui->spinHighThreshold->value();
    double dSigma = ui->spinSigma->value();

    pshCV::CannyEdged(igMain, dSigma, nHighThld, nLowThld);

    ImageForm*  q_pForm = new ImageForm(igMain,"Canny Edge", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}


void MainFrame::on_buttonCircleHT_clicked()
{
    KImageGray igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() && _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;

    int nRadius = 103;

    KImageColor icResult(igMain.Row(), igMain.Col());

    icResult = pshCV::CircleHoughTransform(igMain, nRadius);

    ImageForm*  q_pForm = new ImageForm(icResult,"Circle Hough Transform", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();

}


void MainFrame::on_buttonGeneralizedHT_clicked()
{
    KImageGray igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() && _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;

    KImageColor icResult(igMain.Row(), igMain.Col());

    icResult = pshCV::GeneralizedHoughTransform(igMain);

    ImageForm*  q_pForm = new ImageForm(icResult,"Generalized Hough Transform", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}


void MainFrame::on_buttonOpticalFlow_clicked()
{
    KImageGray   igMain1;
    KImageGray   igMain2;

    QString ig1 = QString::fromStdString("./hw08/yos.01.pgm");
    QString ig2 = QString::fromStdString("./hw08/yos.02.pgm");

    ImageForm *q_pForm = new ImageForm(ig1,"ig1", this);
    qDebug() << "file open";
    igMain1 = q_pForm->ImageGray();

    ImageForm * q_pForm1 = new ImageForm(ig2,"ig2",this);
    igMain2 = q_pForm1->ImageGray();

    KImageColor Optical(igMain1.Row(),igMain1.Col());
    pshCV::OpticalFlow(igMain1,igMain2,Optical,ui->spinWindowSize->value());

    qDebug() << "Optical Complete";
    ImageForm* q_pForm2 = new ImageForm(Optical, "Optical Flow", this);

    _plpImageForm->Add(q_pForm2);
    q_pForm2 -> show();
    UpdateUI();
}



void MainFrame::on_buttonOptNext_clicked()
{
    KImageGray   igMain1;
    KImageGray   igMain2;

    ImageForm *q_pForm =0;
    for(unsigned int i = 0; i<_plpImageForm->Count();i++){
        if((*_plpImageForm)[i]->ID() == "Optical Flow"){
            q_pForm = (*_plpImageForm)[i];
            break;
        }
    }
    int num = ui->spinOpt->value();

    std::string optcNum = std::to_string(num);
    std::string optcNum2 = std::to_string(num-1);
    std::string name1, name2;

    if(num > 9){
        name1 = optcNum;
    }
    else{
        name1 = "0" + optcNum;
        name2 = "0" + optcNum2;
    }
    if(num > 10){
        name2 = optcNum2;
    }

    QString ig1 = QString::fromStdString("./hw08/yos." + name1 + ".pgm");
    QString ig2 = QString::fromStdString("./hw08/yos." + name2 + ".pgm");

    ImageForm *q_pForm1 = new ImageForm(ig1,"OPEN", this);
    //qDebug() << "file open";
    igMain1 = q_pForm1->ImageGray();

    ImageForm *q_pForm2 = new ImageForm(ig2,"OPEN",this);
    igMain2 = q_pForm2->ImageGray();

    KImageColor Optical(igMain1.Row(),igMain1.Col());
    pshCV::OpticalFlow(igMain1,igMain2,Optical,ui->spinWindowSize->value());


    if(q_pForm)
        q_pForm->Update(Optical);
    else{
        q_pForm = new ImageForm(Optical,"Optical Flow",this);
        q_pForm -> show();
        _plpImageForm->Add(q_pForm);
    }
    //UI 활성화 갱신
    UpdateUI();
    ui->spinOpt->setValue(num+1);
    delete q_pForm1;
}


void MainFrame::on_spinOpt_textChanged(const QString &arg1)
{
    KImageGray   igMain1;
    KImageGray   igMain2;

    ImageForm *q_pForm =0;
    for(unsigned int i = 0; i<_plpImageForm->Count();i++){
        if((*_plpImageForm)[i]->ID() == "Optical Flow"){
            q_pForm = (*_plpImageForm)[i];
            break;
        }
    }
    int num = ui->spinOpt->value();

    std::string optcNum = std::to_string(num);
    std::string optcNum2 = std::to_string(num-1);
    std::string name1, name2;

    if(num > 9){
        name1 = optcNum;
    }
    else{
        name1 = "0" + optcNum;
        name2 = "0" + optcNum2;
    }
    if(num > 10){
        name2 = optcNum2;
    }

    QString ig1 = QString::fromStdString("./hw08/yos." + name1 + ".pgm");
    QString ig2 = QString::fromStdString("./hw08/yos." + name2 + ".pgm");

    ImageForm *q_pForm1 = new ImageForm(ig1,"OPEN", this);
    //qDebug() << "file open";
    igMain1 = q_pForm1->ImageGray();

    ImageForm *q_pForm2 = new ImageForm(ig2,"OPEN",this);
    igMain2 = q_pForm2->ImageGray();

    KImageColor Optical(igMain1.Row(),igMain1.Col());
    pshCV::OpticalFlow(igMain1,igMain2,Optical,ui->spinWindowSize->value());

    if(q_pForm)
        q_pForm->Update(Optical);
    else{
        q_pForm = new ImageForm(Optical,"Optical Flow",this);
        q_pForm -> show();
        _plpImageForm->Add(q_pForm);
    }
    //UI 활성화 갱신
    UpdateUI();
    //ui->spinOptc->setValue(num+1);
    delete q_pForm1;
}

