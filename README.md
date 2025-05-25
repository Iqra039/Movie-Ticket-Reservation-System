# 🎬 Movie Ticket Reservation System (C++)

This is a simple console-based C++ project that allows users to:
- Add and delete movies
- Book tickets and manage reservations
- Search for movies by name, genre, or showtime
- View reservation history
- Demonstrates use of **pointers**, **file handling**, and **CRUD operations**

---

🔧 Features

- Add and delete movies (Admin only)
- View movie list
- Book tickets (Customer)
- Search movies by name, genre, or time
- View reservation history
- All actions logged in a `history.txt` file
- Uses file handling to store:
  - Movie list (`movies.txt`)
  - Reservations (`reservations.txt`)
  - Action log (`history.txt`)

---


## 👤 User Roles

### Admin
- Password protected (`mrbean`)
- Can add/delete movies
- Can view reservations
- Can view action history

### Customer
- Can view available movies
- Can search movies
- Can book tickets

---

💻 Technologies Used

- C++  
- File Handling (`fstream`)  
- Pointers  
- Console-based UI (no external libraries)

---


## 💻 How to Run

1. Clone or download the repository.
2. Make sure the following files are in the same directory:
   - `main.cpp`
   - `movies.txt`
   - `reservations.txt`
   - `history.txt`
3. Open `main.cpp` in a C++ IDE like CodeBlocks or Dev-C++.
4. Compile and run the program.
5. Choose user type: Admin or Customer.

---


📁 Files

- `MovieTicketReservation.cpp` – Complete source code of the program  
- movies.txt – Stores movie data
- reservations.txt – Stores reservation records
- history.txt – Logs all admin and customer actions
- `README.md` – This file  
- `flowchart.png` – Flowchart image  

---
