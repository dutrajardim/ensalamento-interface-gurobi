/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpRequests.h
 * Author: rafael
 *
 * Created on 3 de Dezembro de 2017, 14:11
 */

#ifndef HTTPREQUESTS_H
#define HTTPREQUESTS_H

#include <jsoncpp/json/json.h>
#include <curl/curl.h>
#include <iostream>
#include <string>

using namespace std;

class HttpRequests {
public:
    HttpRequests();
    HttpRequests(const HttpRequests& orig);
    virtual ~HttpRequests();
    
    static string get(string url);
    static string post(string url, Json::Value data);
private:

};

#endif /* HTTPREQUESTS_H */

