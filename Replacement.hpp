#ifndef REPLACEMENT_HPP
#define REPLACEMENT_HPP

#include <vector>
#include <string>
#include <unordered_set>
#include <map>

class Replacement 
{
public:
    Replacement(const std::string&, const std::string&);
    std::string loadText() const;
    std::unordered_set<std::string> loadNamesDatabase() const;
    std::vector<std::string> findNames() const;
    std::string replaceNames() const;
    std::map<std::string, int> countOccurencies() const;
    std::string getReplacedText() const;

private:
    std::string _database;
    std::string _input;
};

#endif // REPLACEMENT_HPP