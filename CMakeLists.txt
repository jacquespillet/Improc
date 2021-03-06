cmake_minimum_required(VERSION 3.10)
project(DevantEnd)
set(PROJECT_BRIEF "Front end for renderer")

set(CMAKE_AUTOMOC ON)

set(CMAKE_BUILD_TYPE RELEASE)
SET(GCC_COMPILE_FLAGS "-std=c++11 -Wall -03 -g -static /bigobj")
set(GCC_LINK_FLAGS "")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
set(CMAKE_GENERATOR_PLATFORM "x64")

find_package(Qt5 COMPONENTS Core Widgets Gui OpenGL 3DCore 3DExtras 3DRender 3DInput)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
set(QT_BIN_DIR "C:/Qt/5.12.2/msvc2017_64/bin")
set(QT_BUILD_DIR  "C:/Qt/5.12.2/msvc2017_64")

#glm
set(GLM_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/glm)
include_directories(${GLM_INC_DIR})

#stbi
set(STBI_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/STB_image)
include_directories(${STBI_INC_DIR})


#FreeImag
set(FREEIMAGE_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/FreeImage/Dist/x64)
set(FREEIMAGE_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/FreeImage/Dist/x64)
link_directories(${FREEIMAGE_INC_DIR})
include_directories(${FREEIMAGE_INC_DIR})

include_directories(src)
add_subdirectory(src)


install(FILES ${QT_BIN_DIR}/Qt5Core.dll
			  ${QT_BIN_DIR}/Qt5Cored.dll
			  ${QT_BIN_DIR}/Qt5Gui.dll
			  ${QT_BIN_DIR}/Qt5Guid.dll
			  ${QT_BIN_DIR}/Qt5Widgets.dll
			  ${QT_BIN_DIR}/Qt5Widgetsd.dll
			  ${QT_BIN_DIR}/Qt5Charts.dll
			  ${QT_BIN_DIR}/Qt5Chartsd.dll
			  ${QT_BIN_DIR}/Qt5OpenGL.dll
			  ${QT_BIN_DIR}/Qt5OpenGLd.dll
			  ${QT_BIN_DIR}/Qt5Concurrent.dll
			  ${QT_BIN_DIR}/Qt5Concurrentd.dll
			  ${QT_BIN_DIR}/Qt5Gamepad.dll
			  ${QT_BIN_DIR}/Qt5Gamepadd.dll
			  ${QT_BIN_DIR}/Qt53DCore.dll
			  ${QT_BIN_DIR}/Qt53DCored.dll
			  ${QT_BIN_DIR}/Qt53DExtras.dll
			  ${QT_BIN_DIR}/Qt53DExtrasd.dll
			  ${QT_BIN_DIR}/Qt53DInput.dll
			  ${QT_BIN_DIR}/Qt53DInputd.dll
			  ${QT_BIN_DIR}/Qt53DLogic.dll
			  ${QT_BIN_DIR}/Qt53DLogicd.dll
			  ${QT_BIN_DIR}/Qt53DRender.dll
			  ${QT_BIN_DIR}/Qt53DRenderd.dll
			  ${QT_BIN_DIR}/Qt5Network.dll
			  ${QT_BIN_DIR}/Qt5Networkd.dll
			  
		DESTINATION bin
		COMPONENT DevantEndWindowDist
)

install(FILES ${FREEIMAGE_BIN_DIR}/FreeImage.dll
		DESTINATION bin
		COMPONENT DevantEndWindowDist
)

install(DIRECTORY ${QT_BUILD_DIR}/plugins/platforms
		DESTINATION bin
		COMPONENT DevantEndWindowDist
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/res/
		DESTINATION bin/res
		COMPONENT DevantEndWindowDist
)