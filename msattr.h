#ifndef msattr_h
#define msattr_h

#include<iostream>
#include<vector>
#include<random>
#include<array>
#include <cstring>
#include <set>
//#include <intrin.h>
#include <xmmintrin.h>
#include "bbits.h"
//namespace justforkicks{
using namespace std;

typedef  unsigned char u_char;
typedef  unsigned int u_int;
typedef  unsigned long long u_lol;
struct mapToArray {
	unsigned int PCE : 5;
	unsigned int CLR : 2;
	unsigned int MAP : 7;
	unsigned int PROM : 5;
	unsigned int pad : 13;
};
struct mapToTable {
		 unsigned char PCE ;
		 unsigned char CLR ;
		 unsigned char MAP ;
		 unsigned char PREV ;
		 unsigned char NEXT ;
		 unsigned char STAT ;
		 unsigned char S1 ;
		 unsigned char S2 ;

	 }
//__attribute__((aligned(8)))
#ifdef __GNUC__
#endif
		;
struct  moveCPiece{
	unsigned char FR_PO;
	unsigned char TO_PO;
	unsigned char PROM;
	unsigned char sig;
	unsigned int WH_CSL:1;
	unsigned int WH_CSR:1;
	unsigned int BL_CSL:1;
	unsigned int BL_CSR:1;
	unsigned int IS_TK:1;
	unsigned int ANP_AV:1;
	unsigned int ANP_MOV:1;
	unsigned int ATT_SID:1;
	unsigned int GIV_CHK:1;
};
/*
struct  moveCPiece{
	unsigned int FR_PO:7;
	unsigned int TO_PO:7;
	unsigned int PROM:3;
	unsigned int WH_CSL:1;
	unsigned int WH_CSR:1;
	unsigned int BL_CSL:1;
	unsigned int BL_CSR:1;
	unsigned int IS_TK:1;
	unsigned int ANP_AV:1;
	unsigned int ANP_MOV:1;
	unsigned int ATT_SID:1;
	unsigned int sig:4;
};
*/


constexpr moveCPiece EMPTY_movePiece{0,0,0,0,0,0,0,0,0,0,0,0};
/*struct checkingPcs{
   unsigned char  PCE1;
   unsigned char  PCE2;
};
checkingPcs EMPTY_checkingPcs={0,0};*/
//static unsigned long long bhashes[8][64];
//static unsigned long long whashes[8][64];



//static u_lol ROOK_ATT_B[100];
//static u_lol ROOK_ATT_S[100];

