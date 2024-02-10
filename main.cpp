#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map>
#include "Replacement.hpp"
#include "dependencies/include/nlohmann/json.hpp"

int main() {
    try {
        Replacement r("database.txt", "input.txt");
        std::unordered_set<std::string> db = r.loadNamesDatabase();
        std::string replacedText = r.getReplacedText();
        std::map<std::string, int> freq = r.countOccurencies();

        nlohmann::json objJson;

        objJson["Text"] = replacedText;

        for (auto it = freq.begin(); it != freq.end(); ++it) {
            const std::string& name = it->first;
            int count = it->second;
            objJson["ProperNouns"][name] = count;
        }


        std::ofstream outputFile("output.json");
        outputFile << objJson.dump(4); // Pretty print with 4 spaces of indentation
        outputFile.close();

        std::cout << "JSON file created: output.json" << std::endl;
    } catch(const std::runtime_error& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}