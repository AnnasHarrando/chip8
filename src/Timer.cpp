#include <ctime>

class Timer {
private:
    clock_t startTime;
public:
    void start() {
        startTime = clock();
    }

    float elapsedTime() {
        return ((float)(clock() - startTime))/CLOCKS_PER_SEC;
    }

};