//static u_lol BISHOP_ATT_B[100];
//static u_lol BISHOP_ATT_S[100];
u_lol diag=0x8040201008040201;
static u_lol lls[64];
static unsigned char att_arr[2048];
static u_lol dirs[256];
static u_lol WH_PAWN_ATT[64];
static u_lol BL_PAWN_ATT[64];
static u_lol BISHOP_RAYS[64];
static u_lol ROOK_RAYS[64];
static u_lol QUEEN_ATT_B[64];
static u_lol QUEEN_ATT_S[64];
static u_lol KNIGHT_ATT[64];
static u_lol KING_ATT[64];
static u_lol CORD[64][64];
static array<array<char,64>,64> rays_dir;
static array<array<unsigned long long,64>,8> rays;
static array<array<unsigned long long,64>,8> bhashes_;
static array<array<unsigned long long,64>,8> whashes_;
static signed char KNG_DIRS[64][64];
//const static unsigned long long BXOR = 0x1425763098acbdf;
static u_lol dpthcntr[7]={0,0,0,0,0,0,0};
static u_lol chckcnta[7]={0,0,0,0,0,0,0};
bool panic_dbg=false;
//static int chckcntr=0;
static int pushpopcntr=0;
enum {
	EMPTY=0,  V_PAWN , PROM, ROOK, BISHOP, KNIGHT, QUEEN, C2_KING, AN_PASS//, CR_KING, KING
};
enum{LEFT_TOP=21,RIGHT_TOP=28,LEFT_BOT=91,RIGHT_BOT=98,WH_KING=95,BL_KING=25,WH_V_PAWNS=81,BL_V_PAWNS=31};
enum{KING_VAL=50000};
enum{NO_CLR=0,WHITE,BLACK};
struct gmoves{
	mapToArray w;
	bool isch;
	bool istake;
	char FR_f;
	char FR_r;
	char TO_f;
	char TO_r;
};
//bool fst_loop=true;
static const char *cpcs[]={"0","P","M","R","B","N","Q","K","A"};
#define OFF_TABLE 0xff
#define ON_TABLE 0
#define HASH_SIZE 0x10000*0x100
#define HASH_DEPTH 1
#define PERFT_DEPTH 2
#define ASSERT_KINGS false
#define ASSERT_KING_SAFETY false
#define ASSERT_EQ_BITS false
struct mvv{
	unsigned char from;
	unsigned char to;
	unsigned char pce;
	unsigned char isch;
	unsigned char pch;
};
static const int TableLineFromRank[][8]={
	{91, 92, 93, 94, 95, 96, 97, 98 },
	{81, 82, 83, 84, 85, 86, 87, 88 },
	{71, 72, 73, 74, 75, 76, 77, 78 },
	{61, 62, 63, 64, 65, 66, 67, 68 },
	{51, 52, 53, 54, 55, 56, 57, 58 },
	{41, 42, 43, 44, 45, 46, 47, 48 },
	{31, 32, 33, 34, 35, 36, 37, 38 },
	{21, 22, 23, 24, 25, 26, 27, 28}
};

static const int TableColumneFromFile[][8]={
	{21, 31,  41,  51,  61,  71,  81,  91},
	{22,  32,  42,  52,  62,  72,  82,  92},
	{23,  33,  43,  53,  63,  73,  83,  93},
	{24,  34,  44,  54,  64,  74,  84,  94},
	{25,  35,  45,  55,  65,  75,  85,  95},
	{26,  36,  46,  56,  66,  76,  86,  96},
	{27,  37,  47,  57,  67,  77,  87,  97},
	{28,  38,  48,  58,  68,  78,  88,  98}};
const static char * Ranks=
"                    \
 88888888 \
 77777777 \
 55555555 \
 66666666 \
 44444444 \
 33333333 \
 22222222 \
 11111111 ";
static const u_lol mics_r[64]=
{0xcac009d80005800 , 0x651000a680700400, 0x621c005804080080, 0x794c402008001000, 0x1f18018980054800, 0xdd40028308400020, 0x9d00095200002100, 0x21b803a10000b008,
		 0xe361c80008204400, 0x4ec500080400,     0x7b8a100110006000, 0x99f5000088101100, 0x17bf000090480300, 0xd128002584500020, 0x39ad000982012040, 0xb06c4001c8001120,
		 0x1589e1181008000,  0xe21c082400400100, 0x28e23a0002010c40, 0xab21a60010000200, 0xd5a04a0001040200, 0x54df00400040020,  0x4d4c10c002802100, 0x6703849000800008,
		 0x148140084000,     0x4ae008a60800b000, 0xe470a20a0000400,  0xa8180c0410008120, 0x60000eab00010900, 0x240e840900100200, 0x428ca15400008108, 0xc191904380002820,
		 0x8320470ea0018000, 0xa298429000014000, 0xa43001120a000200, 0x33a0950286000120, 0x4452024306000090, 0x6513004980010a0,  0x1c29990240200100, 0x450620a102000c0,
		 0xc164044580148000, 0x20525c2840000200, 0x9a0e211024202000, 0x4a02131780200040, 0x901801dd80900800, 0x3960240500402400, 0xd0c61121c0840008, 0x20c3a08300000810,
		 0x222898e01001200 , 0x762181200c40200,  0x727b00a00300 ,    0xe0b042982d0c4200, 0x9800d40e86080b00, 0x6080240860804600, 0x4a1a528481001400, 0xe4c0e00480900840,
		 0xd3044e048020083e, 0x18c8d040e0800202, 0xf220190a50400202, 0x8eb10a0001248222, 0x4843067200008402, 0x2aa8aa444080102 , 0x74a6802440b10402, 0x1086208408104102};
