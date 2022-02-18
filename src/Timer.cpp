#include <ctime>

class Timer {
private:
    unsigned long startTime;
public:
    void start() {
        startTime = clock();
    }

    unsigned long elapsedTime() {
        return ((unsigned long) clock() - startTime);
    }

};

