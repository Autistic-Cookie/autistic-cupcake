// reading a text file
#include <iostream>
#include <fstream>
#include <string>
//#include <string_view>
#include <vector>
#include "msattr.h"
using namespace std;


//void convstr(string& ,gmoves & );
//#####################################################################################################
//void parse(string &in,vector<vector<string>> & vs);

bool convstr(string& is,gmoves & imap){
#define tconv(xp,xr) ((static_cast<unsigned int>(xp)-97) + ((7-(static_cast<unsigned int>(xr)-49))*10))+21
#define smapp(cq,cw,ce,cr,frf,frr,tof,tor) imap.w.MAP=tconv(cq,cw);\
    imap.isch=ce;\
    imap.istake=cr;\
    imap.FR_r=frr;\
    imap.FR_f=frf;\
    imap.TO_r=tor;\
    imap.TO_f=tof;\
    return true;

    char lc=is[0];
    switch(lc){
    case 'R':imap.w.PCE=ROOK; break;
    case 'N':imap.w.PCE=KNIGHT;break;
    case 'B':imap.w.PCE=BISHOP;break;
    case 'Q':imap.w.PCE=QUEEN;break;
    case 'K':imap.w.PCE=C2_KING;break;
    default :imap.w.PCE=V_PAWN;break;
    }
    if(is[is.size()-1]=='#')is[is.size()-1]='+';
    if(is.size()==2){//pawn move only "yy"
	smapp(lc,is[1],0,0,EMPTY,EMPTY,lc,is[1])
    }
    else if(is.size()==3){ // yyy
	char lc2=is[1],lc3=is[2];
	if('A' <= lc && lc<='Z' ){ // "Yyy"
	    if('a' <= lc2 && lc2 <= 'h' && '1' <= lc3 && lc3<='8'){ // Big move only
		smapp(lc2,lc3,0,0,EMPTY,EMPTY,lc2,lc3)
	    }
	    else cout <<"=== "<<is << "\nbug? g787g3898y8g\n";
	}else if('a' <= lc && lc <= 'h' ){ //pawn chess
	    if(lc3=='+'){ // "yy+"
		smapp(lc,lc2,1,0,EMPTY,EMPTY,lc,lc2)
	    }
	}
    }
    else if(is.size()==4){ // yyyy
	char lc2=is[1],lc3=is[2],lc4=is[3];
	if(lc2=='x'){ // yxyy
	    if('A' <= lc && lc<='Z' ){//big pce take Yxyy
		if('a' <= lc3 && lc3 <= 'h' && '1' <= lc4 && lc4<='8'){
		    smapp(lc3,lc4,0,1,EMPTY,EMPTY,lc3,lc4)
		}
		else cout << "\nbug? gkjsrg022dg\n";
	    }else if('a' <= lc && lc<='h' ){//pawn take yxyy
		if('a' <= lc3 && lc3 <= 'h' && '1' <= lc4 && lc4<='8'){
		    smapp(lc3,lc4,0,1,lc,EMPTY,lc3,lc4)
		}
		else cout << "\nbug? gkjsrg022dg\n";
	    }

	        /*{
		smapp(lc3,lc4,0,1,255)
	    }*/
	}else if(lc4=='+'){// yyy+
	    if('A' <= lc && lc<='Z' ){ //Yyy+
		if('a' <= lc2 && lc2 <= 'h' && '1' <= lc3 && lc3<='8'){//big pce chess
		    smapp(lc2,lc3,1,0,EMPTY,EMPTY,lc2,lc3)
		}
		else cout<< "==== " <<is << "\nbug? g787g3898y8g\n";
	    }else{//pawn chess yyy+
		smapp(lc2,lc3,1,0,lc,EMPTY,lc2,lc3)
	    }
	}else if('0'<=lc2 && lc2<='8'){//move FROM rank yyyy
	    if('A' <= lc && lc<='Z' ){//Y[1-8]yy
		if('a' <= lc3 && lc3 <= 'h' && '1' <= lc4 && lc4<='8'){
		    smapp(lc3,lc4,0,0,EMPTY,lc2,lc3,lc4)
		}
		else cout << "\nbug? g3qvvx6798y8g\n";
	    }else if (lc3=='='){
		switch(lc4){
		case 'R':imap.w.PROM=ROOK; break;
		case 'N':imap.w.PROM=KNIGHT;break;
		case 'B':imap.w.PROM=BISHOP;break;
		case 'Q':imap.w.PROM=QUEEN;break;
		}
		smapp(lc,lc2,0,0,EMPTY,EMPTY,lc,lc2)
		//cout<< "\npossible? tyu7548ghfjd " <<is << "---\n";
	    }
	}else if('a'<=lc2 && lc2<='h'){// move FROM file//y[a-h]yy
	    if('A' <= lc && lc<='Z' ){//Y[a-h]yy
		if('a' <= lc3 && lc3 <= 'h' && '1' <= lc4 && lc4<='8'){
		    smapp(lc3,lc4,0,0,lc2,EMPTY,lc3,lc4)
		}
		//else cout << "\nbug? g3qvvx6798y8g\n";
	    }else{
		smapp(lc2,lc3,1,0,EMPTY,lc2,lc3,lc4)
		//cout<< "\npossible? tsu678968vd\n";cout <<"-- "<<is << "\n-----------------?----------------\n";
	    }
	}
    }else if(is.size()==5){
	char lc2=is[1],lc3=is[2],lc4=is[3],lc5=is[4];
	if(is[4]=='+'){// yyyy+
	    if(lc2=='x'){// yxyy+
		if('A' <= lc && lc<='Z' ){// Yxyy+
		smapp(lc3,lc4,1,1,EMPTY,EMPTY,lc3,lc4);
		}else if('a' <= lc && lc<='h' ){// yxyy+
		    smapp(lc3,lc4,1,1,lc,EMPTY,lc3,lc4);
		}

	    }else if(lc3=='='){
		if('1' <= lc2 && lc2<='8'){
		    switch(lc4){
		    case 'R':imap.w.PROM=ROOK; break;
		    case 'N':imap.w.PROM=KNIGHT;break;
		    case 'B':imap.w.PROM=BISHOP;break;
		    case 'Q':imap.w.PROM=QUEEN;break;
		    }
		    smapp(lc,lc2,1,0,EMPTY,EMPTY,lc,lc2)
		}else if('a' <= lc2 && lc2<='h'){
		    switch(lc4){
		    case 'R':imap.w.PROM=ROOK; break;
		    case 'N':imap.w.PROM=KNIGHT;break;
		    case 'B':imap.w.PROM=BISHOP;break;
		    case 'Q':imap.w.PROM=QUEEN;break;
		    }
		    smapp(lc,lc2,1,0,EMPTY,EMPTY,lc,lc2)
		}
	    }
	    else if('a' <= lc2 && lc2<='h' ){
		smapp(lc3,lc4,1,0,lc2,EMPTY,lc3,lc4);
	    }else if('1' <= lc2 && lc2<='8' ){
		smapp(lc3,lc4,1,0,EMPTY,lc2,lc3,lc4);
	    }

	}else if(lc3=='x'){//yyxyy -> Y[a-h]xyy ,Y[1-8]xyy
	    if('A' <= lc && lc<='Z' ){// Y[a-h]xyy
		if('a' <= lc2 && lc2<='h' ){
		    smapp(lc4,lc5,0,1,lc2,EMPTY,lc4,lc5);
		}else if('1' <= lc2 && lc2<='8' ){//Y[1-8]xyy
		    smapp(lc4,lc5,0,1,EMPTY,lc2,lc4,lc5);
		}

	    }else if('a' <= lc && lc<='h' ){
		smapp(lc4,lc5,0,1,lc,lc2,lc4,lc5);
	    }
	}

    }else if(is.size()==6){
	char lc2=is[1],lc3=is[2],lc4=is[3],lc5=is[4],lc6=is[5];
	if(lc6=='+'){// yyyyy+
	    if(lc3=='x'){//Yyxyy+
		if('A' <= lc && lc<='Z' ){
		    smapp(lc4,lc5,1,1,lc2,EMPTY,lc4,lc5);
		}else if('a' <= lc && lc<='h' ){
		    smapp(lc4,lc5,1,1,lc,lc2,lc4,lc5);
		}

	    }

	}else if(lc2=='x' && lc5=='='){//bxc8=Q
	    switch(lc5){
	    case 'R':imap.w.PROM=ROOK; break;
	    case 'N':imap.w.PROM=KNIGHT;break;
	    case 'B':imap.w.PROM=BISHOP;break;
	    case 'Q':imap.w.PROM=QUEEN;break;
	    }
	    smapp(lc3,lc4,0,0,lc,EMPTY,lc3,lc4)
	}
    }else if(is.size()==7){
	char lc2=is[1],lc3=is[2],lc4=is[3],lc5=is[4],lc6=is[5],lc7=is[6];
	        if(lc2=='x' && lc7=='+' && lc5=='='){//exf8=Q+
		            switch(lc6){
			    case 'R':imap.w.PROM=ROOK; break;
			    case 'N':imap.w.PROM=KNIGHT;break;
			    case 'B':imap.w.PROM=BISHOP;break;
			    case 'Q':imap.w.PROM=QUEEN;break;
			    }
			    smapp(lc3,lc4,1,0,lc,EMPTY,lc3,lc4)
		        }
                }


cout << "unproced : " << is << " ----------------------\n";
return false;
}

