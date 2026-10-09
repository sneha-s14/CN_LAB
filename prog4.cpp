#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<bits/stdc++.h>
#include<ctime>

using namespace std;

struct Frame{
	int SeqNo;
	string data;
};

int main(){
	string message;
	int chunksize;
	vector<Frame> frames;
	cout<<"Enter the message to be transmitted:";
	getline(cin, message);
	cout<<"Enter the frame chunk size:";
	cin>>chunksize;
	int msgLen=message.length();
	int seq=0;
	for(int i=0;i<msgLen;i+=chunksize){
	    Frame f;
	    f.SeqNo=seq++;
	    f.data=message.substr(i,chunksize);
	    frames.push_back(f);
	}
	
	srand(static_cast<unsigned int>(time(0)));
	for(size_t i=frames.size()-1;i>0;--i){
		size_t j=rand()%(i+1);
		swap(frames[i], frames[j]);
	}
	cout<<"\n---Frames Received Out of Order at Receiver---"<<endl;
	cout<<"Seq No\tData"<<endl;
	for(const auto& f:frames){
		cout<<f.SeqNo<<"\t"<<f.data<<endl;
	}
	int n=frames.size();
	for(int i=0;i<n-1;++i){
		for(int j=0;j<n-i-1;++j){
			if(frames[j].SeqNo>frames[j+1].SeqNo){
				swap(frames[j],frames[j+1]);
			}
		}
	}
	cout<<"\n---Frames After Applying Sorting Technique---"<<endl;
	cout<<"Seq No\t Data"<<endl;
	for(const auto& f:frames){
		cout<<f.SeqNo<<"\t"<<f.data<<endl;
	}
	cout<<"\nReconstructed Message:";
	for(const auto& f:frames){
		cout<<f.data;
	}
	cout<<endl;
	return 0;
}
