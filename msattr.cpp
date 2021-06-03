#ifndef msattrcpp
#define msattrcpp
#include <algorithm>
#include<iostream>
#include<vector>
 //#include <iomanip>
#include"msattr.h"
#include"fparse.cpp"
using namespace std;
#define COL_PERFT false
 u_lol msatr::bPCS_btARR[8];
 u_lol msatr::wPCS_btARR[8];
 u_lol msatr::wPCS_BITS,msatr::bPCS_BITS;

int rankFile2idx(char rank, char file) {
	return (7 - (rank - 49)) * 10 + ((file - 97)) + 21;
}
void bsf(int *r,u_lol rd){
	_BitScanForward64(r,rd);
}
void bsr(int *r,u_lol rd){
	_BitScanReverse64(r,rd);
}
void dbgptr_ull1(unsigned long long in){
	u_lol b1=0x8000000000000000;
	for(int x=0;x<64;x++){if(in&b1)cout<<"1";else cout<<"0";b1>>=1;
	}
}

void dbgptr_ull(unsigned long long in){
	cout <<"\n";
	for (int x=0;x<8;x++) {
	 for (int xi=0;xi<8;xi++) {
		 int r=x*8+xi;
		 if(in & ((unsigned long long)0x8000000000000000>> r))cout <<'1';
		 else cout << '0';
	 }
	 cout << "\n";
	}
	 cout << "\n"<<flush;
}
void dbgptr_uch(unsigned char in){
	cout <<"\n";
		 for (int xi=0;xi<8;xi++) {
		 if(in & ((unsigned char)0x80>> xi))cout <<'1';
		 else cout << '0';
	 }
	 cout << "\n";

}
int ctr=0;
unsigned char mk_mask(unsigned char in, int ridx){
   // cout<< in << " " <<ridx <<" "  << ctr++<<";";
	int lidx=ridx;
		unsigned char bit1=1<<(ridx-1);
	unsigned char em=0;
	//em|=1<<ridx;
	while(!(in&bit1) && ridx>=0){em|=bit1;ridx--;bit1=bit1>>1;}
	if(ridx>0){/*bit1>>1;*/em|=bit1;}
	bit1=1<<(lidx+1);
	//char em=0;
	while(!(in&bit1) && lidx<=8){em|=bit1;lidx++;bit1=bit1<<1;}
	if(lidx<8){/*bit1<<1*/;em|=bit1;}
return em;
}


void setls(u_lol in){
	u_lol tmp=in;
	while (in){
	int a=lsb(in);
	lls[a]=tmp;
		in^=1ull<<a;
	}
        //cout << "-" <<flush;
}

void mkl(){
	u_lol pp=diag;
	u_lol pmsk=0x7f7f7f7f7f7f7f7f;
	u_lol pmsk1=0xfefefefefefefefe;
	setls(diag);
	for(int x=0;x<7;x++){
		pp&=pmsk;
		pp=pp<<1;
		//dbgptr_ull(pp);
		setls(pp);
	}
	pp=diag;
		for(int x=0;x<7;x++){
		pp&=pmsk1;
		pp=pp>>1;
		//dbgptr_ull(pp);
		setls(pp);
	}

}

u_lol get_bmask(int bpos,u_lol BISHOP_ATT_MSK){
	//cout<< "Enter Mask : ";
	//dbgptr_ull(BISHOP_ATT_MSK);
	u_lol pmsk=0x7f7f7f7f7f7f7f7f;
	u_lol pmsk1=0xfefefefefefefefe;
	u_lol d_line=lls[bpos];
	u_lol cline=(BISHOP_ATT_MSK&d_line)|(1ull<<bpos);
	u_lol s_line=cline;
	int po=lsb(s_line);
	s_line^=1ull<<po;

	u_lol s_lineb=s_line;
	s_line=(s_line&pmsk1)>>1;
	s_lineb=(s_lineb/*&pmsk*/)>>8;

	u_lol t_clineb= (cline&pmsk)>>7;
	u_lol t_clinet= (cline&pmsk1)<<7;

	//dbgptr_ull(t_clineb);
	//dbgptr_ull(t_clinet);
	while(t_clineb&BISHOP_ATT_MSK){
		cline|=t_clineb|s_lineb;
		t_clineb= (t_clineb&pmsk)>>7;
		s_lineb=(s_lineb&pmsk)>>7;
	}
	while(t_clinet&BISHOP_ATT_MSK){
		cline|=t_clinet|s_line;
		t_clinet= (t_clinet&pmsk1)<<7;
		s_line=(s_line&pmsk1)<<7;
	}
	//cout << "Final : ";
	//dbgptr_ull(cline);
	return cline;
}

void msatr::assert_kings(){
	if constexpr(!ASSERT_KINGS)return;
	if(wlpieces[C2_KING].NEXT==0){
		printt();
		cout << "wKing!!!";
	}
	if(blpieces[C2_KING].NEXT==0){
		printt();
		cout << "bKing!!!";
	}
}

void msatr::assert_eq_bts(){
	if constexpr (!(ASSERT_EQ_BITS)) return;
	u_lol pp=0;
	int p=wlpieces[V_PAWN].NEXT;
	while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}
	p=wlpieces[KNIGHT].NEXT;
	while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}
	p=wlpieces[BISHOP].NEXT;
	while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}
	p=wlpieces[ROOK].NEXT;
	while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}
	p=wlpieces[QUEEN].NEXT;
	while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}
	p=wlpieces[C2_KING].NEXT;
	while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}

   if(pp!=wPCS_BITS){
	   printt();
	   dbgptr_ull(pp);
	   dbgptr_ull(wPCS_BITS);
	   cout <<"Unequal"<<flush;
   }

	pp=0;
	p=blpieces[V_PAWN].NEXT;
   while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}
   p=blpieces[KNIGHT].NEXT;
   while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}
   p=blpieces[BISHOP].NEXT;
   while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}
   p=blpieces[ROOK].NEXT;
   while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}
   p=blpieces[QUEEN].NEXT;
   while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}
   p=blpieces[C2_KING].NEXT;
  while(p!=0){pp|=bits1[p];p=Table[p].NEXT;}

  if(pp!=bPCS_BITS){
	  printt();
	  dbgptr_ull(pp);
	  dbgptr_ull(bPCS_BITS);
	  cout <<"Unequal"<<flush;
  }

}
moveCPiece msatr::fenParser(string instr){
	for (int x=0;x<64;x++)Table[toBigTable[x]]=EMPTY_mapToTable;
	moveCPiece lmpc=EMPTY_movePiece;
	mapToTable lvmp=EMPTY_mapToTable;
	int pce,clr,pos;
	int rank=7,file=0;
	int pcce=0;
	int anp;
		Table[firstBPce[V_PAWN]].NEXT=0;
	Table[firstBPce[ROOK]].NEXT=0;
	Table[firstBPce[BISHOP]].NEXT=0;
	Table[firstBPce[KNIGHT]].NEXT=0;
	Table[firstBPce[QUEEN]].NEXT=0;
	Table[firstBPce[C2_KING]].NEXT=0;

	Table[firstWPce[V_PAWN]].NEXT=0;
	Table[firstWPce[ROOK]].NEXT=0;
	Table[firstWPce[BISHOP]].NEXT=0;
	Table[firstWPce[KNIGHT]].NEXT=0;
	Table[firstWPce[QUEEN]].NEXT=0;
	Table[firstWPce[C2_KING]].NEXT=0;
	memset(bPCS_btARR,0,64);
	memset(wPCS_btARR,0,64);
	bPCS_BITS=0;
	wPCS_BITS=0;
#define setb(pcce) lvmp.PCE= pcce;\
	lvmp.CLR=BLACK;\
	lvmp.MAP=toBigTable[(7-rank)*8+file];\
	lvmp.PREV=firstBPce[pcce];\
	lvmp.NEXT=Table[firstBPce[pcce]].NEXT;\
	Table[lvmp.PREV].NEXT=lvmp.MAP;\
	Table[lvmp.NEXT].PREV=lvmp.MAP;\
	bPCS_btARR[pcce]|=bits1[lvmp.MAP];\
	bPCS_BITS|=bits1[lvmp.MAP];\
	Table[lvmp.MAP]=lvmp;


#define setw(pcce) lvmp.PCE= pcce;\
	lvmp.CLR=WHITE;\
	lvmp.MAP=toBigTable[ (7-rank)*8+file];\
	lvmp.PREV=firstWPce[pcce];\
	lvmp.NEXT=Table[firstWPce[pcce]].NEXT;\
	Table[lvmp.PREV].NEXT=lvmp.MAP;\
	Table[lvmp.NEXT].PREV=lvmp.MAP;\
	wPCS_btARR[pcce]|=bits1[lvmp.MAP];\
	wPCS_BITS|=bits1[lvmp.MAP];\
	Table[lvmp.MAP]=lvmp;
//////problem    rnb3kr/ppp2ppp/1b6/3q4/3pN3/Q4N2/PPP2KPP/R1B1R3 w - - bm Nf6+
/// 130840222 2889877 83863 1777 50 0 0
/// 130840144 2889877 83863 1777 50
///
///+k  rnb3kr/ppp2ppp/1b6/3q4/3pN3/Q4N2/PPP1K1PP/R1B1R3 b - - 1 1
///
///
	//problematic  { "r3k3/8/1N6/r7/8/8/8/1K6 w q - 0 1", 5, 346695 },
	//{ "4k2r/8/8/7r/8/8/1B6/1K6 w k - 0 1", 5, 1063513 },
	//{ "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1", 6, 706045033 },
	//unsigned char fenc[]={"r3k2r/1b4bq/8/8/8/8/7B/R3K2R w KQkq -;"};
	//rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -
	// big--rn5r/ppp2k2/1B3n2/3qp1pp/Pb3p2/1P1P3b/R2QPPP1/1N2KBNR w K -
	//8/8/1k6/8/2pP4/8/5BK1/8 b - d3 0 1
	// big r3r1k1/1pq2pp1/2p2n2/1PNn4/2QN2b1/6P1/3RPP2/2R3KB b - -
	//"r3k2r/1bp2pP1/5n2/1P1Q4/1pPq4/5N2/1B1P2p1/R3K2R b KQkq c3 0 1";
	const  char *fenc=instr.c_str();
	//{"r3r1k1/1pq2pp1/2p2n2/1PNn4/2QN2b1/6P1/3RPP2/2R3KB b - -"};
	int x=0;
	char c=fenc[x++];
	while(c!=' '){
	switch(c){
	case '/':{
		rank--;
		file=0;
	}
		break;
	case '1':file+=(c-48);break;
	case '2':file+=(c-48);break;
	case '3':file+=(c-48);break;
	case '4':file+=(c-48);break;
	case '5':file+=(c-48);break;
	case '6':file+=(c-48);break;
	case '7':file+=(c-48);break;
	case '8':file+=(c-48);break;



	case 'p':{setb(V_PAWN);}file++;break;
	case 'r':{setb(ROOK);}file++;break;
	case 'n':{setb(KNIGHT);}file++;break;
	case 'b':{setb(BISHOP);}file++;break;
	case 'q':{setb(QUEEN);}file++;break;
	case 'k':{setb(C2_KING);}file++;break;


	case 'P':{setw(V_PAWN);}file++;break;
	case 'R':{setw(ROOK);}file++;break;
	case 'N':{setw(KNIGHT);}file++;break;
	case 'B':{setw(BISHOP);}file++;break;
	case 'Q':{setw(QUEEN);}file++;break;
	case 'K':{setw(C2_KING);}file++;break;

	}
	//if(file==8){file=0;rank--;}
	//x++;
	c=fenc[x++];
	//printt();
	}
	while(c==' ')c=fenc[x++];

	auto [ a1,a2 ] = kingXSafety< WHITE,BLACK >(wlpieces[C2_KING].NEXT);
			auto whitek=(a1|a2)&wPCS_BITS;
			auto [ a4,a5 ] = kingXSafety< WHITE,BLACK >(blpieces[C2_KING].NEXT);
			auto blackk=(a5|a4)&bPCS_BITS;

			if(c=='w'){lmpc.ATT_SID=0;if (kingSafety<WHITE, BLACK>(wlpieces[C2_KING].NEXT) == KING_VAL)lmpc.GIV_CHK = 1;}
			if(c=='b'){lmpc.ATT_SID=1;if (kingSafety<BLACK, WHITE>(blpieces[C2_KING].NEXT) == KING_VAL)lmpc.GIV_CHK = 1;}
			c=fenc[x++];
	while(c==' ')c=fenc[x++];
	while(c!=' ' /*&& c!='-'*/){
	switch(c){
	case 'K':{lmpc.WH_CSR=1;Table[WH_KING].STAT=true;Table[RIGHT_BOT].STAT=2;}break;
	case 'Q':{lmpc.WH_CSL=1;Table[WH_KING].STAT=true;Table[LEFT_BOT].STAT=1;}break;
	case 'k':{lmpc.BL_CSR=1;Table[BL_KING].STAT=true;Table[RIGHT_TOP].STAT=2;}break;
	case 'q':{lmpc.BL_CSL=1;Table[BL_KING].STAT=true;Table[LEFT_TOP].STAT=1;}break;
	case'-':break;
	}
	c=fenc[x++];

	}
	c=fenc[x++];
	while(c==' ')c=fenc[x++];
	if(c>='a' && c<='h'){
	anp=rankFile2idx(fenc[x++],c);
	lmpc.ANP_AV=1;
	if(lmpc.ATT_SID==0){
		lmpc.FR_PO =anp+30;
		lmpc.TO_PO =anp+10;
	}else{
		lmpc.FR_PO =anp-30;
		lmpc.TO_PO =anp-10;
	}
	}
return lmpc;
}

void msatr::movePawn(vector<mapToArray>(&pieces)[8], int CHRG_PCE, int CHRG_POS, int TARG_PCE, int TARG_POS, int PROM)
{
	int idx = 0;
	mapToTable lmpt = Table[CHRG_POS];
	Table[lmpt.PREV].NEXT = TARG_POS;
	Table[lmpt.NEXT].PREV = TARG_POS;
	while (idx < pieces[CHRG_PCE].size()) {
	//cerr << pieces[CHRG_PCE][idx].MAP << " ";
	if (pieces[CHRG_PCE][idx].MAP == CHRG_POS) {
		if (!PROM) {
		if (CHRG_PCE == V_PAWN) {
			for (int x = 0; x < pieces[V_PAWN].size(); x++) {
			if (pieces[V_PAWN][x].MAP == CHRG_POS) {
				mapToArray lm = pieces[V_PAWN][x];
				lm.PCE = V_PAWN;
				pieces[V_PAWN].push_back(lm);
				pieces[V_PAWN].erase(pieces[V_PAWN].begin() + x);
				idx = pieces[V_PAWN].size() - 1;
				CHRG_PCE = V_PAWN;
				break;
			}
			}
		}
		Table[CHRG_POS].PCE = V_PAWN;
		pieces[CHRG_PCE][idx].MAP = TARG_POS;
		Table[TARG_POS] = Table[CHRG_POS];
		Table[CHRG_POS] = EMPTY_mapToTable;
		}
		else {
		mapToArray l1 = pieces[CHRG_PCE][idx];
		mapToTable mpl;
		fill_mapToTable(mpl, PROM, l1.CLR, TARG_POS, 0)

				pieces[CHRG_PCE].erase(pieces[CHRG_PCE].begin() + idx);
		l1.PCE = PROM;
		l1.MAP = TARG_POS;
		Table[CHRG_POS].PCE = PROM;
		pieces[PROM].push_back(l1);
		Table[CHRG_POS].MAP = pieces[PROM].size() - 1;
		Table[TARG_POS] = Table[CHRG_POS];
		Table[CHRG_POS] = EMPTY_mapToTable;
		}
		break;
	}
	idx++;
	}

}

void msatr::moveTablePce(vector<mapToArray>(&pieces)[8], int CHRG_PCE, int CHRG_POS, int TARG_POS)
{
	int idx = 0;
	mapToTable lmpt = Table[CHRG_POS];
	Table[lmpt.PREV].NEXT = TARG_POS;
	Table[lmpt.NEXT].PREV = TARG_POS;
	while (idx < pieces[CHRG_PCE].size()) {
	if (pieces[CHRG_PCE][idx].MAP == CHRG_POS) {
		pieces[CHRG_PCE][idx].MAP = TARG_POS;
		Table[TARG_POS] = Table[CHRG_POS];
		Table[CHRG_POS] = EMPTY_mapToTable;
		break;
	}
	idx++;
	}

#ifdef DEBUG
	assert_consist();
#endif
}
template <int CLR_ATT>
void msatr::moveTablePce_L(unsigned char PCE,unsigned char CHRG_POS,unsigned char TARG_POS)
{
    u_lol u1;
    u1=bits1[CHRG_POS]|bits1[TARG_POS];
    if constexpr(CLR_ATT==WHITE){
        wPCS_btARR[PCE]^=u1;
        wPCS_BITS^=u1;
    }else{
        bPCS_btARR[PCE]^=u1;
        bPCS_BITS^=u1;
    }
    union{
        mapToTable lmpt;
        u_lol lol;
    };

    lol =ulp[CHRG_POS];
    ulp[TARG_POS]=lol;
    ulp[CHRG_POS]=0;
}

void msatr::popPieceFromArray(vector<mapToArray>(&pieces)[8],int TARG_PCE, int TARG_POS)
{
	int idx = 0;
	mapToTable lmpt = Table[TARG_POS];
	Table[lmpt.PREV].NEXT = lmpt.NEXT;
	Table[lmpt.NEXT].PREV = lmpt.PREV;
	takenPieces.push_back(lmpt);
	while (idx < pieces[TARG_PCE].size()) {

	if (pieces[TARG_PCE][idx].MAP == TARG_POS) {
		mapToArray l1 = pieces[TARG_PCE][idx];
		pieces[TARG_PCE].erase(pieces[TARG_PCE].begin() + idx);
		pieces[EMPTY].push_back(l1);
		break;
	}
	idx++;
	}
}
template <int CLR_P>
void msatr::popPieceFromArray_L(int TARG_POS)
{
	mapToTable lmpt = Table[TARG_POS];
	if constexpr(CLR_P==WHITE){
	wPCS_btARR[lmpt.PCE]^=bits1[TARG_POS];
	wPCS_BITS^=bits1[TARG_POS];
	}else{
	bPCS_btARR[lmpt.PCE]^=bits1[TARG_POS];
	bPCS_BITS^=bits1[TARG_POS];
	}

	//Table[lmpt.PREV].NEXT = lmpt.NEXT;
	//Table[lmpt.NEXT].PREV = lmpt.PREV;
	lmpt.MAP = TARG_POS;
	takenPieces.push_back(lmpt);
	Table[TARG_POS]=EMPTY_mapToTable;

}
void msatr::applyMove(gmoves &tmove, int CHRG_PCE, int CHRG_POS, int TARG_PCE, int TARG_POS) {
	if (tmove.w.CLR == WHITE) {
	if (tmove.istake) {
		popPieceFromArray(bpieces, TARG_PCE, TARG_POS);
	}
	moveTablePce(wpieces, CHRG_PCE, CHRG_POS, TARG_POS);
	}
	else {
	if (tmove.istake) {
		popPieceFromArray(wpieces, TARG_PCE, TARG_POS);
	}
	moveTablePce(bpieces, CHRG_PCE, CHRG_POS, TARG_POS);
	}
#ifdef DEBUG
	assert_consist();
#endif
}

