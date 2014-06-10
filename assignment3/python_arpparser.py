import dpkt,socket
f=open("arp-storm.pcap","rb")
pcap = dpkt.pcap.Reader(f)
count=0
for ts,buf in pcap:
        count+=1
        print "\n\n\n"
        print "processing packet %d:"%count
        eth=dpkt.ethernet.Ethernet(buf)
        print "source=%s"%(eth.src).encode("hex")
        print "destination=%s"%(eth.dst).encode("hex")
        print "operation:%d"%eth.data.op
        print "source hardware address=%s"%(eth.data.sha).encode("hex")
        print "target hardware address=%s"%(eth.data.tha).encode("hex")
        print "source protocol address=%s"%socket.inet_ntoa(eth.data.spa)
        print "target protocol address=%s"%socket.inet_ntoa(eth.data.tpa)
f.close()

    
    
