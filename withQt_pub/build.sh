qmake -project
qmake
mwc --type automake -features qt4=1 withQt.mpc
export QTDIR=/user/share/qt
make qt4=1
