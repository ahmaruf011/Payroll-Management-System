# Payroll Management System (C)

A console-based **academic payroll management project** developed in C for university coursework. This is a learning project, **not production-ready payroll software**.

## Features

- Admin and employee login menus
- Employee record management (add, view, search, update and delete)
- Attendance and leave management
- Salary records, salary slips, history, reports and statistics
- Employee loans and repayment-related functionality
- Dashboard summaries, notices and activity logging
- File-based data persistence

## Technologies and Concepts

- C programming language and standard C libraries
- Modular `.c` and `.h` files
- Structures, pointers and linked data structures
- File handling and console menus

## Project Structure

```text
Payroll-Management-System/
├── src/          # C source files
├── include/      # Header files
├── data/         # Local runtime data (not committed)
├── .gitignore
└── README.md
```

## Build and Run

Install GCC and open a terminal in the repository root.

```bash
gcc -std=c11 -Iinclude src/*.c -o payroll
./payroll
```

On Windows, run `./payroll.exe` in a compatible terminal. Run from the repository root because the application uses relative paths under `data/`.

## First-Run Administrator Setup

This public version does not contain a hard-coded default administrator password. Set a local demo password (4–29 characters) before running.

**Windows PowerShell:**

```powershell
$env:PAYROLL_ADMIN_PASSWORD = "choose-a-unique-demo-password"
.\payroll.exe
```

**Linux/macOS:**

```bash
export PAYROLL_ADMIN_PASSWORD='choose-a-unique-demo-password'
./payroll
```

Default administrator username: `admin`. If a local `data/admin.txt` exists, its credentials take precedence over the environment variable.

## Security and Limitations

**For educational use only.** Employee passwords and locally changed administrator passwords are still stored in plaintext. Some input paths lack length limits. Do not use real employee records, credentials or sensitive payroll data. Authentication, validation and data protection require improvement before real-world use.

## Future Improvements

- Implement secure password hashing
- Improve input validation and error handling
- Add automated tests
- Introduce database storage and role-based access control

## Project Context

Created as a university academic project to practice C programming and modular software development.
