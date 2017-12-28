/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Turma.h
 * Author: rafael
 *
 * Created on 3 de Dezembro de 2017, 14:24
 */

#ifndef TURMA_H
#define TURMA_H

#include <string>

using namespace std;

class Turma {
public:
    
    Turma();
    Turma(const Turma& orig);
    virtual ~Turma();
    void SetDescricao(string descricao);
    string GetDescricao() const;
    void SetAbreviacao(string abreviacao);
    string GetAbreviacao() const;
    void SetId(int id);
    int GetId() const;
    
    
private:
    int id;
    string abreviacao;
    string descricao;
};

#endif /* TURMA_H */