void msatr::printt() {
	cout<<"\n";
	for (int x = 0; x < 8; x++) {
	for (int xi = 0; xi < 8; xi++) {
		int d = 21 + x * 10 + xi;
		if (Table[d].CLR == WHITE && (Table[d].PCE == V_PAWN || Table[d].PCE == V_PAWN))cout << "P";
		else if (Table[d].CLR == WHITE && Table[d].PCE == ROOK)cout << "R";
		else if (Table[d].CLR == WHITE && Table[d].PCE == KNIGHT)cout << "N";
		else if (Table[d].CLR == WHITE && Table[d].PCE == BISHOP)cout << "B";
		else if (Table[d].CLR == WHITE && Table[d].PCE == QUEEN)cout << "Q";
		else if (Table[d].CLR == WHITE && Table[d].PCE == C2_KING)cout << "K";

		else if (Table[d].CLR == BLACK && (Table[d].PCE == V_PAWN || Table[d].PCE == V_PAWN))cout << "p";
		else if (Table[d].CLR == BLACK && Table[d].PCE == ROOK)cout << "r";
		else if (Table[d].CLR == BLACK && Table[d].PCE == KNIGHT)cout << "n";
		else if (Table[d].CLR == BLACK && Table[d].PCE == BISHOP)cout << "b";
		else if (Table[d].CLR == BLACK && Table[d].PCE == QUEEN)cout << "q";
		else if (Table[d].CLR == BLACK && Table[d].PCE == C2_KING)cout << "k";
		else cout << ".";// dbgt64[x * 8 + xi];
	}
	cout << "\n";
	}
        cout << "-------------\n"<<flush;
}

bool msatr::makeMoveFromFile(gmoves &tmove)
{
#ifdef DEBUG
	assert_consist();
#endif
	int rpos;
	int SRCH_CLR;
	if (tmove.w.CLR == WHITE) { SRCH_CLR = WHITE; }
	else SRCH_CLR = BLACK;
	int CHRG_PCE = tmove.w.PCE;
	int TARG_POS = tmove.w.MAP;
	int PROM = tmove.w.PROM;
	mapToTable TARGET = Table[TARG_POS];
	int TARG_PCE = TARGET.PCE;
	int CHRG_POS;
	int frf = tmove.FR_f;
	int tof = tmove.TO_f;
	int tor = tmove.TO_r;
	int frr = tmove.FR_r;
	switch (CHRG_PCE) {
	case V_PAWN:
	//case V_PAWN:
	if (tmove.w.CLR == WHITE) {

		if (tmove.istake) {
		if (Table[TARG_POS].CLR != BLACK) {
			cout << "bad target CLR?"; return false;
		}
		if (frf < tof)CHRG_POS = TARG_POS + 9;
		else CHRG_POS = TARG_POS + 11;
		int LPCE = Table[CHRG_POS].PCE;
		if (LPCE != V_PAWN && LPCE != V_PAWN) {
			cout << " bad FROM?"; return false;
		}
		int idx = 0;
		popPieceFromArray(bpieces, TARG_PCE, TARG_POS);
		if (mapBrdTbl2file[CHRG_POS] == '2')CHRG_PCE = V_PAWN;
		movePawn(wpieces, CHRG_PCE, CHRG_POS, TARG_PCE, TARG_POS, PROM);
		}
		else {
		if (Table[TARG_POS + 10].PCE != 0) {
			CHRG_POS = TARG_POS + 10;
		}
		else if (Table[TARG_POS + 20].PCE != 0) {
			CHRG_POS = TARG_POS + 20;
		}
		if (mapBrdTbl2file[CHRG_POS] == '2')CHRG_PCE = V_PAWN;
		movePawn(wpieces, CHRG_PCE, CHRG_POS, TARG_PCE, TARG_POS, PROM);
		}
	}
	else if (tmove.w.CLR == BLACK) {

		if (tmove.istake) {
		if (Table[TARG_POS].CLR != WHITE) {
			cout << "bad target CLR?"; return false;
		}
		if (frf < tof)CHRG_POS = TARG_POS - 11;
		else CHRG_POS = TARG_POS - 9;
		int LPCE = Table[CHRG_POS].PCE;
		if (LPCE != V_PAWN && LPCE != V_PAWN) {
			cout << " bad FROM?"; return false;
		}
		popPieceFromArray(wpieces, TARG_PCE, TARG_POS);
		if (mapBrdTbl2file[CHRG_POS] == '7')CHRG_PCE = V_PAWN;
		movePawn(bpieces, CHRG_PCE, CHRG_POS, TARG_PCE, TARG_POS, PROM);
		}
		else {
		if (Table[TARG_POS - 10].PCE != 0) {
			CHRG_POS = TARG_POS - 10;
		}
		else if (Table[TARG_POS - 20].PCE != 0) {
			CHRG_POS = TARG_POS - 20;
		}
		if (mapBrdTbl2file[CHRG_POS] == '7')CHRG_PCE = V_PAWN;
		movePawn(bpieces, CHRG_PCE, CHRG_POS, TARG_PCE, TARG_POS, PROM);
		}
	}
	break;
	//assert_consist();
	case KNIGHT:
	{
	if (frf == 0 && frr == 0) {
		for (int x = 0; x < 8; x++) {
		if (Table[KNIGHT_JUMPS[x] + TARG_POS].PCE == KNIGHT && Table[KNIGHT_JUMPS[x] + TARG_POS].CLR == SRCH_CLR) {
			rpos = TARG_POS + KNIGHT_JUMPS[x];
			break;
		}
		}
	}
	else if (frf == 0 && frr >= '1'&&frr <= '8') {
		int lin = frr - 49;
		for (int x = 0; x < 8; x++) {
		int lm = TableLineFromRank[lin][x];
		if (Table[lm].PCE == KNIGHT && Table[lm].CLR == SRCH_CLR) { rpos = lm; goto FOUNDN; }
		}
	}
	else if (frr == 0 && frf >= 'a'&&frf <= 'h') {
		int lin = frf - 97;
		for (int x = 0; x < 8; x++) {
		int lm = TableColumneFromFile[lin][x];
		if (Table[lm].PCE == KNIGHT && Table[lm].CLR == SRCH_CLR) { rpos = lm; goto FOUNDN; }
		}
	}
	else if (frr >= '1' && frr <= '8'&& frf >= 'a'&&frf <= 'h') {
		rpos = rankFile2idx(frf, frr);
	}
FOUNDN:
	CHRG_POS = rpos;
	applyMove(tmove, CHRG_PCE, CHRG_POS, TARG_PCE, TARG_POS);
	break;
	}//KNIGHT
	//assert_consist();
	case ROOK: {
	int lm = TARG_POS - 1;
	int rm = TARG_POS + 1;
	int dm = TARG_POS + 10;
	int um = TARG_POS - 10;
	if (frf == 0 && frr == 0) {
		while (!Table[lm].PCE)lm--;
		if (Table[lm].PCE == ROOK && Table[lm].CLR == SRCH_CLR) { rpos = lm; goto FOUND; }
		while (!Table[rm].PCE)rm++;
		if (Table[rm].PCE == ROOK && Table[rm].CLR == SRCH_CLR) { rpos = rm; goto FOUND; }
		while (!Table[um].PCE)um -= 10;
		if (Table[um].PCE == ROOK && Table[um].CLR == SRCH_CLR) { rpos = um; goto FOUND; }
		while (!Table[dm].PCE)dm += 10;
		if (Table[dm].PCE == ROOK && Table[dm].CLR == SRCH_CLR) { rpos = dm; goto FOUND; }
	}
	else if (frf == 0 && frr >= '1'&&frr <= '8') {
		int lin = frr - 49;
		for (int x = 0; x < 8; x++) {
		lm = TableLineFromRank[lin][x];
		if (Table[lm].PCE == ROOK && Table[lm].CLR == SRCH_CLR) { rpos = lm; goto FOUND; }
		}
	}
	else if (frr == 0 && frf >= 'a'&&frf <= 'h') {
		int lin = frf - 97;
		for (int x = 0; x < 8; x++) {
		lm = TableColumneFromFile[lin][x];
		if (Table[lm].PCE == ROOK && Table[lm].CLR == SRCH_CLR) { rpos = lm; goto FOUND; }
		}
	}
	else if (frr >= '1'&&frr <= '8' && frf >= 'a'&&frf <= 'h') {
		rpos = rankFile2idx(frf, frr);
	}
#ifdef DEBUG
	else {
		cout << "Rook from file bad proc \n";
	}
#endif
FOUND:
	CHRG_POS = rpos;
	applyMove(tmove, CHRG_PCE, CHRG_POS, TARG_PCE, TARG_POS);
	}//ROOK
	//assert_consist();
	break;
	case BISHOP: {
	int lu = TARG_POS - 11;
	int ru = TARG_POS - 9;
	int ld = TARG_POS + 9;
	int rd = TARG_POS + 11;
	if (frf == 0 && frr == 0) {
		while (!Table[lu].PCE)lu -= 11;
		if (Table[lu].PCE == BISHOP && Table[lu].CLR == SRCH_CLR) { rpos = lu; goto FOUNDB; }
		while (!Table[ld].PCE)ld += 9;
		if (Table[ld].PCE == BISHOP && Table[ld].CLR == SRCH_CLR) { rpos = ld; goto FOUNDB; }
		while (!Table[rd].PCE)rd += 11;
		if (Table[rd].PCE == BISHOP && Table[rd].CLR == SRCH_CLR) { rpos = rd; goto FOUNDB; }
		while (!Table[ru].PCE)ru += -9;
		if (Table[ru].PCE == BISHOP && Table[ru].CLR == SRCH_CLR) { rpos = ru; goto FOUNDB; }
	}
	else if (frf == 0 && frr >= '1'&&frr <= '8') {
		int lin = frr - 49;
		for (int x = 0; x < 8; x++) {
		lu = TableLineFromRank[lin][x];
		if (Table[lu].PCE == BISHOP && Table[lu].CLR == SRCH_CLR) { rpos = lu; goto FOUNDB; }
		}
	}
	else if (frr == 0 && frf >= 'a'&&frf <= 'h') {
		int lin = frr - 97;
		for (int x = 0; x < 8; x++) {
		lu = TableColumneFromFile[lin][x];
		if (Table[lu].PCE == BISHOP && Table[lu].CLR == SRCH_CLR) { rpos = lu; goto FOUNDB; }
		}
	}
	else if (frr >= '1'&&frr <= '8' && frf >= 'a'&&frf <= 'h') {
		rpos = rankFile2idx(frf, frr);
	}
FOUNDB:
	CHRG_POS = rpos;
	applyMove(tmove, CHRG_PCE, CHRG_POS, TARG_PCE, TARG_POS);
	}//BISHOP
	//assert_consist();
	break;
	case QUEEN: {
	int lm = TARG_POS - 1;
	int rm = TARG_POS + 1;
	int dm = TARG_POS + 10;
	int um = TARG_POS - 10;
	int lu = TARG_POS - 11;
	int ru = TARG_POS - 9;
	int ld = TARG_POS + 9;
	int rd = TARG_POS + 11;
	if (frf == 0 && frr == 0) {
		while (!Table[lm].PCE)lm--;
		if (Table[lm].PCE == QUEEN && Table[lm].CLR == SRCH_CLR) { rpos = lm; goto FOUNDQ; }
		while (!Table[rm].PCE)rm++;
		if (Table[rm].PCE == QUEEN && Table[rm].CLR == SRCH_CLR) { rpos = rm; goto FOUNDQ; }
		while (!Table[um].PCE)um -= 10;
		if (Table[um].PCE == QUEEN && Table[um].CLR == SRCH_CLR) { rpos = um; goto FOUNDQ; }
		while (!Table[dm].PCE)dm += 10;
		if (Table[dm].PCE == QUEEN && Table[dm].CLR == SRCH_CLR) { rpos = dm; goto FOUNDQ; }
		while (!Table[lu].PCE)lu -= 11;
		if (Table[lu].PCE == QUEEN && Table[lu].CLR == SRCH_CLR) { rpos = lu; goto FOUNDQ; }
		while (!Table[ld].PCE)ld += 9;
		if (Table[ld].PCE == QUEEN && Table[ld].CLR == SRCH_CLR) { rpos = ld; goto FOUNDQ; }
		while (!Table[rd].PCE)rd += 11;
		if (Table[rd].PCE == QUEEN && Table[rd].CLR == SRCH_CLR) { rpos = rd; goto FOUNDQ; }
		while (!Table[ru].PCE)ru += -9;
		if (Table[ru].PCE == QUEEN && Table[ru].CLR == SRCH_CLR) { rpos = ru; goto FOUNDQ; }
	}
	else if (frf == 0 && frr >= '1'&&frr <= '8') {
		int lin = frr - 49;
		for (int x = 0; x < 8; x++) {
		lu = TableColumneFromFile[lin][x];
		if (Table[lu].PCE == QUEEN && Table[lu].CLR == SRCH_CLR) { rpos = lu; goto FOUNDQ; }
		}
	}
	else if (frr == 0 && frf >= 'a'&&frf <= 'h') {
		int lin = frr - 97;
		for (int x = 0; x < 8; x++) {
		lu = TableLineFromRank[lin][x];
		if (Table[lu].PCE == QUEEN && Table[lu].CLR == SRCH_CLR) { rpos = lu; goto FOUNDQ; }
		}
	}
	else if (frr >= '1'&&frr <= '8' && frf >= 'a'&&frf <= 'h') {
		rpos = rankFile2idx(frf, frr);
	}
FOUNDQ:
	CHRG_POS = rpos;
	applyMove(tmove, CHRG_PCE, CHRG_POS, TARG_PCE, TARG_POS);
	}//QUEEN
	break;
#ifdef DEBUG
	assert_consist();
#endif
	case C2_KING: {
	if (SRCH_CLR == WHITE) {
		mapToArray lmp = wpieces[C2_KING][0];
		CHRG_POS = lmp.MAP;
		applyMove(tmove, CHRG_PCE, CHRG_POS, TARG_PCE, TARG_POS);
	}
	else {
		mapToArray lmp = bpieces[C2_KING][0];
		CHRG_POS = lmp.MAP;
		applyMove(tmove, CHRG_PCE, CHRG_POS, TARG_PCE, TARG_POS);
	}
	}//KING
	break;
	}//switch
#ifdef DEBUG
	assert_consist();
#endif
	//emptyHash();
	//moveCPiece lmv{0,0,0,1,1,1,1,0,0};
	//if (SRCH_CLR == WHITE)moves(lmv,  6,false,bsinf);
	//else moves(lmv,  6,false,wsinf);
	//printt();
	return true;
}


void msatr::dbgptr()
{
	for (int x = 0; x < 12; x++) {
	for (int xi = 0; xi < 10; xi++) {
		cout << Table[x * 10 + xi].PCE << " ";
	}
	cout << "\n";
	}
	for (int x = 0; x < 12; x++) {
	for (int xi = 0; xi < 10; xi++) {
		cout << Table[x * 10 + xi].CLR << " ";
	}
	cout << "\n";
	}
	for (int x = 0; x < 8; x++) {
	for (int xi = 0; xi < 8; xi++) {
		int d = 21 + xi * 10 + x;
		cout << toBigTable[x * 8 + xi] << " ";
	}
	cout << "\n";
	}
	for (int x = 0; x < 8; x++) {
	for (int xi = 0; xi < 8; xi++) {
		int d = 21 + x * 10 + xi;
		cout << toRegularTable[d] << " ";
	}
	cout << "\n";
	}
	for (int x = 0; x < 8; x++) {
	cout << "Whites:\n";
	for (auto b : wpieces[x]) {
		cout << "m: " << b.MAP << " " << pname[b.PCE] << "\n";
	}
	}
	for (int x = 0; x < 8; x++) {
	cout << "Blacks:\n";
	for (auto b : bpieces[x]) {
		cout << "m: " << b.MAP << " " << pname[b.PCE] << "\n";
	}
	}
	for (int x = 0; x < 8; x++) {
	for (int xi = 0; xi < 8; xi++) {
		cout << dbgt64[x * 8 + xi];

	}
	cout << "\n";
	}
	cout << "\n----------------------------------------*********\n\n";
}

