#include <iostream>
#include <string>
using namespace std;

/* ===================== SUBJECT INTERFACE ===================== */

class Image {
public:
    virtual void display() = 0;
    virtual ~Image() = default;
};

/* ===================== REAL OBJECT ===================== */

class RealImage : public Image {
    string filename;

public:
    RealImage(const string& name) : filename(name) {
        cout << "Loading image from disk: " << filename << endl;
    }

    void display() override {
        cout << "Displaying image: " << filename << endl;
    }
};

/* ===================== PROXY ===================== */

class ProxyImage : public Image {
    RealImage* realImage;
    string filename;

public:
    ProxyImage(const string& name)
        : realImage(nullptr), filename(name) {}

    void display() override {
        if (realImage == nullptr) {
            // Lazy initialization
            realImage = new RealImage(filename);
        }
        realImage->display();
    }

    ~ProxyImage() {
        delete realImage;
    }
};

/* ===================== CLIENT ===================== */

int main() {
    Image* image = new ProxyImage("photo.png");

    cout << "First call:\n";
    image->display();   // Image loaded from disk

    cout << "\nSecond call:\n";
    image->display();   // Cached image used

    delete image;
    return 0;
}
