#include <vector>
class Server{
public:
    int max_clients = 30;
    SOCKET master_socket , new_socket , client_socket[30];
    const char *response = "ECHO Daemon v1.0 \r\n";
    int opt = TRUE;

    char buffer[1025];
    int valread;

    struct sockaddr_in address;
    fd_set readfds;

    Server(unsigned short port){
        //initialise all client_socket[] to 0 so not checked
        memset(client_socket, 0, sizeof(SOCKET) * 30);

        if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0){
            perror("socket failed"); return;
        }

        if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 ){
            perror("setsockopt"); return;
        }

        address.sin_family = AF_INET;
        inet_pton(AF_INET, "0.0.0.0", &address.sin_addr);
        address.sin_port = htons( port );

        if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0){
            perror("bind failed"); return;
        }

            //try to specify maximum of 3 pending connections for the master socket

        if (listen(master_socket, SOMAXCONN) < 0){
            perror("listen"); return;
        }

        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);

    }
    ///message : {user - message}

    /// new user : {-(user + 1) - "new"}

    /// deleted user : {-(user + 1) - "delete"}
    std::vector<std::pair<int,std::string> > process_updates(){
        std::vector<std::pair<int,std::string> > ret;
        int max_sd = master_socket;







        //add child sockets to set

        for (int i = 0 ; i < max_clients ; i++){
            int sd = client_socket[i];

            if(sd > 0)
                FD_SET( sd , &readfds);

            if(sd > max_sd)
                max_sd = sd;

        }



        //wait for an activity on one of the sockets , timeout is NULL ,

        //so wait indefinitely

        fd_set copy = readfds;

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 1000 * 10; /// 10 ms


        if ((select( max_sd + 1 , &copy , NULL , NULL , &tv) < 0) && (errno!=EINTR)){
            printf("select error"); return {{-1,""}};
        }

        int addrlen = sizeof(address);

        if (FD_ISSET(master_socket, &copy)){

            if ((new_socket = accept(master_socket,(struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
                perror("accept"); return {{-1,""}};
            }



            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs

                  (address.sin_port));



            //send new connection greeting message

            if( send(new_socket, response, strlen(response), 0) != strlen(response) ){
                perror("send"); return {{-1,""}};
            }



            puts("Welcome message sent successfully");



            //add new socket to array of sockets

            for (int i = 0; i < max_clients; ++i){

                //if position is empty
                if(client_socket[i] ){continue;}
                client_socket[i] = new_socket;
                ret.push_back({-(i+1),"new"});
                printf("Adding to list of sockets as %d\n" , i);
                break;
            }

        }



        for (int i = 0; i < max_clients; ++i){

            int sd = client_socket[i];



            if (FD_ISSET( sd , &copy)){

                //Check if it was for closing , and also read the

                //incoming message

                if ((valread = recv( sd , buffer, 1024, 0)) == 0)

                {

                    //Somebody disconnected , get his details and print

                    getpeername(sd , (struct sockaddr*)&address , \

                        (socklen_t*)&addrlen);

                    printf("Host disconnected , ip %s , port %d \n" ,

                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                    ret.push_back({-(i+1),"delete"});


                    //Close the socket and mark as 0 in list for reuse

                    close( sd );

                    client_socket[i] = 0;

                }else{ //Echo back the message that came in

                    //set the string terminating NULL byte on the end

                    //of the data read
                    ret.push_back({i,buffer});

                    buffer[valread] = '\0';

                    send(sd , buffer , strlen(buffer) , 0 );

                }

            }

        }

        return ret;
    }
};