bool convert2g(vector<gmoves> &gmv,vector<vector<string>> &mvs){
    //mapToArray lmp;
    //int rr;

    gmoves whgm,blgm;
    whgm.w.CLR=WHITE;
    blgm.w.CLR=BLACK;
    whgm.w.PROM=EMPTY;
    blgm.w.PROM=EMPTY;
    for(auto o:mvs){
	if (o.size()<3){
	 //cerr << o.size() <<" ";
	    return true;
	}
	cout << o[0] << " ";
	string f=o[1];
	if(f!=""){
	    whgm.w.PROM=EMPTY;
	    if(f[0]=='O'){
		if(f.size()==3){
		    f="Rhf1";
		    convstr(f,whgm);
		    gmv.push_back(whgm);
		    f="K1g1";
		    convstr(f,whgm);
		    gmv.push_back(whgm);
		}else if(f.size()==4){
		    f="Rhf1+";
		    convstr(f,whgm);
		    gmv.push_back(whgm);
		    f="K1g1";
		    convstr(f,whgm);
		    gmv.push_back(whgm);
		}else if(f.size()==5){
		    f="Rad1";
		    convstr(f,whgm);
		    gmv.push_back(whgm);
		    f="K1c1";
		    convstr(f,whgm);
		    gmv.push_back(whgm);
		}else if(f.size()==6){
		    f="Rad1+";
		    convstr(f,whgm);
		    gmv.push_back(whgm);
		    f="K1c1";
		    convstr(f,whgm);
		    gmv.push_back(whgm);
		}
	    }else{
		if(!convstr(f,whgm)){
		    cout << o[0] << " " << o[1] << " " << o[2] << " \n";
		    return false;
		};
		gmv.push_back(whgm);

	    }
	    //if(whgm.w.PROM)  cout << "prom \n";
	    //if(f.size()>=5)
	    cout << f << " "<<cpcs[whgm.w.PCE] <<whgm.FR_f <<whgm.FR_r <<whgm.istake<<whgm.TO_f <<whgm.TO_r << whgm.isch<< " ";
	}
	else return true;

    //gmv[gmv.size()-1].w.MAP=ugm.w.MAP;
	f=o[2];
	if(f!=""){
	    blgm.w.PROM=EMPTY;
	    if(f[0]=='O'){
		if(f.size()==3){
		    f="Rhf8";
		    convstr(f,blgm);
		    gmv.push_back(blgm);
		    f="K8g8";
		    convstr(f,blgm);
		    gmv.push_back(blgm);
		}else if(f.size()==4){
		    f="Rhf8+";
		    convstr(f,blgm);
		    gmv.push_back(blgm);
		    f="K8g8";
		    convstr(f,blgm);
		    gmv.push_back(blgm);
		}else if(f.size()==5){
		    f="Rad8";
		    convstr(f,blgm);
		    gmv.push_back(blgm);
		    f="K8c8";
		    convstr(f,blgm);
		    gmv.push_back(blgm);
		}else if(f.size()==6){
		    f="Rad8+";
		    convstr(f,blgm);
		    gmv.push_back(blgm);
		    f="K8c8";
		    convstr(f,blgm);
		    gmv.push_back(blgm);
		}
	    }else{
		//convstr(f,blgm);
		if(!convstr(f,blgm)){
		    cout << o[0] << " " << o[1] << " " << o[2] << " \n";
		return false;
		};
		gmv.push_back(blgm);
	    }
	    //if(blgm.w.PROM)  cout << "prom \n";
	    //if(f.size()>=5)
	cout << f << " "<<cpcs[blgm.w.PCE]<<blgm.FR_f <<blgm.FR_r <<blgm.istake<<blgm.TO_f <<blgm.TO_r << blgm.isch<<"\n";
	}
	else return true;
    }
    return true;
}

