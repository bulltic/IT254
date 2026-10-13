# Webcam Object Classifier with Arduino 7-Segment Display

A computer-vision project that uses a webcam and a Teachable Machine image-classification model to recognize objects, then sends the predicted class to an Arduino over USB serial. The Arduino displays the class number on a 7-segment display.

The project includes a Python-only version for testing predictions and a serial-enabled version that connects the classifier to the Arduino.

## Features

- Runs a trained image-classification model on live webcam frames.
- Uses OpenCV to capture and preprocess camera images.
- Prints the predicted class and confidence score in the terminal.
- Sends a class number to an Arduino when the prediction confidence meets a configurable threshold.
- Displays the received number on a 7-segment display.
- Includes photos of the hardware setup in `Pictures/`.

## How It Works

1. The webcam captures a frame.
2. Python center-crops the frame to a square, resizes it to `224 × 224`, converts it to RGB, and normalizes pixel values to the range `-1` to `1`.
3. The Keras model predicts a class.
4. The serial-enabled script checks the prediction confidence. If it is at least `0.80`, it sends the mapped class number to the Arduino.
5. The Arduino reads the newline-terminated serial message and displays the corresponding digit.

The current labels in `labels.txt` are:

| Model index | Label | Serial behavior |
| ---: | --- | --- |
| `0` | Background | No message is mapped |
| `1` | Pens or Pencils | Sends `1` |
| `2` | Other Objects | Sends `2` |

The labels and serial mapping are defined by `labels.txt` and `MESSAGE_FOR_LABEL` in `GoogleTeachableCode-KerasOpenCV-Serial.py`.

## Repository Structure

```text
Project/
├── GoogleTeachableCode-KerasOpenCV.py
├── GoogleTeachableCode-KerasOpenCV-Serial.py
├── keras_model.h5
├── labels.txt
├── ard_final/
│   └── ard_final.ino
└── Pictures/
    ├── IMG_3519.jpeg
    ├── IMG_3520.jpeg
    ├── IMG_3521.jpeg
    ├── IMG_3523.jpeg
    ├── IMG_3524.jpeg
    ├── IMG_3525.jpeg
    └── IMG_3526.jpeg
```

- `GoogleTeachableCode-KerasOpenCV.py` — runs webcam inference and prints predictions; does not require an Arduino connection.
- `GoogleTeachableCode-KerasOpenCV-Serial.py` — runs inference and sends class numbers to the Arduino over serial.
- `keras_model.h5` — trained Keras image-classification model exported from Google Teachable Machine.
- `labels.txt` — class indices and names used by the model.
- `ard_final/ard_final.ino` — Arduino sketch that receives serial messages and controls the display.
- `Pictures/` — project and hardware photos.

## Requirements

### Hardware

- A computer with Python support
- A webcam
- An Arduino-compatible board
- A 7-segment display
- A breadboard and jumper wires
- A USB cable to connect the Arduino to the computer
- Current-limiting resistors for the display segments, as appropriate for the display and board

Wire the 7-segment display to match the pin assignments in `ard_final/ard_final.ino`. The sketch uses these Arduino pins:

| Segment | Arduino pin |
| --- | ---: |
| A | 7 |
| B | 6 |
| C | 5 |
| D | 11 |
| E | 10 |
| F | 8 |
| G | 9 |
| Decimal point | 4 |

The sketch drives segments `HIGH` to illuminate them and `LOW` to turn them off. This assumes a display and wiring arrangement compatible with that behavior; verify whether your display is common-cathode or common-anode before wiring.

### Software

- Python 3
- A working webcam driver and camera permission
- Arduino IDE
- Python packages:
  - OpenCV (`opencv-python`)
  - NumPy
  - `tf-keras`
  - TensorFlow
  - PySerial (`pyserial`)

The model script sets `TF_USE_LEGACY_KERAS=1` before importing TensorFlow-related modules because the exported model is intended for legacy Keras. Package compatibility can vary by Python and TensorFlow version, so use a virtual environment and install compatible versions if necessary.

## Setup

### 1. Download or clone the project

Place the Python scripts, `keras_model.h5`, and `labels.txt` in the same directory. The scripts locate the model and labels relative to their own file paths.

### 2. Create a virtual environment

**Windows (PowerShell):**

