/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ensalamento.h
 * Author: rafael
 *
 * Created on 3 de Dezembro de 2017, 14:21
 */

#ifndef HORARIO_H
#define HORARIO_H

#include <jsoncpp/json/json.h>

#include "Turma.h"
#include "Disciplina.h"
#include "Sala.h"
#include <stdlib.h> 
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Horario {
public:
    Horario();
    Horario(const Horario& orig);
    Horario(const Json::Value& jData);
    virtual ~Horario();

    void SetHorario(int horario);
    int GetHorario() const;

    void SetDia(int dia);
    void SetDia(string dia);
    int GetDia() const;

    void SetTurma(Turma* turma);
    Turma* GetTurma() const;
    
    void SetDisciplina(Disciplina* disciplina);
    Disciplina* GetDisciplina() const;
    
    void SetId(int id);
    int GetId() const;
    
    void SetAlunos_qtd(int alunos_qtd);
    int GetAlunos_qtd() const;

    void SetDisciplinasTurmasId(int disciplinasTurmasId);
    int GetDisciplinasTurmasId() const;
    
    void SetSala(Sala* sala);
    Sala* GetSala() const;
    
    Json::Value GetJson();

private:
    int id;
    int dia;
    int horario;
    int alunos_qtd;
    int disciplinasTurmasId;

    Disciplina *disciplina;
    Turma *turma;
    Sala *sala;
};

#endif /* ENSALAMENTO_H */

