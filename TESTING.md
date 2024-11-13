# SmartBack System Testing and Validation

## Test Plan 1: Real-Time Pressure Monitoring
**Objective**: Verify that the pressure sensors accurately detect and report real-time weight distribution across the backrest.  
**Test Setup**: Secure the SmartBack system on a testing platform with adjustable weights to simulate varied load distributions. Connect the STM32 microcontroller to a data logger for capturing sensor readings.  
**Environmental Parameters**: Controlled at 22°C and 50% humidity.  
**Test Input**: Incremental weights from 1 kg to 10 kg at different positions.  
**Measurement Standard**: Pressure changes must be detected accurately within ±10 Pa and proportionally reflect applied weights.  
**Pass/Fail Criteria**:  
- **Pass**: Consistent change in readings with each weight increment within the ±10 Pa tolerance.  
- **Fail**: Sensor fails to detect or deviates beyond tolerance.

---

## Test Plan 2: Vibration Feedback for Posture Correction
**Objective**: Confirm immediate feedback from the vibration motor upon detecting uneven load distribution.  
**Test Setup**: Apply a 3 kg weight imbalance on one side of the backrest while monitoring motor response.  
**Environmental Parameters**: Standard room temperature.  
**Test Input**: Imbalance creation using weights.  
**Measurement Standard**: Motor activation within 1 second for imbalance detection.  
**Pass/Fail Criteria**:  
- **Pass**: Motor vibrates within 1 second and provides appropriate feedback.  
- **Fail**: Delay exceeds 1 second or fails to activate.

---

## Test Plan 3: Battery Life and Power Efficiency
**Objective**: Ensure the SmartBack system operates for 8 hours on a single charge.  
**Test Setup**: Fully charge the battery and monitor its usage over 8 hours.  
**Environmental Parameters**: Controlled environment without temperature/humidity impact.  
**Test Input**: Normal usage scenarios.  
**Measurement Standard**: System should enter low-power mode after 15 minutes of inactivity.  
**Pass/Fail Criteria**:  
- **Pass**: 8-hour operation without recharging.  
- **Fail**: Battery life falls short.

---

## Test Plan 4: Data Logging and Summary
**Objective**: Track posture corrections and provide summary feedback.  
**Test Setup**: Validate data transfer from sensors to STM32 microcontroller.  
**Environmental Parameters**: Users perform various activities like standing, walking, etc.  
**Test Input**: Simulated different postures and movements.  
**Measurement Standard**: Latency under 1 second for data transfer.  
**Pass/Fail Criteria**:  
- **Pass**: Continuous logging for at least 2 hours without interruptions.  
- **Fail**: Data loss or interruptions.

---

## Test Plan 5: Onboard Feedback Customization Controls
**Objective**: Allow users to customize vibration intensity and pressure sensitivity using onboard controls.  
**Test Setup**: Users adjust settings between 0.2g and 0.6g, and verify LED indicator responses.  
**Environmental Parameters**: Controlled environment to minimize distractions.  
**Test Input**: Switch between sensitivity levels.  
**Measurement Standard**: Vibration range within 0.2g and 0.6g.  
**Pass/Fail Criteria**:  
- **Pass**: Proper user adjustments and indicator responses.  
- **Fail**: No adjustments or incorrect responses.
