#include "diary.h"
#include <ctime>
#include <regex>

DigitalDiary::DigitalDiary() {
    loadEntries();
}

void DigitalDiary::run() {
    int choice;
    
    while (true) {
        clearScreen();
        displayMenu();
        
        std::cout << "Enter your choice (1-5): ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number." << std::endl;
            pauseScreen();
            continue;
        }
        std::cin.ignore(); // Clear newline from buffer
        
        switch (choice) {
            case 1:
                addEntry();
                break;
            case 2:
                viewByDay();
                break;
            case 3:
                viewByDate();
                break;
            case 4:
                viewAll();
                break;
            case 5:
                std::cout << "Thank you for using Digital Diary! Goodbye!" << std::endl;
                return;
            default:
                std::cout << "Invalid choice! Please select 1-5." << std::endl;
                pauseScreen();
        }
    }
}

void DigitalDiary::loadEntries() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // File doesn't exist yet, which is fine for first run
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string day_str, date, entry_text;
        
        if (std::getline(ss, day_str, '|') &&
            std::getline(ss, date, '|') &&
            std::getline(ss, entry_text)) {
            
            try {
                int day_number = std::stoi(day_str);
                entries.emplace_back(day_number, date, entry_text);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }
    }
    file.close();
}

void DigitalDiary::saveEntries() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not save to file " << filename << std::endl;
        return;
    }
    
    for (const auto& entry : entries) {
        file << entry.day_number << "|" << entry.date << "|" << entry.entry_text << std::endl;
    }
    file.close();
}

void DigitalDiary::displayMenu() {
    std::cout << "========================================" << std::endl;
    std::cout << "    DIGITAL DIARY - Task Tracker" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Add Entry" << std::endl;
    std::cout << "2. View by Day Number" << std::endl;
    std::cout << "3. View by Date" << std::endl;
    std::cout << "4. View All Entries" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Total entries: " << entries.size() << std::endl;
    std::cout << std::endl;
}

void DigitalDiary::addEntry() {
    clearScreen();
    std::cout << "========== ADD NEW ENTRY ==========" << std::endl;
    std::cout << "1. Add entry for today" << std::endl;
    std::cout << "2. Add entry for specific date" << std::endl;
    std::cout << "Enter choice (1-2): ";
    
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input!" << std::endl;
        pauseScreen();
        return;
    }
    std::cin.ignore();
    
    std::string date;
    if (choice == 1) {
        date = getCurrentDate();
    } else if (choice == 2) {
        std::cout << "Enter date (DD-MM-YYYY): ";
        std::getline(std::cin, date);
        
        if (!isValidDate(date)) {
            std::cout << "Invalid date format! Use DD-MM-YYYY." << std::endl;
            pauseScreen();
            return;
        }
    } else {
        std::cout << "Invalid choice!" << std::endl;
        pauseScreen();
        return;
    }
    
    if (dateExists(date)) {
        std::cout << "Entry for " << date << " already exists!" << std::endl;
        pauseScreen();
        return;
    }
    
    std::cout << "Date: " << date << std::endl;
    std::cout << "Enter your diary entry: ";
    std::string entry_text;
    std::getline(std::cin, entry_text);
    
    if (entry_text.empty()) {
        std::cout << "Entry cannot be empty!" << std::endl;
        pauseScreen();
        return;
    }
    
    int day_number = getNextDayNumber();
    entries.emplace_back(day_number, date, entry_text);
    saveEntries();
    
    std::cout << "Entry added successfully! (Day " << day_number << ")" << std::endl;
    pauseScreen();
}

void DigitalDiary::viewByDay() {
    clearScreen();
    std::cout << "========== VIEW BY DAY NUMBER ==========" << std::endl;
    
    if (entries.empty()) {
        std::cout << "No entries found. Add some entries first!" << std::endl;
        pauseScreen();
        return;
    }
    
    std::cout << "Enter day number (1-" << entries.size() << "): ";
    int day_number;
    if (!(std::cin >> day_number)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input!" << std::endl;
        pauseScreen();
        return;
    }
    std::cin.ignore();
    
    auto it = std::find_if(entries.begin(), entries.end(),
                          [day_number](const DiaryEntry& entry) {
                              return entry.day_number == day_number;
                          });
    
    if (it != entries.end()) {
        std::cout << std::endl;
        std::cout << "Day " << it->day_number << " - " << it->date << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << it->entry_text << std::endl;
    } else {
        std::cout << "No entry found for day " << day_number << std::endl;
    }
    
    pauseScreen();
}

