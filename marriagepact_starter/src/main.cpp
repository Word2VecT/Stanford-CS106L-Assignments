/* 
Assignment 2: Marriage Pact

This assignment asks you to discover your one true love using containers and pointers.
There are two parts: implement get_applicants and find_matches.

Submit to Paperless by 11:59pm on 2/1/2024.
*/

#include <__config>
#include <fstream>
#include <iostream>
#include <ostream>
#include <queue>

#include <random>

#include <set>
#include <string>

#include <unordered_set>


std::set<std::string> get_applicants(const std::string& filename) {
    // TODO: Implement this function. Feel free to change std::set to std::unordered_set if you wish!
    std::set<std::string> applicants;
    std::ifstream students(filename);
    std::string line;
    while (std::getline(students, line)) {
        applicants.insert(line);
        std::cout << line << std::endl;
    }
    return applicants;
}

std::queue<const std::string*> find_matches(std::set<std::string> &students) {
    // TODO: Implement this function.
    std::queue<const std::string*> matches;

    for (const auto &student : students) {
        if (student.front() == 'B') {
            if (student.find(" P") != std::string::npos) {
              matches.push(&student);
            }
        }
    }

    return matches;
}



int main() {
    // Your code goes here. Don't forget to print your true love!
    auto applicants = get_applicants("students.txt");
    auto matches = find_matches(applicants);

    std::random_device rdm;
    std::mt19937 mt_rand(rdm());
    std::uniform_int_distribution<int> dist(1, static_cast<int>(matches.size()));

    int random_number = dist(mt_rand);
    std::cout << std::endl;
    while (random_number != 0) {
        random_number--;
        std::cout << *matches.front() << std::endl;
        matches.pop();
    }

    return 0;
}