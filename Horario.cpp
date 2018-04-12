/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ensalamento.cpp
 * Author: rafael
 * 
 * Created on 3 de Dezembro de 2017, 14:21
 */

#include "Horario.h"

Horario::Horario() {
    this->SetDisciplina(new Disciplina());
    this->SetTurma(new Turma());
}

Horario::Horario(const Json::Value& jData) {
    this->SetDisciplina(new Disciplina());
    this->SetTurma(new Turma());
    
    this->SetId(jData["id"].asInt());
    this->SetDia(jData["dia"].asString());
    this->SetHorario(jData["horario"].asInt());
    this->SetAlunos_qtd(jData["alunos_qtd"].asInt());
    this->SetDisciplinasTurmasId(jData["disciplinas_turmas_id"].asInt());

    this->GetDisciplina()->SetId(jData["disciplina"]["id"].asInt());
    this->GetDisciplina()->SetNome(jData["disciplina"]["nome"].asString());
    
    this->GetTurma()->SetId(jData["turma"]["id"].asInt());
    this->GetTurma()->SetAbreviacao(jData["turma"]["abreviacao"].asString());
    this->GetTurma()->SetDescricao(jData["turma"]["descricao"].asString());
}

Horario::Horario(const Horario& orig) {
}

Horario::~Horario() {
}

Json::Value Horario::GetJson() {
    Json::Value value(Json::objectValue);
    value["salas_id"] = this->GetSala()->GetId();
    ostringstream str;
    str << this->GetDia();
    value["horarios_id"] = this->GetId();
    value["dia"] = str.str();
    value["horario"] = this->GetHorario();
    value["disciplinas_turmas_id"] = this->GetDisciplinasTurmasId();
    return value;
}

void Horario::SetHorario(int horario) {
    this->horario = horario;
}

int Horario::GetHorario() const {
    return horario;
}

void Horario::SetDia(int dia) {
    this->dia = dia;
}

void Horario::SetDia(string dia) {
    this->dia = atoi(dia.c_str());
}

int Horario::GetDia() const {
    return dia;
}

void Horario::SetTurma(Turma* turma) {
    this->turma = turma;
}

Turma* Horario::GetTurma() const {
    return turma;
}

void Horario::SetDisciplina(Disciplina* disciplina) {
    this->disciplina = disciplina;
}

Disciplina* Horario::GetDisciplina() const {
    return disciplina;
}

void Horario::SetId(int id) {
    this->id = id;
}

int Horario::GetId() const {
    return id;
}

void Horario::SetAlunos_qtd(int alunos_qtd) {
    this->alunos_qtd = alunos_qtd;
}

int Horario::GetAlunos_qtd() const {
    return alunos_qtd;
}

void Horario::SetDisciplinasTurmasId(int disciplinasTurmasId) {
    this->disciplinasTurmasId = disciplinasTurmasId;
}

int Horario::GetDisciplinasTurmasId() const {
    return disciplinasTurmasId;
}

void Horario::SetSala(Sala* sala) {
    this->sala = sala;
}

Sala* Horario::GetSala() const {
    return sala;
}


