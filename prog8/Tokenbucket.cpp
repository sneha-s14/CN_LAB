#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int bucketCapacity, tokenRate, numPackets;

    cout << "Enter bucket capacity (number of tokens): ";
    cin >> bucketCapacity;

    cout << "Enter token generation rate (tokens per second): ";
    cin >> tokenRate;

    cout << "Enter the number of packets: ";
    cin >> numPackets;

    int packetSizes[numPackets];

    cout << "Enter the packet sizes: ";
    for (int i = 0; i < numPackets; i++) {
        cin >> packetSizes[i];
    }

    int tokens = 0;
    int sent = 0;

    cout << "\nPacket Size\tTokens Available\tSent\tTokens Remaining\tStatus\n";

    for (int i = 0; i < numPackets; i++) {

        // Generate tokens for this iteration
        tokens = min(tokens + tokenRate, bucketCapacity);

        // Check if packet can be processed
        if (packetSizes[i] <= tokens) {
            tokens -= packetSizes[i];
            sent = packetSizes[i];

            cout << packetSizes[i] << "\t\t"
                 << (tokens + packetSizes[i]) << "\t\t\t"
                 << sent << "\t"
                 << tokens << "\t\t\tAccepted" << endl;
        }
        else {
            sent = 0;

            cout << packetSizes[i] << "\t\t"
                 << tokens << "\t\t\t"
                 << sent << "\t"
                 << tokens << "\t\t\tDropped" << endl;
        }
    }

    return 0;
}