array<array<u_lol,8192>,64>  ROOK_MASKS_BLCKS/*[64][16384]*/;
array<array<u_lol,4096>,64>  BISHOP_MASKS_BLCKS/*[64][16384]*/;

static const  u_lol mics_r13[64]=
{0xc0f7fe1002000300,  0x4a0006b080204200,  0xa9fffade11400200,  0xe200018288120020,  0x10000a100020408 ,  0xa00017400520028 ,  0xcc00059d04002048,  0xa70001a840108100,
 0xa8ef80120100    ,  0xbc71fffa80204200,  0x2862000288045200,  0xd8d2000528022200,  0xffb5fffb005c0200,  0x55e6000280440108,  0x103fff782050048 ,  0xe8b50fff03000008,
 0xffffda5480000800,  0x2c00515001244000,  0x6762020002900840,  0xef65720002000420,  0x98cb8a0001100200,  0xf86fbe0004810408,  0x54a8fc0000208a08,  0x37fffe6002840012,
 0xfffef12a88022200,  0xf9e0734200060080,  0x4ca6aa2200020040,  0xe360cc7a00010a00,  0xd503108a00048600,  0x880c570e00008a00,  0x44c4ea4600010084,  0x3fffffc680800408,
 0xffff6f4400908000,  0x1cc0233082000600,  0xfba06e7842000200,  0xa0c3316226000200,  0x6157873406000200,  0x42df97c306000200,  0x4758e0c94c000048,  0x740003a6612000d0,
 0x87e2719880408000,  0x47cfb3bfe0000200,  0x6200803002011000,  0x60002c2d040a0002,  0xb0000a880800d800,  0x1a1f418102000400,  0xef4991c102040008,  0xb6000395801e2002,
 0x840a00bf21005200,  0xf4de5c4e00044200,  0x13ebd35c82000600,  0x1d5f1e2512000200,  0xe9ae005601008600,  0x2e2507c804018200,  0xec0406e881024200,  0xce51f2a100408200,
 0x2a11a04a01004082,  0x9442481200a08052,  0x4000b07620400202,  0xe000086600214c02,  0xd6000ab81014010a,  0xde00030984004812,  0x1323af8800410204,  0x2e000425810010c2 };

 static const u_lol magics_b_12[64]=
{0xb4ad9f1140200040, 0x48cd47c00400800 , 0x1e9aa4e100407000, 0xb872426d33020000, 0x8bed736880400d00, 0xadf500add000c028, 0xa09c428d84010500, 0x88449f442000504 ,
 0xdf2e9f5b02940400, 0x83d8983080020008, 0x222256de01010000, 0xf067b9a7c0080001, 0xd6134fe00a000040, 0x9a96bc4e90030006, 0x92954ace8015a100, 0x732f321492414080,
 0x63703d9008080060, 0x582981541800b010, 0xe076a59500048008, 0xfeae43ae04000200, 0x42aa981380200000, 0xb54a65ce04000800, 0x1054f87a0303000 , 0x8b6f078b8040c404,
 0x8c1864ed002200a4, 0xeb91c3eb80204080, 0xf1be1ba80d000400, 0xb0a2002000640004, 0x2efffb7808802000, 0x546017ec000a0800, 0x66b8435c09908200, 0x938ed69116800140,
 0x2a8acca008201b0 , 0xb8f578d8d0000801, 0x7425401304020800, 0x4600030101000400, 0xa581224080010080, 0x570c214080005000, 0xcca5b93050c48800, 0x1f8ebd5280012008,
 0x56a9459023420080, 0x502103ae00081020, 0xb442b5f481000200, 0xf2baeb0300090280, 0x6383987684004010, 0xb8f2e4ea00200a00, 0x2ad562d200600010, 0x4252dba481228080,
 0x4c32a12504e00101, 0x14464ad483008800, 0xe33c79e080050000, 0x18c9c66080809020, 0xdda8e5c240200a08, 0x34033ff634010240, 0xfda0886282005400, 0x54398f3740400100,
 0x48bf653aa0a00840, 0x79c0f44500010404, 0xb560c01ec0401004, 0x1c5e1dc3c0100818, 0xbeafeb2f42042024, 0x3fc84ec6020020c0, 0x15716f3f84080008, 0xb6930d4504010841};

		const int index64[64] = {
			0, 47,  1, 56, 48, 27,  2, 60,
		   57, 49, 41, 37, 28, 16,  3, 61,
		   54, 58, 35, 52, 50, 42, 21, 44,
		   38, 32, 29, 23, 17, 11,  4, 62,
		   46, 55, 26, 59, 40, 36, 15, 53,
		   34, 51, 20, 43, 31, 22, 10, 45,
		   25, 39, 14, 33, 19, 30,  9, 24,
		   13, 18,  8, 12,  7,  6,  5, 63
		};
		int bitScanForward(u_lol bb) {
		   const u_lol debruijn64 = u_lol(0x03f79d71b4cb0a89);
		   return index64[((bb ^ (bb-1)) * debruijn64) >> 58];
		}
	   /*
   struct mapToTable {
	unsigned int PCE : 5;
	unsigned int CLR : 2;
	unsigned int MAP : 7;
	unsigned int PREV : 7;
	unsigned int NEXT : 7;
	unsigned int pad : 4;
};*/
		static u_lol sum_try=0;
