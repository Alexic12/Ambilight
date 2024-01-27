import sys
import serial
import serial.tools.list_ports
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget, QComboBox, QLabel
from PyQt5.QtGui import QPixmap, QIcon
import time

def list_serial_ports():
    """ Lists serial port names """
    return [port.device for port in serial.tools.list_ports.comports()]

class ESP32ControlApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('Ambilight Control')
        self.setGeometry(100, 100, 400, 300)  # Increased window size
        
        # Set window icon
        self.setWindowIcon(QIcon('icon.ico'))  # Replace with your icon path

        # Main widget
        widget = QWidget(self)
        self.setCentralWidget(widget)
        
        # Set background image
        background = QLabel(widget)
        pixmap = QPixmap('logo.png')  # Replace with your image path
        #background.setPixmap(pixmap)
        background.resize(400, 300)  # Same size as the window

        # Layout
        layout = QVBoxLayout(widget)

        # Dropdown for COM ports
        self.comPortDropdown = QComboBox()
        self.comPortDropdown.addItems(list_serial_ports())
        layout.addWidget(self.comPortDropdown)

        # Dropdown for colors
        self.colorDropdown = QComboBox()
        all_colors = [ "RED", "GREEN", "BLUE", "YELLOW", "ORANGE", "PURPLE", "AMETHYST", "AQUA", "AZURE", "BLACK", "BLUEVIOLET", "CHARTREUSE", "CORAL", "CYAN", "DARKBLUE", "DARKCYAN", "DARKGREEN", "DARKORANGE", "DARKRED", "DEEPSKYBLUE", "DODGERBLUE", "FIREBRICK", "FUCHSIA", "GOLD", "GOLDENROD", "GRAY", "GREENYELLOW", "HOTPINK", "INDIANRED", "INDIGO", "LAVENDER", "LIGHTBLUE", "LIGHTCORAL", "RAINBOW", "MOV_RAINBOW", "OFF"]
        self.colorDropdown.addItems(all_colors)
        layout.addWidget(self.colorDropdown)

        # Send button
        btnSend = QPushButton('Send Color', self)
        btnSend.clicked.connect(self.send_color)
        layout.addWidget(btnSend)

    def send_color(self):
        selected_port = self.comPortDropdown.currentText()
        selected_color = self.colorDropdown.currentText()
        try:
            with serial.Serial(selected_port, 115200, timeout=1) as ser:
                ser.write((selected_color + "\n").encode())
                # Add delay
                time.sleep(0.1)
                ser.write((selected_color + "\n").encode())
                time.sleep(0.2)
                ser.write((selected_color + "\n").encode())
                print(f"Sent '{selected_color}' to {selected_port}")
        except serial.SerialException as e:
            print(f"Error: {e}")

def main():
    app = QApplication(sys.argv)
    ex = ESP32ControlApp()
    ex.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
