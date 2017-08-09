// cc -o r-daemon r-daemon.c -lwiringPi -lm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>

#include <wiringPi.h>

unsigned int timWheel;
long int cntWheel = 0;
unsigned int timBar;
long int Bar = 0;

int write_file(char fnp[256],long int d) {
	
	FILE *fp;
	char fn[256]="/tmp/";

	strcat(fn,fnp);
	strcat(fn,".txt");
	
	if((fp=fopen(fn,"r+"))==NULL) {
		fp=fopen(fn,"w+");
	};
	
	fprintf(fp,"%8d",d);
	fclose(fp);
}

int read_file(char fnp[256]) {
	
	FILE *fp;
	char fn[256]="/tmp/";
	long int d;

	strcat(fn,fnp);
	strcat(fn,".txt");
	
	if((fp=fopen(fn,"r"))!=NULL) {
		fscanf(fp,"%8d",&d);
		fclose(fp);
	} else d=0;
	return d;
}

void main() {
	
	char t[256];
	char s[256];
	int tmp;
	
	wiringPiSetup();
	pinMode(16,INPUT);pullUpDnControl(16,PUD_UP); // cntWheel
//	system("sudo /home/pi/robot/self &");
	
	write_file("cntWheel"		,0 );
	
	while(1) {
		
		if (timWheel != digitalRead(16)) {
			timWheel = digitalRead(16);
			cntWheel = read_file("cntWheel");
			cntWheel++;
			write_file("cntWheel"		,cntWheel );
		};


	};
}

