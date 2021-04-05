#include "CommonIncludes.hpp"
#include "MainWindow.hpp"

#include <set>
#include <array>

#include "NodeEditor/NodeEditor.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));

    // MainWindow mainWindow;
    // mainWindow.showMaximized();


    //
    NodeEditor *nodeEditor = new NodeEditor();
    nodeEditor->showMaximized();



    return app.exec(); 
}
