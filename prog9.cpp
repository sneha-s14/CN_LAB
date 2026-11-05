#include <iostream>
#include <random>
using namespace std;

class RandomEarlyDetection {
private:
    double minThreshold;
    double maxThreshold;
    double maxDropProb;
    int queueSize;
    int currentQueue;

    mt19937 rng{random_device{}()};
    uniform_real_distribution<double> dist{0.0, 1.0};

public:
    RandomEarlyDetection(double min, double max,
                         double prob, int size) {
        minThreshold = min;
        maxThreshold = max;
        maxDropProb = prob;
        queueSize = size;
        currentQueue = 0;
    }

    bool enqueue() {
        if (currentQueue >= queueSize) {
            cout << "Packet dropped (Queue Full)" << endl;
            return false;
        }

        double dropProb = calcDropProb();

        if (dropProb > 0 && shouldDrop(dropProb)) {
            cout << "Packet Dropped (RED)" << endl;
            return false;
        }

        currentQueue++;

        cout << "Packet enqueued. Current queue size: "
             << currentQueue << endl;

        return true;
    }

private:
    double calcDropProb() {
        if (currentQueue < minThreshold)
            return 0.0;

        else if (currentQueue >= maxThreshold)
            return 1.0;

        else
            return maxDropProb *
                   ((currentQueue - minThreshold) /
                   (maxThreshold - minThreshold));
    }

    bool shouldDrop(double prob) {
        return dist(rng) < prob;
    }
};

int main() {
    double min, max, prob;
    int size, n;

    cout << "Enter the minimum threshold: ";
    cin >> min;

    cout << "Enter the maximum threshold: ";
    cin >> max;

    cout << "Enter the maximum drop probability(0-1): ";
    cin >> prob;

    cout << "Enter the queue size: ";
    cin >> size;

    cout << "Enter the number of packets: ";
    cin >> n;

    RandomEarlyDetection red(min, max, prob, size);

    for (int i = 0; i < n; i++) {
        red.enqueue();
    }

    return 0;
}
