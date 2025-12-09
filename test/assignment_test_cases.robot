*** Settings ***
Documentation    Embedded Systems Project Test Cases

*** Test Cases ***

Test Case 1: Enter Required Temperature (Keypad Input)

[Documentation] Ensure keypad correctly enters digits in Mode 1.
# Set mode to 1 using the push button.
# Press numeric keys (e.g., 2 → 5).
# LCD should show “SET TEMP: 25”.

Test Case 2: Save Required Temperature

[Documentation] Ensure the entered temperature is saved into memory after pressing “Enter” key.
# After entering temperature, press “Enter”.
# LCD displays “TEMP SAVED”.
# Value stored in EEPROM matches keypad input.

Test Case 3: Push Button Mode Switching

[Documentation] Confirm push button toggles between Mode 1 and Mode 2.
# Press mode button once → LCD shows “MODE 2”.
# Press button again → LCD shows “MODE 1”.
# Assert correct switching each time.

Test Case 4: Mode 2 Increment Temperature Button

[Documentation] Ensure external “#” button increments temperature by 1°.
# Switch to Mode 2.
# Press increment button once.
# LCD value increases by exactly 1.

Test Case 5: Mode 2 Decrement Temperature Button

[Documentation] Ensure “*” button decrements temperature by 1°.
# Switch to Mode 2.
# Press decrement button once.
# LCD value decreases by exactly 1.

Test Case 6: LM35 Sensor Real-Time Temperature Reading

[Documentation] Ensure system reads live temperature from LM35.
# Apply known temperature source (e.g., 30°C).
# LCD displays real-time reading “TEMP NOW: 30”.
# Variation stays within ±1°C accuracy.

Test Case 7: Fan Motor Direction Control

[Documentation] Verify motor rotates CW and CCW according to system command.
# Set required temperature lower than current.
# System should turn fan ON (cooling) → clockwise rotation.
# Set required temp higher than current.
# System rotates motor in opposite direction (heating mode).

Test Case 8: Motor Speed Levels

[Documentation] Validate motor speed changes with temperature difference.
# If difference = small (1–2°C) → LOW speed.
# If difference = moderate (3–5°C) → MED speed.
# If difference > 5°C → HIGH speed.
# Assert RPM matches levels.

Test Case 9: Motor Status LED Indicator

[Documentation] Ensure LED indicates motor ON/OFF status.
# Motor OFF → LED OFF.
# Motor ON → LED ON.
# Toggle motor condition and verify LED behavior.

Test Case 10: Mode Switch Debounce Validation

[Documentation] Ensure push button for mode switching does not bounce.
# Press the button rapidly 5 times.
# System must detect the correct number of valid presses.
# No accidental double-switching.

Test Case 11: Temperature Boundary Validation

[Documentation] Ensure system enforces allowed temp range (e.g., 16–30°C).
# Try entering “10” using keypad.
# LCD should show “last temp set”.
# Value should NOT save.

Test Case 12: Power Cycle Persistence Check

[Documentation] Ensure last saved temperature is loaded from EEPROM after reset.
# Save required temperature (e.g., 24°C).
# Power cycle the board.
# LCD shows “LAST TEMP: 24”.
# Fan logic uses this value.

Test Case 13: Real-Time Control Logic Integration

[Documentation] Ensure full closed-loop control works correctly based on real-time LM35 readings.
# Current temp = 32°C, required temp = 24°C.
# Motor must run HIGH speed cooling in correct direction.
# When real temp drops to 24°C, motor stops and LED turns OFF.