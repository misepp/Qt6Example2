find_package(Qt6 6.2 COMPONENTS Qml REQUIRED)

qt_add_resources(QML_RESOURCES qml.qrc)
qt_add_resources(QML_ASSETS assets.qrc)

# static libraries for the resources
add_library(ui_qml STATIC ${QML_RESOURCES})
add_library(ui_assets STATIC ${QML_ASSETS})
target_link_libraries(ui_qml PRIVATE Qt6::Qml)
