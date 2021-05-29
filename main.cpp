#include<iostream>
#include<vector>
#include<sstream>
#include<chrono>
#include <stdlib.h>
//#include <boost\tokenizer.hpp>
using namespace std;
#include "msattr.cpp"


/*

struct mapToArray{
	unsigned int PCE:5;
	unsigned int CLR:1;
	unsigned int MAP:5;
	unsigned int pad:21;
};
struct mapToTable{
	unsigned int PCE:5;
	unsigned int CLR:1;
	unsigned int MAP:7;
	unsigned int pad:19;
};
*/
struct fenin{
	string instr;
	u_lol expect[7];
};

void loadfens(vector<fenin> &lfns){
	//ifstream file_("C:\\t\\t\\perftsuite.epd");
    ifstream file_("/home/mxlinux/Documents/perfts.txt");
	//ifstream file_("C:\\t\\t\\slow.txt");
	//ifstream file_("C:\\t\\t\\perftsuite.epd");
	fenin lfenin;
    //cout << "-----------"<<flush;
	string line,l1,l2;
	stringstream ss,ss2;
	vector<string> vstr;
	while(getline(file_, line)){
		ss<<line;
		int c=0;
		while(getline(ss,l1,';')){
			if(c>0){
				ss2<<l1;
				while(getline(ss2,l2,' ')){
					if(l2[0]>='0' && l2[0]<='9'){
					lfenin.expect[c-1]=atoll(l2.c_str());
					break;
					}
				}
				//getline(ss2,l2,' ');
				//l2="";
				//getline(ss2,l2,' ');
				ss2.clear();
			}else lfenin.instr=l1;
			c++;
		}
		lfns.push_back(lfenin);
		ss.clear();
	}
}

int main() {
vector<fenin> lfns;
loadfens(lfns);
	PGNLoader pgnl;
    //string str{"C:\\t\\p\\1.pgn"};
	msatr msl;
	//msl.dbgptr();
	msl.initb();
	//msl.dbgptr();
	//msl.moves(msl.wpieces,BLACK);
	//msl.dbgptr();
	//"8/1p1p4/5k2/8/2K5/8/4P1P1/8 w - - 0 1 "
	//moveCPiece lmv{0,0,0,1,1,1,1,0,0,0,0,0};"k4r2/1R4pb/1pQp1n1p/3P4/5p1P/3P2P1/r1q1R2K/8 w - - bm Rxb6+ "
	u_lol cumul[7]={};
	auto start =std::chrono::system_clock::now();
	bool isc=false;


	for(size_t ox=0;ox<lfns.size();ox++){// lfns[ox].instr"r3k2r/1bp2pP1/5n2/1P1Q4/1pPq4/5N2/1B1P2p1/R3K2R b KQkq c3 0 1"
	//3r1k2/1ppPR1n1/p2pRrP1/3P3p/5p1N/5K2/P1P2P2/8 b - - 0 1
	//"r4k2/1ppPR1n1/p2pRrP1/3P3p/5p1N/5K2/P1P2P2/8 w - - 0 1 ""1k6/5RP1/1P6/1K6/6r1/8/8/8 w - - bm Ka5 Kc5 b7 "
	moveCPiece lmv=msl.fenParser(lfns[ox].instr);
	if(lmv.GIV_CHK)isc=true;
	for(int op=5;op<6;op++){
		//msl.printt();
		if(lmv.ATT_SID==0)msl.moves<WHITE,BLACK>(lmv,  op,isc);
		else msl.moves<BLACK,WHITE>(lmv,  op,isc);
	cout<<"\nno : "<<ox << "\n";
	cout << lfns[ox].instr << "\n";
	for (int x1=0;x1<7;x1++) {
		cout<< dpthcntr[x1] <<" ";
		cumul[x1]+=dpthcntr[x1];
		//dpthcntr[x1]=0;
	}
	cout << "\n";



	for (int x1=0;x1<7;x1++) {
		cout<< chckcnta[x1] <<" ";
		chckcnta[x1]=0;
	}
	auto end = std::chrono::system_clock::now();
	 chrono::duration<double> elapsed_seconds = end-start;
	 time_t end_time = std::chrono::system_clock::to_time_t(end);
	 cout << "\n";
	 for (int x1=0;x1<7;x1++) {
		 cout<< (long double)cumul[x1]/(long double)elapsed_seconds.count() <<" ";
	 }
	 cout  << " \npush " << pushpopcntr << " -- false p " <<falsep <<" - - " << ((double)falsep)/((double)dpthcntr[0])<<" _ " <<((double)falsea)/((double)dpthcntr[0])<<"\n";
	 pushpopcntr=0;falsep=0;falsea=0;
cout << "\n";
	 for (int x1=0;x1<5;x1++) {
		 cout<< lfns[ox].expect[4-x1] <<" ";
		 dpthcntr[x1]=0;
	 }
	 //if(dpthcntr[0]!=lfns[ox].expect[5]){cout <<"--------------------------panic----------------------";}
	}
	cout << "\n";
	//msl.printt();
	cout <<flush<< "\n";
	//cout<< hashw << " "<<hashb << "\n";
	//cout<< xashw << " "<<xashb << "\n";
	//hashw=0;hashb=0;
	//xashw=0;xashb=0;
	//msl.emptyHash();
	}//<=================================== pgn loop

	/*pgnl.loadPGN(str);


	int x=0;
	for(auto b:pgnl.gmv){
		x++;
		cout << "\n";
		for (int x=0;x<7;x++) {
			cout<< dpthcntr[x] <<" ";
			dpthcntr[x]=0;
		}
		cout << "\n";
		for (int x1=0;x1<7;x1++) {
			cout<< chckcnta[x1] <<" ";
		}
		cout << "\n";
		cout<< "chechs "<< chckcntr << " \npush" << pushpopcntr <<"cntr "<<dbgcntr << " "<< x << " --------------------------\n";
		dbgcntr=0;
		pushpopcntr=0;
		chckcntr=0;
		msl.makeMoveFromFile(b);
cerr << x << " ";
		//msl.dbgptrmoves();
	   // msl.moves(msl.bpieces,BLACK,WHITE);
		msl.dbgptrmoves();
		cout << flush;
	}*/

	cout << "\nnot catched chcks : \n"<<    "\n";
	return 0;
}

