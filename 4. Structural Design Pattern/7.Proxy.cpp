/*
Client-->  YouTubeDownloadProxy(Youtube instance),(download())
                  ||
           Downloader(download)
                 ||
           YouTubeDownload(download)
*/
#include <iostream>
using namespace std;

//interface
class Downloader{
public:
      virtual void download()=0;
virtual ~Downloader(){};
};

class YouTubeDownload: public Downloader{
    public:
        void download(){
          cout<<"YouTUbe videos Downloaded"<<endl;
        }
};

class YouTubeDownloadProxy: public Downloader{
     public: 
         YouTubeDownload *youTube;
         
         void download(){
             if(!youTube){
               cout<<"Initial call"<<endl;
               youTube=new YouTubeDownload();
             }
             youTube->download();
         }
};
int main() 
{
    Downloader*proxy =new YouTubeDownloadProxy();
    proxy->download();
    cout<<"proxy call"<<endl;
    proxy->download();
  
}