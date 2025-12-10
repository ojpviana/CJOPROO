#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class TaskWidget;
}

class TaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWidget(const QString &text, bool isCompleted = false, QWidget *parent = nullptr);
    ~TaskWidget();

    QString text() const;
    bool isCompleted() const;

signals:
    void taskStatusChanged(TaskWidget *task, bool isCompleted);
    void taskRemoved(TaskWidget *task);

private slots:
    void on_taskCheckBox_stateChanged(int state);
    void on_deleteButton_clicked();

private:
    Ui::TaskWidget *ui;
};

#endif 

