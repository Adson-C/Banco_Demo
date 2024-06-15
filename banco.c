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
    Cliente cliente;

	// Data de cadastro
	char dia[3]; //06\0
	char mes[3]; //08
	char ano[5]; //2024
	char data_cadastro[20];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	// dia
	if (tm.tm_mday < 10){
		sprintf(dia, "0%d", tm.tm_mday); // 1,2,3,4,5,6,7,8,9 -> 01/05/2022
	}else{
		sprintf(dia, "%d", tm.tm_mday);
	}
	// mes
	if (tm.tm_mon + 1 < 10){
		sprintf(mes, "0%d", tm.tm_mon + 1); // 01/05/2022
	}else{
		sprintf(mes, "%d", tm.tm_mon + 1);
	}
	// ano
	sprintf(ano, "%d", tm.tm_year + 1900);

	strcpy(data_cadastro, "");
	strcat(data_cadastro, dia); // 06
	strcat(data_cadastro, "/"); // 06/
	strcat(data_cadastro, mes); // 06/08
	strcat(data_cadastro, "/"); // 06/08/
	strcat(data_cadastro, ano); // 06/08/2022
	strcat(data_cadastro, "\0"); // 06/08/2022\0 finaliza a string
	strcpy(cliente.dataCadstro, data_cadastro);

	// Cria o cliente
	printf("Informe os dados do cliente: \n");
	cliente.codigo = contador_clientes + 1;

	printf("Nome do cliente: \n");
	fgets(cliente.nome, 50, stdin);

	printf("E-mail do cliente: \n");
	fgets(cliente.email, 50, stdin);

	printf("CPF do cliente: \n");
	fgets(cliente.cpf, 20, stdin);

	printf("Data de nascimento do cliente: \n");
	fgets(cliente.dataNasciimento, 20, stdin);

	contador_clientes++;

	// Criar a conta
	contas[contador_contas].numero = contador_contas + 1;
	contas[contador_contas].cliente = cliente;
	contas[contador_contas].saldo = 0.0;
	contas[contador_contas].limite = 0.0;
	contas[contador_contas].saldoTotal = atualizacaoTotal(contas[contador_contas]);

	printf("Conta criada com sucesso! \n");
	printf("\n");
	printf("Dados da conta criada: \n");
	printf("\n");
	infoConta(contas[contador_contas]);
	contador_contas++;
	Sleep(4000);
	menu();
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
    if (contador_contas > 0) {
        int numero;
        printf("Infome número da conta: \n");
        scanf("%d", &numero);

        Conta conta = buscarContaPorNumero(numero);
        if (conta.numero == numero) {
            float valor;
            printf("Infome o valor do saque: \n");

            scanf("%f", &valor);
            sacar(conta, valor);

        }else {
            printf("Não foi emcontrado uma conta com este número %d!\n", numero);
        }

    }else {
        printf("Ainda não existem contas para saque!\n");
    }

    Sleep(2000);
    menu();
}
void efetuarDeposito(){
    if (contador_contas > 0) {
        int numero;
        printf("Infome número da conta: \n");
        scanf("%d", &numero);

        Conta conta = buscarContaPorNumero(numero);
        if (conta.numero == numero) {
            float valor;
            printf("Infome o valor do depósito: \n");

            scanf("%f", &valor);
            depositar(conta, valor);

        }else {
            printf("Não foi emcontrado uma conta com este número %d!\n", numero);
        }

    }else {
        printf("Ainda não existem contas para o depósito!\n");
    }

    Sleep(2000);
    menu();
}
void efetuarTransferencia(){
    if (contador_contas > 0) {
        int numero_origem, numero_destino;
        printf("Infome o número da sua conta: \n");
        scanf("%d", &numero_origem);

        Conta conta_origem = buscarContaPorNumero(numero_origem);

        if (conta_origem.numero == numero_origem) {
            printf("Infome o número da conta de destino: \n");
            scanf("%d", &numero_destino);

            Conta conta_destino = buscarContaPorNumero(numero_destino);

            if (conta_destino.numero == numero_destino) {
                float valor;
                printf("Infome o valor da transferência: \n");
                scanf("%f", &valor);

                transferir(conta_origem, conta_destino, valor);
            }else {
                printf("Não foi emcontrado uma conta com este número %d!\n", numero_destino);
            }
            }else {
                printf("A conta com número %d não foi encontrada!\n", numero_origem);
            }
    }else {
        printf("Ainda não existem contas para transferência!\n");
    }
    Sleep(2000);
    menu();
}
void listarConta(){
    if (contador_contas > 0) {
        for (int co = 0; co < contador_contas; co++) {
            infoConta(contas[co]);
            printf("\n");
            Sleep(1000);
        }
    }else {
        printf("Não existem contas cadastradas ainda!\n");
    }
    Sleep(2000);
    menu();
}