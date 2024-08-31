#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <string>
#include <unordered_map>
#include <cctype>
#include <array>

struct SoundexMapping {
    char letter;
    char code;
};

struct Soundex {
    static std::string generate(const std::string& name);

private:
    static char getSoundexCode(char c);
    static bool isVowelOrIgnored(char c);
    static std::string padWithZeroes(const std::string& soundex, std::size_t targetLength = 4);
};

// Utility function for initializing the Soundex map
std::unordered_map<char, char> initializeSoundexMap();

#endif // SOUNDEX_H
