#include "Soundex.h"
#include <algorithm>

const SoundexMap Soundex::mapping = {
    {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
    {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'},
    {'Q', '2'}, {'S', '2'}, {'X', '2'}, {'Z', '2'},
    {'D', '3'}, {'T', '3'},
    {'L', '4'},
    {'M', '5'}, {'N', '5'},
    {'R', '6'}
};

char SoundexUtils::getSoundexCode(char c) {
    c = std::toupper(c);
    auto it = Soundex::mapping.find(c);
    if (it != Soundex::mapping.end()) {
        return it->second;
    }
    return '0'; // For A, E, I, O, U, H, W, Y
}

std::string SoundexUtils::padWithZeroes(const std::string& soundex, std::size_t targetLength) {
    if (soundex.length() >= targetLength) return soundex;
    return soundex + std::string(targetLength - soundex.length(), '0');
}

bool SoundexUtils::isVowelOrIgnored(char c) {
    static const std::string vowelsAndIgnored = "AEIOUHWY";
    return vowelsAndIgnored.find(std::toupper(c)) != std::string::npos;
}

std::string Soundex::generate(const std::string& name) {
    if (name.empty()) return "";

    std::string soundex = initializeSoundex(name);
    processNameCharacters(name, soundex);

    return SoundexUtils::padWithZeroes(soundex, 4);
}

std::string Soundex::initializeSoundex(const std::string& name) {
    return std::string(1, std::toupper(name[0]));
}
void Soundex::processCharacter(std::string& soundex, char currentChar, char& prevCode) {
    if (shouldProcessCharacter(currentChar)) {
        addCharacterToSoundex(soundex, currentChar, prevCode);
    }
}

void Soundex::processNameCharacters(const std::string& name, std::string& soundex) {
    char prevCode = SoundexUtils::getSoundexCode(name[0]);

    for (size_t i = 1; i < name.length() && soundex.length() < 4; ++i) {
        char currentChar = std::toupper(name[i]);
        processCharacter(soundex, currentChar, prevCode);
    }
}

bool Soundex::shouldProcessCharacter(char c) {
    return !SoundexUtils::isVowelOrIgnored(c);
}

void Soundex::addCharacterToSoundex(std::string& soundex, char currentChar, char& prevCode) {
    char code = SoundexUtils::getSoundexCode(currentChar);
    soundex += code;
    prevCode = code;
}

bool Soundex::shouldSkipCharacter(char c) {
    return (c == 'H' || c == 'W');
}

bool Soundex::isValidNewCode(char currentChar, char prevCode) {
    char code = SoundexUtils::getSoundexCode(currentChar);
    return (code != '0' && code != prevCode);
}
