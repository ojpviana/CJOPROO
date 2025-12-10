#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pomodoroTimer(new QTimer(this))
    , timeRemaining(Work)
    , isPomodoroRunning(false)
    , currentMode(Work)
{
    ui->setupUi(this);

    // Carrega as tarefas salvas ao iniciar
    loadTasks();

    // Configura o timer do Pomodoro
    connect(pomodoroTimer, &QTimer::timeout, this, &MainWindow::updatePomodoroTimer);

    // Conecta os radio buttons para mudar o modo do Pomodoro
    connect(ui->radioWork, &QRadioButton::toggled, this, &MainWindow::updatePomodoroMode);
    connect(ui->radioShort, &QRadioButton::toggled, this, &MainWindow::updatePomodoroMode);
    connect(ui->radioLong, &QRadioButton::toggled, this, &MainWindow::updatePomodoroMode);

    // Inicia o estado do Pomodoro
    ui->radioWork->setChecked(true);
    resetPomodoro(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Salva as tarefas ao fechar a janela
void MainWindow::closeEvent(QCloseEvent *event)
{
    saveTasks();
    QMainWindow::closeEvent(event);
}

void MainWindow::on_addTaskButton_clicked()
{
    const QString taskText = ui->taskInput->text().trimmed();
    if (!taskText.isEmpty()) {
        addTask(taskText);
        ui->taskInput->clear();
    }
}

void MainWindow::on_taskInput_returnPressed()
{
    on_addTaskButton_clicked();
}

void MainWindow::addTask(const QString &text, bool isCompleted)
{
    TaskWidget *task = new TaskWidget(text, isCompleted);
    connect(task, &TaskWidget::taskStatusChanged, this, &MainWindow::handleTaskStatusChanged);
    connect(task, &TaskWidget::taskRemoved, this, &MainWindow::handleTaskRemoved);

    if (isCompleted) {
        ui->completedLayout->addWidget(task);
    } else {
        ui->pendingLayout->addWidget(task);
    }
}

void MainWindow::handleTaskStatusChanged(TaskWidget *task, bool isCompleted)
{
    moveTask(task, isCompleted);
}

void MainWindow::moveTask(TaskWidget *task, bool isCompleted)
{
    if (isCompleted) {
        ui->pendingLayout->removeWidget(task);
        ui->completedLayout->addWidget(task);
    } else {
        ui->completedLayout->removeWidget(task);
        ui->pendingLayout->addWidget(task);
    }
}

void MainWindow::handleTaskRemoved(TaskWidget *task)
{
    // Remove o widget do layout e o deleta
    task->setParent(nullptr);
    delete task;
}

void MainWindow::saveTasks()
{
    QJsonArray tasksArray;

    // Salva tarefas pendentes
    for (int i = 0; i < ui->pendingLayout->count(); ++i) {
        TaskWidget *task = qobject_cast<TaskWidget*>(ui->pendingLayout->itemAt(i)->widget());
        if (task) {
            QJsonObject taskObj;
            taskObj["text"] = task->text();
            taskObj["completed"] = false;
            tasksArray.append(taskObj);
        }
    }

    // Salva tarefas concluídas
    for (int i = 0; i < ui->completedLayout->count(); ++i) {
        TaskWidget *task = qobject_cast<TaskWidget*>(ui->completedLayout->itemAt(i)->widget());
        if (task) {
            QJsonObject taskObj;
            taskObj["text"] = task->text();
            taskObj["completed"] = true;
            tasksArray.append(taskObj);
        }
    }

    QJsonDocument doc(tasksArray);
    QFile file("tasks.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void MainWindow::loadTasks()
{
    QFile file("tasks.json");
    if (!file.open(QIODevice::ReadOnly)) {
        return; // Arquivo não existe ainda, sem problemas.
    }

    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isArray()) {
        QJsonArray tasksArray = doc.array();
        for (const QJsonValue &value : tasksArray) {
            QJsonObject taskObj = value.toObject();
            if (taskObj.contains("text") && taskObj.contains("completed")) {
                addTask(taskObj["text"].toString(), taskObj["completed"].toBool());
            }
        }
    }
}

// --- Lógica do Pomodoro ---

void MainWindow::updatePomodoroMode()
{
    if (isPomodoroRunning) return; // Não muda o modo enquanto o timer está rodando

    if (ui->radioWork->isChecked()) {
        currentMode = Work;
    } else if (ui->radioShort->isChecked()) {
        currentMode = ShortBreak;
    } else if (ui->radioLong->isChecked()) {
        currentMode = LongBreak;
    }
    resetPomodoro(true);
}

void MainWindow::on_btnStart_clicked()
{
    isPomodoroRunning = !isPomodoroRunning;
    if (isPomodoroRunning) {
        pomodoroTimer->start(1000); // Dispara a cada 1 segundo
        ui->btnStart->setText("Pausar");
    } else {
        pomodoroTimer->stop();
        ui->btnStart->setText("Iniciar");
    }
}

void MainWindow::on_btnReset_clicked()
{
    resetPomodoro(false);
}

void MainWindow::resetPomodoro(bool force)
{
    if (isPomodoroRunning && !force) return; // Não reinicia se estiver rodando, a menos que seja forçado

    pomodoroTimer->stop();
    isPomodoroRunning = false;
    timeRemaining = currentMode;
    ui->btnStart->setText("Iniciar");

    int minutes = timeRemaining / 60;
    int seconds = timeRemaining % 60;
    ui->pomodoroLabel->setText(QString("%1:%2")
                               .arg(minutes, 2, 10, QChar('0'))
                               .arg(seconds, 2, 10, QChar('0')));
}

void MainWindow::updatePomodoroTimer()
{
    if (timeRemaining > 0) {
        timeRemaining--;
        int minutes = timeRemaining / 60;
        int seconds = timeRemaining % 60;
        ui->pomodoroLabel->setText(QString("%1:%2")
                                   .arg(minutes, 2, 10, QChar('0'))
                                   .arg(seconds, 2, 10, QChar('0')));
    } else {
        // O tempo acabou, reseta o timer
        resetPomodoro(true);
        // Poderia adicionar um som de notificação aqui
    }
}
