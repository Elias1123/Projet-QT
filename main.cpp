#include <QApplication>
#include <QFileDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImageReader>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout layout(&window);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    layout.addWidget(&view);

    QPushButton changeButton("Changer d'image");
    layout.addWidget(&changeButton);

    QPushButton deleteButton("Supprimer l'image");
    layout.addWidget(&deleteButton);

    QObject::connect(&changeButton, &QPushButton::clicked, [&]{
        QFileDialog dialog;
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setNameFilter("Images (*.png *.jpg)");
        if (dialog.exec() != QDialog::Accepted)
            return;

        QImageReader reader(dialog.selectedFiles().first());
        QImage image = reader.read();
        if (image.isNull())
            return;

        scene.clear();
        scene.addPixmap(QPixmap::fromImage(image));
    });

    QObject::connect(&deleteButton, &QPushButton::clicked, [&]{
        scene.clear();
    });

    window.show();

    return app.exec();
}
