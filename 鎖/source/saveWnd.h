#ifndef	_MY_SAVEWND

#define MAX_CHAR	4
#define WAVE_BUFFER_NUM			16
#define WAVE_STREAM_NUM			4
#define WAVE_SOUND_NUM			(WAVE_BUFFER_NUM-WAVE_STREAM_NUM)

#include "escript.h"

typedef struct{
	int		sk_flag;
	int		sk_dir;
	int		sk_pich;
	int		sk_type;
	int		bs_bno;			
	int		bs_x, bs_y;		
	int		bs_w, bs_h;		
	int		bs_cg;			
	int		bs_effect;		

	int		bs_flag;		
	int		bs_rate;		
	int		bs_fade;		

	int		bs_zoom;		
	int		bs_cscop;		
	int		bs_tone;		
	int		bs_tone2;		
	int		bs_tone_ch;		
	int		bs_tone_bk;		
	int		cs_flag[MAX_CHAR];		
	int		cs_cno[MAX_CHAR];		
	int		cs_pose[MAX_CHAR];		
	int		cs_loc1[MAX_CHAR];		
	int		cs_layer[MAX_CHAR];		
	int		cs_fade[MAX_CHAR];		
	int		cs_alph[MAX_CHAR];		
	char	ms_flag;			
	char	ms_wflag;			
	char	ms_cno;				
	short	ms_wait;			
	short	ms_wait_op;			

	char	ms_add;			
	char	ms_disp;		
	char	ms_step1;		
	short	ms_count;		
	short	ms_kstep;		
	short	ms_max;			
	
	char	ms_str[1024];		

	int		sw_flag;			
	int		sw_ex;				
	int		sw_mnum;			
	char	sw_mes[8][28*2*4];	
	char	sw_sno[8][6];	
	char	sw_no[8];			
	char	sw_value[8];		

	int		ws_flag;		
	int		ws_wno;			
	int		ws_twind;		
	int		ws_tspeed;		
	int		ws_tamount;		
	int		we_flag;		
	int		we_type;		
	int		we_ewav;		
	int		pm_mus_no[WAVE_STREAM_NUM];	
	int		pm_mode[WAVE_STREAM_NUM];	
	int		pm_loop[WAVE_STREAM_NUM];		
	int		pm_next_vol[WAVE_STREAM_NUM];	
	int		mainRoomNo;				
	int		subRoomNo;				
	int		ss_flag[WAVE_SOUND_NUM];	
	int		ss_se_no[WAVE_SOUND_NUM];	
	int		ss_loop[WAVE_SOUND_NUM];	
	int		ss_vol[WAVE_SOUND_NUM];		
	int		bs_r,bs_g,bs_b;
}AVG_SAVE_DATA;

typedef struct{
	int			ver_no;		
	int			sin_no;		
	SYSTEMTIME	sys_time;	

	char		message[42];
	char		chapter[22];
}SAVE_HEADER;

struct SAVE_STRUCT{
	SAVE_HEADER		save_head;

	EXEC_DATA 		EXEC_LangInfo;					
	char			NowLangFileName[16];			
	int				RunLangBlockNo;
	int				PrevRunLangBlockNo;

	int				ESC_FlagBuf[ ESC_FLAG_MAX ];
	AVG_SAVE_DATA	sdata;

	SAVE_STRUCT(){
		Reset();
	}
	void Reset(){
		ZeroMemory(this,sizeof(SAVE_STRUCT));
		strcpy(save_head.chapter, "章タイトル未設定");
	}
};

struct MySaveHead
{
	char	head[4];
	WORD	ver;
};

enum SaveWndState{
	save_fadein = 0,
	save_fadeout,
	save_exec,
	save_writeSure,
	save_writeExec,
	save_loadSure,
	save_writeEnd,
	save_loadEnd,
};

class SaveWnd
{
	SaveWndState state;
	float		alpha;
	BYTE		selectNum;
	BYTE		offsetNum;
	BYTE		btnSelect;
	BYTE		new_time;
	BYTE		newMark;
	BYTE		bYesNo;
	BYTE		useTable[50];
	time_t		file_time[50];
	exec_mode	mode;
	DWORD		startTime;
	ColorBuf	panel[3];
	ColorBuf	button;
	ColorBuf	pagebutton;
	ColorBuf	numParts;
	ColorBuf	newParts;
	ColorBuf	backWnd;
	ColorBuf	infoWnd;
	ColorBuf	retBtnPrt;
	ColorBuf	confirmWnd;
	ColorBuf	yesNoWnd;
	ColorBuf	backupWnd;
	ColorBuf	maskWnd;
	MyButton	btn[3];
	MyButton	pageBtn[10];
	MyButton	yesnoBtn[2];
public:
	BYTE		bFadeOut;
	ColorBuf	saveBmp;
	exec_mode	bak_mode;
	char		voicefile[32];

	SaveWnd(exec_mode s_mode);
	~SaveWnd(){
		Release();
	}
	void Release(){
		int		i;
		for(i=0;i<3;i++)panel[i].Release();
		button.Release();
		pagebutton.Release();
		numParts.Release();
		newParts.Release();
		backWnd.Release();
		infoWnd.Release();
		retBtnPrt.Release();
		confirmWnd.Release();
		yesNoWnd.Release();
		backupWnd.Release();
		EnableMenuItem( sysInf.hMenu,ID_LOADEXEC,   MF_ENABLED  );
		EnableMenuItem( sysInf.hMenu,ID_SAVEEXEC,   MF_ENABLED  );
	}
	void CreateInfo(void);
	void Blt(void);
	void time_info(int x,int y,exec_mode mode,char *tbuf);
	void TextOutSaveMsg(int x, int y, char *msg);
	BOOL selectExec(void);
	void SetAlpha(void){
		for(int i=0;i<3;i++)panel[i].alpha = alpha;
		backWnd.alpha = button.alpha = pagebutton.alpha = numParts.alpha = newParts.alpha = infoWnd.alpha = confirmWnd.alpha = yesNoWnd.alpha = retBtnPrt.alpha = alpha;
		maskWnd.alpha = alpha *0.5f;
	}
};

void SAV_Save( int save_no );
BOOL SAV_Load( int save_no );
void saveMessage(BYTE *msgBuf);
void saveChapterTitle(char *msg);
void SetRoomNo(int mainRoom, int subRoom);

extern SaveWnd		*saveWnd;
extern SAVE_STRUCT	SaveStruct;

#define	_MY_SAVEWND
#endif	_MY_SAVEWND