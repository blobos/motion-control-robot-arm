
# Motion‑Controlled Robot Arm (Arduino UNO)
![image](https://user-images.githubusercontent.com/7018624/236264524-dbf8d309-f401-4df3-97fa-50235881d622.png)
A one‑hand‑operated robot arm built from simple materials (popsicle sticks + a weighted base), actuated by **3× SG90 micro‑servos**, **1× MG90S micro-servo** and a **28BYJ‑48 5 V stepper**. It uses an **MPU6050** IMU and a **6‑axis joystick** for intuitive motion control.

!Arduino build
!Claw / wrist assembly

---

## 🎥 Demo (click to watch)

![Video 1 — short overview(Youtube)](https://www.youtube.com/watch?v=lfKzZH-8aY8)

![Video 2 — additional motion clip(Youtube)](https://www.youtube.com/watch?v=bbvp0ymRyoc)

---

## ✨ Highlights

- **One‑hand control** using **joystick** + **MPU6050** (gyro/accelerometer).
- **Actuation**: 3× SG90 servos (hand/claw, wrist, elbow) + 1× MG90S servo (shoulder) + **28BYJ‑48 stepper** for base.
- **Materials**: popsicle sticks for links; **plastic yogurt/omega3 lid + mini weights** for a stable base.
- **Simplicity**: claw button removed; wrist/hand rotation not implemented (yet).
  ![image](https://user-images.githubusercontent.com/7018624/236264466-32aeda4c-b04f-4dd6-9bca-12ee0e63e1e5.png)

---

## 🧱 Bill of Materials

- **Arduino UNO**
- **Servos**: 3× SG90 micro‑servos, 1× MG90S micro-servo
- **Stepper**: 28BYJ‑48 5 V (ULN2003 driver board recommended)
- **Sensors/Controls**: MPU6050 IMU, 6‑axis analog joystick (only 2 axes used)
- **Structure**: popsicle sticks, screws/glue
- **Base**: plastic lid + mini weights
- **Power**: 5 V supply (servos + stepper), common ground with the UNO

---

## 🔌 Pin Map (from the sketch)

### Servos
- **Hand / Claw** — signal **D9**
- **Wrist** — signal **D6**
- **Elbow** — signal **D5**
- **Shoulder** — signal **D3**
*(All servos: Vcc → 5 V, GND → GND)*

### Joystick (6‑axis)
- **X‑axis** → **A0**
- **Y‑axis** → **A1**
*(Optional SW pin unused)*

### IMU (I²C)
- **MPU6050**: **SDA → A4**, **SCL → A5**
- **Vcc** → 3.3 V/5 V (module dependent), **GND** → GND

### Stepper (28BYJ‑48 via four digital pins)
- IN1 → **D10**
- IN2 → **D11**
- IN3 → **D12**
- IN4 → **D13**

> The code uses `Stepper baseStepper = Stepper(2038, 10, 12, 11, 13);` — empirical step count near 2048.

---

## 🕹️ Control Logic

- **Joystick X (A0)** → **Hand / Claw angle** (decrement below ~250, increment above ~850).
- **Joystick Y (A1)** → **Wrist angle** (decrement below ~250, increment above ~850).
- **MPU6050 pitch (AngleX)** → **Shoulder & Elbow** (inverse motion, only if `|AngleX| > 10`).
- **MPU6050 roll (AngleY)** → **Base stepper** (±1 step when roll exceeds ±15°; otherwise hold).

---

## ⚙️ Setup & Calibration

1. **Libraries**: `Servo`, `Wire`, `Stepper`, `MPU6050_tockn`.
2. **Upload** `robot_arm.ino` to your UNO.
3. **IMU offsets**: keep arm neutral; `calcGyroOffsets(true)` measures biases.
4. **Test**: move joystick X/Y slowly; tilt board to confirm shoulder/elbow & base behavior.
5. **Tune**: adjust servo pulse widths, angle constraints, and IMU dead‑zones to taste.

---

## 🔋 Power & Grounding

- Use a **separate 5 V supply** for servos/stepper; tie **all grounds together** (UNO GND ↔ Servo PSU GND ↔ ULN2003 GND ↔ sensor GND).
- Add **bulk capacitance** (e.g., 470–1000 µF) on the 5 V rail to reduce brown‑outs.

---

## ✅ Small Fixes / To‑Dos

- **Elbow constrain bug** in code:
  ```cpp
  // current line
  elbow.write(elbowAngle = constrain (shoulderAngle, 10, 120));
  // should be
  elbow.write(elbowAngle = constrain (elbowAngle, 10, 120));
 
