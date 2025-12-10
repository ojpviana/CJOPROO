#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "taskwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_addTaskButton_clicked();
    void on_taskInput_returnPressed();
    void on_btnStart_clicked();
    void on_btnReset_clicked();


    void handleTaskStatusChanged(TaskWidget *task, bool isCompleted);
    void handleTaskRemoved(TaskWidget *task);
    void updatePomodoroTimer();
    void updatePomodoroMode();

private:
    void addTask(const QString &text, bool isCompleted = false);
    void moveTask(TaskWidget *task, bool isCompleted);
    void saveTasks();
    void loadTasks();
    void resetPomodoro(bool force);

    Ui::MainWindow *ui;
    QTimer *pomodoroTimer;
    int timeRemaining; 
    bool isPomodoroRunning;

    enum PomodoroMode {
        Work = 25 * 60,
        ShortBreak = 5 * 60,
        LongBreak = 15 * 60
    };
    PomodoroMode currentMode;
};
#endif

