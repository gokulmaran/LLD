////////////////////
#include <bits/stdc++.h>
using namespace std;

atomic<int>counter(0);

void increment(){
    for(int i=0;i<1000;i++){
        counter++;
    }
}
int main(){
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();
}

///////////////////
#include <bits/stdc++.h>
using namespace std;

mutex mtx;
condition_variable cv;
queue<int>q;
bool done=false;

void producer(){
    for(int i=0;i<5;i++){
        this_thread::sleep_for(chrono::milliseconds(300));
        {
        lock_guard<mutex>lock(mtx);
        q.push(i);
        cout<<"[Producer] pushed: "<<i<<endl;
       }
       cv.notify_one();
    }
    {
        lock_guard<mutex>lock(mtx);
        done=true;
    }
    cv.notify_all();
}

void consumer(int id){
    while(true){
        unique_lock<mutex> lock(mtx);

        cv.wait(lock,[]{
           return !q.empty() ||done;
        });

        while(!q.empty()){
           int val=q.front();
           q.pop();

           lock.unlock();
           cout<<"Consumer "<<id<< "] Got: "<<val<<endl;
           lock.lock();
        }
        if(done and q.empty()) break;
    }
    cout<<"Consumer"<<id<<"] Exiting.]\n";
}

int main(){
    cout<<"Producer consumer Demo\n";

    thread prod(producer);
    thread cons1(consumer,1);
    thread cons2(consumer,2);

    prod.join();
    cons1.join();
    cons2.join();

    cout<<"All threads done queue size: "<<q.size()<<endl;
}
////////////////////
#include <bits/stdc++.h>
#include <semaphore>
using namespace std;

counting_semaphore<5> emptySlots(5); // max 5 items
counting_semaphore<5> filledSlots(0);

mutex mtx;
queue<int> q;

// Producer
void producer() {
    for (int i = 1; i <= 10; i++) {
        emptySlots.acquire(); // wait if buffer full

        {
            lock_guard<mutex> lock(mtx);
            q.push(i);
            cout << "Produced: " << i << endl;
        }

        filledSlots.release(); // signal item available
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

// Consumer
void consumer() {
    for (int i = 1; i <= 10; i++) {
        filledSlots.acquire(); // wait if buffer empty

        int val;
        {
            lock_guard<mutex> lock(mtx);
            val = q.front();
            q.pop();
            cout << "Consumed: " << val << endl;
        }

        emptySlots.release(); // signal space available
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}

/////////////////////////
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

void server_connection() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);

    cout << "Server waiting...\n";

    int client_socket = accept(server_fd, nullptr, nullptr);

    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);
    cout << "Client: " << buffer << endl;

    const char* msg = "Hello client";
    send(client_socket, msg, strlen(msg), 0);

    close(client_socket);
    close(server_fd);
}

void client_connection() {
    // small delay to ensure server starts first
    this_thread::sleep_for(chrono::seconds(1));

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr));

    const char* msg = "Hello server";
    send(sock, msg, strlen(msg), 0);

    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    cout << "Server: " << buffer << endl;

    close(sock);
}

int main() {
    thread server(server_connection);
    thread client(client_connection);

    server.join();
    client.join();

    return 0;
}
