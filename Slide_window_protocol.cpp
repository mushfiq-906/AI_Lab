#include <bits/stdc++.h>
#include<unistd.h>

using namespace std;

int nf,r,f_size,cnt=0;
string s="";
void sender();
void receive_ack(int,int);
void send_window(int,int);
void resend_window();

struct frame{
    int ack;
    char data;
}f[15];

bool allReceived(){
    cnt = 0;
    for(int i=0;i<nf;i++){
        if(f[i].ack == 1){
            cnt++;
        }
    }
    if(cnt == nf)
        return true;
    else
        return false;
}

void sender(){

    string input;
    cout<<"Enter a String: ";
    getline(cin,input);
    nf = input.size();
    for(int i=0;i<nf;i++){
//        printf("\nData for frame %d  :",i);
        f[i].data = input[i];
        f[i].ack = 1;
    }
}
void send_window(int st,int stp){
    if(stp>nf)
        stp= nf;
    if(st == stp )
        return;
    for(int i=st ; i<stp ;i++){
        printf("Sending data : frame %d(%c)\n",i,f[i].data);
        f[i].ack = 1;
    }
    receive_ack(st,stp);
}

void resend_window(){
    if(allReceived())
    {
        return;
    }
    printf("\nResending Window\n");
    sleep(1);
    send_window(r,r+f_size);
}

void receive_ack(int st,int stp){
    int x= 0;
    r = rand() % stp;
    r += st;
    f[r].ack = 0;
    for (int i = st; i < stp; i++) {
        if(f[i].ack == 0){
            printf("\nFrame no. %d is not received\n",r);
            break;
        }
        printf("\nFrame no. %d is received\n",i);
        printf("\nData received: %c\n",f[i].data);
        s+=f[i].data;
        x++;
    }
    if(x==f_size){
        send_window(stp,stp+f_size);
    }
    for(int i=r+1;i<stp;i++){
        printf("Frame no %d is discarded\n",i);
    }
    resend_window();
}

int main(){
    srand(time(NULL));
    sender();
    cout<<"\nEnter frame size: ";
    cin>>f_size;
    send_window(0,f_size);
    cout<<"Received Data: "<<s<<endl;
}
