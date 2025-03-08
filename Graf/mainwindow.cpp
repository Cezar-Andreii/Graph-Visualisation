#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QRadioButton>
#include<QGraphicsScene>
#include<QVBoxLayout>
#include<QGraphicsView>
#include<QGraphicsEllipseItem>
#include<QGraphicsTextItem>
#include<graph.h>
#include<QInputDialog>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_isFirstNodeSelected(false)
{
    ui->setupUi(this);

    // Conectăm butoanele radio la sloturi
    connect(ui->radioOriented, &QRadioButton::toggled, this, &MainWindow::on_radioOriented_toggled);
    connect(ui->radioUnoriented, &QRadioButton::toggled, this, &MainWindow::on_radioUnoriented_toggled);

    ui->radioOriented->setChecked(true); // Presupunem că graful este orientat la început
    m_graph.setOrientation(true); // Setăm graful ca fiind orientat
    connect(ui->checkTreeButton, &QPushButton::clicked, this, &MainWindow::on_checkTreeButton_clicked);
    // connect(ui->checkCycleButton, &QPushButton::clicked, this, &MainWindow::on_checkCycleButton_clicked);
    //connect(ui->calculateGenericTreeButton, &QPushButton::clicked, this, &MainWindow::on_calculateGenericTreeButton_clicked);

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *m)
{
    if(m->button()==Qt::RightButton)
    {
        QPoint pos = m->pos();
        if (!m_graph.addNode(pos)) {
            QMessageBox::warning(this, "Eroare", "Un nod deja existent se suprapune.");
            return;
        }
        update();
    }
    else if (m->button()==Qt::LeftButton)
    {
        std::vector<Node>& nodes=m_graph.getNodes();
        for(auto &n :nodes)
        {

            if ((n.getPos().x() - m->pos().x()) * (n.getPos().x() - m->pos().x()) +
                    (n.getPos().y() - m->pos().y()) * (n.getPos().y() - m->pos().y()) <= 100)
            {
                if(!m_isFirstNodeSelected)
                {
                    m_selectedNode=n;
                    m_isFirstNodeSelected=true;
                }
                else

                {
                    bool ok;
                    int cost = QInputDialog::getInt(this, "Cost muchie",
                                                    "Introduceți costul muchiei:", 1, 1, 1000, 1, &ok);
                    if (ok) {
                        m_graph.addEdge(m_selectedNode, n, cost);
                        m_isFirstNodeSelected = false;
                        update();
                    }

                }
                break;
            }


        }
    }
}


void MainWindow::paintEvent(QPaintEvent *ev) {
    QPainter p(this);
    std::vector<Node>& nodes = m_graph.getNodes();

    // Desenarea nodurilor
    for (auto& node : nodes) {
        QRect r(node.getPos().x() - 10, node.getPos().y() - 10, 20, 20);
        p.drawEllipse(r);
        QString str = QString::number(node.getValue());
        p.drawText(r, Qt::AlignCenter, str);
    }

    std::vector<Edge>& edges = m_graph.getEdges();

    // Desenarea muchiilor
    for (const auto& edge : edges) {
        QPoint start = edge.getFirst().getPos();
        QPoint end = edge.getSecond().getPos();

        // Dacă muchia este evidențiată, folosește culoarea corespunzătoare
        if (edge.isHighlighted()) {
            p.setPen(QPen(edge.getColor(), 2)); // Folosește culoarea atribuită
        } else {
            p.setPen(QPen(Qt::black, 1)); // Culoare negru pentru celelalte muchii
        }

        drawArrow(p, start, end);

        QPoint mid((start.x() + end.x()) / 2, (start.y() + end.y()) / 2);
        QString costText = QString::number(edge.getCost());
        p.drawText(mid, costText);
    }

    // Evidențierea muchiilor MST în albastru
    if(drawBoruvkaMST){
        for (const auto& edge : edges) {
            if (edge.isHighlighted() && edge.getColor() == Qt::blue) {
                QPoint start = edge.getFirst().getPos();
                QPoint end = edge.getSecond().getPos();

                p.setPen(QPen(Qt::blue, 2)); // Folosește culoarea albastră pentru MST
                drawArrow(p, start, end);

                QPoint mid((start.x() + end.x()) / 2, (start.y() + end.y()) / 2);
                QString costText = QString::number(edge.getCost());
                p.drawText(mid, costText);
            }
        }
    }
}