msatr::msatr() {
	mapToTable mpt{ 31,NO_CLR,EMPTY,0 };
	vecMoves.reserve(4000);
	for (int x = 0; x < 120; x++) {
	Table[x] = mpt;
	}
	mpt.STAT = ON_TABLE;
	mpt.PCE = 0;
	for (int x = 0; x < 8; x++) {
	for (int xi = 0; xi < 8; xi++) {
		int d = 21 + x * 10 + xi;
		Table[d] = EMPTY_mapToTable;
		toBigTable[x * 8 + xi] = d;
		toRegularTable[d] = x * 8 + xi;
		mapBrdTbl2file[d] = static_cast<char>(((8 - x) + 48));
		mapBrdTbl2rank[d] = static_cast<char>(xi + 97);
	}
	}
	wlpieces = &Table[1];
	blpieces = &Table[10];
	ulp=(u_lol*)&Table[0];
	for(int x=0;x<64;x++){
	memset(&CORD[x][0],0,4096);
	}
for(int x=0;x<8;x++)memset(&rays[x][0],0,512);
for(int x=0;x<64;x++)memset(&rays_dir[x][0],0xff,64);
for(int x=0;x<8;x++){
	const u_lol bg=0x8000000000000000;
	for(int xi=0;xi<8;xi++){
	int d=x*8+xi;
	int p=d-8;
	while(p>=0){rays[1][d]|=bg>>p;rays_dir[d][p]=1;  p-=8;}
	//dbgptr_ull(rays[0][d]);

	p=d-9;
	int l1=x-1;
	int l2=xi-1;
	while(l2>=0 && l1>=0){rays[2][d]|=bg>>p;rays_dir[d][p]=2;p-=9;l1--;l2--;}
//dbgptr_ull(rays[1][d]);
	p=d-1;
	l2=xi-1;
	while(l2>=0){rays[3][d]|=bg>>p;rays_dir[d][p]=3;p-=1;l2--;}
//dbgptr_ull(rays[2][d]);
	p=d+7;
	 l1=x+1;
	 l2=xi-1;
	while(l2>=0 && l1<=7){rays[4][d]|=bg>>p;rays_dir[d][p]=4;p+=7;l1++;l2--;}
//dbgptr_ull(rays[3][d]);
	p=d+8;
	while(p<=63){rays[5][d]|=bg>>p;rays_dir[d][p]=5;p+=8;}
//dbgptr_ull(rays[4][d]);
	p=d+9;
	 l1=x+1;
	 l2=xi+1;
	while(l2<=7 && l1<=7){rays[6][d]|=bg>>p;rays_dir[d][p]=6;p+=9;l1++;l2++;}
//dbgptr_ull(rays[5][d]);
	p=d+1;
	l2=xi+1;
	while(l2<=7){rays[7][d]|=bg>>p;rays_dir[d][p]=7;p+=1;l2++;}
//dbgptr_ull(rays[6][d]);
	p=d-7;
	 l1=x-1;
	 l2=xi+1;
	 while(l2<=7 && l1>=0){rays[0][d]|=bg>>p;rays_dir[d][p]=0;p-=7;l1--;l2++;}
	 //dbgptr_ull(rays[7][d]);
	 /*for(int o1=0;o1<8;o1++){
		 for(int o2=0;o2<8;o2++){
		 cout<<(int)rays_dir[d][o1*8+o2]<< " ";
		 }
		 cout<<"\n";
	 }
	 cout<<"\n";*/
	 u_lol pl=rays[1][d]|rays[5][d];
	 dirs[d<<2]=pl;
	 //dbgptr_ull(pl);
	 pl=rays[3][d]|rays[7][d];
	 dirs[(d<<2)+1]=pl;
	 //dbgptr_ull(pl);
	 pl=rays[0][d]|rays[4][d];
	 dirs[(d<<2)+2]=pl;
	 //dbgptr_ull(pl);
	 pl=rays[2][d]|rays[6][d];
	 dirs[(d<<2)+3]=pl;

	 const static u_lol trim6_l4=0x8080808080808080;
	 const static u_lol trim6_r4=0x0101010101010101;
	 const static u_lol trim6_u4=0xff00000000000000;
	 const static u_lol trim6_d4=0x00000000000000ff;
	 const static u_lol trim64=  0xff818181818181ff;
	 u_lol l3=0;
	 for(int o1=0;o1<8;o1++){
		 l3|=rays[o1][d];
	 }
	 QUEEN_ATT_B[d]=l3;
	 if(d==0)      l3^=(trim6_r4|trim6_d4)&l3;
	 else if(d==7 )l3^=(trim6_l4|trim6_d4)&l3;
	 else if(d==56)l3^=(trim6_r4|trim6_u4)&l3;
	 else if(d==63)l3^=(trim6_l4|trim6_u4)&l3;
	 else if(x==0) l3^=(trim6_r4|trim6_d4|trim6_l4)&l3;
	 else if(x==7) l3^=(trim6_r4|trim6_u4|trim6_l4)&l3;
	 else if(xi==0) l3^=(trim6_r4|trim6_d4|trim6_u4)&l3;
	 else if(xi==7) l3^=(trim6_u4|trim6_d4|trim6_l4)&l3;
	 else l3^=trim64&l3;
	 QUEEN_ATT_S[d]=l3;
	 int aa=toBigTable[d];
	 l3=0;
	 u_lol l4=0;
	 for(int x=0;x<8;x++){
		 if(Table[aa+KNIGHT_JUMPS[x]].PCE==0){l3|=bits1[aa+KNIGHT_JUMPS[x]];}
		 if(Table[aa+QUEEN_DIRECTIONS[x]].PCE==0){l4|=bits1[aa+QUEEN_DIRECTIONS[x]];}
	 }
	 KNIGHT_ATT[d]=l3;
	 KING_ATT[d]=l4;
	 //dbgptr_ull(l3);
	 //dbgptr_ull(l4);

	l3=0;l4=0;
	/*for(int x=0;x<8;x++){
	}*/
	l3|=rays[1][d]|rays[3][d]|rays[5][d]|rays[7][d];
	l4|=rays[0][d]|rays[2][d]|rays[4][d]|rays[6][d];
	ROOK_RAYS[d]=l3;
	BISHOP_RAYS[d]=l4;
	//dbgptr_ull(l3);
	//dbgptr_ull(l4);
	if((d&56)+8<64)
	WH_PAWN_ATT[d]=(5ull<<(d+7))&((0xffull<<((d&56)+8)));
	else WH_PAWN_ATT[d]=0;
	if ((d&56)-8>=0)
	BL_PAWN_ATT[d]=(5ull<<(d-9))&((0xffull<<((d&56)-8)));
	else BL_PAWN_ATT[d]=0;
	/*cout << "white\n";
	dbgptr_ull(WH_PAWN_ATT[d]);
	cout << "black\n";
	dbgptr_ull(BL_PAWN_ATT[d]);*/
	}
	for(int x=0;x<8;x++){
	for(u_char xi=0;xi<=255;xi++){
		att_arr[x*256+xi]=mk_mask(xi,x);
		if (xi==255)break;
	}

	}
}
BL_PAWN_ATT[8]=2ull;
/*for(int x=0;x<64;x++){
	dbgptr_ull(BL_PAWN_ATT[x]|WH_PAWN_ATT[x]|1ull<<x);
}*/



/*
for(int o1=0;o1<512;o1++){
dbgptr_ull(dirs[o1]);
}*/
mkl();
/*for (int x=0;x<8;x++){
	for (int xi=0;xi<8;xi++){
		int d=x*8+xi;
		dbgptr_ull(1ull<<d);
		dbgptr_ull(lls[d]);
	}

}*/
u_lol blck,bmsk,amsk,mgc;
for(u_lol b_pos=0;b_pos<64;b_pos++){
	mgc=mics_r13[b_pos];
	for(u_char hc=0;hc<128;hc++){
		for(u_char vc=0;vc<128;vc++){
			bits66(blck,bmsk, amsk,b_pos,hc,vc);
			int ixx=hc*128+vc;
			int inx=((bmsk*mgc)>>51);
			ROOK_MASKS_BLCKS[b_pos][inx]=blck;
		}
	}
}
struct st11{u_lol btm;u_lol blm;};
#include<set>
auto abc=[](st11 const&in1,st11 const&in2){return in1.btm <in2.btm;};
set<st11,decltype(abc)> sull(abc);

for(u_lol b_pos=0;b_pos<64;b_pos++){
	mgc=magics_b_12[b_pos];
	//for (int x = 0; x < 64; x++) { ch_bits[x]=0xff;}
	u_lol b_blck;//;
	u_lol b_blck1= BISHOP_RAYS[b_pos];
	char bit_cnt=popcnt(b_blck1);
	u_lol x_cnt=1ull<<bit_cnt;
	/*for (int x = 0; x < bit_cnt; x++) {
		int a=lsb(b_blck1);
		b_blck1^=1ull<<a;
		//ch_bits[bit_cnt]=a;
	}*/
	for (u_lol x = 0; x < x_cnt; x++) {
		b_blck=BISHOP_RAYS[63-b_pos];
		bits67(b_blck,bmsk, x,b_pos,bit_cnt,nullptr);
		bmsk|=1ull<<b_pos;
		st11 sss{bmsk,b_blck};
		sull.insert(sss);
	}
	int cntt=0;
	for(auto b:sull){
		int inx=(b.btm*mgc)>>52;
		BISHOP_MASKS_BLCKS[b_pos][inx]=b.blm;
		//cout <<cntt << " " << b_pos << " " << inx << "-=-=-";
		//cntt++;
		//dbgptr_ull(BISHOP_RAYS[63-b_pos]);
		//dbgptr_ull(BISHOP_MASKS_BLCKS[b_pos][inx]);

	}
	sull.clear();
}

}

void msatr::initb()
{

	for(int xn=0;xn<64;xn++){
	int lx=toBigTable[xn];
	Table[lx]=EMPTY_mapToTable;
	}

	for(int xn=0;xn<64;xn++){
	int lx=toBigTable[xn];
	for (int xx = 0; xx < 8; xx++) {
		int lp = lx, ori = lx;
		lp += QUEEN_DIRECTIONS[xx];
		u_lol pp=0;
		while(!Table[lp].PCE){

		if(Table[lp+QUEEN_DIRECTIONS[xx]].PCE==0){
			pp|=bits1[lp];
			CORD[63-xn][63-toRegularTable[lp+QUEEN_DIRECTIONS[xx]]]=pp;
			//cout << xn << " " << toRegularTable[lp+QUEEN_DIRECTIONS[xx]] <<"\n";
			//dbgptr_ull(pp);
		}
		KNG_DIRS[xn][toRegularTable[lp]]=QUEEN_DIRECTIONS[xx];
		lp += QUEEN_DIRECTIONS[xx];
		}
		//if(!Table[lx+KNIGHT_JUMPS[xx]].PCE)KNG_DIRS[xn][toRegularTable[lx+KNIGHT_JUMPS[xx]]]=30;
	}
	}

	init_hashes();
	for (int x = 0; x < 8; x++) {
	wpieces[x].clear(); bpieces[x].clear();
	}
	mapToTable bl{ V_PAWN,BLACK,0,0 }, wh{ V_PAWN,WHITE,0,0 };
	mapToArray bla{ V_PAWN, BLACK, 0, 0 }, wha{ V_PAWN,WHITE,0,0 };
	for (int x = 0; x < 8; x++) {
	bl.MAP = bpieces->size();
	Table[toBigTable[8 + x]] = bl;
	bla.MAP = toBigTable[8 + x];
	bpieces[V_PAWN].push_back(bla);
	}
	for (int x = 0; x < 8; x++) {
	wh.MAP = wpieces->size();
	Table[toBigTable[48 + x]] = wh;
	wha.MAP = toBigTable[48 + x];
	wpieces[V_PAWN].push_back(wha);
	}


#define SET_PIECE(p,m,t,a,i,pcs) t.PCE = p;\
	t.MAP = m;\
	Table[toBigTable[i]] = t;\
	a.PCE = p;\
	a.MAP = toBigTable[i];\
	pcs[p].push_back(a);

	SET_PIECE(ROOK, 0, wh, wha, 56, wpieces)
			SET_PIECE(ROOK, 1, wh, wha, 63, wpieces)
			SET_PIECE(ROOK, 0, bl, bla, 0, bpieces)
			SET_PIECE(ROOK, 1, bl, bla, 7, bpieces)

			SET_PIECE(KNIGHT, 0, wh, wha, 57, wpieces)
			SET_PIECE(KNIGHT, 1, wh, wha, 62, wpieces)
			SET_PIECE(KNIGHT, 0, bl, bla, 1, bpieces)
			SET_PIECE(KNIGHT, 1, bl, bla, 6, bpieces)

			SET_PIECE(BISHOP, 0, wh, wha, 58, wpieces)
			SET_PIECE(BISHOP, 1, wh, wha, 61, wpieces)
			SET_PIECE(BISHOP, 0, bl, bla, 2, bpieces)
			SET_PIECE(BISHOP, 1, bl, bla, 5, bpieces)

			SET_PIECE(QUEEN, 0, bl, bla, 3, bpieces)
			SET_PIECE(QUEEN, 0, wh, wha, 59, wpieces)
			bl.STAT = wh.STAT = bla.pad = wha.pad = 3;
	SET_PIECE(C2_KING, 0, bl, bla, 4, bpieces);
	SET_PIECE(C2_KING, 0, wh, wha, 60, wpieces);

	for(int x=0;x<21;x++)Table[x].MAP=x;
	blpieces[V_PAWN].NEXT = 31;
	Table[31].PREV = 11;
	Table[31].NEXT = 32;
	Table[32].PREV = 31;
	Table[32].NEXT = 33;
	Table[33].PREV = 32;
	Table[33].NEXT = 34;
	Table[34].PREV = 33;
	Table[34].NEXT = 35;
	Table[35].PREV = 34;
	Table[35].NEXT = 36;
	Table[36].PREV = 35;
	Table[36].NEXT = 37;
	Table[37].PREV = 36;
	Table[37].NEXT = 38;
	Table[38].PREV = 37;
	Table[38].NEXT = 0;

	blpieces[ROOK].NEXT = 21;
	Table[21].PREV = 13;
	Table[21].NEXT = 28;
	Table[28].PREV = 21;
	Table[28].NEXT = 0;
	blpieces[KNIGHT].NEXT = 22;
	Table[22].PREV = 15;
	Table[22].NEXT = 27;
	Table[27].PREV = 22;
	Table[27].NEXT = 0;
	blpieces[BISHOP].NEXT = 23;
	Table[23].PREV = 14;
	Table[23].NEXT = 26;
	Table[26].PREV = 23;
	Table[26].NEXT = 0;
	blpieces[QUEEN].NEXT = 24;
	Table[24].PREV = 16;
	Table[24].NEXT = 0;
	blpieces[C2_KING].NEXT = 25;
	Table[25].PREV = 17;
	Table[25].NEXT = 0;

	wlpieces[V_PAWN].NEXT = 81;
	Table[81].PREV = 2;
	Table[81].NEXT = 82;
	Table[82].PREV = 81;
	Table[82].NEXT = 83;
	Table[83].PREV = 82;
	Table[83].NEXT = 84;
	Table[84].PREV = 83;
	Table[84].NEXT = 85;
	Table[85].PREV = 84;
	Table[85].NEXT = 86;
	Table[86].PREV = 85;
	Table[86].NEXT = 87;
	Table[87].PREV = 86;
	Table[87].NEXT = 88;
	Table[88].PREV = 87;
	Table[88].NEXT = 0;

	wlpieces[ROOK].NEXT = 91;
	Table[91].PREV = 4;
	Table[91].NEXT = 98;
	Table[98].PREV = 91;
	Table[98].NEXT = 0;
	wlpieces[KNIGHT].NEXT = 92;
	Table[92].PREV = 6;
	Table[92].NEXT = 97;
	Table[97].PREV = 92;
	Table[97].NEXT = 0;
	wlpieces[BISHOP].NEXT = 93;
	Table[93].PREV = 5;
	Table[93].NEXT = 96;
	Table[96].PREV = 93;
	Table[96].NEXT = 0;
	wlpieces[QUEEN].NEXT = 94;
	Table[94].PREV = 7;
	Table[94].NEXT = 0;
	wlpieces[C2_KING].NEXT = 95;
	Table[95].PREV = 8;
	Table[95].NEXT = 0;

	bsinf.other=&wsinf;
	bsinf.fhashes=&bhashes_;
	bsinf.shashes=&whashes_;
	bsinf.fpieces=blpieces;
	bsinf.spieces=wlpieces;
	bsinf.clr=BLACK;
	bsinf.otclr=WHITE;

	wsinf.other=&bsinf;
	wsinf.fhashes=&whashes_;
	wsinf.shashes=&bhashes_;
	wsinf.fpieces=wlpieces;
	wsinf.spieces=blpieces;
	wsinf.clr=WHITE;
	wsinf.otclr=BLACK;

}

void msatr::assert_consist()
{
	return;
}

bool msatr::retBackPiece(vector<mapToArray>(&pieces)[8]) {

	mapToArray pma = pieces[0].back();
	pieces[0].pop_back();
	mapToTable mtt;
	int lMAP = pma.MAP;
	mtt.PCE = pma.PCE;
	mtt.CLR = pma.CLR;
	mtt.STAT = 0;
	Table[lMAP] = mtt;
	pieces[mtt.PCE].push_back(pma);
	return true;
}
template <int CLR_P>
bool msatr::retBackPiece_L () {

	mapToTable lmpt = takenPieces.back();
	u_lol j=lmpt.MAP;
	if constexpr(CLR_P==WHITE){
	wPCS_btARR[lmpt.PCE]^=bits1[j];
	wPCS_BITS^=bits1[j];
	}else{
	bPCS_btARR[lmpt.PCE]^=bits1[j];
	bPCS_BITS^=bits1[j];
	}


	takenPieces.pop_back();
	//Table[lmpt.PREV].NEXT = lmpt.MAP;
	//Table[lmpt.NEXT].PREV = lmpt.MAP;
	Table[lmpt.MAP] = lmpt;

	return true;
}
void msatr::prom(vector<mapToArray>(&pieces)[8], int PCE, int PR_PCE, int MAP) {
	int x = 0;
	while (x < pieces[PCE].size()) {
	if (pieces[PCE][x].MAP == MAP) {
		mapToArray l1 = pieces[PCE][x];
		pieces[PCE].erase(pieces[PCE].begin() + x);
		l1.PCE = PR_PCE;
		pieces[PR_PCE].push_back(l1);
		Table[MAP].PCE = PR_PCE;
		goto uiui;
		break;

	}
	x++;
	}
uiui:;

}
//########################################################
void msatr::prom_L(u_lol FR_POS_,/*u_lol TO_POS_,*/u_lol PROM_PCE){
	mapToTable lmpt=Table[FR_POS_];
	takenPieces.push_back(lmpt);
	Table[FR_POS_].PCE=PROM_PCE;
	//Table[lmpt.PREV].NEXT=lmpt.NEXT;
	//Table[lmpt.NEXT].PREV=lmpt.PREV;

	//Table[FR_POS_].PCE=PROM_PCE;
	//u_lol t1 = sdinf.fpieces[PROM_PCE].NEXT;
	//sdinf.fpieces[PROM_PCE].NEXT=FR_POS_;

	//Table[FR_POS_].PREV=sdinf.fpieces[PROM_PCE].MAP;
	//Table[FR_POS_].NEXT=t1;
	//Table[t1].PREV=FR_POS_;
		//printt();
}
//######################################################
void msatr::undoProm_L(u_lol FR_POS_,/*u_lol TO_POS_,*/u_lol PROM_PCE){
	//mapToTable lmpt=Table[FR_POS_];
	mapToTable ompt=takenPieces.back();
	takenPieces.pop_back();
	//Table[lmpt.PREV].NEXT=lmpt.NEXT;
	//Table[lmpt.NEXT].PREV=lmpt.PREV;
	//Table[ompt.PREV].NEXT=FR_POS_;
	//Table[ompt.NEXT].PREV=FR_POS_;

	Table[FR_POS_]=ompt;
		//printt();
}

//###########################################################################
u_lol msatr::king_XRAY_Safety(int pos,  u_lol mask) {
			/*u_lol rr = BISHOP_RAYS[63-pos];
		u_lol rp = (rr & mask)|(1ull<<pos);
		rp *= magics_b_12[pos];
		rp >>= 52;
		return BISHOP_MASKS_BLCKS[pos][rp];*/
/*
				 u_lol rr = BISHOP_RAYS[63-pos];
				 u_lol rp = (rr & mask)|(1ull<<pos);
				 rp *= magics_b_12[pos];
				 rp >>= 52;
				 u_lol us_xrat = BISHOP_MASKS_BLCKS[pos][rp];
				 return  us_xrat;*/

	u_lol pm_3,pm_4,mmask=0x0101010101010101;
	u_lol rm_3,rm_4;
	u_lol rm;
	int kx=63-pos;
	int kps=(7-(kx &7))*256;
	int kp=kx<<2;

	pm_3=dirs[kp+2];
	pm_4=dirs[kp+3];
	rm_3=pm_3&mask;
	rm_4=pm_4&mask;

rm=(rm_3*mmask)>>56;
rm=att_arr[rm + kps];
rm|=rm<<8;
rm|=rm<<16;
rm|=rm<<32;
pm_3&=rm;

rm=(rm_4*mmask)>>56;
rm=att_arr[rm + kps];
rm|=rm<<8;
rm|=rm<<16;
rm|=rm<<32;
pm_4&=rm;

return pm_3|pm_4;
}

//###########################################################################
u_lol msatr::king_PLUS_Safety(int pos, u_lol mask1) {
	u_lol pm_1,pm_2,mmask=0x0101010101010101;
	u_lol rm_1,rm_2;
	u_lol rm;
	int kx=63-pos;
		int kps=(7-(kx &7))*256;
int kp=kx<<2;
		pm_1=dirs[kp];
	pm_2=dirs[kp+1];

	rm_1=pm_1&mask1;
	rm_2=pm_2&mask1;


rm=(rm_2>>((63-kx)&56));
rm=att_arr[rm + kps];
rm|=rm<<8;
rm|=rm<<16;
rm|=rm<<32;
pm_2&=rm;

rm_1=rm_1>>((7-(kx &7)));
rm_1=rm_1*0x8040201008040201;
rm_1=rm_1>>56;
rm_1=att_arr[rm_1 + (kx>>3)*256];
rm_1=rm_1*0x8040201008040201;
rm_1&=0x8080808080808080;
rm_1=rm_1>>(kx &7);

return pm_2|rm_1;
}