constexpr static u_lol bits1[120]={
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0x8000000000000000, 0x4000000000000000, 0x2000000000000000, 0x1000000000000000, 0x800000000000000, 0x400000000000000, 0x200000000000000, 0x100000000000000,0,
		0,0x80000000000000, 0x40000000000000, 0x20000000000000, 0x10000000000000, 0x8000000000000, 0x4000000000000, 0x2000000000000, 0x1000000000000,0,
		0,0x800000000000, 0x400000000000, 0x200000000000, 0x100000000000, 0x80000000000, 0x40000000000, 0x20000000000, 0x10000000000,0,
		0,0x8000000000, 0x4000000000, 0x2000000000, 0x1000000000, 0x800000000, 0x400000000, 0x200000000, 0x100000000,0,
		0,0x80000000, 0x40000000, 0x20000000, 0x10000000, 0x8000000, 0x4000000, 0x2000000, 0x1000000,0,
		0,0x800000, 0x400000, 0x200000, 0x100000, 0x80000, 0x40000, 0x20000, 0x10000,0,
		0,0x8000, 0x4000, 0x2000, 0x1000, 0x800, 0x400, 0x200, 0x100,0,
		0,0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0};

const static int firstBPce[]={0,11,0,13,14,15,16,17};
const static int firstWPce[]={0,2,0,4,5,6,7,8};
#define fill_mapToTable(pmt,pc,cl,ma,pa) pmt.PCE=pc;\
	pmt.CLR=cl;\
	pmt.MAP=ma;\
	pmt.STAT=pa;
