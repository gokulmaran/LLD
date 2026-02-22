#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// =======================
// Component Interface
// =======================
class FileSystemComponent {
public:
    virtual void printContents() = 0;
    virtual ~FileSystemComponent() {}
};

// =======================
// Leaf - File
// =======================
class File : public FileSystemComponent {
private:
    string fileName;

public:
    File(const string& name) : fileName(name) {}

    void printContents() override {
        cout << "File name: " << fileName << endl;
    }
};

// =======================
// Composite - Directory
// =======================
class Directory : public FileSystemComponent {
private:
    string directoryName;
    vector<FileSystemComponent*> children;

public:
    Directory(const string& name) : directoryName(name) {}

    void add(FileSystemComponent* component) {
        children.push_back(component);
    }

    void remove(FileSystemComponent* component) {
       auto it = std::find(children.begin(), children.end(), component);
        if (it != children.end()) {
            children.erase(it);
        }
    }

    void printContents() override {
        cout << "Directory Name: " << directoryName << endl;
        for (auto child : children) {
            child->printContents();
        }
    }

    // Destructor: delete all children
    ~Directory() {
        for (auto child : children) {
            delete child;
        }
    }
};

// =======================
// Client Code
// =======================
int main() {
    cout << "======= Composite Design Pattern =======" << endl;

    // Create files
    FileSystemComponent* receipt = new File("receipt.pdf");
    FileSystemComponent* invoice = new File("invoice.pdf");
    FileSystemComponent* torrentLinks = new File("torrentLinks.txt");
    FileSystemComponent* tomCruise = new File("tomCruise.jpg");
    FileSystemComponent* dumbAndDumber = new File("DumbAndDumber.mp4");
    FileSystemComponent* hangoverI = new File("HangoverI.mp4");

    // Create directories
    Directory* moviesDirectory = new Directory("Movies");
    Directory* comedyMovieDirectory = new Directory("ComedyMovies");

    // Build directory structure
    moviesDirectory->add(receipt);
    moviesDirectory->add(invoice);
    moviesDirectory->add(torrentLinks);
    moviesDirectory->add(tomCruise);
    moviesDirectory->add(comedyMovieDirectory);

    comedyMovieDirectory->add(dumbAndDumber);
    comedyMovieDirectory->add(hangoverI);

    // Print full structure
    moviesDirectory->printContents();

    // Clean up (recursively deletes all children)
    delete moviesDirectory;

    return 0;
}
