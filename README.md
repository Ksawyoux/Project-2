
# Hospital Management System

## Overview
This Hospital Management System is a simple command-line application developed in C to manage patient queues in a hospital. The system allows for adding new patients, processing the next patient, updating patient priority, and displaying all patients in the queue. It supports basic priority queue operations including insertion, deletion, and dynamic updates.

## Features
- **Add New Patients:** Input patient details including name, gender, SSN, date of birth, and a task (e.g., surgery, X-ray scan).
- **Process Patients:** Processes patients based on their priority and arrival time.
- **Update Patient Priority:** Change a patient's priority, which automatically updates their assigned task.
- **Display All Patients:** View all patients currently in the queue with details including name, gender, DOB, SSN, task, priority, and the timestamp of when they were added to the queue.
- **Duplicate SSN Check:** Ensures that no two patients have the same SSN in the system.

## Compilation and Running
To compile and run the Hospital Management System, follow these steps:

### Requirements
- GCC Compiler or any standard C compiler that supports C99.

### Compilation
Navigate to the directory containing the source code and open your terminal. Type the following command to compile the program:
```bash
gcc -o HospitalManagementSystem HospitalManagementSystem.c
```

### Execution
After compilation, run the program by typing:
```bash
./HospitalManagementSystem
```

## Using the System
The program operates in a menu-driven manner. Here are the options you will see:

1. **Add New Patient** - Follow the prompts to enter patient details.
2. **Process Next Patient** - Automatically selects and processes the patient with the highest priority.
3. **Update Patient Priority** - Enter the SSN of the patient to update and follow prompts to change their priority and task.
4. **Display All Patients** - Lists all the patients currently in the queue.
5. **Exit** - Closes the application.

## File Structure
- `HospitalManagementSystem.c`: Contains the source code with all functionalities.

## Contributing
Contributions to the Hospital Management System are welcome. Please ensure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)

## Contact
For support or queries, reach out via email at [support@example.com](mailto:support@example.com).
