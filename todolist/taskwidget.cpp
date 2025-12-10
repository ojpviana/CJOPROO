#include "taskwidget.h"
#include "ui_taskwidget.h"

TaskWidget::TaskWidget(const QString &text, bool isCompleted, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskWidget)
{
    ui->setupUi(this);

    ui->taskCheckBox->blockSignals(true);
    ui->taskCheckBox->setText(text);
    ui->taskCheckBox->setChecked(isCompleted);
    ui->taskCheckBox->blockSignals(false);
}

TaskWidget::~TaskWidget()
{
    delete ui;
}

QString TaskWidget::text() const
{
    return ui->taskCheckBox->text();
}

bool TaskWidget::isCompleted() const
{
    return ui->taskCheckBox->isChecked();
}

void TaskWidget::on_taskCheckBox_stateChanged(int state)
{
    emit taskStatusChanged(this, state == Qt::Checked);
}

void TaskWidget::on_deleteButton_clicked()
{
    emit taskRemoved(this);
}

