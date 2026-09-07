#pragma once
#include <vector>
#include <memory>
#include <string>
#include "03_Screen.cpp"
using namespace std;

// Composition: Cinema owns its Screens.
class Cinema {
private:
    string name;
    vector<shared_ptr<Screen>> screens;

public:
    explicit Cinema(string name) : name(name) {}

    void addScreen(int screenNumber) {
        screens.push_back(make_shared<Screen>(screenNumber));
    }

    string getName() const { return name; }
    const vector<shared_ptr<Screen>>& getScreens() const { return screens; }

    shared_ptr<Screen> getScreen(int screenNumber) const {
        for (const auto& screen : screens)
            if (screen->getScreenNumber() == screenNumber) return screen;
        return nullptr;
    }
};
