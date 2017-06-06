create *.mpc <br>
check *.moc <br>
if not : <br>
do moc -o *_moc.cpp *.h <br>
add *.moc to *.mpc <br>
<br>
qmake -project<br>
qmake<br>
