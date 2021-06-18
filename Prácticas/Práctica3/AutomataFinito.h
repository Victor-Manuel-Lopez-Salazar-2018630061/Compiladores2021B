#ifndef AUTOMATAFINITO_H
#define AUTOMATAFINITO_H
#include <bits/stdc++.h>
#include "ReceptorTransiciones.h"
#include "EmisorDatos.h"
using namespace std;
class AutomataFinito
{
protected:
    string estadoInicial;
    vector<string> estados;
    vector<string> estadosAntes;   //antes de la flechita
    vector<string> estadosDespues; //despues de la flechita
    vector<string> estadosFinales;
    string alfabeto;
    vector<string> transiciones;
    //transiciones separadas por inicial, simbolo del alfabeto -> final
    vector<int> transicionesEstadoIncial;
    vector<int> transicionesEstadoFinal;
    string transicionesAlfabeto;
public:
    ReceptorTransiciones archivo;
    EmisorDatos emisor;
    AutomataFinito();
    ~AutomataFinito();
    void llenadoDeAutomataFinito();
    void establecerTrancisiones();
    // getters
    string getEstadoInicial();
    vector<string> getEstados();
    vector<string> getEstadosFinales();
    string getAlfabeto();
    vector<string> getTransiciones();
    //setters
    void setEstadoInicial(string);
    void setEstados(vector<string>);
    void setEstadosFinales(vector<string>);
    void setAlfabeto(string);
    void setTransiciones(vector<string>);
};
//Constructor
AutomataFinito::AutomataFinito(/* args */)
{
}
//Destructor
AutomataFinito::~AutomataFinito()
{
}
//lenado de Automata Finito
void AutomataFinito::llenadoDeAutomataFinito()
{
    //transiciones
    transiciones = archivo.getTransiciones();
    //alfabeto
    int repetidas = 0; // variable auxiliar
    for (int i = 0; i < transiciones.size(); i++)
    {
        for (int j = 0; j < transiciones[i].size(); j++)
        {
            if (j > 0 && transiciones[i][j - 1] == ',')
            {
                if (alfabeto.size() == 0)
                    alfabeto.push_back(transiciones[i][j]);
                else
                {
                    for (int k = 0; k < alfabeto.size(); k++)
                    {
                        if (transiciones[i][j] == alfabeto[k])
                            repetidas++;
                    }
                    if (repetidas == 0)
                        alfabeto.push_back(transiciones[i][j]);
                    repetidas = 0;
                }
            }
        }
    }
    // estados antes de la ,
    string estadoAux; // variable auxiliar
    for (int i = 0; i < transiciones.size(); i++)
    {
        for (int j = 0; j < transiciones[i].size(); j++)
        {
            estadoAux.push_back(transiciones[i][j]);
            if (transiciones[i][j + 1] == ',')
                break;
        }
        if (estados.size() == 0)
            estados.push_back(estadoAux);
        else
        {
            for (int k = 0; k < estados.size(); k++)
            {
                if (estadoAux == estados[k])
                    repetidas++;
            }
            if (repetidas == 0)
                estados.push_back(estadoAux);
            repetidas = 0;
        }
        estadoAux.clear();
        estadosAntes = estados;
    }

    // estados despues de la ->
    int flecha = 0;
    for (int i = 0; i < transiciones.size(); i++)
    {
        for (int j = 0; j < transiciones[i].size(); j++)
        {
            if (j > 0 && transiciones[i][j - 1] == '>')
                flecha = 1;
            if (flecha == 1)
                estadoAux.push_back(transiciones[i][j]);
        }
        if (estados.size() == 0)
            estados.push_back(estadoAux);
        else
        {
            for (int k = 0; k < estados.size(); k++)
            {
                if (estadoAux == estados[k])
                    repetidas++;
            }
            if (repetidas == 0)
                estados.push_back(estadoAux);
            repetidas = 0;
        }
        if (estadosDespues.size() == 0)
            estadosDespues.push_back(estadoAux);
        else
        {
            for (int k = 0; k < estadosDespues.size(); k++)
            {
                if (estadoAux == estadosDespues[k])
                    repetidas++;
            }
            if (repetidas == 0)
                estadosDespues.push_back(estadoAux);
            repetidas = 0;
        }
        estadoAux.clear();
        flecha = 0;
    }
    // estado inicial
    for (int i = 0; i < estadosAntes.size(); i++)
    {
        for (int j = 0; j < estadosDespues.size(); j++)
        {
            if (estadosAntes[i] == estadosDespues[j])
                repetidas++;
        }
        if (repetidas == 0)
            estadoInicial = estadosAntes[i];
        repetidas = 0;
        break;
    }
    // estados finales
    for (int i = 0; i < estadosDespues.size(); i++)
    {
        for (int j = 0; j < estadosAntes.size(); j++)
        {
            if (estadosDespues[i] == estadosAntes[j])
                repetidas++;
        }
        if (repetidas == 0)
        {
            if (estadosFinales.size() == 0)
                estadosFinales.push_back(estadosDespues[i]);
            else
            {
                for (int k = 0; k < estadosFinales.size(); k++)
                {
                    if (estadosDespues[i] == estadosFinales[k])
                        repetidas++;
                }
                if (repetidas == 0)
                    estadosFinales.push_back(estadosDespues[i]);
            }
        }
        repetidas = 0;
    }
}
//establecer trancisiones
void AutomataFinito::establecerTrancisiones()
{
    string aux;
    int coma = 0, flecha = 0;
    for (int i = 0; i < transiciones.size(); i++)
    {
        for (int j = 0; j < transiciones[i].size(); j++)
        {
            if (transiciones[i][j] == ',')
            {
                coma++;
                transicionesEstadoIncial.push_back(atoi(aux.c_str()));
                aux.clear();
            }
            else if (transiciones[i][j] == '>')
            {
                flecha++;
            }
            else if (coma == 0 && flecha == 0)
                aux.push_back(transiciones[i][j]);
            else if (coma != 0 && flecha == 0 && transiciones[i][j] != '-')
                transicionesAlfabeto.push_back(transiciones[i][j]);
            else if (coma != 0 && flecha != 0)
                aux.push_back(transiciones[i][j]);
        }
        transicionesEstadoFinal.push_back(atoi(aux.c_str()));
        aux.clear();
        coma = 0;
        flecha = 0;
    }
}
//gets
string AutomataFinito::getEstadoInicial()
{
    return estadoInicial;
}
vector<string> AutomataFinito::getEstados()
{
    return estados;
}
vector<string> AutomataFinito::getEstadosFinales()
{
    return estadosFinales;
}
string AutomataFinito::getAlfabeto()
{
    return alfabeto;
}
vector<string> AutomataFinito::getTransiciones()
{
    return transiciones;
}
//setters
void AutomataFinito::setEstadoInicial(string estadoInicial)
{
    this->estadoInicial = estadoInicial;
}
void AutomataFinito::setEstados(vector<string> estados)
{
    this->estados = estados;
}
void AutomataFinito::setEstadosFinales(vector<string> estadosFinales)
{
    this->estadosFinales = estadosFinales;
}
void AutomataFinito::setAlfabeto(string alfabeto)
{
    this->alfabeto = alfabeto;
}
void AutomataFinito::setTransiciones(vector<string> transiciones)
{
    this->transiciones = transiciones;
}
#endif