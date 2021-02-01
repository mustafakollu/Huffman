
#include <fstream>
#include "Program.h"


    int main(int argc, char** argv) {
        Program work;
        string arg1=argv[1];

        if(arg1.compare("-i")==0){
            string line;
            string text;
            string arg3= argv[3];
            if(arg3.compare("-encode")==0){
                ofstream fout("temp.txt");
                ifstream readFile(argv[2]);
                if (readFile.is_open()) {
                    while (getline(readFile, line)) {
                        text= line;
                    }
                }
                int indis=0;
                while(text[indis])
                {
                    int deger = text[indis];
                    if(deger>64 && deger<91)
                        text[indis]+=32;
                    indis++;
                }
                work.createHuffmanTree(text,fout);
                fout.close();
            }
            if(arg3.compare("-decode")==0){
                ifstream readFile2("temp.txt");
                if (readFile2.is_open()) {
                    while (getline(readFile2, line)) {
                        text= line;
                        if(text.substr(0,13).compare("DecodedString")==0){
                            for (int i = 14; i <text.length() ; i++) {
                                cout<<text[i];
                            }
                        }
                    }
                }
                cout<<endl;
            }
        }

        if(arg1.compare("-s")==0){
            string line;
            string text;
            string arg2=argv[2];
            ifstream readFile2("temp.txt");
            if (readFile2.is_open()) {
                while (getline(readFile2, line)) {
                    text= line;
                    if(text.substr(0,6).compare("Codes-")==0){
                        if(text.substr(6,1).compare(arg2)==0){
                            for (int j=8;j<text.length();j++){
                                cout<<text[j];
                            }
                            cout<<endl;
                        }
                    }
                }
            }
        }
        if(arg1.compare("-l")==0){
            string line;
            string text;
            ifstream readFile2("temp.txt");
            if (readFile2.is_open()) {
                while (getline(readFile2, line)) {
                    text= line;
                    if(text.substr(0,4).compare("tree")==0){
                        for (int i = 4; i <text.length() ; i++) {
                            cout<<text[i];
                        }
                        cout<<endl;
                    }
                }
            }
        }
        return 0;
    }
