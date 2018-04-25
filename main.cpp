/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rafael
 *
 * Created on 15 de Outubro de 2017, 13:42
 */

#include <cstdlib>
#include <iostream>
#include <getopt.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <map>
#include <vector>
#include "gurobi_c++.h"

#include <jsoncpp/json/json.h>

#include "Horario.h"
#include "HttpRequests.h"
#include "Disciplina.h"
#include "Sala.h"

using namespace std;

vector<Horario*> getHorarios();
vector<Sala*> getSalas();
void setFuncaoObjetivo(GRBModel* model);
void initVars(GRBModel* model);
void setFuncoesRestricoes(GRBModel* model);
void setArgs(int argc, char** argv);

GRBVar ***r; // número de alunos acima do limite de 60
GRBVar ***s_p; // número de alunos que ultrapassa capacidade da sala
GRBVar ***s_n; // número da capacidade que ultrapassa a demanda
GRBVar ***x; // alocação de turmas (1 ou 0)
GRBVar *t; // número de salas diferentes que uma sala foi alocada
GRBVar **v; // alocação de disciplina em sala

int num_horarios = 14;
int num_turmas;
int num_salas;

int *demanda;
int **horario;

vector<Sala*> salas;
vector<Horario*> horarios;

char param_ensalamentoID[30];
char param_ano[30];
char param_semestre[30];

string baseURL = "http://52.205.160.150/api/v1/";
// string baseURL = "http://localhost:8000/api/v1/";

int main(int argc, char** argv) {
    
    // configura argumentos passado em command line
    ::setArgs(argc, argv);
    
    // recupera informações de api
    horarios = ::getHorarios();
    salas = ::getSalas();
    
    num_salas = salas.size(); 
    num_turmas = horarios.size();
    demanda = new int[num_turmas];
    
    // cria matriz (turmas x horarios) e aloca 0 para cada elemento
    horario = new int*[num_turmas];
    for (int i=0; i<num_turmas; i++) {
        horario[i] = new int[num_horarios];
        for (int j=0; j<num_horarios; j++) {
            horario[i][j] = 0;
        }
    }
    
    // aloca demanda de turma em vetor demanda e
    // aloca turma em mapper que indica posição de turma
    map<int, Horario*> turmas;
    int temp_horario;
    for (int i=0; i<num_turmas; i++) {
        turmas[i] = horarios[i];
        
        demanda[i] = horarios[i]->GetAlunos_qtd();
        
        // Converte horaio e dia em um valor de 0 até 13
        temp_horario = ((horarios[i]->GetDia() - 1) * 2  + horarios[i]->GetHorario()) - 1;
        horario[i][temp_horario] = 1;
    }
    
    // definindo ambiente para o gurobi
    try {
        GRBEnv env = GRBEnv();
        GRBModel model = GRBModel(env);
        
        // inicializa variáveis
        ::initVars(&model);
        
        // configura função objetivo
        ::setFuncaoObjetivo(&model);
        
        // configura funções de restrição
        ::setFuncoesRestricoes(&model);
        
        model.update();
        model.optimize();
        
        // cout << endl << endl << endl;
        
        // for(int i = 0; i < num_turmas; i++){
        //     for(int j = 0; j < num_horarios; j++){
        //         bool print = true;
        //         for(int k = 0; k < num_salas; k++){
        //             if(x[i][j][k].get(GRB_DoubleAttr_X) > 0.5){
        //                 cout << salas.at(k)->GetNome() << "\t";
        //                 print = false;
        //             }                            
        //         }
        //         if (print) cout << "---\t";
        //     }
        //     cout << endl;
        // }         
        
        Json::Value ensalamentosArr(Json::arrayValue);
        
        for (int i=0; i<num_turmas; i++) {
            for (int j=0; j<num_horarios; j++) {
                for (int k=0; k<num_salas; k++) {
                    if(x[i][j][k].get(GRB_DoubleAttr_X) > 0.5) {
                        for(map<int, Horario*>::iterator pos = turmas.begin(); pos != turmas.end(); pos++) {
                            if (pos->first == i) {
                                pos->second->SetSala(salas.at(k));
                                ensalamentosArr.append(pos->second->GetJson());
                            }
                        }
                    }
                }
            }
            // cout << endl;
        }

        Json::Value root(Json::objectValue);
        root["ensalamentos"] = ensalamentosArr;

        string urlHorario = baseURL + "ensalamentos/";
        urlHorario += param_ensalamentoID;
        urlHorario += "/ensalar";
        // cout << root.toStyledString() << endl;
        string responseJson = HttpRequests::post(urlHorario, root);
        cout << responseJson;
    
    } catch (GRBException e) {
        // cout << "Error code = " << e.getErrorCode() << endl;
        // cout << e.getMessage() << endl;
        std::exit(EXIT_FAILURE);
    } catch(...) {
        // cout << "Exception during optimization" << endl;
        std::exit(EXIT_FAILURE);
    }
    
    return 0;
}

