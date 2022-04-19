QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Administrator.cpp \
    CMD.cpp \
    Calculator.cpp \
    Data.cpp \
    SQL.cpp \
    User.cpp \
    adminwindow.cpp \
    backbutton.cpp \
    buywidget.cpp \
    change_commodity_dialog.cpp \
    change_information_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mypushbutton.cpp \
    on_self_dialog.cpp \
    order_complete.cpp \
    recharge.cpp \
    recharge_dialog.cpp \
    register_dialog.cpp \
    smallbutton.cpp \
    userwindow.cpp

HEADERS += \
    Administrator.h \
    CMD.h \
    Calculator.h \
    Data.h \
    SQL.h \
    User.h \
    adminwindow.h \
    backbutton.h \
    buywidget.h \
    change_commodity_dialog.h \
    change_information_dialog.h \
    mainwindow.h \
    mypushbutton.h \
    on_self_dialog.h \
    order_complete.h \
    recharge.h \
    recharge_dialog.h \
    register_dialog.h \
    smallbutton.h \
    userwindow.h

FORMS += \
    adminwindow.ui \
    buywidget.ui \
    change_commodity_dialog.ui \
    change_information_dialog.ui \
    mainwindow.ui \
    on_self_dialog.ui \
    order_complete.ui \
    recharge.ui \
    recharge_dialog.ui \
    register_dialog.ui \
    userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    res/newBackground.png \
    res/registButton.png \
    res/signButton.png

OTHER_FILES += myapp.rc

RC_FILE += myapp.rc
