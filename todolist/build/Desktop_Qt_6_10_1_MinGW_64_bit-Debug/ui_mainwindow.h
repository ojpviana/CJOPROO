/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainLayout;
    QWidget *tasksPanel;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *taskInput;
    QPushButton *addTaskButton;
    QFrame *line;
    QLabel *label_2;
    QScrollArea *pendingScrollArea;
    QWidget *pendingTasksWidget;
    QVBoxLayout *pendingLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QScrollArea *completedScrollArea;
    QWidget *completedTasksWidget;
    QVBoxLayout *completedLayout;
    QSpacerItem *verticalSpacer_2;
    QFrame *line_2;
    QWidget *pomodoroPanel;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_3;
    QLabel *pomodoroLabel;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radioWork;
    QRadioButton *radioShort;
    QRadioButton *radioLong;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnStart;
    QPushButton *btnReset;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QHBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        tasksPanel = new QWidget(centralwidget);
        tasksPanel->setObjectName("tasksPanel");
        verticalLayout_2 = new QVBoxLayout(tasksPanel);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(tasksPanel);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        taskInput = new QLineEdit(tasksPanel);
        taskInput->setObjectName("taskInput");

        horizontalLayout_2->addWidget(taskInput);

        addTaskButton = new QPushButton(tasksPanel);
        addTaskButton->setObjectName("addTaskButton");

        horizontalLayout_2->addWidget(addTaskButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        line = new QFrame(tasksPanel);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line);

        label_2 = new QLabel(tasksPanel);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        pendingScrollArea = new QScrollArea(tasksPanel);
        pendingScrollArea->setObjectName("pendingScrollArea");
        pendingScrollArea->setWidgetResizable(true);
        pendingTasksWidget = new QWidget();
        pendingTasksWidget->setObjectName("pendingTasksWidget");
        pendingTasksWidget->setGeometry(QRect(0, 0, 378, 199));
        pendingLayout = new QVBoxLayout(pendingTasksWidget);
        pendingLayout->setSpacing(6);
        pendingLayout->setObjectName("pendingLayout");
        pendingLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        pendingLayout->addItem(verticalSpacer);

        pendingScrollArea->setWidget(pendingTasksWidget);

        verticalLayout_2->addWidget(pendingScrollArea);

        label_3 = new QLabel(tasksPanel);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        completedScrollArea = new QScrollArea(tasksPanel);
        completedScrollArea->setObjectName("completedScrollArea");
        completedScrollArea->setWidgetResizable(true);
        completedTasksWidget = new QWidget();
        completedTasksWidget->setObjectName("completedTasksWidget");
        completedTasksWidget->setGeometry(QRect(0, 0, 378, 198));
        completedLayout = new QVBoxLayout(completedTasksWidget);
        completedLayout->setSpacing(6);
        completedLayout->setObjectName("completedLayout");
        completedLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        completedLayout->addItem(verticalSpacer_2);

        completedScrollArea->setWidget(completedTasksWidget);

        verticalLayout_2->addWidget(completedScrollArea);


        mainLayout->addWidget(tasksPanel);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        mainLayout->addWidget(line_2);

        pomodoroPanel = new QWidget(centralwidget);
        pomodoroPanel->setObjectName("pomodoroPanel");
        verticalLayout_3 = new QVBoxLayout(pomodoroPanel);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        pomodoroLabel = new QLabel(pomodoroPanel);
        pomodoroLabel->setObjectName("pomodoroLabel");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Monospace")});
        font1.setPointSize(72);
        font1.setBold(true);
        pomodoroLabel->setFont(font1);
        pomodoroLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(pomodoroLabel);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        radioWork = new QRadioButton(pomodoroPanel);
        radioWork->setObjectName("radioWork");
        radioWork->setChecked(true);

        horizontalLayout_3->addWidget(radioWork);

        radioShort = new QRadioButton(pomodoroPanel);
        radioShort->setObjectName("radioShort");

        horizontalLayout_3->addWidget(radioShort);

        radioLong = new QRadioButton(pomodoroPanel);
        radioLong->setObjectName("radioLong");

        horizontalLayout_3->addWidget(radioLong);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        btnStart = new QPushButton(pomodoroPanel);
        btnStart->setObjectName("btnStart");

        horizontalLayout_4->addWidget(btnStart);

        btnReset = new QPushButton(pomodoroPanel);
        btnReset->setObjectName("btnReset");

        horizontalLayout_4->addWidget(btnReset);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_4);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);


        mainLayout->addWidget(pomodoroPanel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Minhas Tarefas", nullptr));
        taskInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Digite uma nova tarefa...", nullptr));
        addTaskButton->setText(QCoreApplication::translate("MainWindow", "Adicionar", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Pendentes", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Conclu\303\255das", nullptr));
        pomodoroLabel->setText(QCoreApplication::translate("MainWindow", "25:00", nullptr));
        radioWork->setText(QCoreApplication::translate("MainWindow", "Trabalho", nullptr));
        radioShort->setText(QCoreApplication::translate("MainWindow", "Pausa Curta", nullptr));
        radioLong->setText(QCoreApplication::translate("MainWindow", "Pausa Longa", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "Iniciar", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "Reiniciar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