//###########################################################################
array<u_lol, 2> msatr::kingRSafety(int pos, u_lol mask1, u_lol mask2) {
	u_lol pm_1,pm_2,pm_3,pm_4,mmask=0x0101010101010101;
	u_lol rm_1,rm_2,rm_3,rm_4;
	u_lol rm;
	int kx=63-pos;
		int kps=(7-(kx &7))*256;
int kp=kx<<2;
		pm_1=dirs[kp];
	pm_2=dirs[kp+1];
	pm_3=dirs[kp+2];
	pm_4=dirs[kp+3];
	rm_1=pm_1&mask1;
	rm_2=pm_2&mask1;
	rm_3=pm_3&mask2;
	rm_4=pm_4&mask2;

rm=(rm_2>>((63-kx)&56));
rm=att_arr[rm + kps];
rm|=rm<<8;
rm|=rm<<16;
rm|=rm<<32;
pm_2&=rm;

rm=(rm_3*mmask)>>56;
rm=att_arr[rm + kps];
rm|=rm<<8;
rm|=rm<<16;
rm|=rm<<32;
pm_3&=rm;

rm=(rm_4*mmask)>>56;
rm=att_arr[rm + kps];
rm|=rm<<8;
rm|=rm<<16;
rm|=rm<<32;
pm_4&=rm;

rm_1=rm_1>>((7-(kx &7)));
rm_1=rm_1*0x8040201008040201;
rm_1=rm_1>>56;
rm_1=att_arr[rm_1 + (kx>>3)*256];
rm_1=rm_1*0x8040201008040201;
rm_1&=0x8080808080808080;
rm_1=rm_1>>(kx &7);

return {pm_2|rm_1,pm_3|pm_4};
}

u_lol msatr::attMaskStar(u_lol pos,u_lol mask){
	u_lol rr = BISHOP_RAYS[63-pos];
	u_lol rp = (rr & mask)|(1ull<<pos);
	//rp *= mics_r[a];
	rp *= magics_b_12[pos];
	rp >>= 52;
	u_lol a2 = BISHOP_MASKS_BLCKS[pos][rp];

	 rr = ROOK_RAYS[63-pos];
	 rp = (rr & mask)|(1ull<<pos);
	//rp *= mics_r[a];
	rp *= mics_r13[pos];
	rp >>= 51;
	rr &= ROOK_MASKS_BLCKS[pos][rp];
	return a2|rr;
}
template <int CLR_ATT ,int CLR_P>
array<u_lol,2> msatr::kingBSafety(u_lol pos,u_lol mask){
	u_lol pm_1,pm_2,pm_3,pm_4,mmask=0x0101010101010101;
	u_lol rm_1,rm_2,rm_3,rm_4;
	u_lol rm;
	int kx=toRegularTable[pos];
		int kps=(7-(kx &7))*256;
int kp=kx<<2;
		pm_1=dirs[kp];
	pm_2=dirs[kp+1];
	pm_3=dirs[kp+2];
	pm_4=dirs[kp+3];
	rm_1=pm_1&mask;
	rm_2=pm_2&mask;
	rm_3=pm_3&mask;
	rm_4=pm_4&mask;


rm=(rm_2>>((63-kx)&56));
rm=att_arr[rm + kps];
rm|=rm<<8;
rm|=rm<<16;
rm|=rm<<32;
pm_2&=rm;

rm=(rm_3*mmask)>>56;
rm=att_arr[rm + kps];
rm|=rm<<8;
rm|=rm<<16;
rm|=rm<<32;
pm_3&=rm;

rm=(rm_4*mmask)>>56;
rm=att_arr[rm + kps];
rm|=rm<<8;
rm|=rm<<16;
rm|=rm<<32;
pm_4&=rm;

rm_1=rm_1>>((7-(kx &7)));
rm_1=rm_1*0x8040201008040201;
rm_1=rm_1>>56;
rm_1=att_arr[rm_1 + (kx>>3)*256];
rm_1=rm_1*0x8040201008040201;
rm_1&=0x8080808080808080;
rm_1=rm_1>>(kx &7);

return {pm_2|rm_1,pm_3|pm_4};
}

void msatr::bits67(u_lol &b_blck,u_lol& bmsk, u_lol& x, int pos, u_char bit_cnt, u_char *b_map){
	u_lol f=0;
	//cout <<pos << " ;";
	//cout <<x << "---BISHOP_RAYS---";
	//dbgptr_ull(BISHOP_RAYS[pos]);
	for (int xb = 0; xb < bit_cnt; ++xb) {
		//cout  << "---b_blck---";
		//dbgptr_ull(b_blck);
		int a=lsb(b_blck);
		u_lol b1=1ull<<a;
		if(x&(1ull<<xb)){f|=b1;}
		b_blck^=b1;
		//cout << "---f---";
		//dbgptr_ull(f);

		//if(b_map[a]!=0xff)
		//if(x)
	}
	bmsk=f;
	b_blck=king_XRAY_Safety(pos,bmsk);
	//cout <<x << "--0--";
	//dbgptr_ull(b_blck);
	//dbgptr_ull(bmsk);
	/*int h_rem=7-(pos&7);
	int v_rem=7-(pos>>3);
	int h_pos=7-h_rem;
	int v_pos=7-v_rem;
	u_lol lr=(static_cast<u_lol>(iver)*0x0101010101010101)&0x0102040810204080;

	u_lol rl=static_cast<u_lol>(iver)*0x0101010101010101;//)|(static_cast<u_lol>(iver&1)));//&0x8040201008040201;
	rl|=rl>>8;
	rl|=rl>>16;
	rl|=rl>>32;

	rl&=0x8040201008040201;
	cout<<"--0--";

	dbgptr_ull(static_cast<u_lol>(iver));
	dbgptr_ull(lr);

	dbgptr_ull(static_cast<u_lol>(iver)*0x0101010101010101);
	dbgptr_ull(rl);*/
}

//######################################################
void msatr::bits66(u_lol &blck_mask,u_lol& bit_mask, u_lol& att_mask, int pos, u_char ihor, u_char iver) {
int h_rem=7-(pos&7);
int v_rem=7-(pos>>3);
int h_pos=7-h_rem;
int v_pos=7-v_rem;
u_lol testb = static_cast<u_lol>(ihor) & 0x7f;
testb |= (static_cast<u_lol>(iver) & 0x7f) << 7;

//cout << pos << " h pos: " << h_pos << " v pos: " << v_pos << " h rem: " << h_rem << " v rem: " << v_rem << "\n";
u_char fc = ihor & ~(0xffu<<h_pos);
//dbgptr_uch(ihor);
//dbgptr_uch(fc);
fc |= (ihor & (~(0xffu << h_rem) )<< h_pos)<<1;
//dbgptr_uch(fc);
//dbgptr_uch(iver);

u_char sc = iver & ~(0xffu << v_pos);
//dbgptr_uch(sc);
sc |= (iver & (~(0xffu << v_rem)) << v_pos )<<1;
//dbgptr_uch(sc);
u_lol gg = (u_lol)fc << (v_pos << 3);
gg |= ((((u_lol)(sc&0xfe) * 0x0102040810204080)|((u_lol)(sc&1)<<7)) & 0x8080808080808080) >> h_rem;
 att_mask = king_PLUS_Safety(pos, gg);
 bit_mask=gg;
 bit_mask|=1ull<<pos;
//dbgptr_ull(gg);
//dbgptr_ull(att_mask);
blck_mask=att_mask|(1ull<<pos);// | (1ull<<(pos-14))| (1ull<<(pos-18))*/;
u_lol ix = (blck_mask & (0x00000000000000ffull << (v_pos << 3))) >> 8;
while (ix & blck_mask) {
	blck_mask |= ix;
	ix >>= 8;
}
 ix = (blck_mask & (0x00000000000000ffull << (v_pos << 3))) << 8;
while (ix & blck_mask) {
	blck_mask |= ix;
	ix <<= 8;
}
//dbgptr_ull(blck_mask);
//u_lol lb_m=(0x00000000000000ffull << (v_pos << 3));
//cout<< "e---\n";
//dbgptr_ull(((u_lol)sc) );
//dbgptr_ull(0x0102040810204080);
//dbgptr_ull(0x8040201008040201);
//dbgptr_ull(((u_lol)sc) * 0x0102040810204080);
//dbgptr_ull(((u_lol)sc) * 0x8040201008040201);
//dbgptr_ull(gg);

u_lol vt = (gg & (0x00000000000000ffull << (v_pos << 3))) >> (v_pos << 3);
//dbgptr_ull(vt);
u_lol vtr = vt & ~(0xffffffffffffffffull << h_pos);
u_lol maskh = (~(0xffffffffffffffffull << h_rem) << (h_pos + 1));
//cout << "msk--\n";
//dbgptr_ull(maskh);
//dbgptr_ull((vt & maskh) >> 1);
//cout << "first mask--\n";
//dbgptr_ull(vtr);
vtr |= ((vt & maskh ) >> 1);
//cout << "sec mask--\n";
//dbgptr_ull(vtr);
//dbgptr_ull(in);
u_lol hrr = gg >> (pos & 7);
//cout << "Vert--------\n";
//dbgptr_ull(hrr);
hrr &= 0x0101010101010101;
hrr = (hrr * 0x0102040810204080);
//cout << "rev--";
//dbgptr_ull(hrr);
hrr = hrr >> 56;
//cout << "Vert->h-\n";
//dbgptr_ull(hrr);
//cout << "f mask--\n";
//dbgptr_ull(~(0xffffffffffffffffull << v_pos));
vtr |= (hrr & ~(0xffffffffffffffffull << v_pos)) << 7;
//cout << "Ins 3---\n";
//dbgptr_ull(vtr);
//cout << "mask 2--\n";
//dbgptr_ull((~(0xffffffffffffffffull << v_rem) << v_pos ));
vtr |= ((hrr & (~(0xffffffffffffffffull << v_rem) << (v_pos+1))) << 6);

if (vtr != testb) {
	cout << "------------:::\n";
dbgptr_ull(vtr);
dbgptr_ull(testb);
}
//cout << "eof--\n";
}
//######################################################
template <int CLR_ATT ,int CLR_P>
array<u_lol,2> msatr::kingXSafety(u_lol pos){
	u_lol their_ks_r=0,their_ks_b=0;
	for (int xx = 0; xx < 4; xx++) {
	int lp = pos;
	lp += ROOK_DIRECTIONS[xx];
	while(Table[lp].PCE==EMPTY ||Table[lp].CLR==CLR_ATT){their_ks_r|=bits1[lp]; lp += ROOK_DIRECTIONS[xx];}
	if(Table[lp].CLR==CLR_P)their_ks_r|=bits1[lp];
	}

	for (int xx = 0; xx < 4; xx++) {
	int lp = pos;
	lp += BISHOP_DIRECTIONS[xx];
	while(Table[lp].PCE==EMPTY ||Table[lp].CLR==CLR_ATT){their_ks_b|=bits1[lp]; lp += BISHOP_DIRECTIONS[xx];}
	if(Table[lp].CLR==CLR_P)their_ks_b|=bits1[lp];
	}
return {their_ks_r,their_ks_b};
}
//#######################################################
template<int CLR_P>
int msatr::king_ALL_Safety()
{

	u_lol blck;
	int ourk, thrk;
	constexpr u_lol &us = CLR_P==WHITE?  msatr::wPCS_BITS : msatr::bPCS_BITS;
	constexpr u_lol &them = CLR_P==WHITE? msatr::bPCS_BITS : msatr::wPCS_BITS;
	constexpr u_lol *us_ARR=CLR_P==WHITE? &msatr::wPCS_btARR[0]:&msatr::bPCS_btARR[0];
	constexpr u_lol *them_ARR=CLR_P==WHITE? &msatr::bPCS_btARR[0]:&msatr::wPCS_btARR[0];
	if constexpr (CLR_P == WHITE) {
	  ourk =  lsb(wPCS_btARR[C2_KING]);
	  thrk =  lsb(bPCS_btARR[C2_KING]);
	  if(WH_PAWN_ATT[ourk]&them_ARR[V_PAWN])return KING_VAL;
	} else {
	  ourk = lsb(bPCS_btARR[C2_KING]);
	  if(BL_PAWN_ATT[ourk]&them_ARR[V_PAWN])return KING_VAL;
	  thrk = lsb(wPCS_btARR[C2_KING]);
	}

	u_lol rr = BISHOP_RAYS[63 - ourk];
	u_lol rp = (rr & (us|them)) | (1ull << ourk);
	rp *= magics_b_12[ourk];
	rp >>= 52;
	u_lol a2 = BISHOP_MASKS_BLCKS[ourk][rp];

	rr = ROOK_RAYS[63 - ourk];
	rp = (rr & (us|them)) | (1ull << ourk);
	rp *= mics_r13[ourk];
	rp >>= 51;
	rr &= ROOK_MASKS_BLCKS[ourk][rp];
	//return a2 | rr;
	//auto [us_ksr, us_ksb] = kingRSafety(ourk, us|them, us|them);
	u_lol us_ksr = rr;
	u_lol us_ksb = a2;
	if(2){}
	u_lol thr_PLUS_SLID = them_ARR[ROOK] | them_ARR[QUEEN];
	u_lol thr_XRAY_SLID = them_ARR[BISHOP] | them_ARR[QUEEN];

if(us_ksr&thr_PLUS_SLID)return KING_VAL;
if(us_ksb&thr_XRAY_SLID)return KING_VAL;

//_____________________________________________________ knight
	u_lol knight_thrt=KNIGHT_ATT[63-ourk];
	if(knight_thrt&them_ARR[KNIGHT])return KING_VAL;

	if(1ull<<ourk &KING_ATT[63-thrk])return  KING_VAL;

return 0;
}

//######################################################
template <int CLR_P,int CLR_ATT>
int  msatr::kingSafety(u_int pos) {
	/*u_lol us, them;
	if (CLR_P == WHITE) {
		us = wPCS_BITS; them = bPCS_BITS;
	}else{them = wPCS_BITS;us = bPCS_BITS; }
	*/
	if constexpr ( CLR_P==BLACK){
	if(Table[pos+9].CLR==CLR_ATT && Table[pos+9].PCE==V_PAWN)return KING_VAL;
	if(Table[pos+11].CLR==CLR_ATT && Table[pos+11].PCE==V_PAWN)return KING_VAL;
	}else{
	if(Table[pos-9].CLR==CLR_ATT && Table[pos-9].PCE==V_PAWN)return KING_VAL;
	if(Table[pos-11].CLR==CLR_ATT && Table[pos-11].PCE==V_PAWN)return KING_VAL;
	}
	//u_lol kk=king_XRAY_Safety(pos,)
	for (int xx = 0; xx < 4; xx++) {
	int lp = pos;
	lp += BISHOP_DIRECTIONS[xx];
	while(ulp[lp]==0) lp += BISHOP_DIRECTIONS[xx];
	if(Table[lp].CLR == CLR_ATT) {
		if(Table[lp].PCE==BISHOP || Table[lp].PCE==QUEEN) return KING_VAL;
	}
	}
	for (int xx = 0; xx < 4; xx++) {
	int lp = pos;
	lp += ROOK_DIRECTIONS[xx];
	while(ulp[lp]==0) lp += ROOK_DIRECTIONS[xx];
	if(Table[lp].CLR == CLR_ATT) {
		if(Table[lp].PCE==ROOK || Table[lp].PCE==QUEEN) return KING_VAL;
	}
	}

	for (int xx = 0; xx < 8; xx++) {
	int lp = pos;
	lp += KNIGHT_JUMPS[xx];
	if(Table[lp].CLR == CLR_ATT && Table[lp].PCE==KNIGHT) return KING_VAL;
	if(Table[pos+QUEEN_DIRECTIONS[xx]].CLR == CLR_ATT && Table[pos+QUEEN_DIRECTIONS[xx]].PCE==C2_KING) return KING_VAL;
	}
	return 0;
}
//######################################################
template <int CLR_P,int CLR_ATT>
int  msatr::assert_kingSafety(u_int pos) {
if constexpr(!ASSERT_KING_SAFETY)return 0;
	if constexpr ( CLR_P==BLACK){
	if(Table[pos+9].CLR==CLR_ATT && Table[pos+9].PCE==V_PAWN)return KING_VAL;
	if(Table[pos+11].CLR==CLR_ATT && Table[pos+11].PCE==V_PAWN)return KING_VAL;
	}else{
	if(Table[pos-9].CLR==CLR_ATT && Table[pos-9].PCE==V_PAWN)return KING_VAL;
	if(Table[pos-11].CLR==CLR_ATT && Table[pos-11].PCE==V_PAWN)return KING_VAL;
	}

	for (int xx = 0; xx < 4; xx++) {
	int lp = pos;
	lp += BISHOP_DIRECTIONS[xx];
	while(ulp[lp]==0) lp += BISHOP_DIRECTIONS[xx];
	if(Table[lp].CLR == CLR_ATT) {
		if(Table[lp].PCE==BISHOP || Table[lp].PCE==QUEEN) return KING_VAL;
	}
	}
	for (int xx = 0; xx < 4; xx++) {
	int lp = pos;
	lp += ROOK_DIRECTIONS[xx];
	while(ulp[lp]==0) lp += ROOK_DIRECTIONS[xx];
	if(Table[lp].CLR == CLR_ATT) {
		if(Table[lp].PCE==ROOK || Table[lp].PCE==QUEEN) return KING_VAL;
	}
	}

	for (int xx = 0; xx < 8; xx++) {
	int lp = pos;
	lp += KNIGHT_JUMPS[xx];
	if(Table[lp].CLR == CLR_ATT && Table[lp].PCE==KNIGHT) return KING_VAL;
	if(Table[pos+QUEEN_DIRECTIONS[xx]].CLR == CLR_ATT && Table[pos+QUEEN_DIRECTIONS[xx]].PCE==C2_KING) return KING_VAL;
	}
	return 0;
}

