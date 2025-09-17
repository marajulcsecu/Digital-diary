# Digital Diary (DD) - A Long-Term Task Tracker

A simple, console-based application to serve as your personal digital diary. Record what you did each day and track your progress over 1000+ days. Perfect for building a habit of daily logging and reflection.

## Features

- **Add Entry**: Log your activities for today or a specific past/future date.
- **View Entries**: Retrieve your logs:
  - By Sequential Day Number (e.g., "Day 1", "Day 365")
  - By Specific Date (format: DD-MM-YYYY)
  - View All entries in a paginated list.
- **Data Persistence**: All your entries are automatically saved to a text file (`diary_entries.txt`) so they are never lost between sessions.

## Requirements

- C++11 or later compiler (g++, clang++, etc.)
- Make (for building)

## Building and Installation

### Build the Application

```bash
# Clone the repository
git clone https://github.com/marajulcsecu/Digital-diary.git
cd Digital-diary

# Build using make
make

# Or build manually
g++ -std=c++11 -Wall -Wextra -O2 main.cpp diary.cpp -o digital_diary
```

### Run the Application

```bash
./digital_diary
```

### Optional System-wide Installation

```bash
# Install to /usr/local/bin (requires sudo)
sudo make install
```

## Usage

When you run the application, you'll see a menu with the following options:

1. **Add Entry**: Create a new diary entry
   - Add for today (uses current date automatically)
   - Add for specific date (enter in DD-MM-YYYY format)
2. **View by Day Number**: View a specific entry by its sequential number (1, 2, 3...)
3. **View by Date**: View an entry by its date (DD-MM-YYYY format)
4. **View All Entries**: Browse all entries with pagination (5 entries per page)
5. **Exit**: Save and close the application

### Example Session

```
========================================
    DIGITAL DIARY - Task Tracker
========================================
1. Add Entry
2. View by Day Number
3. View by Date
4. View All Entries
5. Exit
========================================
Total entries: 2

Enter your choice (1-5): 1
========== ADD NEW ENTRY ==========
1. Add entry for today
2. Add entry for specific date
Enter choice (1-2): 1
Date: 16-09-2025
Enter your diary entry: Started learning about digital diaries and implemented one!
Entry added successfully! (Day 3)
```

## File Format

The diary entries are stored in a simple, human-readable text file (`diary_entries.txt`):

```
DayNo|Date|EntryText
1|17-09-2025|Learned smart pointers in C++.
2|18-09-2025|Started building the Digital Diary project.
3|19-09-2025|Implemented and tested the Digital Diary application successfully.
...
1000|11-06-2028|Completed my graduation!
```

## Features Implemented

- ✅ Console-based menu interface
- ✅ Add entries for current day or specific dates
- ✅ View entries by day number or date
- ✅ View all entries with pagination
- ✅ Data persistence to file
- ✅ Duplicate date prevention
- ✅ Input validation and error handling
- ✅ Auto-incrementing day numbers
- ✅ Human-readable file format

## Technical Details

- **Language**: C++11
- **Build System**: Make
- **Data Storage**: Plain text file with pipe-delimited format
- **Dependencies**: Standard C++ library only (no external dependencies)

## Development

### Build Commands

```bash
# Build the application
make

# Clean build artifacts
make clean

# Build with debug information
g++ -std=c++11 -Wall -Wextra -g main.cpp diary.cpp -o digital_diary
```

### Project Structure

```
Digital-diary/
├── main.cpp          # Application entry point
├── diary.h           # Header file with class definitions
├── diary.cpp         # Implementation of diary functionality
├── Makefile          # Build configuration
├── README.md         # This documentation
├── .gitignore        # Git ignore rules
└── diary_entries.txt # Data file (created automatically)
```
