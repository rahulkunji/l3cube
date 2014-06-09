#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
/*libpcap file format 
 *<Global-header><packet header><packet data> <packet header><packet data>..
 * This assumes a fixed byte ordering.. for a variable byte ordering,
 *byte order can be flipped
 * */
FILE *fp;
int read_32bit(void)
{
	int b1=getc(fp);
	int b2=getc(fp);
	int b3=getc(fp);
	int b4=getc(fp);
	int complete_32bit=(b4 << 24 ) | (b3 <<16) | (b2<<8) | b1;
	return complete_32bit;
}
int read_16bit(void)
{
	int b1=getc(fp);
	int b2=getc(fp);
	int complete_16bit=(b2<<8 )| b1;
	return complete_16bit;
}
int flipped_16bit_read()
{
	int b1=getc(fp);
	int b2=getc(fp);
	int complete_16bit=(b1<<8|b2);
	return complete_16bit;
}
int flipped_32bit_read()
{
	int b1=getc(fp);
	int b2=getc(fp);
	int b3=getc(fp);
	int b4=getc(fp);
	int complete_32bit=(b1 << 24 ) | (b2 <<16) | (b3<<8) | b4;
	return complete_32bit;
}
int read_global_header()
{
    int magic_number = read_32bit();
    int major_version = read_16bit();
    int minor_version = read_16bit();
    int thiszone = read_32bit();
    int sigfigs = read_32bit();
    int snaplength = read_32bit();
    int network = read_32bit();
	if(magic_number==0xa1b2c3d4)
	{
		printf("\nMagic number is valid\n");
	}
	else
	{
		printf("\ninvalid magic number %x",magic_number);
		return 1;
	}
	printf("\nHeader details::\n");
	printf("\nMagic number:%x\n",magic_number);
	printf("\nversion major:%d.%d\n",major_version,minor_version);
	printf("\nsnaplength:%d\n",snaplength);
	printf("\nnetwork type:%d\n",network);
}
int packet_info()
{
    struct tm * timestamp;
    char buffer[80];
    time_t ts_sec = read_32bit();
    unsigned int ts_usec = read_32bit();
    int incl_len = read_32bit();
    int orig_len = read_32bit();
    timestamp = localtime( &ts_sec );
    strftime( buffer, 80, "%B %d, %Y %H:%M:%S", timestamp );
    printf( "Timestamp: %s.%06d\n", buffer, ts_usec );
    printf( "Length of packet on network: %d bytes\n", orig_len );
    printf( "Length of packet actually captured: %d bytes\n", incl_len );
    return incl_len;
}
void getmac()
{
	printf("\n");
	printf("%04X",getc(fp));	
	printf(":%04X",getc(fp));
	printf(":%04X",getc(fp));
	printf(":%04X",getc(fp));	
	printf(":%04X",getc(fp));
	printf(":%04X",getc(fp));
	printf("\n");
}
void skip_bytes(int len)
{
    int i;
    for ( i = 0; i < len; i++ )
        getc(fp);
}


void get_ipv6_addr( void )
{
    int i;
    printf( "%x", flipped_16bit_read() );
    for ( i = 0; i < 7; i++ )
        printf( ":%x", flipped_16bit_read());
}

void get_ipv4_addr( void )
{
    int i;
    printf( "%d", getc(fp) );
    for ( i = 0; i < 3; i++ )
        printf( ".%d", getc(fp) );
}


void process_arp()
{
	//obtain ether type
	int ether_type=flipped_16bit_read();
	int hlen,plen,oper,htype,ptype;
	if(ether_type==0x0806)//arp packet
	{
		htype=flipped_16bit_read();
		ptype=flipped_16bit_read();
		hlen=getc(fp);
		plen=getc(fp);
		oper=flipped_16bit_read();
		printf("ARP frame:\n");
		if(oper==1)
		printf("\nREQUEST\n");
		else
		printf("\nRESPONSE\n");
		printf("\nSender MAC:\n");
		getmac();
		printf("\nSender IP:\n");
    		if ( ptype == 0x0800 )
        		get_ipv4_addr();
    		else if ( ptype == 0x86dd )
        		get_ipv6_addr();
		printf("\nTarget MAC\n");
		getmac();
		printf( "Target IP:\n" );
    		if ( ptype == 0x0800 )
        		get_ipv4_addr();
    		else if ( ptype == 0x86dd )
        		get_ipv6_addr();
		skip_bytes(18);//18 bytes left ignored
	}
}
int main()
{	
	int length=0,ch=0,counter=0;
	fp=fopen("arp-storm.pcap","r");
	if(!fp)
	{
		fprintf(stderr,"error in opening file");
		exit(-1);
	}
	else
	{
		read_global_header();
		while(1)//decoding starts here
		{
			length=packet_info();
			counter++;
			printf("\nPACKET %d\n",counter);
			printf("\ndestination:\n");
			getmac();
			printf("\nsource\n");
			getmac();
			process_arp();
			ch=getc(fp);
			if(ch==EOF)
			break;
			else
			ungetc(ch,fp);//not EOF-push back to stream
		}
	}
	return 0;
}
