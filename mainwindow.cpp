#include "mainwindow.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Set up the main window
    setWindowTitle("Sagar Sahu");


    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);


    QLabel *infoLabel = new QLabel("Welcome to EditAI!\nPlease enter a prompt for your edit in a single line:", this);
    layout->addWidget(infoLabel);

    // Create a line edit for user input (e.g., video genre or theme/stylistic choice)
    QLineEdit *genreLineEdit = new QLineEdit(this);
    genreLineEdit->setObjectName("genreLineEdit");  // Set object name for later finding
    genreLineEdit->setPlaceholderText("What can I do for you?");
    layout->addWidget(genreLineEdit);

    //QLabel *space = new QLabel(" ", this);
    //layout->addWidget(space);

    // Create a button to select a video file
    startButton = new QPushButton("Select Video File", this);
    layout->addWidget(startButton);


    // Create a button to start video editing
    QPushButton *startEditingButton = new QPushButton("Start", this);
    layout->addWidget(startEditingButton);

    // Create a button to clear/reset data
    QPushButton *clearButton = new QPushButton("Clear", this);
    layout->addWidget(clearButton);

    progressBar = new QProgressBar(this);
    layout->addWidget(progressBar);

    // Create a text edit for displaying debug messages
    debugTextEdit = new QTextEdit(this);
    debugTextEdit->setReadOnly(true);
    layout->addWidget(debugTextEdit);

    // Set the central widget
    setCentralWidget(centralWidget);

    // Connect signals and slots
    connect(startButton, SIGNAL(clicked()), this, SLOT(selectVideoFile()));
    connect(startEditingButton, SIGNAL(clicked()), this, SLOT(startVideoEditing()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearData()));
}

void MainWindow::selectVideoFile() {
    // Open a file dialog to select a video file
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mp4 *.avi *.mkv)"));

    if (!filePath.isEmpty()) {
        // Display the selected video file path in the debug text edit
        debugTextEdit->append("Selected file: " + filePath + "\n");
    } else if (filePath.isEmpty()) {
        debugTextEdit->append("Error: please select a valid file.");
    }
}

void MainWindow::startVideoEditing() {
    // Get the entered genre from the line edit
    QLineEdit *genreLineEdit = findChild<QLineEdit*>("genreLineEdit");
    if (genreLineEdit && !genreLineEdit->text().isEmpty()) {
        QString genre = genreLineEdit->text();
        debugTextEdit->append("User prompts:\n" + genre + "\n");

        // Check if a video file is selected
        if (debugTextEdit->toPlainText().isEmpty()) {
            debugTextEdit->append("Error: No video file selected.\n");
            return;  // Stop further execution if no video file is selected
        }

        // Continue with the editing process
        QString filePath = debugTextEdit->toPlainText();
        debugTextEdit->append("Started video editing process...\n");

        // Simulate video editing process with a progress bar
        simulateVideoEditing(filePath);
    } else {
        debugTextEdit->append("Error: Please enter a valid prompt.\n");
    }
}


void MainWindow::simulateVideoEditing(const QString &filePath) {

    if (progressBar) {

        int totalSteps = 10;
        int currentStep = 0;

        // Use QTimer to periodically update the progress bar
        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [=]() mutable {
            if (currentStep <= totalSteps) {
                progressBar->setValue(currentStep * (100 / totalSteps));
                ++currentStep;

                // Display progress message in the GUI window
                //debugTextEdit->append("Processing step " + QString::number(currentStep));
            } else {
                // Video editing is complete, stop the timer
                timer->stop();
                debugTextEdit->append("Editing process complete!\n");
                timer->deleteLater();
            }
        });

        // Set the timer interval (adjust based on the actual video editing time)
        int interval = 500;  // milliseconds
        timer->start(interval);
    }
}

void MainWindow::clearData() {

    QLineEdit *genreLineEdit = findChild<QLineEdit*>("genreLineEdit");
    if (genreLineEdit) {
        genreLineEdit->clear();
        //debugTextEdit->append("Cleared genre.");
    }

    if (debugTextEdit) {
        debugTextEdit->clear();  // Clear the content of debugTextEdit
        //debugTextEdit->append("Cleared file path.");
    }

    // Reset the progress bar
    QProgressBar *progressBar = findChild<QProgressBar*>();
    if (progressBar) {
        progressBar->reset();
        //debugTextEdit->append("Progress bar reset.");
    }
}