//###############################################################
template <int CLR_ATT,int CLR_P>
int msatr::p_XKingSafety(u_lol posk, u_lol posp, u_lol post, u_lol ksfr,u_lol ksfb){
u_lol* cB_MSK,bit1,wpcs;
if constexpr(CLR_ATT==WHITE){
	cB_MSK=&wPCS_btARR[0];
	wpcs=wPCS_BITS;
}else {
	cB_MSK=&bPCS_btARR[0];
	wpcs=bPCS_BITS;
}
	u_lol lpce=Table[post].PCE;

	if(lpce==KNIGHT){
	if(bits1[posk]&KNIGHT_ATT[toRegularTable[post]])return KING_VAL;
		/*int rr=post-posk;
	for (int xi = 0; xi < 8; xi++) {
		if(rr==KNIGHT_JUMPS[xi])return KING_VAL;
		//u_lol d=post+KNIGHT_JUMPS[xi];
		//if(Table[d].PCE == C2_KING &&Table[d].CLR==CLR_P)return KING_VAL;
	}*/
	}
	 else if(lpce==V_PAWN){
	int d=post-posk;
	 if constexpr (CLR_P==BLACK){
		 //if(abs(d)<12){
		 if(d==9 || d==11)return KING_VAL;
		 //if(Table[posk+9].CLR==CLR_ATT && Table[posk+9].PCE==V_PAWN)return KING_VAL;
		 //if(Table[posk+11].CLR==CLR_ATT && Table[posk+11].PCE==V_PAWN)return KING_VAL;//}
	 }else{
		 //if(abs(d)<12){
		 if(d==-9 || d==-11)return KING_VAL;
		 //if(Table[posk-9].CLR==CLR_ATT && Table[posk-9].PCE==V_PAWN)return KING_VAL;
		 //if(Table[posk-11].CLR==CLR_ATT && Table[posk-11].PCE==V_PAWN)return KING_VAL;//}
	 }
	 }else if (lpce==C2_KING){
			if(KING_ATT[toRegularTable[posk]]&bits1[post])return KING_VAL;
	 }
	 else if((bit1=(bits1[post]&ksfr))){
	//int diry=KNG_DIRS[toRegularTable[posk]][toRegularTable[post]];
	//if(diry){
	//sx=true;
			//dbgptr_ull(bit1);
			//dbgptr_ull(cB_MSK[ROOK]);
			//dbgptr_ull(cB_MSK[QUEEN]);
			//dbgptr_ull(CORD[toRegularTable[post]][toRegularTable[posk]]);
		if(bit1&cB_MSK[ROOK] || bit1 &cB_MSK[QUEEN]){
		if(!(63-CORD[toRegularTable[post]][63-toRegularTable[posk]]&(wPCS_BITS|bPCS_BITS))){return KING_VAL;}

		}


		  /*  if(Table[posk+diry].PCE==C2_KING)return KING_VAL;
		u_lol poss=diry+posk;
		while(ulp[poss]==0){ poss += diry;}
		if(Table[poss].CLR==CLR_ATT){
		int tpcr=Table[poss].PCE;
		if(tpcr==QUEEN){return KING_VAL;}
		diry=abs(diry);
		if((diry==1||diry==10)&&tpcr==ROOK){return KING_VAL;}
		if((diry==9||diry==11)&&tpcr==BISHOP){return KING_VAL;}
	   // }*/
		}else if((bit1=(bits1[post]&ksfb))){
	if(bit1&cB_MSK[BISHOP] || bit1 &cB_MSK[QUEEN]){
	if(!(63-CORD[toRegularTable[post]][63-toRegularTable[posk]]&(wPCS_BITS|bPCS_BITS))){return KING_VAL;}
	}

		//if(KING_ATT[toRegularTable[post]]&bits1[post])return KING_VAL;
		}
	/*u_lol apcs;
	if constexpr(CLR_ATT==WHITE){
	apcs=bPCS_BITS;
}else {
	apcs=wPCS_BITS;
}*/

	 if((bit1=(wpcs&ksfr))){
			 /*if(panic_dbg){
			 dbgptr_ull(bit1);
			 dbgptr_ull(cB_MSK[ROOK]);
			 dbgptr_ull(cB_MSK[QUEEN]);
		 }*/
	 u_lol bn=(bit1&cB_MSK[ROOK]) | (bit1 &cB_MSK[QUEEN]);
	 if(bn){
			 /*if(panic_dbg){
dbgptr_ull(bn);
dbgptr_ull(CORD[63-bitScanForward(bn)][toRegularTable[posk]]);
dbgptr_ull((CORD[63-bitScanForward(bn)][toRegularTable[posk]]&(wPCS_BITS|bPCS_BITS)));
		 }*/
		 agn:
		 u_lol pgp=bitScanForward(bn);
		 if(!(CORD[pgp][63-toRegularTable[posk]]&(wPCS_BITS|bPCS_BITS)))return KING_VAL;
		 else{
				 //if(panic_dbg){dbgptr_ull(bn);}
			 bn^=1ULL<<pgp;
			 //if(panic_dbg){dbgptr_ull(bn);}
			 if(bn)goto agn;
		 }
	 }
		 /*int dirx=KNG_DIRS[toRegularTable[posk]][toRegularTable[posp]];

		if(Table[posk+dirx].PCE==C2_KING)return KING_VAL;
		u_lol poss=dirx+posk;
		while( ulp[poss]==0){ poss += dirx;}
		if(Table[poss].CLR==CLR_ATT){
		int tpcr=Table[poss].PCE;
		if(tpcr==QUEEN)return KING_VAL;
		dirx=abs(dirx);
		if((dirx==1||dirx==10)&&tpcr==ROOK)return KING_VAL;
		if((dirx==9||dirx==11)&&tpcr==BISHOP)return KING_VAL;
	}*/
	 }

	 if((bit1=(wpcs&ksfb))){
	 u_lol bn=(bit1&cB_MSK[BISHOP]) | (bit1 &cB_MSK[QUEEN]);
	 if(bn){
	 //if(bit1&cB_MSK[BISHOP] || bit1 &cB_MSK[QUEEN]){
			   /* if(panic_dbg){
	 dbgptr_ull(bit1);
	 dbgptr_ull(cB_MSK[ROOK]);
	 dbgptr_ull(cB_MSK[QUEEN]);
	 }*/
		 //u_lol bn=(bit1&cB_MSK[BISHOP]) | (bit1 &cB_MSK[QUEEN]);
	 /* if(panic_dbg){
		  dbgptr_ull(bn);
		  dbgptr_ull(CORD[63-bitScanForward(bn)][toRegularTable[posk]]);
		  dbgptr_ull((CORD[63-bitScanForward(bn)][toRegularTable[posk]]&(wPCS_BITS|bPCS_BITS)));
	  }*/
	  agn1:
		 u_lol pgp=bitScanForward(bn);
		 if(!(CORD[pgp][63-toRegularTable[posk]]&(wPCS_BITS|bPCS_BITS)))return KING_VAL;
		  else{
				  //if(panic_dbg){dbgptr_ull(bn);}
			 bn^=1ULL<<pgp;
			 //if(panic_dbg){ dbgptr_ull(bn); }
			 if(bn)goto agn1;
		 }
	 }
	 }
		return 0;
	}


//###############################################################
template <int CLR_ATT,int CLR_P>
int msatr::p_KingSafety(u_lol posk, u_lol posp, u_lol post, u_lol ksft){


	//bool sx=false;
	u_lol lpce=Table[post].PCE;

	if(lpce==KNIGHT){
	if(bits1[posk]&KNIGHT_ATT[toRegularTable[post]])return KING_VAL;
		/*int rr=post-posk;
	for (int xi = 0; xi < 8; xi++) {
		if(rr==KNIGHT_JUMPS[xi])return KING_VAL;
		//u_lol d=post+KNIGHT_JUMPS[xi];
		//if(Table[d].PCE == C2_KING &&Table[d].CLR==CLR_P)return KING_VAL;
	}*/
	}
	 else if(lpce==V_PAWN){
	int d=post-posk;
	 if constexpr (CLR_P==BLACK){
		 //if(abs(d)<12){
		 if(d==9 || d==11)return KING_VAL;
		 //if(Table[posk+9].CLR==CLR_ATT && Table[posk+9].PCE==V_PAWN)return KING_VAL;
		 //if(Table[posk+11].CLR==CLR_ATT && Table[posk+11].PCE==V_PAWN)return KING_VAL;//}
	 }else{
		 //if(abs(d)<12){
		 if(d==-9 || d==-11)return KING_VAL;
		 //if(Table[posk-9].CLR==CLR_ATT && Table[posk-9].PCE==V_PAWN)return KING_VAL;
		 //if(Table[posk-11].CLR==CLR_ATT && Table[posk-11].PCE==V_PAWN)return KING_VAL;//}
	 }
	 }
/*
	 int p1;
	 if(( p1=rays_dir[toRegularTable[ posk]][toRegularTable [post]])>=0){
	 u_lol rd;
	 if constexpr (CLR_ATT==BLACK){
		 u_lol ray=rays[p1][toRegularTable[ posk]];
		 u_lol all_pcs=(bPCS_BITS|wPCS_BITS);
		 if((ray&bPCS_BITS)){
		 rd=ray&all_pcs;
		 //dbgptr_ull(rd);
		 unsigned long r;
		 if(p1<=3){
			 _BitScanForward64(&r,rd);
			 //u_lol ii=(u_lol)1 << r;
			 //if(ii&bPCS_btARR[QUEEN]){return KING_VAL;}
			 //if(p1&1){if(ii&bPCS_btARR[ROOK]){return KING_VAL;}}
			 //else if(ii&bPCS_btARR[BISHOP]){return KING_VAL;}

		 }
		 else{
			 _BitScanReverse64(&r,rd);

		 }
		 //(*p_bsfr[p1])(&r,rd);
		 u_lol ii=(u_lol)1 << r;
		 if(ii&bPCS_btARR[QUEEN]){return KING_VAL;}
		 if(p1&1){if(ii&bPCS_btARR[ROOK]){return KING_VAL;}}
		 else if(ii&bPCS_btARR[BISHOP]){return KING_VAL;}
		 }
	 }else{
		 u_lol ray=rays[p1][toRegularTable[ posk]];
		 if((ray&wPCS_BITS)){
		 u_lol all_pcs=(bPCS_BITS|wPCS_BITS);
		 rd=ray&all_pcs;
		 unsigned long r;
		 if(p1<=3){
			 _BitScanForward64(&r,rd);
			 //u_lol ii=(u_lol)1 << r;
			 //if(ii&bPCS_btARR[QUEEN]){return KING_VAL;}
			 //if(p1&1){if(ii&bPCS_btARR[ROOK]){return KING_VAL;}}
			 //else if(ii&bPCS_btARR[BISHOP]){return KING_VAL;};

		 }
		 else{
			 _BitScanReverse64(&r,rd);
		 }
		 //(*p_bsfr[p1])(&r,rd);
		 u_lol ii=(u_lol)1 << r;
		 if(ii&wPCS_btARR[QUEEN]){return KING_VAL;}
		 if(p1&1){if(ii&wPCS_btARR[ROOK]){return KING_VAL;}}
		 else if(ii&wPCS_btARR[BISHOP]){return KING_VAL;};
		 }
	 }
	 }
	 //return 0;
	 if((p1=rays_dir[toRegularTable[posk]][toRegularTable[posp]])>=0){
	 u_lol rd;
	 //u_lol all_pcs=(bPCS_BITS|wPCS_BITS);
	 //if(rd=(rays[p1][toRegularTable[posp]]&all_pcs)){

	 if constexpr (CLR_ATT==BLACK){
		 u_lol ray=rays[p1][toRegularTable [posk]];
		 if((ray&bPCS_BITS)){
		 u_lol all_pcs=(bPCS_BITS|wPCS_BITS);
		 rd=ray&all_pcs;
		 unsigned long r;
		 if(p1<=3){
			 _BitScanForward64(&r,rd);
			 //u_lol ii=(u_lol)1 << r;
			 //if(ii&bPCS_btARR[QUEEN])return KING_VAL;
			 //if(p1&1){if(ii&bPCS_btARR[ROOK])return KING_VAL;}
			 //else if(ii&bPCS_btARR[BISHOP])return KING_VAL;

		 }
		 else{
			 _BitScanReverse64(&r,rd);
		 }
		 //(*p_bsfr[p1])(&r,rd);
		 u_lol ii=(u_lol)1 << r;
		 if(ii&bPCS_btARR[QUEEN])return KING_VAL;
		 if(p1&1){if(ii&bPCS_btARR[ROOK])return KING_VAL;}
		 else if(ii&bPCS_btARR[BISHOP])return KING_VAL;
		 }
	 }else{
		 u_lol ray=rays[p1][toRegularTable [posk]];
		 if(ray&wPCS_BITS){
		 u_lol all_pcs=(bPCS_BITS|wPCS_BITS);
		 rd=ray&all_pcs;
		 unsigned long r;
		 if(p1<=3){
			 _BitScanForward64(&r,rd);
			 //u_lol ii=(u_lol)1 << r;
			 //if(ii&wPCS_btARR[QUEEN])return KING_VAL;
			 //if(p1&1){if(ii&wPCS_btARR[ROOK])return KING_VAL;}
			 //else if(ii&wPCS_btARR[BISHOP])return KING_VAL;

		 }
		 else{
			 _BitScanReverse64(&r,rd);

		 }
		 //(*p_bsfr[p1])(&r,rd);
		 u_lol ii=(u_lol)1 << r;
		 if(ii&wPCS_btARR[QUEEN])return KING_VAL;
		 if(p1&1){if(ii&wPCS_btARR[ROOK])return KING_VAL;}
		 else if(ii&wPCS_btARR[BISHOP])return KING_VAL;
		 }
	 }
	 }

	 return 0;
*/



		//if(!dirx&& !diry)return 0;
else
	if(bits1[post]&ksft/*QUEEN_ATT_S[posk]*/){
	int diry=KNG_DIRS[toRegularTable[posk]][toRegularTable[post]];
	//if(diry){
	//sx=true;
			if(Table[posk+diry].PCE==C2_KING)return KING_VAL;
		u_lol poss=diry+posk;
		while(ulp[poss]==0){ poss += diry;}
		if(Table[poss].CLR==CLR_ATT){
		int tpcr=Table[poss].PCE;
		if(tpcr==QUEEN){return KING_VAL;}
		diry=abs(diry);
		if((diry==1||diry==10)&&tpcr==ROOK){return KING_VAL;}
		if((diry==9||diry==11)&&tpcr==BISHOP){return KING_VAL;}
	   // }
	}
	 }

	 if(bits1[posp]&ksft/*QUEEN_ATT_S[posk]*/){
	 int dirx=KNG_DIRS[toRegularTable[posk]][toRegularTable[posp]];
		//if(dirx){
	 //sx=true;
		if(Table[posk+dirx].PCE==C2_KING)return KING_VAL;
		u_lol poss=dirx+posk;
		while( ulp[poss]==0){ poss += dirx;}
		if(Table[poss].CLR==CLR_ATT){
		int tpcr=Table[poss].PCE;
		if(tpcr==QUEEN)return KING_VAL;
		dirx=abs(dirx);
		if((dirx==1||dirx==10)&&tpcr==ROOK)return KING_VAL;
		if((dirx==9||dirx==11)&&tpcr==BISHOP)return KING_VAL;
	  //  }
	}
	 }
	 //if(sx)falsep++;
	return 0;
	}

//#################################################################
template <int CLR_P,int CLR_ATT>
int msatr::attKingSafety(u_lol posk, u_lol posp, u_lol post, u_lol ksft){

	//bool sx=false;
	//constexpr int CLR_P=clr_a;//,CLR_ATT;
	//constexpr int CLR_ATT=clr_p;//Table[posk].CLR;
        if(posk==post)return king_ALL_Safety<CLR_P>();
	//mapToTable tm=Table[posp];
	//Table[posp]=EMPTY_mapToTable;
	//if(CLR_P==WHITE)CLR_ATT=BLACK;
	//else CLR_ATT=WHITE;
	if(bits1[posp]&ksft){
	int dirx=KNG_DIRS[toRegularTable[posk]][toRegularTable[posp]];
	if(!dirx /*||dirx==30*/)return 0;
	posk+=dirx;
agn:
	while(ulp[posk]==0){if(posk==post)return 0; posk += dirx;}
	if(Table[posk].CLR==CLR_ATT){
	//sx=true;
	int tpcr=Table[posk].PCE;
	if(tpcr==QUEEN)return KING_VAL;
	dirx=abs(dirx);
	if((dirx==1||dirx==10)&&tpcr==ROOK)return KING_VAL;
	if((dirx==9||dirx==11)&&tpcr==BISHOP)return KING_VAL;
	}
	else if(posk==posp){
	posk+=dirx;goto agn;
	}
}

	return 0;
}
//#############################################################
void msatr::divide(int FR_POS_,int TO_POS_){
	if constexpr(COL_PERFT){
	//if(depth==PERFT_DEPTH  ){
		cout<< cpcs[Table[TO_POS_].PCE]<<ranksFiles[FR_POS_]<<"-"<< ranksFiles[TO_POS_] << " ";
		for (int x1=0;x1<6;x1++) {
		cout<< dpthcntr[x1] <<" ";
		dpthcntr[x1]=0;
		}
		cout<<"\n";
	//}
	}
}

//########################################################### tryAllMoves
template <int CLR_ATT> int weight_npcs(){
	constexpr u_lol *us_ARR=CLR_ATT==WHITE? &msatr::wPCS_btARR[0]:&msatr::bPCS_btARR[0];
	constexpr u_lol *them_ARR=CLR_ATT==WHITE? &msatr::bPCS_btARR[0]:&msatr::wPCS_btARR[0];
	int r=popcnt(us_ARR[V_PAWN])*100+popcnt(us_ARR[KNIGHT])*330+popcnt(us_ARR[BISHOP])*300+popcnt(us_ARR[ROOK])*500+popcnt(us_ARR[QUEEN])*900;
	int q=popcnt(them_ARR[V_PAWN])*100+popcnt(them_ARR[KNIGHT])*330+popcnt(them_ARR[BISHOP])*300+popcnt(them_ARR[ROOK])*500+popcnt(them_ARR[QUEEN])*900;
	return r-q;
}

