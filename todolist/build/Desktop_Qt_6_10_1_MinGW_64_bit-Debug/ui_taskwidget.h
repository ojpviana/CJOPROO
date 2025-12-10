/********************************************************************************
** Form generated from reading UI file 'taskwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKWIDGET_H
#define UI_TASKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *taskCheckBox;
    QPushButton *deleteButton;

    void setupUi(QWidget *TaskWidget)
    {
        if (TaskWidget->objectName().isEmpty())
            TaskWidget->setObjectName("TaskWidget");
        TaskWidget->resize(400, 50);
        horizontalLayout = new QHBoxLayout(TaskWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        taskCheckBox = new QCheckBox(TaskWidget);
        taskCheckBox->setObjectName("taskCheckBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(taskCheckBox->sizePolicy().hasHeightForWidth());
        taskCheckBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(taskCheckBox);

        deleteButton = new QPushButton(TaskWidget);
        deleteButton->setObjectName("deleteButton");

        horizontalLayout->addWidget(deleteButton);


        retranslateUi(TaskWidget);

        QMetaObject::connectSlotsByName(TaskWidget);
    } // setupUi

    void retranslateUi(QWidget *TaskWidget)
    {
        TaskWidget->setWindowTitle(QCoreApplication::translate("TaskWidget", "Form", nullptr));
        taskCheckBox->setText(QCoreApplication::translate("TaskWidget", "Placeholder Task", nullptr));
        deleteButton->setText(QCoreApplication::translate("TaskWidget", "Deletar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskWidget: public Ui_TaskWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKWIDGET_H
