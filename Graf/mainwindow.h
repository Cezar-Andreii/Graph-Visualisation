#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include"graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mouseReleaseEvent(QMouseEvent *m) override;
    void paintEvent(QPaintEvent *ev) override;
    void drawArrow(QPainter& painter, const QPoint& start, const QPoint& end);


private slots: // Adăugați aici slots pentru a conecta butoanele radio
    void on_radioOriented_toggled(bool checked);
    void on_radioUnoriented_toggled(bool checked);
    void on_checkTreeButton_clicked();
    void on_findRootButton_clicked();
    void on_showConnectedComponentsButton_clicked();
    void on_runKruskalButton_clicked();
    void on_calculatePrimMSTButton_clicked();
    void on_HighlightButton_clicked();
    void on_calculateGenericTreeButton_clicked();

private:
    Ui::MainWindow *ui;
    Graph m_graph;
    Node m_selectedNode;
    bool m_isFirstNodeSelected;
    std::map<int, QColor> m_nodeColors;
    std::vector<Edge> m_mstEdges;
    bool drawBoruvkaMST;


};
#endif // MAINWINDOW_H
