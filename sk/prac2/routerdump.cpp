#include "structures.h"
using namespace std;

map< network , route> routing;
vector<network> neighbours;

long long cur_round = 0;
const int round_wait = 3;
const int round_broadcast = 6;
map<network, int> last_round_heard;

void write_buff(char* buf, int s) {
    for(int i = 0; i< s; i++) {
    
        printf("%x\n", buf[i]);
    }
} 

void delete_indirect(network neigh){
    for(pair<network, route>  net : routing){
        network n = net.first;
        int kandydat = inet_addr(net.second.via.c_str());//jezeli pierwszy router na trasie jest w odciętej sieci
        if(neigh.in(kandydat)){
            routing[n] = route(routing[n].via);//ustaw inf
        }
    }
}

int write_network(int sockfd, struct sockaddr_in server_address,in_addr ip, network neigh, network n, int dist){
        route r = routing[n];
        
        if(cur_round - last_round_heard[n]  > round_broadcast){
            if(r.via != "unreachable" && r.via!="direct") {
                routing.erase(n);
            }
            return 1;
        }
        printf("%s\n", inet_ntoa(ip));
        server_address.sin_addr = ip;
        //inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

        char message[9];
        ((int*) message)[0] = htonl(n.ip); 
        message[4] = n.mask; 
        char *temp = message + 5;
        *((int*) temp) = htonl(dist);
        write_buff(message, 9);
	ssize_t message_len = 9;
	if (sendto(sockfd, message, message_len, 0, (struct sockaddr*) &server_address, sizeof(server_address)) != message_len) {
                routing[neigh] = route(routing[neigh].dist, "unreachable");//jezeli nie moge wyslac to zaznacz brak polaczenia
                delete_indirect(neigh);
		//fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
		//return 0;		
	}

	close (sockfd);
	return 1;
}



void remove_bad(){// usuwanie przeterminownych
    
    for(pair<network, route>  net : routing){
        network n = net.first;
        if(cur_round - last_round_heard[n]  > round_wait ){
            if(routing[n].via !="direct")
                routing[n] = route(routing[n].via);
            else
                routing[n] = route(routing[n].dist, "unreachable");
        }
    }
    
    for (network neigh : neighbours){
        if(routing[neigh].via == "unreachable")
            delete_indirect(neigh);
    }
            
    
}

void write_vector(int sockfd, struct sockaddr_in server_address){
    
    for(pair<network, route>  net : routing){
        for (network neigh : neighbours){
                write_network(sockfd, server_address, neigh.broadcast(), neigh, net.first, net.second.dist);        
        }
    }
}

void find_and_update_sender(char * sender){
    int ip = inet_addr(sender);
    for(network neigh : neighbours)
        if(neigh.in(ip)){
            last_round_heard[neigh] = cur_round;
            routing[neigh].via = "direct";
        }
}

void update_vector( u_int8_t *buffer, char* sender){
    write_buff((char*)buffer, 9);
    int addr = *((int*) buffer);
    addr = ntohl(addr);
    u_int8_t mask= *(buffer + 4);
    void* temp = buffer + 5;
    int d = *((int *)temp);
    d = ntohl(d);
    
    printf("to %d mask %d dist %d via%s",addr, mask, d, sender);
    network dest(addr, mask);
    find_and_update_sender(sender);
    if(d != max_dist) 
        last_round_heard[dest] = cur_round;
    route cur= routing[dest];
    if(cur. dist > d){
        if(d +1 > max_dist) d = max_dist-1;
        routing[dest] = route(d+1, sender);
    }
    if(cur.via == sender) {
        routing[dest] = route(d, sender);
    }
    
}

void print_vector(){
    printf("Aktualna tablica routingu :\n");
    for(auto a : routing){
        struct in_addr adres; 
        adres.s_addr = a.first.ip;
        char ipstr[20];
        inet_ntop(AF_INET, &adres, ipstr, sizeof(ipstr));
        printf("%s/%" PRIu8" distance %d %s last heard on round%d\n", ipstr, a.first.mask, a.second.dist, a.second.via.c_str(), last_round_heard[a.first]);
    }
}
int receive_and_parse(struct sockaddr_in server_address, int sockfd) 
{
    struct sockaddr_in  sender;
    socklen_t           sender_len = sizeof(sender);
    u_int8_t            buffer[IP_MAXPACKET+1];
    //select zeby nie czekal dluzej niz ture
    fd_set descriptors;
    FD_ZERO (&descriptors);
    FD_SET (sockfd, &descriptors);
    struct timeval tv; tv.tv_sec = 1; tv.tv_usec = 0;
    int ready = select (sockfd+1, &descriptors, NULL, NULL, &tv);
    if( ready < 0) {
        //fprintf(stderr, "select error: %s\n", strerror(errno));
        return 0;
    }
    if( ready == 0 ) {
        return 1;
    }
    if( ready > 0){
        ssize_t datagram_len = recvfrom (sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
        if (datagram_len < 0) {
            //fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
            return 0;
        }

        char sender_ip_str[20]; 
        inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
        printf ("Received UDP packet from IP address: %s, port: %d\n", sender_ip_str, ntohs(sender.sin_port));

        buffer[datagram_len] = 0;
        //printf ("%ld-byte message: +%s+\n", datagram_len, buffer);
        
        update_vector(buffer, sender_ip_str);
        
        return 1;
    }
    return 1;
}

long long get_time(struct timeval prev_time){
    struct timeval curtime, tval_result; 
    gettimeofday(&curtime, NULL);
    timersub(&curtime, &prev_time, &tval_result);
    return tval_result.tv_sec;
    
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "socket error: %s\n", strerror(errno)); 
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_address;
    bzero (&server_address, sizeof(server_address));
    server_address.sin_family      = AF_INET;
    server_address.sin_port        = htons(54321);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind (sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        fprintf(stderr, "bind error: %s\n", strerror(errno)); 
        return EXIT_FAILURE;
    }
   
    const int NUM_SECONDS = 10;
    struct timeval prev_time;
    gettimeofday(&prev_time, NULL);
    for (;;) {
        
        long long elapsed = get_time(prev_time);

        if(elapsed > NUM_SECONDS)
        {
            gettimeofday(&prev_time, NULL);
            
            //write_vector();
            print_vector();
            remove_bad();
            cur_round++;
        }
        receive_and_parse(server_address, sockfd);
        fflush(stdout);
    }

	close (sockfd);
	return EXIT_SUCCESS;
}

