set(DevantEndWindowSrc
    Front.cpp

	Image/Image.cpp
	Image/Maths.cpp
	Image/ProcessingStack.cpp
	Image/Processes/ColorProcess.cpp
	Image/Processes/LoadImageProcess.cpp
	Image/Processes/SpatialProcess.cpp

	Maths/VectorMaths.cpp


	MainWindow.cpp

	SidePanel/SidePanel.cpp
	SidePanel/BaseProcessWidget.cpp
	SidePanel/Processes/ColorArithmetic/AddColorFromPaletteProcessWidget.cpp
	SidePanel/Processes/ColorArithmetic/SubtractColorFromPaletteProcessWidget.cpp
	SidePanel/Processes/ColorArithmetic/MultiplyColorFromPaletteProcessWidget.cpp
	SidePanel/Processes/ColorArithmetic/DivideColorFromPaletteProcessWidget.cpp
	SidePanel/Processes/ImageFileArithmetic/AddImageWidget.cpp
	SidePanel/Processes/ImageFileArithmetic/SubtractImageWidget.cpp
	SidePanel/Processes/ImageFileArithmetic/MultiplyImageWidget.cpp
	SidePanel/Processes/ImageFileArithmetic/DivideImageWidget.cpp
	SidePanel/Processes/ImageFileArithmetic/MinImageWidget.cpp
	SidePanel/Processes/ImageFileArithmetic/MaxImageWidget.cpp
	SidePanel/Processes/Spatial/SpatialProcessWidget.cpp

	SidePanel/CurveEditor/CurveEditor.cpp
	SidePanel/CurveEditor/CurveEditorScene.cpp
	SidePanel/CurveEditor/ControlPoint.cpp

	GL_View3D/GL_View3D.cpp
	GL_View3D/GL_Engine/GL_Object3D.cpp
	GL_View3D/GL_Engine/GL_Shader.cpp
	GL_View3D/GL_Engine/GL_Material.cpp
	GL_View3D/GL_Engine/GL_Mesh.cpp
	GL_View3D/GL_Engine/GL_Util.cpp
	GL_View3D/GL_Engine/GL_Renderer.cpp
)


add_executable(DevantEndWindow ${DevantEndWindowSrc})

target_link_libraries(DevantEndWindow Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::3DCore Qt5::3DExtras Qt5::3DRender Qt5::3DInput)

target_link_libraries(DevantEndWindow FreeImage)

install(TARGETS DevantEndWindow
		RUNTIME DESTINATION bin
		COMPONENT DevantEndWindowDist
) 