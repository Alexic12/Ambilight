import serial
import serial.tools.list_ports
import time

def find_esp32_com_ports():
    esp32_ports = []
    ports = serial.tools.list_ports.comports()
    for port, desc, hwid in sorted(ports):
        if 'CH340' in desc:  # Adjust this condition if needed
            esp32_ports.append(port)
    return esp32_ports

def identify_and_connect_to_esp32(ports):
    for port in ports:
        try:
            # Open the serial port with a higher timeout
            with serial.Serial(port, 115200, timeout=5) as ser:
                print(f"Trying {port}...")
                ser.flushInput()  # Flush any existing input buffer
                ser.write(b"DEVICE\n")  # Send the command
                time.sleep(2)  # Increase sleep time to ensure device has time to respond
                
                # Wait for data to become available
                while ser.in_waiting <= 0:
                    time.sleep(0.1)
                
                response = ser.read(ser.in_waiting).decode('utf-8').strip()  # Read and decode response, then strip whitespace
                if "AMBILIGHT" in response:  # Check for expected response
                    print(f"Correct ESP32 identified on {port}. Staying connected...")
                    return ser.portstr
                else:
                    print(f"{port} responded but is not the correct device.")
        except serial.SerialException as e:
            print(f"Error connecting to {port}: {e}")
    return None

# Find all possible ESP32 ports
esp32_ports = find_esp32_com_ports()
if not esp32_ports:
    print("No potential ESP32 devices found.")
else:
    # Attempt to identify and connect to the correct ESP32
    correct_port = identify_and_connect_to_esp32(esp32_ports)
    if correct_port:
        # If a correct device is found, you can continue to communicate with it here
        # For example, you can create a new serial connection to `correct_port`
        # Remember, the connection in `identify_and_connect_to_esp32` is closed when the function ends
        print(f"Connected to ESP32 on {correct_port}. You can now communicate with it.")
    else:
        print("No correct ESP32 device was identified.")