```powershell
py -m venv .venv
.\.venv\Scripts\Activate.ps1
python -m pip install --upgrade pip
```

**macOS / Linux:**

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
```

### 3. Install dependencies

```bash
pip install tensorflow tf-keras opencv-python numpy pyserial
```

If installation fails, check that your Python version is supported by the TensorFlow version being installed. You can also install compatible versions of TensorFlow and `tf-keras` together.

### 4. Connect the Arduino (serial version only)

1. Open `ard_final/ard_final.ino` in the Arduino IDE.
2. Select your board and its port from the **Tools** menu.
3. Upload the sketch to the Arduino.
4. Close the Arduino IDE Serial Monitor before running the Python serial script; another application holding the same port can prevent the Python program from connecting.
5. Find the port name shown in the Arduino IDE.

In `GoogleTeachableCode-KerasOpenCV-Serial.py`, update:

```python
SERIAL_PORT = "COM7"
BAUD_RATE = 9600
```

Set `SERIAL_PORT` to your actual port. Examples include `COM3` on Windows or `/dev/cu.usbmodem...` on macOS. The baud rate must match `Serial.begin(9600)` in the Arduino sketch.

## Run the Project

### Option A: Test the model without an Arduino

From the directory containing the Python script and model files, run:

```bash
python GoogleTeachableCode-KerasOpenCV.py
```

A webcam window should open. The terminal prints the predicted class and confidence score for each frame.

### Option B: Run the classifier with the Arduino display

After uploading the Arduino sketch and configuring the serial port, run:

```bash
python GoogleTeachableCode-KerasOpenCV-Serial.py
```

When the model predicts a mapped class with confidence of at least `80%`, the script sends its number to the Arduino. The Arduino displays that digit.

Click the webcam window and press **`q`** or **Esc** to quit. You can also stop the script with `Ctrl+C` in the terminal.

## Configuration

In `GoogleTeachableCode-KerasOpenCV-Serial.py`, you can adjust:

```python
MESSAGE_FOR_LABEL = {
    1: "1",
    2: "2",
}

BAUD_RATE = 9600
CONFIDENCE_THRESHOLD = 0.80
SERIAL_PORT = "COM7"
```

- `MESSAGE_FOR_LABEL` maps model output indices to serial messages. The Arduino sketch currently recognizes digits `0` through `9` and the message `off`.
- `CONFIDENCE_THRESHOLD` controls how confident the model must be before a mapped message is sent.
- `SERIAL_PORT` must match the connected board's port.
- `BAUD_RATE` must match the Arduino sketch's serial baud rate.

To change the classes, retrain or update the Teachable Machine model and keep `labels.txt` aligned with the model's output order. If you change the labels or serial messages, update the Python mapping and Arduino sketch as needed.

## Troubleshooting

- **Camera does not open:** Try changing `cv2.VideoCapture(0)` to `cv2.VideoCapture(1)`. Also check operating-system camera permissions and close other apps using the camera.
- **Arduino connection fails:** Verify `SERIAL_PORT`, check the USB cable and board connection, and close the Arduino Serial Monitor or other programs using the port.
- **No digit appears:** Confirm that the Python confidence threshold is reached, the predicted class has an entry in `MESSAGE_FOR_LABEL`, the baud rate matches, and the Arduino sketch is uploaded.
- **Model or label file not found:** Keep `keras_model.h5` and `labels.txt` beside the Python script being run.
- **Keras/TensorFlow import or model-loading errors:** Check compatibility between Python, TensorFlow, and `tf-keras`. The script uses the legacy Keras interface for the exported model.
- **Display segments are incorrect or do not light:** Check the wiring, segment pinout, display type, and resistor placement. The sketch assumes `HIGH` turns a segment on.

## Notes and Limitations

- The classifier's performance depends on the images used to train the model, lighting, camera quality, object placement, and background.
- The confidence score is the model's prediction score, not a guarantee that the classification is correct.
- The current serial script sends digits for the two mapped object classes. Background predictions do not send a message, so the display can continue showing the last digit.
- The Arduino sketch includes an `off` command to clear the display, but the current Python mapping does not send it.
- This project is a demonstration and should not be relied on for safety-critical decisions.

## License

No license file was included in the provided project. Add a `LICENSE` file if you intend to distribute the project, and make sure the model and any third-party components are licensed appropriately.
