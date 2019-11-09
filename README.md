# ODA-IDE

This is a simply IDE for C and C++ development.

## Dependencies

Install QTermwidget from source
QTermWidget [link|https://github.com/lxqt/qtermwidget]

or from your distro manager
```sudo apt-get install libqtermwidget5-0  libqtermwidget5-0-dev```

## Compile

For compilation you need to have Qt5 and qmake5.

```bash
cd /desired/path/
git clone https://github.com/bartfaimate/ODA-IDE
mkdir build
cd build
qmake ../ODA-IDE.pro
make
```

## Status

\[ 2019-10-17\]
Refactored the previous version of ODA-IDE. Old version moved to ODA-IDE\_old https://github.com/bartfaimate/ODA-IDE_old

## License

GPLv3
