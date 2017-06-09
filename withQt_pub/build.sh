qmake -project
qmake
mwc.pl --type gnuace -features qt4=1,boost=1
export QTDIR=/usr/share/qt4
make qt4=1 boost=1
