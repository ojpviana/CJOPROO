#include "WordManager.h"
#include "raylib.h"
#include <fstream>


WordManager::WordManager(float limit) : initialTimeLimit(limit), timeLimit(limit) {
    std::random_device rd;
    rng.seed(rd()); 
    LoadWords();
    Reset();
}

void WordManager::LoadWords() {
    words.clear(); 

    std::ifstream file("assets/words.txt"); 
    if (file.is_open()) {
        std::string word;
        while (std::getline(file, word)) { 

            std::transform(word.begin(), word.end(), word.begin(), ::toupper);
            words.push_back(word); 
        }
        file.close();
        TraceLog(LOG_INFO, TextFormat("WORD_MANAGER: %d words loaded from words.txt", words.size()));
    } else {
        TraceLog(LOG_ERROR, "WORD_MANAGER: Could not open words.txt file! Using default words.");
    
        words = {
            "DRAGAO", "FOGO", "ASAS", "GUARDA", "TESOURO",
            "CAVERNA", "MITO", "LENDA", "GUERREIRO", "MAGIA",
            "ESCAMA", "GARRAS", "CHAMA", "DESTRUIDOR", "VALENTE",
            "ENIGMA", "CRIATURA", "ANCIENT", "PROTEC", "DEIXA"
        };
    }

    std::shuffle(words.begin(), words.end(), rng);
}


void WordManager::Reset() {
    if (words.empty()) {
        LoadWords(); 
        TraceLog(LOG_INFO, "All words used. Re-shuffling.");
    }
    
    currentWord = words[0]; 
    words.erase(words.begin()); 
    
    typedText = ""; 
    wordTimer = initialTimeLimit; 
}


void WordManager::Update(float deltaTime) {
    wordTimer -= deltaTime;
    if (wordTimer < 0) wordTimer = 0; 
}


void WordManager::HandleInput(int key) {

    if (std::isalpha(key) || std::isspace(key)) { 

        typedText += (char)std::toupper(key); 
    }
}

void WordManager::HandleBackspace() {
    if (typedText.length() > 0) {
        typedText.pop_back();
    }
}


bool WordManager::IsTypedPrefixCorrect() const {
    if (typedText.length() > currentWord.length()) {
        return false; 
    }
    return currentWord.rfind(typedText, 0) == 0;
}

void WordManager::SetInitialTime(float time) {
    initialTimeLimit = time;
}