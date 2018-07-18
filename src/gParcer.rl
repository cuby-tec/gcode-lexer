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

%%{
	machine gparcer;
	
	
	access fsm->;
	variable p fsm->p;
	variable pe fsm->pe;
	variable eof fsm->eof;
	variable cs fsm->cs;
	variable stack fsm->stack;
	variable top fsm->top;
	
	newline = '\n' @{
		//parser_out = command;
		(*prs[eCommand])(fsm->curline ,fsm->ts,fsm->te-fsm->ts);
		fsm->curline += 1;
		fsm->pe = fsm->te;
		fsm->done = 1;
//		fsm->eof = fsm->te;
		};
		
	any_count_line = any | newline;


	# Alpha numberic characters or underscore.
	alnum_u = alnum | '_';

	# Alpha charactres or underscore.
	alpha_u = alpha | '_';

	optional = (('+'|'-')? digit+ ('.' digit+)?){,1};
	
	decimal = ('+'|'-')? digit+ ('.' digit+)?;
		
	word = alnum*;

	a1 = ';' (any-'\n')* ;

	# g command GXX.X
	a3 = 'G' digit{1,2} ('.' digit+)? ;

	# g X coordinate
	a4 = 'X' optional ;

	# g Y coordinate
	a5 = 'Y' optional ;

	# g Z coordiane
	a6 = 'Z' optional ;

	# g A    Stepper A position or angle {Annn]
	a7 = 'A' decimal ;
	
	# g B  Stepper B position or angle {Bnnn}
	a8 = 'B' decimal ;

	# g C  Stepper C position or angle {Cnnn}
	a9 = 'C' decimal ;

	# g D  Adjust Diagonal Rod {D}
	a10 = 'D' ;

	# g E coordinate
	a11 = 'E' optional ;


	# g F Feed rate parameter in G-command
	a12 = 'F' decimal ;
	# g I X offset for arcs and G87 canned cycles
	a13 = 'I' optional ;

	# g J Y offset for arcs and G87 canned cycles
	a14 = 'J' decimal ;

	# g K Z offset for arcs and G87 canned cycles.
	a15 = 'K' decimal ;
	
	
	# g L generic parameter word for G10, M66 and others
	a16 = 'L' decimal ;
	
	# g M Code Modal Groups
	a17 = 'M'  digit+ ;

	# g N Line number 
	a18 = 'N'  digit+ ;

	# g P  	Command parameter, such as time in milliseconds; proportional (Kp) in PID Tuning 
	#		Dwell time in canned cycles and with G4. Key used with G10.
	a19 = 'P' alnum_u*  ;

	# g R Arc radius or canned cycle plane
	#	R Relative move flag 
	a20 = 'R' optional ;

	# g S Spindle speed; Command parameter, such as time in seconds; temperatures; voltage to send to a motor 
	a21 = 'S'  optional   ;
		
	# g T Tool selection
	a22 = 'T'  digit? ;

	# g U  	U axis of machine;
	#		Un <bool> with a non-zero value will apply the result to current zprobe_zoffset 
	a23 = 'U' optional ;
		
	# g V  	V axis of machine;
	a24 = 'V' optional ;

	# g W  	W axis of machine;
	a25 = 'W' optional ;

	# g * Checksum 
	a26 = '*' digit{2} ;

	# Whitespace is standard ws, newlines and control codes.
	a29 = any_count_line - 0x21..0x7e;

	# Symbols. Upon entering clear the buffer. On all transitions
	# buffer a character. Upon leaving dump the symbol.
	a27 = ( punct - [_'"()] ) ;


	# Describe both c style comments and c++ style comments. The
	# priority bump on tne terminator of the comments brings us
	# out of the extend* which matches everything.
	# eof string
	a28 = '\n'* newline;
#	'\n'* newline $!finish_ok;


	
#	main :=  ( )* @/ fcall gparcer ;
	
	
	action finish_ok {
//		if ( fsm->buflen > 0 )
//			fsm->write( fsm->buf, fsm->buflen );
//		fwrite("End\n",1,4,stdout);
		printf("\n action finish_ok.\n");
	}
	
	action dgt      {
		append(fc);
//		printf("DGT: %c\n", fc); 
	}
	
	action dec      {
		append(fc);
//		printf("DEC: .\n"); 
	}


	action return { printf("RETURN\n"); fret; }
	
	action call_gblock {
//		append(fc);
//		printf("NAME: %c\n",fc);
		fcall gname; 
	}
	
	action start_param {
		gts = buffer_index;
		printf("start param: %c\n",fc); 
	}
	
	action end_param {
		(*prs[eXparam])(fsm->curline ,&gBuffer[gts],buffer_index - gts);
		fwrite( &gBuffer[gts], 1, buffer_index - gts, stdout );
		printf("\n\tend_param: %c\n",fc); 
	}
	
	action start_tag {
		resetBuffer();
		append(fc);
		printf("start_tag: %c\n",fc); 
	}
	
	action command_index{
		(*prs[eGcommand])(fsm->curline ,gBuffer,buffer_index-gts);
		fwrite( gBuffer, 1, buffer_index, stdout );
		printf("\ncommand_index: %c\n",fc);
	}
	
	action end_comment{
		(*prs[eComment])(fsm->curline ,fsm->buf,fsm->p - fsm->buf);
		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
		printf("\nend_comment: %c\n",fc);
	}
	
	action end_otag{
		(*prs[eOcommand])(fsm->curline ,fsm->buf,fsm->p - fsm->buf);
		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
		printf("\nend_otag: %c\n",fc);
	}
	
	# A parser for date strings.
	date := decimal  '\n' @return;

	
	gindex = digit+ $dgt ( '.' @dec [0-9]+ $dgt )? ;
	
	#Local commentary
	#l_com = ( (';' (any)* :>> cntrl)) @end_param ;
	l_com = (( '('(any)* :>> ')') | (';' (any)* :>> cntrl)) @end_param ;
	
	malpha = [A-Za-z*];
	
	param_data = ((malpha) ([+\-]? digit+)? ('.' digit+)? )%end_param ; 
	
	param = ((param_data) | ( l_com  ) )>start_param $dgt ;
	
	# A parser for name strings.
	gname := (( gindex)%command_index (' '+ ( (param).(space)* )*)?  '\n') @return;

	#Comment content
	comment = ( (print)+  ) %end_comment ;
	
	o_tag = ( (any)* :> cntrl ) %end_otag ;
	
	# The main parser.
	block =( ( 'G'|'M' )  @call_gblock |  'O' o_tag | (extend-ascii)*
	| ('F' gindex ) | ('T' gindex) | 'S' gindex 
	| ';' comment  | ('(' (any)* :>> ')')%end_comment )>start_tag;
	
	main := (block (l_com)? '\n'? | ('' '\n')? ) %finish_ok;	
	
	
	
	
}%%

%% write data ;


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
	%% write init;
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
	%% write exec;
	
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
