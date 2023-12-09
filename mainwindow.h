#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include <QTextEdit>
#include <QLineEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void selectVideoFile();
    void startVideoEditing();
    void simulateVideoEditing(const QString &filePath);
    void clearData();

private:
    QPushButton *startButton;
    QProgressBar *progressBar;
    QTimer *timer;
    QTextEdit *debugTextEdit;
    QPushButton *stopEditingButton;
};

#endif //MAINWINDOW_H
