export QTDIR=/usr/share/qt4
qmake -project
qmake
mwc.pl --type automake -features qt4=1 withQt.mpc
make qt4=1 boost=1
