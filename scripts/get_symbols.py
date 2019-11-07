from PyQt5 import QtGui
from PyQt5 import QtWidgets
from PyQt5 import QtCore


import sys


class Window(QtWidgets.QMainWindow):

    def __init__(self):
        super(Window,self).__init__()
        self.setGeometry(100,100,800,600)
        self.setWindowTitle("Qregexp test")
        # self.show()

        path = "/home/mate/develop/odaide/ODA-IDE2/editor.cpp"
        file = open()

        rex = ""
        regexp = QtCore.QRegExp()



def main():
    app = QtWidgets.QApplication(sys.argv)
    window = Window()
    sys.exit(app.exec())
  

if __name__ == '__main__':
   # window()
  main()