void DigitalDiary::viewByDate() {
    clearScreen();
    std::cout << "========== VIEW BY DATE ==========" << std::endl;
    std::cout << "Enter date (DD-MM-YYYY): ";
    
    std::string date;
    std::getline(std::cin, date);
    
    if (!isValidDate(date)) {
        std::cout << "Invalid date format! Use DD-MM-YYYY." << std::endl;
        pauseScreen();
        return;
    }
    
    auto it = std::find_if(entries.begin(), entries.end(),
                          [&date](const DiaryEntry& entry) {
                              return entry.date == date;
                          });
    
    if (it != entries.end()) {
        std::cout << std::endl;
        std::cout << "Day " << it->day_number << " - " << it->date << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << it->entry_text << std::endl;
    } else {
        std::cout << "No entry found for date " << date << std::endl;
    }
    
    pauseScreen();
}

void DigitalDiary::viewAll() {
    clearScreen();
    std::cout << "========== ALL ENTRIES ==========" << std::endl;
    
    if (entries.empty()) {
        std::cout << "No entries found. Add some entries first!" << std::endl;
        pauseScreen();
        return;
    }
    
    const int entriesPerPage = 5;
    int totalPages = (entries.size() + entriesPerPage - 1) / entriesPerPage;
    int currentPage = 1;
    
    while (true) {
        clearScreen();
        std::cout << "========== ALL ENTRIES (Page " << currentPage << "/" << totalPages << ") ==========" << std::endl;
        
        int start = (currentPage - 1) * entriesPerPage;
        int end = std::min(start + entriesPerPage, (int)entries.size());
        
        for (int i = start; i < end; ++i) {
            const auto& entry = entries[i];
            std::cout << "Day " << entry.day_number << " - " << entry.date << std::endl;
            std::cout << entry.entry_text << std::endl;
            std::cout << "----------------------------------------" << std::endl;
        }
        
        std::cout << std::endl;
        if (totalPages > 1) {
            std::cout << "Navigation: [P]revious, [N]ext, [Q]uit" << std::endl;
            std::cout << "Enter choice: ";
            
            char choice;
            std::cin >> choice;
            std::cin.ignore();
            
            choice = std::tolower(choice);
            
            if (choice == 'q') {
                break;
            } else if (choice == 'n' && currentPage < totalPages) {
                currentPage++;
            } else if (choice == 'p' && currentPage > 1) {
                currentPage--;
            } else if (choice == 'n' && currentPage >= totalPages) {
                std::cout << "Already on last page!" << std::endl;
                pauseScreen();
            } else if (choice == 'p' && currentPage <= 1) {
                std::cout << "Already on first page!" << std::endl;
                pauseScreen();
            }
        } else {
            pauseScreen();
            break;
        }
    }
}

bool DigitalDiary::isValidDate(const std::string& date) {
    std::regex dateRegex(R"(^\d{2}-\d{2}-\d{4}$)");
    if (!std::regex_match(date, dateRegex)) {
        return false;
    }
    
    // Basic validation for month and day ranges
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));
    
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    
    return true;
}

bool DigitalDiary::dateExists(const std::string& date) {
    return std::any_of(entries.begin(), entries.end(),
                      [&date](const DiaryEntry& entry) {
                          return entry.date == date;
                      });
}

std::string DigitalDiary::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << ltm->tm_mday << "-"
       << std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon) << "-"
       << (1900 + ltm->tm_year);
    
    return ss.str();
}

int DigitalDiary::getNextDayNumber() {
    if (entries.empty()) {
        return 1;
    }
    
    int maxDay = 0;
    for (const auto& entry : entries) {
        if (entry.day_number > maxDay) {
            maxDay = entry.day_number;
        }
    }
    
    return maxDay + 1;
}

void DigitalDiary::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void DigitalDiary::pauseScreen() {
    std::cout << "Press Enter to continue...";
    std::cin.get();
}