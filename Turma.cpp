/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Turma.cpp
 * Author: rafael
 * 
 * Created on 3 de Dezembro de 2017, 14:24
 */

#include "Turma.h"

Turma::Turma() {
}

Turma::Turma(const Turma& orig) {
}

Turma::~Turma() {
}

void Turma::SetDescricao(string descricao) {
    this->descricao = descricao;
}

string Turma::GetDescricao() const {
    return descricao;
}

void Turma::SetAbreviacao(string abreviacao) {
    this->abreviacao = abreviacao;
}

string Turma::GetAbreviacao() const {
    return abreviacao;
}

void Turma::SetId(int id) {
    this->id = id;
}

int Turma::GetId() const {
    return id;
}

