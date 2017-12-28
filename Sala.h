/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sala.h
 * Author: rafael
 *
 * Created on 3 de Dezembro de 2017, 16:32
 */

#ifndef SALA_H
#define SALA_H

#include <string>
#include <jsoncpp/json/json.h>

using namespace std;

class Sala {
public:
    
    Sala();
    Sala(const Sala& orig);
    Sala(const Json::Value& jData);
    virtual ~Sala();
    
    void SetArCondicionado(int arCondicionado);
    int GetArCondicionado() const;
    
    void SetCapacidade(int capacidade);
    int GetCapacidade() const;
    
    void SetNome(string nome);
    string GetNome() const;
    
    void SetId(int id);
    int GetId() const;
    
private:
    string nome;
    int capacidade;
    int arCondicionado;
    int id;
};

#endif /* SALA_H */

