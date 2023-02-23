find_package(Qt6 6.2 COMPONENTS Core Gui Network REQUIRED)

qt_add_executable(appExample
    main.cpp
    backend.cpp backend.h
    dataserver.cpp dataserver.h
    dataproducerbase.cpp dataproducerbase.h
    speeddataproducer.cpp speeddataproducer.h
    financedataproducer.cpp financedataproducer.h
    prducerfactory.h prducerfactory.cpp
    datamodel.h datamodel.cpp
)

target_link_libraries(appExample
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    ui_qml
    ui_assets
)

set_target_properties(appExample PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appExample
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
