# Elevator Simulation (C++)

A single-elevator simulator that handles multiple **time-based pickup and drop-off requests**.  
The elevator moves one floor per time step and merges compatible requests along its route using **priority queues**.

---


## Build & Run
### Build
```bash
make build
```

### Run with an input file
```bash
./elevator < input.txt
```

### Clean
```bash
make clean
```

## Assumptions and Features Not Implemented

### **Assumptions**
- The elevator moves **one floor per simulation step** (no travel time per distance or acceleration).  
- Each request represents a **single passenger** (no batching of multiple people from the same floor).  
- The elevator **immediately picks up or drops off** when reaching a floor (no door-open delays).  
- Input data is assumed to be **valid** (floors are non-negative integers, and times are sorted or reasonably spaced).  
- There is only **one elevator**, and it always starts at the given `startFloor` at time `0`.  
- Floors are assumed to be sequential integers (no basement or skipped levels).  

---

### **Features Not Implemented**
- **Multiple elevators** — the system currently handles one elevator only.  
- **Passenger capacity limits** — the elevator can accept unlimited requests.  
- **Door timing or delays** — stops occur instantly when the elevator reaches a target floor.  
- **Energy or efficiency optimization** — direction switches are based solely on remaining stops, not energy minimization.  
- **Out-of-order request handling** — requests are processed at or after their time value; if two arrive simultaneously, they’re added in input order.  

---


---

## Input Format
The simulator reads from standard input (`cin`) or a file redirected to stdin.

```
startFloor
numRequests
time fromFloor toFloor
time fromFloor toFloor
...
```

### Example (`input01.txt`)
```
1
4
0 1 8
2 3 6
6 2 5
10 4 9
```

**Meaning**
- Elevator starts at floor **1**  
- There are **4** total requests  
- At time **0**, request **1 → 8**  
- At time **2**, request **3 → 6**, etc.

---

## Simulation Summary
- Elevator moves **one floor per time step**  
- Requests are injected at their specified **time**  
- While going **UP**, it serves higher floors using a **min-heap** (`upStops`)  
- While going **DOWN**, it serves lower floors using a **max-heap** (`downStops`)  
- When current-direction stops are exhausted, it **switches direction** if the other heap isn’t empty  
- When both heaps empty, elevator becomes **IDLE**

---

## Example Run 
**Command**
```bash
./elevator < input01.txt
```

**Output (sample)**
```
[t=0] New request: from 1 to 8
--- Step 0 ---
Stop at floor 1 (UP)
Elevator: Floor 2 | Direction: UP | UpStops: 1 | DownStops: 0
...
Simulation complete at time 20.
```

---
