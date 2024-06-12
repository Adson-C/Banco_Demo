#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct{
    int codigo;
    char nome[50];
    char email[50];
    char cpf[20];
    char dataNasciimento[20];
    char dataCadstro[20];
}Cliente;

typedef struct{
    int numero;
    Cliente cliente;
    float saldo;
    float limite;
    float saldoTotal; // Saldo + limite
}Conta;

void menu();
void infoCliente(Cliente cliente);
void infoConta(Conta conta);
void criarConta();
void efetuarSaque();
void efetuarDeposito();
void efetuarTransferencia();
void listarConta();
float atualizacaoTotal(Conta conta);
Conta buscarContaPorNumero(int numero);
void sacar(Conta conta, float valor);
void depositar(Conta conta, float valor);
void transferir(Conta conta_origem, Conta conta_destino, float valor);

static Conta contas[50];
static int contador_contas = 0;
static int contador_clientes = 0;

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    menu();
    return 0;
}

void menu() {
    int opcao = 0;
    printf("==================================================\n");
    printf("======================  ATM  ======================\n");
    printf("================= -> JHON BANK <- ==================\n");
    printf("=====================================================\n");

    printf("Selecione uma opção no Menu: \n");
    printf("1 - Criar Conta\n");
    printf("2 - Efetuar Saque\n");
    printf("3 - Efetuar Depósito\n");
    printf("4 - Efetuar Transferência\n");
    printf("5 - Listar Contas\n");
    printf("6 - Sair\n");

    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            criarConta();
            break;
        case 2:
            efetuarSaque();
            break;
        case 3:
            efetuarDeposito();
            break;
        case 4:
            efetuarTransferencia();
            break;
        case 5:
            listarConta();
            break;
        case 6:
            printf("Até a proxima!\n");
            Sleep(2000);
            exit(0);
        default:
            printf("Opção inválida!\n");
            Sleep(2000);
            menu();
            break;
    }
}


void infoCliente(Cliente cliente){
    printf("Código: %d\nNome: %s\nData de Nascimento: %s\nCadastro: %s", cliente.codigo, strtok(cliente.nome, "\n"), 
    strtok(cliente.dataNasciimento, "\n"), strtok(cliente.dataCadstro, "\n"));
}
void infoConta(Conta conta){
    printf("Número da Conta: %d \nCliente: %s\nData Nascimento: %s \nData Cadastro: %s \nSaldo Total: %.2f\n ", conta.numero, strtok(conta.cliente.nome, "\n"),
    strtok(conta.cliente.dataNasciimento, "\n"), strtok(conta.cliente.dataCadstro, "\n"), conta.saldoTotal);
}
void criarConta(){
    // falta implementar a funcionalidade
}
float atualizacaoTotal(Conta conta){
    return conta.saldo + conta.limite;
}
Conta buscarContaPorNumero(int numero){
    Conta conta;
    if (contador_contas > 0) {
        for (int i = 0; i < contador_contas; i++) {
            if(contas[i].numero == numero) {
                conta = contas[i];
        }
    }   
 }
return conta;
}
void sacar(Conta conta, float valor){
    if (valor > 0 && conta.saldoTotal >= valor) {
        for (int i = 0; i < contador_contas; i++) {
            if(contas[i].numero == conta.numero) {
                if (contas[i].saldo >= valor) {
                    contas[i].saldoTotal = atualizacaoTotal(contas[i]);
                    printf("Saque realizado com sucesso!\n");
                }else {
                    float restante = contas[i].saldo - valor;
                    contas[i].limite = contas[i].limite + restante;
                    contas[i].saldo = 0.0;
                    contas[i].saldoTotal = atualizacaoTotal(contas[i]);
                    printf("Saque efetuado com sucesso!\n");
                }
            }
        }
        
    }else {
        printf("Saque não realizado, Tente navamente!\n");
    }
}
void depositar(Conta conta, float valor){
    if (valor > 0) {
        for (int i = 0; i < contador_contas; i++) {
            if(contas[i].numero == conta.numero) {
                contas[i].saldo = contas[i].saldo + valor;
                contas[i].saldoTotal = atualizacaoTotal(contas[i]);
                printf("Depósito efetuado com sucesso!\n");
            }
        }
    }else {
        printf("Deposito não realizado, Tente navamente!\n");
    }
}   
void transferir(Conta conta_origem, Conta conta_destino, float valor){
    if (valor > 0 && conta_origem.saldoTotal >= valor) {
        for (int co = 0; co < contador_contas; co++) {
            if (contas[co].numero == conta_origem.numero){
                for (int cd = 0; cd < contador_contas; cd++){
                    if (contas[cd].numero == conta_destino.numero){
                        if (contas[co].saldo >= valor) {
                            contas[co].saldo = contas[co].saldo - valor;
                            contas[cd].saldo = contas[cd].saldo + valor;
                            contas[co].saldoTotal = atualizacaoTotal(contas[co]);
                            contas[cd].saldoTotal = atualizacaoTotal(contas[cd]);
                            printf("Transferência efetuada com sucesso!\n");
                        }else {
                            float restante = contas[co].saldo - valor;
                            contas[co].limite = contas[co].limite + restante;
                            contas[co].saldo = 0.0;
                            contas[cd].saldo = contas[cd].saldo + valor;
                            contas[co].saldoTotal = atualizacaoTotal(contas[co]);
                            contas[cd].saldoTotal = atualizacaoTotal(contas[cd]);
                            printf("Transferência efetuada com sucesso!\n");
                        }
                    }
                }
            }
        }

    }else {
        printf("Transferência não efetuada, Tente navamente!\n");
    }
}
void efetuarSaque(){
    // falta implementar a funcionalidade
}
void efetuarDeposito(){
    // falta implementar a funcionalidade
}
void efetuarTransferencia(){
    // falta implementar a funcionalidade
}
void listarConta(){
    // falta implementar a funcionalidade
}