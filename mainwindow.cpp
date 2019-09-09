#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLineEdit>
#include<QGridLayout>
#include<QDockWidget>
#include<QScreen>
#include<QGuiApplication>
#include<QHeaderView>
#include<QFileDialog>
#include"globalinfos.h"
#include"QtFileUtils.h"
#include<QMessageBox>
#include<globalvalutil.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QScreen* mainScreen = QGuiApplication::primaryScreen();
    devicePixelRatio = static_cast<int>(mainScreen->devicePixelRatio());
    ui->setupUi(this);

    initUI();
    connectSignalsAndSlots();
//    workerThread.start();
//    emit uiSetupFinished(pPreviewWindow);
//    pTimer->start(33);
      loadWorkspaceContents();
      gl_s::init( pPreviewWindow->width(), pPreviewWindow->height());
      pPreviewWindow->update();

//    _remoteCommandController.initialize();
    //ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::initUI(){


      //  pTimer = new QTimer(this);

        /************************************************************************/
        /*项目列表                                                               */
        /************************************************************************/
        pEffectTreeWidget = new QTreeWidget(this);
      //  pEffectTreeWidget->headerItem()->setFont(0, GlobalInfos::getTitleFont());
        pEffectTreeWidget->headerItem()->setText(0, QObject::tr("文件名称"));
        pEffectTreeWidget->headerItem()->setText(1, QObject::tr("备注"));
        pEffectTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
      //  connect(pEffectTreeWidget, &QWidget::customContextMenuRequested, this, &MainWindow::onTreeWidgetCustomContextMenuRequested);
      //  connect(pEffectTreeWidget, &QTreeWidget::currentItemChanged, this, &MainWindow::onEffectItemSelected);



//        AcceptedDropWidget* baseInfoWidget = new AcceptedDropWidget(this);
//        baseInfoWidget->setLayout(baseInfoContainer);
//        connect(baseInfoWidget, &AcceptedDropWidget::urlDropEvent, this, &MainWindow::onWorkspaceDroped);

        /************************************************************************/
        /*操作按钮组                                                             */
        /************************************************************************/
        QHBoxLayout* buttonsLayout = new QHBoxLayout();
        pOpenButton = new QPushButton(QObject::tr("打开"), this);
        buttonsLayout->addWidget(pOpenButton);
        pAssembleButton = new QPushButton(QObject::tr("打包"), this);
        buttonsLayout->addWidget(pAssembleButton);
        pRefreshButton = new QPushButton(QObject::tr("刷新"), this);
        buttonsLayout->addWidget(pRefreshButton);
        QWidget* buttonsContainer = new QWidget(this);
        buttonsContainer->setLayout(buttonsLayout);

        /************************************************************************/
        /* 资源文件管理器模块                                                     */
        /************************************************************************/
//        pFileResourcesTreeWidget = new AcceptedDropFilesTreeWidget(this);
//        pFileResourcesTreeWidget->setHeaderHidden(true);

        QDockWidget* fileResourcesWidgetContainer = new QDockWidget(QObject::tr("title_resources_manager"), this);
        fileResourcesWidgetContainer->setFeatures(QDockWidget::NoDockWidgetFeatures);
        //fileResourcesWidgetContainer->setWidget(pFileResourcesTreeWidget);

        /************************************************************************/
        /*组合项目列表和操作按钮组和基础信息                                       */
        /************************************************************************/
        QVBoxLayout* effectInfoContainerLayout = new QVBoxLayout();
        effectInfoContainerLayout->setSpacing(0);
        effectInfoContainerLayout->setMargin(0);
        effectInfoContainerLayout->setContentsMargins(0, 0, 0, 0);
        effectInfoContainerLayout->addWidget(buttonsContainer);
        effectInfoContainerLayout->addWidget(pEffectTreeWidget);
        effectInfoContainerLayout->addWidget(fileResourcesWidgetContainer);
        effectInfoContainerLayout->setStretch(0, 0);
        effectInfoContainerLayout->setStretch(1, 0);
        effectInfoContainerLayout->setStretch(2, 1);
        effectInfoContainerLayout->setStretch(3, 1);
        pEffectInfoContainer = new QWidget(this);
        pEffectInfoContainer->setLayout(effectInfoContainerLayout);

        /************************************************************************/
        /* 动态属性模块 根据当前选中项目改变                                       */
        /************************************************************************/
        pPropertiesDockWidget = new QDockWidget(QObject::tr("title_properties_editor"), this);
        pPropertiesDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

        pPropertiesTable = new QTableWidget(0, 2, this);
        pPropertiesTable->installEventFilter(this);
        pPropertiesTable->setShowGrid(false);
    #ifdef _WINDOWS
        QPalette pal;
        pal.setColor(QPalette::Base, QColor("#F2F2F2"));
        pal.setColor(QPalette::AlternateBase, QColor("#fffffb"));
        pPropertiesTable->setPalette(pal);
    #endif
        pPropertiesTable->setAlternatingRowColors(true);

        pPropertiesTable->verticalHeader()->hide();
        pPropertiesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QStringList header;
        header << QObject::tr("property") << QObject::tr("value");
        pPropertiesTable->setHorizontalHeaderLabels(header);
        pPropertiesTable->horizontalHeader()->setStretchLastSection(true);
        pPropertiesTable->setSelectionMode(QAbstractItemView::NoSelection);
        pPropertiesDockWidget->setWidget(pPropertiesTable);

        /************************************************************************/
        /* 预览模块                                                              */
        /************************************************************************/
         pPreviewWindow = new MyOpenGL();
