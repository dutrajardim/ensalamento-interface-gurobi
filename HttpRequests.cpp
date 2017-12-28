/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HttpRequests.cpp
 * Author: rafael
 * 
 * Created on 3 de Dezembro de 2017, 14:12
 */

#include "HttpRequests.h"

HttpRequests::HttpRequests() {
}

HttpRequests::HttpRequests(const HttpRequests& orig) {
}

HttpRequests::~HttpRequests() {
}

size_t functionCallback(char *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

struct curl_slist *headers = NULL;

string HttpRequests::post(string url, Json::Value data) {
    CURL *curl;
    Json::StyledWriter wr;
    
    string apiUrlEnsalamentos = url;
    string json = wr.write(data);
    
    curl = curl_easy_init();
    
    if(curl) {
        
        int httpCode;
        string httpData;
        
        headers = curl_slist_append(headers, "Content-Type: application/json");
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, apiUrlEnsalamentos.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, functionCallback);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
        
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);
        
        if (httpCode == 200) {
            return httpData;
        }
        else {
            cout << "Couldn't GET from " << apiUrlEnsalamentos << " - exiting" << endl;
        }
        
    }
    return 0;
}

string HttpRequests::get(string url) {
    CURL *curl;
    string apiUrlEnsalamentos = url;
    
    curl = curl_easy_init();
    
    if(curl) {
        
        int httpCode;
        string httpData;
        
        curl_easy_setopt(curl, CURLOPT_URL, apiUrlEnsalamentos.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, functionCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
        
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);
        
        if (httpCode == 200) {
            return httpData;
        }
        else {
            cout << "Couldn't GET from " << apiUrlEnsalamentos << " - exiting" << endl;
        }
        
    }
    return 0;
}