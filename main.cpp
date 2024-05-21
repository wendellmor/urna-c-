#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

map<int, string> eleitores;
map<int, pair<string, int>> candidatos;
map<int, int> votos_candidatos;

bool identificadorValido(int identificador) {
    return identificador >= 10000 && identificador <= 99999;
}

bool incluirEleitor() {
    string nome;
    int idade, identificador;
    cout << "Nome do eleitor: ";
    cin >> nome;
    cout << "Idade do eleitor: ";
    cin >> idade;
    cout << "Identificador do eleitor (5 digitos): ";
    cin >> identificador;

    if (!identificadorValido(identificador)) {
        cout << "Erro em incluir o eleitor (identificador)" << endl;
        return false;
    } else if (eleitores.find(identificador) != eleitores.end()) {
        cout << "Erro em incluir eleitor: identificador ja existe" << endl;
        return false;
    } else {
        eleitores[identificador] = nome;
        cout << "Eleitor " << nome << " incluido com sucesso." << endl;
        return true;
    }
}

bool incluirCandidato() {
    string nome;
    int idade, identificador, numero_votacao;
    cout << "Nome do candidato: ";
    cin >> nome;
    cout << "Idade do candidato: ";
    cin >> idade;
    cout << "Identificador do candidato (exatamente 5 digitos): ";
    cin >> identificador;
    cout << "Numero de votacao do candidato: ";
    cin >> numero_votacao;

    if (!identificadorValido(identificador)) {
        cout << "Erro em incluir candidato: identificador nao e de 5 digitos" << endl;
        return false;
    } else if (candidatos.find(identificador) != candidatos.end()) {
        cout << "Erro em incluir candidato: identificador ja existe" << endl;
        return false;
    } else {
        candidatos[identificador] = make_pair(nome, idade);
        votos_candidatos[numero_votacao] = 0;
        cout << "Candidato " << nome << " adicionado." << endl;
        return true;
    }
}

bool iniciarEleicao() {
    if (eleitores.empty() || candidatos.empty()) {
        cout << "Erro: Nao ha eleitores ou candidatos suficientes para iniciar a eleicao." << endl;
        return false;
    }

    cout << "Eleicao em andamento" << endl;
    for (auto &pair : eleitores) {
        int identificador = pair.first;
        string nome = pair.second;
        cout << "Eleitor " << nome << ", digite o candidato (numero) ou digite 0 para voto em branco(ninguem) :" << endl;
        for (auto &c : candidatos) {
            cout << " " << c.first << ": " << c.second.first << endl;
        }
        int voto;
        cin >> voto;
        if (candidatos.find(voto) != candidatos.end()) {
            votos_candidatos[voto] += 1;
        } else {
            cout << "Voto em branco contabilizado." << endl;
        }
    }

    int max_votos = -1;
    int vencedor;
    for (auto &v : votos_candidatos) {
        if (v.second > max_votos) {
            max_votos = v.second;
            vencedor = v.first;
        }
    }
    cout << "O vencedor da eleicao e " << candidatos[vencedor].first << " com " << max_votos << " votos." << endl;
    return true;
}

int main() {
    int opcao;
    do {
        cout <<"" << endl;
        cout << "1.Incluir eleitor" << endl;
        cout << "2.Incluir candidato" << endl;
        cout << "3.Comecar eleicao" << endl;
        cout << "4.Sair" << endl;
        cin >> opcao;

        bool resultado;
        switch (opcao) {
            case 1:
                resultado = incluirEleitor();
                if (!resultado) {
                    cout << "Falha ao incluir eleitor." << endl;
                }
                break;
            case 2:
                resultado = incluirCandidato();
                if (!resultado) {
                    cout << "Falha ao incluir candidato." << endl;
                }
                break;
            case 3:
                resultado = iniciarEleicao();
                if (!resultado) {
                    cout << "Houve um erro ao iniciar eleicao." << endl;
                }
                break;
            case 4:
                cout << "O programa esta fechando..." << endl;
                break;
            default:
                cout << "Opcao invalida" << endl;
        }
    } while (opcao != 4);

    return 0;
}