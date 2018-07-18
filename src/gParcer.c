
#line 1 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
/*
 * A mini G_Code language scanner.
 */


#include "gParcer.h"
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stddef.h>


//#define BUFLEN 512

typedef void (*gfunction)(size_t, char *, size_t );  // Declare typedef

#define INPUT_BUFSIZE 1024

#define FLOG



enum prsCmd{
	eCommand, eComment, eGcommand, eXparam, eOcommand
 	,eStarparam,ePunct
	
};


typedef void (*WriteFunc)( char *data, int len );

struct format
{
	char* buf;	//char buf[BUFLEN+1];
	int buflen;
	WriteFunc write;

	int flags;
	int width;
	int prec;
	int cs;
	//--------
	int act;
	char* te;
	char* ts;
	char* p;
	char* pe;
	char* eof;
	int done;	// Исполнение текущего тега.
	int have;
	int curline;
	int space;
	int eofile;
	int lenfile;
	uint state;
	int top;
	int stack[100];
};

//#define curline	fsm->curline

//------------------- vars

static const int format_start = 11;
static const int format_first_final = 11;
static const int format_error = 0;

char buf[INPUT_BUFSIZE];


//	int have = 0, curline = 1;
//	char *ts, *te = 0;
//	int done = 0;


	FILE *fp;
	FILE *flog;
//static void (* parser_out)(size_t number, char * param, size_t len);

static gfunction parser_out;

 void command (size_t curline, char * param, size_t len);
 void gcomment (size_t curline, char * param, size_t len);
 void g_command (size_t curline, char * param, size_t len);
 void x_coordinate(size_t curline, char * param, size_t len);
 void o_command (size_t curline, char * param, size_t len);

 //fprintf(flog, "symbol(%i): %c\n", fsm->curline, fsm->ts[0] );
 void gpunct(size_t curline, char * param, size_t len);

gfunction prs[] = {&command,&gcomment,&g_command,&x_coordinate, &o_command
		, &gpunct };


// g Command
 void command (size_t curline, char * param, size_t len){
#ifdef FLOG
		fprintf(flog, "Command(%lu): ", curline );
		fwrite( param, 1, len, flog );  
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_command(curline,param,len);
#endif
}

#define gBUFFER_SIZE	100 
 
 char gBuffer[gBUFFER_SIZE];
 
 size_t buffer_index = 0;
 size_t param_index;
 size_t gts;

void append(char ch)
{
	gBuffer[buffer_index++] = ch;
}

void resetBuffer()
{
	gts = 0;
	buffer_index = 0;
	param_index = 0;
	memset(gBuffer,0,gBUFFER_SIZE);
}


// g comment
 void gcomment (size_t curline, char * param, size_t len){
#ifdef FLOG
		fprintf(flog, "gcomment(%lu): ", curline );
		fwrite( param, 1, len, flog );  
		fprintf(flog,"\n");
#endif
#ifdef SCANNER		
		b_gcomment(curline,param,len);
#endif
}

