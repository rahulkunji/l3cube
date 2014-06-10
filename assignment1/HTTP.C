#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	FILE *fp,*fp1,*output;
	int flag=0,cnt,i;
	system("copy /Y d:\\weblog.txt d:\\real.txt>temp3.txt");
	char proxy[30]={0},command[80]={0},temp[1000]={0},temp_char[2]={0};
	output=fopen("d:\\output.txt","w");
	while(1)
	{
		fp=fopen("d:\\weblog.txt","r");
		if(fscanf(fp,"%s",proxy)==EOF)
		break;
		fclose(fp);
		for(i=0;command[i]!='\0';i++)
		command[i]='\0';
        strcpy(command,"findstr ");
		strcat(command,proxy);
		strcat(command," d:\\weblog.txt>d:\\temp.txt");
		system(command);
		for(i=0;command[i]!='\0';i++)
		command[i]='\0';
		strcpy(command,"findstr /V ");
		strcat(command,proxy);
		strcat(command," d:\\weblog.txt>d:\\temp2.txt");
		system(command);
		system("copy /Y d:\\temp2.txt d:\\weblog.txt>temp3.txt");
		flag=0;
		cnt=1;
		fp1=fopen("d:\\temp.txt","r");
		while(fscanf(fp1,"%s",temp)!=EOF)
		{
			if(flag==0)
			{
				fprintf(output,"\n\nUser_proxy= %s ",proxy);
				fprintf(output,"\n\nLog No.  Date_time\t\t        Zone   Method  Resource\t\t\t\t\t\t\t\t\t\t\t\t\t\t Protocol   Code   Size\n");
			}
			fscanf(fp1,"%s",temp);
			fscanf(fp1,"%s",temp);
            fscanf(fp1,"%s",temp);
			fprintf(output,"\n%-7d  %-20s",cnt++,temp);
			fscanf(fp1,"  %s",temp);
			fprintf(output," %-4s",temp);
			fscanf(fp1,"%s",temp);
			fprintf(output,"  %-6s",temp);
			fscanf(fp1,"%s",temp);
			fprintf(output,"  %-60s",temp);
			fscanf(fp1,"%s",temp);
			fprintf(output,"  %-8s  ",temp);
			fscanf(fp1,"%s",temp);
			fprintf(output,"  %-4s",temp);
			fscanf(fp1,"%s",temp);
			fprintf(output,"  %s",temp);
			fgets(temp,1000,fp1);
			flag=1;
		}
		fclose(fp1);
	}
	fclose(output);
    system("copy /Y d:\\real.txt d:\\weblog.txt>temp3.txt");
    system("del /Q d:\\real.txt");
    system("del /Q d:\\temp.txt");
    system("del /Q d:\\temp2.txt");
    system("del /Q d:\\temp3.txt");
    return 0;
}