/**
 * Configura argumentos passados em command line
 * @param argc
 * @param argv
 */
void setArgs(int argc, char** argv) {
    //opcoes de entrada terminal
    struct option OpcoesLongas[] = {
            {"ajuda", no_argument, NULL, 'h'},
            {"codigo do ensalamento", required_argument, NULL, 'e'},
            {"ano para ensalamento", required_argument, NULL, 'a'},
            {"semestre para ensalamento", required_argument, NULL, 's'},
            {"arquivo sala", required_argument, NULL, 'r'},
            {0, 0, 0, 0}
    };
    
    char optc = 0;  // Parece estranho... Mas todo CHAR é na verdade um INT
    while((optc = getopt_long(argc, argv, "h:e:a:s:r", OpcoesLongas, NULL)) != -1) {
            switch(optc) {
                case 'h' : 
                    break;                                   
                case 'e' :
                    strcpy(param_ensalamentoID, optarg);
                    break;
                case 'a':
                    strcpy(param_ano, optarg);
                    break;
                case 's' :
                    strcpy(param_semestre, optarg);
                    break;
                case 'r' :
                    break;    
                default :
                    printf("Parametros incorretos.\n");
            }
    }
}

/**
 * Configura restrições
 * @param model
 */
void setFuncoesRestricoes(GRBModel* model) {
    for (int i=0; i<num_turmas; i++) {
        for (int j=0; j<num_horarios; j++) {
            GRBLinExpr alocar_aula;
            for (int k=0; k<num_salas; k++) {
                // restrição 1
                model->addConstr( ((x[i][j][k]*demanda[i]) * (1-salas.at(k)->GetArCondicionado())) - 60 - r[i][j][k] <= 0);

                // restrição 2
                model->addConstr( x[i][j][k]*(salas.at(k)->GetCapacidade() - demanda[i]) + s_p[i][j][k] - s_n[i][j][k] == 0);

                // restrição 3
                model->addConstr(x[i][j][k] - v[i][k] <= 0);

                // construção restrições 4
                alocar_aula += x[i][j][k];
            }
            // conjunto de restrições 4
            model->addConstr(alocar_aula == horario[i][j]);
        }
    }
    
    for (int j=0; j<num_horarios; j++) {
        for (int k=0; k<num_salas; k++) {
            GRBLinExpr uma_turma_sala_horario;
            for (int i=0; i<num_turmas; i++) {
                uma_turma_sala_horario += x[i][j][k];
            }
            model->addConstr(uma_turma_sala_horario <= 1);
        }
    }

    for (int i=0; i<num_turmas; i++) {
        GRBLinExpr qtde_sala_utilizada_por_turma;
        for (int k=0; k<num_salas; k++) {
            qtde_sala_utilizada_por_turma += v[i][k];
        }
        qtde_sala_utilizada_por_turma += -1;
        model->addConstr(qtde_sala_utilizada_por_turma <= t[i]);
    }
}

