#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include <vector>
#include <atomic>
#include <memory>
#include <thread>

// LSL API
#include <lsl_cpp.h>

//#define WIN32_LEAN_AND_MEAN
//#include "windows.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent, const std::string &config_file);
    ~MainWindow();
    
private slots:
    // config file dialog ops (from main menu)
    void load_config_dialog();
    void save_config_dialog();

    // start the cognionics connection
    void on_link();

    // close event (potentially disabled)
    void closeEvent(QCloseEvent *ev);

signals:
    void error();

private:
    // background data reader thread
    void read_thread(const std::string &comPort, unsigned int baudRate, unsigned int dataBits, int parity, int stopbits, int readmode,
                     int samplingRate, int chunkSize, const std::string &streamName);

    // raw config file IO
    std::string _filename;
    void load_config(const std::string &filename);
    void save_config(const std::string &filename);

    std::unique_ptr<std::thread> reader_thread_{nullptr};   // our reader thread
    std::atomic<bool> shutdown_{false};                     // flag indicating whether the streaming thread should quit

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
