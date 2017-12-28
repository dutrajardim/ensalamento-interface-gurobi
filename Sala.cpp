/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sala.cpp
 * Author: rafael
 * 
 * Created on 3 de Dezembro de 2017, 16:32
 */

#include "Sala.h"

Sala::Sala() {
}

Sala::Sala(const Sala& orig) {
}

Sala::Sala(const Json::Value& jData) {
    this->SetNome(jData["nome"].asString());
    this->SetArCondicionado(jData["arCondicionado"].asInt());
    this->SetCapacidade(jData["capacidade"].asInt());
    this->SetId(jData["id"].asInt());
}

Sala::~Sala() {
}

void Sala::SetArCondicionado(int arCondicionado) {
    this->arCondicionado = arCondicionado;
}

/*
 * Retorna valor que informa se sala possui arcondicionado
 * @return 0: não possui ar, 1: possui ar
 */
int Sala::GetArCondicionado() const {
    return arCondicionado;
}

void Sala::SetCapacidade(int capacidade) {
    this->capacidade = capacidade;
}

int Sala::GetCapacidade() const {
    return capacidade;
}

void Sala::SetNome(string nome) {
    this->nome = nome;
}

string Sala::GetNome() const {
    return nome;
}

void Sala::SetId(int id) {
    this->id = id;
}

int Sala::GetId() const {
    return id;
}

