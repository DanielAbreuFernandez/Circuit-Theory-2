// IPCReceiver.cpp - Process 2 (Receiver)

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <mqueue.h>
#include <unistd.h>
 #include <time.h>

int main() {
    const char* queueName = "/my_queue";
    mqd_t mq;
    char buffer[1024];
    unsigned int prio;

    // Open the message queue for reading
    

    mq = mq_open(queueName, O_RDONLY);
    
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }

    /*
    // Receive a message from the queue
    ssize_t bytesReceived = mq_receive(mq, buffer, sizeof(buffer), &prio);

    if (bytesReceived == -1) {
        perror("mq_receive");
        return 1;
    }

    buffer[bytesReceived] = '\0';
    std::cout << "Received: " << buffer << std::endl;
    */
    std::string terminate = "Terminate\0";
    ssize_t bytesReceived = 0;
    while (bytesReceived != -1) {
    
    	bytesReceived = mq_receive(mq, buffer, sizeof(buffer), &prio);
    	
        if (bytesReceived == -1) {
            perror("mq_receive");
            return 1;
         }
	
        buffer[bytesReceived] = '\0';

    	std::cout << "Received: " << buffer << std::endl;
    	
    	if (buffer == terminate) 
    	{
    	    	std::cout << "Leave: " << buffer << std::endl;
    	   break;
    	   
    	   }
 
    }
    
    
    // Close the message queue
    mq_close(mq);

    // Unlink the message queue (remove it)
    mq_unlink(queueName);

    return 0;
}