// g GXX.X digit 		=command=	command GXX.X
 void g_command (size_t curline, char * param, size_t len){
#ifdef FLOG	 
		fprintf(flog, "command line(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER		
		b_g_command (curline, param, len);
#endif
}

// g X coordinate
 void x_coordinate(size_t curline, char * param, size_t len)
{
#ifdef FLOG
	 fprintf(flog, "\t parameter line(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER		
		b_x_coordinate (curline, param, len);
#endif
}

 // O command
void o_command (size_t curline, char * param, size_t len){
#ifdef FLOG
	 fprintf(flog, "command line(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER		
		b_o_command (curline, param, len);
#endif

}
 
// g *	digit		Checksum 


void gpunct(size_t curline, char * param, size_t len)
{
#ifdef FLOG
	fprintf(flog, "symbol(%lu): %c\n", curline, *param );
#endif
#ifdef SCANNER
	b_punct(curline, param, len);
#endif	
}




// 		punct			Symbols.


#line 427 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"



#line 206 "/home/walery/workspace_cdt/Strlen/src/gParcer.c"
static const char _gparcer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 6, 1, 7, 1, 8, 1, 
	9, 1, 10, 2, 5, 1, 2, 6, 
	1, 2, 6, 3, 2, 7, 0, 2, 
	7, 4, 2, 8, 3, 2, 9, 0, 
	2, 9, 6, 2, 10, 0, 3, 6, 
	5, 1
};

static const unsigned char _gparcer_key_offsets[] = {
	0, 0, 1, 4, 5, 10, 14, 16, 
	18, 21, 25, 27, 31, 33, 36, 38, 
	43, 52, 53, 64, 80, 82, 96, 98, 
	111, 114, 116, 120, 133, 138, 138, 139, 
	142, 150, 159, 161, 162, 165, 171, 176, 
	179, 182, 182, 182
};

static const char _gparcer_trans_keys[] = {
	41, 127, 0, 31, 41, 127, 0, 31, 
	32, 126, 41, 127, 0, 31, 48, 57, 
	48, 57, 127, 0, 31, 43, 45, 48, 
	57, 48, 57, 10, 46, 48, 57, 48, 
	57, 10, 48, 57, 48, 57, 10, 32, 
	46, 48, 57, 10, 32, 40, 42, 59, 
	65, 90, 97, 122, 41, 10, 32, 40, 
	42, 59, 9, 13, 65, 90, 97, 122, 
	10, 32, 40, 42, 43, 45, 46, 59, 
	9, 13, 48, 57, 65, 90, 97, 122, 
	48, 57, 10, 32, 40, 42, 46, 59, 
	9, 13, 48, 57, 65, 90, 97, 122, 
	48, 57, 10, 32, 40, 42, 59, 9, 
	13, 48, 57, 65, 90, 97, 122, 127, 
	0, 31, 48, 57, 10, 32, 48, 57, 
	10, 40, 59, 70, 71, 77, 79, 0, 
	82, 83, 84, 85, 127, 10, 40, 59, 
	0, 127, 10, 10, 40, 59, 10, 40, 
	59, 127, 0, 31, 32, 126, 10, 40, 
	41, 59, 127, 0, 31, 32, 126, 10, 
	41, 41, 127, 0, 31, 10, 40, 46, 
	59, 48, 57, 10, 40, 59, 48, 57, 
	10, 40, 59, 10, 40, 59, 10, 32, 
	40, 42, 59, 9, 13, 65, 90, 97, 
	122, 0
};

static const char _gparcer_single_lengths[] = {
	0, 1, 1, 1, 1, 2, 0, 0, 
	1, 2, 0, 2, 0, 1, 0, 3, 
	5, 1, 5, 8, 0, 6, 0, 5, 
	1, 0, 2, 7, 3, 0, 1, 3, 
	4, 5, 2, 1, 1, 4, 3, 3, 
	3, 0, 0, 5
};

static const char _gparcer_range_lengths[] = {
	0, 0, 1, 0, 2, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	2, 0, 3, 4, 1, 4, 1, 4, 
	1, 1, 1, 3, 1, 0, 0, 0, 
	2, 2, 0, 0, 1, 1, 1, 0, 
	0, 0, 0, 3
};

static const unsigned char _gparcer_index_offsets[] = {
	0, 0, 2, 5, 7, 11, 15, 17, 
	19, 22, 26, 28, 32, 34, 37, 39, 
	44, 52, 54, 63, 76, 78, 89, 91, 
	101, 104, 106, 110, 121, 126, 127, 129, 
	133, 140, 148, 151, 153, 156, 162, 167, 
	171, 175, 176, 177
};

static const char _gparcer_indicies[] = {
	1, 0, 1, 1, 2, 4, 3, 1, 
	1, 5, 2, 8, 7, 7, 6, 9, 
	10, 11, 10, 13, 13, 12, 14, 14, 
	15, 10, 15, 10, 16, 17, 15, 10, 
	18, 10, 16, 18, 10, 19, 10, 20, 
	21, 22, 19, 10, 23, 24, 25, 26, 
	27, 26, 26, 10, 29, 28, 31, 30, 
	25, 26, 27, 30, 26, 26, 10, 33, 
	32, 34, 35, 36, 36, 37, 39, 32, 
	38, 35, 35, 10, 38, 10, 33, 32, 
	34, 35, 37, 39, 32, 38, 35, 35, 
	10, 40, 10, 33, 32, 34, 35, 39, 
	32, 40, 35, 35, 10, 29, 29, 41, 
	42, 10, 20, 21, 42, 10, 44, 45, 
	46, 47, 48, 48, 49, 10, 47, 10, 
	43, 51, 0, 2, 10, 50, 10, 51, 
	10, 52, 53, 54, 10, 55, 56, 57, 
	1, 1, 5, 2, 58, 56, 60, 56, 
	7, 7, 59, 6, 61, 1, 0, 1, 
	0, 1, 1, 2, 51, 0, 62, 2, 
	9, 10, 51, 0, 2, 11, 10, 51, 
	0, 2, 10, 63, 64, 65, 10, 10, 
	10, 31, 30, 25, 26, 27, 30, 26, 
	26, 10, 0
};

static const char _gparcer_trans_targs[] = {
	1, 30, 2, 3, 31, 32, 5, 34, 
	36, 37, 0, 38, 8, 40, 10, 11, 
	41, 12, 13, 15, 42, 16, 25, 42, 
	16, 17, 19, 24, 17, 18, 18, 43, 
	18, 43, 17, 19, 20, 22, 21, 24, 
	23, 24, 26, 28, 29, 3, 4, 6, 
	39, 8, 28, 29, 29, 1, 2, 30, 
	33, 32, 34, 33, 32, 35, 7, 29, 
	1, 2
};

static const char _gparcer_trans_actions[] = {
	0, 9, 0, 0, 9, 0, 0, 9, 
	9, 3, 0, 3, 0, 0, 0, 0, 
	7, 0, 0, 3, 34, 13, 5, 7, 
	0, 19, 19, 19, 3, 22, 0, 7, 
	9, 25, 46, 46, 3, 3, 3, 46, 
	3, 3, 3, 11, 11, 11, 11, 11, 
	31, 11, 0, 0, 15, 15, 15, 40, 
	15, 15, 40, 0, 9, 0, 5, 17, 
	17, 17
};

static const char _gparcer_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 28, 1, 1, 1, 37, 
	37, 37, 1, 1, 1, 1, 1, 1, 
	43, 0, 0, 0
};

static const int gparcer_start = 27;
static const int gparcer_first_final = 27;
static const int gparcer_error = 0;

static const int gparcer_en_date = 9;
static const int gparcer_en_gname = 14;
static const int gparcer_en_main = 27;


#line 430 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"


struct format fsm;




int format_finish( struct format *fsmp )
{
	if ( fsmp->cs == format_error )
		return -1;
	if ( fsmp->cs >= format_first_final )
		return 1;
	return 0;
}

void format_init( struct format *fsm )
{
	buffer_index = 0;
	fsm->buflen = 0;
	fsm->done = 0;
	//int cs, act, have = 0, curline = 1;
	fsm->have = 0;
	fsm->curline = 1;
	fsm->state = 0;
	
#line 377 "/home/walery/workspace_cdt/Strlen/src/gParcer.c"
	{
	( fsm->cs) = gparcer_start;
	( fsm->top) = 0;
	}

#line 456 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
}
static int strnum = 0;
void format_execute( struct format *fsm, char *data, int len, int isEof )
{
//	const char *p = data;
//	const char *pe = data + len;
//	const char *eof = isEof ? pe : 0;
	fsm->curline = ++strnum;
	fsm->buf = data;
	fsm->p = data;
	fsm->pe = data+len;
	fsm->eof = isEof ? fsm->pe : 0;
	printf("format_execute[892]: len:%d  done:%d line:%d \n",len,fsm->done,fsm->curline);
	if(len == 0)
		return;
	
#line 400 "/home/walery/workspace_cdt/Strlen/src/gParcer.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( ( fsm->p) == ( fsm->pe) )
		goto _test_eof;
	if ( ( fsm->cs) == 0 )
		goto _out;
_resume:
	_keys = _gparcer_trans_keys + _gparcer_key_offsets[( fsm->cs)];
	_trans = _gparcer_index_offsets[( fsm->cs)];

	_klen = _gparcer_single_lengths[( fsm->cs)];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*( fsm->p)) < *_mid )
				_upper = _mid - 1;
			else if ( (*( fsm->p)) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _gparcer_range_lengths[( fsm->cs)];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*( fsm->p)) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*( fsm->p)) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _gparcer_indicies[_trans];
	( fsm->cs) = _gparcer_trans_targs[_trans];

	if ( _gparcer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _gparcer_actions + _gparcer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 1:
#line 339 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		append((*( fsm->p)));
//		printf("DGT: %c\n", fc); 
	}
	break;
	case 2:
