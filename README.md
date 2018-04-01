# audiobook
Minimal audio book reader

# requirements:
QT5
c++

# build and run:
http://doc.qt.io/qt-5/qmake-running.html

qmake -project
qmake
make

# build and install taglib:

cmake -DBUILD_EXAMPLES=ON .

or to a path: cmake -DCMAKE_INSTALL_PREFIX=/usr/

make

sudo make install

should install to /usr/local/include/taglib/