static  constexpr mapToTable EMPTY_mapToTable{0,0,0,0,0,0};
static constexpr short KNIGHT_JUMPS[]={-21,-19,-12,-8,8,12,19,21};
static constexpr short QUEEN_DIRECTIONS[]={-11,-10,-9,-1,1,9,10,11};
static constexpr short ROOK_DIRECTIONS[]={-10,-1,1,10};
static constexpr short BISHOP_DIRECTIONS[]={-11,-9,9,11};
static constexpr int WHITE_PAWN_ATTACK[]={-11,-9};
static constexpr int WHITE_PAWN_MOVE[]={-10,-20};
static constexpr int BLACK_PAWN_ATTACK[]={11,9};
static constexpr int BLACK_PAWN_MOVE[]={10,20};
 /*template <int T> struct _spcs{};
 template<> struct _spcs<BLACK>{
	u_lol PCS_btARR[8];
	u_lol PCS_BITS;
};
 template<> struct _spcs<WHITE>{
	u_lol PCS_btARR[8];
	u_lol PCS_BITS;
};*/
/*struct moveStr{
	unsigned int PCE : 5;
	unsigned int CLR : 2;
	unsigned int FROM : 7;
	unsigned int TO : 7;
};*/
u_lol falsep={};
u_lol falsea={};
struct stinf{
	//stinf(array<array<unsigned long long,64>,8> *b_hashes,array<array<unsigned long long,64>,8> *w_hashes):fhashes(b_hashes),shashes(w_hashes){}
	//unsigned char enp_rank;
	unsigned char clr,otclr;
	unsigned char lro_pos,rro_pos,ko_pos;
//char pawnVrank, pawnPrank;
mapToTable * fpieces,*spieces;
//int * pawn_mov, *pawn_att;
stinf *other;
array<array<unsigned long long,64>,8> *fhashes;
array<array<unsigned long long,64>,8> *shashes;
//unsigned long long (&fhashes)[8][64];
//unsigned long long (&shashes)[8][64];
};
//constexpr u_lol bPCS_btAR[]={0,0,0,0,0,0,0,0};
static char ranksFiles [100][3]=
{"0","0","0","0","0","0","0","0","0","0",
"0","0","0","0","0","0","0","0","0","0",
 "0","a8","b8","c8","d8","e8","f8","g8","h8","0",
 "0","a7","b7","c7","d7","e7","f7","g7","h7","0",
 "0","a6","b6","c6","d6","e6","f6","g6","h6","0",
 "0","a5","b5","c5","d5","e5","f5","g5","h5","0",
 "0","a4","b4","c4","d4","e4","f4","g4","h4","0",
 "0","a3","b3","c3","d3","e3","f3","g3","h3","0",
 "0","a2","b2","c2","d2","e2","f2","g2","h2","0",
 "0","a1","b1","c1","d1","e1","f1","g1","h1","0",
};
static char  pname[][10] = { "ZERO", "V_PAWN", "M_PAWN", "ROOK", "BISHOP", "KNIGHT", "QUEEN", "C2_KING" };
static char  pcolor[][6] = { "White", "Black" };
unsigned int toBigTable[64];
unsigned int toRegularTable[128];

static char mapBrdTbl2file[120];
static char mapBrdTbl2rank[120];