#line 344 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		append((*( fsm->p)));
//		printf("DEC: .\n"); 
	}
	break;
	case 3:
#line 350 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{ printf("RETURN\n"); {( fsm->cs) = ( fsm->stack)[--( fsm->top)]; goto _again;} }
	break;
	case 4:
#line 352 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
//		append(fc);
//		printf("NAME: %c\n",fc);
		{( fsm->stack)[( fsm->top)++] = ( fsm->cs); ( fsm->cs) = 14; goto _again;} 
	}
	break;
	case 5:
#line 358 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		gts = buffer_index;
		printf("start param: %c\n",(*( fsm->p))); 
	}
	break;
	case 6:
#line 363 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		(*prs[eXparam])(fsm->curline ,&gBuffer[gts],buffer_index - gts);
		fwrite( &gBuffer[gts], 1, buffer_index - gts, stdout );
		printf("\n\tend_param: %c\n",(*( fsm->p))); 
	}
	break;
	case 7:
#line 369 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		resetBuffer();
		append((*( fsm->p)));
		printf("start_tag: %c\n",(*( fsm->p))); 
	}
	break;
	case 8:
#line 375 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		(*prs[eGcommand])(fsm->curline ,gBuffer,buffer_index-gts);
		fwrite( gBuffer, 1, buffer_index, stdout );
		printf("\ncommand_index: %c\n",(*( fsm->p)));
	}
	break;
	case 9:
