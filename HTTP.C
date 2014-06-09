#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	FILE *fp,*fp1,*output;
	int flag=0,cnt,i;
	char proxy[30]={0},command[80]={0},temp[100]={0},temp_char;
	output=fopen("d:\\output.txt","w");
	while(1)
	{
		fp=fopen("d:\\weblog.txt","r");
		if(fscanf(fp,"%s",proxy)==EOF)
		break;
		for(i=0;command[i]!='\0';i++)
		command[i]='\0';
		strcpy(command,"grep ");
		strcat(command,proxy);
		strcat(command,"weblog.txt>d:\\temp.txt");
		system(command);
		for(i=0;command[i]!='\0';i++)
		command[i]='\0';
		fp1=fopen("d:\\temp.txt","r");
		strcpy(command,"findstr /V ");
		strcat(command,proxy);
		strcat(command," d:\\weblog.txt>d:\\temp2.txt");
		system(command);
		system("copy /Y d:\\temp2.txt d:\\weblog.txt");
		flag=0;
		cnt=1;
		while(fscanf(fp1,"%s",temp)!=EOF)
		{
			if(flag==0)
			{
				fprintf(output,"\nUser_proxy= %s ",proxy);
				fprintf(output,"\n\nLog No.  Date_time\t\t   Zone  Method  Resource\t\t\t\t    Protocol  Code  Size\n");
			}
			while(fscanf(fp1,"%c",temp_char))
			if(temp_char=='[')
			break;
			fscanf(fp1,"%c",temp_char);
			fscanf(fp1,"%s",temp);
			fprintf(output,"\n%-7d  %-20s",cnt++,temp);
			fscanf(fp1,"  %s",temp);
			fprintf(output," %-4s",temp);
			while(fscanf(fp1,"%c",temp_char))
			if(temp_char=='"')
			break;
			fscanf(fp1,"%c",temp_char);
			fscanf(fp1,"%s",temp);
			fprintf(output,"  %-6s",temp);
			fscanf(fp1,"%s",temp);
			fprintf(output,"  %-30s",temp);
			fscanf(fp1,"%s",temp);
			fprintf(output,"  %-8s\b ",temp);
			fscanf(fp1,"%s",temp);
			fprintf(output,"  %-4s",temp);
			fscanf(fp1,"%s",temp);
			fprintf(output,"  %s",temp);
			flag=1;
		}
		fclose(fp);
		fclose(fp1);
	}
	fclose(output);
	fclose(fp);
	return 0;
}
