//
// Created by douglas on 6/7/17.
//

#include "IOObjects.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>
#include <ctime>


using namespace std;

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

void IOObjects::store(list <Object3D>& objectsSelected) {
    ofstream myfile ("../figure_save.dat");
    if (myfile.is_open()){
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        myfile << "#Imagem com objetos selecionados em " << (now->tm_year + 1900) << '-'
               << (now->tm_mon + 1) << '-'
               <<  now->tm_mday
               << endl;
        myfile << "100 -100 100 -100" << endl;
        myfile << objectsSelected.size() << endl;
        for (list<Object3D>::iterator it = objectsSelected.begin(); it!= objectsSelected.end(); it++){
            myfile << "#" << it->name << endl;
            myfile << it->p << " " << it->l << endl;
            for (int i = 0; i < it->p; i++){
                myfile << it->points[i][0] << " " << it->points[i][1] << " " << it->points[i][2] << endl;
            }
            for (int i = 0; i < it->l; i++){
                myfile << it->lines[i][0] << " " << it->lines[i][1] << endl;
            }
            myfile << it->ang[0] << " " << it->ang[1] << " " << it->ang[2] << endl;
            myfile << it->scale[0] << " " << it->scale[1] << " " << it->scale[2] << endl;
            myfile << it->trans[0] << " " << it->trans[1] << " " << it->trans[2] << endl;
        }

        myfile.close();
    }
    else cout << "Unable to open file";
}

void IOObjects::read(list<Object3D>&objects) {
    string line;
    ifstream myfile ("../figure.dat");
    int n;
    if (myfile.is_open()){
        // Imagem
        getline(myfile,line);
        cout << "Imagem a ser carregada >> " + line.substr(1,string::npos) << endl;
        // Dimensao
        getline(myfile,line);
        vector<string> vec = split(line, ' ');
        // Numero de objetos
        getline(myfile,line);
        n = stoi(line);
        string name;
        //Pegar os n objetos
        for(int i=0; i<n; i++){
            getline(myfile,line);
            name = line.substr(1,string::npos);
            cout << "Objeto " << i  << " >> " << name << endl;
            getline(myfile,line);
            vec = split(line, ' ');
            int pontos = stoi(vec[0]);
            int linhas = stoi(vec[1]);
            Object3D obj(pontos,linhas);
            obj.isSelected = false;
            obj.color = 0;
            obj.name = name;
            for (int j = 0; j < pontos; ++j) {
                getline(myfile,line);
                vec = split(line, ' ');
                obj.points[j][0] = stod(vec[0]);
                obj.points[j][1] = stod(vec[1]);
                obj.points[j][2] = stod(vec[2]);
                obj.points[j][3] = 1;
            }
            for (int j = 0; j < linhas; ++j) {
                getline(myfile,line);
                vec = split(line, ' ');
                obj.lines[j][0] = stoi(vec[0]);
                obj.lines[j][1] = stoi(vec[1]);
            }
            //Valores de rotacao
            getline(myfile,line);
            vec = split(line, ' ');
            obj.rotateX(stoi(vec[0]));
            obj.rotateY(stoi(vec[1]));
            obj.rotateZ(stoi(vec[2]));
            //Valores de escala
            getline(myfile,line);
            vec = split(line, ' ');
            obj.scaleX(stoi(vec[0]));
            obj.scaleY(stoi(vec[1]));
            obj.scaleZ(stoi(vec[2]));
            //Valores de translacao
            getline(myfile,line);
            vec = split(line, ' ');
            obj.addTransX(stoi(vec[0]));
            obj.addTransY(stoi(vec[1]));
            obj.addTransZ(stoi(vec[2]));
            //adiciona na list
            objects.push_back(obj);
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
}

