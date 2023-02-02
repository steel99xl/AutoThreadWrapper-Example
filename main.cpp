#include "autothread.hpp"
#include "sillycurl.hpp"
#include "sillyinput.hpp"
#include <fstream>
#define threadlimit 4

struct DlFile{
	std::string Buffer = "";
	std::string Url = "";
	std::string FileName = "";
};



//Our threadable web handeler... the hole point of this
struct Downloader : autothread::Thread{

    DlFile m_File;

    void SaveFile(DlFile *File){
        std::ofstream Contraband;

        if(strcmp(File->FileName.c_str() , "") == 0){
            Contraband.open(File->Url.c_str(), std::ios::out);
        } else {
            Contraband.open(File->FileName.c_str(), std::ios::out);
            }

        if(Contraband.is_open()){
            Contraband << File->Buffer + "\n";
            Contraband.close();
        } else { 
            std::cout << "ERROR could not open FILE for writeing" << std::endl;
        }

    }    

    void SetURL(const char *URL){this->m_File.Url = URL;}

    void SetName(const char *FILENAME){this->m_File.FileName = FILENAME;}


    void FunctionCallBack() override{
        
        this->m_File.Buffer = sillycurl::WebHandler(this->m_File.Url.c_str());

        SaveFile(&this->m_File);

        //to more easily show a thread is done
        this->m_File.FileName = "";

    }

};



int main(){
    Downloader DLRS[threadlimit];
    bool isRunning = true;
    int AvalibleWorkers = 0;

    std::string Input;

    while(isRunning){
        AvalibleWorkers = 0;
        for(int i = 0; i < threadlimit; i++){
            if(DLRS[i].IsWorking){
            } else {
                AvalibleWorkers++;
            }

        }

        std::cout << "[";
        std::cout << AvalibleWorkers;
        std:: cout << "/";
        std::cout << threadlimit;
        std::cout << "]";
        std::cout << " - Avalible Threads";
        
        Input = sillyinput::UserAutoCap();

        if((std::strcmp(Input.c_str(),"EXIT") == 0 || std::strcmp(Input.c_str(),"QUIT") == 0) && AvalibleWorkers == threadlimit){
            isRunning = false;
        }

        if(std::strcmp(Input.c_str(),"DOWNLOAD") == 0 || std::strcmp(Input.c_str(),"DL") == 0){
            std::cout << "Enter URL for file" << std::endl;
             for(int i = 0; i < threadlimit; i++){
                if(!DLRS[i].IsWorking){
                    DLRS[i].SetURL(sillyinput::UserInput().c_str());
                    std::cout << "Enter a name for the file" << std::endl;
                    DLRS[i].SetName(sillyinput::UserInput().c_str());
                    autothread::StartWork(&DLRS[i]);
                    AvalibleWorkers--;
                    break;
                }

            }
        }

        if((std::strcmp(Input.c_str(),"LIST") == 0 || std::strcmp(Input.c_str(),"LS") == 0)){
            for(int i = 0; i < threadlimit; i++){
                std::cout << "Thread : " << i << std::endl;
                std::cout << "isWorking : " << DLRS[i].IsWorking << std::endl;
                std::cout << "File Name : " << DLRS[i].m_File.FileName << std::endl;
                std::cout << "#########################################" << std::endl;
            }
        };

    };

    std::cout << "uwu" << std::endl;
    return 0;
}