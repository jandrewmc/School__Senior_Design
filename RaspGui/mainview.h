#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

    QVector<int> listToNodeIdVector;

public slots:
    void generateRooms();
    void roomChange();
    void updateStruct();
    void updateRooms();
    void updateDB();
    void clearNames();
    void addNames();
    void spinValueChange();

private:
    int roomsDisplayed;
    bool heatOn;
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