#line 381 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		(*prs[eComment])(fsm->curline ,fsm->buf,fsm->p - fsm->buf);
		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
		printf("\nend_comment: %c\n",(*( fsm->p)));
	}
	break;
	case 10:
#line 387 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		(*prs[eOcommand])(fsm->curline ,fsm->buf,fsm->p - fsm->buf);
		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
		printf("\nend_otag: %c\n",(*( fsm->p)));
	}
	break;
#line 547 "/home/walery/workspace_cdt/Strlen/src/gParcer.c"
		}
	}

_again:
	if ( ( fsm->cs) == 0 )
		goto _out;
	if ( ++( fsm->p) != ( fsm->pe) )
		goto _resume;
	_test_eof: {}
	if ( ( fsm->p) == ( fsm->eof) )
	{
	const char *__acts = _gparcer_actions + _gparcer_eof_actions[( fsm->cs)];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 0:
#line 332 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
//		if ( fsm->buflen > 0 )
//			fsm->write( fsm->buf, fsm->buflen );
//		fwrite("End\n",1,4,stdout);
		printf("\n action finish_ok.\n");
	}
	break;
	case 7:
#line 369 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		resetBuffer();
		append((*( fsm->p)));
		printf("start_tag: %c\n",(*( fsm->p))); 
	}
	break;
	case 9:
#line 381 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		(*prs[eComment])(fsm->curline ,fsm->buf,fsm->p - fsm->buf);
		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
		printf("\nend_comment: %c\n",(*( fsm->p)));
	}
	break;
	case 10:
#line 387 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	{
		(*prs[eOcommand])(fsm->curline ,fsm->buf,fsm->p - fsm->buf);
		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
		printf("\nend_otag: %c\n",(*( fsm->p)));
	}
	break;
