#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ================= Component =================

class FileSystemComponent {
public:
    virtual ~FileSystemComponent() {}
    virtual void printContents() const = 0;
};

// ================= Leaf =================

class File : public FileSystemComponent {
    string fileName;

public:
    File(const string& name) : fileName(name) {
        cout << "[DEBUG] File created: " << fileName << endl;
    }

    ~File() {
        cout << "[DEBUG] File deleted: " << fileName << endl;
    }

    void printContents() const override {
        cout << "File name: " << fileName << endl;
    }
};

// ================= Composite =================

class Directory : public FileSystemComponent {
    string directoryName;
    vector<FileSystemComponent*> children;

public:
    Directory(const string& name) : directoryName(name) {
        cout << "[DEBUG] Directory created: " << directoryName << endl;
    }

    ~Directory() {
        cout << "[DEBUG] Deleting Directory: " << directoryName << endl;
        for (auto child : children) {
            delete child;
        }
    }

    void add(FileSystemComponent* component) {
        cout << "[DEBUG] Adding component to " << directoryName << endl;
        children.push_back(component);
    }

    void printContents() const override {
        cout << "Directory Name: " << directoryName << endl;
        for (auto child : children) {
            child->printContents();
        }
    }
};

// ================= Client =================

int main() {
    cout << "======= Composite Design Pattern =======\n";

    File* receipt = new File("receipt.pdf");
    File* invoice = new File("invoice.pdf");
    File* torrentLinks = new File("torrentLinks.txt");
    File* tomCruise = new File("tomCruise.jpg");
    File* dumbAndDumber = new File("DumbAndDumber.mp4");
    File* hangoverI = new File("HangoverI.mp4");

    Directory* moviesDirectory = new Directory("Movies");
    Directory* comedyMovieDirectory = new Directory("ComedyMovies");

    comedyMovieDirectory->add(dumbAndDumber);
    comedyMovieDirectory->add(hangoverI);

    moviesDirectory->add(receipt);
    moviesDirectory->add(invoice);
    moviesDirectory->add(torrentLinks);
    moviesDirectory->add(tomCruise);
    moviesDirectory->add(comedyMovieDirectory);

    moviesDirectory->printContents();

    // ONLY delete root
    delete moviesDirectory;

    return 0;
}
