QT       += core gui sql multimedia multimediawidgets network printsupport widgets axcontainer charts serialport svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connection.cpp \
    dialog_map.cpp \
    dialog_stats.cpp \
    emission.cpp \
    emp.cpp \
    employes.cpp \
    equipement.cpp \
    exportexcelobject.cpp \
    forgot.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    qrcode.cpp \
    qrcodegeneratordemo.cpp \
    qrcodegeneratorworker.cpp \
    qrwidget.cpp \
    reclamation.cpp \
    smtp.cpp \
    sponsor.cpp \
    todolist.cpp \

HEADERS += \
    arduino.h \
    connection.h \
    dialog_map.h \
    dialog_stats.h \
    emission.h \
    emp.h \
    employes.h \
    equipement.h \
    exportexcelobject.h \
    forgot.h \
    mainwindow.h \
    qcustomplot.h \
    qrcode.h \
    qrcodegeneratordemo.h \
    qrwidget.h \
    reclamation.h \
    smtp.h \
    sponsor.h \
    todolist.h \
    webaxwidget.h \

FORMS += \
    arduino.ui \
    emission.ui \
    emp.ui \
    forgot.ui \
    mainwindow.ui


RC_ICONS = icon.ico

QMAKE_CXXFLAGS += -std=gnu++14

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

SUBDIRS += \
    Atelier_Connexion.pro \
    Atelier_Connexion.pro \
    GestionEquipement.pro \
    SMTPEmail.pro \
    Sponsor.pro


