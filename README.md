# Payroll Management System (C)

A console-based **academic payroll management project** developed in C for university coursework. This repository contains the academic source code with limited public-sharing safety edits and documents its modules and limitations. It is a learning project, **not production-ready payroll software**.

## Features

- Admin and employee login menus
- Employee record management (add, view, search, update and delete)
- Attendance and leave management
- Salary records, salary slips, history, reports and statistics
- Employee loans and repayment-related functionality
- Dashboard summaries, notices and activity logging
- File-based data persistence

## Technologies and concepts

- C programming language and standard C libraries
- Modular `.c` and `.h` files
- Structures, pointers and linked data structures
- File handling and console menus

## Project structure

```text
Payroll-Management-System/
├── src/          # C source files, including main.c
├── include/      # Header files
├── data/         # Local runtime data (not committed)
├── .gitignore
└── README.md
```

## Build and run

Install GCC (for example, through MSYS2/MinGW on Windows). Open a terminal in the repository root and run:

```bash
gcc -std=c11 -Iinclude src/*.c -o payroll
./payroll
```

On Windows, the executable is typically `payroll.exe`; run it with `./payroll.exe` in a compatible terminal. Run from the repository root because the program uses relative paths such as `data/employee.txt`. The `data/` folder is included but starts empty; runtime records may be generated as you use the application.

## First-run administrator setup

There is **no hard-coded default administrator password** in this public version.
Set a temporary password locally before running the program (at least 4 characters; maximum 29).

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

Default administrator username: `admin`. Do not use real credentials.
If a local `data/admin.txt` exists, its stored credentials take precedence over the environment variable. Delete this local file if you want to reset the demo login.

## Security and limitations

**For educational use only.** The public version removes the hard-coded administrator password and bounds login text inputs. **Employee passwords and locally changed administrator passwords are still stored in plaintext.** Several other input paths still lack length limits. Do not use real employee records, real credentials, or sensitive payroll data. The `data/` directory is excluded from Git to avoid publishing local records. Authentication, input validation and data protection require improvement before any real-world use.

## Possible improvements

- Replace plaintext passwords with secure authentication and password hashing
- Add bounds-checked input handling and stronger validation
- Add automated tests and improve error handling
- Use a database and role-based access control

## Project context

Created as a university academic project to practice C programming and modular software development.