void MainWindow::drawArrow(QPainter& painter, const QPoint& start, const QPoint& end) {
    QLineF line(start, end);
    double angle = std::atan2(-line.dy(), line.dx());


    int arrowSize = 10;


    QPoint arrowP1 = end - QPoint(arrowSize * std::cos(angle + M_PI / 6), arrowSize * std::sin(angle + M_PI / 6));
    QPoint arrowP2 = end - QPoint(arrowSize * std::cos(angle - M_PI / 6), arrowSize * std::sin(angle - M_PI / 6));

    painter.drawLine(start, end);
    painter.drawLine(end, arrowP1);
    painter.drawLine(end, arrowP2);
}
void MainWindow::on_radioOriented_toggled(bool checked)
{
    if (checked) {
        m_graph.setOrientation(true);
    }
}

void MainWindow::on_radioUnoriented_toggled(bool checked)
{
    if (checked) {
        m_graph.setOrientation(false);
    }
}

void MainWindow::on_checkTreeButton_clicked() {
    if (m_graph.isTree()) {
        QMessageBox::information(this, "Rezultat", "Graful este un arbore.");
    } else {
        QMessageBox::warning(this, "Rezultat", "Graful NU este un arbore.");
    }
}

void MainWindow::on_findRootButton_clicked() {
    int root = m_graph.findRoot();
    if (root == -1) {
        QMessageBox::warning(this, "Rezultat", "Nu există rădăcină pentru acest graf.");
    } else {
        QMessageBox::information(this, "Rezultat", QString("Rădăcina grafului este nodul %1.").arg(root));
    }
}

void MainWindow::on_showConnectedComponentsButton_clicked() {
    if (m_graph.getOrientation()) {
        QMessageBox::warning(this, "Eroare", "Componentele conexe sunt aplicabile doar pentru grafuri neorientate.");
        return;
    }

    auto components = m_graph.getConnectedComponents();
    m_nodeColors.clear();


    std::vector<QColor> colors = { Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta };
    int colorIndex = 0;

    for (const auto& component : components) {
        QColor color = colors[colorIndex % colors.size()];
        colorIndex++;
        for (const auto& node : component) {
            m_nodeColors[node.getValue()] = color;
        }
    }

    update();
}

void MainWindow::on_runKruskalButton_clicked() {
    auto mstEdges = m_graph.findMSTWithKruskal();
    m_graph.highlightMSTEdges(mstEdges);

    QMessageBox::information(this, "Rezultat", "Arborele de cost minim a fost generat și evidențiat.");

    update(); // Redraw the graph
}

void MainWindow::on_calculatePrimMSTButton_clicked() {
    auto mstEdges = m_graph.computePrimMST();

    if (mstEdges.empty()) {
        QMessageBox::warning(this, "Rezultat", "Graful nu este conex. Nu se poate calcula un arbore de cost minim.");
        return;
    }

    m_mstEdges = mstEdges;
    update();
}


void MainWindow::on_HighlightButton_clicked()
{

    auto mstEdges = m_graph.boruvkaMST();
    m_graph.highlightBoruvkaMSTEdges();
    drawBoruvkaMST = true;

    update();
}

void MainWindow::on_calculateGenericTreeButton_clicked() {
    auto genericEdges = m_graph.getGenericTree();

    if (genericEdges.empty()) {
        QMessageBox::warning(this, "Eroare", "Graful nu este conex. Nu se poate calcula arborele generic.");
        return;
    }

    m_graph.highlightGenericTreeEdges(genericEdges);
    update();
}