unsigned int findLastMatchPar(const string & str,unsigned int pos){
renew:
    pos++;
    char lc=str[pos];

while(lc!='}' && lc!=')' && lc!=']'){
    if(lc=='{' || lc=='('|| lc=='[')pos= findLastMatchPar(str, pos);
    pos++;
    lc=str[pos];
}
if(lc==')'&&str[pos-1]==':')
    goto renew;
return pos;
}

bool parse(const string &in,vector<vector<string>> & vs){
    vector<string> lvstr;
    string::size_type idx=0;

    string tok;
    while(idx<in.size()){
	char lc=in[idx];
	if(lc==' ' && tok!="" && lvstr.size() < 3){
	    lvstr.push_back(tok);
	    if(tok.size()>15) cout<<"in"<<"\n";
	    tok="";
	}else if(lc=='.'){
	    if(in[idx+1]=='.' && in[idx+2]=='.'){lc=' ';tok="";idx+=2;}
	    else{
		if(lvstr.size()==3)vs.push_back(lvstr);
	    if(tok.size()>15) cout<<"in"<<"\n";
	    //if(lvstr.size()==3)
	    //cout <<"\n"<< lvstr[0]<<" "<< lvstr[1]<<" "<< lvstr[2];
	    lvstr.clear();
	    lvstr.push_back(tok);
	    tok="";
	    lc =' ';}
	}else if(lc=='{' || lc=='(' || lc=='[')idx= findLastMatchPar(in, idx);

	else if(lc=='$')
	{
	    while(in[idx+1]>='0' && in[idx+1]<='9')idx++;
	}else if(lc==')')lc=' ';
	else {
	    if(lc!=' ')tok.push_back(lc);
	}
	idx++;
    }
    if(lvstr.size())vs.push_back(lvstr);
    auto aa=vs[vs.size()-1];
    auto ab=aa[aa.size()-1];
    if(ab=="*" || ab=="1-0" || ab=="0-1" || ab=="1/2-1/2"){vs[vs.size()-1].pop_back();}
//vector<gmoves> gmv;

return true;
}

