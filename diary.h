#ifndef DIARY_H
#define DIARY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

struct DiaryEntry {
    int day_number;
    std::string date;
    std::string entry_text;
    
    DiaryEntry(int day_num, const std::string& entry_date, const std::string& text)
        : day_number(day_num), date(entry_date), entry_text(text) {}
};

class DigitalDiary {
private:
    std::vector<DiaryEntry> entries;
    const std::string filename = "diary_entries.txt";
    
public:
    DigitalDiary();
    void run();
    
private:
    void loadEntries();
    void saveEntries();
    void displayMenu();
    void addEntry();
    void viewByDay();
    void viewByDate();
    void viewAll();
    
    bool isValidDate(const std::string& date);
    bool dateExists(const std::string& date);
    std::string getCurrentDate();
    int getNextDayNumber();
    void clearScreen();
    void pauseScreen();
};

#endif // DIARY_H