#ifndef WORD_MANAGER_H
#define WORD_MANAGER_H


#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype> 

const float WORD_TIME_LIMIT = 5.0f; 

class WordManager {
private:
    std::vector<std::string> words;
    std::string currentWord;
    std::string typedText;
    float initialTimeLimit;
    float timeLimit;
    float wordTimer;
    
    std::mt19937 rng;

    void LoadWords();

public:
    WordManager(float limit = WORD_TIME_LIMIT); 
    void SetInitialTime(float time);
    void Reset();
    void Update(float deltaTime);
    void HandleInput(int key);
    void HandleBackspace();

    bool IsTimeUp() const { return wordTimer <= 0; }
    bool IsWordCorrect() const { return typedText == currentWord; }
    bool IsTypedPrefixCorrect() const;

    const std::string& GetCurrentWord() const { return currentWord; }
    const std::string& GetTypedText() const { return typedText; }
    float GetWordTimer() const { return wordTimer; }
};

#endif 