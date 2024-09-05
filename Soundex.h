#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <string>
#include <unordered_map>
#include <cctype>

using SoundexMap = std::unordered_map<char, char>;

struct Soundex {
    static std::string generate(const std::string& name);

private:
    static const SoundexMap mapping;

    // Helper methods for SRP
    static std::string initializeSoundex(const std::string& name);
    static void processNameCharacters(const std::string& name, std::string& soundex);
    
    static bool shouldProcessCharacter(char currentChar, char prevCode);
    static void addCharacterToSoundex(std::string& soundex, char currentChar, char& prevCode);

    static bool shouldSkipCharacter(char c);
    static bool isValidNewCode(char currentChar, char prevCode);
};

struct SoundexUtils {
    static char getSoundexCode(char c);
    static bool isVowelOrIgnored(char c);
    static std::string padWithZeroes(const std::string& soundex, std::size_t targetLength = 4);
};

#endif // SOUNDEX_H
