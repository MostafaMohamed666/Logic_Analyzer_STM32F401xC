import serial
import matplotlib.pyplot as plt

# === Config ===
PORT = 'COM8'           # Change this to your actual COM port
BAUDRATE = 115200         # Match your STM32 UART baud rate
SAMPLES_PER_CHANNEL = 10000
CHANNELS = 4
TOTAL_BYTES = SAMPLES_PER_CHANNEL * CHANNELS

# === Open serial port ===
ser = serial.Serial(PORT, BAUDRATE, timeout=2)
print(f"Listening on {PORT}... Waiting for start byte 's'")

# === Wait for single 's' byte to begin ===
while True:
    byte = ser.read()
    if byte == b's':
        print("Start byte received. Receiving data...")
        break

# === Read bytes ===
raw = ser.read(TOTAL_BYTES)
if len(raw) < TOTAL_BYTES:
    print(f"Warning: Only received {len(raw)} bytes. Expected {TOTAL_BYTES}.")

# === Parse interleaved data ===
channels = [[] for _ in range(CHANNELS)]
for i in range(0, len(raw), CHANNELS):
    for ch in range(CHANNELS):
        if i + ch < len(raw):
            byte = raw[i + ch]
            channels[ch].append(1 if byte == ord('1') else 0)

# === Plot ===
plt.figure(figsize=(10, 6))
t = list(range(len(channels[0])))

for ch in range(CHANNELS):
    plt.step(t, [v + ch * 2 for v in channels[ch]], where='mid', label=f'CH{ch+1}')

plt.yticks([i * 2 for i in range(CHANNELS)], [f'CH{i+1}' for i in range(CHANNELS)])
plt.xlabel("Sample Number")
plt.title("Captured Logic Analyzer Signals")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