//########################################################### tryAllMoves
template <int CLR_ATT,int CLR_P >
void msatr::tryAllMoves( int depth,bool isch,u_lol _ksft,u_lol gg1,u_lol gg2) {
	//u_lol dbg_bits=wPCS_BITS|bPCS_BITS;
	assert_eq_bts();
assert_kings();
//cout << ":";
	u_lol retv = 0;
	//depth--;
	const u_lol cnt = lastMoveCount.back();
	const u_lol epos = vecMoves.size();
	u_lol cpos = epos - cnt;
	//u_lol us,them,*them_ARR,*us_ARR;
	constexpr u_lol &us = CLR_ATT==WHITE?  msatr::wPCS_BITS : msatr::bPCS_BITS;
	constexpr u_lol &them = CLR_ATT==WHITE? msatr::bPCS_BITS : msatr::wPCS_BITS;
	constexpr u_lol *us_ARR=CLR_ATT==WHITE? &msatr::wPCS_btARR[0]:&msatr::bPCS_btARR[0];
	constexpr u_lol *them_ARR=CLR_ATT==WHITE? &msatr::bPCS_btARR[0]:&msatr::wPCS_btARR[0];
	/*if constexpr(CLR_ATT==WHITE){
	us=wPCS_BITS;
	them=bPCS_BITS;
	them_ARR = &bPCS_btARR[0];
	us_ARR = &wPCS_btARR[0];
	}else {
us=bPCS_BITS;
them=wPCS_BITS;
them_ARR = &wPCS_btARR[0];
us_ARR = &bPCS_btARR[0];
}*/
	const u_lol p_KING=toBigTable[63-msb(them_ARR[C2_KING])];
	//const mapToTable *mptt=&sdinf.fpieces[C2_KING];

	//auto oo=kAttckMsk[kAttckMsk.size()-2];
	//kingBSafety
	//if(oo=oo&wPCS_BITS)
	//auto[ ksfr,ksfb] = kingXSafety< CLR_ATT, CLR_P >(p_KING);
	//u_lol _ksft;
	//ksft=ksfr|ksfb;
//			auto[ _ksfr,_ksfb] = kingBSafety<CLR_P , CLR_ATT >(mptt->NEXT,us);
//		auto _ksft=_ksfr|_ksfb;
//auto [gg1,gg2] =kingBSafety< CLR_ATT, CLR_P >(p_KING,them);
//		u_lol gg=gg1|gg2;
		/*if(gg^ksft){
	auto [bb,bb1] =dbgkingBSafety< CLR_ATT, CLR_P >(p_KING);

		dbgptr_ull(bb);
		dbgptr_ull(wPCS_BITS);
	dbgptr_ull(bPCS_BITS);
		dbgptr_ull(ksft);
		dbgptr_ull(gg);
		cout << "--------";}*/
					//assert_kings();
	for (; cpos < epos; cpos++) {
		 moveCPiece lmvcp = vecMoves[cpos];
		//cout << "{" << (int)lmvcp.sig  <<"}";
		bool dbghash=false;
			bool misch=false;
	const u_lol TO_POS_ = lmvcp.TO_PO;
	u_lol PAT_POS_ = lmvcp.TO_PO;
	const u_lol FR_POS_ = lmvcp.FR_PO;
	 u_lol /*TCHRG_PCE = Table[FR_POS_].PCE,*/ CHRG_PCE = Table[FR_POS_].PCE;
	if (lmvcp.PROM) {
		u_lol * ul;
		if constexpr(CLR_ATT==WHITE){
		ul=&wPCS_btARR[0];
		}else{
		ul=&bPCS_btARR[0];
		}
		u_lol pp=bits1[FR_POS_];
		ul[V_PAWN]^=pp;
		ul[lmvcp.PROM]^=pp;
		prom_L(FR_POS_,lmvcp.PROM);
		CHRG_PCE=lmvcp.PROM;
	}
	if (lmvcp.IS_TK) {
		assert_eq_bts();
assert_kings();

//#define HASH_ENABLED
#ifdef HASH_ENABLED
		int TARG_PCE = Table[TO_POS_].PCE;
		hash ^= sdinf.shashes[0][TARG_PCE][toRegularTable[TO_POS_]];
		hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[FR_POS_]];
		hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[TO_POS_]];
		if (/*depth == 3 ||depth == 2*/ depth>=1) {
		u_lol h3=hash^depth;
		bool hexst;
		if(CLR_ATT==WHITE){hexst=winsert_hash(h3);}
		else hexst=binsert_hash(h3);
		if (!hexst) {
			hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[TO_POS_]];
			hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[FR_POS_]];
			hash ^= sdinf.shashes[0][TARG_PCE][toRegularTable[TO_POS_]];
			goto fbreak;
		}
		}
#endif
assert_eq_bts();
		if  (lmvcp.ANP_MOV){
		if constexpr (CLR_P==WHITE){
			PAT_POS_=TO_POS_-10;
		}else {
			PAT_POS_=TO_POS_+10;
		}

		popPieceFromArray_L<CLR_P>(PAT_POS_);

		if(p_XKingSafety<CLR_ATT , CLR_P>(p_KING,PAT_POS_+10, PAT_POS_,  QUEEN_ATT_B[toRegularTable[p_KING]], QUEEN_ATT_B[toRegularTable[p_KING]])==KING_VAL)misch=true;
		lmvcp.ANP_MOV=0;
		}else popPieceFromArray_L<CLR_P>(TO_POS_);

assert_kings();
		moveTablePce_L<CLR_ATT>(CHRG_PCE,FR_POS_ , TO_POS_);


		if(p_XKingSafety<CLR_ATT , CLR_P>(p_KING,FR_POS_, TO_POS_,  gg1,gg2)==KING_VAL){
		//if((retv=kingSafety<CLR_ATT , CLR_P>(mptt->NEXT))!=KING_VAL){
                        if((retv = king_ALL_Safety<CLR_ATT>())!=KING_VAL){
			misch=true;
			chckcnta[depth]++;
			if(!depth)goto skip;
		}else goto skip;
		}


		 //if(isch )retv=kingSafety<CLR_ATT , CLR_P>(mptt->NEXT);
                if (isch)retv = king_ALL_Safety<CLR_ATT>();
		else    retv=attKingSafety<CLR_ATT,CLR_P>(toBigTable[63-msb(us_ARR[C2_KING])],FR_POS_, TO_POS_,_ksft);
		 if(retv==KING_VAL)goto skip;
		if (depth>0) {


		retv=moves<CLR_P,CLR_ATT>(lmvcp, depth,misch);

		if(depth==PERFT_DEPTH  )divide(FR_POS_,TO_POS_);
		/*if constexpr(COL_PERFT){
		if(depth==PERFT_DEPTH  ){
			cout<< cpcs[Table[TO_POS_].PCE]<<ranksFiles[FR_POS_]<<"-"<< ranksFiles[TO_POS_] << " ";
			for (int x1=0;x1<7;x1++) {
			cout<< dpthcntr[x1] <<" ";
			dpthcntr[x1]=0;
			}
			cout<<"\n";
		}
		}*/
		}
		else {
		//if(isch /*|| mptt->NEXT == TO_POS_*/)retv=kingSafety<CLR_ATT , CLR_P>(mptt->NEXT);
		//else    retv=attKingSafety<CLR_ATT,CLR_P>(mptt->NEXT,FR_POS_, TO_POS_,_ksft);

		}
skip:
		moveTablePce_L<CLR_ATT>(CHRG_PCE, TO_POS_, FR_POS_);
		retBackPiece_L<CLR_P>();
/*		if(dbg_bits!=(wPCS_BITS|bPCS_BITS)){
			cout << "Bits Mismatch: \n";
			printt();
			dbgptr_ull(dbg_bits ^ (wPCS_BITS|bPCS_BITS));
			cout << "---";
				}*/
		if (retv != KING_VAL){ dpthcntr[depth]++;

		//cout<<"count : " << FR_POS_ << " "<<(int)lmvcp.PROM<<" " << TO_POS_ << " " << dpthcntr[depth] << "\n";
		}
		//else cout << "skip 1>: " << FR_POS_ << " " << (int)lmvcp.PROM << " " << TO_POS_ << ";";
		assert_eq_bts();
assert_kings();
#ifdef HASH_ENABLED
		hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[TO_POS_]];
		hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[FR_POS_]];
		hash ^= sdinf.shashes[0][TARG_PCE][toRegularTable[TO_POS_]];
#endif
	}
	else {
#ifdef HASH_ENABLED
		hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[TO_POS_]];
		hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[FR_POS_]];
		if (/*depth == 3 ||depth == 2*/depth>=1) {
		u_lol h3=hash^depth;
		bool hexst;
		moveTablePce_L(FR_POS_, TO_POS_);
		if(CLR_ATT==WHITE){hexst=winsert_hash(h3);}
		else{ hexst=binsert_hash(h3);}
		moveTablePce_L(TO_POS_, FR_POS_);
		if (!hexst) {
			/*if(depth==5)
			{moveTablePce_L(FR_POS_, TO_POS_);
			printt();
			cout <<"\n"<<hash<<"\n";
			moveTablePce_L(TO_POS_,FR_POS_ );
			}*/
			hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[TO_POS_]];
			hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[FR_POS_]];
			goto fbreak;
		}
		}
#endif
		moveTablePce_L<CLR_ATT>(CHRG_PCE,FR_POS_ , TO_POS_);
int retvq=0;



	//if((retv=attKingSafety<CLR_ATT,CLR_P>(mptt->NEXT,FR_POS_, TO_POS_))==KING_VAL)goto skip1;


	if(p_XKingSafety<CLR_ATT , CLR_P>(p_KING,FR_POS_, TO_POS_,  gg1,gg2)==KING_VAL){
			//if((retv=kingSafety<CLR_ATT , CLR_P>(mptt->NEXT))!=KING_VAL){
                if((retv=retv = king_ALL_Safety<CLR_ATT>())!=KING_VAL){
			misch=true;
			chckcnta[depth]++;
			if(!depth)goto skip1;
		}else goto skip1;
		}

	//if(isch)retv=kingSafety<CLR_ATT , CLR_P>(mptt->NEXT);
        if (isch)retv = king_ALL_Safety<CLR_ATT>();
	else retv = attKingSafety<CLR_ATT, CLR_P>(toBigTable[63-msb(us_ARR[C2_KING])], FR_POS_, TO_POS_, _ksft);
	/*if (isch) {
		retvq = king_ALL_Safety<CLR_ATT>(mptt->NEXT);
		if (retv != retvq){
			printt();
		cout << "-------------------------------------------------------------------------------------------------------------";
		retvq = king_ALL_Safety<CLR_ATT>(mptt->NEXT);
		cout << retvq;
	}
	}*/

	if(retv==KING_VAL)goto skip1;
		if (depth>0) {

			assert_eq_bts();
assert_kings();
		retv=moves<CLR_P,CLR_ATT>(lmvcp, depth,misch) ;

		if(depth==PERFT_DEPTH  )divide(FR_POS_,TO_POS_);
		/*if constexpr(COL_PERFT){
		if(depth==PERFT_DEPTH){
			cout << cpcs[Table[TO_POS_].PCE]<<ranksFiles[FR_POS_]<<"-"<< ranksFiles[TO_POS_] << " ";
			for (int x1=0;x1<7;x1++) {
			cout<< dpthcntr[x1] <<" ";
			dpthcntr[x1]=0;
			}
			cout<<"\n";
		}
		}*/
		}else {
		//if(isch /*|| mptt->NEXT == TO_POS_*/)retv=kingSafety<CLR_ATT , CLR_P>(mptt->NEXT);
		//else retv=attKingSafety<CLR_ATT,CLR_P>(mptt->NEXT,FR_POS_, TO_POS_,_ksft);

	}
		/*if(isch){
		moveCPiece llcp=MoveSeq.back();
		if((retvd=p_KingSafety<CLR_P , CLR_ATT>(mptt->NEXT,llcp.FR_PO, llcp.TO_PO))==KING_VAL){}//goto skip1;
		if(retvd==KING_VAL&& retv==0){
			printt();
			p_KingSafety<CLR_P , CLR_ATT>(mptt->NEXT,llcp.FR_PO, llcp.TO_PO);
		}
		}*/
skip1:
		moveTablePce_L<CLR_ATT>(CHRG_PCE, TO_POS_, FR_POS_);
		/*if(dbg_bits!=(wPCS_BITS|bPCS_BITS)){
			cout << "Bits Mismatch: \n";
			printt();
			dbgptr_ull(dbg_bits ^ (wPCS_BITS|bPCS_BITS));
			cout << "---";
				}*/

#ifdef HASH_ENABLED
		hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[TO_POS_]];
		hash ^= sdinf.fhashes[0][CHRG_PCE][toRegularTable[FR_POS_]];
#endif
		if (retv != KING_VAL){  dpthcntr[depth]++;/*if(misch)cout<<"#";*/
		//if(!(dpthcntr[0]%20000000)){printt();dbgptr_ull(wPCS_BITS|bPCS_BITS);}

		//cout<<"count 2>: " << FR_POS_ << " "<<(int)lmvcp.PROM<<" " << TO_POS_ << " " << dpthcntr[depth] <<"\n";
		}
		//else cout << "skip 2>: " << FR_POS_ << " " << (int)lmvcp.PROM << " " << TO_POS_ << ";";
	}
	assert_eq_bts();
assert_kings();


fbreak:;
	if (lmvcp.PROM) {
		undoProm_L(FR_POS_,CHRG_PCE);
		u_lol * ul;
		if constexpr(CLR_ATT==WHITE){
		ul=&wPCS_btARR[0];
		}else{
		ul=&bPCS_btARR[0];
		}
		u_lol pp=bits1[FR_POS_];
		ul[lmvcp.PROM]^=pp;
		ul[V_PAWN]^=pp;
	}
	}
	assert_eq_bts();
