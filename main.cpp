#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Eleitor {
    string nome;
    int idade;
    int identificador;
};

struct Candidato {
    string nome;
    int idade;
    int identificador;
    int numero_votacao;
    int votos;
};

map<int, Eleitor> eleitores;
map<int, Candidato> candidatos;

bool identificadorValido(int identificador) {
    return identificador >= 10000 && identificador <= 99999;
}

bool incluirEleitor() {
    Eleitor eleitor;
    cout << "Nome do eleitor: ";
    cin >> eleitor.nome;
    cout << "Idade do eleitor: ";
    cin >> eleitor.idade;
    cout << "Identificador do eleitor (exatamente 5 dígitos): ";
    cin >> eleitor.identificador;

    if (!identificadorValido(eleitor.identificador)) {
        cout << "Erro em incluir eleitor: identificador não é de 5 dígitos" << endl;
        return false;
    } else if (eleitores.find(eleitor.identificador) != eleitores.end()) {
        cout << "Erro em incluir eleitor: identificador já existe" << endl;
        return false;
    } else {
        eleitores[eleitor.identificador] = eleitor;
        cout << "Eleitor " << eleitor.nome << " incluído com sucesso." << endl;
        return true;
    }
}

bool incluirCandidato() {
    Candidato candidato;
    cout << "Nome do candidato: ";
    cin >> candidato.nome;
    cout << "Idade do candidato: ";
    cin >> candidato.idade;
    cout << "Identificador do candidato (exatamente 5 dígitos): ";
    cin >> candidato.identificador;
    cout << "Número de votação do candidato: ";
    cin >> candidato.numero_votacao;

    if (!identificadorValido(candidato.identificador)) {
        cout << "Erro em incluir candidato: identificador não é de 5 dígitos" << endl;
        return false;
    } else if (eleitores.find(candidato.identificador) != eleitores.end()) {
        cout << "Erro em incluir candidato: identificador já existe" << endl;
        return false;
    } else {
        candidato.votos = 0;
        eleitores[candidato.identificador] = {candidato.nome, candidato.idade, candidato.identificador};
        candidatos[candidato.numero_votacao] = candidato;
        cout << "Candidato " << candidato.nome << " adicionado com sucesso." << endl;
        return true;
    }
}

bool iniciarEleicao() {
    if (eleitores.empty() || candidatos.empty()) {
        cout << "Erro: Não há eleitores ou candidatos suficientes para iniciar a eleição." << endl;
        return false;
    }

    cout << "Iniciando eleição..." << endl;
    for (auto &pair : eleitores) {
        Eleitor &eleitor = pair.second;
        if (candidatos.find(eleitor.identificador) != candidatos.end()) {
            continue;
        }
        cout << "Eleitor " << eleitor.nome << ", vote em um candidato (número) ou digite 0 para voto em branco:" << endl;
        for (auto &c : candidatos) {
            cout << " " << c.second.numero_votacao << ": " << c.second.nome << endl;
        }
        int voto;
        cin >> voto;
        if (candidatos.find(voto) != candidatos.end()) {
            candidatos[voto].votos += 1;
        } else {
            cout << "Voto em branco registrado." << endl;
        }
    }

    Candidato vencedor;
    bool primeiro = true;
    for (auto &c : candidatos) {
        if (primeiro || c.second.votos > vencedor.votos ||
            (c.second.votos == vencedor.votos && c.second.idade < vencedor.idade) ||
            (c.second.votos == vencedor.votos && c.second.idade == vencedor.idade && c.second.identificador < vencedor.identificador)) {
            vencedor = c.second;
            primeiro = false;
        }
    }
    cout << "O vencedor da eleição é " << vencedor.nome << " com " << vencedor.votos << " votos." << endl;
    return true;
}

int main() {
    int opcao;
    do {
        cout << "\nEscolha uma opção:" << endl;
        cout << "1. Incluir eleitor" << endl;
        cout << "2. Incluir candidato" << endl;
        cout << "3. Iniciar eleição" << endl;
        cout << "4. Sair" << endl;
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
                    cout << "Falha ao iniciar eleição." << endl;
                }
                break;
            case 4:
                cout << "Encerrando o programa." << endl;
                break;
            default:
                cout << "Opção inválida" << endl;
        }
    } while (opcao != 4);

    return 0;
}