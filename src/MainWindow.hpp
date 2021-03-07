#pragma once

#include "CommonIncludes.hpp"

#include "GL_View3D/GL_View3D.hpp"


class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        MainWindow();
        ~MainWindow();
        ImProc::processes_stack Stack;

        void Process();
        GL_View3D* view3D;

        ImProc::image In;
        ImProc::image Out;

        uint32_t Width, Height;

        void GetSize(uint32_t *Width, uint32_t *Height);

};