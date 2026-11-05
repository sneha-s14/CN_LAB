#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int bucketCapacity, outputRate, numPackets;

    cout << "Enter bucket capacity: ";
    cin >> bucketCapacity;

    cout << "Enter output rate (packets per second): ";
    cin >> outputRate;

    cout << "Enter the number of packets: ";
    cin >> numPackets;

    int packetSizes[numPackets];

    cout << "Enter the packet sizes: ";
    for (int i = 0; i < numPackets; i++) {
        cin >> packetSizes[i];
    }

    int currentBucketSize = 0;

    cout << "\nPacket Size\tBucket Size\tSent\tRemaining\tStatus\n";

    for (int i = 0; i < numPackets; i++) {

        if (currentBucketSize + packetSizes[i] <= bucketCapacity) {
            currentBucketSize += packetSizes[i];

            cout << packetSizes[i] << "\t\t"
                 << currentBucketSize << "\t\t"
                 << min(outputRate, currentBucketSize) << "\t\t"
                 << max(0, currentBucketSize - outputRate)
                 << "\t\tAccepted" << endl;
        }
        else {
            cout << packetSizes[i] << "\t\t"
                 << currentBucketSize << "\t\t"
                 << min(outputRate, currentBucketSize) << "\t\t"
                 << max(0, currentBucketSize - outputRate)
                 << "\t\tDropped" << endl;
        }

        currentBucketSize = max(0, currentBucketSize - outputRate);
    }

    return 0;
}