assert_kings();
	return;
}
template <int clr_a,int clr_p>
void msatr::castle(u_lol posk,u_lol posr,u_lol depth,moveCPiece lmvcp,int side,u_lol _ksft,u_lol gg1,u_lol gg2){
	//if(posk!=25 && posk != 95){printt();cout<<"\nbad cast\n";}
	assert_eq_bts();
	moveTablePce_L<clr_a>(C2_KING, posk, posk+side);
	//mvv lmvv={(unsigned char)posk,(unsigned char)(posk+side),(unsigned char)C2_KING};
	//moveTrain.push_back(lmvv);
	lmvcp.FR_PO=posr;
	lmvcp.TO_PO=posk+(side/2);
	lmvcp.IS_TK=0;
	//dpthcntr[depth-1]++;
	vecMoves.push_back(lmvcp);
	lastMoveCount.push_back(1);
	//if(p_XKingSafety<CLR_ATT , CLR_P>(posk,posr, posk+(side/2),  QUEEN_ATT_B[toRegularTable[]], QUEEN_ATT_B[])==KING_VAL)
	tryAllMoves<clr_a,clr_p>(depth,0,_ksft,gg1,gg2);
	moveTablePce_L<clr_a>(C2_KING, posk+side,posk);
	vecMoves.resize(vecMoves.size()-1);
	lastMoveCount.pop_back();
	assert_eq_bts();
	//moveTrain.pop_back();
}
mt19937 mt;
constexpr bool statAnalysis=false;
template <int CLR_ATT,int CLR_P>
int msatr::moves( moveCPiece lmvcp, int depth,bool isch)
{
	if constexpr(statAnalysis){cout << "enter moves";}
	assert_kings();
	depth--;
	u_lol blc;// ,  *them_ARR, *us_ARR,us ,them;
	int ourk, thrk;
	constexpr u_lol &us = CLR_ATT==WHITE?  msatr::wPCS_BITS : msatr::bPCS_BITS;
	constexpr u_lol &them = CLR_ATT==WHITE? msatr::bPCS_BITS : msatr::wPCS_BITS;
	constexpr u_lol *us_ARR = CLR_ATT==WHITE? &msatr::wPCS_btARR[0]:&msatr::bPCS_btARR[0];
	constexpr u_lol *them_ARR = CLR_ATT==WHITE? &msatr::bPCS_btARR[0]:&msatr::wPCS_btARR[0];
	constexpr u_lol S_RANK = CLR_ATT==WHITE? 0x000000000000ff00 : 0x00ff000000000000;
	constexpr u_lol P_RANK = CLR_ATT==WHITE? 0x00ff000000000000 : 0x000000000000ff00;
	constexpr u_lol *PAWN_ATT = CLR_ATT==WHITE? &WH_PAWN_ATT[0]:&BL_PAWN_ATT[0];
	constexpr int PAWN_MOV_1 = CLR_ATT==WHITE? 8:-8;
	constexpr int PAWN_MOV_10 = CLR_ATT==WHITE? -10:10;
	constexpr int PAWN_MOV_2 = CLR_ATT==WHITE? 16:-16;
	constexpr int PAWN_MOV_20 = CLR_ATT==WHITE? -20:20;
	constexpr int PAWN_ATT_L = CLR_ATT==WHITE? 9:-9;
	constexpr int PAWN_ATT_R = CLR_ATT==WHITE? 7:-7;
	constexpr int PAWN_ATT_L12 = CLR_ATT==WHITE? -11:9;
	constexpr int PAWN_ATT_R12 = CLR_ATT==WHITE? -9:11;
	u_lol all_pcs= them|us;
	//u_lol us_pawns = CLR_ATT==WHITE?wPCS_btARR[V_PAWN]:bPCS_btARR[V_PAWN];
	//ourk =lsb(us_ARR[C2_KING]);
	//thrk =lsb(them_ARR[C2_KING]);
	int rv=0;
	u_lol p_1mov,p_2mov,p_latt,p_ratt;
	if constexpr(statAnalysis){cout << "pawn moves:";}
	if constexpr (CLR_ATT == WHITE) {
		//cout<< "white";
		u_lol us_pawns=wPCS_btARR[V_PAWN];
		p_1mov=((us_pawns<<8)& ~all_pcs)>>8;
		p_ratt=(((us_pawns&0x7f7f7f7f7f7f7f7f)<<9)& them)>>9;
		p_latt=(((us_pawns&0xfefefefefefefefe)<<7)& them)>>7;
		p_2mov=(us_pawns &S_RANK)<<8;
		p_2mov=(p_2mov& ~all_pcs)<<8;
		p_2mov=(p_2mov& ~all_pcs)>>16;
	  //us = wPCS_BITS;
	  //them = bPCS_BITS;
//	  them_ARR = &bPCS_btARR[0];
//	  us_ARR = &wPCS_btARR[0];
		rv=1000000;
	  ourk =  lsb(wPCS_btARR[C2_KING]);
	  thrk =  lsb(bPCS_btARR[C2_KING]);
	} else {
		//cout<< "black";
		u_lol us_pawns=bPCS_btARR[V_PAWN];
		 p_1mov=((us_pawns>>8)& ~all_pcs)<<8;
		p_latt=(((us_pawns&0x7f7f7f7f7f7f7f7f)>>7)& them)<<7;
		p_ratt=(((us_pawns&0xfefefefefefefefe)>>9)& them)<<9;
		p_2mov=(us_pawns &S_RANK)>>8;
		p_2mov=(p_2mov& ~all_pcs)>>8;
		p_2mov=(p_2mov& ~all_pcs)<<16;
//	  us = bPCS_BITS;
//	  them = wPCS_BITS;
//	  them_ARR = &wPCS_btARR[0];
//	  us_ARR = &bPCS_btARR[0];
		rv=-1000000;
	  ourk = lsb(bPCS_btARR[C2_KING]);
	  thrk = lsb(wPCS_btARR[C2_KING]);
	}
	if constexpr(statAnalysis){cout << "end pawn moves:";}
	/*if((popcnt(p_latt)>2)||(popcnt(p_ratt)>2)){
	printt();
	dbgptr_ull(p_1mov);
	dbgptr_ull(p_2mov);
	dbgptr_ull(p_latt);
	dbgptr_ull(p_ratt);}*/
	if(assert_kingSafety< CLR_ATT, CLR_P>( toBigTable[63-ourk] )==KING_VAL){
		printt();
		cout<<"-------king gone ----";
	}
u_lol CKECK_MASK = 0;
	if(isch && check_MASK.size()){
                CKECK_MASK=check_MASK.back();
	check_MASK.pop_back();
		//cout << popcnt(lpx);
		//printt();
		//dbgptr_ull(lpx);
	}
//cout<< "kings : ";
	//dbgptr_ull(1ULL << thrk);
	//dbgptr_ull(1ULL << ourk);

	assert_eq_bts();

	//const mapToTable *lpiecesl;
//	u_lol pawnVrank, pawnPrank;
	lmvcp.PROM = 0;
	lmvcp.sig = 0;
	lmvcp.IS_TK = 0;
	lmvcp.GIV_CHK=0;
	u_lol tx,tx1;
#define push_movs(str,to) str.TO_PO=to;\
	vecMoves.push_back(str);

#define push_movsa(str,to) str.TO_PO=to;\
	vecMoves.push_back(str);
	//lmvcp.FR_PO=fr;
	//lmvcp.IS_TK=0;

#define push_movp_r(fr,to) ll.FR_PO=fr;\
	ll.TO_PO=to;\
	ll.IS_TK=0;\
	vecMoves.push_back(ll);
#define push_mov_a_r(fr,to) ll.FR_PO=fr;\
	ll.TO_PO=to;\
	ll.IS_TK=1;\
	vecMoves.push_back(ll);

#define move_plain(PIECE,MOVE_STR) 	moveTablePce_L<CLR_ATT>(PIECE,curr_pce_tbl_pos,ee);\
	if(depth>0)moves<CLR_P,CLR_ATT>(MOVE_STR,depth,lisch);\
	lisch=false;\
        if(depth==PERFT_DEPTH  )divide(curr_pce_tbl_pos,ee);\
         moveTablePce_L<CLR_ATT>(PIECE,ee,curr_pce_tbl_pos);

	//else weighs.push_back(weight_npcs<CLR_ATT>());

	/*
	auto move_plain_lambda=[&](auto pce,auto m_s,auto p_,auto ee_,auto lisch_){
		moveTablePce_L<CLR_ATT>(pce,p_,ee_);
			if(depth>0)moves<CLR_P,CLR_ATT>(m_s,depth,lisch_);
			else weighs.push_back(weight_npcs<CLR_ATT>());
			if(depth==PERFT_DEPTH  )divide(p_,ee_);
			lisch_=false;\
			 moveTablePce_L<CLR_ATT>(pce,ee_,p_);
	};
*/
//cout << "-";
#define move_take(PIECE,MOVE_STR) popPieceFromArray_L<CLR_P>(ee);\
        moveTablePce_L<CLR_ATT>(PIECE,curr_pce_tbl_pos,ee);\
	if(depth>0){moves<CLR_P,CLR_ATT>(MOVE_STR,depth,lisch);}\
        if(depth==PERFT_DEPTH  )divide(curr_pce_tbl_pos,ee);\
	lisch=false;\
        moveTablePce_L<CLR_ATT>(PIECE,ee,curr_pce_tbl_pos);\
	retBackPiece_L<CLR_P>();

	//else weighs.push_back(weight_npcs<CLR_ATT>());\

#define push_movp(fr,to) lmvcp.TO_PO=to;\
	lmvcp.FR_PO=fr;\
	lmvcp.IS_TK=0;\
	vecMoves.push_back(lmvcp);

#define push_mov_a(fr,to) lmvcp.FR_PO=fr;\
	lmvcp.TO_PO=to;\
	lmvcp.IS_TK=1;\
	vecMoves.push_back(lmvcp);
assert_kings();

#define markd(md) /*dbgt64[toRegularTable[(md)]]++;*/ \
	cnt++;
#define whl_esq(esq) while(ulp[esq]==0)
#define if_clr(cl) if(Table[cl].CLR == CLR_P)
#define esq(cl) ulp[cl]==0
#define pattck(cl) attcka|=0x8000000000000000>> toRegularTable[cl];
   u_lol cnt = 0,psh=0;
	const int * pawn_mov, *pawn_att;
	u_lol k1,k2,k3;
	if constexpr (CLR_ATT == WHITE) {
	pawn_mov = &WHITE_PAWN_MOVE[0];
	pawn_att = &WHITE_PAWN_ATTACK[0];
	}
	else {
	pawn_mov = &BLACK_PAWN_MOVE[0];
	pawn_att = &BLACK_PAWN_ATTACK[0];
	}
	if constexpr(statAnalysis){cout << "blockers bits:";}
	u_lol usb=0,thb=0,usk_thb=0,thk_usb=0;
	u_lol thr_PLUS_SLID = them_ARR[ROOK] | them_ARR[QUEEN];
        u_lol thr_XRAY_SLID = them_ARR[BISHOP] | them_ARR[QUEEN];
        u_lol us_PLUS_SLID = us_ARR[ROOK] | us_ARR[QUEEN];
        u_lol us_XRAY_SLID = us_ARR[BISHOP] | us_ARR[QUEEN];

        u_lol rr = ROOK_RAYS[63 - thrk];
        u_lol rp = (rr & them)|(1ull<<thrk);
        rp *= mics_r13[thrk];
        rp >>= 51;
        u_lol th_ksr = rr & ROOK_MASKS_BLCKS[thrk][rp];

        rr = BISHOP_RAYS[63-thrk];
        rp = (rr & them)|(1ull<<thrk);
        rp *= magics_b_12[thrk];
        rp >>= 52;
        u_lol th_ksb = BISHOP_MASKS_BLCKS[thrk][rp];

        u_lol us_ks = attMaskStar(ourk,us);
        u_lol us_kgrd = us_ks & us;
        u_lol th_ks = th_ksr | th_ksb;
        u_lol th_kgrd = th_ks & them;
        u_lol thr_PLUS_SLID_POT_THRT=thr_PLUS_SLID&ROOK_RAYS[63-ourk];

        if(thr_PLUS_SLID_POT_THRT){
            u_lol rr = ROOK_RAYS[63 - ourk];
            u_lol rp = (rr & thr_PLUS_SLID)|(1ull<<ourk);
            rp *= mics_r13[ourk];
            rp >>= 51;
            u_lol th_plat = rr & ROOK_MASKS_BLCKS[ourk][rp];
            th_plat&=thr_PLUS_SLID;
            while(th_plat){
                char x = msb(th_plat);
                th_plat ^=1ull <<x;
                u_lol lrayp= CORD[x][ourk];
                u_lol lray =lrayp& all_pcs;
                if(!(lray & (lray-1))){
                    if(lray&us_kgrd)
                        usb|=lray;
                }
            }
        }

        u_lol thr_XRAY_SLID_POT_THRT=thr_XRAY_SLID&BISHOP_RAYS[63-ourk];
        if(thr_XRAY_SLID_POT_THRT){
            u_lol rr = BISHOP_RAYS[63-ourk];
            u_lol rp = (rr & thr_XRAY_SLID)|(1ull<<ourk);
            rp *= magics_b_12[ourk];
            rp >>= 52;
            u_lol th_xrat = BISHOP_MASKS_BLCKS[ourk][rp];

            th_xrat &= thr_XRAY_SLID;
            while(th_xrat){
                int x = msb(th_xrat);
                th_xrat ^=1ull <<x;
                u_lol lrayp= CORD[x][ourk];
                u_lol lray =lrayp& all_pcs;
                if(!(lray & (lray-1))){
                    if(lray&us_kgrd)
                        usb|=lray;
                }
            }
        }

        u_lol us_PLUS_SLID_POT_THRT=us_PLUS_SLID&ROOK_RAYS[63-thrk];
        if(us_PLUS_SLID_POT_THRT){
            u_lol rr = ROOK_RAYS[63 - thrk];
            u_lol rp = (rr & us_PLUS_SLID) |(1ull<<thrk);
            rp *= mics_r13[thrk];
            rp >>= 51;
            auto us_plat=rr & ROOK_MASKS_BLCKS[thrk][rp];
            us_plat &= us_PLUS_SLID;
            while(us_plat){
                int x = msb(us_plat);
                us_plat ^=1ull <<x;
                u_lol lrayp= CORD[x][thrk];
                u_lol lray =lrayp& all_pcs;
                if(!(lray & (lray-1))){
                    if(lray&th_kgrd)thb|=lray;
                    else thk_usb |= lray;
                }
            }
        }
        u_lol us_XRAY_SLID_POT_THRT=us_XRAY_SLID&BISHOP_RAYS[63-thrk];

        if(us_XRAY_SLID_POT_THRT){
            u_lol rr = BISHOP_RAYS[63-thrk];
            u_lol rp = (rr & us_XRAY_SLID)|(1ull<<thrk);
            rp *= magics_b_12[thrk];
            rp >>= 52;
            u_lol us_xrat = BISHOP_MASKS_BLCKS[thrk][rp];
            us_xrat &= us_XRAY_SLID;
            while(us_xrat){
                int x = msb(us_xrat);
                us_xrat ^=1ull <<x;
                u_lol lrayp= CORD[x][thrk];
                u_lol lray =lrayp& all_pcs;
                if(!(lray & (lray-1))){
                    if(lray&th_kgrd)thb|=lray;
                    else thk_usb |= lray;
                }
            }
        }
        u_lol all_bl = usb  | thk_usb;

assert_kings();
	//moveCPiece lanp=lmvcp;
if constexpr(statAnalysis){cout << "en passant:";}
//___________________________________________________________________ en passant
	if(lmvcp.ANP_AV){
	const u_char ls=lmvcp.TO_PO;
	lmvcp.ANP_AV=0;
	if(Table[ls-1].PCE==V_PAWN && Table[ls-1].CLR==CLR_ATT){
		lmvcp.FR_PO=ls-1;
		lmvcp.TO_PO=ls+PAWN_MOV_10;
		lmvcp.sig= AN_PASS;
		lmvcp.IS_TK=1;
		lmvcp.ANP_MOV=1;
		vecMoves.push_back(lmvcp);
		cnt++;
	}
	if(Table[ls+1].PCE==V_PAWN && Table[ls+1].CLR==CLR_ATT){
		lmvcp.FR_PO=ls+1;
		lmvcp.TO_PO=ls+PAWN_MOV_10;
		lmvcp.sig=AN_PASS;
		lmvcp.IS_TK=1;
		lmvcp.ANP_MOV=1;
		vecMoves.push_back(lmvcp);
		cnt++;
	}
	lmvcp.ANP_MOV=0;
	lmvcp.IS_TK=0;
	}
	moveCPiece lmvcp_a=lmvcp;
	lmvcp_a.IS_TK=1;
        u_lol curr_pce_tbl_pos;
assert_kings();
lmvcp.sig=V_PAWN;
//####################################################### <promotion>
u_lol curr_pcs=us_ARR[V_PAWN];
auto Promotions = [&](){
        lmvcp.sig = PROM;lmvcp.PROM = QUEEN;push_movp(curr_pce_tbl_pos, tx);cnt++;lmvcp.PROM = ROOK;push_movp(curr_pce_tbl_pos, tx);cnt++;lmvcp.PROM = KNIGHT;push_movp(curr_pce_tbl_pos, tx);cnt++;lmvcp.PROM = BISHOP;push_movp(curr_pce_tbl_pos, tx);cnt++;lmvcp.PROM=0;lmvcp.sig =  V_PAWN;
};
auto Promotions_a=[&](auto tx_){lmvcp.sig = PROM;lmvcp.PROM = QUEEN;push_mov_a(curr_pce_tbl_pos, tx_);cnt++;
        lmvcp.PROM = ROOK;push_mov_a(curr_pce_tbl_pos, tx_);cnt++;lmvcp.PROM = KNIGHT;push_mov_a(curr_pce_tbl_pos, tx_);cnt++;
        lmvcp.PROM = BISHOP;push_mov_a(curr_pce_tbl_pos, tx_);cnt++;lmvcp.PROM=0;lmvcp.sig = V_PAWN;
};

//######################################################## <pawn bit logic>
if constexpr(statAnalysis){cout << "pawn logic:";}
//int lcc=0,llc=popcnt(p_2mov);

while(curr_pcs){
    int curr_pawn_bit=lsb(curr_pcs);
    u_lol mbit=1ull<<curr_pawn_bit;
    curr_pcs^=mbit;
    curr_pce_tbl_pos=toBigTable[63^curr_pawn_bit];
    if (bits1[curr_pce_tbl_pos] & all_bl || isch){
        //----------------------------------------------------------------------- move
        tx=curr_pce_tbl_pos + PAWN_MOV_10;tx1=curr_pce_tbl_pos + pawn_mov[1];
        if (p_1mov &mbit) {
            if (mbit&P_RANK) {
                Promotions();
            }  else { push_movp(curr_pce_tbl_pos, tx); markd(tx)}
        }
        //---------------------------------------------------------------------- 2 move
        if (p_2mov&mbit){lmvcp.ANP_AV=1; markd(tx1); push_movp(curr_pce_tbl_pos, tx1); lmvcp.ANP_AV=0;};

        //_____________________________________________________________________ attack
        tx=curr_pce_tbl_pos + pawn_att[0];tx1=curr_pce_tbl_pos + pawn_att[1];
        if(mbit & p_ratt) {
            if (mbit&P_RANK) {Promotions_a(tx);}else {markd(tx);  push_mov_a(curr_pce_tbl_pos, tx); }}
        if(mbit & p_latt) {
            if (mbit&P_RANK) {Promotions_a(tx1);}else {markd(tx1);  push_mov_a(curr_pce_tbl_pos, tx1); } };
    }else
    {//************************************************************************************ bb
        tx=curr_pce_tbl_pos + PAWN_MOV_10;tx1=curr_pce_tbl_pos + PAWN_MOV_20;
        if (p_1mov &mbit) {
            if (!(mbit&P_RANK))    {
                bool lisch=false;
                dpthcntr[depth]++;
                if (depth > 0){
                    moveTablePce_L<CLR_ATT>(V_PAWN, curr_pce_tbl_pos, tx);
                    if(PAWN_ATT[curr_pawn_bit+PAWN_MOV_1]&(1ull<<thrk))
                    {lisch=true;check_MASK.push_back(1ull<<(curr_pawn_bit+PAWN_MOV_1));}
                    moves<CLR_P, CLR_ATT>(lmvcp, depth, lisch);lisch = false;
                    if(depth==PERFT_DEPTH  )divide(curr_pce_tbl_pos,tx);
                    moveTablePce_L<CLR_ATT>(V_PAWN, tx, curr_pce_tbl_pos);
                }
            }else{
                Promotions();
            }
        }
        //---------------------------------------------------------------------- 2 move
        if(p_2mov &mbit) {
            if(PAWN_ATT[curr_pawn_bit+PAWN_MOV_1]&them_ARR[V_PAWN]){lmvcp.ANP_AV=1;{markd(tx1); push_movp(curr_pce_tbl_pos, tx1);}lmvcp.ANP_AV=0;}
            else{
                bool lisch=false;
                dpthcntr[depth]++;
                if (depth > 0){
                    moveTablePce_L<CLR_ATT>(V_PAWN, curr_pce_tbl_pos, tx1);
                    if(PAWN_ATT[curr_pawn_bit+PAWN_MOV_2]&(1ull<<thrk))
                    {lisch=true;check_MASK.push_back(1ull<<(curr_pawn_bit+PAWN_MOV_2));}
                    moves<CLR_P, CLR_ATT>(lmvcp, depth, lisch);
                    lisch = false;
                    if(depth==PERFT_DEPTH  )divide(curr_pce_tbl_pos,tx1);
                    moveTablePce_L<CLR_ATT>(V_PAWN, tx1, curr_pce_tbl_pos);
                }
            }
        }

        //_____________________________________________________________________ attack
        tx=curr_pce_tbl_pos + pawn_att[0];tx1=curr_pce_tbl_pos + pawn_att[1];
        if(mbit & p_ratt) {
            if (mbit&P_RANK) {Promotions_a(tx);}
            else {
                bool lisch=false;
                dpthcntr[depth]++;
                if (depth > 0){
                    popPieceFromArray_L<CLR_P>(tx);
                    moveTablePce_L<CLR_ATT>(V_PAWN, curr_pce_tbl_pos, tx);
                    if(PAWN_ATT[curr_pawn_bit+PAWN_ATT_L]&(1ull<<thrk))//lisch=true;
                    {lisch=true;check_MASK.push_back(1ull<<(curr_pawn_bit+PAWN_ATT_L));}
                    moves<CLR_P, CLR_ATT>(lmvcp, depth, lisch);lisch = false;
                    if(depth==PERFT_DEPTH  )divide(curr_pce_tbl_pos,tx);
                    moveTablePce_L<CLR_ATT>(V_PAWN, tx, curr_pce_tbl_pos);
                    retBackPiece_L<CLR_P>();
                }
            }
        }
        if(mbit & p_latt) {
            if (mbit&P_RANK) {Promotions_a(tx1);}
            else {
                bool lisch=false;
                dpthcntr[depth]++;
                if (depth > 0){
                    popPieceFromArray_L<CLR_P>(tx1);
                    moveTablePce_L<CLR_ATT>(V_PAWN, curr_pce_tbl_pos, tx1);
                    if(PAWN_ATT[curr_pawn_bit+PAWN_ATT_R]&(1ull<<thrk))//lisch=true;
                    {lisch=true;check_MASK.push_back(1ull<<(curr_pawn_bit+PAWN_ATT_R));}
                    moves<CLR_P, CLR_ATT>(lmvcp, depth, lisch);lisch = false;
                    if(depth==PERFT_DEPTH  )divide(curr_pce_tbl_pos,tx1);
                    moveTablePce_L<CLR_ATT>(V_PAWN, tx1, curr_pce_tbl_pos);
                    retBackPiece_L<CLR_P>();
                }
            }
        }
    }
}
//######################################################## <knight bit logic>
if constexpr(statAnalysis){cout << "knight logic:";}
lmvcp.IS_TK=0;
curr_pcs=us_ARR[KNIGHT];
while(curr_pcs){
    int curr_knight_bit=lsb(curr_pcs);
    curr_pce_tbl_pos=toBigTable[63^curr_knight_bit];
    curr_pcs^=1ull<<curr_knight_bit;
    lmvcp.sig = KNIGHT;
    lmvcp.FR_PO = curr_pce_tbl_pos;
    bool lisch = false;
    u_lol knight_all_att_bits=KNIGHT_ATT[63^curr_knight_bit];
    u_lol knight_true_att_bits = knight_all_att_bits &~us;

    //if((1ull<<curr_knight_bit) &usb)cout << "%";
    if ((isch  && !CKECK_MASK) || (1ull<<curr_knight_bit & all_bl)) {
        if (!((1ull<<curr_knight_bit) &usb) )
        {
                //if(/*(isch  && !CKECK_MASK) &&*/((1ull<<curr_knight_bit) &usb))cout<<"&";
                //if(/*(isch  && !CKECK_MASK) &&*/((1ull<<curr_knight_bit) &thk_usb))cout<<"*";
            lmvcp_a.FR_PO=curr_pce_tbl_pos;
        /*if(1ull<<curr_knight_bit & usb){
            cout<<"s-------\n";
            printt();
            cout<<"1-------\n";
            dbgptr_ull(all_bl);
            cout<<"2-------\n";
            dbgptr_ull(usb);
            cout <<"e-------\n";
            dbgptr_ull(thk_usb);
            cout <<"e-------\n";
        }*/
//if((isch  && !CKECK_MASK) &&)cout << "-";
//cout << "\n"<<flush;
            while (knight_true_att_bits) {
                u_int knight_curr_att_bit = msb(knight_true_att_bits);
                u_lol movbit = 1ull << knight_curr_att_bit;
                knight_true_att_bits ^= movbit;
                knight_all_att_bits=KNIGHT_ATT[63^knight_curr_att_bit];
                u_int kni = toBigTable[63^knight_curr_att_bit];


                if (!((1ull<<knight_curr_att_bit)&them)) {  markd(kni); push_movs(lmvcp, kni); }
                else {  markd(kni);
                    push_movs(lmvcp_a, kni); }
            }
        }
    }else {
        if(CKECK_MASK  ){knight_true_att_bits&=CKECK_MASK;}
        //if(depth>0)
        if(/*(isch  && !CKECK_MASK) &&*/((1ull<<curr_knight_bit) &usb))cout<<"+";
        while (knight_true_att_bits) {
            u_int knight_curr_att_bit = msb(knight_true_att_bits);
            u_lol movbit = 1ull << knight_curr_att_bit;

            knight_all_att_bits=KNIGHT_ATT[63^knight_curr_att_bit];
            u_int ee = toBigTable[63^knight_curr_att_bit];
            if (knight_all_att_bits & (1ull<<thrk)) { lisch=true;if(depth>0)check_MASK.push_back(1ull<<(knight_curr_att_bit));}
            else lisch = false;
            knight_true_att_bits ^= movbit;
            if (them & movbit) {

                dpthcntr[depth]++;
                //if (depth > 0){
                move_take(KNIGHT,lmvcp);
                /*popPieceFromArray_L<CLR_P>(ee);
                                                moveTablePce_L<CLR_ATT>(KNIGHT, p, ee);psh++;
                                                        moves<CLR_P, CLR_ATT>(lmvcp, depth, lisch);lisch = false;
                                                        if(depth==PERFT_DEPTH  )divide(p,ee);
                                                moveTablePce_L<CLR_ATT>(KNIGHT, ee, p);
                                                retBackPiece_L<CLR_P>();*/
                //}
            }else {
                dpthcntr[depth]++;
                //if (depth > 0){
                move_plain(KNIGHT,lmvcp);
                //move_plain_lambda(KNIGHT,lmvcp,p,ee,lisch);
                /*moveTablePce_L<CLR_ATT>(KNIGHT, p, ee);psh++;
                                                        moves<CLR_P, CLR_ATT>(lmvcp, depth, lisch);lisch = false;
                                                if(depth==PERFT_DEPTH  )divide(p,ee);
                                                moveTablePce_L<CLR_ATT>(KNIGHT, ee, p);*/
                //}
            }
        }//else dpthcntr[depth]+=popcnt(a3);
    }
}

assert_kings();

//######################################################## <rook bit logic>
if constexpr(statAnalysis){cout << "rook logic:";}
curr_pcs=us_ARR[ROOK];
while(curr_pcs){
    int a=lsb(curr_pcs);
    curr_pcs^=1ull<<a;
    curr_pce_tbl_pos=toBigTable[63^a];
    moveCPiece ll = lmvcp;
    ll.sig = ROOK;
    if constexpr(CLR_ATT == WHITE) {if (curr_pce_tbl_pos == LEFT_BOT)ll.WH_CSL = 0;if (curr_pce_tbl_pos == RIGHT_BOT) ll.WH_CSR = 0;}
    else {if (curr_pce_tbl_pos == LEFT_TOP)ll.BL_CSL = 0;if (curr_pce_tbl_pos == RIGHT_TOP) ll.BL_CSR = 0;}
    bool lisch = false;
    u_lol rr = ROOK_RAYS[63^a];
    u_lol rp = (rr & all_pcs)|(1ull<<a);
    rp *= mics_r13[a];
    rp >>= 51;
    rr &= ROOK_MASKS_BLCKS[a][rp];
    u_lol a3 = (rr ) & ~us;
    /*if ((1ull<<a) & (usb&~thk_usb)){
                        int asx=BLCK_RAY.size()-1;
                        while(1){
                                u_lol lox=BLCK_RAY[asx--];
                                if((1ull<<a)&lox){a3 &= lox; break;}
                        }
                }*//* printt();dbgptr_ull(a3); */ /*(lox^(1ull<<a));dbgptr_ull(a3);*/
    if ((1ull<<a) & all_bl || (isch  && !CKECK_MASK)) {
        //if (1ull<<a & usb){u_lol crd=CORD[ourk][1ull<<a];a3&=crd;}
        while(a3){
            int b=lsb(a3);
            a3^=1ull<<b;
            int lp=toBigTable[63^b];
            int ori = curr_pce_tbl_pos;
            if (!((1ull<<b)&them)) { { push_movp_r(ori, lp); } markd(lp); }
            else { {push_mov_a_r(ori, lp); } markd(lp); }
        }
    }else {
        if(CKECK_MASK  ){a3&=CKECK_MASK;}
        //if(depth>0)
        while (a3) {
            u_int b = msb(a3);u_lol movbit = 1ull << b;a3 ^= movbit;u_int ee = toBigTable[63 ^ b];
            if (depth>0 &&movbit & th_ksr) {u_lol crd=CORD[thrk][b];if(!(crd&(wPCS_BITS|bPCS_BITS))){lisch=true;check_MASK.push_back(crd|movbit);}
                else lisch = false;}
            if (them & movbit) {
                dpthcntr[depth]++;
                //if (depth > 0){
                move_take(ROOK,ll);
                /*popPieceFromArray_L<CLR_P>(ee);
                                                moveTablePce_L<CLR_ATT>(ROOK, p, ee);psh++;
                                                        moves<CLR_P, CLR_ATT>(ll, depth, lisch);lisch = false;
                                                        if(depth==PERFT_DEPTH  )divide(p,ee);
                                                moveTablePce_L<CLR_ATT>(ROOK, ee, p);
                                                retBackPiece_L<CLR_P>();*/
                //}
            }else {dpthcntr[depth]++;
                //if (depth > 0){
                move_plain(ROOK,ll);
                //move_plain_lambda(ROOK,ll,p,ee,lisch);
                /*moveTablePce_L<CLR_ATT>(ROOK, p, ee);psh++;
                                                        moves<CLR_P, CLR_ATT>(ll, depth, lisch);lisch = false;
                                                        if(depth==PERFT_DEPTH  )divide(p,ee);
                                                moveTablePce_L<CLR_ATT>(ROOK, ee, p);*/
                //}
            }
        }//else dpthcntr[depth]+=popcnt(a3);
    }
    //p = Table[p].NEXT;
}

//######################################################## <bishop bit logic>
if constexpr(statAnalysis){cout << "bishop logic:";}
assert_kings();
lmvcp.IS_TK=0;
lmvcp.sig = BISHOP;
curr_pcs=us_ARR[BISHOP];
while(curr_pcs){
    int a=lsb(curr_pcs);
    curr_pcs^=1ull<<a;
    curr_pce_tbl_pos=toBigTable[63^a];
    if (bits1[curr_pce_tbl_pos] & all_bl || (isch  && !CKECK_MASK)) {
        lmvcp.FR_PO = curr_pce_tbl_pos;
        lmvcp_a.FR_PO = curr_pce_tbl_pos;
        for (int xx = 0; xx < 4; xx++) {
            int lp = curr_pce_tbl_pos;
            lp += BISHOP_DIRECTIONS[xx];
            whl_esq(lp) { { push_movs(lmvcp, lp); } lmvcp.sig = BISHOP;  cnt++; lp += BISHOP_DIRECTIONS[xx]; }
            if_clr(lp) {  markd(lp); push_movs(lmvcp_a, lp); }
        }
    }
    else {
        lmvcp.FR_PO = curr_pce_tbl_pos;
        bool lisch = false;
        u_lol rr = BISHOP_RAYS[63^a];
        u_lol rp = (rr & all_pcs)|(1ull<<a);
        rp *= magics_b_12[a];
        rp >>= 52;
        u_lol a2 = BISHOP_MASKS_BLCKS[a][rp];
        if (2) {}
        u_lol a3 = a2 &~us;
        if(CKECK_MASK  ){a3&=CKECK_MASK;}
        //if(depth>0)
        while (a3) {
            u_int b = msb(a3);
            u_lol movbit = 1ull << b;
            a3 ^= movbit;
            u_int ee = toBigTable[63 ^ b];
            if (movbit & th_ksb) {
                u_lol crd=CORD[thrk][b];
                if((depth>0)&&!(crd&(wPCS_BITS|bPCS_BITS))){lisch=true;check_MASK.push_back(crd|movbit);}
                else lisch = false;
            }
            if (them & movbit) {
                dpthcntr[depth]++;
                //if (depth > 0){
                move_take(BISHOP,lmvcp);
                /*popPieceFromArray_L<CLR_P>(ee);
                                        moveTablePce_L<CLR_ATT>(BISHOP, p, ee);psh++;
                                                moves<CLR_P, CLR_ATT>(lmvcp, depth, lisch);lisch = false;
                                                if(depth==PERFT_DEPTH  )divide(p,ee);
                                        moveTablePce_L<CLR_ATT>(BISHOP, ee, p);
                                        retBackPiece_L<CLR_P>();*/
                //}
            }
            else {
                dpthcntr[depth]++;
                //if (depth > 0){
                move_plain(BISHOP,lmvcp);
                //move_plain_lambda(BISHOP,lmvcp,p,ee,lisch);
                /*moveTablePce_L<CLR_ATT>(BISHOP, p, ee);psh++;
                                                moves<CLR_P, CLR_ATT>(lmvcp, depth, lisch);lisch = false;
                                                if(depth==PERFT_DEPTH  )divide(p,ee);
                                        moveTablePce_L<CLR_ATT>(BISHOP, ee, p);*/
                //}
            }
        } //else dpthcntr[depth]+=popcnt(a3);
    }
}
assert_kings();

//######################################################## <queen bit logic>
if constexpr(statAnalysis){cout << "queen logic:";}
lmvcp.sig = QUEEN;
lmvcp_a.sig = QUEEN;
curr_pcs=us_ARR[QUEEN];
while(curr_pcs){
    int a=lsb(curr_pcs);
    curr_pce_tbl_pos=toBigTable[63^a];
    curr_pcs^=1ull<<a;
    bool lisch=false;
    u_lol a3=attMaskStar(a,all_pcs)& ~us;
    if (1ull<<a & all_bl || (isch  && !CKECK_MASK)) {
        lmvcp.FR_PO = curr_pce_tbl_pos;
        lmvcp_a.FR_PO = curr_pce_tbl_pos;
        while(a3){
            int b=lsb(a3);
            a3^=1ull<<b;
            int lp=toBigTable[63^b];
            if (!((1ull<<b)&them)) {
                cnt++; push_movs(lmvcp, lp);
            }
            else {cnt++; push_movs(lmvcp_a, lp); }
        }
    }
    else {

        if(CKECK_MASK  ){a3&=CKECK_MASK;}
        auto pp=curr_pce_tbl_pos;
        //if(depth>0)
        while(a3){
            u_int b=msb(a3);
            u_lol movbit=1ull<<b;
            a3^=movbit;
            u_int ee=toBigTable[63-b];
            if(movbit&th_ks){
                u_lol crd=CORD[thrk][b];
                if(depth>0 && !(crd&(wPCS_BITS|bPCS_BITS))){lisch=true;check_MASK.push_back(crd|movbit);}
                else{ lisch= false;}
            }
            if(them &movbit){
                dpthcntr[depth]++;psh++;
                //if(depth>0){
                move_take(QUEEN,lmvcp);
                /*popPieceFromArray_L<CLR_P>(ee);
                                        moveTablePce_L<CLR_ATT>(QUEEN,p,ee);
                                        moves<CLR_P,CLR_ATT>(lmvcp,depth,lisch);lisch=false;
                                        if(depth==PERFT_DEPTH  )divide(p,ee);
                                        moveTablePce_L<CLR_ATT>(QUEEN,ee,p);
                                        retBackPiece_L<CLR_P>();*/
                //}
            }else{
                dpthcntr[depth]++;psh++;
                move_plain(QUEEN,lmvcp);
                //move_plain_lambda(QUEEN,lmvcp,p,ee,lisch);
                //if(depth>0){

                /*moveTablePce_L<CLR_ATT>(QUEEN,p,ee);

                                        moves<CLR_P,CLR_ATT>(lmvcp,depth,lisch);lisch=false;
                                        if(depth==PERFT_DEPTH  )divide(p,ee);
                                        //p=ee;
                                        moveTablePce_L<CLR_ATT>(QUEEN,ee,p);*/
                //}
            }//}

        }///----
        //else dpthcntr[depth]+=popcnt(a3);
    }
}
//######################################################## <king bit logic>
if constexpr(statAnalysis){cout << "king logic:";}
assert_kings();
curr_pcs=us_ARR[C2_KING];
while(curr_pcs){
    int a=lsb(curr_pcs);
    curr_pcs^=1ull<<a;
    curr_pce_tbl_pos=toBigTable[63-a];
    moveCPiece ll=lmvcp;
    ll.sig=C2_KING;
    if constexpr(CLR_ATT==WHITE){
        ll.WH_CSL=0;
        ll.WH_CSR=0;
    }else{
        ll.BL_CSL=0;
        ll.BL_CSR=0;
    }
    u_lol katt=KING_ATT[63-a];
    katt &= ~us;
    while(katt){
        int b=lsb(katt);
        katt^=1ull<<b;
        int lp=toBigTable[63-b];
        if (!((1ull<<b)&them)) {
            if (bits1[curr_pce_tbl_pos] & all_bl){markd(lp); push_movp_r(curr_pce_tbl_pos, lp);}
            else{
                moveTablePce_L<CLR_ATT>(C2_KING,curr_pce_tbl_pos,lp);
                if(king_ALL_Safety<CLR_ATT>()!=KING_VAL)
                {
                    int aa=0;
                    if (depth)
                        aa=moves<CLR_P,CLR_ATT>(ll,depth,0);
                    if(depth==PERFT_DEPTH  )divide(curr_pce_tbl_pos,lp);
                    psh++;
                    dpthcntr[depth]++;
                }
                moveTablePce_L<CLR_ATT>(C2_KING,lp,curr_pce_tbl_pos);
            }
        }
        else {

            if (bits1[curr_pce_tbl_pos] & all_bl){markd(lp); push_mov_a_r(curr_pce_tbl_pos, lp);}
            else{
                popPieceFromArray_L<CLR_P>(lp);
                moveTablePce_L<CLR_ATT>(C2_KING,curr_pce_tbl_pos,lp);
                if(king_ALL_Safety<CLR_ATT>()!=KING_VAL)
                {
                    if (depth)
                        moves<CLR_P,CLR_ATT>(ll,depth,0);
                    if(depth==PERFT_DEPTH  )divide(curr_pce_tbl_pos,lp);
                    psh++;
                    dpthcntr[depth]++;
                }
                moveTablePce_L<CLR_ATT>(C2_KING,lp,curr_pce_tbl_pos);
                retBackPiece_L<CLR_P>();
            }
        }
    }
}
//######################################################## <castle ?bit? logic>
if constexpr(statAnalysis){cout << "castle logic:";}
if constexpr (CLR_ATT == WHITE){
    int posk=toBigTable[63-ourk];
    moveCPiece ll=lmvcp;
    assert_kings();
    if(lmvcp.WH_CSL){
        if((all_pcs&0x70)==0){
            //if(Table[posk-1].PCE==EMPTY && Table[posk-2].PCE==EMPTY&& Table[posk-3].PCE==EMPTY){
            if(kingSafety<CLR_ATT , CLR_P>(posk)!=KING_VAL && kingSafety<CLR_ATT , CLR_P>(posk-1)!=KING_VAL && kingSafety<CLR_ATT , CLR_P>(posk-2)!=KING_VAL ){

                if(Table[91].PCE==ROOK && Table[91].STAT==1){
                    moveCPiece ll=lmvcp;
                    ll.WH_CSR=0;
                    ll.WH_CSL=0;
                    castle<CLR_ATT,CLR_P>(posk,91,depth,ll,-2,us_ks,th_ksr,th_ksb);
                }else lmvcp.WH_CSL=0;

            }
        }
    }
    if(lmvcp.WH_CSR){
        if((all_pcs&0x6)==0){
            //if(Table[posk+1].PCE==EMPTY && Table[posk+2].PCE==EMPTY){
            if((k1=kingSafety<CLR_ATT , CLR_P>(posk))!=KING_VAL&& (k2=kingSafety<CLR_ATT , CLR_P>(posk+1))!=KING_VAL&& (k3=kingSafety<CLR_ATT , CLR_P>(posk+2))!=KING_VAL){

                if(Table[98].PCE==ROOK && Table[98].STAT==2){
                    moveCPiece ll=lmvcp;
                    ll.WH_CSR=0;
                    ll.WH_CSL=0;
                    castle<CLR_ATT,CLR_P>(posk,98,depth,ll,2,us_ks,th_ksr,th_ksb);
                }else lmvcp.WH_CSR=0;

            }
        }
    }
}else{
    u_int posk=toBigTable[63-ourk];
    moveCPiece ll=lmvcp;
    ll.BL_CSR=0;
    ll.BL_CSL=0;
    if(lmvcp.BL_CSL){
        if((all_pcs&(0x70ull<<56))==0){
            ///if(Table[posk-1].PCE==EMPTY && Table[posk-2].PCE==EMPTY&& Table[posk-3].PCE==EMPTY){
            if(kingSafety<CLR_ATT , CLR_P>(posk)!=KING_VAL && kingSafety<CLR_ATT , CLR_P>(posk-1)!=KING_VAL && kingSafety<CLR_ATT , CLR_P>(posk-2)!=KING_VAL ){

                if(Table[21].PCE==ROOK && Table[21].STAT==1){
                    moveCPiece ll=lmvcp;
                    ll.BL_CSR=0;
                    ll.BL_CSL=0;
                    castle<CLR_ATT,CLR_P>(posk,21,depth,ll,-2,us_ks,th_ksr,th_ksb);
                }else lmvcp.BL_CSL=0;

            }
        }
    }
    if(lmvcp.BL_CSR){
        if((all_pcs&(0x6ull<<56))==0){
            //if(Table[posk+1].PCE==EMPTY && Table[posk+2].PCE==EMPTY){
            if(kingSafety<CLR_ATT , CLR_P>(posk)!=KING_VAL && kingSafety<CLR_ATT , CLR_P>(posk+1)!=KING_VAL && kingSafety<CLR_ATT , CLR_P>(posk+2)!=KING_VAL ){

                if(Table[28].PCE==ROOK && Table[28].STAT==2){
                    moveCPiece ll=lmvcp;
                    ll.BL_CSR=0;
                    ll.BL_CSL=0;
                    castle<CLR_ATT,CLR_P>(posk,28,depth,ll,2,us_ks,th_ksr,th_ksb);
                }
            }
        }
    }
}
	assert_eq_bts();
assert_kings();
//cout <<cnt<< ", ";
//if (isch) cout << "[ck]";
if constexpr(statAnalysis){cout << "end logic:";}
if(cnt){
	lastMoveCount.push_back(cnt);
	if(depth>=0){
		//if(isch) cout<<"\n[check][" << depth << "]\n";
	//cout << cnt << " "<< psh << ";";
		/*if(all_bl)cout<<".";
		cout << "<";
	for(auto x=0;x<cnt;x++){
		moveCPiece lk=vecMoves[vecMoves.size()-x-1];
		cout   << cpcs[lk.sig];
	}
	cout << ">";*/
		/*
	if (popcnt(all_bl)>2){
		printt();dbgptr_ull(all_bl);
	for(int xc=BLCK_RAY.size()-1;xc>BLCK_RAY.size()-1-popcnt(all_bl);xc--)dbgptr_ull(BLCK_RAY[xc]);
	}*/
	//if (psh==0)cout <<"####";
	}

	tryAllMoves<CLR_ATT,CLR_P>(depth,isch,us_ks,th_ksr,th_ksb);
	vecMoves.resize(vecMoves.size() - cnt);
	lastMoveCount.pop_back();
}
//if(all_bl)BLCK_RAY.resize(BLCK_RAY.size()-popcnt(all_bl));
	return 0;
}


#endif // !msattrcpp


