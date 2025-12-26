#include <iostream>
#include <unordered_map>
using namespace std;

/* =========================
   Flyweight Interface
   ========================= */
class Character {
public:
    virtual void display(int row, int col) = 0;
    virtual ~Character() = default;
};

/* =========================
   Concrete Flyweight
   ========================= */
class ConcreteCharacter : public Character {
private:
    // Intrinsic (shared) state
    char symbol;
    string font;
    int size;

public:
    ConcreteCharacter(char c, const string& f, int s)
        : symbol(c), font(f), size(s) {}

    void display(int row, int col) override {
        cout << "Character '" << symbol
             << "' [Font=" << font
             << ", Size=" << size
             << "] at (" << row << ", " << col << ")\n";
    }
};

/* =========================
   Flyweight Factory
   ========================= */
class CharacterFactory {
private:
    static unordered_map<string, Character*> characterCache;

public:
    static Character* getCharacter(char c, const string& font, int size) {
        string key = string(1, c) + "_" + font + "_" + to_string(size);

        // Reuse flyweight if exists
        if (characterCache.find(key) != characterCache.end()) {
            return characterCache[key];
        }

        // Create new flyweight
        Character* character = new ConcreteCharacter(c, font, size);
        characterCache[key] = character;
        return character;
    }

    static int totalCharacters() {
        return characterCache.size();
    }

    // Cleanup all flyweights
    static void clear() {
        for (auto& pair : characterCache) {
            delete pair.second;
        }
        characterCache.clear();
    }
};

// Static member initialization
unordered_map<string, Character*> CharacterFactory::characterCache;

/* =========================
   Client Code
   ========================= */
int main() {
    cout << "====== Flyweight Pattern: Word Processor ======\n";

    Character* c1 = CharacterFactory::getCharacter('A', "Arial", 12);
    c1->display(1, 1);

    Character* c2 = CharacterFactory::getCharacter('A', "Arial", 12);
    c2->display(1, 2);

    Character* c3 = CharacterFactory::getCharacter('B', "Arial", 12);
    c3->display(1, 3);

    Character* c4 = CharacterFactory::getCharacter('A', "TimesNewRoman", 14);
    c4->display(2, 1);

    cout << "\nTotal unique character objects created: "
         << CharacterFactory::totalCharacters() << endl;

    // Cleanup memory
    CharacterFactory::clear();

    return 0;
}
