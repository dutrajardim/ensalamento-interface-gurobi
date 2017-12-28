/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Disciplina.h
 * Author: rafael
 *
 * Created on 3 de Dezembro de 2017, 14:24
 */

#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <string>

using namespace std;

class Disciplina {
public:
    
    Disciplina();
    Disciplina(const Disciplina& orig);
    virtual ~Disciplina();
    
    void SetNome(string nome);
    string GetNome() const;
    void SetId(int id);
    int GetId() const;
    
private:
    int id;
    string nome;
};

#endif /* DISCIPLINA_H */