#line 596 "/home/walery/workspace_cdt/Strlen/src/gParcer.c"
		}
	}
	}

	_out: {}
	}

#line 472 "/home/walery/workspace_cdt/Strlen/src/gParcer.rl"
	
		if ( format_finish( fsm ) <= 0 ){
//			int as = 1;
			printf("[898] FAIL :finish code:%d  %-10s \n", format_finish( fsm ) ,data);
			assert(format_finish( fsm ) >= 1) ;
		}

	
}

void init(){
	format_init(&fsm);
}

void execute(char *data, int len){
	fsm.done = 0;
	format_execute(&fsm, data, len, true);
}

int finish(){
	return (format_finish(&fsm));
}

void scanner(){
scannerstart:
	switch (fsm.state)
	{
	case 0:
		fsm.space = INPUT_BUFSIZE - fsm.have;
		fsm.p = fsm.buf + fsm.have;
		
		if ( fsm.space == 0 ) {
			/* We've used up the entire buffer storing an already-parsed token
			 * prefix that must be preserved. */
			fprintf(stderr, "OUT OF BUFFER SPACE\n" );
			exit(1);
		}
	
		fsm.lenfile = fread( fsm.buf+fsm.have, 1, fsm.space, fp );
		
		fsm.eofile = fsm.lenfile != fsm.space;
		
		format_execute( &fsm, fsm.p, fsm.lenfile, fsm.eofile );
		fsm.state = 1;
		 return;
	
	case 1:
		if(fsm.done)
		{
			fsm.done = 0;
			fsm.lenfile = INPUT_BUFSIZE - (fsm.pe - fsm.buf);
			format_execute( &fsm, fsm.pe, fsm.lenfile, fsm.eofile );
			return;
		}
	case 3:
//		printf("[646] done:  %i \n", fsm.done);
		if ( fsm.eofile ){
//			fprintf(stderr, " [650] EOF lenfile:%i  space:%i \n", fsm.lenfile , fsm.space);
			return;
		//	break;
		}	
		
		if ( fsm.ts == 0 ){
			fsm.have = 0;
		}
		else {
			/* There is a prefix to preserve, shift it over. */
			fsm.have = fsm.pe - fsm.ts;
			memmove( fsm.buf, fsm.ts, fsm.have );
			fsm.te = fsm.buf + (fsm.te-fsm.ts);
			fsm.ts = fsm.buf;
		}
	
	}
	
	fsm.state = 0;
	goto scannerstart;

}

#ifndef SCANNER
int _main(int argc, char* argv[])
{

//	int eofile;
//	int len;

	fsm.buf = buf;
	format_init( &fsm );

	char* gfile = "exmple.gcode";
	char* logFile = "gParcer.log";
	
	if(argc == 2){
		gfile = argv[1];
		printf("main[832] param0:%s\n",argv[1]);
	}
	
	if(argc == 3){
		gfile = argv[1];
		logFile = argv[2];
		printf("main[841] gfile:%s\n",gfile);
		printf("main[842] logFile:%s\n",logFile);
	}
	
	
	fp = fopen(gfile,"r");
	   if (fp==NULL) 
	   {
//	   fputs ("File error:"+gfile,stderr); exit (1);
		   fprintf(stderr,"File error: %s",gfile);
	   }else{
		   printf("Open G-file:%s\n",gfile);
	   
	   }
	   
	   
	flog = fopen(logFile,"w");
	   if (flog==NULL) {
//		   fputs ("File error",stderr); exit (1);
		   fprintf(stderr,"Log file error:%s",logFile);
	   }else{
		   printf("Open log file:%s\n",logFile);
	   }


	while(!fsm.eof)
	{	
		scanner();
	}
	
	if ( format_finish( &fsm ) <= 0 )
		printf("[679] FAIL  %li \n", (unsigned long)&fsm);

	printf("main[871]:  %i \n", format_finish( &fsm ));
	
	fclose(fp);
	fclose(flog);
	return 0;
}
#endif
