#include "gtest/gtest.h"
#include "Soundex.h"

class SoundexTest : public ::testing::Test {
protected:
    Soundex soundex;
};

TEST_F(SoundexTest, RetainsFirstLetterOfOneLetterWord) {
    ASSERT_EQ(soundex.generate("A"), "A000");
}

TEST_F(SoundexTest, PadsWithZeroesToEnsureThreeDigits) {
    ASSERT_EQ(soundex.generate("I"), "I000");
}

TEST_F(SoundexTest, ReplacesConsonantsWithAppropriateDigits) {
    ASSERT_EQ(soundex.generate("Ab"), "A100");
    ASSERT_EQ(soundex.generate("Ac"), "A200");
}

TEST_F(SoundexTest, IgnoresVowelsAndCertainLetters) {
    ASSERT_EQ(soundex.generate("Aaeiouhywb"), "A100");
}

TEST_F(SoundexTest, CombinesDuplicateEncodings) {
    ASSERT_EQ(soundex.generate("Abfcgk"), "A112");
}

TEST_F(SoundexTest, HandlesConsonantsWithHAndWCorrectly) {
    ASSERT_EQ(soundex.generate("Ashcraft"), "A226");  // 'sh' should combine
    ASSERT_EQ(soundex.generate("Pfister"), "P236");   // 'Pf' should not combine
}

TEST_F(SoundexTest, DropsHAndWCorrectlyWhenNotFirstLetter) {
    ASSERT_EQ(soundex.generate("Thompson"), "T512");
    ASSERT_EQ(soundex.generate("Washington"), "W252");
}

TEST_F(SoundexTest, HandlesEmptyInput) {
    ASSERT_EQ(soundex.generate(""), "");
}
