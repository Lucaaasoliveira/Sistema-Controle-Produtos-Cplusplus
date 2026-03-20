#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
using namespace std;
//Definida 100 para produtos do mercadinho
const int maxProdutos = 100;

void incluirProduto();
void consultaProduto();
void adquirirProduto();
void venderProduto();
void exibirRelatorio();
 //validar pra ver se o produto ja existe
bool produtoExiste(int, string, string[]);
//função para validar a data correta
bool validarData(string, int&, int&, int& );
int menu();

//se eu declaro esses vetores no main da um monte de erro, nao me pergunte o pq
string nomes[maxProdutos];
bool pereciveis[maxProdutos];
float precosUnitarios[maxProdutos];
int quantidades[maxProdutos], vetDia[maxProdutos], vetMes[maxProdutos], vetAno[maxProdutos];

//declarado aqui a variavel que vai controlar os for's
int numProdutos = 0;

int main()
{
    int escolha;

    //menu em função também
    do{
    escolha = menu();
    switch (escolha){
        case 1:
            incluirProduto();
            break;
        case 2:
            consultaProduto();
            break;
        case 3:
            adquirirProduto();
            break;
        case 4:
            venderProduto();
            break;
        case 5:
            exibirRelatorio();
            break;
        case 0:
            cout << "PROGRAMA ENCERRADO!";
            break;
        default:
            cout << "Opcao invalida!" << endl;
       }
       }while(escolha != 0);

    return 0;
}