/**
 * Inicializa as variaveis para o gurobi
 * @param model
 */
void initVars(GRBModel* model) {
    // Cria quatro matriz tridimensional de variávels gurobi
    // matriz (turamas X horarios X salas)
    r = new GRBVar**[num_turmas]; // número de alunos acima do limite de 60
    s_p = new GRBVar**[num_turmas]; // número de alunos que ultrapassa capacidade da sala
    s_n = new GRBVar**[num_turmas]; // número da capacidade que ultrapassa a demanda
    x = new GRBVar**[num_turmas]; // alocação de turmas (1 ou 0)

    for (int i=0; i<num_turmas; i++) {

        r[i] = new GRBVar*[num_horarios];
        s_p[i] = new GRBVar*[num_horarios];
        s_n[i] = new GRBVar*[num_horarios];
        x[i] = new GRBVar*[num_horarios];

        for (int j=0; j<num_horarios; j++) {
            r[i][j] = new GRBVar[num_salas];
            s_p[i][j] = new GRBVar[num_salas];
            s_n[i][j] = new GRBVar[num_salas];
            x[i][j] = new GRBVar[num_salas];

            for (int k=0; k<num_salas; k++) {
                r[i][j][k] = model->addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS);
                s_p[i][j][k] = model->addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS);
                s_n[i][j][k] = model->addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS);
                x[i][j][k] = model->addVar(0.0, 1.0, 0.0, GRB_BINARY);
            }
        }
    }

    t = new GRBVar[num_turmas]; // número de salas diferentes que uma sala foi alocada
    v = new GRBVar*[num_turmas]; // alocação de disciplina em sala
    for (int i=0; i<num_turmas; i++) {
        t[i] = model->addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS);
        v[i] = new GRBVar[num_salas];

        for (int k=0; k<num_salas; k++) {
            v[i][k] = model->addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS);
        }
    }
}


/**
 * Configura função objetiva
 * @param model
 */
void setFuncaoObjetivo(GRBModel* model) {
    // variávis de peso para penalidades
    double alpha1 = 100;
    double alpha2 = 100;
    double alpha3 = 100;
    
    GRBLinExpr funcao_objetivo;
    for(int i=0; i<num_turmas; i++) {
        for(int j=0; j<num_horarios; j++) {
            for(int k=0; k<num_salas; k++) {
                funcao_objetivo += alpha1*r[i][j][k] + alpha2*s_p[i][j][k] + 2*s_n[i][j][k];
            }
        }
    }

    for (int i=0; i<num_turmas; i++) {
        for (int k=0; k<num_salas; k++) {
            funcao_objetivo += alpha2*v[i][k];
        }
        funcao_objetivo += alpha3*t[i];
    }

    model->setObjective(funcao_objetivo, GRB_MINIMIZE);
}


/** 
 *  Recupera informações de ensalamento da api
 */
vector<Horario*> getHorarios() {
    vector<Horario*> horarios; 
    string horariosJson = HttpRequests::get(baseURL + "horarios?filters=ano:" + param_ano + ",semestre:" + param_semestre);
    
    Json::Value jData;
    Json::Reader jReader;
    
    if(jReader.parse(horariosJson, jData)) {
        for (Json::Value::ArrayIndex i = 0; i != jData.size(); i++) {
            horarios.push_back(new Horario(jData[i]));
        }
    } 
    else {
        // cout << "Could not parse HTTP data as JSON" << endl;
    }
    return horarios;
}


/**
 * Recupera informações de salas da api
 */
vector<Sala*> getSalas() {
    vector<Sala*> salas;
    string salasJson = HttpRequests::get(baseURL + "salas");
    
    Json::Value jData;
    Json::Reader jReader;
    
    if (jReader.parse(salasJson, jData)) {
        for (Json::Value::ArrayIndex i = 0; i != jData.size(); i++) {
            salas.push_back(new Sala(jData[i]));
        }
    }
    else {
        // cout << "Could not parse HTTP data as JSON" << endl;
    }
    return salas;
}