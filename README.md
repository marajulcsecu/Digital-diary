# Digital Diary (DD) - A Long-Term Task Tracker

A simple, console-based application to serve as your personal digital diary. Record what you did each day and track your progress over 1000+ days. Perfect for building a habit of daily logging and reflection.

## Features

- **Add Entry**: Log your activities for today or a specific past/future date.
- **View Entries**: Retrieve your logs:
  - By Sequential Day Number (e.g., "Day 1", "Day 365")
  - By Specific Date (format: DD-MM-YYYY)
  - View All entries in a paginated list.
- **Data Persistence**: All your entries are automatically saved to a text file (`diary_entries.txt`) so they are never lost between sessions.

## File Format

The diary entries are stored in a simple, human-readable text file:
DayNo|Date|EntryText
1|17-09-2025|Learned smart pointers in C++.
2|18-09-2025|Started building the Digital Diary project.
...
1000|11-06-2028|Completed my graduation!
