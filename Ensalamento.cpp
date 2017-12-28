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

#include "Ensalamento.h"

Ensalamento::Ensalamento() {
    this->SetDisciplina(new Disciplina());
    this->SetTurma(new Turma());
}

Ensalamento::Ensalamento(const Json::Value& jData) {
    this->SetDisciplina(new Disciplina());
    this->SetTurma(new Turma());
    
    this->SetId(jData["id"].asInt());
    this->SetDia(jData["dia"].asString());
    this->SetHorario(jData["horario"].asInt());
    this->SetAlunos_qtd(jData["alunos_qtd"].asInt());

    this->GetDisciplina()->SetId(jData["disciplina"]["id"].asInt());
    this->GetDisciplina()->SetNome(jData["disciplina"]["nome"].asString());
    
    this->GetTurma()->SetId(jData["turma"]["id"].asInt());
    this->GetTurma()->SetAbreviacao(jData["turma"]["abreviacao"].asString());
    this->GetTurma()->SetDescricao(jData["turma"]["descricao"].asString());
}

Ensalamento::Ensalamento(const Ensalamento& orig) {
}

Ensalamento::~Ensalamento() {
}

Json::Value Ensalamento::GetJson() {
    Json::Value value(Json::objectValue);
    value["turmas_id"] = this->GetTurma()->GetId();
    value["dia"] = this->GetDia();
    value["horario"] = this->GetHorario();
    value["disciplinas_id"] = this->GetDisciplina()->GetId();
    value["salas_id"] = this->GetSala()->GetId();
    return value;
}

void Ensalamento::SetHorario(int horario) {
    this->horario = horario;
}

int Ensalamento::GetHorario() const {
    return horario;
}

void Ensalamento::SetDia(int dia) {
    this->dia = dia;
}

void Ensalamento::SetDia(string dia) {
    this->dia = atoi(dia.c_str());
}

int Ensalamento::GetDia() const {
    return dia;
}

void Ensalamento::SetTurma(Turma* turma) {
    this->turma = turma;
}

Turma* Ensalamento::GetTurma() const {
    return turma;
}

void Ensalamento::SetDisciplina(Disciplina* disciplina) {
    this->disciplina = disciplina;
}

Disciplina* Ensalamento::GetDisciplina() const {
    return disciplina;
}

void Ensalamento::SetId(int id) {
    this->id = id;
}

int Ensalamento::GetId() const {
    return id;
}

void Ensalamento::SetAlunos_qtd(int alunos_qtd) {
    this->alunos_qtd = alunos_qtd;
}

int Ensalamento::GetAlunos_qtd() const {
    return alunos_qtd;
}

void Ensalamento::SetSala(Sala* sala) {
    this->sala = sala;
}

Sala* Ensalamento::GetSala() const {
    return sala;
}


