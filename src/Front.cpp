#include "CommonIncludes.hpp"
#include "MainWindow.hpp"


#include <set>
#include <array>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));

    MainWindow mainWindow;
    mainWindow.showMaximized();

    return app.exec(); 
}
