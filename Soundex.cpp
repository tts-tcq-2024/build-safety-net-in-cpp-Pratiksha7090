#include "Soundex.h"

const SoundexMap Soundex::mapping = {{
    {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
    {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'},
    {'Q', '2'}, {'S', '2'}, {'X', '2'}, {'Z', '2'},
    {'D', '3'}, {'T', '3'},
    {'L', '4'},
    {'M', '5'}, {'N', '5'},
    {'R', '6'}
}};

char SoundexUtils::getSoundexCode(char c) {
    c = std::toupper(c);
    auto it = Soundex::mapping.find(c);
    if (it != Soundex::mapping.end()) {
        return it->second;
    }
    return '0'; // For A, E, I, O, U, H, W, Y
}

bool SoundexUtils::isVowelOrIgnored(char c) {
    static const std::string vowelsAndIgnored = "AEIOUHWY";
    return vowelsAndIgnored.find(std::toupper(c)) != std::string::npos;
}

std::string SoundexUtils::padWithZeroes(const std::string& soundex, std::size_t targetLength) {
    if (soundex.length() >= targetLength) return soundex;
    return soundex + std::string(targetLength - soundex.length(), '0');
}

std::string Soundex::generate(const std::string& name) {
    if (name.empty()) return "";

    std::string soundex(1, std::toupper(name[0]));
    char prevCode = SoundexUtils::getSoundexCode(name[0]);

    for (size_t i = 1; i < name.length() && soundex.length() < 4; ++i) {
        char currentChar = std::toupper(name[i]);

        // Skip 'H' and 'W' if they are not the first letter
        if (currentChar == 'H' || currentChar == 'W') {
            continue;
        }

        char code = SoundexUtils::getSoundexCode(currentChar);

        if (code != '0' && code != prevCode) {
            soundex += code;
            prevCode = code;
        }
    }

    return SoundexUtils::padWithZeroes(soundex, 4);
}
