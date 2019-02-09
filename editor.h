#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QtWidgets>
#include <QLineEdit>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QTextEdit;
QT_END_NAMESPACE

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    ~Editor();

private:
    QLineEdit *txtNombre;
    QMenu *menuArchivo;
    QLineEdit *txtApellido;
    QTextEdit *txtDescripcion;
    QString appTitle = "Editor XML v2", nombArchivo = "";

private slots:
    void nuevo();
    void guardar();
    void guardarComo();
    void abrir();
    void salir();
    void crearMenu();

};

#endif // EDITOR_H
