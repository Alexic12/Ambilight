import sys
import serial
import serial.tools.list_ports
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget, QComboBox, QLabel
from PyQt5.QtGui import QPixmap, QIcon
from PyQt5.QtCore import QTimer  # Import QTimer
import time

def list_serial_ports():
    """ Lists serial port names """
    return [port.device for port in serial.tools.list_ports.comports()]

def find_esp32_com_port():
    ports = serial.tools.list_ports.comports()
    for port in ports:  # `port` is a ListPortInfo object
        if 'CH340' in port.description:  # Use port.description to get the description of the port
            try:
                # Correctly access the port name with port.device
                with serial.Serial(port.device, 115200, timeout=5) as ser:
                    ser.flushInput()  # Flush any existing input buffer
                    ser.write(b"DEVICE\n")  # Send the command
                    time.sleep(2)  # Increase sleep time to ensure device has time to respond
                    
                    # Wait for data to become available
                    while ser.in_waiting <= 0:
                        time.sleep(0.1)
                    
                    response = ser.read(ser.in_waiting).decode('utf-8').strip()  # Read and decode response, then strip whitespace
                    if "AMBILIGHT" in response:  # Check for expected response
                        return port.device  # Correctly return the device path or name
            except serial.SerialException as e:
                print(f"Error connecting to {port.device}: {e}")
    return None

class ESP32ControlApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.esp32_port = None  # Store the ESP32 port
        self.initUI()
        

        # Setup QTimer
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.detect_and_connect_esp32)
        self.timer.setInterval(5000)  # Check every 5000 milliseconds (5 seconds)
        self.detect_and_connect_esp32()  # Start the initial detection

    def initUI(self):
        self.setWindowTitle('Ambilight Control')
        self.setGeometry(100, 100, 400, 300)
        
        self.setWindowIcon(QIcon('icon.ico'))  # Replace with your icon path

        widget = QWidget(self)
        self.setCentralWidget(widget)
        
        layout = QVBoxLayout(widget)

        # Status label
        self.statusLabel = QLabel('Detecting Ambilight device...')
        layout.addWidget(self.statusLabel)

        # Dropdown for colors
        self.colorDropdown = QComboBox()
        all_colors = ["RED", "GREEN", "BLUE", "YELLOW", "ORANGE", "PURPLE", "AMETHYST", "AQUA", "AZURE", "BLACK", "BLUEVIOLET", "CHARTREUSE", "CORAL", "CYAN", "DARKBLUE", "DARKCYAN", "DARKGREEN", "DARKORANGE", "DARKRED", "DEEPSKYBLUE", "DODGERBLUE", "FIREBRICK", "FUCHSIA", "GOLD", "GOLDENROD", "GRAY", "GREENYELLOW", "HOTPINK", "INDIANRED", "INDIGO", "LAVENDER", "LIGHTBLUE", "LIGHTCORAL", "RAINBOW", "MOV_RAINBOW", "OFF"]
        self.colorDropdown.addItems(all_colors)
        layout.addWidget(self.colorDropdown)

        # Send button
        btnSend = QPushButton('Send Color', self)
        btnSend.clicked.connect(self.send_color)
        layout.addWidget(btnSend)

    def detect_and_connect_esp32(self):
        # Attempt to detect the device only if it's not already connected
        if not self.esp32_port:
            self.esp32_port = find_esp32_com_port()
            if self.esp32_port:
                self.statusLabel.setText(f"Ambilight device found on {self.esp32_port}")
                self.timer.stop()  # Stop checking if device is found
            else:
                self.statusLabel.setText("No Ambilight device detected. Retrying...")
                self.timer.start()  # Start or keep the timer running

    def send_color(self):
        if not self.esp32_port:
            print("No Ambilight device connected.")
            return

        selected_color = self.colorDropdown.currentText()
        try:
            with serial.Serial(self.esp32_port, 115200, timeout=1) as ser:
                ser.write((selected_color + "\n").encode())
                print(f"Sent '{selected_color}' to {self.esp32_port}")
        except serial.SerialException as e:
            print(f"Error: {e}")

def main():
    app = QApplication(sys.argv)
    ex = ESP32ControlApp()
    ex.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
