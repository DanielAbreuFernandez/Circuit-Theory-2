// IPCSender.cpp - Process 1 (Sender)

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <mqueue.h>
#include <unistd.h>

int main() {
    const char* queueName = "/my_queue";
    mqd_t mq;
    struct mq_attr attr;

    // Create and open the message queue
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;
    attr.mq_curmsgs = 0;

    mq = mq_open(queueName, O_CREAT | O_WRONLY, 0666, &attr);

    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }
    
        
    // spawn the reader processor
    int child_process = fork();
    if(child_process){
    	execlp("./IPCReceiver","./IPCReceiver",(char*)NULL);
    }

    /*
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int randomData = std::rand();

    // Send a message to the queue
    std::string message = "Message from Sender: " + std::to_string(randomData);
    mq_send(mq, message.c_str(), message.size(), 0);

    std::cout << "Sent: " << message << std::endl;
    */
    
    for(int i = 0; i < 10; i++) {
        std::string message = "Message from Sender: " + std::to_string(i);
    	mq_send(mq, message.c_str(), message.size(), 0);
    }
    
    std::string message = "Terminate";
    mq_send(mq, message.c_str(), message.size(), 0);


    // Close the message queue
    mq_close(mq);
    
    return 0;
}
