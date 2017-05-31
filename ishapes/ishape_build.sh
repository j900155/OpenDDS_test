qmake -project
qmake
mwc --type automake -features qt4=1,boost=1 ishapes.mpc
export QTDIR=/usr/share/qt4
make qt4=1 boost=1
