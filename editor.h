#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

namespace Ui {
class Editor;
}

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

private slots:
    void on_actionSalir_del_editor_triggered();

    void on_actionGuardar_como_triggered();

    void on_actionAbrir_triggered();

private:
    Ui::Editor *ui;
};

#endif // EDITOR_H
