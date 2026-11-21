# Payroll Management System (C)

A modular, console-based **academic payroll management system** implemented in C (`C11`) for university coursework. Designed to practice structured programming, modular architecture, and file-based persistence—**intended strictly for educational use, not production deployment**.

> **Academic & Security Notice:** This project is an academic learning exercise. Some inputs lack strict length bounds, and local credential files are stored in plaintext. Never use real employee records, personal identifiers, or sensitive financial data.

---

## Key Features

- **Authentication & Role Menus:** Admin and employee login flows with local credential setup (`data/admin.txt` or environment variable).
- **Employee Management (`employee`):** Add, view, search, update, and delete employee records.
- **Attendance & Leave (`attendance`, `leave`):** Track attendance and manage employee leave workflows.
- **Payroll & Compensation (`salary`, `loan`):** Manage salary records, generate salary slips, view history, analyze reports/statistics, and handle employee loans and repayments.
- **Workspace & Auditing (`dashboard`, `notice`, `activity`):** View summary dashboards, publish notices, and record system activity logs.
- **File-Based Persistence:** Stores local runtime data under `data/` using relative paths.

---

## Core Concepts & Stack

- **Language & Standard:** C (`C11`) with standard C library headers
- **Architecture:** Modular separation of interface (`.h`) and implementation (`.c`) files with shared utilities (`utils`)
- **Data & Logic:** `struct` definitions, pointers, dynamic/linked structures, file I/O, and interactive CLI menus
- **Build Tooling:** `gcc` (compatible with Linux/macOS shells and Windows terminals)

---

## Project Structure

```text
Payroll-Management-System/
├── include/            # Module header files (*.h)
│   ├── activity.h
│   ├── attendance.h
│   ├── dashboard.h
│   ├── employee.h
│   ├── leave.h
│   ├── login.h
│   ├── loan.h
│   ├── notice.h
│   ├── report.h
│   ├── salary.h
│   └── utils.h
├── src/                # Module source implementations (*.c)
│   ├── main.c
│   ├── activity.c
│   ├── attendance.c
│   ├── dashboard.c
│   ├── employee.c
│   ├── leave.c
│   ├── login.c
│   ├── loan.c
│   ├── notice.c
│   ├── report.c
│   ├── salary.c
│   └── utils.c
├── data/               # Runtime data directory (ignored in Git)
│   └── .gitkeep
├── .gitignore
└── README.md
