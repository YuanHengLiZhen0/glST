#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTreeWidget>
#include <QMainWindow>

#include<QLabel>
#include<QComboBox>
#include<QPushButton>
#include<QCheckBox>
#include"myopengl.h"
#include<QTableWidget>
#include"globalvalutil.h"
#include<opencv2/opencv.hpp>
using namespace  cv;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:


private:
    const QString workspaceInfoFileName = "ui_workspace.info";
    const QString baseInfoFileName = "ui_baseinfo.json";
    const QString effectListFileName = "ui_effectlist.json";
    const QString effectsRenderTempFolderName = ".effects";





    Ui::MainWindow *ui;




//界面
     int devicePixelRatio = 1;
     QWidget* pEffectInfoContainer = nullptr;
     QTreeWidget* pEffectTreeWidget = nullptr;		         // 效果树结构控件
    // AcceptedDropFilesTreeWidget* pFileResourcesTreeWidget = nullptr;	 // 资源管理器树结构控件
    // ClickableLabel* pIconWidget = nullptr;					 // icon控件
     QPushButton* pOpenButton = nullptr;
     QPushButton* pAssembleButton = nullptr;
     QPushButton* pRefreshButton = nullptr;
     QTableWidget* pPropertiesTable = nullptr;                // 自定义属性控件组容器
     QDockWidget* pPropertiesDockWidget = nullptr;
    // AdjustorControllerContainer* pCustomEffectAdjustorContainer = nullptr;   // 当前自定义效果调整控件容器
     MyOpenGL* pPreviewWindow = nullptr;						 // 预览控件
     QLabel *pPictureSizeTextLabel = nullptr;
     QPushButton* pJPGButton = nullptr;
     QCheckBox *pRenderEffectsCheckBox = nullptr;


     float _scale = 1.0f;
     QString srcImagePath = "";
     Mat srcImage;
     int faceCount;
     gl_s::HBKFace* srcFaceData = nullptr;
     gl_s::HBKFace* readLandmarksInfoForStillImage();
     QFont boldFont = QFont("黑体", 15, QFont::Bold);
     QFont italicFont = QFont("黑体", 14, QFont::StyleItalic);


    void saveWorkSpacePath();
    void loadWorkSpacePath();
    void onWorkspaceChanged(const QString &workspacePath);
    void loadWorkspaceContents();



     void initUI();
     void connectSignalsAndSlots();
     void onOpenButtonClicked(bool checked);

};

#endif // MAINWINDOW_H
