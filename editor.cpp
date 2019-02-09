#include "editor.h"

Editor::Editor(QWidget *parent) :
    QMainWindow(parent)
{

    QWidget *widget = new QWidget;
    this->setCentralWidget(widget);
    crearMenu();

    QLabel *labelNombre = new QLabel(tr("Nombre:"));
    txtNombre = new QLineEdit;

    QLabel *labelApellido = new QLabel(tr("Apellido:"));
    txtApellido = new QLineEdit;

    QLabel *labelDescripcion = new QLabel(tr("Texto:"));
    txtDescripcion = new QTextEdit;

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(labelNombre, 0, 0);
    mainLayout->addWidget(txtNombre, 0, 1);
    mainLayout->addWidget(labelApellido, 1, 0);
    mainLayout->addWidget(txtApellido, 1, 1);
    mainLayout->addWidget(labelDescripcion, 2, 0);
    mainLayout->addWidget(txtDescripcion, 2, 1);

    this->setMinimumSize(600, 460);
    this->setMaximumSize(1280, 720);
    this->setLayout(mainLayout);
    this->setWindowTitle(appTitle);
    widget->setLayout(mainLayout);

}

Editor::~Editor()
{
    delete this;
}

void::Editor::crearMenu(){

    //[1] Creación de la instancia del objeto Menú y las acciones que éste va a contener.

    menuArchivo = new QMenu(tr("Archivo"));

    QAction *accionNuevo = new QAction(tr("&Nuevo documento"), this);
    accionNuevo->setShortcuts(QKeySequence::New);

    QAction *accionAbrir = new QAction(tr("&Abrir documento"), this);
    accionAbrir->setShortcuts(QKeySequence::Open);

    QAction *accionSalir = new QAction(tr("&Salir del programa"), this);
    accionSalir->setShortcuts(QKeySequence::Quit);

    QAction *accionGuardar = new QAction(tr("&Guardar"), this);
    accionGuardar->setShortcuts(QKeySequence::Save);

    QAction *accionGuardarComo = new QAction(tr("Guardar como"), this);
    accionGuardarComo->setShortcuts(QKeySequence::SaveAs);

    //[2] Conectar cada acción con sus respectivos metodos:

    connect(accionNuevo, &QAction::triggered, this, &Editor::nuevo);
    connect(accionAbrir, &QAction::triggered, this, &Editor::abrir);
    connect(accionGuardar, &QAction::triggered, this, &Editor::guardar);
    connect(accionGuardarComo, &QAction::triggered, this, &Editor::guardarComo);
    connect(accionSalir, &QAction::triggered, this, &Editor::salir);

    // [3] Construcción del menú:

    menuArchivo->addAction(accionNuevo);
    menuArchivo->addAction(accionAbrir);
    menuArchivo->addAction(accionGuardar);
    menuArchivo->addAction(accionGuardarComo);
    menuArchivo->addSeparator();
    menuArchivo->addAction(accionSalir);

    this->menuBar()->addMenu(menuArchivo);

}
void::Editor::nuevo(){

    nombArchivo = "";
    this->setWindowTitle(appTitle + " | " + "Archivo nuevo");
    txtNombre->clear();
    txtApellido->clear();
    txtDescripcion->clear();

}

void::Editor::abrir(){

    QString nombreAtributo;
    QXmlStreamReader xmlReader;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Abrir documento"), "",
                                                    tr("Documento XML (*.xml);;All Files (*)"));

    if(fileName.isEmpty()){
        return;

    }else{

        nombArchivo = fileName;

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

                }else if(nombreAtributo == "Apellido" && apellido == ""){
                    apellido =  xmlReader.readElementText();

                }else if(nombreAtributo == "Texto" && texto == ""){
                    texto =  xmlReader.readElementText();

                }
                xmlReader.readNext();
                //break;
            }

            txtNombre->setText(nombre);
            txtApellido->setText(apellido);
            txtDescripcion->setPlainText(texto);

            file.close();
            this->setWindowTitle(appTitle + " | " + fileName);
        }

    }
}

void::Editor::guardar(){

    if(nombArchivo != ""){
        qDebug()<<"Acción guardar.";

    }else{
        guardarComo();
    }

}

void::Editor::guardarComo(){

    QXmlStreamWriter xmlWriter;

    if(txtNombre->text() != "" && txtApellido->text() != "" && txtDescripcion->toPlainText() != ""){

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
                xmlWriter.writeTextElement("Nombre", txtNombre->text());
                xmlWriter.writeTextElement("Apellido",txtApellido->text());
                xmlWriter.writeTextElement("Texto", txtDescripcion->toPlainText());
                xmlWriter.writeEndElement();
                xmlWriter.writeEndDocument();
                file.close();

                nombArchivo = fileName;
                this->setWindowTitle(appTitle + " | " + fileName);
            }
        }


    }else{
        QMessageBox::information(this, "Error" , "No puede guardar archivos con campos vacíos.");
    }


}

void::Editor::salir(){
    QCoreApplication::exit();
}


