#include "editor.h"
#include "ui_editor.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFile>

Editor::Editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
}

Editor::~Editor()
{
    delete ui;
}

void Editor::on_actionSalir_del_editor_triggered()
{
    QApplication::quit();
}

void Editor::on_actionGuardar_como_triggered()
{
    QXmlStreamWriter xmlWriter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Guardar información"), "",
                                                    tr("Documento XML (*.xml);;All Files (*)"));


    if(fileName.isEmpty()){
        return;
    }else{

        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly)) {

            QMessageBox::information(this, tr("No es posible guardar el archivo actual"),
                                     file.errorString());

        }else{

            xmlWriter.setDevice(&file);
            xmlWriter.setAutoFormatting(true);
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("Informacion");
            xmlWriter.writeTextElement("Nombre", ui->txtNombre->toPlainText());
            xmlWriter.writeTextElement("Apellido", ui->txtApellido->toPlainText());
            xmlWriter.writeTextElement("Texto", ui->txtTextoPlano->toPlainText());
            xmlWriter.writeEndElement();
            xmlWriter.writeEndDocument();
            file.close();

        }
    }


}

void Editor::on_actionAbrir_triggered()
{
    QString nombreAtributo;
    QXmlStreamReader xmlReader;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Abrir documento"), "",
                                                    tr("Documento XML (*.xml);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }else{

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Imposible abrir el documento escogido"),
                                     file.errorString());
            return;
        }else{
            QString nombre, apellido, texto;
            xmlReader.setDevice(&file);

            while(!xmlReader.atEnd()){

                nombreAtributo = xmlReader.name().toString();

                if(nombreAtributo == "Nombre" && nombre == ""){
                    nombre = xmlReader.readElementText();
                    qDebug() << "1er con";
                }else if(nombreAtributo == "Apellido" && apellido == ""){
                    apellido =  xmlReader.readElementText();
                    qDebug() << "2do con";
                }else if(nombreAtributo == "Texto" && texto == ""){
                    texto =  xmlReader.readElementText();
                    qDebug() << "3er con";
                }
                xmlReader.readNext();
                //break;
            }

            ui->txtNombre->setPlainText(nombre);
            ui->txtApellido->setPlainText(apellido);
            ui->txtTextoPlano->setPlainText(texto);

            file.close();
        }

    }
}
