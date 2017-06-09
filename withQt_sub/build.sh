export QTDIR=/usr/share/qt4
qmake -project
qmake
mwc.pl --type automake -features qt4=1,boost=1 
make qt4=1 boost=1
