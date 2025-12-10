#include "taskwidget.h"
#include "ui_taskwidget.h"

TaskWidget::TaskWidget(const QString &text, bool isCompleted, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskWidget)
{
    ui->setupUi(this);

    // Configura o estado inicial sem emitir sinais
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
    // Emite o sinal para a MainWindow saber da mudança de status
    emit taskStatusChanged(this, state == Qt::Checked);
}

void TaskWidget::on_deleteButton_clicked()
{
    // Emite o sinal para a MainWindow saber que esta tarefa deve ser removida
    emit taskRemoved(this);
}
