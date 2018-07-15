//============================================================================
// Name        : Strlen.cpp
// Author      : CUBY,Ltd
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

//#include <string.h>
#include "gParcer.h"
#include <assert.h>

FILE *fp;
//FILE *flog;

using namespace std;


int main(int argc, char* argv[]) {


	char const * gfile = "testg1.ngx";
	char const * logFile = "gParcer.log";

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
	assert(fp!=NULL);
/*	   if (fp==NULL)
	   {
//	   fputs ("File error:"+gfile,stderr); exit (1);
		   fprintf(stderr,"File error: %s",gfile);
	   }else{
		   printf("Open G-file:%s\n",gfile);

	   }
*/

	flog = fopen(logFile,"w");
	assert(flog!=NULL);
/*	   if (flog==NULL) {
//		   fputs ("File error",stderr); exit (1);
		   fprintf(stderr,"Log file error:%s",logFile);
		   EXIT_FAILURE;
	   }else{
		   printf("Open log file:%s\n",logFile);
	   }
*/

#define BUF_SIZE	100


	init();

	char buffer[BUF_SIZE];

	while(fgets(buffer,100,fp) != NULL)
	{

		init();
		size_t len = strlen(buffer);

		execute(buffer,len);

		//			   buffer[len-2] = 0;

//		printf("buffer:%s : %li \n",buffer, strlen(buffer));
	}


	fclose(fp);
	fclose(flog);



	size_t len = strlen("hello");

	cout << "!!!Hello World!!!"<< len << endl; // prints !!!Hello World!!!
	return 0;
}