struct PGNLoader{
    vector<gmoves> gmv;
    bool loadPGN(string &FName);
};

bool PGNLoader::loadPGN(string &FName){
    int cctr=0;
    vector<vector<string>> mvs;
    string line;
    ifstream myfile (FName);
    //ifstream myfile ("c:\\t\\t\\8.txt");
    //ifstream myfile ("C:\\t\\arena_3.5.1\\Databases\\e.pgn");
    //ifstream myfile ("C:\\t\\arena_3.5.1\\Databases\\o-deville.pgn");
    string bigl="";
    if (myfile.is_open())
    {
	while ( getline (myfile,line) )
	{
	    //cout << line <<" ^^^^\n";
	    if(line.size())
	    while(line[line.size()-1]==' ')line.pop_back();
	    if(line[0]=='{' && line[line.size()-1]!='}'){
		while ( getline (myfile,line) )
		{
		    while(line[line.size()-1]==' ')line.pop_back();
		    if(line[line.size()-1]=='}'){getline (myfile,line);break;}
		}
	    }

	    if(line[0]=='1'){
		bigl=line;
		bigl += " ";
		while ( getline (myfile,line) )
		{

		    if(/*line[0]!=' ' ||*/ line!=""){
			//cout << line <<" ||\n";
			bigl+=line;
			bigl += " ";
		    }
		    else break;
		}

		cctr++; cout<<"\ngame #: " <<cctr<<" \n"; //
		//cout<< "\nbigl : " << bigl <<" nbigl  ||\n";
		if(!parse(bigl,mvs)){cout << bigl <<"\n\n";return false;}
		if(!convert2g(gmv,mvs))return false;
		//if(!(cctr%100))
		/*for (auto b:mvs){
	    for (auto bin:b){
	    //cout << bin <<" ";
	    }
	    //cout << "\n";
	}*/
		//convert2g(gmv,mvs);
		//return 0;
		/*for(auto b:gmv){
	    //cout << b.w.MAP << " " <<b.w.PCE  << " ;;;";
	}*/
		//gmv.clear();
		mvs.clear();
		//cout<<"\n";
		//cout << bigl << "\n\n";
		bigl="";
	    }

	}
	myfile.close();
    }
    else {cout << "Unable to open file";

    }
    return 0;
}