int menu(){
    int opcao;
    do{
            cout << "Opcoes do menu a seguir: " << endl;
            cout << "1- Incluir um produto." << endl;
            cout << "2- Consultar um produto." << endl;
            cout << "3- Adquirir um produto." << endl;
            cout << "4- Vender um produto." << endl;
            cout << "5- Relatorio dos produtos." << endl;
            cout << "0- Sair" << endl;
            cout << "--------------------------" << endl;
            cout << "Escolha uma opcao: ";
            cin >> opcao;
            cin.ignore();
       }while(opcao < 0 or opcao > 5);
       return opcao;

}
void incluirProduto(){

    string nome, dataValidade;
    bool perecivel;
    char resp;
    float precoUnit;
    int qntd;

    //Pra ver se há mais produtos do que o limite
    if(numProdutos > maxProdutos){
        cout << "Limite de produtos atingidos!";
        return;
    }

    cout << "Digite o nome do produto: " << endl;
    getline(cin, nome);

    //for para transformar o nome todo em maiusculo
    for(unsigned int i = 0; i < nome.size(); i++)
        nome[i] = toupper(nome[i]);

    cout << "--------------------------" << endl;

    //condicao pra ver se o produto ja existe
    if(produtoExiste(numProdutos, nome, nomes)){
        cout << "Produto ja existente." << endl;
        return;}

    do{
    cout << "O produto eh perecivel?(S/N): ";
    cin.get(resp);
    cin.ignore();
    }while(toupper(resp) != 'S' and toupper(resp)!= 'N');
    cout << "-------------------------- " << endl;
    //condicao se for S(true) e N(false)
    if (resp == 'S')
        perecivel = true;
    else
        perecivel = false;

    do{
        cout << "Digite o preco unitario do produto: ";
        cin >> precoUnit;
    }while(precoUnit < 0);
    cin.ignore();
    cout << "--------------------------" << endl;

    do{
        cout << "Digite a quantidade de produtos: ";
        cin >> qntd;
    }while(qntd < 0);
    cout << "--------------------------" << endl;

    int dia, mes, ano;
    cout << "Digite a data de validade do produto no formato(DD/MM/AAAA): ";
    cin >> dataValidade;

    //Condicao para se retornar true mostrar a data válida, se nao retorna vazio e refaz o programa
    //se eu colocasse isso num do while dava um erro e eu nao sei resolver esse erro
    if (validarData(dataValidade, dia, mes, ano)){
        cout << "Data valida: Dia=" << dia << "  Mes=" << mes << "   Ano=" << ano << endl;
        cout << "--------------------------" << endl;
    }
    else{
        cout << "Selecione novamente a opçao no menu e coloque os dados corretamente!" <<  endl;
        cout << "--------------------------" << endl;
        return;
    }

    //espaço para atribuição dos dados nos vetores
    nomes[numProdutos] = nome;
    pereciveis[numProdutos] = perecivel;
    precosUnitarios[numProdutos] = precoUnit;
    quantidades[numProdutos] = qntd;
    vetDia[numProdutos] = dia;
    vetMes[numProdutos] = mes;
    vetAno[numProdutos] = ano;

    numProdutos++;
    cout << "INCLUSAO CONFIRMADA!" << endl;
    cout << "--------------------------" << endl;
}
void consultaProduto(){
    string nome;
    do{
        cout << "Digite o nome do produto que quer consultar: ";
        getline(cin, nome);
    }while(nome == "" or nome == " ");
    cout << "--------------------------" << endl;

    //for para transformar o nome todo em maiusculo
    for(unsigned int i = 0; i < nome.size(); i++)
        nome[i] = toupper(nome[i]);

    for(int i = 0; i <= numProdutos; i++){
        if(nomes[i] == nome){
            cout << ">>Nome do produto: \n" << nomes[i] << endl;
            //0- se nao for perecivel / 1-se for perecivel
            cout << ">>Perecivel(1-Sim/0-Nao):\n " << pereciveis[i] << endl;
            cout << ">>Preco de venda unitario: \n R$" << precosUnitarios[i] << endl;
            cout << ">>Quantidade em estoque: \n" << quantidades[i] << endl;
            cout << ">>Data de validade: \n" << vetDia[i] << "/" << vetMes[i] << "/" << vetAno[i] << endl;
            cout << "--------------------------" << endl;
            return;
        }
    }
    cout << "PRODUTO INEXISTENTE!";
    cout << "--------------------------" << endl;
}
void adquirirProduto(){
    string nome; int quantidade;
    do{
        cout << "Digite o nome do produto que quer incrementar: ";
        getline(cin, nome);
        cin.ignore();

    }while(nome == "" or nome == " ");
    cout << "--------------------------" << endl;

    //for para transformar o nome todo em maiusculo
    for(unsigned int i = 0; i < nome.size(); i++)
        nome[i] = toupper(nome[i]);

    for(int i = 0; i <= numProdutos; i++){
        if(nomes[i] == nome){
            cout << "Digite a quantidade a ser aumentada: ";
            cin >> quantidade;
            cout << "--------------------------" << endl;
            quantidades[i] += quantidade;
            cout << "AQUISICAO CONFIRMADA!" << endl;
            cout << "--------------------------" << endl;
            cout << ">>Quantidade atual: \n" << quantidades[i] << " unidades." << endl;
            cout << "--------------------------" << endl;
            return;
        }
    }
    cout << "PRODUTO INEXISTENTE!";
    cout << "--------------------------" << endl;
}
void venderProduto(){
    string nome; int quantidade; char confirmacao;
    do{
        cout << "Digite o nome do produto a ser vendido: ";
        getline(cin, nome);
    }while(nome == "" or nome == " ");
    cout << "--------------------------" << endl;

    //for para transformar o nome todo em maiusculo
    for(unsigned int i = 0; i < nome.size(); i++)
        nome[i] = toupper(nome[i]);

    for(int i = 0; i <= numProdutos; i++){
        if(nomes[i] == nome){
            cout << "Digite a quantidade a ser vendida: ";
            cin >> quantidade;
            cin.ignore();
            cout << "--------------------------" << endl;
            if(quantidade <= quantidades[i]){
                float total;
                total = quantidade * precosUnitarios[i];
                cout << ">>Quantidade vendida do produto: " << quantidade << " unidades." << endl;
                cout << ">>Preco da venda de cada produto: R$" << precosUnitarios[i] << endl;
                cout << ">>Total a pagar: R$" << total << endl;
                cout << "--------------------------" << endl;
                do{
                    //se eu fizesse toupper(confirmacao) = 'S' dava uma warning
                    cout << "Confirmar a venda?(S/N): " << endl;
                    cin.get(confirmacao);
                    confirmacao = toupper(confirmacao);
                }while(confirmacao != 'S' and confirmacao != 'N');

                if(confirmacao == 'S'){
                    quantidades[i] -= quantidade;
                    cout << "VENDA REALIZADA!" << endl;
                    cout << "--------------------------" << endl;
                }
                else{
                    cout << "VENDA CANCELADA!" << endl;
                    cout << "--------------------------" << endl;
                }
        }
        else{
            cout << "NAO HA ESTOQUE SUFICENTE!" << endl;
            cout << "--------------------------" << endl;
        }
        return;
        }
    }
    cout << "PRODUTO INEXISTENTE!" << endl;
    cout << "--------------------------" << endl;
}
void exibirRelatorio(){
    cout << "Relatorio de produtos: " << endl;
    cout << "--------------------------" << endl;
    for(int i = 0; i < numProdutos; i++){
        cout << "Nome: \n" << nomes[i] << endl;
        //0- se nao for perecivel / 1- se for perecivel
        cout << "Perecivel(1-Sim/0-Nao): \n" << pereciveis[i] << endl;
        cout << "Preco Unitario: \n" << precosUnitarios[i] << endl;
        cout << "Quantidade em estoque: \n" << quantidades[i] << endl;
        cout << "Data de validade: \n" << vetDia[i] << "/" << vetMes[i] << "/" << vetAno[i] << endl;
        cout << "------------------------------------------" << endl;
    }
}
bool produtoExiste(int numProdutos, string nome,string nomes[]){
    //mudei nome pra nomeProd para ficar mais facil de entender
    string nomeProd = nome;
    for(int i = 0; i < numProdutos; i++){
        if(nomeProd == nomes[i])
            return true;
    }
    return false;
}
bool validarData(string data, int& dia, int& mes, int& ano) {
    //fazer com for dava um erro que eu nao sabia arrumar
    // tinha que ter 10 caracteres
    // sendo o 2 e o 5 = /
    if (data.size() != 10 or not isdigit(data[0]) or not isdigit(data[1]) or data[2] != '/' or not isdigit(data[3]) or not isdigit(data[4]) or data[5] != '/' or not isdigit(data[6]) or not isdigit(data[7]) or not isdigit(data[8]) or not isdigit(data[9])) {
        return false;
    }

    //convertemos string para int de acordo com o periodo
    //dia de 0 a 1, mes de 3 a 4 e ano de 6 a 9
    dia = atoi(data.substr(0, 2).c_str());
    mes = atoi(data.substr(3, 2).c_str());
    ano = atoi(data.substr(6, 4).c_str());

    //para validar a data de cada dia, mes e ano
    //coloquei o ano de 2023 sendo menor
    //e a validade maxima para 2050(exagero)
    if (dia < 1 or dia > 31 or mes < 1 or mes > 12 or ano < 2023 or ano > 2050) {
        return false;
    }

    return true;
}
