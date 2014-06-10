import dpkt,socket
f=open('tcp-ecn-sample.pcap','rb')
pcap = dpkt.pcap.Reader(f)
count=0
for ts,buf in pcap:
    try:
        eth=dpkt.ethernet.Ethernet(buf)
        print (eth.dst).encode("hex")   #source hex
        print (eth.src).encode("hex")   #destination hex
        ip_temp=eth.data
        if ip_temp.p==dpkt.ip.IP_PROTO_TCP:
            count=count+1
            print "analyzing IP packet %d"%count
            print "tos:%d"%ip_temp.tos
            print "source address:%s"%socket.inet_ntoa(ip_temp.src)
            print "destination address:%s"%socket.inet_ntoa(ip_temp.dst)
            encap_tcp=ip_temp.data
            print "source port:%d"%encap_tcp.sport
            print "destination port:%d"%encap_tcp.dport
            print "urgent pointer:%d"%encap_tcp.urp
            print "seq :%d"%encap_tcp.seq
            print "ack:%d"%encap_tcp.ack
    except dpkt.dpkt.NeedData:
         print "EOF reached"
        