static char dbgt64[] = { "0000000000000000000000000000000000000000000000000000000000000000" }; // debug
 struct msatr {
	u_lol*ulp;
	stinf bsinf,wsinf;
	vector<mapToArray> wpieces[8];
	vector<mapToArray> bpieces[8];
	mapToTable *blpieces;
	mapToTable *wlpieces;
	vector<u_lol> check_MASK;
	vector<u_lol> BLCK_RAY;
	vector<int> weighs;
	vector<mapToTable> takenPieces;
	vector<moveCPiece> vecMoves;
	vector<moveCPiece> MoveSeq;
	//vector<mvv> moveTrain;
	vector<int> lastMoveCount;
	mapToTable Table[120];
	static u_lol bPCS_btARR[8];
	static u_lol wPCS_btARR[8];
	static u_lol wPCS_BITS,bPCS_BITS;
	unsigned long long hash;
	unsigned long long *wHASH_ap;
	unsigned long long *bHASH_ap;
	set<u_lol> masks;
	//u_lol their_ks;
	template <int CLR_ATT ,int CLR_P>
	array<u_lol,2> kingXSafety(u_lol pos);
	void prom(vector<mapToArray>(&pieces)[8], int PCE, int PR_PCE, int MAP);
	void assert_consist();
	void emptyHash();
	bool winsert_hash(unsigned long long in);
	bool binsert_hash(unsigned long long in);
	void printt();
	template <int CLR_ATT> int weight_npcs();
	u_lol attMaskStar(u_lol pos,u_lol mask);
	array<u_lol, 2> kingRSafety(int pos, u_lol mask1, u_lol mask2);
	template <int clr_a,int clr_p>
	int  p_KingSafety(u_lol posk, u_lol posp, u_lol post,u_lol ksft);
	template <int CLR_ATT,int CLR_P>
	int p_XKingSafety(u_lol posk, u_lol posp, u_lol post, u_lol ksft,u_lol ksfb);
	template <int clr_a,int clr_p>
	int attKingSafety(u_lol posk, u_lol posp, u_lol post,u_lol ksft);
	int kingSafety1Dir(int pos,int dir);
	template <int clr_a,int clr_p>
	int kingSafety(u_int pos);
	template <int CLR_P>
        int king_ALL_Safety();
	template <int CLR_ATT ,int CLR_P>
	array<u_lol,2> kingBSafety(u_lol pos,u_lol mask);
	template <int CLR_ATT ,int CLR_P>
	array<u_lol,2> dbgkingBSafety(u_lol pos);
	u_lol king_PLUS_Safety(int pos, u_lol mask1);
	u_lol king_XRAY_Safety(int pos, u_lol mask2);
	template <int clr_a,int clr_p>
	void tryAllMoves(int depth, bool isch,u_lol _ksft,u_lol gg1,u_lol gg2);
	void prom_L(u_lol FR_POS_, /*u_lol TO_POS_,*/u_lol PROM_PCE);
	void undoProm_L(u_lol FR_POS_, /*u_lol TO_POS_,*/u_lol PROM_PCE);
	void applyMove(gmoves &tmove, int CHRG_PCE, int CHRG_POS, int TARG_PCE, int TARG_POS);
	void movePawn(vector<mapToArray>(&pieces)[8], int CHRG_PCE, int CHRG_POS, int TARG_PCE, int TARG_POS, int PROM);
	void moveTablePce(vector<mapToArray>(&pieces)[8], int CHRG_PCE, int CHRG_POS, int TARG_POS);
	template <int clr_a,int clr_p>
	int moves(moveCPiece lmvcp, int depth, bool isch);
	bool retBackPiece(vector<mapToArray>(&pieces)[8]);
	void popPieceFromArray(vector<mapToArray> (&pieces)[8],int TARG_PCE,int TARG_POS);

	template <int clr_a,int clr_p>
	void castle(u_lol posk, u_lol posr, u_lol depth, moveCPiece lmvcp,  int side,u_lol _ksft,u_lol gg1,u_lol gg2);
	template <int CLR_P>
	bool retBackPiece_L();
	template <int CLR_ATT>
        void moveTablePce_L(unsigned char PCE,unsigned char CHRG_POS,unsigned char TARG_POS);
	template <int CLR_P>
	void popPieceFromArray_L( int TARG_POS);
	bool makeMoveFromFile(gmoves & tmove);
	void init_hashes();
	void dbgptr();
	moveCPiece fenParser(string instr);
	void strl(u_lol from,u_lol to){Table[to]=Table[from];Table[from]=EMPTY_mapToTable;}
	void assert_eq_bts();
	void assert_kings();
	template <int CLR_P,int CLR_ATT>
	int assert_kingSafety(u_int pos);
	void divide(int FR_POS_,int TO_POS_);
	void bits66(u_lol &blck_mask,u_lol& bit_mask, u_lol& att_mask, int pos, u_char ihor, u_char iver) ;
	void bits67(u_lol &blck_mask,u_lol& bit_mask, u_lol& att_mask, int pos, u_char ihor, u_char *i);
	/*template <int T> void xorbits(u_lol IN,u_lol PCE);
	template <>  void xorbits<BLACK>(u_lol IN,u_lol PCE){
		bPCS_btARR[PCE]^=IN;
		bPCS_BITS^=IN;
	}
	template <>  void xorbits<WHITE>(u_lol IN,u_lol PCE){
		bPCS_btARR[PCE]^=IN;
		bPCS_BITS^=IN;
	}*/

	void dbgptrmoves(){
		for (int x = 0; x < 64; x++){dbgt64[x]='0';}
		/*for (int x = 0; x < 8; x++) {
		for (int xi = 0; xi < 8; xi++) {
			int d = 21 + xi * 10 + x;
			cout << dbgt64[x * 8 + xi] << " ";
		}
		cout << "\n";
		}*/
		cout << "\n***********************\n";
	};
	msatr();
	void initb();
};

