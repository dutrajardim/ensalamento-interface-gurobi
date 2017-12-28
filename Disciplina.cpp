/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Disciplina.cpp
 * Author: rafael
 * 
 * Created on 3 de Dezembro de 2017, 14:24
 */

#include "Disciplina.h"

Disciplina::Disciplina() {
}

Disciplina::Disciplina(const Disciplina& orig) {
}

Disciplina::~Disciplina() {
}

void Disciplina::SetNome(string nome) {
    this->nome = nome;
}

string Disciplina::GetNome() const {
    return nome;
}

void Disciplina::SetId(int id) {
    this->id = id;
}

int Disciplina::GetId() const {
    return id;
}

