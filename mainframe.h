#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QDialog>
#include "kfc.h"

namespace Ui {
class MainFrame;

}

class ImageForm;

class MainFrame : public QDialog
{
    Q_OBJECT

private:
    Ui::MainFrame *ui;

    KPtrList<ImageForm*>*   _plpImageForm;
    ImageForm*              _q_pFormFocused;
    ImageForm*              _q_pFormTarget;

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

    void            ImageFormFocused(ImageForm* q_pImageForm)
                    {   _q_pFormFocused  = q_pImageForm;   //활성화된 창의 포인터를 저장함
                        UpdateUI();                        //UI 활성화 갱신
                    }
    void            UpdateUI();
    void            Detach(ImageForm* pForm);

public:
    void            OnMousePos(const int& nX, const int& nY, ImageForm* q_pForm);

private slots:
    void on_buttonOpen_clicked();
    void on_buttonDeleteContents_clicked();    
    void on_buttonShowList_clicked();    

    void on_buttonSepiaTone_clicked();

    void on_buttonCustomThd_clicked();

    void on_buttonOstu_clicked();

    void on_buttonDilation_clicked();

    void on_buttonErosion_clicked();

    void on_buttonLabeling_clicked();

    void on_buttonHistoEq_clicked();

    void on_buttonHistoMatchRef_clicked();

    void on_buttonHistoMatching_clicked();

    void on_buttonGaussianNoise_clicked();

    void on_buttonSnPNoise_clicked();

    void on_pushButton_3_clicked();

    void on_buttonGaussianFiltering_clicked();

    void on_buttonMedianFiltering_clicked();

    void on_buttonCannyEdge_clicked();

    void on_buttonCircleHT_clicked();

    void on_buttonGeneralizedHT_clicked();

    void on_buttonOpticalFlow_clicked();

    void on_buttonOptNext_clicked();

    void on_spinOpt_textChanged(const QString &arg1);

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // MAINFRAME_H