void msatr::init_hashes()
{
	return;
	struct s{
	   uint32_t f;
	   uint32_t s;
	};
	union{
		s ls;
		unsigned long long m;
	};
	mt19937 mt;

	ls.f=mt();
	ls.s=mt();
	hash=m;
	for (int xo=0;xo<8;xo++){
		for (int x=0;x<64;x++){
			ls.f=mt();
			ls.s=mt();
			bhashes_[xo][x]=m;
			ls.f=mt();
			ls.s=mt();
			whashes_[xo][x]=m;
		}
	}
	ls.f=mt();
	ls.s=mt();
	hash=m;
	int x=0;
	wHASH_ap = new unsigned long long[HASH_SIZE];
	bHASH_ap = new unsigned long long[HASH_SIZE];
	for( x=0;x<HASH_SIZE;x++){
		wHASH_ap[x]=0;
		bHASH_ap[x]=0;
	}
	cout<<x;
	int idx=(hash&0xfffff)*0x10;
	wHASH_ap[idx]=hash;
	//unsigned long long‭
	emptyHash();
}

void msatr::emptyHash()
{
	memset(wHASH_ap,0,sizeof(u_lol)*HASH_SIZE);
	memset(bHASH_ap,0,sizeof(u_lol)*HASH_SIZE);
	/*int x=0;
	for( x=0;x<HASH_SIZE;x++){
		wHASH_ap[x]=0;
		bHASH_ap[x]=0;
	}*/
}
int hashw=0,hashb=0;
int xashw=0,xashb=0;
bool msatr::winsert_hash(unsigned long long in){
	if(in==8087056252371640873){
		printt();
		cout <<"++"<<in<<"\n";
	}
	//return true;
	int bidx,idx=(in&0xfffff)*0x10;
	bidx=idx;
	/*while(HASH_ap[idx]!=in){
		if cerr<<"^";
	}*/
	if(in==0)cout <<"0";
	while(1){
	   unsigned long long p= wHASH_ap[idx];
	   if (in==p){xashw++; return false;}
	   if (p==0){
		   hashw++;
		   wHASH_ap[idx]=in;
		   return true;
	   }
	   idx++;
	   if(idx-bidx >15){
		   cerr<<"Bucket overflow ";
		   return true;
	   }
	}
}

bool msatr::binsert_hash(unsigned long long in){
	//return true;
	int bidx,idx=(in&0xfffff)*0x10;
	bidx=idx;
	/*while(HASH_ap[idx]!=in){
		if cerr<<"^";
	}*/
	//cout << in << "\n";
	while(1){
	   unsigned long long p= bHASH_ap[idx];
	   if (in==p){/* cerr <<".";*/xashb++; return false;}
	   if (p==0){
		   bHASH_ap[idx]=in;
		   hashb++;
		   return true;
	   }
	   idx++;
	   if(idx-bidx >15){
		   cerr<<"Bucket overflow ";
		   return true;
	   }
	}
}
//}
#endif
