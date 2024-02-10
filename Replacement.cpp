#include "Replacement.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>

Replacement::Replacement(const std::string& database, const std::string& input)
    : _database(database)
    , _input(input)
{}

std::string Replacement::loadText() const
{
    std::ifstream file(_input);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: input.txt");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    file.close();
    return text;
}

std::unordered_set<std::string> Replacement::loadNamesDatabase() const
{
    std::ifstream file(_database);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: database.txt");
    }

    std::unordered_set<std::string> db;
    std::string name;

    while (std::getline(file >> std::ws, name, ',')) {
        name = std::regex_replace(name, std::regex("^\\s*\"*|\"*\\s*$"), "");
        db.insert(name);
    }

    file.close();
    return db;
}

std::vector<std::string> Replacement::findNames() const
{
    std::vector<std::string> names;
    std::unordered_set<std::string> db = loadNamesDatabase();
    std::string text = loadText();
    
    for (const std::string& name : db) {
        std::regex nameRegex("\\b" + name + "\\b");
        auto begin = std::sregex_iterator(text.begin(), text.end(), nameRegex);
        auto end = std::sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            names.push_back(it->str());
        }
    }

    return names;
}

std::string Replacement::replaceNames() const
{
    std::unordered_set<std::string> db = loadNamesDatabase();
    std::string text = loadText();

    for (const std::string& name : db) {
        std::regex nameRegex("\\b" + name + "\\b");
        text = std::regex_replace(text, nameRegex, "X");
    }

    return text;
}

std::map<std::string, int> Replacement::countOccurencies() const
{
    std::vector<std::string> names = findNames();
    std::map<std::string, int> freq;

    for (const std::string& name : names) {
        ++freq[name];
    }

    return freq;
}

std::string Replacement::getReplacedText() const
{
    std::string newText = replaceNames();
    return newText;
}