//        pPreviewWindow->setFormat(pRenderController->surfaceFormat());
//        pPreviewWindow->show();
       // pPreviewWindowWidget = QWidget::createWindowContainer(pPreviewWindow, this);

        pJPGButton=new QPushButton(QObject::tr("选择图像"), this);
        pPictureSizeTextLabel = new QLabel("");
        pRenderEffectsCheckBox = new QCheckBox("渲染特效");
        pRenderEffectsCheckBox->setCheckState(Qt::Checked);
        //connect(pRenderEffectsCheckBox, &QCheckBox::stateChanged, pRenderController, &OpenglRenderController::onChangeRenderEffectsFlag);
        QFrame *previewToolbar = new QFrame();
        QHBoxLayout *previewToolbarLayout = new QHBoxLayout();
        previewToolbarLayout->setAlignment(Qt::AlignCenter);
        previewToolbarLayout->addWidget(pJPGButton);
        previewToolbarLayout->addSpacing(40);
        previewToolbarLayout->addWidget(pPictureSizeTextLabel);
        previewToolbarLayout->addSpacing(40);
        previewToolbarLayout->addWidget(pRenderEffectsCheckBox);
        previewToolbar->setLayout(previewToolbarLayout);

        QVBoxLayout *previewContainerLayout = new QVBoxLayout();
        previewContainerLayout->setSpacing(0);
        previewContainerLayout->setMargin(0);
        previewContainerLayout->addWidget(pPreviewWindow);
        previewContainerLayout->addWidget(previewToolbar);
        previewContainerLayout->setStretch(0, 1);
        previewContainerLayout->setStretch(1, 0);
        QFrame *previewContainer = new QFrame(this);
        previewContainer->setLayout(previewContainerLayout);

        /************************************************************************/
        /* 特殊编辑行为模块                                                        */
        /************************************************************************/
    //    pCustomEffectAdjustorContainer = new AdjustorControllerContainer(this);

        /************************************************************************/
        /* 组合所有模块                                                          */
        /************************************************************************/
        QHBoxLayout* mainContainer = new QHBoxLayout;

            mainContainer->addWidget(pEffectInfoContainer);
            mainContainer->addWidget(pPropertiesDockWidget);
            mainContainer->addWidget(previewContainer);
            mainContainer->setStretch(0, 1);
            mainContainer->setStretch(1, 2);
            mainContainer->setStretch(2, 3);

        ui->centralWidget->setLayout(mainContainer);

        QMenuBar *menuBar = new QMenuBar(this);
        QMenu *toolMenu = menuBar->addMenu("工具");
       // buildToolMenu(toolMenu);
        setMenuBar(menuBar);
    }
void MainWindow::connectSignalsAndSlots(){



      connect(pOpenButton, &QPushButton::clicked, this, &MainWindow::onOpenButtonClicked);
       pOpenButton->setShortcut(QKeySequence(QLatin1String("Ctrl+O")));
}

void MainWindow:: loadWorkspaceContents(){
    QString oldImagePath = srcImagePath;
    QString expectedImagePath = GlobalInfos::getCurrentWorkspacePath() + "/ui_rawimage.jpeg";
    if (QFileInfo::exists(expectedImagePath))
        srcImagePath = expectedImagePath;
    else
        srcImagePath = "../resources/rawImage.png";
    srcImage = imread(srcImagePath.toUtf8().constData());
    cvtColor(srcImage, srcImage, COLOR_BGR2RGBA);
    pPictureSizeTextLabel->setText(QString::fromUtf8("图片尺寸 %1 * %2").arg(srcImage.cols).arg(srcImage.rows));

    if (oldImagePath != srcImagePath && srcFaceData != nullptr)
    {
        delete [] srcFaceData;
        srcFaceData = nullptr;
    }
 }

void MainWindow::loadWorkSpacePath()
{
    if (QFileInfo::exists(workspaceInfoFileName))
    {
        QFile file(workspaceInfoFileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray data = file.readAll();
        file.close();

        GlobalInfos::setCurrentWorkspacePath(QString(data));
    }
    else
    {
        GlobalInfos::setCurrentWorkspacePath("temp/workspace");
    }
}

void MainWindow::saveWorkSpacePath()
{
    QtFileUtils::writeStringToFile(GlobalInfos::getCurrentWorkspacePath(), workspaceInfoFileName);
}


void MainWindow::onWorkspaceChanged(const QString &workspacePath)
{
    QFileInfo fInfo(workspacePath);
    QString realWorkspacePath = workspacePath;
    if (fInfo.isFile())
        realWorkspacePath = fInfo.dir().absolutePath();
    else if (fInfo.isDir())
        realWorkspacePath = fInfo.absoluteFilePath();
    else
        return;

    if (GlobalInfos::getCurrentWorkspacePath() == realWorkspacePath) return;

//    QString effectName = pNameEdit->text();


//    if (_effectConfigurationManager.checkConfigurationsChanged(type, effectName, version, authorName))
//    {
//        QMessageBox::StandardButton resBtn = QMessageBox::question(this, QObject::tr("app_name"),
//            QObject::tr("warning_exit_without_save"),
//            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
//            QMessageBox::Yes);

//        if (resBtn == QMessageBox::Cancel)
//            return;
//        else if (resBtn == QMessageBox::Yes)
//        {
//            _effectConfigurationManager.updateRenderConfigurations(type, effectName, version, authorName, false, false);
//            refreshBaseInfo();
//        }
//    }

    GlobalInfos::setCurrentWorkspacePath(realWorkspacePath);
    saveWorkSpacePath();
    //loadWorkspaceContents();
}

void MainWindow::onOpenButtonClicked(bool checked)
{
    Q_UNUSED(checked);
    QString selectedDir = QFileDialog::getExistingDirectory(this, QObject::tr("tips_select_workspace_folder"), GlobalInfos::getCurrentWorkspacePath());
    if (!selectedDir.isEmpty())
        onWorkspaceChanged(selectedDir);
}


