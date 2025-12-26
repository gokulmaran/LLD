#include <iostream>
#include <stack>
#include <string>

using namespace std;

/* =========================
   MEMENTO
   ========================= */
class EditorMemento {
private:
    string content;

public:
    EditorMemento(const string& content) : content(content) {}

    string getContent() const {
        return content;
    }
};

/* =========================
   ORIGINATOR
   ========================= */
class TextEditor {
private:
    string content;

public:
    void write(const string& text) {
        content = text;
    }

    EditorMemento save() {
        cout << "[+] Saving state\n";
        return EditorMemento(content);
    }

    void restore(const EditorMemento& memento) {
        content = memento.getContent();
        cout << "[+] Restored previous state\n";
    }

    void show() const {
        cout << "Editor Content: " << content << endl;
    }
};

/* =========================
   CARETAKER
   ========================= */
class History {
private:
    stack<EditorMemento> history;

public:
    void save(const EditorMemento& memento) {
        history.push(memento);
    }

    bool canUndo() const {
        return !history.empty();
    }

    EditorMemento undo() {
        EditorMemento m = history.top();
        history.pop();
        return m;
    }
};

/* =========================
   CLIENT
   ========================= */
int main() {
    cout << "====== Memento Design Pattern ======\n\n";

    TextEditor editor;
    History history;

    editor.write("Hello");
    history.save(editor.save());

    editor.write("Hello World");
    history.save(editor.save());

    editor.write("Hello World!!!");
    editor.show();

    cout << "\nUndo 1\n";
    editor.restore(history.undo());
    editor.show();

    cout << "\nUndo 2\n";
    editor.restore(history.undo());
    editor.show();

    return 0;
}
